/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcInit.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2013��07��30��
  ����޸�   :
  ��������   : MTCģ��ĳ�ʼ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��30��
    ��    ��   : l60609
    �޸�����   : ������

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcInit.h"
#include "MtcCtx.h"
#include "MtcMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_INIT_C
/*lint +e767 �޸���: l00198894; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
/*****************************************************************************
 �� �� ��  : MTC_PidInit
 ��������  : MTCģ���Pid��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��12��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_UINT32 MTC_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ��ʼ�������� */
            MTC_InitCtx();
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif
/*****************************************************************************
 �� �� ��  : MTC_FidInit
 ��������  : MTC��FID��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_UINT32 MTC_FidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTC,
                                         (Init_Fun_Type)MTC_PidInit,
                                         (Msg_Fun_Type)MTC_ProcMsg);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(UEPS_FID_MTC, VOS_PRIORITY_M5);
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

