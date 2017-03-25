/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccTimer.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��7��10��
  ����޸�   :
  ��������   : XCCģ��timer��صĶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��10��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XCC_TIMER_H__
#define __CNAS_XCC_TIMER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* TI_CNAS_XCC_T52M ��ʱ��5s */
#define TI_CNAS_XCC_T52M_LEN                                (5*1000)

/* TI_CNAS_XCC_T53M ��ʱ��65s */
#define TI_CNAS_XCC_T53M_LEN                                (65*1000)

/* TI_CNAS_XCC_T54M ��ʱ��0.2s */
#define TI_CNAS_XCC_T54M_LEN                                (2*100)

/* L2 ACK�����ı���ʱ����120S, ����ʱ�������ı���ʱ����300S */
#define TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN                (5*1000)
#define TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN                     (305*1000)
#define TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN               (15*1000)
#define TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN               (5*1000)
#define TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN           (5*1000)

/* CNAS����CNAS_CAS_1X_DSCH_DATA_REQ��CAS��CAS��6s��ʱ����CTTF��cancel
   �յ�cancel�����ʱ�󣬸�CNAS��DATA_CNF�����CAS�����12s��CNAS��
   1s��������ʱ����Ϊ12+1=13s  */
#define TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN                    (13*1000)
#define TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK_LEN               (13*1000)

#define TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK_LEN          (13*1000)

#define TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK_LEN (13*1000)

#define TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK_LEN            (13*1000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : CNAS_XCC_TIMER_ID_ENUM
 ö��˵��  : XCCģ���TIMER ID����
 1.��    ��   : 2014��07��10��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_TIMER_ID_ENUM
{
    /* Reference to C.S0005-A Table D-1. Time Limits:
     Maximum time to receive a message in the Waiting for Order Substate of the Call Control processing
     that transits Call Control instance to a different substate or state */
    TI_CNAS_XCC_T52M,

    /* Reference to C.S0005-A Table D-1. Time Limits:
     Maximum time to receive a message in the Waiting for Mobile Station Answer Substate of Call Control
     processing that transits the Call Control instance to a different substate or state */
    TI_CNAS_XCC_T53M,

    TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP,
    TI_CNAS_XCC_WAIT_AS_EST_CNF,
    TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND,
    TI_CNAS_XCC_WAIT_CONN_L2_ACK,
    TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP,
    TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,

    TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,

    TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,

    TI_CNAS_XCC_TIMER_ID_BUTT
};
typedef VOS_UINT32  CNAS_XCC_TIMER_ID_ENUM_UINT32;


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



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

#endif /* end of __CNAS_XCC_TIMER_H__ */
