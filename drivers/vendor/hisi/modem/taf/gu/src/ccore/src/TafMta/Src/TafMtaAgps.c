/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaProcAgps.c
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2012��6��27��
  ����޸�   :
  ��������   : MTAģ��������ģ����Ϣ����������ʵ��
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

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaComm.h"
#include "TafMtaMain.h"
#include "AtMtaInterface.h"
#include "TafMtaTimerMgmt.h"
#include "TafMtaAgps.h"
#include "TafAppMma.h"
#include "MnComm.h"

/* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
#include "NasUtranCtrlInterface.h"
#include "TafSdcLib.h"
/* Added by l00198894 for ����+ECID����, 2013-12-10, end */


/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_AGPS_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_AGPS)

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtXcposrRptInd
 ��������  : ���������������������Ϣ��ָʾ
 �������  : VOS_UINT32 ulClearFlg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndAtXcposrRptInd(VOS_UINT32 ulClearFlg)
{
    AT_APPCTRL_STRU                     stAppCtrl;                    /* ������Ϣָ�� */
    MTA_AT_XCPOSRRPT_IND_STRU           stXcposrRptInd;

    /* ��д��Ϣ�ṹ */
    stXcposrRptInd.ulClearFlg = ulClearFlg;

    /* ��д�¼��ͻ�������Ϊ�㲥�¼� */
    stAppCtrl.usClientId      = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId          = MTA_INVALID_TAB_INDEX;

    /* ��ATģ�鷢��ID_MTA_AT_XCPOSRRPT_IND��Ϣ */
    TAF_MTA_SndAtMsg( &stAppCtrl,
                      ID_MTA_AT_XCPOSRRPT_IND,
                      sizeof(MTA_AT_XCPOSRRPT_IND_STRU),
                      (VOS_UINT8*)&stXcposrRptInd );

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtCposrInd
 ��������  : �������㷢�͵Ĳ����������ݺͲ���ָʾ
 �������  : XML_COMM_NODE_STRU    *pstNode,        XML���ڵ�
             XML_COMM_CTX_STRU     *pstXmlCommCtx   XML���洢�ṹ
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndAtCposrInd(
    XML_COMM_NODE_STRU                 *pstNode,
    XML_COMM_CTX_STRU                  *pstXmlCommCtx
)
{
    VOS_CHAR                           *pcXmlStr;                               /* XML�����׵�ַ */
    VOS_CHAR                           *pcXmlStrCur;                            /* XML������ǰλ�� */
    VOS_UINT32                          i;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulXmlLen;
    AT_APPCTRL_STRU                     stAppCtrl;                              /* ������Ϣָ�� */
    MTA_AT_CPOSR_IND_STRU              *pstCposrInd;
    XML_COMM_RESULT_ENUM_UINT32         enResult;

    /* �ڴ����롢��ʼ�� */
    pstCposrInd = PS_MEM_ALLOC(UEPS_PID_MTA, sizeof(MTA_AT_CPOSR_IND_STRU));
    if (VOS_NULL_PTR == pstCposrInd)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCposrInd: Message malloc Failed!");
        return VOS_ERR;
    }
    PS_MEM_SET(pstCposrInd, 0x00, sizeof(MTA_AT_CPOSR_IND_STRU));

    /* XML������̬�洢���롢��ʼ�� */
    pcXmlStr = PS_MEM_ALLOC( UEPS_PID_MTA, MTA_XML_TEXT_MAX_BUFF_SIZE);
    if (VOS_NULL_PTR == pcXmlStr)
    {
        PS_MEM_FREE(UEPS_PID_MTA, pstCposrInd);
        MTA_ERROR_LOG("TAF_MTA_SndCposrInd: Xml text malloc Failed!");
        return VOS_ERR;
    }
    PS_MEM_SET(pcXmlStr, 0x00, MTA_XML_TEXT_MAX_BUFF_SIZE);

    /* ����XML����, �������������򷵻�VOS_ERR*/
    ulXmlLen = MTA_XML_TEXT_MAX_BUFF_SIZE;
    enResult =  XML_COMM_BuildXMLStr(pstNode, pcXmlStr, &ulXmlLen, XML_FORMATTING_NONE);

    /* �������ʧ�ܻ���XML����������󳤶ȣ����ͷ��ڴ���˳� */
    if (XML_COMM_RESULT_SUCCEED != enResult)
    {
        PS_MEM_FREE(UEPS_PID_MTA, pcXmlStr);
        PS_MEM_FREE(UEPS_PID_MTA, pstCposrInd);
        MTA_WARNING_LOG("TAF_MTA_SndCposrInd: Build XML text Failed!");
        return VOS_ERR;
    }

    /* ��д�ϱ�����Ϊ�㲥�¼� */
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* ��д��Ϣ�ṹ */
    pcXmlStrCur          = pcXmlStr;

    /* XML�����ָ���� */
    ulLoop = (VOS_UINT32)(ulXmlLen/(MTA_CPOSR_XML_MAX_LEN));

    /* ÿ�η���1024���ֽڵ����� + '\0' */
    for (i = 0; i < ulLoop; i++)
    {
        /* ����ǰ1024���ַ�������ĩβ��Ϊ'\0' */
        PS_MEM_CPY(pstCposrInd->acXmlText, pcXmlStrCur, MTA_CPOSR_XML_MAX_LEN);
        pstCposrInd->acXmlText[MTA_CPOSR_XML_MAX_LEN] = '\0';
        pcXmlStrCur                                  += MTA_CPOSR_XML_MAX_LEN;

        /* ��ATģ�鷢��ID_MTA_AT_CPOSR_IND��Ϣ */
        TAF_MTA_SndAtMsg( &stAppCtrl,
                          ID_MTA_AT_CPOSR_IND,
                          sizeof(MTA_AT_CPOSR_IND_STRU),
                          (VOS_UINT8*)pstCposrInd);

    }

    /* �ٷ���ʣ�µ����� + '\0' */
    PS_MEM_SET(pstCposrInd, 0, sizeof(MTA_AT_CPOSR_IND_STRU));
    PS_MEM_CPY(pstCposrInd->acXmlText, pcXmlStrCur, (VOS_UINT32)(ulXmlLen - (VOS_UINT32)(pcXmlStrCur - pcXmlStr)));
    pstCposrInd->acXmlText[(VOS_UINT32)(ulXmlLen - (VOS_UINT32)(pcXmlStrCur - pcXmlStr))] = '\0';

    /* ��ATģ�鷢��ID_MTA_AT_CPOSR_IND��Ϣ */
    TAF_MTA_SndAtMsg( &stAppCtrl,
                      ID_MTA_AT_CPOSR_IND,
                      sizeof(MTA_AT_CPOSR_IND_STRU),
                      (VOS_UINT8*)pstCposrInd);

    /* �ͷ�������ڴ� */
    PS_MEM_FREE(UEPS_PID_MTA, pstCposrInd);
    PS_MEM_FREE(UEPS_PID_MTA, pcXmlStr);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcAssistData
 ��������  : �������㷢�͵Ĳ����������ݣ�ͨ��ID_MTA_AT_CPOSR_IND��Ϣ���͸�ATģ��
 �������  : AGPS_ASSIST_DATA_STRU *pstAssistData
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_UINT32 TAF_MTA_ProcAssistData(AGPS_ASSIST_DATA_STRU *pstAssistData)
{
    XML_COMM_CTX_STRU                   stXmlCommCtx;                           /* XML���洢�ṹ */
    XML_COMM_NODE_STRU                 *pstNodePos;                             /* XML���ڵ� */
    XML_COMM_NODE_STRU                 *pstNodeAssistData;
    VOS_UINT32                          ucResult;
    XML_COMM_RESULT_ENUM_UINT32         enXmlRslt;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stXmlCommCtx, 0x00, sizeof(XML_COMM_CTX_STRU));

    /* ��ʼ��XmlCtx */
    if (XML_COMM_RESULT_SUCCEED != XML_COMM_InitXMLCtx(&stXmlCommCtx))
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcAssistData: WARNING: Init xmlCtx fail!");
        return VOS_ERR;
    }

    /* ����XML���ṹ���캯��,����XML�ṹ�� */
    pstNodePos = TAF_MTA_AGPS_ConvertPos(&stXmlCommCtx);
    if (VOS_NULL_PTR == pstNodePos)
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcAssistData: WARNING: Create pos fail!");
        return VOS_ERR;
    }

    /* ����Assist Data���ݽṹ */
    pstNodeAssistData = TAF_MTA_AGPS_ConvertAssistData(&stXmlCommCtx, pstAssistData);
    if (VOS_NULL_PTR == pstNodeAssistData)
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcAssistData: WARNING: Create assist data fail!");
        return VOS_ERR;
    }

    /* ����������POS���ṹ */
    enXmlRslt = XML_COMM_AddAChildNode(pstNodePos, pstNodeAssistData, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != enXmlRslt)
    {
        XML_WARNING_LOG("XML_COMM_AddAChildNode: Error!");
    }

    /* XML��ת��ΪXML���������͵�ATģ�� */
    ucResult = TAF_MTA_SndAtCposrInd(pstNodePos, &stXmlCommCtx);

    /* �ͷ�XMLCTX��Դ */
    XML_COMM_ClearXMLCtx(&stXmlCommCtx);

    return ucResult;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetRemainDgpsCorrectionsNodeNum
 ��������  : <assist_data>�е�<GPS_assist>�ڵ��У�<DGPS_corrections>��ȥ��һ��
             ���⣬��ʣ��ĸ���
 �������  : AGPS_ASSIST_DATA_STRU *pstAssistData
 �������  : VOS_UINT32            *pulRemainDgpsCorrectionNum
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��07��04��
    ��    ��   : L47619
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_GetRemainDgpsCorrectionsNodeNum(
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist,
    VOS_UINT32                         *pulRemainDgpsCorrectionNum
)
{
    if (VOS_TRUE == pstGpsAssist->bitOpDgpsCorrection)
    {
        if (MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET <= pstGpsAssist->stDgpsCorrection.ulDgpsCorrectionNum)
        {
            *pulRemainDgpsCorrectionNum = pstGpsAssist->stDgpsCorrection.ulDgpsCorrectionNum
                                          - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET;
        }
        else
        {
            *pulRemainDgpsCorrectionNum = 0;
        }
    }
    else
    {
        *pulRemainDgpsCorrectionNum = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetRemainGpsRtIntegrityNodeNum
 ��������  : <assist_data>�е�<GPS_assist>�ڵ��У�<GPS_rt_integrity>��ȥ��һ��
             ���⣬��ʣ��ĸ���
 �������  : AGPS_ASSIST_DATA_STRU *pstAssistData
 �������  : VOS_UINT32            *pulRemainBadSatListBadSatListNum
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��07��04��
    ��    ��   : L47619
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_GetRemainGpsRtIntegrityNodeNum(
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist,
    VOS_UINT32                         *pulRemainBadSatListBadSatListNum
)
{
    if (VOS_TRUE == pstGpsAssist->bitOpGpsRealTimeIntegrity)
    {
        if (MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET <= pstGpsAssist->stGpsRealTimeIntegrity.ulBadSatListBadSatListNum)
        {
            *pulRemainBadSatListBadSatListNum = pstGpsAssist->stGpsRealTimeIntegrity.ulBadSatListBadSatListNum
                                                - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET;
        }
        else
        {
            *pulRemainBadSatListBadSatListNum = 0;
        }
    }
    else
    {
        *pulRemainBadSatListBadSatListNum = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcExtraAssistData
 ��������  : <assist_data>�е�<GPS_assist>�ڵ��У�<DGPS_corrections>��<GPS_rt_integrity>�ӽڵ���27007 XML DTD�淶��
             ���ǵ����ģ���������ϱ��Ľṹ�������Ƕ���ġ����ڴˣ�MTA��Ҫ�����⴦��: ��<DGPS_corrections>��
             <GPS_rt_integrity>����1�������״��ϱ���<assist_data> XML�У�ֻ�ϱ���һ����ʣ��������ϱ���ÿ��
             <assist_data>�ϱ��д�һ����ͨ��ID_MTA_AT_CPOSR_IND��Ϣ���͸�ATģ��
 �������  : AGPS_ASSIST_DATA_STRU *pstAssistData
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��07��04��
    ��    ��   : L47619
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_ProcExtraAssistData(AGPS_ASSIST_DATA_STRU *pstAssistData)
{
    AGPS_GPS_ASSIST_STRU               *pstGpsAssist;
    AGPS_ASSIST_DATA_STRU              *pstTmpAssistData;
    VOS_UINT32                          ulRemainDgpsCorrectionNum;
    VOS_UINT32                          ulRemainBadSatListBadSatListNum;
    VOS_UINT32                          ulFirstLoop;
    VOS_UINT32                          ulSecondLoop;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulResult;

    pstGpsAssist = &pstAssistData->stGpsAssist;

    /* ��ȡʣ���<DGPS_corrections>�ڵ���� */
    TAF_MTA_GetRemainDgpsCorrectionsNodeNum(pstGpsAssist, &ulRemainDgpsCorrectionNum);

    /* ��ȡʣ���<GPS_rt_integrity>�ڵ���� */
    TAF_MTA_GetRemainGpsRtIntegrityNodeNum(pstGpsAssist, &ulRemainBadSatListBadSatListNum);

    /* û��ʣ���<DGPS_corrections>�ڵ����<GPS_rt_integrity>�ڵ㣬���ز����� */
    if ((0 == ulRemainDgpsCorrectionNum)
     && (0 == ulRemainBadSatListBadSatListNum))
    {
        return VOS_OK;
    }

    /* ʣ���<DGPS_corrections>�ڵ��������15����15���� */
    if (ulRemainDgpsCorrectionNum > (AGPS_MAX_SAT_NUM - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET))
    {
        ulRemainDgpsCorrectionNum = AGPS_MAX_SAT_NUM - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET;
    }

    /* ʣ���<GPS_rt_integrity>�ڵ��������15����15���� */
    if (ulRemainBadSatListBadSatListNum > (AGPS_MAX_SAT_NUM - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET) )
    {
        ulRemainBadSatListBadSatListNum = AGPS_MAX_SAT_NUM - MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET;
    }

    /* �����һ��ѭ���͵ڶ���ѭ����ѭ������ */
    if (ulRemainDgpsCorrectionNum >= ulRemainBadSatListBadSatListNum)
    {
        ulFirstLoop  = ulRemainBadSatListBadSatListNum;
        ulSecondLoop = ulRemainDgpsCorrectionNum - ulRemainBadSatListBadSatListNum;
    }
    else
    {
        ulFirstLoop  = ulRemainDgpsCorrectionNum;
        ulSecondLoop = ulRemainBadSatListBadSatListNum - ulRemainDgpsCorrectionNum;
    }

    /* ���붯̬�ڴ棬���ڻ��湹���pstTmpGpsAssist�ṹ�� */
    pstTmpAssistData = (AGPS_ASSIST_DATA_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, sizeof(AGPS_ASSIST_DATA_STRU));
    if (VOS_NULL_PTR == pstTmpAssistData)
    {
        MTA_ERROR_LOG("TAF_MTA_ProcExtraAssistData: ERROR: Alloc mem fail!");
        return VOS_ERR;
    }

    PS_MEM_SET(pstTmpAssistData, 0x00, sizeof(AGPS_ASSIST_DATA_STRU));

    /* ��һ��ѭ�� */
    for (ulLoop = 0; ulLoop < ulFirstLoop; ulLoop++)
    {
        pstTmpAssistData->bitOpGpsAssist = VOS_TRUE;
        /* �Ƚ�bitλȫ��Ϊ0��������<DGPS_corrections>��<GPS_rt_integrity>�ڵ��bitλ */
        *((VOS_UINT32 *)(&pstTmpAssistData->stGpsAssist))       = 0;
        pstTmpAssistData->stGpsAssist.bitOpDgpsCorrection       = VOS_TRUE;
        pstTmpAssistData->stGpsAssist.bitOpGpsRealTimeIntegrity = VOS_TRUE;

        /* ������ѭ������Ӧ�Ľڵ��Ƶ���Ӧ�ṹ��ĵ�һ��λ�� */
        pstTmpAssistData->stGpsAssist.stDgpsCorrection.ulDgpsCorrectionNum = 1;
        PS_MEM_CPY(&pstTmpAssistData->stGpsAssist.stDgpsCorrection.astUpDgpsCorrection[0],
                   &pstGpsAssist->stDgpsCorrection.astUpDgpsCorrection[ulLoop + MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET],
                   sizeof(AGPS_UP_DGPS_CORRECTION_STRU));

        pstTmpAssistData->stGpsAssist.stGpsRealTimeIntegrity.ulBadSatListBadSatListNum = 1;
        pstTmpAssistData->stGpsAssist.stGpsRealTimeIntegrity.ausBadSatListBadSatList[0]
                   = pstGpsAssist->stGpsRealTimeIntegrity.ausBadSatListBadSatList[ulLoop + MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET];

        /* ����<assist_data> */
        ulResult = TAF_MTA_ProcAssistData(pstTmpAssistData);
        if (VOS_OK != ulResult)
        {
            PS_MEM_FREE(UEPS_PID_MTA, pstTmpAssistData);
            return ulResult;
        }
    }

    /* �ڶ���ѭ�� */
    for (ulLoop = 0; ulLoop < ulSecondLoop; ulLoop++)
    {
        pstTmpAssistData->bitOpGpsAssist = VOS_TRUE;
        /* �Ƚ�bitλȫ��Ϊ0���ٸ��ݽڵ�������<DGPS_corrections>��<GPS_rt_integrity>�ڵ��bitλ */
        *((VOS_UINT32 *)(&pstTmpAssistData->stGpsAssist)) = 0;

        if (ulRemainDgpsCorrectionNum >= ulRemainBadSatListBadSatListNum)
        {
            pstTmpAssistData->stGpsAssist.bitOpDgpsCorrection = VOS_TRUE;

            /* ������ѭ������Ӧ�Ľڵ��Ƶ���Ӧ�ṹ��ĵ�һ��λ�� */
            pstTmpAssistData->stGpsAssist.stDgpsCorrection.ulDgpsCorrectionNum = 1;
            PS_MEM_CPY(&pstTmpAssistData->stGpsAssist.stDgpsCorrection.astUpDgpsCorrection[0],
                       &pstGpsAssist->stDgpsCorrection.astUpDgpsCorrection[ulLoop + MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET + ulFirstLoop],
                       sizeof(AGPS_UP_DGPS_CORRECTION_STRU));
        }
        else
        {
            pstTmpAssistData->stGpsAssist.bitOpGpsRealTimeIntegrity = VOS_TRUE;

            /* ������ѭ������Ӧ�Ľڵ��Ƶ���Ӧ�ṹ��ĵ�һ��λ�� */
            pstTmpAssistData->stGpsAssist.stGpsRealTimeIntegrity.ulBadSatListBadSatListNum = 1;
            pstTmpAssistData->stGpsAssist.stGpsRealTimeIntegrity.ausBadSatListBadSatList[0]
                    = pstGpsAssist->stGpsRealTimeIntegrity.ausBadSatListBadSatList[ulLoop + MTA_AGPS_CVRT_EXTRA_ASSI_DATA_OFFSET + ulFirstLoop];
        }

        /* ����<assist_data> */
        ulResult = TAF_MTA_ProcAssistData(pstTmpAssistData);
        if (VOS_OK != ulResult)
        {
            PS_MEM_FREE(UEPS_PID_MTA, pstTmpAssistData);
            return ulResult;
        }
    }

    PS_MEM_FREE(UEPS_PID_MTA, pstTmpAssistData);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcMeasureReq
 ��������  : �������㷢�͵Ĳ���ָʾ��ͨ��ID_MTA_AT_CPOSR_IND��Ϣ���͸�ATģ��
 �������  : AGPS_MEASURE_REQ_STRU *pstMeasureReq
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_UINT32 TAF_MTA_ProcMeasureReq(AGPS_MEASURE_REQ_STRU *pstMeasureReq)
{
    XML_COMM_CTX_STRU                   stXmlCommCtx;                           /* XML���洢�ṹ */
    XML_COMM_NODE_STRU                 *pstNodePos;                             /* XML���ڵ� */
    XML_COMM_NODE_STRU                 *pstNodeMeasureReq;                      /* XML���ڵ� */
    VOS_UINT32                          ulResult;
    XML_COMM_RESULT_ENUM_UINT32         enXmlRslt;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stXmlCommCtx, 0x00, sizeof(XML_COMM_CTX_STRU));

    /* ��ʼ��XmlCtx */
    if (XML_COMM_RESULT_SUCCEED != XML_COMM_InitXMLCtx(&stXmlCommCtx))
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcMeasureReq: WARNING: Init xmlCtx fail!");
        return VOS_ERR;
    }

    /* ����XML���ṹ���캯��,����XML�ṹ�� */
    pstNodePos = TAF_MTA_AGPS_ConvertPos(&stXmlCommCtx);
    if (VOS_NULL_PTR == pstNodePos)
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcMeasureReq: WARNING: Create Pos fail!");
        return VOS_ERR;
    }

    /* ����Measure Req���ݽṹ */
    pstNodeMeasureReq = TAF_MTA_AGPS_ConvertMeasureReq(&stXmlCommCtx, pstMeasureReq);
    if (VOS_NULL_PTR == pstNodeMeasureReq)
    {
        XML_COMM_ClearXMLCtx(&stXmlCommCtx);
        MTA_WARNING_LOG("TAF_MTA_ProcMeasureReq: WARNING: Create MeasureReq fail!");
        return VOS_ERR;
    }

    /* ����������POS���ṹ */
    enXmlRslt = XML_COMM_AddAChildNode(pstNodePos, pstNodeMeasureReq, VOS_NULL_PTR);
    if (XML_COMM_RESULT_SUCCEED != enXmlRslt)
    {
        XML_WARNING_LOG("XML_COMM_AddAChildNode: Error!");
    }
    /* XML��ת��ΪXML���������͵�ATģ�� */
    ulResult = TAF_MTA_SndAtCposrInd(pstNodePos, &stXmlCommCtx);

    /* �ͷ�XMLCTX��Դ */
    XML_COMM_ClearXMLCtx(&stXmlCommCtx);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAsPosCnf
 ��������  : MTA�����㷢����Ϣ����
 �������  : TAF_MMA_RAT_TYPE_ENUM_UINT8    enPhRatType ��ǰפ����ģʽ
             MTA_RRC_POSITION_CNF_STRU     *pstMsg      ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_VOID TAF_MTA_SndAsPosCnf(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enPhRatType,
    MTA_RRC_POSITION_CNF_STRU          *pstPosCnf
)
{
    VOS_UINT32                          ulLength;
    MTA_RRC_POSITION_CNF_STRU          *pstPositionCnf;

    /* ����ṹ�ڴ� */
    ulLength     = sizeof(MTA_RRC_POSITION_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPositionCnf = (MTA_RRC_POSITION_CNF_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstPositionCnf)
    {
        MTA_WARNING_LOG("TAF_MTA_SndAsPosCnf: WARNING: Memory malloc failed!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstPositionCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPositionCnf->stMsgHeader.ulMsgName         = ID_MTA_RRC_MSG_POSITION_CNF;
    if (TAF_MMA_RAT_GSM == enPhRatType)
    {
        pstPositionCnf->stMsgHeader.ulReceiverPid = UEPS_PID_GAS;
    }
    else
    {
        pstPositionCnf->stMsgHeader.ulReceiverPid = WUEPS_PID_WCOM;
    }
    PS_MEM_CPY(((VOS_UINT8*)pstPositionCnf + sizeof(MSG_HEADER_STRU)),
               ((VOS_UINT8*)pstPosCnf + sizeof(MSG_HEADER_STRU)),
               (sizeof(MTA_RRC_POSITION_CNF_STRU) - sizeof(MSG_HEADER_STRU)));

    /* ������Ϣ��ASģ�� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstPositionCnf))
    {
        MTA_WARNING_LOG("TAF_MTA_SndAsPosCnf():WARNING:SEND MSG FIAL");
    }
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyMsg
 ��������  : MTA������㷢����Ϣ����
 �������  : TAF_MMA_RAT_TYPE_ENUM_UINT8    enPhRatType ��ǰפ����ģʽ
             MTA_AT_CGPSCLOCK_ENUM_UINT32   enCgpsClock
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��03��11��
    ��    ��   : l00198894
    �޸�����   : BODYSAR��Ŀ��������
  4.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhySetGpsRfClockReq(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRatType,
    MTA_AT_CGPSCLOCK_ENUM_UINT32        enCgpsClock
)
{
    VOS_UINT32                          ulLength;
    MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU  *pstMtaPhyCgpsClockReq;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyCgpsClockReq = (MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaPhyCgpsClockReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhySetGpsRfClockReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaPhyCgpsClockReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    if (TAF_MMA_RAT_GSM == enPhRatType)
    {
        pstMtaPhyCgpsClockReq->ulReceiverPid    = DSP_PID_GPHY;
        pstMtaPhyCgpsClockReq->usMsgID          = ID_MTA_GPHY_SET_GPS_RF_CLOCK_REQ;
    }
    else
    {
        pstMtaPhyCgpsClockReq->ulReceiverPid    = DSP_PID_WPHY;
        pstMtaPhyCgpsClockReq->usMsgID          = ID_MTA_WPHY_SET_GPS_RF_CLOCK_REQ;
    }

    if (MTA_AT_CGPSCLOCK_STOP == enCgpsClock)
    {
        pstMtaPhyCgpsClockReq->enGpsClockState = MTA_PHY_GPS_RF_CLOCK_STATE_STOP;
    }
    else
    {
        pstMtaPhyCgpsClockReq->enGpsClockState = MTA_PHY_GPS_RF_CLOCK_STATE_RUNNING;
    }

    /* ������Ϣ��DSPģ�� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyCgpsClockReq))
    {
        MTA_WARNING_LOG("TAF_MTA_SndPhySetGpsRfClockReq():WARNING:SEND MSG FIAL");
    }
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_FreeAgpsXmlCtx
 ��������  : �ͷŴ洢XML��������������Դ
 �������  : AGPS_MEASURE_REQ_STRU *pstMeasureReq
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_FreeAgpsXmlCtx(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx)
{
    /* �ͷ�AGPS XML���������� */
    if (VOS_NULL_PTR != pstAgpsCtx->stXmlText.pcBufHead)
    {
        PS_MEM_FREE(UEPS_PID_MTA, pstAgpsCtx->stXmlText.pcBufHead);
        pstAgpsCtx->stXmlText.pcBufHead = VOS_NULL_PTR;
        pstAgpsCtx->stXmlText.pcBufCur  = VOS_NULL_PTR;
    }
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : TAF_MTA_DealCposSetReqAbnormal
 ��������  : MTAģ����XML�������쳣����
 �������  : AGPS_MEASURE_REQ_STRU *pstMeasureReq
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_DealCposSetReqAbnormal(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    XML_COMM_CTX_STRU                  *pstXmlCtx,
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx
)
{
    /* �ͷ�AGPS XML���������� */
    TAF_MTA_FreeAgpsXmlCtx(pstAgpsCtx);

    /* �ͷ�XML����������ڴ� */
    if (VOS_NULL_PTR != pstXmlCtx)
    {
        XML_COMM_ClearXMLCtx(pstXmlCtx);
    }

    /* ��ATģ��ظ�������Ϣ */
    TAF_MTA_SndAtCposSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_ERROR);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_MgmtCposTimer
 ��������  : MTA�����·���λ��Ϣ�����ж�ʱ������
 �������  : VOS_UINT32     ulTimerFlg  ������ֹͣ��ʱ���ı�־
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_MgmtCposTimer(
    VOS_UINT32                          ulTimerFlg
)
{
    if (VOS_OK != ulTimerFlg)
    {
        if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF))
        {
            TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF);
        }

        /* ����2s������ʱ�� */
        (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF, TI_TAF_MTA_CPOS_TIMER_LEN);
    }
    else
    {
        /* ֹͣ2s������ʱ�� */
        if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF))
        {
            TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SaveXmlText
 ��������  : �洢AT�·���XML����
 �������  : TAF_MTA_AGPS_CTX_STRU *pstAgpsCtx  XML�����洢��������Դ
             VOS_CHAR              *pcXml       XML����
             VOS_UINT32             ulXmlLen    XML��������
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_SaveXmlText(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx,
    VOS_CHAR                           *pcXml,
    VOS_UINT32                          ulXmlLen
)
{
    VOS_UINT32                          ulXmlCount;
    /* ��һ�δ洢XML������Ϊ�����  8193 �ֽ��ڴ�(���һ���ֽڴ���ַ���������'\0')*/
    if (VOS_NULL_PTR == pstAgpsCtx->stXmlText.pcBufHead)
    {
        pstAgpsCtx->stXmlText.pcBufHead = PS_MEM_ALLOC(UEPS_PID_MTA,
                                                       MTA_XML_TEXT_MAX_BUFF_SIZE + 1);
        if (VOS_NULL_PTR == pstAgpsCtx->stXmlText.pcBufHead)
        {
            MTA_WARNING_LOG("TAF_MTA_SaveXmlText: WARNING: Memory malloc failed!");
            return VOS_ERR;
        }

        pstAgpsCtx->stXmlText.pcBufCur = pstAgpsCtx->stXmlText.pcBufHead;
    }

    /* ���������ȴ���XML���������ճ��ȣ��򷵻�VOS_ERR */
    ulXmlCount = (pstAgpsCtx->stXmlText.pcBufCur - pstAgpsCtx->stXmlText.pcBufHead) + ulXmlLen;
    if (MTA_XML_TEXT_MAX_BUFF_SIZE < ulXmlCount)
    {
        MTA_WARNING_LOG("TAF_MTA_SaveXmlText: WARNING: Xml text is longer than memory!");
        return VOS_ERR;
    }

    /* ����XML���� */
    PS_MEM_CPY(pstAgpsCtx->stXmlText.pcBufCur,
               pcXml,
               ulXmlLen);

    pstAgpsCtx->stXmlText.pcBufCur += ulXmlLen;

    /* XML�����Ľ�β��ΪNULL */
    *pstAgpsCtx->stXmlText.pcBufCur = '\0';

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_CheckXmlEnd
 ��������  : ����XML�Ľ�β��ǩ
 �������  : TAF_MTA_AGPS_CTX_STRU *pstAgpsCtx  �洢XML������������
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_CheckXmlEnd(
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx
)
{
    VOS_CHAR                           *pcBufCur;

    /* ��XML������ĩβ��ʼ���ҵ�һ��'>' */
    pcBufCur = pstAgpsCtx->stXmlText.pcBufCur - 1;
    /*lint -e961*/
    while(('>' != *(pcBufCur--)))
    {
        if (pstAgpsCtx->stXmlText.pcBufHead == pcBufCur)
        {
            return VOS_ERR;
        }
    }

    /* ��XML������ĩβ��ʼ���ҵ�һ��'<' */
    while(('<' != *(pcBufCur--)))
    {
        if (pstAgpsCtx->stXmlText.pcBufHead == pcBufCur)
        {
            return VOS_ERR;
        }
    }
    /*lint +e961*/

    /* �Աȱ�ǩ���� */
    pcBufCur += 1;
    if (VOS_OK == PS_MEM_CMP(MTA_AGPS_LABEL_POS_END, pcBufCur, VOS_StrLen(MTA_AGPS_LABEL_POS_END)))
    {
        pcBufCur += VOS_StrLen(MTA_AGPS_LABEL_POS_END);

        /* "</pos"��������ַ���ɸ��ָ����ͬ����Ϊ�Ϸ����� */
        while(pstAgpsCtx->stXmlText.pcBufCur != pcBufCur)
        {
            if ((VOS_TRUE != XML_COMM_IsSeparator(*pcBufCur))
             && ('>' != *pcBufCur))
            {
                return VOS_ERR;
            }
            pcBufCur++;
        }

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_FillXmlStru
 ��������  : �洢AT�·���XML����
 �������  : XML_COMM_NODE_STRU        *pstXmlNode      ���ڵ�
             MTA_RRC_POSITION_CNF_STRU *pPositionCnf    ��Ϣ�ṹ
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_FillXmlStru(
    XML_COMM_NODE_STRU                 *pstXmlNode,
    MTA_RRC_POSITION_CNF_STRU          *pstPositionCnf
)
{
    XML_COMM_NODE_STRU                 *pstXmlFirstNode;
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    /* ��ȡ�ӽڵ��� */
    if (MTA_AGPS_XML_NODE_COUNT_1 != XML_COMM_GetChildCount(pstXmlNode))
    {
        return VOS_ERR;
    }

    /*��ȡ�ӽڵ� */
    pstXmlFirstNode = XML_COMM_GetChildNodeByIndex(pstXmlNode, 0);
    if (VOS_NULL_PTR ==pstXmlFirstNode)
    {
        return VOS_ERR;
    }

    /* ��д���ݽṹ */
    if (VOS_TRUE == XML_COMM_CheckLabelName(pstXmlFirstNode, MTA_AGPS_LABEL_LOCATION))
    {
        ulResult = TAF_MTA_AGPS_FillLocationInfo(pstXmlFirstNode, &pstPositionCnf->u.stLocationInfo);
        pstPositionCnf->enResultTypeChoice  = AGPS_POSITION_RESULT_TYPE_LOCATION;
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstXmlFirstNode, MTA_AGPS_LABEL_GPS_MEAS))
    {
        ulResult = TAF_MTA_AGPS_FillGpsMeas(pstXmlFirstNode, &pstPositionCnf->u.stGpsMeasInfo);
        pstPositionCnf->enResultTypeChoice  = AGPS_POSITION_RESULT_TYPE_MEAS;
    }
    else if ( VOS_TRUE == XML_COMM_CheckLabelName(pstXmlFirstNode, MTA_AGPS_LABEL_GPS_ASSIST_REQ))
    {
        ulResult = TAF_MTA_AGPS_FillGpsAssistReq(pstXmlFirstNode, &pstPositionCnf->u.stAssistDataReq);
        pstPositionCnf->enResultTypeChoice  = AGPS_POSITION_RESULT_TYPE_ASSIST_REQ;
    }
    else if (VOS_TRUE == XML_COMM_CheckLabelName(pstXmlFirstNode, MTA_AGPS_LABEL_POS_ERR))
    {
        ulResult = TAF_MTA_AGPS_FillPosErr(pstXmlFirstNode, &pstPositionCnf->u.stPosErr);
        pstPositionCnf->enResultTypeChoice  = AGPS_POSITION_RESULT_TYPE_ERROR;
    }
    else
    {
        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
       return VOS_ERR;
    }

    return VOS_OK;
}
#endif /* FEATURE_AGPS */

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtCposSetCnf
 ��������  : MTA����+CPOS��Ϣ�󣬸�ATģ�����Ϣ
 �������  : AT_MTA_MSG_STRU                *pstAtMtaReqMsg   AT��MTA���͵���Ϣ
             AT_MTA_MSG_TYPE_ENUM_UINT32     enErr            ������
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_SndAtCposSetCnf (
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    MTA_AT_RESULT_ENUM_UINT32           enErr
)
{
    MTA_AT_CPOS_CNF_STRU                stMtaAtCposCnf;

    /* ������Ϣ��ATģ�� */
    stMtaAtCposCnf.enResult = enErr;

    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_CPOS_SET_CNF,
                      sizeof(MTA_AT_CPOS_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtCposCnf );
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtCgpsClockSetCnf
 ��������  : MTA����^CGPSCLOCK��Ϣ���ATģ�����Ϣ
 �������  : AT_MTA_MSG_STRU   *pstAtMtaReqMsg   AT��MTA���͵���Ϣ
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_SndAtCgpsClockSetCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    AT_MTA_MSG_TYPE_ENUM_UINT32         enErr)
{
    MTA_AT_CGPSCLOCK_CNF_STRU           stMtaAtCgpsClockCnf;

    /* ���ͽ����ATģ�� */
    stMtaAtCgpsClockCnf.enResult = enErr;

    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_CGPSCLOCK_SET_CNF,
                      sizeof(MTA_AT_CGPSCLOCK_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtCgpsClockCnf );
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtCposSetReq
 ��������  : ����ATģ�鷢�͵�ID_AT_MTA_CPOS_SET_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtCposSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;                     /* �յ�AT��������Ϣָ�� */
#if (FEATURE_ON == FEATURE_AGPS)
    VOS_UINT32                          ulResult;
    XML_COMM_CTX_STRU                   stXmlCtx;
    XML_COMM_NODE_STRU                 *pstXmlNode;
    AT_MTA_CPOS_REQ_STRU               *pstAtMtaCposReq;
    TAF_MTA_AGPS_CTX_STRU              *pstAgpsCtx;
    MTA_RRC_POSITION_CNF_STRU          *pstPositionCnf;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;                              /* ��ǰפ��ģʽ */

    enRatType = TAF_SDC_GetSysMode();
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

#endif

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg  = (AT_MTA_MSG_STRU*)pMsg;

#if (FEATURE_ON == FEATURE_AGPS)
    pstAtMtaCposReq = (AT_MTA_CPOS_REQ_STRU*)pstAtMtaReqMsg->aucContent;
    pstAgpsCtx      = VOS_NULL_PTR;
    PS_MEM_SET(&stXmlCtx, 0x00, sizeof(XML_COMM_CTX_STRU));

    /* ��ȡAGPS XML��Դ������ */
    pstAgpsCtx = TAF_MTA_GetMtaAgpsCtxAddr();

    /* ����ǰCPOS����ΪCANCEL�����ͷ�֮ǰ������ڴ棬����AT������Ϣ */
    if (MTA_AT_CPOS_CANCEL == pstAtMtaCposReq->enCposOpType)
    {
        TAF_MTA_FreeAgpsXmlCtx(pstAgpsCtx);
        TAF_MTA_SndAtCposSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_NO_ERROR);
        return;
    }

    /* �洢XML���� */
    MTA_WARNING1_LOG("TAF_MTA_RcvAtCposSetReq: Xml text Length:", pstAtMtaCposReq->ulXmlLength);
    ulResult = TAF_MTA_SaveXmlText(pstAgpsCtx,
                                   pstAtMtaCposReq->acXmlText,
                                   pstAtMtaCposReq->ulXmlLength);
    if (VOS_OK != ulResult)
    {
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, VOS_NULL_PTR, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: Xml text Saving failed!");
        return;
    }

    /* �жϵ�ǰXML�����Ƿ����������жϽ����Ϊ��ͣ������ʱ���Ŀ��� */
    ulResult = TAF_MTA_CheckXmlEnd(pstAgpsCtx);

    /* ��������ֹͣ2s������ʱ���������ȹرն�ʱ��������������2S��ʱ�� */
    TAF_MTA_MgmtCposTimer(ulResult);

    /* XML��������������ATģ��ظ���Ϣ */
    if (VOS_OK != ulResult)
    {
        TAF_MTA_SndAtCposSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_NO_ERROR);
        return;
    }

    /* ��ȡ��ǰפ����ģʽ,����ǰģʽ��ΪG/W,����ERROR */

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    if ((TAF_SDC_SYS_MODE_GSM != enRatType)
     && (TAF_SDC_SYS_MODE_WCDMA != enRatType))
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
    {
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, VOS_NULL_PTR, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: RatType is not G or W!");
        return;
    }

    /* ����XML������������,����XML�ṹ�� */
    if (XML_COMM_RESULT_SUCCEED != XML_COMM_InitXMLCtx(&stXmlCtx))
    {
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, &stXmlCtx, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: Xml initialization failed!");
        return;
    }
    pstXmlNode = XML_COMM_BuildXMLTree( pstAgpsCtx->stXmlText.pcBufHead,
                                        &stXmlCtx);

    if (VOS_NULL_PTR == pstXmlNode)
    {
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, &stXmlCtx, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: Build xml tree failed!");
        return;
    }

    /* ����ṹ�ڴ� */
    pstPositionCnf = (MTA_RRC_POSITION_CNF_STRU*)PS_MEM_ALLOC(UEPS_PID_MTA,
                                                            sizeof(MTA_RRC_POSITION_CNF_STRU));
    if (VOS_NULL_PTR == pstPositionCnf)
    {
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, &stXmlCtx, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: Memory malloc failed!");
        return;
    }
    PS_MEM_SET(pstPositionCnf, 0x00, sizeof(MTA_RRC_POSITION_CNF_STRU));

    /* ���ø�����ǩ���캯����Ϊ��Ϣ�ṹ�����ڴ棬��дXML���ݽṹ */
    ulResult = TAF_MTA_FillXmlStru(pstXmlNode, pstPositionCnf);

    /* �������ʧ�ܣ����ͷ�������ڴ棬��ATģ�鷵��VOS_ERR */
    if (VOS_OK != ulResult)
    {
        PS_MEM_FREE(UEPS_PID_MTA, pstPositionCnf);
        TAF_MTA_DealCposSetReqAbnormal(pstAtMtaReqMsg, &stXmlCtx, pstAgpsCtx);
        MTA_WARNING_LOG("TAF_MTA_RcvAtCposSetReq: WARNING: Fill xml structure failed!");
        return;
    }

    /* ������Ϣ������� */
    TAF_MTA_SndAsPosCnf(enRatType, pstPositionCnf);

    /* �ͷŷ�����ڴ� */
    XML_COMM_ClearXMLCtx(&stXmlCtx);
    TAF_MTA_FreeAgpsXmlCtx(pstAgpsCtx);
    PS_MEM_FREE(UEPS_PID_MTA, pstPositionCnf);

    /* ��ATģ��ظ���Ϣ */
    TAF_MTA_SndAtCposSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_NO_ERROR);
    return;
#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־����ATģ��ظ�������Ϣ */
    TAF_MTA_SndAtCposSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_ERROR);
    MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: Msg is unexpected!");
    return;
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiCposSetReqExpired
 ��������  : CPOS�·���λ��Ϣ��ʱ����
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiCposSetReqExpired(VOS_VOID *pMsg)
{
#if (FEATURE_ON == FEATURE_AGPS)
    TAF_MTA_AGPS_CTX_STRU                  *pstAgpsCtx;

    /* �ͷ��������Դ */
    pstAgpsCtx = TAF_MTA_GetMtaAgpsCtxAddr();

    /* �ͷ�AGPS XML���������� */
    if (VOS_NULL_PTR != pstAgpsCtx->stXmlText.pcBufHead)
    {
        PS_MEM_FREE(UEPS_PID_MTA, pstAgpsCtx->stXmlText.pcBufHead);
        pstAgpsCtx->stXmlText.pcBufHead = VOS_NULL_PTR;
        pstAgpsCtx->stXmlText.pcBufCur  = VOS_NULL_PTR;
    }

    return;
#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־�����Ը���Ϣ */
    MTA_WARNING_LOG("TAF_MTA_RcvTiCposSetReqExpired: WARNING: Msg is unexpected!");
    return;
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRrcMsgPositionReq
 ��������  : �������㷢�͵�ID_RRC_MTA_MSG_POSITION_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

  2.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcMsgPositionReq(VOS_VOID *pMsg)
{
#if (FEATURE_ON == FEATURE_AGPS)
    MTA_RRC_POSITION_REQ_STRU          *pstMtaRrcPositionReqMsg;           /* ������Ϣָ�� */
    VOS_UINT32                          ulResult;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;                              /* ��ǰפ��ģʽ */

    enRatType = TAF_SDC_GetSysMode();

    /* �ֲ�������ʼ�� */
    pstMtaRrcPositionReqMsg = (MTA_RRC_POSITION_REQ_STRU*)pMsg;
    ulResult                = VOS_ERR;

    /* ��ȡ��ǰפ����ģʽ,����ǰģʽ��ΪG/W,����ERROR */
    if ((TAF_SDC_SYS_MODE_GSM != enRatType)
     && (TAF_SDC_SYS_MODE_WCDMA != enRatType))
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: RatType is not G or W!");
        return;
    }

    /* �ж��Ƿ��ϱ���ո�������ָʾ */
    if (PS_TRUE == pstMtaRrcPositionReqMsg->enDeleteAssistDataFlag)
    {
        ulResult = TAF_MTA_SndAtXcposrRptInd((VOS_UINT32)pstMtaRrcPositionReqMsg->enDeleteAssistDataFlag);
    }

    /* �ж��Ƿ������ϱ��������� */
    if (VOS_TRUE == pstMtaRrcPositionReqMsg->bitOpAssistData)
    {
        ulResult = TAF_MTA_ProcAssistData(&pstMtaRrcPositionReqMsg->stAssistData);
        if (VOS_OK != ulResult)
        {
            MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: Report AssistData failed!");
            return;
        }

        /* <assist_data>�е�<GPS_assist>�ڵ��У�<DGPS_corrections>��<GPS_rt_integrity>�ӽڵ���27007 XML DTD�淶��
           ���ǵ����ģ���������ϱ��Ľṹ�������Ƕ���ġ����ڴˣ�MTA��Ҫ�����⴦��: ��<DGPS_corrections>��
           <GPS_rt_integrity>����1�������״��ϱ���<assist_data> XML�У�ֻ�ϱ���һ����ʣ��������ϱ���ÿ��
           <assist_data>�ϱ��д�һ�� */
        ulResult = TAF_MTA_ProcExtraAssistData(&pstMtaRrcPositionReqMsg->stAssistData);
        if (VOS_OK != ulResult)
        {
            MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: Report ExtrAssistData failed!");
            return;
        }
    }

    /* �ж��Ƿ������ϱ�����ָʾ*/
    if (VOS_TRUE == pstMtaRrcPositionReqMsg->bitOpPosMeas)
    {
        ulResult = TAF_MTA_ProcMeasureReq(&pstMtaRrcPositionReqMsg->stPosMeas);
        if (VOS_OK != ulResult)
        {
            MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: Report MeasureReq failed!");
            return;
        }
    }

    return;

#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־�����Ը���Ϣ */
    MTA_WARNING_LOG("TAF_MTA_RcvRrcMsgPositionReq: WARNING: Msg is unexpected!");
    return;

#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtCgpsClockSetReq
 ��������  : ����ATģ�鷢�͵�ID_AT_MTA_CGPSCLOCK_SET_REQ��Ϣ��Ȼ����ݵ�ǰפ��
             ״̬������㷢����Ϣ��GSM��ϢΪID_MTA_GPHY_SET_GPS_RF_CLOCK_REQ��
             UMTS��ϢΪID_MTA_WPHY_SET_GPS_RF_CLOCK_REQ
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtCgpsClockSetReq(VOS_VOID *pMsg)
{

    AT_MTA_MSG_STRU                        *pstAtMtaReqMsg;                     /* �յ�AT��������Ϣָ�� */
#if (FEATURE_ON == FEATURE_AGPS)
#if 0
    AT_MTA_CGPSCLOCK_REQ_STRU              *pstAtMtaCgpsClockReq;               /* ��ͣʱ�� */
    TAF_MMA_RAT_TYPE_ENUM_UINT8             enRatType;                          /* ��ǰפ��ģʽ */
    TAF_MTA_TIMER_ID_ENUM_UINT32            enMtaTimerId;                       /* ��ʱ��ID */
#endif
#endif

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg                          = (AT_MTA_MSG_STRU*)pMsg;

#if (FEATURE_ON == FEATURE_AGPS)

#if 1
    /* Ŀǰ��DSP��ʱ��Ϊ�ϵ缴������Ϊ�˺�AP�Խӣ���ATģ���·�AT^CGPSCLOCK����ʱ��
    ��MTAģ��ֱ�Ӹ�ATģ�鷵��MTA_AT_RESULT_NO_ERROR */
    TAF_MTA_SndAtCgpsClockSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_NO_ERROR);
    return;

#else /* ���������´��뱣�����Ա����AP���GPSʱ�ӷ���ʱ����ֱ������ */
    pstAtMtaCgpsClockReq                    = (AT_MTA_CGPSCLOCK_REQ_STRU *)pstAtMtaReqMsg->aucContent;
    enMtaTimerId                            = TI_TAF_MTA_TIMER_BUTT;

    /* ��ȡ��ǰפ����ģʽ,����ǰģʽ��ΪG��Wģ�����AT���ش���ֵ */
    enRatType = MN_PH_GetCurRat();

    if (TAF_MMA_RAT_GSM == enRatType)
    {
        enMtaTimerId = TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF;
    }
    else if (TAF_MMA_RAT_WCDMA == enRatType)
    {
        enMtaTimerId = TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF;
    }
    else
    {
        TAF_MTA_SndAtCgpsClockSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_ERROR);
        return;
    }

    /* �����ǰ��ʱ�����������򷵻�VOS_ERR */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(enMtaTimerId))
    {
        TAF_MTA_SndAtCgpsClockSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_ERROR);
        return;
    }

    /* ������Ϣ��DSPģ�� */
    if (VOS_OK != TAF_MTA_SndPhySetGpsRfClockReq(enRatType, pstAtMtaCgpsClockReq->enGpsClockState))
    {
        return;
    }
    /* ����1s������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(enMtaTimerId, TI_TAF_MTA_GPS_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(enMtaTimerId,
                                     (VOS_UINT8*)&pstAtMtaReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
#endif

#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־����ATģ��ظ�������Ϣ */
    TAF_MTA_SndAtCgpsClockSetCnf(pstAtMtaReqMsg, MTA_AT_RESULT_ERROR);

    MTA_WARNING_LOG("TAF_MTA_RcvAtCgpsClockSetReq: WARNING: Msg is unexpected!");
    return;

#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvPhyCgpsClockSetCnf
 ��������  : ��������㷢�͵���Ϣ��ΪID_GPHY_MTA_SET_GPS_RF_CLOCK_CNF��
             ID_WPHY_MTA_SET_GPS_RF_CLOCK_CNF��Ȼ���ATģ�鷢����Ϣ
             ID_MTA_AT_CGPSCLOCK_SET_CNF
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��03��11��
    ��    ��   : l00198894
    �޸�����   : Body SAR��Ŀ��������
  3.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyCgpsClockSetCnf(VOS_VOID *pMsg)
{
#if (FEATURE_ON == FEATURE_AGPS)
    TAF_MTA_CMD_BUFFER_STRU                 *pstCmdBuf;
    MTA_AT_CGPSCLOCK_CNF_STRU                stAtMtaCgpsClockCnf;               /* ��ͣʱ������ִ�н�� */
    MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU       *pstMtaPhyCgpsClockCnf;             /* ���յ�DSP���ص���Ϣ�ṹ */
    TAF_MTA_TIMER_ID_ENUM_UINT32             enTimerId;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8               enRatType;                         /* ��ǰפ��ģʽ */

    enRatType = TAF_SDC_GetSysMode();

    /* �ֲ�������ʼ�� */
    pstMtaPhyCgpsClockCnf        = (MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU*)pMsg;

    /* ��ȡ��ǰפ����ģʽ,����ǰģʽΪLTE */
    if (TAF_SDC_SYS_MODE_GSM == enRatType)
    {
        enTimerId = TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF;
    }
    else if (TAF_SDC_SYS_MODE_WCDMA == enRatType)
    {
        enTimerId = TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF;
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyCgpsClockSetCnf: WARNING: RatType is unexpected!");
        return;
    }

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyCgpsClockSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ������Ϣ�ṹ�� */
    if (MTA_PHY_RESULT_NO_ERROR == pstMtaPhyCgpsClockCnf->enResultType)
    {
        stAtMtaCgpsClockCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stAtMtaCgpsClockCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_CGPSCLOCK_SET_CNF,
                      sizeof(MTA_AT_CGPSCLOCK_CNF_STRU),
                      (VOS_UINT8*)&stAtMtaCgpsClockCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־�����Ը���Ϣ */
    MTA_WARNING_LOG("TAF_MTA_RcvPhyCgpsClockSetCnf: WARNING: Msg is unexpected!");
    return;
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiCgpsClockSetReqExpired
 ��������  : ����ʱ����ʱ���͵���Ϣ
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiCgpsClockSetReqExpired(VOS_VOID *pMsg)
{
#if (FEATURE_ON == FEATURE_AGPS)
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf;
    MTA_AT_CGPSCLOCK_CNF_STRU               stAtMtaCgpsClockCnf;               /* ��ͣʱ������ִ�н�� */
    TAF_MTA_TIMER_ID_ENUM_UINT32            enTimerId;

    /* ��ȡ��ǰפ����ģʽ,����ǰģʽ��ΪG/W,����ERROR */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8              enRatType;                        /* ��ǰפ��ģʽ */
    enRatType = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_GSM == enRatType)
    {
        enTimerId = TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF;
    }
    else if (TAF_SDC_SYS_MODE_WCDMA == enRatType)
    {
        enTimerId = TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF;
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiCgpsClockSetReqExpired: WARNING: RatType is not G or W!");
        return;
    }

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiCgpsClockSetReqExpired: WARNING: buffer is null!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    stAtMtaCgpsClockCnf.enResult = MTA_AT_RESULT_ERROR;

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_CGPSCLOCK_SET_CNF,
                      sizeof(MTA_AT_CGPSCLOCK_CNF_STRU),
                      (VOS_UINT8*)&stAtMtaCgpsClockCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־�����Ը���Ϣ */
    MTA_WARNING_LOG("TAF_MTA_RcvTiCgpsClockSetReqExpired: WARNING: Msg is unexpected!");
    return;
#endif
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTcResetUePosStoredInfoInd
 ��������  : ����TC���͵�TCMTA_RESET_UE_POS_STORED_INFO_IND��Ϣ
 �������  : VOS_VOID *pMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTcResetUePosStoredInfoInd(VOS_VOID *pMsg)
{
#if (FEATURE_ON == FEATURE_AGPS)
    /* ��AT���͸����������ָʾ */
    TAF_MTA_SndAtXcposrRptInd(VOS_TRUE);

    return;
#else
    /* FEATURE_AGPS����δ�򿪣���ӡ�澯��־�����Ը���Ϣ */
    MTA_WARNING_LOG("TAF_MTA_RcvTcResetUePosStoredInfoInd: WARNING: Msg is unexpected!");
    return;
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitAsQryNmrCnfExpired
 ��������  : �ȴ�as�ظ�nmr�ظ�������ʱ����ʱ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitAsQryNmrCnfExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU             stQryNmrCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryNmrCnf, 0x0, sizeof(stQryNmrCnf));

    stQryNmrCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ѽ�����ϱ���nmr�����ϱ���ATģ�� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_QRY_NMR_CNF,
                     sizeof(stQryNmrCnf),
                     (VOS_UINT8*)&stQryNmrCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAsQryNmrReqMsg
 ��������  : MTA�����㷢��ID_TAF_AGENT_RRC_QRY_NMR_REQ��Ϣ
 �������  : ulReceiverPid - ���շ�pid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndAsQryNmrReqMsg(
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulLength;
    MTA_RRC_QRY_NMR_REQ_STRU           *pstMtaAsQryNmrReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_RRC_QRY_NMR_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaAsQryNmrReq     = (MTA_RRC_QRY_NMR_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaAsQryNmrReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAsQryNmrReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaAsQryNmrReq->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaAsQryNmrReq->MsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstMtaAsQryNmrReq->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaAsQryNmrReq->MsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMtaAsQryNmrReq->MsgHeader.ulMsgName         = ID_MTA_RRC_QRY_NMR_REQ;

    PS_MEM_SET(pstMtaAsQryNmrReq->aucReserve, 0x0, sizeof(pstMtaAsQryNmrReq->aucReserve));

    /* ������Ϣ��AS */
    PS_SEND_MSG(UEPS_PID_MTA, pstMtaAsQryNmrReq);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvQryNmrReq
 ��������  : mta�յ�ID_AT_MTA_QRY_NMR_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��^CNMR��������

  2.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryNmrReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstQryNmrReq      = VOS_NULL_PTR;
    AT_MTA_QRY_NMR_REQ_STRU            *pstRrcAtQryNmrReq = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU             stQryNmrCnf;
    /* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enQryNmrTiStatus;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enEcidSetTiStatus;
    /* Added by l00198894 for ����+ECID����, 2013-12-10, end */
    VOS_UINT32                          ulResult;

    pstQryNmrReq      = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtQryNmrReq = (AT_MTA_QRY_NMR_REQ_STRU *)pstQryNmrReq->aucContent;

    /* ��ѯ�Ĳ���2g��3g��nmr���ݣ����ߵ�ǰ����ģʽ���ѯģʽ��ƥ�䣬ֱ�ӷ���ʧ��*/
    if ((RRC_MTA_UTRAN_NMR != pstRrcAtQryNmrReq->ucRatType)
     && (RRC_MTA_GSM_NMR != pstRrcAtQryNmrReq->ucRatType))
    {
        PS_MEM_SET(&stQryNmrCnf, 0x0, sizeof(stQryNmrCnf));
        stQryNmrCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryNmrReq->stAppCtrl,
                      ID_MTA_AT_QRY_NMR_CNF,
                      sizeof(stQryNmrCnf),
                      (VOS_UINT8*)&stQryNmrCnf );

        return;
    }

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    /* Modified by l00198894 for ����+ECID����, 2013-12-10, begin */
    enQryNmrTiStatus  = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);
    enEcidSetTiStatus = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);
    if ( (TAF_MTA_TIMER_STATUS_RUNING == enQryNmrTiStatus)
      || (TAF_MTA_TIMER_STATUS_RUNING == enEcidSetTiStatus) )
    /* Modified by l00198894 for ����+ECID����, 2013-12-10, end */
    {
        PS_MEM_SET(&stQryNmrCnf, 0x0, sizeof(stQryNmrCnf));
        stQryNmrCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryNmrReq->stAppCtrl,
                      ID_MTA_AT_QRY_NMR_CNF,
                      sizeof(stQryNmrCnf),
                      (VOS_UINT8*)&stQryNmrCnf );
        return;
    }

    /* �յ�at��^cnmr���󣬷�ID_AT_MTA_QRY_NMR_REQ��Ϣ֪ͨas */
    if (RRC_MTA_UTRAN_NMR == pstRrcAtQryNmrReq->ucRatType)
    {
        ulResult = TAF_MTA_SndAsQryNmrReqMsg(WUEPS_PID_WRR);
    }
    else
    {
        ulResult = TAF_MTA_SndAsQryNmrReqMsg(UEPS_PID_GAS);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryNmrCnf, 0x0, sizeof(stQryNmrCnf));
        stQryNmrCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryNmrReq->stAppCtrl,
                         ID_MTA_AT_QRY_NMR_CNF,
                         sizeof(stQryNmrCnf),
                         (VOS_UINT8*)&stQryNmrCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF, TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF,
                                     (VOS_UINT8*)&pstQryNmrReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasQryNmrCnf
 ��������  : MTA�յ�ID_RRC_MTA_QRY_NMR_CNF��Ϣ������
 �������  : pstRcvQryAsNmrCnf  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��^CNMR��������
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity

*****************************************************************************/
VOS_VOID NAS_MMC_RcvWasQryNmrCnf(RRC_MTA_QRY_NMR_CNF_STRU *pstRcvQryAsNmrCnf)
{
    MTA_AT_QRY_NMR_CNF_STRU             stSndAtQryNmrCnf;
    MTA_AT_QRY_NMR_CNF_STRU            *pstSndAtQryNmrCnf = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFreqNum;

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }


    if (0 == pstRcvQryAsNmrCnf->u.stUtranNMRData.ulFreqNum)
    {
        stSndAtQryNmrCnf.enResult     = MTA_AT_RESULT_NO_ERROR;
        stSndAtQryNmrCnf.ucTotalIndex = 0;
        stSndAtQryNmrCnf.ucCurrIndex  = 0;
        stSndAtQryNmrCnf.usNMRLen     = 0;
        PS_MEM_SET(stSndAtQryNmrCnf.aucNMRData, 0x0, sizeof(stSndAtQryNmrCnf.aucNMRData));

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         sizeof(stSndAtQryNmrCnf),
                         (VOS_UINT8*)&stSndAtQryNmrCnf);

        /* �ӵȴ�������ɾ����Ϣ */
        TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
        return;
    }

    ucFreqNum = (VOS_UINT8)pstRcvQryAsNmrCnf->u.stUtranNMRData.ulFreqNum;

    usLen             = (sizeof(MTA_AT_QRY_NMR_CNF_STRU) + sizeof(NMR_UTRAN_MEASURED_RESULTS_STRU)) - 4;
    pstSndAtQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, usLen);

    if (VOS_NULL_PTR == pstSndAtQryNmrCnf)
    {
        MTA_ERROR_LOG("NAS_MMC_RcvWasQryNmrCnf: alloc msg fail!");

        stSndAtQryNmrCnf.enResult     = MTA_AT_RESULT_NO_ERROR;
        stSndAtQryNmrCnf.ucTotalIndex = ucFreqNum;
        stSndAtQryNmrCnf.ucCurrIndex  = ucFreqNum;
        stSndAtQryNmrCnf.usNMRLen     = 0;
        PS_MEM_SET(stSndAtQryNmrCnf.aucNMRData, 0x0, sizeof(stSndAtQryNmrCnf.aucNMRData));

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         sizeof(stSndAtQryNmrCnf),
                         (VOS_UINT8*)&stSndAtQryNmrCnf);

        /* �ӵȴ�������ɾ����Ϣ */
        TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
        return;
    }

    for (ucLoop = 0; ucLoop < ucFreqNum; ucLoop++)
    {
        pstSndAtQryNmrCnf->enResult     = MTA_AT_RESULT_NO_ERROR;
        pstSndAtQryNmrCnf->ucTotalIndex = ucFreqNum;
        pstSndAtQryNmrCnf->ucCurrIndex  = ucLoop + 1;
        pstSndAtQryNmrCnf->usNMRLen     = sizeof(NMR_UTRAN_MEASURED_RESULTS_STRU);

        PS_MEM_CPY(pstSndAtQryNmrCnf->aucNMRData, &pstRcvQryAsNmrCnf->u.stUtranNMRData.astMeasResults[ucLoop], pstSndAtQryNmrCnf->usNMRLen);

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         usLen,
                         (VOS_UINT8*)pstSndAtQryNmrCnf);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pstSndAtQryNmrCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasQryNmrCnf
 ��������  : MTA�յ�ID_RRC_MTA_QRY_NMR_CNF��Ϣ������
 �������  : pstRcvQryAsNmrCnf  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��^CNMR��������
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity

