/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgSendSms.h
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��21��
  ����޸�   :
  ��������   : MSG���͸�SMSģ��Ľӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��21��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __MNMSGSENDSMS_H__
#define __MNMSGSENDSMS_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MnMsgApi.h"
#include  "MnMsgSmCommProc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �ӿں�������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsRpDataReq
 ��������  : ����Rp-Data���ݵ�NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��10��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ     
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpDataReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    const VOS_UINT8                     *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);

/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsCpAckReq
 ��������  : ����CP-ACK���ݵ�NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pucSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_VOID MN_MSG_SendSmsCpAckReq(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsRpReportReq
 ��������  : ����Rp-Report���ݵ�NAS���SMSģ��
 �������  : pSendMsg:�������ݵ�����,����ΪЭ��24011��RP-ACK��RP-ERROR������
             ucSendLen:�������ݵĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��3��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpReportReq(
    const VOS_UINT8                     *pucSendMsg,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType    
);

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsSmmaReq
 ��������  : ����SMMA��Ϣ��NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��3��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ     
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsSmmaReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */


/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpData
 ��������  : ����24011��Rp-Data�Ľṹ����һ��Rp-Data���ֽ���
 �������  : stRpData:24011��Rp-Data�Ľṹ
 �������  : pucRpduContent:Rp-Data���ֽ���������
             pucRpduLen:Rp-Data���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpData(
    const MN_MSG_RP_DATA_STRU           *pstRpData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);

/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpAck
 ��������  : ����24011��Rp-ACK�Ľṹ����һ��Rp-ACK���ֽ���
 �������  : pstRpAck:24011��Rp-ACK�Ľṹ
 �������  : pucRpduContent:Rp-ACK���ֽ���������
             pucRpduLen:Rp-ACK���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpAck(
    const MN_MSG_RP_ACK_STRU            *pstRpAck,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
);

/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpErr
 ��������  : ����24011��Rp-Error�Ľṹ����һ��Rp-Error���ֽ���
 �������  : pstRpErr:24011��Rp-Error�Ľṹ
 �������  : pucRpduContent:Rp-Error���ֽ���������
             pucRpduLen:Rp-Error���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpErr(
    const MN_MSG_RP_ERR_STRU            *pstRpErr,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
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

#endif /* __MNMSGSENDSMS_H__ */

