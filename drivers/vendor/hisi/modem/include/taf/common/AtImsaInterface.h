

#ifndef  AT_IMSA_INTERFACE_H
#define  AT_IMSA_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"

#include "TafApsApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#define AT_IMSA_IMPU_MAX_LENGTH     (128)

/* equals IMSA_MAX_CALL_NUMBER_LENGTH */
#define AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH     (40)
/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : AT_IMSA_MSG_TYPE_ENUM
�ṹ˵��  : AT ��IMSA��֮�����Ϣ

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����AT��IMSA֮��Ľӿ���Ϣ
*****************************************************************************/
enum AT_IMSA_MSG_TYPE_ENUM
{
    /* AT->IMSA */
    ID_AT_IMSA_CIREG_SET_REQ                = 0x0001,                           /* _H2ASN_MsgChoice AT_IMSA_CIREG_SET_REQ_STRU */
    ID_AT_IMSA_CIREG_QRY_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREG_QRY_REQ_STRU */
    ID_AT_IMSA_CIREP_SET_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREP_SET_REQ_STRU */
    ID_AT_IMSA_CIREP_QRY_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREP_QRY_REQ_STRU */
    ID_AT_IMSA_VOLTEIMPU_QRY_REQ,                                               /* _H2ASN_MsgChoice AT_IMSA_VOLTEIMPU_QRY_REQ_STRU */




    /* IMSA->AT */
    ID_IMSA_AT_CIREG_SET_CNF                = 0x1001,                           /* _H2ASN_MsgChoice IMSA_AT_CIREG_SET_CNF_STRU */
    ID_IMSA_AT_CIREG_QRY_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREG_QRY_CNF_STRU */
    ID_IMSA_AT_CIREP_SET_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREP_SET_CNF_STRU */
    ID_IMSA_AT_CIREP_QRY_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREP_QRY_CNF_STRU */

    ID_IMSA_AT_VOLTEIMPU_QRY_CNF,                                               /* _H2ASN_MsgChoice IMSA_AT_VOLTEIMPU_QRY_CNF_STRU */




    ID_IMSA_AT_CIREGU_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREGU_IND_STRU */
    ID_IMSA_AT_CIREPH_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREPH_IND_STRU */
    ID_IMSA_AT_CIREPI_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREPI_IND_STRU */

    ID_IMSA_AT_VT_PDP_ACTIVATE_IND,                                             /* _H2ASN_MsgChoice IMSA_AT_VT_PDP_ACTIVATE_IND_STRU */
    ID_IMSA_AT_VT_PDP_DEACTIVATE_IND,                                           /* _H2ASN_MsgChoice IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU */

    ID_IMSA_AT_MT_STATES_IND,                                                   /* _H2ASN_MsgChoice IMSA_AT_MT_STATES_IND_STRU */

    ID_AT_IMSA_MSG_BUTT
};
typedef  VOS_UINT32  AT_IMSA_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
ö����    : AT_IMSA_IMS_REG_STATE_REPORT_ENUM
�ṹ˵��  : IMSע��״̬�ϱ�����

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_IMSA_IMS_REG_STATE_REPORT_ENUM
{
    AT_IMSA_IMS_REG_STATE_DISABLE_REPORT        = 0,
    AT_IMSA_IMS_REG_STATE_ENABLE_REPORT,
    AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT,

    AT_IMSA_IMS_REG_STATE_REPROT_BUTT
};
typedef  VOS_UINT32  AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32;