*****************************************************************************/
VOS_VOID NAS_MMC_RcvGasQryNmrCnf(RRC_MTA_QRY_NMR_CNF_STRU *pstRcvQryAsNmrCnf)
{
    MTA_AT_QRY_NMR_CNF_STRU             stSndAtQryNmrCnf;
    MTA_AT_QRY_NMR_CNF_STRU            *pstSndAtQryNmrCnf = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucFreqNum;

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }
    if (0 == pstRcvQryAsNmrCnf->u.stGsmNMRData.ulElemNum)
    {
        stSndAtQryNmrCnf.enResult     = MTA_AT_RESULT_NO_ERROR;
        stSndAtQryNmrCnf.ucTotalIndex = 0;
        stSndAtQryNmrCnf.ucCurrIndex  = 0;
        stSndAtQryNmrCnf.usNMRLen     = 0;
        PS_MEM_SET(stSndAtQryNmrCnf.aucNMRData, 0x0, sizeof(stSndAtQryNmrCnf.aucNMRData));

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         sizeof(stSndAtQryNmrCnf),
                         (VOS_UINT8*)&stSndAtQryNmrCnf);

        /* �ӵȴ�������ɾ����Ϣ */
        TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
        return;
    }

    ucFreqNum = (VOS_UINT8)pstRcvQryAsNmrCnf->u.stGsmNMRData.ulElemNum;


    usLen             = (sizeof(MTA_AT_QRY_NMR_CNF_STRU) + sizeof(RRC_MTA_GSM_NMR_ELEMENT_STRU)) - 4;
    pstSndAtQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, usLen);

    if (VOS_NULL_PTR == pstSndAtQryNmrCnf)
    {
        MTA_ERROR_LOG("NAS_MMC_RcvGasQryNmrCnf: alloc msg fail!");

        stSndAtQryNmrCnf.enResult     = MTA_AT_RESULT_NO_ERROR;
        stSndAtQryNmrCnf.ucTotalIndex = ucFreqNum;
        stSndAtQryNmrCnf.ucCurrIndex  = 0;
        stSndAtQryNmrCnf.usNMRLen     = 0;
        PS_MEM_SET(stSndAtQryNmrCnf.aucNMRData, 0x0, sizeof(stSndAtQryNmrCnf.aucNMRData));

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         sizeof(stSndAtQryNmrCnf),
                         (VOS_UINT8*)&stSndAtQryNmrCnf);

        /* �ӵȴ�������ɾ����Ϣ */
        TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
        return;
    }

    for (ucLoop = 0; ucLoop < ucFreqNum; ucLoop++)
    {
        pstSndAtQryNmrCnf->enResult     = MTA_AT_RESULT_NO_ERROR;
        pstSndAtQryNmrCnf->ucTotalIndex = ucFreqNum;
        pstSndAtQryNmrCnf->ucCurrIndex  = ucLoop + 1;
        pstSndAtQryNmrCnf->usNMRLen     = sizeof(RRC_MTA_GSM_NMR_ELEMENT_STRU);

        PS_MEM_CPY(pstSndAtQryNmrCnf->aucNMRData, &pstRcvQryAsNmrCnf->u.stGsmNMRData.astNmrElem[ucLoop], pstSndAtQryNmrCnf->usNMRLen);

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_QRY_NMR_CNF,
                         usLen,
                         (VOS_UINT8*)pstSndAtQryNmrCnf);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pstSndAtQryNmrCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);
    return;

}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRrcQryNmrCnf
 ��������  : MTA�յ�ID_RRC_MTA_QRY_NMR_CNF��Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��^CNMR��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRrcQryNmrCnf(VOS_VOID *pMsg)
{
    RRC_MTA_QRY_NMR_CNF_STRU           *pstRcvQryAsNmrCnf = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;


    pstRcvQryAsNmrCnf = (RRC_MTA_QRY_NMR_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcQryNmrCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* was nmr���ݲ�ѯ��� */
    if (RRC_MTA_UTRAN_NMR == pstRcvQryAsNmrCnf->ulChoice)
    {
        NAS_MMC_RcvWasQryNmrCnf(pstRcvQryAsNmrCnf);
        return;
    }


    /* gas nmr���ݲ�ѯ��� */
    if (RRC_MTA_GSM_NMR == pstRcvQryAsNmrCnf->ulChoice)
    {
        NAS_MMC_RcvGasQryNmrCnf(pstRcvQryAsNmrCnf);

    }

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvReselOffsetCfgSetReq
 ��������  : mta�յ�ID_AT_MTA_RESEL_OFFSET_CFG_SET_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��10��
    ��    ��   : t00212959
    �޸�����   : ֧��^WLTHRESHOLDCFG��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvReselOffsetCfgSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU       *pstAtMtaReselOffsetSet  = VOS_NULL_PTR;
    MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU          *pstMtaRrcReselOffsetCfg = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    pstAtMtaMsg            = (AT_MTA_MSG_STRU *)pMsg;

    pstAtMtaReselOffsetSet = (AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU *)pstAtMtaMsg->aucContent;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                = sizeof(MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaRrcReselOffsetCfg = (MTA_RRC_RESEL_OFFSET_CFG_NTF_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaRrcReselOffsetCfg)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvReselOffsetCfgSetReq: Alloc msg fail!");
        return ;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaRrcReselOffsetCfg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMtaRrcReselOffsetCfg->stMsgHeader.ulSenderPid     = UEPS_PID_MTA;
    pstMtaRrcReselOffsetCfg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMtaRrcReselOffsetCfg->stMsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstMtaRrcReselOffsetCfg->stMsgHeader.ulMsgName       = ID_MTA_RRC_RESEL_OFFSET_CFG_NTF;

    pstMtaRrcReselOffsetCfg->enOffsetEnable = pstAtMtaReselOffsetSet->ucOffsetFlg;

    /* ������Ϣ��AS */
    PS_SEND_MSG(UEPS_PID_MTA, pstMtaRrcReselOffsetCfg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtRefclkfreqSetReq
 ��������  : MTAģ���յ�AT������REFCLKFREQ_SET_REQ������Ϣ�Ĵ�����
 �������  : pMsg   -- AT���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
  2.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtRefclkfreqSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg      = VOS_NULL_PTR;     /* �յ�AT��������Ϣָ�� */
    AT_MTA_REFCLKFREQ_SET_REQ_STRU     *pstRefClkFreqReq    = VOS_NULL_PTR;
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo     = VOS_NULL_PTR;
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    pstAtMtaReqMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstRefClkFreqReq    = (AT_MTA_REFCLKFREQ_SET_REQ_STRU *)pstAtMtaReqMsg->aucContent;
    pstRefClockInfo     = TAF_MTA_GetRefClockInfo();
    enResult            = MTA_AT_RESULT_NO_ERROR;

    /* ��ǰ���������ϱ�״̬��֮ǰһ�£�ֱ�ӻؽ�� */
    if (pstRefClockInfo->enRptFlg == pstRefClkFreqReq->enRptFlg)
    {
        TAF_MTA_SndAtRefclkfreqSetCnf(pstAtMtaReqMsg, enResult);
        return;
    }

    if (pstRefClkFreqReq->enRptFlg >= AT_MTA_CMD_RPT_FLG_BUTT)
    {
        enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;
    }
    else if (AT_MTA_CMD_RPT_FLG_ON == pstRefClkFreqReq->enRptFlg)
    {
        pstRefClockInfo->enRptFlg   = pstRefClkFreqReq->enRptFlg;

        if (VOS_TRUE == TAF_MTA_CheckTLMode())
        {
            TAF_MTA_SndTlphyAfclockStatusNtf(AT_MTA_CMD_RPT_FLG_ON, 1);
        }

        /* ��ǰδ�������ڲ�ѯ��ʱ����������ʱ�� */
        if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND))
        {
            /* �ٴ��������ڲ�ѯ��ʱ�� */
            (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,
                                         TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND_TIMER_LEN);
        }
    }
    else
    {
        pstRefClockInfo->enRptFlg   = pstRefClkFreqReq->enRptFlg;

        if (VOS_TRUE == TAF_MTA_CheckTLMode())
        {
            TAF_MTA_SndTlphyAfclockStatusNtf(AT_MTA_CMD_RPT_FLG_OFF, 0);
        }

        TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND);
    }

    TAF_MTA_SndAtRefclkfreqSetCnf(pstAtMtaReqMsg, enResult);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtRefclkfreqSetCnf
 ��������  : MTAģ���AT����REFCLKFREQ_SET_CNF��Ϣ����
 �������  : pstAtMtaReqMsg     -- AT���͵�������Ϣ
             enResult           -- ��AT�ظ��Ľ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_VOID TAF_MTA_SndAtRefclkfreqSetCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    MTA_AT_RESULT_ENUM_UINT32           enResult
)
{
    MTA_AT_RESULT_CNF_STRU              stMtaAtCnf;

    /* ������Ϣ��ATģ�� */
    stMtaAtCnf.enResult = enResult;

    TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                     ID_MTA_AT_REFCLKFREQ_SET_CNF,
                     sizeof(MTA_AT_RESULT_CNF_STRU),
                     (VOS_UINT8*)&stMtaAtCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtRefclkfreqQryReq
 ��������  : MTAģ���յ�AT������REFCLKFREQ_QRY_REQ������Ϣ�Ĵ�����
 �������  : pMsg   -- AT���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
  2.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ: ���TLģʽ�µ�AGPS����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtRefclkfreqQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg      = VOS_NULL_PTR;     /* �յ�AT��������Ϣָ�� */
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo     = VOS_NULL_PTR;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU      stRefClkFreqCnf;

    PS_MEM_SET(&stRefClkFreqCnf, 0, sizeof(stRefClkFreqCnf));

    pstAtMtaReqMsg              = (AT_MTA_MSG_STRU *)pMsg;
    pstRefClockInfo             = TAF_MTA_GetRefClockInfo();
    stRefClkFreqCnf.enResult    = MTA_AT_RESULT_NO_ERROR;
    stRefClkFreqCnf.ulFreq      = pstRefClockInfo->ulFreq;
    stRefClkFreqCnf.ulPrecision = pstRefClockInfo->ulPrecision;

    if (VOS_TRUE == TAF_MTA_CheckTLMode())
    {
        /* �����ǰ��ʱ���Ѿ����������at�ظ�ʧ�� */
        if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF))
        {
            stRefClkFreqCnf.enResult    = MTA_AT_RESULT_ERROR;

            TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                             ID_MTA_AT_REFCLKFREQ_QRY_CNF,
                             sizeof(MTA_AT_REFCLKFREQ_QRY_CNF_STRU),
                             (VOS_UINT8*)&stRefClkFreqCnf);
            return;
        }

        /* ��ǰ�Ѿ����ϱ�����ֱ���ϱ���ǰ�����״̬�������ѯһ�� */
        if (AT_MTA_CMD_RPT_FLG_ON == pstRefClockInfo->enRptFlg)
        {
            stRefClkFreqCnf.enStatus    = pstRefClockInfo->enStatus;

            TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                             ID_MTA_AT_REFCLKFREQ_QRY_CNF,
                             sizeof(MTA_AT_REFCLKFREQ_QRY_CNF_STRU),
                             (VOS_UINT8*)&stRefClkFreqCnf);
        }
        else
        {
            TAF_MTA_SndTlphyAfclockStatusNtf(AT_MTA_CMD_RPT_FLG_ON, 1);

            /* ��������ʱ�� */
            (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF,
                                         TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF_TIMER_LEN);

            /* �����Ϣ���ȴ����� */
            TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF,
                                             (VOS_UINT8*)&pstAtMtaReqMsg->stAppCtrl,
                                             sizeof(AT_APPCTRL_STRU));
        }

        return;
    }
    else
    {
        stRefClkFreqCnf.enStatus    = pstRefClockInfo->enStatus;

        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                         ID_MTA_AT_REFCLKFREQ_QRY_CNF,
                         sizeof(MTA_AT_REFCLKFREQ_QRY_CNF_STRU),
                         (VOS_UINT8*)&stRefClkFreqCnf);

        return;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtRefclkfreqInd
 ��������  : ��ATģ���ϱ�GPS�ο�ʱ����Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_VOID TAF_MTA_SndAtRefclkfreqInd(VOS_VOID)
{
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo     = VOS_NULL_PTR;
    MTA_AT_REFCLKFREQ_IND_STRU          stRefClkFreqInd;
    AT_APPCTRL_STRU                     stAppCtrl;

    pstRefClockInfo             = TAF_MTA_GetRefClockInfo();

    if (AT_MTA_CMD_RPT_FLG_OFF == pstRefClockInfo->enRptFlg)
    {
        /* �����������ϱ�ʱ�����ϱ�GPS�ο�ʱ����Ϣ */
        return;
    }

    PS_MEM_SET(&stRefClkFreqInd, 0, sizeof(stRefClkFreqInd));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stRefClkFreqInd.ulFreq      = pstRefClockInfo->ulFreq;
    stRefClkFreqInd.ulPrecision = pstRefClockInfo->ulPrecision;
    stRefClkFreqInd.enStatus    = pstRefClockInfo->enStatus;
    stAppCtrl.usClientId        = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId            = MTA_INVALID_TAB_INDEX;

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_REFCLKFREQ_IND,
                     sizeof(stRefClkFreqInd),
                     (VOS_UINT8*)&stRefClkFreqInd);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvPhyRefClockStatusInd
 ��������  : MTAģ���յ�������ϱ���GPS�ο�ʱ������״̬�Ĵ���
 �������  : pMsg   -- �յ�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
  2.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ: �޸ĺ����жϣ����͸��Ӷ�
  3.��    ��   : 2015��09��28��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ: Gģ��ֻ�ϱ�������״̬
