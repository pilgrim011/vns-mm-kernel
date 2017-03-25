/************************************************************************
 *                                                                      *
 *                             Eap_typ.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             wangyong                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP��eapЭ��ģ��˽�����ݽṹ                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������eapЭ��ģ���ȫ��˽�����ݽṹ                        *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _PPPC_EAP_TYP_H_
#define      _PPPC_EAP_TYP_H_

#ifdef      __cplusplus
extern "C" {
#endif     /* end of __cplusplus */

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "pppc_eap_def.h"

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

/** ****************************************************************************
* Name        : PPPC_EAP_HEADER_STRU
*
* Description : EAP����ͷ�Ĺ����ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEAPCode;
    VOS_UINT8                           ucEAPID;
    VOS_UINT16                          usEAPLen;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT8                           aucResv[3];
}PPPC_EAP_HEADER_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_METHOD_OUTPUT_STRU
*
* Description : ���������
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPppId;
    VOS_UINT16                         *pusRespLen;
    VOS_UINT8                          *pucPktData;
}PPPC_EAP_METHOD_OUTPUT_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_METHOD_INPUT_STRU
*
* Description : EAP����������
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEAPID;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT16                          usEAPLen;                               /* ָʾTYPE-DATA�ĳ��� */
    VOS_UINT8                          *pucPktData;
}PPPC_EAP_METHOD_INPUT_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU
*
* Description : EXPAND NAK���ĵ�type-data��ṹ
*******************************************************************************/
typedef struct
{
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enEAPType;
    VOS_UINT8                           aucIETF[3];
    VOS_UINT32                          ulType;
}PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU;

/*****************************************************************************
 �ṹ��    : PPPC_EAP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EAP ���ƿ����ݽṹ����
*****************************************************************************/
typedef struct
{
    PPPINFO_S                          *pstPppInfo;                             /* PPP���ƿ�ָ�� */
    VOS_UINT16                          usEAPLastReqID;                         /* �ϴη��͵�Response����ID,��UINT16��ʾ��֤��ʼֵ��������յ��ظ� */
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enRequestType;                          /* �յ���Request���ĵ�Type */
    VOS_UINT8                           ucRequestID;                            /* �յ���Request���ĵ�ID */
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enSelectMethod;                         /* ѡ�еķ��� */
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8 enInterType;                      /* �ڲ�ӳ�䷽�� */
    PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16 enEapPeerState;                     /* Peer״̬ */
    HTIMER                              hReqTimeoutID;                          /* �ȴ�EAP Req��ʱ��ʱ�� */
    VOS_UINT32                          ulTimeOutTime;                          /* ��ʱʱ�� */
    VOS_UINT32                          ulLocalResult;                          /* ���ڴ洢���˵ļ�Ȩ��� */
    VOS_UINT32                          ulRemoteResult;                         /* ���ڴ洢����ļ�Ȩ��� */
    VOS_UINT16                          usRespPktLen;                           /* ���Response���ĵĳ��� */
    VOS_UINT8                           aucResv1[2];
    VOS_UINT8                           aucRespPkt[PPPC_EAP_MAX_RESPONSE_LEN];  /* Response����Payload��� */
} PPPC_EAP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_PROC_PKT_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EAP���ü�Ȩ�����Ļص�����������
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_PROC_PKT_FUNC)
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_PRE_PROC_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EAP���ü�Ȩ�����Ļص���������Ԥ������
*****************************************************************************/
typedef PS_BOOL_ENUM_UINT8 (*PPPC_EAP_METHOD_PRE_PROC_FUNC)
(
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_INIT_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EAP���ü�Ȩ�����Ļص�������ʼ������
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_INIT_FUNC)(PPPC_EAP_METHODS_TYPE_ENUM_UINT8);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EAP���ü�Ȩ�����Ļص�����֪ͨ����ļ�Ȩ���
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC)(VOS_UINT32);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_INIT_STATE_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʼ��������״̬
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_METHOD_INIT_STATE_FUNC)(VOS_VOID);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_PEER_EVENT_PROC_FUNC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PEER״̬�����¼�������
*****************************************************************************/
typedef VOS_VOID (*PPPC_EAP_PEER_EVENT_PROC_FUNC)(PPPINFO_S *, VOS_VOID *);

/*****************************************************************************
 �ṹ��    : PPPC_EAP_METHOD_CB_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ĵ���ص�����
*****************************************************************************/
typedef struct
{
    PPPC_EAP_METHOD_INIT_FUNC           pfuncInitMethod;
    PPPC_EAP_METHOD_INIT_STATE_FUNC     pfuncInitMethodState;
    PPPC_EAP_METHOD_RESULT_NOTIFY_FUNC  pfuncNotifyMethodRes;
    PPPC_EAP_METHOD_PROC_PKT_FUNC       pfuncProcMethodPkt;
    PPPC_EAP_METHOD_PRE_PROC_FUNC       pfuncPreProc;
} PPPC_EAP_METHOD_CB_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPPC_EAP_TYP_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

