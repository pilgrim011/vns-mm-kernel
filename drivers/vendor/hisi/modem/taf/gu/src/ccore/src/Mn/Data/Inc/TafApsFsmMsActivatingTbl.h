/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmMsActivatingTbl.h
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2011��12��16��
  ����޸�   :
  ��������   : TafApsFsmMsActivatingTbl.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��16��
    ��    ��   : s62952
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_APS_FSM_MSACTIVATING_TBL_H__
#define __TAF_APS_FSM_MSACTIVATING_TBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
extern TAF_STA_STRU                             g_astTafApsMsActivatingStaTbl[];
#define TAF_APS_GetMsActivatingStaTbl()         (g_astTafApsMsActivatingStaTbl)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_APS_MS_ACTIVATING_SUBSTATE_ENUM_UINT32
 ö��˵��  : MS ACTIVATING��״̬����״̬ö�ٶ���
 1.��    ��   : 2011��12��15��
   ��    ��   : h44270
   �޸�����   : �½�

*****************************************************************************/
enum TAF_APS_MS_ACTIVATING_SUBSTA_ENUM
{
    TAF_APS_MS_ACTIVATING_SUBSTA_INIT,                                          /* MS ACTIVATING״̬���ĳ�ʼ״̬ */
    TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND,                                       /* MS ACTIVATING״̬���Ĺ���״̬ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF,                          /* APS��SM������PDP�������󣬵ȴ�SM��Ӧ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND,                  /* APS��SM������PDP�������󣬵ȴ�SM��Ӧʱ������ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP,                       /* APS��SNDCP�����˼���SNDCP���󣬵ȴ�SNDCP��Ӧ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND,               /* APS��SNDCP�����˼���SNDCP���󣬵ȴ�SNDCP��Ӧʱ������ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ABORT_CNF,                             /* APS��SM����ȡ��ҵ���������APS�ȴ�SM��Ӧ*/
#if (FEATURE_ON == FEATURE_LTE)
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF,                         /* APS��ESM������PDP�������󣬵ȴ�ESM��Ӧ */
    TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND,                 /* APS��ESM������PDP�������󣬵ȴ�ESM��Ӧ������ */
#endif
    TAF_APS_MS_ACTIVATING_SUBSTA_BUTT
} ;
typedef VOS_UINT32 TAF_APS_MS_ACTIVATING_SUBSTATE_ENUM_UINT32;


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
VOS_UINT32 TAF_APS_GetMsActivatingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetMsActivatingFsmDescAddr( VOS_VOID );








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

#endif /* end of TafApsFsmMsActivating.h */