*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyRefClockStatusInd(VOS_VOID *pMsg)
{
    APM_MTA_REFCLOCK_STATUS_IND_STRU   *pstRefClockStatusInd    = VOS_NULL_PTR;
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo         = VOS_NULL_PTR;
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enTempStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysmode;

    pstRefClockStatusInd = (APM_MTA_REFCLOCK_STATUS_IND_STRU *)pMsg;
    pstRefClockInfo      = TAF_MTA_GetRefClockInfo();
    enSysmode            = TAF_SDC_GetSysMode();

    enTempStatus = pstRefClockStatusInd->enStatus;
    if (TAF_SDC_SYS_MODE_GSM == enSysmode)
    {
        enTempStatus = PHY_MTA_REFCLOCK_UNLOCKED;
    }

    if (pstRefClockInfo->enStatus != enTempStatus)
    {
        pstRefClockInfo->enStatus = enTempStatus;
        TAF_MTA_SndAtRefclkfreqInd();
    }
    else
    {
        /* ����״̬û�б仯�������� */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndTlphyAfclockStatusInd
 ��������  : ��Tlphy����AFC����״̬��Ϣ
 �������  : usReportCount
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_SndTlphyAfclockStatusNtf(
    VOS_UINT16                          enRptFlg,
    VOS_UINT16                          usReportCount
)
{
    VOS_UINT32                             ulLength;
    MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU  *pstMtaTlphySetReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaTlphySetReq     = (MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaTlphySetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTlphyAfclockStatusNtf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaTlphySetReq + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ������Ϣ�ṹ�� */
    pstMtaTlphySetReq->ulReceiverPid     = TLPHY_PID_RTTAGENT;
    pstMtaTlphySetReq->usMsgID           = ID_MTA_AGENT_AFCLOCK_STATUS_RPT_NTF;
    pstMtaTlphySetReq->usReportCtrolflag = enRptFlg;
    if (AT_MTA_CMD_RPT_FLG_ON == enRptFlg)
    {
        pstMtaTlphySetReq->usReportCount     = usReportCount;
    }
    else
    {
        pstMtaTlphySetReq->usReportCount     = 0;
    }
    pstMtaTlphySetReq->usReportDuration  = MTA_PHY_AFCLOCK_REPORT_DURATION;

    /* ������Ϣ��TLPHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaTlphySetReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTlphyAfclockStatusNtf: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTlPhyAfclockStatusInd
 ��������  : MTAģ���յ�������ϱ���AFC����״̬�Ĵ���
 �������  : pMsg   -- �յ�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTlPhyAfclockStatusInd(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU               *pstCmdBuf            = VOS_NULL_PTR;
    TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU  *pstRefClockStatusInd = VOS_NULL_PTR;
    TAF_MTA_REFCLOCK_INFO_STRU            *pstRefClockInfo      = VOS_NULL_PTR;
    AT_APPCTRL_STRU                       *pstAppCtrl           = VOS_NULL_PTR;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU         stRefClkFreqCnf;
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16    enOldAfcStatus;

    pstRefClockStatusInd = (TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU *)pMsg;
    pstRefClockInfo      = TAF_MTA_GetRefClockInfo();

    /* ��ȡ�ϵ�����״̬ */
    enOldAfcStatus              = pstRefClockInfo->enStatus;

    /* ����TL����״̬ */
    pstRefClockInfo->enStatus   = pstRefClockStatusInd->usStatus;

    /* �����ǰ���ڲ�ѯ����ִ�й����У���Ҫ�ظ���ѯ�����AT */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF))
    {
        pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF);

        if (VOS_NULL_PTR != pstCmdBuf)
        {
            pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

            PS_MEM_SET(&stRefClkFreqCnf, 0x00, sizeof(stRefClkFreqCnf));
            stRefClkFreqCnf.enResult    = MTA_AT_RESULT_NO_ERROR;
            stRefClkFreqCnf.ulFreq      = pstRefClockInfo->ulFreq;
            stRefClkFreqCnf.ulPrecision = pstRefClockInfo->ulPrecision;
            stRefClkFreqCnf.enStatus    = pstRefClockInfo->enStatus;

            /* �ϱ���ATģ���ѯ���� */
            TAF_MTA_SndAtMsg(pstAppCtrl,
                             ID_MTA_AT_REFCLKFREQ_QRY_CNF,
                             sizeof(MTA_AT_REFCLKFREQ_QRY_CNF_STRU),
                             (VOS_UINT8*)&stRefClkFreqCnf);

            TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF);
            TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF);
        }

    }

    /* ������ش򿪣�����Ҫ���ݱ仯״̬�����ϱ� */
    if (AT_MTA_CMD_RPT_FLG_ON == pstRefClockInfo->enRptFlg)
    {
        /* ֮ǰ��״̬�͵�ǰ�Ĳ�һ�£��������ϱ�һ�� */
        if (enOldAfcStatus != pstRefClockStatusInd->usStatus)
        {
            TAF_MTA_SndAtRefclkfreqInd();
        }

        if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND))
        {
            /* �ٴ��������ڲ�ѯ��ʱ�� */
            (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,
                                         TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND_TIMER_LEN);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitAgentQryAfclockExpired
 ��������  : MTAģ���ѯ�����AFC����״̬��ʱ�Ĵ���
 �������  : pMsg   -- �յ�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitAgentQryAfclockExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU      stRefclkfreqQry;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    PS_MEM_SET(&stRefclkfreqQry, 0x00, sizeof(stRefclkfreqQry));
    stRefclkfreqQry.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_REFCLKFREQ_QRY_CNF,
                     sizeof(MTA_AT_REFCLKFREQ_QRY_CNF_STRU),
                     (VOS_UINT8*)&stRefclkfreqQry);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitAgentRefclockIndExpired
 ��������  : MTAģ����������·�AFC������ʱ�Ĵ���
 �������  : pMsg   -- �յ�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitAgentRefclockIndExpired(VOS_VOID *pMsg)
{
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo = VOS_NULL_PTR;

    /* �·��������أ�����������ϱ���ʱ�������·� */
    pstRefClockInfo      = TAF_MTA_GetRefClockInfo();

    if (AT_MTA_CMD_RPT_FLG_ON == pstRefClockInfo->enRptFlg)
    {
        if (VOS_TRUE == TAF_MTA_CheckTLMode())
        {
            TAF_MTA_SndTlphyAfclockStatusNtf(AT_MTA_CMD_RPT_FLG_ON,1);
        }

        /* ���������ڲ�ѯ��ʱ�� */
        (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,
                                     TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND_TIMER_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_CheckTLMode
 ��������  : ����Ƿ���LTE����TD������ģʽ
 �������  : ϵͳģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ---- �ɹ�
             VOS_FALSE --- ʧ��
 ���ú���  :
 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MTA_CheckTLMode(VOS_VOID)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysmode;

    enSysmode   = TAF_SDC_GetSysMode();

    switch (enSysmode)
    {
        case TAF_SDC_SYS_MODE_LTE:
            return VOS_TRUE;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return VOS_TRUE;
            }

            return VOS_FALSE;

        default:
            return VOS_FALSE;
    }
}

/* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtEcidSetReq
 ��������  : MTAģ���յ�AT������ECID_SET_REQ������Ϣ�Ĵ�����
 �������  : pMsg   -- AT���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����

  2.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ECID�����Ʒ�߶�������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtEcidSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg      = VOS_NULL_PTR;     /* �յ�AT��������Ϣָ�� */
    AT_MTA_ECID_SET_REQ_STRU           *pstEcidSetReq       = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysmode;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enQryNmrTiStatus;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enEcidSetTiStatus;
    VOS_UINT32                          ulResult;

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg  = (AT_MTA_MSG_STRU *)pMsg;
    pstEcidSetReq   = (AT_MTA_ECID_SET_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* �ж�����汾�ţ���ǰ��֧��0 */
    if (pstEcidSetReq->ulVersion != 0)
    {
        TAF_MTA_SndAtEcidSetCnf(&pstAtMtaReqMsg->stAppCtrl,
                                MTA_AT_RESULT_INCORRECT_PARAMETERS,
                                VOS_NULL_PTR);
        return;
    }

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    enQryNmrTiStatus  = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF);
    enEcidSetTiStatus = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);
    if ( (TAF_MTA_TIMER_STATUS_RUNING == enQryNmrTiStatus)
      || (TAF_MTA_TIMER_STATUS_RUNING == enEcidSetTiStatus) )
    {
        TAF_MTA_SndAtEcidSetCnf(&pstAtMtaReqMsg->stAppCtrl,
                                MTA_AT_RESULT_ERROR,
                                VOS_NULL_PTR);
        return;
    }

    /* ���ݵ�ǰ���뼼�����͵���Ӧ�Ľ�����ѯС����Ϣ */
    enSysmode   = TAF_SDC_GetSysMode();
    ulResult    = VOS_ERR;
    switch (enSysmode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            ulResult = TAF_MTA_SndAsQryNmrReqMsg(UEPS_PID_GAS);
            break;
        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                ulResult = TAF_MTA_SndAsQryNmrReqMsg(WUEPS_PID_WRR);
            }
            /* Added by l00198894 for DTS2014012100639 ��������, 2014/1/21, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
            else
            {
                if (VOS_TRUE == TAF_MTA_ProcTdsEcidSetReq(&pstAtMtaReqMsg->stAppCtrl, &ulResult))
                {
                    /* ������ɣ������������ֱ�ӷ��� */
                    return;
                }

            }
