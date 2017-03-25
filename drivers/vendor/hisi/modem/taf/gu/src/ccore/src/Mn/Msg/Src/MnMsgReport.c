/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgReport.c
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D03741,��̹淶���⣺   1��ö�����Ͷ���   2��ȫ�ֱ������ⲿ����   3���ļ�������ע�����⣻   ��ӡ��Ϣ������   1�����ӵ��Դ�ӡ����
  3.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D04609,CMMS��������ӣ�
  4.��    ��   : 2008��8��29��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D05344, ����Ϣģ���ʼ�����̽��������SDT�����뵥�巴���������ӺͶϿ�����,Э��ջ���ظ��ϱ���ʼ������¼�;
  5.��    ��   : 2008��09��08��
    ��    ��   : f62575
    �޸�����   : ���ⵥAT2D05583,CBS����ģ�����PC-lint����
  6.��    ��   : 2008��10��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06152��AT2D06151��, USIMM�Ż������SMSP�ļ���ض�д����ʧ��
  7.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D07942��AT2D09557��, �������ĺ����ϱ�ʱ��ϳ�
  8.��    ��   : 2009��7��18��
    ��    ��   : z40661
    �޸�����   : �ն˿������������
  9.��    ��   : 2009��7��31��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13420,����TAFģ���ʼ���������
 10.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafCbaCtx.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_REPORT_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

MN_MSG_EVENT_INFO_STRU           f_stMsgEventInfo;


extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/***********************************************************************
�� �� ��  : MN_MSG_ReportRcvMsgEvent
��������  : �յ�һ������(����Delliver,Status Report����),�㲥�ϱ�������Ӧ��
�������  : opId:��ʶ���β���
            pstDeliverEvt:Deliver�����ϱ��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportRcvMsgEvent(
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELIVER_EVT_INFO_STRU  *pstDeliverEvt
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    /*�㲥�ϱ���һ������*/
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeliverInfo,pstDeliverEvt,sizeof(f_stMsgEventInfo.u.stDeliverInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER,(VOS_VOID *)&f_stMsgEventInfo);
}


