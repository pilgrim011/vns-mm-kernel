
/************************************************************************
 *                                                                      *
 *                             pppc_eap_def.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             WANGYONG                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP��EAPЭ��ģ��˽�к궨��                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������EAPЭ��ģ���ȫ��˽�к궨��                          *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _PPPC_EAP_DEF_H_
#define      _PPPC_EAP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/* Code + ID + length */
#define PPPC_EAP_HEADERLEN                                  (4)

/* TYPE�򳤶� */
#define PPPC_EAP_TYPE_FIELD_LEN                             (1)

/* ����EXPAND NAK RESPONSE����ʱtype-data��ÿ��Ԫ�صĳ���  */
#define PPPC_EAP_EXPAND_NAK_ELEM_LEN                        (8)

/* RESPONSE���ĵ���󳤶ȸ���Э��Ӧ��Head(4)+TYPE(1)+(TYPE-DATA)(253)=258�ֽ� */
#define PPPC_EAP_MAX_RESPONSE_LEN                           (512)

/*  EAP state */
#define EAP_STATE_INITIAL                     0
#define EAP_STATE_SEND_REQUEST_FOR_IDENTITY   1
#define EAP_STATE_SEND_REQUEST                2
#define EAP_STATE_SUCCESS                     3
#define EAP_STATE_FAILED                      4
#define EAP_STATE_WAITING_AAA                 5

#define PPP_GET_EAP_CODE(ucCode,pEapMsg) (ucCode = (*(VOS_UINT8 *)pEapMsg))
#define PPP_GET_EAP_ID(ucID,pEapMsg) (ucID = (*(VOS_UINT8 *)((VOS_UINT8 *)pEapMsg + EAP_ID_OFFSET)))
#define PPP_GET_EAP_LEN(usCiLen,pEapMsg) {usCiLen = (*(VOS_UINT16 *)((VOS_UINT8 *)pEapMsg + EAP_LEN_OFFSET)); usCiLen = VOS_NTOHS(usCiLen);}
#define PPP_GET_EAP_TYPE(ucType,pEapMsg) (ucType = (*((VOS_UINT8 *)pEapMsg + EAP_TYPE_OFFSET)))
#define PPP_GET_EAP_NAI(pucNAI,pEapMsg) (pucNAI = ((VOS_UINT8 *)pEapMsg + EAP_NAI_OFFSET))


/*  ���EAP���� */
#define EAP_PAYLOAD_MAX_LEN         2048
/*  ���ID���� */
#define PPPC_EAP_ID_MAX_LEN         260

#define EAP_CODE_OFFSET  0      /* codeƫ�� */
#define EAP_ID_DEFAULT  1      /* Identifier��Ĭ��ֵ */
#define EAP_ID_OFFSET   1       /* Identifier��EAP-Message�е�ƫ�� */
#define EAP_LEN_OFFSET  2      /* Length��EAP-Message�е�ƫ�� */
#define EAP_TYPE_OFFSET 4     /* TYPE��EAP-Message�е�ƫ�� */
#define EAP_NAI_OFFSET  5      /* NAI��EAP-Message�е�ƫ�� */

/* EAP-Message����С����,����EAP-Request/Response����,��С���Ȼ�Ҫ��1,
   ����EAP-Success/Failure����,�����4 */
#define EAP_MSG_MIN_LEN 4

/* EAP-Request/Response�е���Ϣ���� */
#define EAP_IDENTITY 1
#define EAP_RESPONSE 2


#define EAP_MAXAUTHTRANSMITS   1

/*EAP ����CORE���¼����� */
#define EAP_EVENT_CLIENTLOWERUP    0
#define EAP_EVENT_SERVERLOWERUP    1
#define EAP_EVENT_LOWERDOWN        2

/*EAP �ڲ����¼����� */
#define EAP_SERVERLOWERUP      0
#define EAP_CLIENTLOWERUP      1
#define EAP_LOWERDOWN          2
#define EAP_RECEIVERESPONSE    4
#define EAP_REQUESTTIMEOUT_FORID    7
#define EAP_REQUESTTIMEOUT     8
#define EAP_INITIALIZATION     9
#define EAP_CODEREJECT         11
#define EAP_ERROREVENT         14

/*״̬����*/
#define EAP_SERVER_STATE       1

/*�ȴ�������Ϣ��ʱ����ʱʱ��*/
#define PPPC_EAP_TIMEOUT_LENTH            (15000)

/*����eap���ƿ��е�respnse����*/
#define PPPC_EAP_UpdateLen(pucPktData, pusRespLen, usEapLen)    \
{   \
    VOS_UINT16 usTemp = VOS_HTONS(usEapLen);    \
    ((PPPC_EAP_HEADER_STRU *)pucPktData)->usEAPLen = usTemp;  \
    *pusRespLen = usEapLen;    \
}


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : PPPC_LOG_EVENT_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PPPC��eventId
*****************************************************************************/
enum PPPC_LOG_EVENT_ID_ENUM
{
    PPPC_LOG_EVENT_STATE_UPDATE         = 0,
    PPPC_LOG_EVENT_EAP_AKA_STATE_UPDATE = 1,

