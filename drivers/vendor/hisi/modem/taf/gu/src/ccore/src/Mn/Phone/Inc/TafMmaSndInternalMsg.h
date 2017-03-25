/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaSndInternalMsg.h
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��7��9��
  ����޸�   :
  ��������   : �����ڲ���Ϣ���ʹ���ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _TAF_MMA_SND_INTERNAL_MSG_H_
#define _TAF_MMA_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafMmaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_INVALID_INTERNAL_MSG_ID                 (0xFFFF)                /* ��ϢID����Чֵ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_MMA_INTERNAL_MSG_ID_ENUM
 �ṹ˵��  : �ڲ���ϢID
 1.��    ��   : 2013��7��9��
   ��    ��   : w00176964
   �޸�����   : MMA�ڲ���ϢIDö��
*****************************************************************************/
enum TAF_MMA_INTERNAL_MSG_ID_ENUM
{
    MMA_MMA_INTER_POWER_INIT                = 0x4000,                       /*_H2ASN_MsgChoice TAF_MMA_INTER_POWER_INIT_REQ_STRU */

    MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,                                   /*_H2ASN_MsgChoice TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU */

    MMA_MMA_PHONE_MODE_RSLT_IND,                                            /*_H2ASN_MsgChoice TAF_MMA_PHONE_MODE_RSLT_IND_STRU */

    MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,                                     /*_H2ASN_MsgChoice TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU */

    MMA_MMA_IMS_SWITCH_RSLT_IND,                                            /*_H2ASN_MsgChoice TAF_MMA_IMS_SWITCH_RSLT_IND_STRU */

    MMA_MMA_INTER_SYS_CFG_SET_REQ,                                          /*_H2ASN_MsgChoice TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU */

    MMA_MMA_INTER_ABORT_IND,                                                /*_H2ASN_MsgChoice TAF_MMA_INTER_ABORT_IND_STRU */

    MMA_MMA_SYS_CFG_RSLT_IND,                                               /*_H2ASN_MsgChoice TAF_MMA_SYS_CFG_RSLT_STRU */

    MMA_MMA_INTER_MSG_BUTT
};
typedef VOS_UINT32 TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : TAF_MMA_PHONE_MODE_RESULT_ENUM
 �ṹ˵��  : PHONE MODE״̬���˳����ö��
 1.��    ��   : 2013��7��19��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
enum TAF_MMA_PHONE_MODE_RESULT_ENUM
{
    TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC,

    TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL,

    TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_SUCC,

    TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL,

    TAF_MMA_PHONE_MODE_RESULT_BUTT,

};
typedef VOS_UINT8 TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8;

enum TAF_MMA_IMS_SWITCH_RESULT_ENUM
{
    TAF_MMA_IMS_SWITCH_RESULT_ON_SUCC,

    TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL,

    TAF_MMA_IMS_SWITCH_RESULT_OFF_SUCC,

    TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL,

    TAF_MMA_IMS_SWITCH_RESULT_BUTT
};
typedef VOS_UINT8 TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_MMA_SYS_CFG_RSLT_ENUM
 �ṹ˵��  : SYS CFG״̬���˳����ö��
 1.��    ��   : 2015��5��5��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum TAF_MMA_SYS_CFG_RSLT_ENUM
{
    TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC,        /* SYS CFG��������ɹ� */

    TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL,        /* SYS CFG��������ʧ�� */

    TAF_MMA_SYS_CFG_RSLT_ATTACH_SUCCESS,      /* ATTACH������������ɹ� */

    TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL,         /* ATTACH�����������ʧ�� */

    TAF_MMA_SYS_CFG_RSLT_DETACH_SUCCESS,      /* DETACH������������ɹ� */

    TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL,         /* DETACH�����������ʧ�� */

    TAF_MMA_SYS_CFG_RSLT_BUTT,
};
typedef VOS_UINT8 TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8;

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
 �ṹ����: TAF_MMA_INTER_POWER_INIT_REQ_STRU
 �ṹ˵��: MMA->MMA,�ڲ��ϵ�������Ϣ�Ľṹ
 1.��    ��   : 2013��7��19��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_INTER_POWER_INIT_REQ_STRU;


/*****************************************************************************
 �ṹ����: TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU
 �ṹ˵��: MMA->MMA,�ڲ���״̬�ı�ָʾ
 1.��    ��   : 2013��7��19��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ����: TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU
 �ṹ˵��: MMA->MMA,����������״̬�ı�ָʾ
 1.��    ��   : 2013��10��15��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;            /* _H2ASN_Skip */
}TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ����: TAF_MMA_PHONE_MODE_RSLT_IND_STRU
 �ṹ˵��: MMA->MMA,�ڲ�PHONE MODE�����Ϣָʾ
 1.��    ��   : 2013��7��19��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt;
    VOS_UINT8                                               aucRsv[3];
}TAF_MMA_PHONE_MODE_RSLT_IND_STRU;

/*****************************************************************************
 �ṹ����: TAF_MMA_IMS_SWITCH_RSLT_IND_STRU
 �ṹ˵��: MMA->MMA,�ڲ�IMS_SWITCH�����Ϣָʾ
 1.��    ��   : 2015-02-04
   ��    ��   : n00269697
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt;
    VOS_UINT8                                               aucRsv[3];
}TAF_MMA_IMS_SWITCH_RSLT_IND_STRU;

/*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_SYS_CFG_PARA_STRU                               stSysCfgPara;
}TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU;


/*****************************************************************************
 �ṹ����: TAF_MMA_INTER_ABORT_IND_STRU
 �ṹ˵��: MMA->MMA, ��ֹ��ǰ״̬��ָʾ
 1.��    ��   : 2015��4��9��
   ��    ��   : y00245242
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[4];
}TAF_MMA_INTER_ABORT_IND_STRU;

/*****************************************************************************
 �ṹ����: TAF_MMA_SYS_CFG_RSLT_STRU
 �ṹ˵��: MMA->MMA,�ڲ�SYS CFG RSLT�����Ϣָʾ
 1.��    ��   : 2015��5��5��
   ��    ��   : y00245242
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32                     enMsgId;            /* _H2ASN_Skip */
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt;
    VOS_UINT8                                               ucIsNeedChkLock;
    VOS_UINT8                                               aucRsv[2];
}TAF_MMA_SYS_CFG_RSLT_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32 enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_INTERNAL_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_SND_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_SND_INTERNAL_MSG_DATA       stMsgData;
}TafMmaSndInternalMsg_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
TAF_MMA_INTERNAL_MSG_BUF_STRU* TAF_MMA_GetNextInternalMsg( VOS_VOID );

TAF_MMA_INTERNAL_MSG_BUF_STRU *TAF_MMA_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MMA_SndInternalMsg(
    VOS_VOID                           *pSndMsg
);


VOS_VOID TAF_MMA_SndPhoneModeRsltInd(
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt
);

VOS_VOID TAF_MMA_SndSysCfgRsltInd(
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt,
    VOS_UINT8                                               ucIsNeedChkLock
);

VOS_VOID TAF_MMA_SndInterUsimChangeInd(VOS_VOID);

VOS_VOID TAF_MMA_SndInterPowerInitReq(VOS_VOID);

VOS_VOID TAF_MMA_SndSimlocakStatusChangeInd(VOS_VOID);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_MMA_SndImsSwitchRsltInd(
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt
);
#endif

VOS_VOID TAF_MMA_SndInterSysCfgSetReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
);

VOS_VOID TAF_MMA_SndInterMmaAbortInd(VOS_VOID);

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

#endif



