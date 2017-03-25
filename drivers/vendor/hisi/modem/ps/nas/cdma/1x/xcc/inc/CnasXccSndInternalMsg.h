/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndInternalMsg.h
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��6��
  ����޸�   :
  ��������   : CnasXccSndInternalMsg.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��6��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XCC_SND_INTERNAL_MSG_H__
#define __CNAS_XCC_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CnasXccCtx.h"
#include "CnasCcb.h"

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
 ö����    : CNAS_XCC_INTERNAL_MSG_TYPE_ENUM
 ö��˵��  : �ڲ���Ϣ��ö�ٶ���
 1.��    ��   : 2014��9��7��
   ��    ��   : w00242748
   �޸�����   : �½�

 2.��    ��   : 2015��1��3��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_XCC_XCC_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_XCC_XCC_ABORT_REQ_STRU */
    ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF      = 0x0001, /* _H2ASN_MsgChoice CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU */
    ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF      = 0x0002, /* _H2ASN_MsgChoice CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU */
    ID_CNAS_XCC_XCC_POWER_DOWN_IND           = 0x0003, /* _H2ASN_MsgChoice CNAS_XCC_XCC_POWER_DOWN_IND_STRU */
    ID_CNAS_XCC_XCC_NDSS_REDIAL_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU */
    ID_CNAS_XCC_XCC_CALL_STATE_IND,                    /* _H2ASN_MsgChoice CNAS_XCC_XCC_CALL_STATE_IND_STRU */

#ifdef DMT
    ID_CNAS_XCC_XCC_TEST_CONFIG_IND,                   /* _H2ASN_MsgChoice CNAS_XCC_XCC_TEST_CONFIG_IND_STRU */
#endif

    ID_CNAS_XCC_XCC_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : CNAS_XCC_MT_CALLING_RESULT_ENUM
 ö��˵��  : MT CALLING״̬����״̬�����ö��ֵ
 1.��    ��   : 2014��9��6��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_MT_CALLING_RESULT_ENUM
{
    CNAS_XCC_MT_CALLING_RESULT_SUCCESS          = 0x00000000,                   /* ˵���绰��ͨ */
    CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED  = 0x00000001,                   /* ˵���绰�Ѿ����� */
    CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING = 0x00000002,                   /* ˵���绰�ڹҶϵĹ����� */
    CNAS_XCC_MT_CALLING_RESULT_BUTT             = 0x00000003
};
typedef VOS_UINT32 CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XCC_MO_CALLING_RESULT_ENUM
 ö��˵��  : MT CALLING״̬����״̬�����ö��ֵ
 1.��    ��   : 2014��9��6��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_MO_CALLING_RESULT_ENUM
{
    CNAS_XCC_MO_CALLING_RESULT_SUCCESS          = 0x00000000,                   /* ˵���绰��ͨ */
    CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED  = 0x00000001,                   /* ˵���绰�Ѿ����� */
    CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING = 0x00000002,                   /* ˵���绰�ڹҶϵĹ����� */
    CNAS_XCC_MO_CALLING_RESULT_BUTT             = 0x00000003
};
typedef VOS_UINT32 CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XCC_MO_CALLING_END_REASON_ENUM
 ö��˵��  : MO CALLING״̬����״̬��������ԭ��
 1.��    ��   : 2014��9��19��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_MO_CALLING_END_REASON_ENUM
{
    CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END      = 0x00000000,                /* ˵���绰��ͨ */
    CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END  = 0x00000001,                /* ˵���绰�Ѿ����� */
    CNAS_XCC_MO_CALLING_END_REASON_BUTT            = 0x00000002
};
typedef VOS_UINT8 CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_XCC_MT_CALLING_END_REASON_ENUM
 ö��˵��  : MT CALLING״̬����״̬��������ԭ��
 1.��    ��   : 2014��9��19��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_MT_CALLING_END_REASON_ENUM
{
    CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END      = 0x00000000,                /* ˵���绰�����Ҷ� */
    CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END  = 0x00000001,                /* ˵���ػ����µĵ绰���� */
    CNAS_XCC_MT_CALLING_END_REASON_BUTT            = 0x00000002
};
typedef VOS_UINT8 CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8;

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
 �ṹ��    : CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU
 �ṹ˵��  : XCC MO CALLING��״̬������ṹ
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt;
    VOS_UINT8                                               ucConnectId;
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason;
    VOS_UINT8                                               aucReserved[2];
}CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU
 �ṹ˵��  : XCC MT CALLING��״̬������ṹ
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt;
    VOS_UINT8                                               ucConnectId;
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason;
    VOS_UINT8                                               aucReserved[2];
}CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_ABORT_REQ_STRU
 �ṹ˵��  : XCC������ֹ״̬����Ϣ�Ľṹ
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;

    VOS_UINT32                                              ulEventType; /* ������ABORT��Ϣ���¼����� */
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
    TAF_XCC_CAUSE_ENUM_UINT32                               enAbortCause;
}CNAS_XCC_XCC_ABORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_POWER_DOWN_IND_STRU
 �ṹ˵��  : �ڲ��ػ�ָʾ
 1.��    ��   : 2014��9��11��
   ��    ��   : y00245242
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_POWER_DOWN_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU
 �ṹ˵��  : �ڲ�NDSS�ز�ָʾ
 1.��    ��   : 2015��1��3��
   ��    ��   : y00245242
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU;

#ifdef DMT
/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_TEST_CONFIG_IND_STRU
 �ṹ˵��  : XCC����������Ϣ
 1.��    ��   : 2014��9��28��
   ��    ��   : y00245242
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucDisableApsSupsRsp; /* �Ƿ���Ҫdisable APS suspend RSP���� */
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_XCC_TEST_CONFIG_IND_STRU;
#endif
/*****************************************************************************
 �ṹ��    : CNAS_XCC_XCC_CALL_STATE_IND_STRU
 �ṹ˵��  : XCC  call state �����ϱ�
 1.��    ��   : 2015��7��21��
   ��    ��   : y00322978
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       enCallState;
    VOS_UINT8                                               aucRslv[3];
}CNAS_XCC_XCC_CALL_STATE_IND_STRU;
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
    CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XCC_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_XCC_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_XCC_INTERNAL_MSG_DATA          stMsgData;
}CNAS_XCC_INTERNAL_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_XCC_SndMoCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason
);

VOS_VOID CNAS_XCC_SndMtCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason
);

VOS_VOID CNAS_XCC_SndXccAbortReq(
    VOS_UINT8                           ucConnId,
    VOS_UINT32                          ulEventType,
    TAF_XCC_CAUSE_ENUM_UINT32           enAbortCause
);

VOS_VOID CNAS_XCC_SndXccPowerDownInd(
    VOS_UINT8                           ucConnId
);

VOS_VOID CNAS_XCC_SndXccNdssRedialInd(
    VOS_UINT8                           ucConnId
);

VOS_VOID CNAS_XCC_SndXcc1xCallStateUpdateInd(
    VOS_VOID
);

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

#endif /* end of CnasXsdSndInternalMsg.h */
