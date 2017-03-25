/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaProcMma.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��21��
  ����޸�   :
  ��������   : ������MMA��ص���Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��21��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbaMntn.h"

#include "TafMmaInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMA_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



/*****************************************************************************
 �� �� ��  : TAF_CBA_ProcMmaMsg
 ��������  : ����MMAģ�鷢�͵���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_ProcMmaMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case MN_USIM_STATUS_IND:
            TAF_CBA_RcvMmaUsimStatusInd(pstMsg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_RcvMmaUsimStatusInd
 ��������  : ����MMA���͵�USIM����λ״̬��Ϣ, �������λ��ʼ��ȡCBS��ص�
             USIM���ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2012��3��28��
    ��    ��   : w00176964
    �޸�����   : �޸Ķ�ȡ�ļ��߼�
  3.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : ����ʱ�ϱ�CBS���NV�Ŀ�ά�ɲ���Ϣ
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  5.��    ��   : 2013��8��12��
    ��    ��   : f62575
    �޸�����   : DTS2013081900835��֧���ȸ���USIM���ã������NV����
*****************************************************************************/
VOS_VOID TAF_CBA_RcvMmaUsimStatusInd(
    struct MsgCB                       *pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU          *pstUsimStatus;

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;

    if (MNPH_USIM_STATUS_AVILABLE != pstUsimStatus->enUsimStatus)
    {
        /* ��ʼ��CBAģ���USIM��ص�ȫ�ֱ��� */
        TAF_CBA_InitSimInfo();
        /* ׷��NV�����õ�CBS������Ϣ�б� */
        TAF_CBA_AppendNvUserAcceptMsgIdList();
        return;
    }

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ��ȡCBS��ص�USIM���ļ�. �ļ���ȡ˳��: CBMI �ļ�; CBMIR �ļ� CBMID */
	/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    /* ׷��NV�����õ�CBS������Ϣ�б� */
    TAF_CBA_AppendNvUserAcceptMsgIdList();

    /* Ӧ��USIM�ļ���Ϣ�����غ�֪ͨ�ײ����ø��� */
    TAF_CBA_ApplyUsimInfo();
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ��NV��صĿ�ά�ɲ���Ϣ  */
    TAF_CBA_SndOmNvimInfo();

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
