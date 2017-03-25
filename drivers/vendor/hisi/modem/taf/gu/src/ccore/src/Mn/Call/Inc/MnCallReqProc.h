/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallReqProc.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��22��
  ����޸�   : 2007��8��22��
  ��������   : Ӧ��������ģ��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  MN_CALL_REQ_PROC_H
#define  MN_CALL_REQ_PROC_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "MnCallBcProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/

/*****************************************************************************
  3���Ͷ���
*****************************************************************************/


/* Deleted by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-15, begin */
/* Deleted by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-15, end */


/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_CALL_CallOrigReqProc
 ��������  : ��������Ӧ�ò����������
             �ú�������鵱ǰ״̬�Ƿ�������һ�����У����Ҽ����еĺ�����ȷ��
             �ú����Ƿ������Լ��Ƿ��ǽ������к��롣���ͨ������CC����
             MNCC_SETUP_REQ��MNCC_EMERG_SETUP_REQԭ�﷢��һ�����л�������С�
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - �������еĺ���ID������Ψһ�ı�ʶ�������
             pstOrigParm - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU             *pstOrigParm
);

/*****************************************************************************
 �� �� ��  : MN_CALL_InternalCallEndReqProc
 ��������  : �ͷź��б�����Դ������CC����MNCC_DISC_REQԭ��
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�Ҷϵĺ��е�ID
             pstEndParm  - �Ҷ�������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
*****************************************************************************/
VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
);

/*****************************************************************************
 �� �� ��  : MN_CALL_CallEndReqProc
 ��������  : ��������Ӧ�ò�ĹҶ�����
             �ú��������ݵ�ǰ״̬�ж���CC����MNCC_DISC_REQ����MNCC_REL_REQԭ�
             Ȼ����ԭ�����ҶϺ��С�
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�Ҷϵĺ��е�ID
             pstEndParm  - �Ҷ�������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��04��                                                    
    ��    ��   : s00217060                                                         
    �޸�����   : VoLTE_PhaseII��Ŀ
*****************************************************************************/
VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        uccallId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
);

/*****************************************************************************
 �� �� ��  : MN_CALL_CallAnswerReqProc
 ��������  : ��������Ӧ�ò��Ӧ������
             �ú�������鵱ǰ״̬�Ƿ��������һ�����磬���ͨ������CC����
             MNCC_SETUP_RESԭ���������
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�����ĺ��е�ID
             pstAnsParam - Ӧ��������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      ucClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
);

/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdReqProc
 ��������  : ��������Ӧ�ò�Ĳ���ҵ���������
             �ú�������Ӧ�÷���Ĳ���ҵ��������ͺ͵�ǰ���к��е�״̬����CC����
             һ�������ԭ�����¼�������õ����������Ӧ���Ա����յ��������Ӧ
             ʱ���жϳ����������Ƿ���ִ����ɣ����Ƿ���Ҫ���ͺ�����ԭ��
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             pstSsParm   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups);
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_BuildNormalCallReqProc
 ��������  : ��������Ӧ�ò����ͨ����
             �ú���������ͨ���е�Setup��Ϣ
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             callId         - �������еĺ���ID������Ψһ�ı�ʶ�������
             pstOrigParam   - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project Ϊ����FDNҵ��CALL SETUP��Ϣ��������Ϣ���Ӻ���ʵ���ȡ
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetMoCallBc
 ��������  : ��ȡ���е�BC��Ϣ
 �������  : pstCallInfo         - ���е�ID
 �������  : pstBc1    -
             pstBc2    -
             penBcRepeatInd
 �� �� ֵ  : VOS_UINT32
                VOS_ERR        ��ȡ���е�BC��Ϣʧ��
                VOS_OK         ��ȡ���е�BC��Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
);


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID);

/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : MN_CALL_StkCallOrigReqProc
 ��������  : ��������STKģ��ĺ�������
 �������  : pstOrigParam   - STK����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸ĺ�����ڲ���

*****************************************************************************/
VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg);
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-5, begin */
TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam    
);
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-5, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_MakeNewCall
 ��������  : �����µ�����
 �������  : MN_CALL_TYPE_ENUM_U8                enCallType   �û��·����º�������
 �������  : MN_CALL_ID_T                        *pNewCallId  �º���CALLID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
);


/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
);
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, end */
/*****************************************************************************
 �� �� ��  : MN_CALL_GetEccNumList
 ��������  : ��ȡ�����������б�
 �������  : ��
 �������  : pstEccNumInfo
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo);

/*****************************************************************************
 �� �� ��  : MN_CALL_RcvAtXlemaReq
 ��������  : �����������ѯ����
 �������  :
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg);


/* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstMsgSend);

VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf);
/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq);

VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);
#endif

VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);

VOS_VOID  TAF_CALL_RcvCcwaiSetReq(MN_CALL_APP_REQ_MSG_STRU *pstAppReq);
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

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

#endif /* MN_CALL_REQ_PROC_H */

