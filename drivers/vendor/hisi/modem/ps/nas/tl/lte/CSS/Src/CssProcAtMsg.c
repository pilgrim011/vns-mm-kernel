/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcAtMsg.c
  Description     : ��C�ļ�������CSS���յ�AT��Ϣ��ʵ��
  History         :
     1.chengmin 00285307    2015-10-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include            "CssAtInterface.h"
#include            "CssProcAtMsg.h"
#include            "CssCloudStrategyPublic.h"
#include            "CssProcCommMsg.h"
#include            "MnClient.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCATMSG_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_UpdateStateAccordingToAtMccSetMsg
 Description    : �����·�����Ϣ������״̬��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2016-01-29  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateStateAccordingToAtMccSetMsg
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU           *pRcvMsg,
    VOS_UINT8                                     aucMcc[2],
    VOS_UINT32                                    ulRslt
)
{
    VOS_UINT32                          ulLoop;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;
    VOS_UINT32                          ulUpdateRslt;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_ENTRY);

    /* �����AP���ڸ��¹����� */
    if (CSS_TRUE == CSS_IsApUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_FUNCTION_LABEL1);

        /* ���������е�״̬�� */
        (VOS_VOID)CSS_UpdateOneMcc(&(pstCssCloudContrl->stApMccUpdate), aucMcc);

        /* ���ȫ���������ˣ�����ֹ������ */
        if ((CSS_TRUE == CSS_IsAllMccUpdated(&(pstCssCloudContrl->stApMccUpdate))
             && CSS_END_OF_AT_SEQ == pRcvMsg->ucSeq)
            || (CSS_CAUSE_NULL_PTR == ulRslt))
        {
            TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_FUNCTION_LABEL2);

            /* ��ֹAP�������� */
            CSS_EndApUpdateProcedure();
        }
    }

    /* ����MMC��AS�Ƿ����ڸ����� */
    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        /* ���������ڸ��µ�������continue */
        if (CSS_TRUE != pstCssCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
        {
            continue;
        }

        /* �ڴ��Ѳ����洢��ֱ���ж����� */
        if (CSS_CAUSE_NULL_PTR == ulRslt)
        {
            /* �ظ�GEO_RSP */
            CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);

            /* ��ֹ���� */
            CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));

            continue;
        }

        /* ״̬����� */
        ulUpdateRslt = CSS_UpdateOneMcc(&(pstCssCloudContrl->astMccUpdate[ulLoop]), aucMcc);

        /* ���ȫ���������ˣ�����ֹ������ */
        if (CSS_TRUE == CSS_IsAllMccUpdated(&(pstCssCloudContrl->astMccUpdate[ulLoop]))
            && CSS_END_OF_AT_SEQ == pRcvMsg->ucSeq)
        {
            /* �ظ�GEO_RSP */
            if (CSS_SUCC == ulRslt)
            {
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_SUCC);
            }
            else
            {
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);
            }

            /* ��ֹ���� */
            CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));
        }
        else
        {
            if (CSS_TRUE == ulUpdateRslt && CSS_SUCC != ulRslt)
            {
                /* �ظ�GEO_RSPʧ�� */
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);

                /* ��ֹ���� */
                CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));
            }
        }
    }
}

/*****************************************************************************
 Function Name  : CSS_SendAtMccSetCnf
 Description    : ��AT�ظ�MCC_INFO_SET_CNF��Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SendAtMccSetCnf(const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg, VOS_UINT32 ulResult)
{
    CSS_AT_MCC_INFO_SET_CNF_STRU       *pstMccSetCnf;

    TLPS_PRINT2LAYER_INFO1(CSS_SendAtMccSetCnf_ENUM, LNAS_ENTRY, ulResult);

    if (VOS_NULL_PTR == pRcvMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    /*������Ϣ�ռ�*/
    pstMccSetCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_MCC_INFO_SET_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstMccSetCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstMccSetCnf),
                    CSS_GET_MSG_LENGTH(pstMccSetCnf),
                    0,
                    CSS_GET_MSG_LENGTH(pstMccSetCnf));

    CSS_WRITE_AT_MSG_HEAD(pstMccSetCnf,ID_CSS_AT_MCC_INFO_SET_CNF);

    pstMccSetCnf->ucSeq                 = pRcvMsg->ucSeq;
    pstMccSetCnf->ulResult              = ulResult;
    pstMccSetCnf->usClientId            = pRcvMsg->usClientId;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstMccSetCnf);
}



