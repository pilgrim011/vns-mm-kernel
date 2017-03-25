/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : GmmMmInterface.h
  �� �� ��   : ����
  ��    ��   : huwen /44270
  ��������   : 2011��07��01��
  ����޸�   :
  ��������   : GMM��MM��ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��01��
    ��    ��   : huwen /40661
    �޸�����   : �����ļ�
  2.��    ��   : 2012��01��12��
    ��    ��   : w00176964
    �޸�����   : ASN����ͳһ����ͷ�ļ�

******************************************************************************/
#ifndef _GMM_MM_INTERFACE_H_
#define _GMM_MM_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "TafTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* GMM���͸�MM����Ϣԭ�� */
/* MNCC Primitives defination */
/*****************************************************************************
 ö����    : GMM_MM_MSG_TYPE_ENUM
 ö��˵��  : GMM��MM�໥�����Ϣԭ�ﶨ��
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
   
 2.��    ��   : 2011��8��17��                 
   ��    ��   : w00167002                    
   �޸�����   : V7R1 PHASEII �ع�: ��ö�ٸ�ֵ��ʼ��������SDT��ӡ��ʾ
 3.��    ��   : 2012��1��12��
   ��    ��   : w00176964
   �޸�����   : ASN����ͳһ����ͷ�ļ�
 4.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
enum GMM_MM_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/  /* ��ע */
/* GMM����MM��ԭ�� */
    GMMMM_LU_INITIATION                         = 0x1000,    /* _H2ASN_MsgChoice GMMMM_LU_INITIATION_STRU */

    GMMMM_COMBINED_ATTACH_INITIATION            = 0x1001,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_INITIATION_STRU */
    GMMMM_COMBINED_ATTACH_ACCEPTED              = 0x1002,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_ACCEPTED_STRU */
    GMMMM_COMBINED_ATTACH_REJECTED              = 0x1003,    /* _H2ASN_MsgChoice GMMMM_COMBINED_ATTACH_REJECTED_STRU */
    GMMMM_IMSI_DETACH_INITIATION                = 0x1004,    /* _H2ASN_MsgChoice GMMMM_IMSI_DETACH_INITIATION_STRU */
    GMMMM_IMSI_DETACH_COMPLETED                 = 0x1005,    /* _H2ASN_MsgChoice GMMMM_IMSI_DETACH_COMPLETED_STRU */
    GMMMM_GPRS_DETACH_INITIATION                = 0x1006,    /* _H2ASN_MsgChoice GMMMM_GPRS_DETACH_INITIATION_STRU */
    GMMMM_GPRS_DETACH_COMPLETED                 = 0x1007,    /* _H2ASN_MsgChoice GMMMM_GPRS_DETACH_COMPLETED_STRU */
    GMMMM_NETWORK_DETACH_IND                    = 0x1008,    /* _H2ASN_MsgChoice GMMMM_NETWORK_DETACH_IND_STRU */
    GMMMM_GMM_ACTION_RESULT_IND                 = 0x1009,    /* _H2ASN_MsgChoice GMMMM_GMM_ACTION_RESULT_IND_STRU */
    GMMMM_COMBINED_RAU_INITIATION               = 0x100a,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_INITIATION_STRU */
    GMMMM_COMBINED_RAU_ACCEPTED                 = 0x100b,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_ACCEPTED_STRU */
    GMMMM_COMBINED_RAU_REJECTED                 = 0x100c,    /* _H2ASN_MsgChoice GMMMM_COMBINED_RAU_REJECTED_STRU */
    GMMMM_AUTHENTICATON_FAILURE_IND             = 0x100d,    /* _H2ASN_MsgChoice GMMMM_AUTHENTICATON_FAILURE_IND_STRU */

    /* MM->GMM */
    MMGMM_LU_RESULT_IND                         = 0x2000,    /* _H2ASN_MsgChoice MMGMM_LU_RESULT_IND_STRU */
    MMGMM_AUTHENTICATON_FAILURE_IND             = 0x2001,    /* _H2ASN_MsgChoice MMGMM_AUTHENTICATON_FAILURE_IND_STRU */
    MMGMM_CS_CONNECT_IND                        = 0x2002,    /* _H2ASN_MsgChoice MMGMM_CS_CONNECT_IND_STRU */
    MMGMM_CM_SERVICE_REJECT_IND                 = 0x2003,    /* _H2ASN_MsgChoice MMGMM_CM_SERVICE_REJECT_IND_STRU */
    MMGMM_REGISTER_INITIATION                   = 0x2004,    /* _H2ASN_MsgChoice MMGMM_REGISTER_INITIATION_STRU */

    MMGMM_CS_LOCAL_DETACH_IND                   = 0x2005,    /* _H2ASN_MsgChoice MMGMM_CS_LOCAL_DETACH_IND_STRU */

    MMGMM_T3211_TIMER_EXPIRED_NOTIFY            = 0x2006,    /* _H2ASN_MsgChoice MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU */

    GMMMM_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16  GMM_MM_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : GMMMM_TIMER_FLG_ENUM
 ö��˵��  : GMM��ʱ����ʱ������
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_TIMER_FLG_ENUM
{
    GMMMM_NO_TIMER_EXPIRED,                                                     /* �޶�ʱ����ʱ */
    GMMMM_T3312_EXPIRED,                                                        /* T3312��ʱ */
    GMMMM_T3311_EXPIRED,                                                        /* T3311��ʱ */
    GMMMM_T3302_EXPIRED,                                                        /* T3302��ʱ */
    GMMMM_T3330_EXPIRED,                                                        /* T3330��ʱ */
    GMMMM_T3412OrT3423_EXPIRED,                                                 /* L��T3412��T3423��ʱ����ʱ */
    GMMMM_TIMER_FLG_BUTT
};
typedef VOS_UINT32  GMMMM_TIMER_FLG_ENUM_UINT32;


