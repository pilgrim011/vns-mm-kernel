/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmFsmMainTbl.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��8��
  ����޸�   :
  ��������   : TafSpmFsmMainTbl.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��8��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmFsmMainTbl.h"
#include "Taf_Tafm_Remote.h"
#include "NasStkInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmFsmMain.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-23, begin */
#include "ImsaInterface.h"
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-23, end */
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_TBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* Ԥ����״̬�� */
TAF_FSM_DESC_STRU                       g_stTafSpmMainFsmDesc;


/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* IDLE״̬���������Ϣ������ */
TAF_ACT_STRU        g_astTafSpmMainProcessActTbl[]   =
{
    /*  AT SS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGISTERSS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ACTIVATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_DEACTIVATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_INTERROGATESS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGPWD_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASECCENTRY_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PROCESS_USS_MSG,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, end */

    /* STK SS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_USSD_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGISTERSS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ERASESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ACTIVATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_DEACTIVATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_INTERROGATESS_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGPWD_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, end */


    /* AT SMS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                      TAF_SPM_RcvAppReqMsg_Main ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_CALLORIG_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, end */

    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */

    /* TAF Internal message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND,
                      TAF_SPM_RcvSpmServiceCtrlResultInd_Main ),



    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */


    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_ECONF_DIAL_REQ,
                      TAF_SPM_RcvAppReqMsg_Main ),
#endif


};

/* MAIN״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafSpmMainProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_SPM_MAIN_STA_IDLE,
                      g_astTafSpmMainProcessActTbl )
};

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetMainProcessStaTblSize
 ��������  : ��ȡSPMģ��������״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:�����������״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetMainProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafSpmMainProcessFsmTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetMainFsmDescAddr
 ��������  : ��ȡSPMģ��������״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��SPM������״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_SPM_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmMainFsmDesc);
}









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