VOS_VOID CSS_SendAtQueryMccNotifyByMccList(CSS_MCC_ID_STRU astMccID[CSS_MAX_PLMN_ID_NUM], VOS_UINT32 ulMccNum, VOS_UINT16 usClientId)
{
    CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU  *pMsg;
    VOS_UINT32                          ulLoop;

    TLPS_PRINT2LAYER_INFO2(CSS_SendAtQueryMccNotifyByMccList_ENUM, LNAS_ENTRY, ulMccNum, usClientId);

    /*������Ϣ�ռ�*/
    pMsg = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pMsg), CSS_GET_MSG_LENGTH(pMsg), 0, CSS_GET_MSG_LENGTH(pMsg));

    CSS_WRITE_AT_MSG_HEAD(pMsg,ID_CSS_AT_QUERY_MCC_INFO_NOTIFY);

    /* ��ֵMCC ID */
    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        pMsg->astMccId[ulLoop].aucMcc[0] = astMccID[ulLoop].aucMccId[0];
        pMsg->astMccId[ulLoop].aucMcc[1] = astMccID[ulLoop].aucMccId[1];
    }

    pMsg->ulMccNum   = ulMccNum;
    pMsg->usClientId = usClientId;

    /* �����汾�� */
    CSS_MEM_CPY_S(  pMsg->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);


    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pMsg);
}



/*****************************************************************************
 Function Name  : CSS_ProcAtMsgDeleteOneMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ��Ϣ��ɾ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgDeleteOneMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    VOS_UINT8                           aucMccId[2] = {0};
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNum;

    CSS_MEM_SET_S(  astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* ת��MCC ID */
    if (CSS_FAIL == CSS_ConvertStrToHex(aucMccId, pRcvMsg->aucMccInfoBuff, 4))
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
        return;
    }

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_ENTRY);

    /* ���MMC����ASû���ڸ��¹����У�����AT����MCC���� */
    if (CSS_FALSE == CSS_IsMmcOrAsUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);

        /* ���ָ��ɾ�������MCC�ڱ��ش��ڣ��������������� */
        if (CSS_TRUE == CSS_IsMccExistInLocal(aucMccId))
        {
            TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL2);

            /* ��AP�ϱ���MCC */
            ulMccNum = 1;
            astMccID[0].aucMccId[0] = aucMccId[0];
            astMccID[0].aucMccId[1] = aucMccId[1];

            /* ����AP�������� */
            CSS_StartApMccUpdateProcedure(astMccID, ulMccNum, pRcvMsg->usClientId);

            /* ɾ����MCCԤ��Ƶ����Ϣ */
            CSS_DeleteOneMcc(aucMccId);
        }
    }
    /* ���MMC����AS���ڸ��¹����У����Ȼ�����̶Գ��������ʱAP��δ�·�MCC��
       ֻ�轫����MCCɾ�����ȴ�AP�·�SET_REQ */
    else
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL3);

        /* ɾ�����ص�MCCԤ��Ƶ����Ϣ */
        CSS_DeleteOneMcc(aucMccId);

        /* �ظ�SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }
}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsgDeleteAllMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ��Ϣ��ɾ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgDeleteAllMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNum;

    CSS_MEM_SET_S(  astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_ENTRY);

    /* ���MMC����ASû���ڸ��¹����У�����AT����MCC���� */
    if (CSS_FALSE == CSS_IsMmcOrAsUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);

        /* ��ȡ�ڴ��е�����MCC ID */
        CSS_GetMccListFromLocal(astMccID, &ulMccNum);

        /* ���MCC ID������Ϊ0���������������� */
        if (0 != ulMccNum)
        {
            /* ����AP�������� */
            CSS_StartApMccUpdateProcedure(astMccID, ulMccNum, pRcvMsg->usClientId);

            /* ɾ�����ص�MCCԤ��Ƶ����Ϣ */
            CSS_DeleteAllMcc();
        }
    }
    /* ���MMC����AS���ڸ��¹����У����Ȼ�����̶Գ��������ʱAP��δ�·�MCC��AP����AT�����Ǵ��д���һ��AT����û�д�����ǰ�����ܴ�������AT����
       ֻ�轫����MCCɾ�����ȴ�AP�·�SET_REQ */
    else
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_FUNCTION_LABEL2);

        /* ɾ�����ص�MCCԤ��Ƶ����Ϣ */
        CSS_DeleteAllMcc();

        /* �ظ�SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }

}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsgAddMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ��Ϣ����Ӵ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgAddMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT8                          *pucBuff;
    VOS_UINT32                          ulBuffLen;
    VOS_UINT32                          ulResult;


    /* ת��MCC ID */
    if (CSS_FAIL == CSS_ConvertStrToHex(aucMcc, pRcvMsg->aucMccInfoBuff, 4))
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
        return;
    }

    TLPS_PRINT2LAYER_INFO2(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_ENTRY, aucMcc[0], aucMcc[1]);

    /* ���ַ���ת��16���� */
    if (0 != (pRcvMsg->ulMccInfoBuffLen % 2))
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        /* ��AT�ظ�SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* ����״̬�� */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    ulBuffLen = pRcvMsg->ulMccInfoBuffLen / 2;
    pucBuff = CSS_MEM_ALLOC(sizeof(VOS_UINT8)*ulBuffLen);
    if (CSS_NULL_PTR == pucBuff)
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL2);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* ����״̬�� */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    if (CSS_FAIL == CSS_ConvertStrToHex(pucBuff, pRcvMsg->aucMccInfoBuff, pRcvMsg->ulMccInfoBuffLen))
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL3);

        CSS_MEM_FREE(pucBuff);
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* ����״̬�� */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    /* �������񣬷�ֹ��������У���������API�ӿ� */
    (VOS_VOID)VOS_TaskLock();

    /* ��ȡ��Ϣ�е�MCCԤ��Ƶ�� */
    ulResult = CSS_ReadMccFromAtMsg(pucBuff, ulBuffLen);

    /* �������� */
    (VOS_VOID)VOS_TaskUnlock();

    if (CSS_SUCC == ulResult)
    {
        /* ��AT�ظ��ɹ� */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }
    else
    {
        /* ��AT�ظ�ʧ�� */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
    }

    /* ����״̬�� */
    CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, ulResult);

    CSS_MEM_FREE(pucBuff);
}



