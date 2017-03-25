/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgReport.h
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
    �޸�����   : ���ⵥ�� AT2D04609,CMMS��������ӣ�
  3.��    ��   : 2008��8��29��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D05344, ����Ϣģ���ʼ�����̽��������SDT�����뵥�巴���������ӺͶϿ�����,Э��ջ���ظ��ϱ���ʼ������¼�;

******************************************************************************/
#ifndef __MNMSGREPORT_H__
#define __MNMSGREPORT_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"
#include  "TafCbsInterface.h"
#include "NasSms.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �ӿں�������
*****************************************************************************/
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
);
/* Added by f62575 for AT Project��2011-10-03,  End*/

/***********************************************************************
�� �� ��  : MN_MSG_ReportRcvMsgEvent
��������  : �յ�һ������(����Delliver,Status Report����),�㲥�ϱ�������Ӧ��
�������  : opId:��ʶ���β���
            pstDeliverEvt:Deliver�����ϱ��������
�������  : ��
�� �� ֵ  : ��
            ��
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
);

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
************************************************************************/
VOS_VOID MN_MSG_ReportSmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bBroadCast,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

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
);

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
);

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
************************************************************************/
VOS_VOID MN_MSG_ReportDeliverErr(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode);

/***********************************************************************
�� �� ��  : MN_MSG_ReportLinkCtrl
��������  : �м���·���Ʋ������ý���ϱ�
�������  : clientId    : ����������Client��ID
            opId        : Operation ID, ��ʶ���β���
            ulErrorCode : ����ԭ��ֵ,MN_ERR_NO_ERROR˵�����óɹ�

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
);

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
);

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
);

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
);

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
);

/***********************************************************************
�� �� ��  : MN_MSG_ReportDeleteTestEvent
��������  : �ϱ�ɾ���������
�������  : clientId  : ����������Client��ID
            opId      : Operation ID, ��ʶ���β���
            pstDeleteTestEvt:ɾ��������Բ������
            ulEventType:�ϱ��¼�����
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
);

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
);

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
);

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
);

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
);


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
    VOS_UINT32                               ulEventType
);

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
);

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
*****************************************************************************/
VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
);


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

#endif /* __MNMSGREPORT_H__*/