/*****************************************************************************
 ö����    : GMMMM_ATTACH_RESLUT_ENUM
 ö��˵��  : GMM�ֻ��෢��ATTACH�Ľ������
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_ATTACH_RESLUT_ENUM
{
    GMMMM_ATTACH_RESLUT_PS_ONLY,                                                /* ֻ��PS��ATTACH�ɹ� */
    GMMMM_ATTACH_RESLUT_COMBINED,                                               /* ֻ��COMBINED ATTACH�ɹ� */
    GMMMM_ATTACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_ATTACH_RESLUT_ENUM_UINT32;

/*****************************************************************************
 ö����    : GMMMM_DETACH_RESLUT_ENUM
 ö��˵��  : GMM�ֻ��෢��DETACH����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_DETACH_TYPE_ENUM
{
    GMMMM_COMBINED_DETACH_NORMAL,                                               /* ֻ��COMBINED ATTACH�ɹ� */
    GMMMM_GPRS_DETACH_NORMAL,                                                   /* ֻ��PS��DETACH�ɹ� */
    GMMMM_DETACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : GMMMM_NET_DETACH_RESLUT_ENUM
 ö��˵��  : ����෢��DETACH�Ľ������
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_NET_DETACH_TYPE_ENUM
{
    GMMMM_NET_DETACH_IMSI,                                                      /* ���緢��IMSI DETACH */
    GMMMM_NET_DETACH_NOATTACH,                                                  /* ���緢�� DETACH��MS����ATTACH */
    GMMMM_NET_DETACH_REATTACH,                                                  /* ���緢�� DETACH��MS��ATTACH */
    GMMMM_NET_DETACH_RESLUT_BUTT
};
typedef VOS_UINT32  GMMMM_NET_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : GMMMM_ACTION_TYPE_ENUM
 ö��˵��  : GMM��ACTION����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_ACTION_TYPE_ENUM
{
    GMMMM_ACTION_RAU,                                                           /* ��ǰ����RAU */
    GMMMM_ACTION_ATTACH,                                                        /* ��ǰ����ATTACH */
    GMMMM_ACTION_SR,                                                            /* ��ǰ����SERVICE REQUEST */
    GMMMM_ACTION_TYPE_BUTT
};
typedef VOS_UINT32  GMMMM_ACTION_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : GMMMM_ACTION_TYPE_ENUM
 ö��˵��  : GMM��ACTION���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_ACTION_RESULT_ENUM
{
    GMMMM_ACTION_SUCCESS,
    GMMMM_ACTION_FAILURE,
    GMMMM_ACTION_RESULT_BUTT
};
typedef VOS_UINT32  GMMMM_ACTION_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : GMMMM_REAL_FLAG_ENUM
 ö��˵��  : ��������Ƿ�Ϊ��ʵ��Ϣ
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_REAL_FLAG_ENUM
{
    GMMMM_REAL_PROCEDURE,                                                       /* ��ʾ����Ϣ,MM��Ҫ����TMSI */
    GMMMM_UNREAL_PROCEDURE,                                                     /* ��ʾ����Ϣ,MM���ܸ���TMSI */
    GMMMM_PROCEDURE_BUTT
};
typedef VOS_UINT32 GMMMM_REAL_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : GMMMM_RAU_RESULT_ENUM
 ö��˵��  : GMM RAU�Ľ��
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_RAU_RESULT_ENUM
{
    GMMMM_RAU_RESULT_PS_ONLY,                                                   /* ֻ��PS��RAU�ɹ� */
    GMMMM_RAU_RESULT_COMBINED,                                                  /* Combined RAU�ɹ� */
    GMMMM_RAU_RESULT_BUTT
};
typedef VOS_UINT32 GMMMM_RAU_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : GMMMM_MS_ID_TYPE_ENUM
 ö��˵��  : MS ID������
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum GMMMM_MS_ID_TYPE_ENUM
{
    GMMMM_MS_ID_TYPE_NULL,
    GMMMM_MS_ID_TYPE_IMSI,                                                      /* IMSI */
    GMMMM_MS_ID_TYPE_TMSI,                                                      /* TMSI */
    GMMMM_MS_ID_TYPE_BUTT
};
typedef VOS_UINT32 GMMMM_MS_ID_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : MMGMM_LU_RESULT_ENUM
 ö��˵��  : MM LU���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum MMGMM_LU_RESULT_ENUM
{
    MMGMM_LU_SUCCESS,                                                           /* LU SUCCESS */
    MMGMM_LU_FAILURE,                                                           /* LU FAILURE */
    MMGMM_LU_RESULT_BUTT
};
typedef VOS_UINT32 MMGMM_LU_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMGMM_CS_CONNECT_STATUS_ENUM
 ö��˵��  : MM LU���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
