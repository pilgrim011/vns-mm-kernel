/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaModemInfoQuery.h
  �� �� ��   : ����
  ��    ��   : zwx247453
  ��������   : 2015��10��19��
  ����޸�   :
  ��������   : MTAģ�鴦��AT���·���ѯ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : Network Monitor����

******************************************************************************/

#ifndef __TAFMTAMODEMINFOQUERY_H__
#define __TAFMTAMODEMINFOQUERY_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "MtaRrcInterface.h"
#include "TafMtaPhy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MTA_NETMON_GSM_TA_INVALID_VALUE (255)

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

VOS_VOID TAF_MTA_RcvQryWrrAutotestReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvQryWrrCellInfoReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvQryWrrMeanrptReq( VOS_VOID  *pMsg );
VOS_VOID TAF_MTA_RcvWrrAutotestQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrCellInfoQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrMeanrptQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvTiReqAutotestQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqCellInfoQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqMeanrptQryExpired( VOS_VOID *pMsg );
VOS_UINT32 TAF_MTA_SndWrrQryAutotestReqMsg( MTA_WRR_AUTOTEST_PARA_STRU  *pAutotestQryPara );
VOS_UINT32 TAF_MTA_SndWrrQryCellinfoReqMsg(
    VOS_UINT32                          ulSetCellInfo
);
VOS_UINT32 TAF_MTA_SndWrrQryMeanrptReqMsg( VOS_VOID );

VOS_VOID TAF_MTA_RcvAtTransModeQryReq(VOS_VOID *pMsg);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MTA_SndLrrcTransModeQryReq(VOS_VOID);
VOS_VOID TAF_MTA_RcvLrrcTransModeQryCnf(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitLrrcTransModeQryExpired(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID    TAF_MTA_RcvAtSetNetMonSCellReq(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvAtSetNetMonNCellReq(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_SndRrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
);
VOS_UINT32  TAF_MTA_SndGasNetMonQryTaReq(
    AT_APPCTRL_STRU                    *pstAppCtrl
);
VOS_VOID    TAF_MTA_RcvGasNetMonTaQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvGasNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvWrrNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired(
    VOS_VOID                           *pMsg
);
VOS_VOID    TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired(
    VOS_VOID                           *pMsg
);
VOS_UINT32  TAF_MTA_GetNetMonSndMsgInfo(
    VOS_UINT32                         *pulMsgName,
    VOS_UINT32                         *pulReceiverPid
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID    TAF_MTA_SndLrrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
);
VOS_VOID    TAF_MTA_RcvLrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_VOID    TAF_MTA_RcvTrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID TAF_MTA_RcvAtQryAfcAndXoInfoReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvRcmAfcInfoCnf(
    VOS_VOID                           *pMsg
);

AT_MTA_AFC_CLK_STATUS_ENUM_UINT32 TAF_MTA_GetAfcClkStatus(PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus);



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

