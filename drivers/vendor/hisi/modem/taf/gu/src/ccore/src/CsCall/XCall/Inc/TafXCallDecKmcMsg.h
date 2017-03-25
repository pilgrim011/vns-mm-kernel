
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallDecKmcMsg.h
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��10��20��
  ��������   : TafXCallDecKmcMsg.c��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00359089
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_DEC_KMC_MSG_H__
#define __TAF_X_CALL_DEC_KMC_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "TafXCallKmcCommType.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT32 TAF_XCALL_ConvertBcdToDecimal(
    VOS_UINT8                                              *pucSrcData,
    VOS_UINT16                                             *pusDestData
);

VOS_UINT32 TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(
    VOS_UINT8                                              *pucSrcData,
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeStamp
);

VOS_VOID TAF_XCALL_DecKeyRspMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecMtEncryptIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecPubKeyUpdateMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecErrIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecPubKeyUpdateAckMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecRemoteCtrlCmdMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecodeKmcMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    TAF_XCALL_KMC_MSG_STRU             *pstDecodedData
);

#endif

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafXCallDecKmcMsg.h */