#endif
            /* Added by l00198894 for DTS2014012100639 ��������, 2014/1/21, end */
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            if (VOS_FALSE == TAF_MTA_ProcEcidCustProgress(&ulResult))
            {
                /* ��������δ�������Ͳ�ѯ�����LRRC */
                ulResult = TAF_MTA_SndLrrcCellinfoQryReq();
            }

            break;
#endif
        default:
            break;
    }

    if (ulResult != VOS_OK)
    {
        /* ��ǰ���뼼����֧��(����ģʽ)�����������󣬷���NONE */
        TAF_MTA_SndAtEcidSetCnf(&pstAtMtaReqMsg->stAppCtrl,
                                MTA_AT_RESULT_NO_ERROR,
                                (VOS_UINT8*)MTA_ECID_NONE_RAT_STR);
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF, TI_TAF_MTA_WAIT_AS_ECID_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF,
                                     (VOS_UINT8*)&pstAtMtaReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtEcidSetCnf
 ��������  : MTA��ATģ�鷢��ECID_SET_REQ��Ϣ�Ĵ�����
 �������  : pAppCtrl       -- AT������Ϣ
             enResult       -- ���������
             pucCellInfoStr -- ת�������ǿ��С����Ϣ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :

  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_SndAtEcidSetCnf (
    AT_APPCTRL_STRU                    *pAppCtrl,
    MTA_AT_RESULT_ENUM_UINT32           enResult,
    VOS_UINT8                          *pucCellInfoStr
)
{
    MTA_AT_ECID_SET_CNF_STRU           *pstMtaAtEcidSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    if (VOS_NULL_PTR == pucCellInfoStr)
    {
        ulLength = sizeof(MTA_AT_ECID_SET_CNF_STRU);
    }
    else
    {
        ulLength = ((sizeof(MTA_AT_ECID_SET_CNF_STRU) - 4) + VOS_StrLen((VOS_CHAR *)pucCellInfoStr)) + 1;
    }

    pstMtaAtEcidSetCnf = (MTA_AT_ECID_SET_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaAtEcidSetCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAtEcidSetCnf: alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstMtaAtEcidSetCnf, 0, ulLength);

    /* ������Ϣ��ATģ�� */
    pstMtaAtEcidSetCnf->enResult = enResult;

    if (VOS_NULL_PTR != pucCellInfoStr)
    {
        PS_MEM_CPY(pstMtaAtEcidSetCnf->aucCellInfoStr,
                   pucCellInfoStr,
                   VOS_StrLen((VOS_CHAR *)pucCellInfoStr));
    }

    TAF_MTA_SndAtMsg( pAppCtrl,
                      ID_MTA_AT_ECID_SET_CNF,
                      ulLength,
                      (VOS_UINT8*)pstMtaAtEcidSetCnf );

    PS_MEM_FREE(UEPS_PID_MTA, pstMtaAtEcidSetCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGUAsEcellInfoQryCnf
 ��������  : MTA�յ�GU�������ǿС����Ϣ��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvGUAsEcellInfoQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    RRC_MTA_QRY_NMR_CNF_STRU           *pstEcellInfoQryCnf = VOS_NULL_PTR;
    VOS_UINT8                          *pucCellInfoStr    = VOS_NULL_PTR;
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    pstEcellInfoQryCnf = (RRC_MTA_QRY_NMR_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF))
    {
        TAF_MTA_RcvRrcQryNmrCnf(pMsg);
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvGUAsEcellInfoQryCnf: No Buffer!");
        return;
    }

    pucCellInfoStr = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, MTA_ECID_CELLINFO_MAX_STRLEN);
    if (VOS_NULL_PTR == pucCellInfoStr)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvGUAsEcellInfoQryCnf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pucCellInfoStr, 0, MTA_ECID_CELLINFO_MAX_STRLEN);

    if (RRC_MTA_GSM_NMR == pstEcellInfoQryCnf->ulChoice)
    {
        enResult = TAF_MTA_CodeGasEcidStr(&(pstEcellInfoQryCnf->u.stGsmNMRData), pucCellInfoStr);
    }
    else if (RRC_MTA_UTRAN_NMR == pstEcellInfoQryCnf->ulChoice)
    {
        enResult = TAF_MTA_CodeWasEcidStr(&(pstEcellInfoQryCnf->u.stUtranNMRData), pucCellInfoStr);
    }
    else
    {
        enResult = MTA_AT_RESULT_ERROR;
    }

    if (MTA_AT_RESULT_NO_ERROR == enResult)
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                pucCellInfoStr);
    }
    else
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                VOS_NULL_PTR);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pucCellInfoStr);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*lint -e438 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MTA_GetPlmnStr
 ��������  : ת��PLMN�ַ���
 �������  : pstPlmnId      -- ��ת����PLMN ID
 �������  : pucPlmnStr     -- ת������ַ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_GetPlmnStr(
    VOS_UINT8                          *pucPlmnStr,
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_INT32                           lMaxLength;
    VOS_INT32                           lLength;
    TAF_SDC_PLMN_ID_STRU                stPlmnIdTmp;

    PS_MEM_SET(&stPlmnIdTmp, 0, sizeof(stPlmnIdTmp));
    lMaxLength  = MTA_ECID_PLMN_MAX_STR_LEN;
    lLength     = 0;

    /* ��PLMN IDת��ΪBCD�� */
    stPlmnIdTmp.ulMcc = pstPlmnId->ulMcc;
    stPlmnIdTmp.ulMnc = pstPlmnId->ulMnc;
    TAF_SDC_PlmnId2Bcd(&stPlmnIdTmp);

    lLength = VOS_nsprintf((VOS_CHAR *)pucPlmnStr,
                            (VOS_UINT32)lMaxLength,
                            "%x%x%x,",
                            (stPlmnIdTmp.ulMcc & 0x0f00) >> 8,
                            (stPlmnIdTmp.ulMcc & 0xf0) >> 4,
                            (stPlmnIdTmp.ulMcc & 0x0f));

    if (lLength <= 0)
    {
        return;
    }

    lMaxLength -= lLength;

    if (0x0f00 == (stPlmnIdTmp.ulMnc & 0x0f00))
    {
        lLength = VOS_nsprintf((VOS_CHAR *)((pucPlmnStr + MTA_ECID_PLMN_MAX_STR_LEN) - lMaxLength),
                                (VOS_UINT32)lMaxLength,
                               "%x%x",
                               (stPlmnIdTmp.ulMnc & 0xf0) >> 4,
                               (stPlmnIdTmp.ulMnc & 0x0f));
    }
    else
    {
        lLength = VOS_nsprintf((VOS_CHAR *)((pucPlmnStr + MTA_ECID_PLMN_MAX_STR_LEN) - lMaxLength),
                                (VOS_UINT32)lMaxLength,
                                "%x%x%x",
                                (stPlmnIdTmp.ulMnc & 0x0f00) >> 8,
                                (stPlmnIdTmp.ulMnc & 0xf0) >> 4,
                                (stPlmnIdTmp.ulMnc & 0x0f));
    }

    return;
}
/*lint +e438 +e830*/

