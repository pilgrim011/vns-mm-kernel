/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndEsm.h
  �� �� ��   : ����
  ��    ��   : w00316404
  ��������   : 2015��12��7��
  ����޸�   :
  ��������   : TafApsSndEsm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFAPSSNDESM_H__
#define __TAFAPSSNDESM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "TafApsComFunc.h"

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
 ö����: APS_ESM_PDP_STATE_ENUM_UINT32
 ö��˵��: PDP״̬
 1.��    ��   : 2015��12��7��
   ��    ��   : w00316404
   �޸�����   : Added for Split L4A Project
*****************************************************************************/
enum APS_ESM_PDP_STATE_ENUM
{
    APS_ESM_PDP_STATE_INACTIVE                  = 0x00,                         /* PDPû���� */
    APS_ESM_PDP_STATE_ACTIVE                    = 0x01,                         /* PDP�Ѽ��� */

    APS_ESM_PDP_STATE_BUTT                      = 0xFF
};
typedef VOS_UINT32 APS_ESM_PDP_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : APS_ESM_BEARER_ACT_RESULT_ENUM
 ö��˵��  : ���ؼ�����ȡֵ
 1.��    ��   : 2015��12��7��
   ��    ��   : w00316404
   �޸�����   : Added for Split L4A Project
*****************************************************************************/
enum APS_ESM_BEARER_ACT_RESULT_ENUM
{
    APS_ESM_BEARER_ACT_ACCEPT           = 0x00,
    APS_ESM_BEARER_ACT_REJ              = 0x01,
    APS_ESM_BEARER_ACT_BUTT
};
typedef VOS_UINT32 APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32;
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
VOS_VOID TAF_APS_SndEsmSetCgactMsgDistr(
    VOS_UINT8                           ucPdpId,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmSetCgactPdpSetupReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmSetCgactPdpReleaseReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);
VOS_VOID TAF_APS_SndEsmPppDialSetupReq(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo
);
VOS_UINT32 TAF_APS_SndEsmNdisconnReq(
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq
);
VOS_VOID TAF_APS_SndEsmPdpModifyReq(
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq
);
VOS_VOID TAF_APS_SndEsmPdpReleaseReq(
    TAF_PS_CALL_END_REQ_STRU           *pstCalEndReq
);
VOS_VOID TAF_APS_SndEsmPdpManagerRsp(
    APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32   ulSetupRslt,
    VOS_UINT8                               ucCid
);

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

#endif /* end of TafApsSndEsm.h */