/*****************************************************************************
ö����    : AT_IMSA_CCWAI_MODE_ENUM
�ṹ˵��  : �����Ƿ�֧��IMSVOPS

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_IMSA_CCWAI_MODE_ENUM
{
    AT_IMSA_CCWAI_MODE_DISABLE               = 0,
    AT_IMSA_CCWAI_MODE_ENABLE,

    AT_IMSA_CCWAI_MODE_BUTT
};
typedef  VOS_UINT8 AT_IMSA_CCWAI_MODE_ENUM_UINT8;


/*****************************************************************************
ö����    : AT_IMSA_IMSVOPS_CAPABILITY_ENUM
�ṹ˵��  : �����Ƿ�֧��IMSVOPS

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_IMSA_IMSVOPS_CAPABILITY_ENUM
{
    AT_IMSA_NW_NOT_SUPORT_IMSVOPS               = 0,
    AT_IMSA_NW_SUPORT_IMSVOPS,

    AT_IMSA_IMSVOPS_CAPABILITY_BUTT
};
typedef  VOS_UINT32  AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32;


/*****************************************************************************
ö����    : AT_IMSA_CIREP_REPORT_ENUM
�ṹ˵��  : �Ƿ�����CIREPH��CIREPI�����ϱ�

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_IMSA_CIREP_REPORT_ENUM
{
    AT_IMSA_CIREP_REPORT_DISENABLE      = 0,
    AT_IMSA_CIREP_REPORT_ENABLE,

    AT_IMSA_CIREP_REPORT_BUTT
};
typedef  VOS_UINT32  AT_IMSA_CIREP_REPORT_ENUM_UINT32;


/*****************************************************************************
ö����    : AT_IMSA_SRVCC_HANDVOER_ENUM
�ṹ˵��  : SRVCC����״̬

  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : ����ö��
*****************************************************************************/
enum AT_IMSA_SRVCC_HANDVOER_ENUM
{
    AT_IMSA_SRVCC_HANDOVER_STARTED                = 0,
    AT_IMSA_SRVCC_HANDOVER_SUCCESS,
    AT_IMSA_SRVCC_HANDOVER_CANCEL,
    AT_IMSA_SRVCC_HANDOVER_FAILURE,

    AT_IMSA_SRVCC_HANDOVER_BUTT
};
typedef  VOS_UINT32  AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32;


/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/*****************************************************************************
�ṹ��    : AT_IMSA_MSG_STRU
�ṹ˵��  : ATģ����IMSAģ������Ϣ�ṹ

1.��    ��  : 2013��09��12��
  ��    ��  : Y00213812
  �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucContent[4];
} AT_IMSA_MSG_STRU;

/*****************************************************************************
�ṹ��    : AT_IMSA_CIREG_QRY_REQ_STRU
�ṹ˵��  : ID_AT_IMSA_CIREG_QRY_REQ����Ϣ�ṹ

1.��    ��  : 2013��09��12��
  ��    ��  : Y00213812
  �޸�����  : �����ṹ
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_CIREG_QRY_REQ_STRU;


/*****************************************************************************
�ṹ��    : AT_IMSA_CIREP_QRY_REQ_STRU
�ṹ˵��  : ID_AT_IMSA_CIREP_QRY_REQ����Ϣ�ṹ

1.��    ��  : 2013��09��12��
  ��    ��  : Y00213812
  �޸�����  : �����ṹ
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_CIREP_QRY_REQ_STRU;

/*****************************************************************************
�ṹ��    : AT_IMSA_VOLTEIMPU_QRY_REQ_STRU
�ṹ˵��  : ID_AT_IMSA_VOLTEIMPU_QRY_REQ����Ϣ�ṹ

1.��    ��  : 2013��12��05��
  ��    ��  : Y00213812
  �޸�����  : �����ṹ
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_VOLTEIMPU_QRY_REQ_STRU;


/*****************************************************************************
 �ṹ��  : AT_IMSA_CCWAI_SET_REQ_STRU
 �ṹ˵��: ^CCWAI IMS  ���еȴ�
 �޸���ʷ      :
  1.��    ��   : 2014��3��11��
    ��    ��   : w00209181
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    AT_IMSA_CCWAI_MODE_ENUM_UINT8       enMode;
    VOS_UINT32                          ulSrvClass;
} AT_IMSA_CCWAI_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��  : IMSA_AT_CCWAI_SET_CNF_STRU
 �ṹ˵��: ^CCWAI IMS  ���еȴ�
 �޸���ʷ      :
  1.��    ��   : 2014��3��11��
    ��    ��   : w00209181
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucReserved;
    VOS_UINT32                          ulResult;
} IMSA_AT_CCWAI_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��  : AT_IMSA_CIREG_SET_REQ_STRU
 �ṹ˵��: +CIREG IMSע��״̬�����ϱ���������

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32    enCireg;
} AT_IMSA_CIREG_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREG_SET_CNF_STRU
 �ṹ˵��: +CIREG IMSע��״̬�����ϱ�����

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;                               /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
} IMSA_AT_CIREG_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREG_QRY_CNF_STRU
 �ṹ˵��: +CIREG IMSע��״̬��ѯ���

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          bitOpExtInfo    : 1 ;                   /* +CIREG=2ʱ,��־λ��1 */
    VOS_UINT32                          bitOpSpare      : 31;

    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32    enCireg;
    VOS_UINT32                          ulRegInfo;
    VOS_UINT32                          ulExtInfo;                              /* +CIREG=2ʱ ����չ��Ϣ��ʱ�ظ�0 */
    VOS_UINT32                          ulResult;                               /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
} IMSA_AT_CIREG_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREGU_IND_STRU
 �ṹ˵��: ID_IMSA_AT_CIREGU_IND IMSע��״̬�����ϱ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* �����ϱ�ʱ��0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* ��0 */
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          bitOpExtInfo    : 1 ;
    VOS_UINT32                          bitOpSpare      : 31;

    VOS_UINT32                          ulRegInfo;
    VOS_UINT32                          ulExtInfo;
} IMSA_AT_CIREGU_IND_STRU;