/*lint -e429 -e438 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MTA_CodeGasEcidStr
 ��������  : MTA����GAS��ѯ����ǿС����Ϣ
 �������  : pstGsmNmr      -- GAS��ѯ����ǿС����Ϣ
 �������  : pucCellinfoStr -- ������ַ��������ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeGasEcidStr(
    RRC_MTA_GSM_NMR_STRU               *pstGsmNmr,
    VOS_UINT8                          *pucCellinfoStr
)
{
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppsysInfo     = VOS_NULL_PTR;
    VOS_INT32                           lMaxLength;
    VOS_INT32                           lLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucPlmnStr[MTA_ECID_PLMN_MAX_STR_LEN];

    lMaxLength     = MTA_ECID_CELLINFO_MAX_STRLEN;
    lLength        = 0;

    pst3gppsysInfo = TAF_SDC_Get3gppSysInfo();

    if (0 == pstGsmNmr->ulElemNum)
    {
        lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                                (VOS_UINT32)lMaxLength,
                                "%s",
                                MTA_ECID_NONE_RAT_STR);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        return MTA_AT_RESULT_NO_ERROR;
    }

    /* 0,GSM:,<MCC>,<MNC>,<LAC>,<CID>,<TA>,<NB_CELL> */
    PS_MEM_SET(aucPlmnStr, 0, sizeof(aucPlmnStr));
    TAF_MTA_GetPlmnStr(aucPlmnStr, &pst3gppsysInfo->stPlmnId);
    lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                            (VOS_UINT32)lMaxLength,
                            "0,GSM:,%s,%d,%d,%d,%d",
                            aucPlmnStr,
                            pst3gppsysInfo->usLac,
                            pst3gppsysInfo->ulCellId,
                            MTA_ECID_UNDEFINED_VALUE,
                            pstGsmNmr->ulElemNum);

    if (lLength <= 0)
    {
        return MTA_AT_RESULT_INCORRECT_PARAMETERS;
    }

    lMaxLength -= lLength;

    for (ulLoop = 0; ulLoop < pstGsmNmr->ulElemNum; ulLoop++)
    {
        /* [,<BSIC>,<ARFCN>,<RX_level>]*NB_CELL */
        lLength = VOS_nsprintf((VOS_CHAR *)((pucCellinfoStr + MTA_ECID_CELLINFO_MAX_STRLEN) - lMaxLength),
                                (VOS_UINT32)lMaxLength,
                                ",%d,%d,%d",
                                pstGsmNmr->astNmrElem[ulLoop].ucBsic,
                                pstGsmNmr->astNmrElem[ulLoop].usArfcn,
                                pstGsmNmr->astNmrElem[ulLoop].ucRxlev);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        lMaxLength -= lLength;
    }

    return MTA_AT_RESULT_NO_ERROR;
}
/*lint +e429 +e438 +e830*/

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetUtranMeasInfo
 ��������  : ��WAS��ѯ�Ľṹ��NMR_UTRAN_MEASURED_RESULTS_STRU�л�ȡ������Ϣ
 �������  : pstUtranMeasRslt   -- WAS��ѯ����ǿС����Ϣ�ṹ
 �������  : plUarfcnUL         -- ����Ƶ��
             plUarfcnDL         -- ����Ƶ��
             plUCRssi           -- �����ź�ǿ��
             pulCMRNum          -- ��������������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_GetUtranMeasInfo(
    NMR_UTRAN_MEASURED_RESULTS_STRU    *pstUtranMeasRslt,
    VOS_INT32                          *plUarfcnUL,
    VOS_INT32                          *plUarfcnDL,
    VOS_INT32                          *plUCRssi,
    VOS_UINT32                         *pulCMRNum)
{
    if (VOS_TRUE == pstUtranMeasRslt->bitOpFrequencyInfo)
    {
        if (NMR_UTRAN_MEASURED_TYPE_FDD == pstUtranMeasRslt->stFrequencyInfo.enFreqInfoChoice)
        {
            if (VOS_TRUE == pstUtranMeasRslt->stFrequencyInfo.u.stFreqInfoFDD.bitOpUarfcn_UL)
            {
                *plUarfcnUL = pstUtranMeasRslt->stFrequencyInfo.u.stFreqInfoFDD.usUlUarfcn;
            }
            *plUarfcnDL = pstUtranMeasRslt->stFrequencyInfo.u.stFreqInfoFDD.usDlUarfcn;
        }
    }

    if (VOS_TRUE == pstUtranMeasRslt->bitOpUTRA_CarrierRSSI)
    {
        *plUCRssi = (VOS_INT32)pstUtranMeasRslt->ulUTRA_CarrierRSSI;
    }

    if (VOS_TRUE == pstUtranMeasRslt->bitOpCellMeasResultsList)
    {
        *pulCMRNum = pstUtranMeasRslt->stCellMeasResultsList.ulMeasCellNum;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetUtranCellInfo
 ��������  : ��WAS��ѯ�Ľṹ��NMR_UTRAN_CELL_MEAS_RESULTS_STRU�л�ȡ������Ϣ
 �������  : pstCellMeasRslt    -- WAS��ѯ����ǿС����Ϣ�ṹ
 �������  : plCellId           -- ������С��ID
             plCellPSC          -- ������������
             plEcNO             -- ������EC NO
             plRscp             -- ������RSCP
             plPathloss         -- ������Pathloss
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_GetUtranCellInfo(
    NMR_UTRAN_CELL_MEAS_RESULTS_STRU   *pstCellMeasRslt,
    VOS_INT32                          *plCellId,
    VOS_INT32                          *plCellPSC,
    VOS_INT32                          *plEcNO,
    VOS_INT32                          *plRscp,
    VOS_INT32                          *plPathloss
)
{
    if (VOS_TRUE == pstCellMeasRslt->bitOpCellID)
    {
        *plCellId = (VOS_INT32)pstCellMeasRslt->ulCellID;
    }

    if (NMR_UTRAN_MEASURED_TYPE_FDD == pstCellMeasRslt->enCellMeasTypeChoice)
    {
        *plCellPSC = pstCellMeasRslt->u.stCellMeasResultsFDD.usCellPSC;

        if (VOS_TRUE == pstCellMeasRslt->u.stCellMeasResultsFDD.bitOpEcn0)
        {
            *plEcNO = pstCellMeasRslt->u.stCellMeasResultsFDD.ucEcn0;
        }

        if (VOS_TRUE == pstCellMeasRslt->u.stCellMeasResultsFDD.bitOpRscp)
        {
            *plRscp = pstCellMeasRslt->u.stCellMeasResultsFDD.ucRscp;
        }

        if (VOS_TRUE == pstCellMeasRslt->u.stCellMeasResultsFDD.bitOpPathloss)
        {
            *plPathloss = pstCellMeasRslt->u.stCellMeasResultsFDD.ucPathloss;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetUtranServingCellInfo
 ��������  : ��ȡUTRAN��ǰ����С����Ϣ
 �������  : pstUtranNmr    -- WAS��ѯ����ǿС����Ϣ
 �������  : plCellPSC      -- ������
             plUarfcnUL     -- ����Ƶ��
             plUarfcnDL     -- ����Ƶ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_UINT32 TAF_MTA_GetUtranServingCellInfo(
    RRC_MTA_UTRAN_NMR_STRU             *pstUtranNmr,
    VOS_INT32                          *plCellPSC,
    VOS_INT32                          *plUarfcnUL,
    VOS_INT32                          *plUarfcnDL
)
{
    if ( (0 == pstUtranNmr->ulFreqNum)
      || (VOS_TRUE != pstUtranNmr->astMeasResults[0].bitOpCellMeasResultsList)
      || (0 == pstUtranNmr->astMeasResults[0].stCellMeasResultsList.ulMeasCellNum)
      || (NMR_UTRAN_MEASURED_TYPE_FDD != pstUtranNmr->astMeasResults[0]
                .stCellMeasResultsList.astCellMeasResults[0].enCellMeasTypeChoice) )
    {
        return VOS_ERR;
    }

    *plCellPSC = pstUtranNmr->astMeasResults[0].stCellMeasResultsList.astCellMeasResults[0].u.stCellMeasResultsFDD.usCellPSC;

    if (VOS_TRUE == pstUtranNmr->astMeasResults[0].bitOpFrequencyInfo)
    {
        if (NMR_UTRAN_MEASURED_TYPE_FDD != pstUtranNmr->astMeasResults[0].stFrequencyInfo.enFreqInfoChoice)
        {
            return VOS_ERR;
        }

        if (VOS_TRUE == pstUtranNmr->astMeasResults[0].stFrequencyInfo.u.stFreqInfoFDD.bitOpUarfcn_UL)
        {
            *plUarfcnUL = pstUtranNmr->astMeasResults[0].stFrequencyInfo.u.stFreqInfoFDD.usUlUarfcn;
        }

        *plUarfcnDL = pstUtranNmr->astMeasResults[0].stFrequencyInfo.u.stFreqInfoFDD.usDlUarfcn;
    }

    return VOS_OK;
}

/*lint -e429 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MTA_CodeWasEcidStr
 ��������  : MTA����WAS��ѯ����ǿС����Ϣ
 �������  : pstUtranNmr    -- WAS��ѯ����ǿС����Ϣ
 �������  : pucCellinfoStr -- ������ַ��������ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeWasEcidStr(
    RRC_MTA_UTRAN_NMR_STRU             *pstUtranNmr,
    VOS_UINT8                          *pucCellinfoStr
)
{
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo     = VOS_NULL_PTR;
    VOS_UINT8                           aucPlmnStr[MTA_ECID_PLMN_MAX_STR_LEN];
    VOS_INT32                           lMaxLength;
    VOS_INT32                           lLength;
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;
    VOS_INT32                           lUarfcnUL;
    VOS_INT32                           lUarfcnDL;
    VOS_INT32                           lUCRssi;
    VOS_UINT32                          ulCMRNum;
    VOS_INT32                           lCellId;
    VOS_INT32                           lCellPSC;
    VOS_INT32                           lEcNO;
    VOS_INT32                           lRscp;
    VOS_INT32                           lPathloss;

    lMaxLength      = MTA_ECID_CELLINFO_MAX_STRLEN;
    lLength         = 0;
    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();
    lUarfcnUL       = MTA_ECID_UNDEFINED_VALUE;
    lUarfcnDL       = MTA_ECID_UNDEFINED_VALUE;
    lCellPSC        = MTA_ECID_UNDEFINED_VALUE;

    if (VOS_OK != TAF_MTA_GetUtranServingCellInfo(pstUtranNmr, &lCellPSC, &lUarfcnUL, &lUarfcnDL))
    {
        lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                                (VOS_UINT32)lMaxLength,
                                "%s",
                                MTA_ECID_NONE_RAT_STR);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        return MTA_AT_RESULT_NO_ERROR;
    }

    /* 0,WCDMA:,<MCC>,<MNC>,<UCID>,<Primary_Scrambling>,<UARFCN_UL>,<UARFCN_DL>,<NB_FREQ> */
    PS_MEM_SET(aucPlmnStr, 0, sizeof(aucPlmnStr));
    TAF_MTA_GetPlmnStr(aucPlmnStr, &pst3gppSysInfo->stPlmnId);
    lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                           (VOS_UINT32)lMaxLength,
                            "0,WCDMA:,%s,%d,%d,%d,%d,%d",
                            aucPlmnStr,
                            pst3gppSysInfo->ulCellId,
                            lCellPSC,
                            lUarfcnUL,
                            lUarfcnDL,
                            pstUtranNmr->ulFreqNum);

    if (lLength <= 0)
    {
        return MTA_AT_RESULT_INCORRECT_PARAMETERS;
    }

    lMaxLength -= lLength;

    for (ulLoop1 = 0; ulLoop1 < pstUtranNmr->ulFreqNum; ulLoop1++)
    {
        /* [,<UARFCN_UL>,<UARFCN_DL>,<UC_RSSI>,<CMR_NB>
            [,<Cell_ID>,<Primary_CPICH>,<CPICH_Ec_NO>,<CPICH_RSCP>,<Pathloss>]*CMR_NB]*NB_FREQ */
        lUarfcnUL   = MTA_ECID_UNDEFINED_VALUE;
        lUarfcnDL   = MTA_ECID_UNDEFINED_VALUE;
        lUCRssi     = MTA_ECID_UNDEFINED_VALUE;
        ulCMRNum    = 0;

        TAF_MTA_GetUtranMeasInfo(&pstUtranNmr->astMeasResults[ulLoop1],
                                 &lUarfcnUL, &lUarfcnDL, &lUCRssi, &ulCMRNum);

        lLength = VOS_nsprintf((VOS_CHAR *)((pucCellinfoStr + MTA_ECID_CELLINFO_MAX_STRLEN) - lMaxLength),
                               (VOS_UINT32)lMaxLength,
                                ",%d,%d,%d,%d",
                                lUarfcnUL,
                                lUarfcnDL,
                                lUCRssi,
                                ulCMRNum);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        lMaxLength -= lLength;

        for (ulLoop2 = 0; ulLoop2 < ulCMRNum; ulLoop2++)
        {
            lCellId     = MTA_ECID_UNDEFINED_VALUE;
            lCellPSC    = MTA_ECID_UNDEFINED_VALUE;
            lEcNO       = MTA_ECID_UNDEFINED_VALUE;
            lRscp       = MTA_ECID_RSCP_UNDEFINED_VALUE;
            lPathloss   = MTA_ECID_UNDEFINED_VALUE;

            TAF_MTA_GetUtranCellInfo(&pstUtranNmr->astMeasResults[ulLoop1].stCellMeasResultsList.astCellMeasResults[ulLoop2],
                                     &lCellId, &lCellPSC, &lEcNO, &lRscp, &lPathloss);

            lLength = VOS_nsprintf((VOS_CHAR *)((pucCellinfoStr + MTA_ECID_CELLINFO_MAX_STRLEN) - lMaxLength),
                                   (VOS_UINT32)lMaxLength,
                                    ",%d,%d,%d,%d,%d",
                                    lCellId,
                                    lCellPSC,
                                    lEcNO,
                                    lRscp,
                                    lPathloss);

            if (lLength <= 0)
            {
                return MTA_AT_RESULT_INCORRECT_PARAMETERS;
            }

            lMaxLength -= lLength;

        }
    }

    return MTA_AT_RESULT_NO_ERROR;
}
/*lint +e429 +e830*/

/* Added by l00198894 for DTS2014012100639 ��������, 2014/1/21, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcTdsEcidSetReq
 ��������  : MTAģ��TDS���뼼��ʱ�յ�AT������ECID_SET_REQ������Ϣ�Ĵ�����
 �������  : AT_APPCTRL_STRU* pstAppCtrl
 �������  : ��
 �� �� ֵ  : VOS_TRUE : �������
             VOS_FALSE: δ�����꣬����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : DTS2014012100639: ��������, TD��֧��AGPS��SUPL��λ

  2.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ECID�����Ʒ�߶�������
*****************************************************************************/
VOS_UINT32 TAF_MTA_ProcTdsEcidSetReq(
    AT_APPCTRL_STRU                    *pstAppCtrl,
    VOS_UINT32                         *pulResult
)
{
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo     = VOS_NULL_PTR;
    VOS_UINT8                          *pucCellInfoStr      = VOS_NULL_PTR;
    VOS_INT32                           lLength;
    VOS_UINT8                           aucPlmnStr[MTA_ECID_PLMN_MAX_STR_LEN];

    if (VOS_TRUE == TAF_MTA_ProcEcidCustProgress(pulResult))
    {
        /* �������̴�����ɣ����ɺ������� */
        return VOS_FALSE;
    }

    pucCellInfoStr = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, MTA_ECID_CELLINFO_MAX_STRLEN);
    if (VOS_NULL_PTR == pucCellInfoStr)
    {
        MTA_ERROR_LOG("TAF_MTA_ProcTdsEcidSetReq: Alloc fail!");
        *pulResult = VOS_ERR;
        return VOS_FALSE;
    }

    PS_MEM_SET(pucCellInfoStr, 0, MTA_ECID_CELLINFO_MAX_STRLEN);
    lLength         = 0;

    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();

    /* 0,GSM:,<MCC>,<MNC>,<LAC>,<CID>,-1,0 */
    PS_MEM_SET(aucPlmnStr, 0, sizeof(aucPlmnStr));
    TAF_MTA_GetPlmnStr(aucPlmnStr, &pst3gppSysInfo->stPlmnId);
    lLength = VOS_nsprintf((VOS_CHAR *)pucCellInfoStr,
                            (VOS_UINT32)MTA_ECID_CELLINFO_MAX_STRLEN,
                            "0,GSM:,%s,%d,%d,%d,0",
                            aucPlmnStr,
                            pst3gppSysInfo->usLac,
                            pst3gppSysInfo->ulCellId,
                            MTA_ECID_UNDEFINED_VALUE);

    if (lLength <= 0)
    {
        TAF_MTA_SndAtEcidSetCnf(pstAppCtrl,
                                MTA_AT_RESULT_INCORRECT_PARAMETERS,
                                VOS_NULL_PTR);
    }
    else
    {
        TAF_MTA_SndAtEcidSetCnf(pstAppCtrl,
                                MTA_AT_RESULT_NO_ERROR,
                                pucCellInfoStr);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pucCellInfoStr);

    *pulResult = VOS_OK;
    return VOS_TRUE;
}
#endif
/* Added by l00198894 for DTS2014012100639 ��������, 2014/1/21, end */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcCellinfoQryReq
 ��������  : MTA����ϢID_MTA_LRRC_CELLINFO_QRY_REQ��LRRC��ѯ��ǿС����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_UINT32 TAF_MTA_SndLrrcCellinfoQryReq(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    MTA_LRRC_CELLINFO_QRY_REQ_STRU     *pstCellinfoQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_CELLINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCellinfoQryReq     = (MTA_LRRC_CELLINFO_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstCellinfoQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcCellinfoQryReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstCellinfoQryReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCellinfoQryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstCellinfoQryReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCellinfoQryReq->stMsgHeader.ulReceiverPid     = PS_PID_ERRC;
    pstCellinfoQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_CELLINFO_QRY_REQ;

    PS_MEM_SET(pstCellinfoQryReq->aucReserved, 0, sizeof(pstCellinfoQryReq->aucReserved));

    /* ������Ϣ��LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstCellinfoQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcCellinfoQryReq(): Send MSG Fail!");
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcCellinfoQryCnf
 ��������  : MTA�յ�LTE�������ǿС����Ϣ��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcCellinfoQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    LRRC_MTA_CELLINFO_QRY_CNF_STRU     *pstCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT8                          *pucCellInfoStr    = VOS_NULL_PTR;
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    pstCellinfoQryCnf = (LRRC_MTA_CELLINFO_QRY_CNF_STRU *)pMsg;
    enResult          = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcCellinfoQryCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcCellinfoQryCnf: No Buffer!");
        return;
    }

    pucCellInfoStr = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, MTA_ECID_CELLINFO_MAX_STRLEN);
    if (VOS_NULL_PTR == pucCellInfoStr)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcCellinfoQryCnf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pucCellInfoStr, 0, MTA_ECID_CELLINFO_MAX_STRLEN);

    if (MTA_RRC_RESULT_NO_ERROR == pstCellinfoQryCnf->enResult)
    {
        enResult = TAF_MTA_CodeLteEcidStr(&(pstCellinfoQryCnf->stCellInfoRslt), pucCellInfoStr);
    }

    if (MTA_AT_RESULT_NO_ERROR == enResult)
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                pucCellInfoStr);
    }
    else
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                VOS_NULL_PTR);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pucCellInfoStr);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetLrrcCellInfo
 ��������  : ��LTE��ѯ�Ľṹ��LRRC_CELLINFO_STRU�л�ȡС����Ϣ
 �������  : pstCellInfo        -- LTE��ѯ����ǿС����Ϣ�ṹ
 �������  : plEarfcn           -- С��Ƶ��
             plRsrp             -- �ο��źŽ��չ���
             plRsrq             -- �ο��źŽ�������
             plTa               -- LTE��ʱ����ǰ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����

  2.��    ��   : 2015��12��2��
    ��    ��   : l00198894
    �޸�����   : DTS2015120206389: LRRC�ӿڱ��
*****************************************************************************/
VOS_VOID TAF_MTA_GetLrrcCellInfo(
    LRRC_CELLINFO_STRU                 *pstCellInfo,
    VOS_INT32                          *plEarfcn,
    VOS_INT32                          *plRsrp,
    VOS_INT32                          *plRsrq,
    VOS_INT32                          *plTa
)
{
    if (VOS_TRUE == pstCellInfo->bitOpEarfcn)
    {
        *plEarfcn = (VOS_INT32)pstCellInfo->ulEarfcn;
    }

    if (VOS_TRUE == pstCellInfo->bitOpRsrp)
    {
        *plRsrp = (VOS_INT32)pstCellInfo->ulRsrp;
    }

    if (VOS_TRUE == pstCellInfo->bitOpRsrq)
    {
        *plRsrq = (VOS_INT32)pstCellInfo->ulRsrq;
    }

    if (VOS_TRUE == pstCellInfo->bitOpTa)
    {
        /* Lrrc�޸Ľӿڣ�TA��ֵ����������ƫ�� */
        *plTa= (VOS_INT32)(pstCellInfo->ulTa);
    }

    return;
}

/*lint -e429 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MTA_CodeLteEcidStr
 ��������  : MTA����LTE��ѯ����ǿС����Ϣ
 �������  : pstCellinfoRslt    -- LTE��ѯ����ǿС����Ϣ
 �������  : pucCellinfoStr     -- ������ַ��������ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeLteEcidStr(
    LRRC_CELLINFO_RSLT_STRU            *pstCellinfoRslt,
    VOS_UINT8                          *pucCellinfoStr
)
{
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo     = VOS_NULL_PTR;
    VOS_UINT8                           aucPlmnStr[MTA_ECID_PLMN_MAX_STR_LEN];
    VOS_INT32                           lMaxLength;
    VOS_INT32                           lLength;
    VOS_UINT32                          ulLoop;
    VOS_INT32                           lPhyCellCode;
    VOS_INT32                           lEarfcn;
    VOS_INT32                           lRsrp;
    VOS_INT32                           lRsrq;
    VOS_INT32                           lTa;

    lMaxLength     = MTA_ECID_CELLINFO_MAX_STRLEN;
    lLength        = 0;
    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();

    if (0 == pstCellinfoRslt->ulCellNum)
    {
        lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                               (VOS_UINT32)lMaxLength,
                                "%s",
                                MTA_ECID_NONE_RAT_STR);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        return MTA_AT_RESULT_NO_ERROR;
    }

    /* 0,LTE:,<MCC>,<MNC>,<TAC>,<LCID>,<L_NB_CELL> */
    PS_MEM_SET(aucPlmnStr, 0, sizeof(aucPlmnStr));
    TAF_MTA_GetPlmnStr(aucPlmnStr, &pst3gppSysInfo->stPlmnId);
    lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                           (VOS_UINT32)lMaxLength,
                            "0,LTE:,%s,%d,%d,%d",
                            aucPlmnStr,
                            pstCellinfoRslt->ulTac,
                            pst3gppSysInfo->ulCellId,
                            pstCellinfoRslt->ulCellNum);

    if (lLength <= 0)
    {
        return MTA_AT_RESULT_INCORRECT_PARAMETERS;
    }

    lMaxLength -= lLength;

    for (ulLoop = 0; ulLoop < pstCellinfoRslt->ulCellNum; ulLoop++)
    {
        lPhyCellCode    = (VOS_INT32)pstCellinfoRslt->astCellInfo[ulLoop].ulPhyCellCode;
        lEarfcn         = MTA_ECID_UNDEFINED_VALUE;
        lRsrp           = MTA_ECID_UNDEFINED_VALUE;
        lRsrq           = MTA_ECID_UNDEFINED_VALUE;
        lTa             = MTA_ECID_UNDEFINED_VALUE;

        /* [,<Cell_Code>,<EARFCN>,<RSRP>,<RSRQ>,<L_TA>] *NB_CELL */
        TAF_MTA_GetLrrcCellInfo(&pstCellinfoRslt->astCellInfo[ulLoop],
                                &lEarfcn, &lRsrp, &lRsrq, &lTa);

        lLength = VOS_nsprintf((VOS_CHAR *)((pucCellinfoStr + MTA_ECID_CELLINFO_MAX_STRLEN) - lMaxLength),
                               (VOS_UINT32)lMaxLength,
                                ",%d,%d,%d,%d,%d",
                                lPhyCellCode,
                                lEarfcn,
                                lRsrp,
                                lRsrq,
                                lTa);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        lMaxLength -= lLength;

    }

    return MTA_AT_RESULT_NO_ERROR;
}
/*lint +e429 +e830*/
#endif

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiEcidSetExpired
 ��������  : MTAģ��ECID�������ʱ������
 �������  : pMsg    -- ��ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiEcidSetExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf;

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiEcidSetExpired: WARNING: buffer is null!");
        return;
    }

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                            MTA_AT_RESULT_OPTION_TIMEOUT,
                            VOS_NULL_PTR);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}
