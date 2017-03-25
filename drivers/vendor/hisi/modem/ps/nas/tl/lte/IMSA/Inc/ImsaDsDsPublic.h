/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaPublic.h
    Description : ImsaPublic.cͷ�ļ�
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSADSDSPUBLIC_H__
#define __IMSADSDSPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "PsCommonDef.h"
#include "LPSCommon.h"
#include "ImsaEntity.h"
#include "LPsOm.h"
#include "ImsaImsEvent.h"
#include "ImsParm.h"
#include "ImsaLrrcInterface.h"
#include "NasFileId.h"
#include "PsRrmInterface.h"
#include "SpmImsaInterface.h"
#include "ImsaImsInterface.h"
#include "MsgImsaInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define TI_IMSA_GET_SERVICE_WAIT_RF_RESOURCE_TIMER_LEN  (5000)
#define TI_IMSA_DEREG_WAIT_RF_RESOURCE_TIMER_LEN        (1000)
#define TI_IMSA_MO_CALL_WAIT_RF_RESOURCE_TIMER_LEN      (30000)
#define TI_IMSA_MT_CALL_WAIT_RF_RESOURCE_TIMER_LEN      (30000)
#define TI_IMSA_EMC_CALL_WAIT_RF_RESOURCE_TIMER_LEN     (30000)
#define TI_IMSA_MO_SMS_WAIT_RF_RESOURCE_TIMER_LEN       (30000)
#define TI_IMSA_MT_SMS_WAIT_RF_RESOURCE_TIMER_LEN       (30000)
#define TI_IMSA_RF_OCCUPIED_DELAY_PROC_TIMER_LEN        (1000)
#define TI_IMSA_POWER_OFF_WAIT_RF_RESOURCE_TIMER_LEN    (1000)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
 ö����    : IMSA_DSDS_ENABLE_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ST����ʹ��
*****************************************************************************/
enum IMSA_DSDS_ENABLE_FLAG_ENUM
{
    IMSA_DSDS_INIT = 0,            /*��ʼdsds*/
    IMSA_DSDS_ENABLE,               /*��dsds*/
    IMSA_DSDS_DISABLE,                 /*�ر�dsds*/
    IMSA_DSDS_BUTT,
};
typedef VOS_UINT8 IMSA_DSDS_ENABLE_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : IMSA_TASKTYPE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : DSDS TASK Type״̬ö��
*****************************************************************************/
enum IMSA_DSDS_MODEMID_ENUM
{
    IMSA_DSDS_MODEM0 = 0,                  /*MODEM0*/
    IMSA_DSDS_MODEM1,                      /*MODEM1*/
    IMSA_DSDS_MODEM_BUTT
};
typedef VOS_UINT8 IMSA_DSDS_MODEMID_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : IMSA_DSDS_TASKTYPE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ѷ��͵�REQ��Ӧ��CNF��Ϣ
*****************************************************************************/
typedef struct
{
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType;
    IMSA_TASKTYPE_STATUS_ENUM_UINT8         enStatus;
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc;
    VOS_UINT32                              ulPara;
    VOS_UINT8                               ucHasBuffer;    /* 1:��ʾ���ڣ�0:��ʾ������ */
    VOS_UINT8                               aucRsv[3];
}IMSA_DSDS_TASKTYPE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_DSDS_BUFFER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA DSDS��صĻ���ṹ
*****************************************************************************/
typedef struct
{
    SPM_IMSA_CALL_ORIG_REQ_STRU             stMoCall;
    SPM_IMSA_CALL_ORIG_REQ_STRU             stEmcCall;
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU       stEnhancedConferrence;
    /* ��ԭ�ṹ������޸�Ϊָ�룬ʹ��ʱ����ռ䣬���յ�����MO SMS CNF�����볬ʱ��
        �Լ��ػ�ʱ�жϲ��ͷ�����Ŀռ䣬�Ӷ�������ڴ����� */
    MSG_IMSA_RP_DATA_REQ_STRU              *pstMoSms;
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU          stMtSms;
    MSG_IMSA_SMMA_REQ_STRU                  stSmma;
}IMSA_DSDS_BUFFER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_DSDS_BUFFER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA DSDS��صĻ���ṹ
*****************************************************************************/
typedef struct
{
    IMSA_DSDS_BUFFER_INFO_STRU              stBufferInfo;

    IMSA_TIMER_STRU                         stWaitRegRFTimer;
    IMSA_TIMER_STRU                         stWaitDeRegRFTimer;
    IMSA_TIMER_STRU                         stWaitMoCallRFTimer;
    IMSA_TIMER_STRU                         stWaitMtCallRFTimer;
    IMSA_TIMER_STRU                         stWaitEmcCallRFTimer;
    IMSA_TIMER_STRU                         stWaitMoSmsRFTimer;
    IMSA_TIMER_STRU                         stWaitMtSmsRFTimer;
    IMSA_TIMER_STRU                         stDelayProcOccupiedTimer;
    IMSA_TIMER_STRU                         stWaitPowerOffRfTimer;
}IMSA_DSDS_PUBLIC_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern IMSA_DSDS_TASKTYPE_INFO_STRU     g_stImsaDsdsTaskTypeInfo[];
extern IMSA_DSDS_PUBLIC_INFO_STRU       g_stDsdsPubilcInfo;
#define IMSA_DSDS_ABNORMAL_IDX  0xff

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  IMSA_DsdsProcRegResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMoCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcEmcCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMtCallResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMoSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcMtSmsResourceTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsProcOccupyDelayTimerExp
(
    const VOS_VOID                     *pMsg
);

extern VOS_VOID  IMSA_DsdsStartApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
);

extern VOS_VOID  IMSA_DsdsStopApplyReqTimer
(
    RRM_PS_TASK_TYPE_ENUM_UINT16            enTaskType,
    IMSA_RF_RES_APPLY_TRIGER_SRC_ENUM_UINT8 enTrigerSrc
);


extern VOS_UINT32  IMSA_DsdsIsHasActiveResource
(
    VOS_VOID
);

extern VOS_VOID IMSA_DsdsInit( VOS_VOID );
extern VOS_VOID IMSA_DsdsClearResource(VOS_VOID);
extern VOS_VOID IMSA_RrmMsgDistr(const VOS_VOID *pRcvMsg);
extern VOS_UINT32 IMSA_DsdsGetIndexByTaskType (RRM_PS_TASK_TYPE_ENUM_UINT16 enTaskType);
extern VOS_VOID IMSA_ProcMsgResourceApplyCnf
(
    const RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU *pstApplyCnf
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaPublic.h */