/*****************************************************************************
 Function Name  : CSS_ProcAtMsgMccSetReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgMccSetReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_ENTRY);

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ��� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL1);
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
        return;
    }

    /* ��������ƶ˻�ȡ��Ҳֱ�ӷ��� */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }

    /* ������ذ汾�Ż�Ϊ��ʼ״̬���򽫱�������MCC��ɾ����Ȼ��汾����� */
    if (CSS_FALSE == CSS_HasGetMccVersionFromAp())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL3);
        CSS_DeleteAllMcc();
    }

    /* ��ȡ�ƶ˰汾�ţ������ڱ��� */
    CSS_MEM_CPY_S(  CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    pRcvMsg->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);

    /* ���ݲ������ʹ��� */
    if (AT_CSS_SET_MCC_TYPE_DELETE_ALL_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgDeleteAllMccReq(pRcvMsg);
    }
    else if (AT_CSS_SET_MCC_TYPE_DELETE_ONE_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgDeleteOneMccReq(pRcvMsg);
    }
    else if (AT_CSS_SET_MCC_TYPE_ADD_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgAddMccReq(pRcvMsg);
    }
    else
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
    }

    /* ��ӡ���ش洢��Ԥ��Ƶ����Ϣ */
    CSS_PrintLocalPrefFreqInfo();

    /* ��������ȫ�ֱ��� */
    CSS_SndOmPubCloudCtrlInd();
}

/*****************************************************************************
 Function Name  : CSS_ProcAtMsgMccVersionReq
 Description    : ID_AT_CSS_MCC_VERSION_INFO_REQ��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgMccVersionReq
(
    const AT_CSS_MCC_VERSION_INFO_REQ_STRU  *pRcvMsg
)
{
    CSS_AT_MCC_VERSION_INFO_CNF_STRU   *pCnf;

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccVersionReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pRcvMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    /*������Ϣ�ռ�*/
    pCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_MCC_VERSION_INFO_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pCnf), CSS_GET_MSG_LENGTH(pCnf), 0, CSS_GET_MSG_LENGTH(pCnf));
    CSS_WRITE_AT_MSG_HEAD(pCnf,ID_CSS_AT_MCC_VERSION_INFO_CNF);

    pCnf->usClientId    = pRcvMsg->usClientId;

    CSS_MEM_CPY_S(  pCnf->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pCnf);
}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsg
 Description    : AT��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsg(const VOS_VOID *pRcvMsg)
{

    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_AT_CSS_MCC_INFO_SET_REQ:
            CSS_ProcAtMsgMccSetReq((const AT_CSS_MCC_INFO_SET_REQ_STRU*)pRcvMsg);
            break;

        case ID_AT_CSS_MCC_VERSION_INFO_REQ:
            CSS_ProcAtMsgMccVersionReq((const AT_CSS_MCC_VERSION_INFO_REQ_STRU *)pRcvMsg);
            break;

        default:
            break;
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of CssProcAtMsg.c */