    PPPC_LOG_EVENT_BUTT
};
typedef VOS_UINT16  PPPC_LOG_EVENT_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : PPPC_EAP_PEER_EVENT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ����PEER״̬��Ǩ�Ƶ��¼�
*****************************************************************************/
enum PPPC_EAP_PEER_EVENT_ENUM
{
    PPPC_EAP_PEER_IDENTITY_REQ_EVENT    = 0,                                    /* �յ�IdentityReq��Ϣ���¼� */
    PPPC_EAP_PEER_NOTIFY_REQ_EVENT      = 1,                                    /* �յ�Notify��Ϣ���¼� */
    PPPC_EAP_PEER_NAK_EVENT             = 2,                                    /* �յ�NAK�¼� */
    PPPC_EAP_PEER_AUTH_REQ_EVENT        = 3,                                    /* �յ�AuthReq���ĵ��¼� */
    PPPC_EAP_PEER_AUTH_IND_EVENT        = 4,                                    /* �յ����˼�Ȩ�����ָʾ�¼� */
    PPPC_EAP_PEER_SUCCESS_EVENT         = 5,                                    /* �յ�Success���ĵ��¼� */
    PPPC_EAP_PEER_FAILURE_EVENT         = 6,                                    /* �յ�Failure���ĵ��¼� */
    PPPC_EAP_PEER_TIMEOUT_EVENT         = 7,                                    /* �յ���ʱ��Ϣ���¼� */

    PPPC_EAP_PEER_EVENT_BUTT
};
typedef VOS_UINT16  PPPC_EAP_PEER_EVENT_ENUM_UINT16;

/*****************************************************************************
 ö����    : PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PEER״̬��
*****************************************************************************/
enum PPPC_EAP_PEER_STATE_MACHINE_ENUM
{
    PPPC_EAP_PEER_IDLE_STATE            = 0,                                    /* IDLE */
    PPPC_EAP_PEER_AUTHENTICATING_STATE  = 1,                                    /* AUTHENTICATING */
    PPPC_EAP_PEER_NOTIFYING_STATE       = 2,                                    /* NOTIFYING */
    PPPC_EAP_PEER_CLOSING_STATE         = 3,                                    /* CLOSING */
    PPPC_EAP_PEER_CLOSED_STATE          = 4,                                    /* CLOSED */

    PPPC_EAP_PEER_STATE_BUTT
};
typedef VOS_UINT16  PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PPPC_EAP_METHODS_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : EAP��������
*****************************************************************************/
enum PPPC_EAP_METHODS_TYPE_ENUM
{
    PPPC_EAP_IDENTITY_TYPE              = 1,                                    /* Identity type */
    PPPC_EAP_NOTIFY_TYPE                = 2,                                    /* Notify type */
    PPPC_EAP_NAK_TYPE                   = 3,                                    /* Nak type */
    PPPC_EAP_MD5_TYPE                   = 4,                                    /* MD5 type */
    PPPC_EAP_AKA_TYPE                   = 23,                                   /* AKA type */
    PPPC_EAP_AKA_PRIME_TYPE             = 50,                                   /* AKA Prime type */
    PPPC_EAP_EXPAND_NAK_TYPE            = 254,                                  /* EXPANDED type */

    PPPC_EAP_TYPE_BUTT
};
typedef VOS_UINT8  PPPC_EAP_METHODS_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : EAP���������ڲ�ӳ��
*****************************************************************************/
enum PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM
{
    PPPC_EAP_INTERNAL_RESV_TYPE                  = 0,                           /* �������� */
    PPPC_EAP_INTERNAL_MD5_TYPE                   = 1,                           /* MD5 type */
    PPPC_EAP_INTERNAL_AKA_TYPE                   = 2,                           /* AKA type */
    PPPC_EAP_INTERNAL_AKA_PRIME_TYPE             = 3,                           /* AKA Prime type */

    PPPC_EAP_INTERNAL_TYPE_BUTT
};
typedef VOS_UINT8  PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : PPPC_EAP_CODE_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : EAP��������
*****************************************************************************/
enum PPPC_EAP_CODE_TYPE_ENUM
{
    PPPC_EAP_REQUEST_TYPE           = 1,                                        /* Request���ͱ��� */
    PPPC_EAP_RESPONSE_TYPE          = 2,                                        /* Response���ͱ��� */
    PPPC_EAP_SUCCESS_TYPE           = 3,                                        /* Success���ͱ��� */
    PPPC_EAP_FAILURE_TYPE           = 4,                                        /* Failure���ͱ��� */

    PPPC_EAP_CODE_TYPE_BUTT
};
typedef VOS_UINT8  PPPC_EAP_CODE_TYPE_ENUM_UINT8;


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPPC_EAP_DEF_H_ */

#endif      /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