/* Added by l00198894 for ����+ECID����, 2013-12-10, end */

/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcEcidCustProgress
 ��������  : MTAģ��TD-SCDMA��LTE���뼼��ʱ�յ�AT������ECID_SET_REQ������Ϣ��
             ��Ӫ�̶��ƴ�����
 �������  : VOS_UINT32 *pulResult -- Ϊ������ʱ�м���̵Ĵ�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : �������
             VOS_FALSE: δ�����꣬����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MTA_ProcEcidCustProgress(
    VOS_UINT32                         *pulResult
)
{
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo     = VOS_NULL_PTR;
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg          = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    MTA_MTC_RESERVE_STRU               *pstReserveMsg       = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                stPlmnId;

    pstEcidCfg      = TAF_MTA_GetEcidCfg();
    pst3gppSysInfo  = TAF_SDC_Get3gppSysInfo();
    stPlmnId        = pst3gppSysInfo->stPlmnId;
    TAF_SDC_PlmnId2Bcd(&stPlmnId);

    if ( (VOS_TRUE == pstEcidCfg->ucEnableFlg)
      && (pstEcidCfg->usMcc == stPlmnId.ulMcc) )
    {
        /* ������Ϣ�ṹ�ڴ� */
        ulLength        = sizeof(MTA_MTC_RESERVE_STRU) - VOS_MSG_HEAD_LENGTH;
        pstReserveMsg   = (MTA_MTC_RESERVE_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
        if (VOS_NULL_PTR == pstReserveMsg)
        {
            MTA_ERROR_LOG("TAF_MTA_ProcEcidCustProgress(): Alloc msg fail!");
            *pulResult = VOS_ERR;
            return VOS_FALSE;
        }

        /* ������Ϣ�ṹ�� */
        pstReserveMsg->stMsgHeader.ulReceiverPid     = UEPS_PID_MTC;
        pstReserveMsg->stMsgHeader.ulMsgName         = ID_MTA_MTC_GSM_CELLINFO_QRY_REQ;

        PS_MEM_SET(pstReserveMsg->aucReserved, 0, sizeof(pstReserveMsg->aucReserved));

        *pulResult = VOS_OK;

        /* ������Ϣ��MTC */
        if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstReserveMsg))
        {
            MTA_ERROR_LOG("TAF_MTA_ProcEcidCustProgress(): Send MSG Fail!");
            *pulResult = VOS_ERR;
        }

        return VOS_TRUE;
    }

    *pulResult = VOS_OK;
    return VOS_FALSE;
}