/*****************************************************************************
 �ṹ��  : AT_IMSA_CIREP_SET_REQ_STRU
 �ṹ˵��: +CIREP SRVCC�л�״̬�����ϱ�����

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_CIREP_REPORT_ENUM_UINT32    enReport;
} AT_IMSA_CIREP_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREP_SET_CNF_STRU
 �ṹ˵��: +CIREP SRVCC�л�״̬�����ϱ�����

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;                               /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
} IMSA_AT_CIREP_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREP_QRY_CNF_STRU
 �ṹ˵��: +CIREP IMSVOPS������ѯ

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_CIREP_REPORT_ENUM_UINT32            enReport;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops;
    VOS_UINT32                          ulResult;                               /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
} IMSA_AT_CIREP_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��  : IMSA_AT_VOLTEIMPU_QRY_CNF_STRU
 �ṹ˵��: ^VOLTEIMPU IMPU��Ϣ��ѯ���

 �޸���ʷ      :
  1.��    ��   : 2013��12��05��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;              /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
    VOS_UINT32                          ulImpuLen;
    VOS_CHAR                            aucImpu[AT_IMSA_IMPU_MAX_LENGTH];
} IMSA_AT_VOLTEIMPU_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREPH_IND_STRU
 �ṹ˵��: +CIREPH SRVCC�л�״̬�����ϱ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��13��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* �����ϱ�ʱ��0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* ��0 */
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32  enHandover;
} IMSA_AT_CIREPH_IND_STRU;

/*****************************************************************************
 �ṹ��  : IMSA_AT_CIREPI_IND_STRU
 �ṹ˵��: +CIREPI IMSVOPS�����ϱ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : Y00213812
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* �����ϱ�ʱ��0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* ��0 */
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops;
} IMSA_AT_CIREPI_IND_STRU;


/*****************************************************************************
 �ṹ����: IMSA_AT_VT_PDP_ACTIVATE_IND_STRU
 �ṹ˵��: IMSA�ϱ�VT���ؼ���ɹ�����Ľṹ

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_DNS_STRU                    stIpv4Dns;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
} IMSA_AT_VT_PDP_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ����: IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU
 �ṹ˵��: IMSA�ϱ�VT����ȥ����ɹ�����Ľṹ

 �޸���ʷ      :
  1.��    ��   : 2014��07��31��
    ��    ��   : f00179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
} IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU;

/*****************************************************************************
 �ṹ���ƣ� IMSA_AT_MT_STATES_IND_STRU
 �ṹ˵��:  IMSA�ϱ�AT�յ������¼��Ľṹ

 �޸���ʷ:
 1.����: 2015��03��18��
   ����: m00277840
   �޸�����:�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCauseCode;
    VOS_UINT8                           ucMtStatus;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucAsciiCallNum[AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH];
} IMSA_AT_MT_STATES_IND_STRU;
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
  7 OTHERS����
*****************************************************************************/

/* ASN�����ṹ */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_IMSA_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_INTERFACE_MSG_DATA           stMsgData;
} AtImsaInterface_MSG;


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

#endif