enum MMGMM_CS_CONNECT_STATUS_ENUM
{
    MMGMM_CS_CONNECT_NOT_EXIST,                                                 /* û��CS��ҵ�� */
    MMGMM_CS_CONNECT_ESTING,                                                    /* ��CS��ҵ�� */
    MMGMM_CS_CONNECT_EXIST,                                                     /* ��CS��ҵ�� */
    MMGMM_CS_CONNECT_BUTT
};
typedef VOS_UINT32 MMGMM_CS_CONNECT_STATUS_ENUM_UINT32;

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
 �ṹ��    : GMMMM_LU_INITIATION_STRU
 �ṹ˵��  : GMM֪ͨMM LU����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    GMMMM_TIMER_FLG_ENUM_UINT32         enTimerExpiredFlg;                      /* timer��ʱ��� */
}GMMMM_LU_INITIATION_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_ATTACH_INITIATION_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED ATTACH��ʼ
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
}GMMMM_COMBINED_ATTACH_INITIATION_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_MS_IDENTITY_STRU
 �ṹ˵��  : MS ID�Ľṹ������
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    GMMMM_MS_ID_TYPE_ENUM_UINT32        enMsIdType;                             /* Ms���� */
    VOS_UINT8                           aucTmsi[4];                             /* TMSI */
}GMMMM_MS_IDENTITY_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_ATTACH_ACCEPTED_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED ATTACH ACCEPT
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
 2.��    ��   : 2012��8��21��
   ��    ��   : l00171473
   �޸�����   : DTS2012081705828, 4�ֽڶ���
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/

    GMMMM_ATTACH_RESLUT_ENUM_UINT32     enAttachResult;                         /* ע���� */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ע��ʧ��ԭ�� */
    VOS_UINT8                           aucReserve[2];
    GMMMM_MS_IDENTITY_STRU              stMsIdentity;                           /* MS ID */
    VOS_UINT32                          ulAttachAttCounter;                     /* Attach attempt counter */
}GMMMM_COMBINED_ATTACH_ACCEPTED_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_ATTACH_REJECTED_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED ATTACH REJECTED
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ע��ʧ��ԭ�� */
    VOS_UINT8                           aucReserve[2];                          /* ����λ */
    VOS_UINT32                          ulAttachAttCounter;                     /* Attach attempt counter */
}GMMMM_COMBINED_ATTACH_REJECTED_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_IMSI_DETACH_INITIATION_STRU
 �ṹ˵��  : GMM֪ͨMM ����IMSI DETACH
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* ����*/
}GMMMM_IMSI_DETACH_INITIATION_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_IMSI_DETACH_COMPLETED_STRU
 �ṹ˵��  : GMM֪ͨMM IMSI DETACH���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* ����*/
}GMMMM_IMSI_DETACH_COMPLETED_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_GPRS_DETACH_INITIATION_STRU
 �ṹ˵��  : GMM֪ͨMM GPRS DETACH����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    GMMMM_DETACH_TYPE_ENUM_UINT32       enDetachType;                           /* DETACH������ */
}GMMMM_GPRS_DETACH_INITIATION_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_GPRS_DETACH_COMPLETED_STRU
 �ṹ˵��  : GMM֪ͨMM GPRS DETACH���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* ����*/
}GMMMM_GPRS_DETACH_COMPLETED_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_NETWORK_DETACH_IND_STRU
 �ṹ˵��  : GMM֪ͨMM ���緢��DETACH
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    GMMMM_NET_DETACH_TYPE_ENUM_UINT32   enDetachType;                           /* Detach���� */
    VOS_UINT32                          ulDetachCause;                          /* Detachԭ�� */
}GMMMM_NETWORK_DETACH_IND_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_GMM_ACTION_RESULT_IND_STRU
 �ṹ˵��  : GMM֪ͨMM ACTION RESULT
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    GMMMM_ACTION_TYPE_ENUM_UINT32       enGmmActionType;                        /* GMM���в��������� */
    GMMMM_ACTION_RESULT_ENUM_UINT32     enActionResult;                         /* ������� */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ����ʧ��ԭ�� */
    VOS_UINT8                           ucAttCounter;                           /* attempt counter */    
    VOS_UINT8                           aucReserve[1];                          /* ����λ */    
}GMMMM_GMM_ACTION_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_RAU_INITIATION_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED RAU����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                             /* ����*/
}GMMMM_COMBINED_RAU_INITIATION_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_RAU_ACCEPTED_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED RAU���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /* ��Ϣͷ */ /*_H2ASN_Skip*/
    GMMMM_RAU_RESULT_ENUM_UINT32        enRauResult;                            /* ���½�� */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ����ʧ��ԭ�� */
    VOS_UINT8                           aucReserve[2];                          /* ����λ */
    GMMMM_MS_IDENTITY_STRU              stMsIdentity;                           /* MS identity */
    VOS_UINT32                          ulRauAttCounter;                        /* RAU attempt counter */
    GMMMM_REAL_FLAG_ENUM_UINT32         enRealProFlg;                           /* ������̱�ʶ */
}GMMMM_COMBINED_RAU_ACCEPTED_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_COMBINED_RAU_ACCEPTED_STRU
 �ṹ˵��  : GMM֪ͨMM COMBINED RAU����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ����ʧ��ԭ�� */
    VOS_UINT8                           aucReserve[2];                          /* ����λ */
    VOS_UINT32                          ulRauAttCounter;                        /* RAU attempt counter */
    GMMMM_REAL_FLAG_ENUM_UINT32         enRealProFlg;                           /* �Ƿ������������̱�־ */
}GMMMM_COMBINED_RAU_REJECTED_STRU;