/***********************************************************************
�� �� ��  : MN_MSG_ReportSmChanged
��������  : ��USIM��NVIM�еĶ���״̬�����˸ı�ʱ,�ϱ�������Ӧ��
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            bBroadCast:�Ƿ��ǹ㲥�ϱ�
            enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��04��23��
   ��    ��   : L00171473
   �޸�����   : for V7R1 porting, �������WARNING
************************************************************************/
VOS_VOID MN_MSG_ReportSmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bBroadCast,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_OPERATION_ID_T                   bcOpId;
    NAS_OM_SMS_STATICS_STRU             stSmsOmEventPara;
    VOS_UINT32                          ulTempRec;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    MN_MSG_GetSmStorageList(enMemStore,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec,
                            f_stMsgEventInfo.u.stStorageListInfo.aulEachStatusRec);
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageListInfo.enMemStroe = enMemStore;
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                           (VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                          (VOS_VOID *)&f_stMsgEventInfo);
    }
    stSmsOmEventPara.ucMemType = NAS_SMS_SAVE_AREA_SM;
    stSmsOmEventPara.ucMemCap  = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
    stSmsOmEventPara.ucMemUsed = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
    NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_STATICS,
                    &stSmsOmEventPara, sizeof(stSmsOmEventPara));

    if (f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec == f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec)
    {
        bcOpId = MN_MSG_GetBCopId();
        f_stMsgEventInfo.opId = bcOpId;
        f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;

        /* Modified by L00171473 for V7R1 porting, 2011-04-23, begin, �������WARNING */
        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = ulTempRec;
        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = ulTempRec;

        if (VOS_TRUE == bBroadCast)
        {
            MN_SendClientEvent(MN_CLIENT_ALL,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
        else
        {
            MN_SendClientEvent(clientId,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
    }


}

/***********************************************************************
�� �� ��  : MN_MSG_ReportMemExceed
��������  : ��USIM��NVIM�еĶ�������,��ʱ�յ���һ������,�ϱ���Ӧ�����㹻�������ն���
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportMemExceed(
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_INFO_LOG("MN_MSG_ReportMemExceed: step into function.");
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;
    f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = MN_MSG_GetSmCapacity(enMemStore);
    f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec;

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_STORAGE_EXCEED,
                       (VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportDeleteEvent
��������  : �ϱ�ɾ���������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pstDeleteEvt:ɾ���������
            ulEventType:ɾ������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportDeleteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_EVT_INFO_STRU   *pstDeleteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteInfo,pstDeleteEvt,sizeof(MN_MSG_DELETE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportDeleteTestEvent
��������  : �ϱ�ɾ���������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pstDeleteTestEvt:ɾ��������Բ������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportDeleteTestEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_TEST_EVT_INFO_STRU *pstDeleteTestEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteTestInfo,pstDeleteTestEvt,sizeof(MN_MSG_DELETE_TEST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportWriteEvent
��������  : �ϱ�д���Ų������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pstDeleteEvt:д���Ų������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportWriteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_EVT_INFO_STRU    *pstWriteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stWriteInfo,pstWriteEvt,sizeof(MN_MSG_WRITE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportReadEvent
��������  : �ϱ������Ų������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pReadEvt:�����Ų������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportReadEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_EVT_INFO_STRU     *pReadEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stReadInfo,pReadEvt,sizeof(MN_MSG_READ_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportListEvent
��������  : �ϱ��б���Ų������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pListEvt:�б���Ų������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportListEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_EVT_INFO_STRU     *pListEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stListInfo,pListEvt,sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportModifyEvent
��������  : �ϱ��޸Ķ��Ų������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pModifyStatusEvt:�޸Ķ���״̬�������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportModifyEvent(
    MN_CLIENT_ID_T                           clientId,
    MN_OPERATION_ID_T                        opId,
    const MN_MSG_MODIFY_STATUS_EVT_INFO_STRU *pModifyStatusEvt,
    VOS_UINT32                                ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stModifyInfo,pModifyStatusEvt,sizeof(MN_MSG_MODIFY_STATUS_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportSrvParmEvent
��������  : �ϱ����Ų������û��ȡ�������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pstSrvParmEvt:���û��ȡ���Ų������
            ulEventType:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportSrvParmEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SRV_PARM_EVT_INFO_STRU *pstSrvParmEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSrvParmInfo,pstSrvParmEvt,sizeof(MN_MSG_SRV_PARM_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReportSentEvent
 ��������  : �ϱ���Ϣ���ͻ򻺴�Ľ��
 �������  : clientId  : ����������Client��ID
             opId      : Operation ID, ��ʶ���β���
             pstSendMsgEvt:��Ϣ���ͻ򻺴�Ľ��
             ulEventType:��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_ReportSentEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SENDMSG_EVT_INFO_STRU        *pstSendMsgEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSendMsgInfo,pstSendMsgEvt,sizeof(MN_MSG_SENDMSG_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReportSubmitRptEvent
 ��������  : �ϱ���Ϣ���ͻ򻺴�Ľ��
 �������  : clientId  : ����������Client��ID
             opId      : Operation ID, ��ʶ���β���
             pstSubmitRptEvt:���շ�����Ϣ�ı���
             ulEventType:��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_ReportSubmitRptEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     *pstSubmitRptEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSubmitRptInfo,
               pstSubmitRptEvt,
               sizeof(f_stMsgEventInfo.u.stSubmitRptInfo));
    MN_SendClientEvent(f_stMsgEventInfo.clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}
/*****************************************************************************
 �� �� ��  : MN_MSG_ReportRcvPathEvent
 ��������  : �ϱ����û��ȡ��ǰ����·���Ľ��
 �������  : clientId  : ����������Client��ID
             opId      : Operation ID, ��ʶ���β���
             bBroadCast:�Ƿ���Ҫ�㲥�ϱ�
             pRcvPathEvt:��ǰ����·���Ľ��
             ulEventType:��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_ReportRcvPathEvent(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    VOS_BOOL                               bBroadCast,
    const MN_MSG_RCVMSG_PATH_EVT_INFO_STRU *pRcvPathEvt,
    VOS_UINT32                             ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stRcvMsgPathInfo,pRcvPathEvt,sizeof(MN_MSG_RCVMSG_PATH_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReportMemStatustEvent
 ��������  : �ϱ����û��ȡ��ǰAPP�ڴ�ʹ�õĽ��
 �������  : clientId  : ����������Client��ID
             opId      : Operation ID, ��ʶ���β���
             bBroadCast:�Ƿ��ǹ㲥�ϱ�
             pstMemStatusEvt:��ǰAPP�ڴ����
             ulEventType:��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_ReportMemStatustEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    VOS_BOOL                             bBroadCast,
    const MN_MSG_MEMSTATUS_EVT_INFO_STRU *pstMemStatusEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stMemStatusInfo,pstMemStatusEvt,sizeof(MN_MSG_MEMSTATUS_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportSrvParmChanged
��������  : ��USIM��NVIM�еĶ��Ų��������˸ı�ʱ,�ϱ�������Ӧ��
�������  : clientId  :����������Client��ID
            opId      :Operation ID, ��ʶ���β���
            enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportSrvParmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    MN_MSG_GetSmspStorageList(enMemStore,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulTotalRec,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulUsedRec,
                               f_stMsgEventInfo.u.stSrvParmChangeInfo.astSrvParm);
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_SRV_PARM_CHANGED,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportDeliverErr
��������  : MTʧ�ܺ�,�㲥��Ӧ���ϱ����ն���ʧ��
�������  : ucRpStatus:ʧ�ܵ�״̬
            ucRpCause:ʧ��ԭ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��11��
   ��    ��   : f62575
   �޸�����   : V9R1 STK������Ŀ
************************************************************************/
VOS_VOID MN_MSG_ReportDeliverErr(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    MN_OPERATION_ID_T                   bcOpId;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    f_stMsgEventInfo.u.stDeliverErrInfo.enErrorCode = enErrorCode;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    bcOpId = MN_MSG_GetBCopId();
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = bcOpId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER_ERR,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_ReportLinkCtrl
��������  : �м���·���Ʋ������ý���ϱ�
�������  : clientId    : ����������Client��ID
            opId        : Operation ID, ��ʶ���β���
            ulEventType : �ϱ��¼�����
            ulErrorCode : ����ԭ��ֵ,MN_ERR_NO_ERROR˵�����óɹ�
            enLinkCtrl  : ��ǰ���õ��м���·��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_ReportLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode,
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl
)
{

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    f_stMsgEventInfo.u.stLinkCtrlInfo.enLinkCtrl = enLinkCtrl;
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    return;
}

/* Added by f62575 for AT Project��2011-10-03,  Begin*/
/*****************************************************************************
 �� �� ��  : MN_MSG_ReportResult
 ��������  : ����������ý���ϱ�
 �������  : MN_CLIENT_ID_T       clientId     ����������Client��ID
             MN_OPERATION_ID_T    opId         Operation ID, ��ʶ���β���
             VOS_UINT32           ulEventType  �ϱ��¼�����
             VOS_UINT32           ulErrorCode  ����ԭ��ֵ,MN_ERR_NO_ERROR˵�����óɹ�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��3��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_ReportResult(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId                     = clientId;
    f_stMsgEventInfo.opId                         = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    MN_SendClientEvent(clientId, MN_CALLBACK_MSG, ulEventType, (VOS_VOID *)&f_stMsgEventInfo);
    return;
}
/* Added by f62575 for AT Project��2011-10-03,  End*/


/*****************************************************************************
 �� �� ��  : MN_MSG_SmspInitFinish
 ��������  : SIM���е�EFSMSS��EFSMSP��ʼ����ɺ�,�ϱ�USIM������ز���
 �������  : ��
 �������  : ��

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��02��26��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SmspInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(enPowerState < MN_MSG_USIM_POWER_WAIT_EFSMSP)
    {
        return;
    }
    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmspStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulTotalSrvParm,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulUsedSrvParm,
                              f_stMsgEventInfo.u.stInitSmspResultInfo.astSrvParm);

    MN_MSG_GetCurRcvMsgPath(&f_stMsgEventInfo.u.stInitSmspResultInfo.stRcvMsgPath);

    f_stMsgEventInfo.u.stInitSmspResultInfo.enClass0Tailor = MN_MSG_GetClass0Tailor();;

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_SMSP_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

}

/*****************************************************************************
 �� �� ��  : MN_MSG_SmInitFinish
 ��������  : SIM����ʼ����ɺ�,�ϱ�USIM������ز���
 �������  : ��
 �������  : ��

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  4.��    ��   : 2015��03��14��
    ��    ��   : y00245242
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

#ifndef __PS_WIN32_RECUR__
    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
#endif

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(MN_MSG_USIM_POWER_ON != enPowerState)
    {
        return;
    }

    /* ��������ļ�Ҫ����µı�־����֤�ظ����յ�REFRESH��Ϣʱ�������ļ������� */
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmStorageList(MN_MSG_MEM_STORE_SIM,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmRec,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmRec,
                            f_stMsgEventInfo.u.stInitResultInfo.aulEachStatusRec);


    MN_MSG_GetSmsrStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmsrRec,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmsrRec);

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

    MN_MSG_StartMemNotification();
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SmInitFinish
 ��������  : ��ʽ��λʱ��ֹAT������ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��07��31��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��10��
    ��    ��   : f62575
    �޸�����   : STK&DCM Project
  3.��    ��   : 2012��12��03��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012120305230,FDN��MO SMS CONTROL���̶�ʱ��δֹͣ���⣻
  4.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
  5.��    ��   : 2013��08��06��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID MN_MSG_FinishMoProc(
    VOS_VOID
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulTotal;

    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));

    PS_MEM_SET(&stMoEntity,0x00,sizeof(stMoEntity));

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
        {
            continue;
        }
        else
        {
            if ((MN_MSG_MO_TYPE_MO == stStoreMsg.stMoInfo.enSmsMoType)
             || (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
             || ((MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType)
              && (VOS_TRUE == stStoreMsg.stMoInfo.bReportFlag)))
            {
                MN_INFO_LOG("MN_MSG_FinishMoProc: Abnormal abort.");
                /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
                stSubmitRptEvt.ucMr                 = stStoreMsg.stMoInfo.ucMr;/*TP-MR*/
                stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
                stSubmitRptEvt.enSaveArea           = stStoreMsg.stMoInfo.enSaveArea;
                stSubmitRptEvt.ulSaveIndex          = stStoreMsg.stMoInfo.ulSaveIndex;
                /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
                MN_MSG_ReportSubmitRptEvent(stStoreMsg.stMoInfo.clientId,
                                            stStoreMsg.stMoInfo.opId,
                                            (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                            MN_MSG_EVT_SUBMIT_RPT);
            }
            MN_MSG_FreeStoreMsg(ulStoreIndex);
        }

    }

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    MN_MSG_GetMoEntity(&stMoEntity);
    if ((stMoEntity.enSmaMoState > MN_MSG_MO_STATE_NULL)
     && (stMoEntity.enSmaMoState < MN_MSG_MO_STATE_MAX))
    {
        if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_FDN_CHECK);
        }

        if (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK);
        }

        MN_INFO_LOG("MN_MSG_FinishMoProc: fail to mo.");
        stSubmitRptEvt.ucMr = stMoEntity.ucMr;/*TP-MR*/
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
        stSubmitRptEvt.enSaveArea           = stMoEntity.enSaveArea;
        stSubmitRptEvt.ulSaveIndex          = stMoEntity.ulSaveIndex;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
        MN_MSG_ReportSubmitRptEvent(stMoEntity.clientId,
                                    stMoEntity.opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_MSG_DestroyMoInfo();
    }

    return;

}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

