/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CmmcaInit.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��01��08��
  ����޸�   :
  ��������   : CMMCAģ��ĳ�ʼ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��01��08��
    ��    ��   : l60609
    �޸�����   : ������

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaInit.h"
#include "CmmcaMain.h"
#include "CmmcaCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_INIT_C
/*lint +e767 �޸���: l60609; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : CMMCA_PidInit
 ��������  : CMMCAģ���Pid��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��08��
    ��    ��   : L60609
    �޸�����   : L-C��������Ŀ

*****************************************************************************/
VOS_UINT32 CMMCA_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ��ʼ�������� */
            CMMCA_InitCtx();
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : CMMCA_FidInit
 ��������  : CMMCA��FID��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CMMCA_FidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CMMCA,
                                         (Init_Fun_Type)CMMCA_PidInit,
                                         (Msg_Fun_Type)CMMCA_ProcMsg);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CMMCA, VOS_PRIORITY_M5);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;

        default:
            break;
    }
#endif

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