/*****************************************************************************
 �ṹ��    : GMMMM_AUTHENTICATON_FAILURE_IND_STRU
 �ṹ˵��  : GMM֪ͨMM��Ȩ����
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
     MSG_HEADER_STRU                    stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
     VOS_UINT32                         ulReserved;                     /* ����*/
}GMMMM_AUTHENTICATON_FAILURE_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMGMM_LU_RESULT_IND_STRU
 �ṹ˵��  : MM֪ͨGMM LU���
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/

    MMGMM_LU_RESULT_ENUM_UINT32         enLuResult;                             /* LU��� */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ����ʧ��ԭ�� */
    VOS_UINT8                           aucReserve[2];                          /* ����λ */
}MMGMM_LU_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMGMM_AUTHENTICATON_FAILURE_IND_STRU
 �ṹ˵��  : MM֪ͨGMM ��Ȩʧ��
 1.��    ��   : 2011��7��11��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserved;                     /* ����*/
}MMGMM_AUTHENTICATON_FAILURE_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMGMM_CS_CONNECT_IND_STRU
 �ṹ˵��  : MM֪ͨGMM ��ǰCS����״̬
 1.��    ��   : 2011��7��16��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MMGMM_CS_CONNECT_STATUS_ENUM_UINT32 enCsConnectStatus;                      /* CS���������ޱ�־  */
}MMGMM_CS_CONNECT_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMGMM_CM_SERVICE_REJECT_IND_STRU
 �ṹ˵��  : MM֪ͨGMM ��ǰCS��ҵ�񱻾ܾ�
 1.��    ��   : 2011��7��16��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;                                /* ʧ��ԭ�� */
}MMGMM_CM_SERVICE_REJECT_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMGMM_REGISTER_INITIATION_STRU
 �ṹ˵��  : MM֪ͨGMM ��ǰCS����ע��
 1.��    ��   : 2011��8��10��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMGMM_REGISTER_INITIATION_STRU;

/*****************************************************************************
 �ṹ��    : MMGMM_CS_LOCAL_DETACH_IND_STRU
 �ṹ˵��  : MM֪ͨGMM ��ǰCS�򱾵�ȥע����
 1.��    ��   : 2013��6��12��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         stMsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMGMM_CS_LOCAL_DETACH_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU
 �ṹ˵��  : MM֪ͨGMM T3211��ʱ����ʱ
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
typedef struct
{

    MSG_HEADER_STRU         stMsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT8               ucRejectCause;                      /* ��¼����T3211ʱmm lau���ܵ�ԭ��ֵ */
    VOS_UINT8               aucReserved[3];                     /* ����*/
} MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU;


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
    GMM_MM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export GMM_MM_MSG_TYPE_ENUM_UINT16*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��GMM_MM_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          GMM_MM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}GMM_MM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    GMM_MM_MSG_DATA                    stMsgData;
}GmmMmInterface_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of GmmMmInterface.h */

