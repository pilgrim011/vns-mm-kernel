

#ifndef __CNAS_EHSM_TIMER_MGMT_H__
#define __CNAS_EHSM_TIMER_MGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_EHSM_ONE_THOUSAND_MILLISECOND                      (1000)                         /* 1000MS */

#define TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN                      (31*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN                (30*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF_LEN                 (10*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_DETACH_CNF_LEN                        (10*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_WAIT_HSM_DISC_CNF_LEN                      (16*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

#define TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN           (4*CNAS_EHSM_ONE_THOUSAND_MILLISECOND)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


enum CNAS_EHSM_TIMER_ID_ENUM
{
    /* timer for common connection establish confirm from HSM */
    TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF,

    /* Timer to retry the commomn connection establish */
    TI_CNAS_EHSM_WAIT_CONN_RETRY_EST,

    /* Timer for PDN setup confirm and Attach confirm from PPP */
    TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF,

    /* Timer to retry the PDN set up */
    TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP,

    /* Timer for PDN disconnect confirm from PPP */
    TI_CNAS_EHSM_WAIT_CTTF_PDN_DISC_CNF,

    /* Timer for detach (disc all pdn)*/
    TI_CNAS_EHSM_WAIT_DETACH_CNF,

    /* Timer for disconnect confirm from HSM */
    TI_CNAS_EHSM_WAIT_HSM_DISC_CNF,

    /* Timer for protecting all power off process for EHSM */
    TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS,

    TI_CNAS_EHSM_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_EHSM_TIMER_ID_ENUM_UINT32;



enum CNAS_EHSM_TIMER_STATUS_ENUM
{
    CNAS_EHSM_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    CNAS_EHSM_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    CNAS_EHSM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_TIMER_STATUS_ENUM_UINT8;

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

typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId;                              /* ��ʱ����ID */
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];
}CNAS_EHSM_TIMER_CTX_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ*/ /*_H2ASN_Skip*/
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* ��ʱ��ʱ�� */
}CNAS_EHSM_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  CNAS_EHSM_SndOmTimerStatus(
    CNAS_EHSM_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  CNAS_EHSM_StartTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  CNAS_EHSM_StopTimer(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
);

CNAS_EHSM_TIMER_STATUS_ENUM_UINT8  CNAS_EHSM_GetTimerStatus(
    CNAS_EHSM_TIMER_ID_ENUM_UINT32      enTimerId
);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasEhsmTimerMgmt.h */
