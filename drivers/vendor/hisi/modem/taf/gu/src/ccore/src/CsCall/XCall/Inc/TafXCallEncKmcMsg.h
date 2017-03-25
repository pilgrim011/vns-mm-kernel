
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallEncKmcMsg.h
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��10��20��
  ��������   : TafXCallEncKmcMsg.c��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00359089
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_ENC_KMC_MSG_H__
#define __TAF_X_CALL_ENC_KMC_MSG_H__

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_KMC_ENC_TBL_ITEM(enMsgType, pProcMsgFunc)\
            {\
                (VOS_UINT32)((enMsgType) & 0x000000FF), (pProcMsgFunc)\
            }

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
typedef TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 (*TAF_XCALL_ENC_KMC_MSG_PROC_FUNC)(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
/*****************************************************************************
�ṹ��    : TAF_XCALL_ENC_KMC_MSG_PROC_STRU
�ṹ˵��  : TAF XCALLģ�����KMC��Ϣ�������Ľṹ
1.��    ��  : 2015��10��26��
  ��    ��  : l00359089
  �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMsgType;          /* TAF XCALL KMC ��Ϣ����*/
    TAF_XCALL_ENC_KMC_MSG_PROC_FUNC                         pProcMsgFunc;
}TAF_XCALL_ENC_KMC_MSG_PROC_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID TAF_XCALL_FillReservedFld(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyReqMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
#ifdef VOS_WIN32
TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncMtEncryptIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncErrIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateAckMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
#endif

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncodeKmcMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
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

#endif /* end of TafXCallEncKmcMsg.h */