/*lint -e429 -e438 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MTA_CodeGasEcidStrEx
 ��������  : MTA����GAS��ѯ����ǿС����Ϣ
 �������  : pstGsmCellInfoEx   -- GSMС����Ϣ
 �������  : pucCellinfoStr     -- ������ַ��������ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_CodeGasEcidStrEx(
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx,
    VOS_UINT8                          *pucCellinfoStr
)
{
    TAF_SDC_PLMN_ID_STRU                stPlmnId;
    VOS_INT32                           lLength;
    VOS_UINT8                           aucPlmnStr[MTA_ECID_PLMN_MAX_STR_LEN];

    /* ���GSMС����Ϣ��Ч����ֱ�Ӹ�AT���ؿս�� */
    if (VOS_FALSE == pstGsmCellInfoEx->ulValidFlg)
    {
        lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                                MTA_ECID_CELLINFO_MAX_STRLEN,
                                "%s",
                                MTA_ECID_NONE_RAT_STR);

        if (lLength <= 0)
        {
            return MTA_AT_RESULT_INCORRECT_PARAMETERS;
        }

        return MTA_AT_RESULT_NO_ERROR;
    }

    stPlmnId.ulMcc = pstGsmCellInfoEx->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstGsmCellInfoEx->stPlmnId.ulMnc;

    /* 0,GSM:,<MCC>,<MNC>,<LAC>,<CID>,<TA>,<NB_CELL> */
    PS_MEM_SET(aucPlmnStr, 0, sizeof(aucPlmnStr));
    TAF_MTA_GetPlmnStr(aucPlmnStr, &stPlmnId);
    lLength = VOS_nsprintf((VOS_CHAR *)pucCellinfoStr,
                            MTA_ECID_CELLINFO_MAX_STRLEN,
                            "0,GSM:,%s,%d,%d,%d,%d",
                            aucPlmnStr,
                            pstGsmCellInfoEx->usLac,
                            pstGsmCellInfoEx->usCellId,
                            MTA_ECID_UNDEFINED_VALUE,
                            0);

    if (lLength <= 0)
    {
        return MTA_AT_RESULT_INCORRECT_PARAMETERS;
    }

    return MTA_AT_RESULT_NO_ERROR;
}
/*lint +e429 +e438 +e830*/

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvMtcGsmCellInfoQryCnf
 ��������  : MTAģ���յ�MTCģ��ظ���GSMС����չ��Ϣ
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvMtcGsmCellInfoQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf               = VOS_NULL_PTR;
    MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU  *pstGsmCellInfoQryCnf    = VOS_NULL_PTR;
    VOS_UINT8                          *pucCellInfoStr          = VOS_NULL_PTR;
    MTA_AT_RESULT_ENUM_UINT32           enResult;

    pstGsmCellInfoQryCnf    = (MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU *)pMsg;
    enResult                = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMtcGsmCellInfoQryCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_AS_ECID_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvMtcGsmCellInfoQryCnf: No Buffer!");
        return;
    }

    pucCellInfoStr = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, MTA_ECID_CELLINFO_MAX_STRLEN);
    if (VOS_NULL_PTR == pucCellInfoStr)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvMtcGsmCellInfoQryCnf: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pucCellInfoStr, 0, MTA_ECID_CELLINFO_MAX_STRLEN);

    if (MTA_MTC_RESULT_NO_ERROR == pstGsmCellInfoQryCnf->enResult)
    {
        enResult = TAF_MTA_CodeGasEcidStrEx(&(pstGsmCellInfoQryCnf->stCellInfoEx), pucCellInfoStr);
    }

    if (MTA_AT_RESULT_NO_ERROR == enResult)
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                pucCellInfoStr);
    }
    else
    {
        TAF_MTA_SndAtEcidSetCnf((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                                enResult,
                                VOS_NULL_PTR);
    }

    PS_MEM_FREE(UEPS_PID_MTA, pucCellInfoStr);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}


/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

