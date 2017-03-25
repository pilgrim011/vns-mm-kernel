/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdTimer.h
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��7��3��
  ����޸�   :
  ��������   : timer��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��3��
    ��    ��   : y00245242
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XSD_TIMER_H__
#define __CNAS_XSD_TIMER_H__

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
/* XSD�ж�ʱ����ʱ�� */
#define TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN                  (30*1000)
#define TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN                  (5*1000)
#define TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN                 (5*1000)
#define TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN                  (10*1000)
#define TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN              (5*1000)
#define TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN               (5*1000)

#define TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN              (17*1000)  /* �ȴ�CASͬ��һ��Ƶ��ı�����ʱ��ʱ�� */

#define TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN                    (30*1000)
#define TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN       (5*1000)

#define TI_CNAS_XSD_AVAILABLE_LEN                           (5*1000)

/* Reference to CDG 143 Table A-1 Configurable Parameters */
#define TI_CNAS_XSD_T_BSR_DIG_LEN                           (180*1000)
#define TI_CNAS_XSD_T_BSR_CALL_LEN                          (5*1000)
#define TI_CNAS_XSD_T_BSR_NEWSYS_LEN                        (1*1000)

#define TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN         (15*3600*1000)  /* 15 hours */

#define TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN         (3*1000)

#define TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN       (1*1000)

#define TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN                 (6*1000)

#define TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER_LEN     (15*1000)   /* ������CallBackģʽ����15s������ʱ�� */
#define TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER_LEN       (500)       /* ������CallBackģʽ����500���뱣����ʱ�� */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_XSD_TIMER_ID_ENUM
 ö��˵��  : XSD��ʱ����ID
 1.��    ��   : 2014��7��4��
   ��    ��   : h00246512
   �޸�����   : �½�

 2.��    ��   : 2015��1��4��
   ��    ��   : y00245242
   �޸�����   : �½�

 3.��    ��   : 2015��7��4��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
enum CNAS_XSD_TIMER_ID_ENUM
{
    TI_CNAS_XSD_WAIT_CARD_FILE_CNF,
    TI_CNAS_XSD_WAIT_XCC_START_CNF,
    TI_CNAS_XSD_WAIT_XREG_START_CNF,
    TI_CNAS_XSD_WAIT_CAS_START_CNF,
    TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF,
    TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
    TI_CNAS_XSD_WAIT_CAS_OHM_IND,
    TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
    TI_CNAS_XSD_AVAILABLE_TIMER,
    /* Reference to CDG 143 Table A-1 Configurable Parameters */
    TI_CNAS_XSD_T_BSR_DIG,
    TI_CNAS_XSD_T_BSR_CALL,
    TI_CNAS_XSD_T_BSR_NEWSYS,
    TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND,
    TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
    TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
    TI_CNAS_XSD_AVAILABLE_MRU0_TIMER,
    TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF,
    TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,    /* ������CALLBACKģʽ15s����������ʱ�� */
    TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,            /* ������CALLBACKģʽ������ʱ�� */
    TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER,      /* ������CaLLBACKģʽ�ļ����ʱ�� */
    TI_CNAS_XSD_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_XSD_TIMER_ID_ENUM_UINT32;

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

#endif /* end of CnasXsdTimerMgmt.h */
