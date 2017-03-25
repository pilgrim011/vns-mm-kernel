/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcSndMm.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2010��5��9��
  ����޸�   :
  ��������   : MMC����MM����Ϣ�Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��05��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasMmSublayerDef.h"
#include "NasMmcCtx.h"
#include "NasMmcSndMm.h"
#include "NasMmlMsgProc.h"
#include "MmcMmInterface.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcComFunc.h"
#include "Nasrrcinterface.h"
#include "NVIM_Interface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_MM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmStartReq
 ��������  : ��MM���Ϳ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��10��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmStartReq(VOS_VOID)
{
    MMCMM_START_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCMM_START_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_START_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ����  */
    pstMsg->MsgHeader.ulMsgName   = MMCMM_START_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}

 /*****************************************************************************
  �� �� ��  : NAS_MMC_SndMmPowerOffReq
  ��������  : ��MMģ�鷢�͹ػ�ԭ��MMCMM_POWER_OFF_REQ�Ĵ���
  �������  : VOS_VOID
  �������  : ��
  �� �� ֵ  : VOS_VOID
  ���ú���  :
  ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmPowerOffReq(VOS_VOID)
{
    MMCMM_POWER_OFF_REQ_STRU               *pstMsg              = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCMM_POWER_OFF_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_POWER_OFF_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstMsg->MsgHeader.ulMsgName         = MMCMM_POWER_OFF_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmSuspendInd
 ��������  : MMC��MM���͹���ָʾ
 �������  : RRMM_SUSPEND_IND_ST                *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
)
{
    /*��MM���͹���ָʾ,����ԭ������ָ�� */
    MMCMM_SUSPEND_IND_STRU             *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCMM_SUSPEND_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SUSPEND_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_SUSPEND_IND;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ucSuspendCause              = pstMsg->ucSuspendCause;
    pstSndMsg->ucSuspendOrigen             = pstMsg->ucSuspendOrigen;
    pstSndMsg->ucSuspendDestination        = pstMsg->ucSuspendDestination;

    PS_MEM_CPY(pstSndMsg->astReTxMsg, pstMsg->astReTxMsg, sizeof(NAS_RRC_RE_TX_MSG_STRU));

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmPlmnSchInit
 ��������  : ��MM����plmnsrchinit
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmPlmnSchInit(VOS_VOID)
{
    /*��MM���͹���ָʾ,����ԭ������ָ�� */
    MMCMM_PLMN_SEARCH_INITIATED_STRU   *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCMM_PLMN_SEARCH_INITIATED_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_PLMN_SEARCH_INITIATED_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmPlmnSchInit:ALLOC MEM ERROR!");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_PLMN_SEARCH_INITIATED_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_PLMN_SEARCH_INITIATED;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmWasSysInfoInd
 ��������  : ��MMת��WASϵͳ��Ϣ
 �������  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT8                           ucUserSpecSrchPlmnFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��24��
    ��    ��   : w00166186
    �޸�����   : DTS2011122004483,ָ��������ͣLAU����ͳһ�޸�
  3.��    ��   : 2012��09��26��
    ��    ��   : l65478
    �޸�����   : DTS2012092201886,HPLMNע��ʧ��#11,����פ����csû�з���ע��
  4.��    ��   : 2012��11��29��
    ��    ��   : W00176964
    �޸�����   : DTS2012112902395,BVT����,hplmn����#11�������Ҫ����ע��
  5.��    ��   : 2013��07��25��
    ��    ��   : l65478
    �޸�����   : ��ǰ����פ��,���û�ָ��������ǰ������ʱ,MM������ע��,GCFʧ��
  6.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��
  7.��    ��   : 2015��6��11��
    ��    ��   : b00269685
    �޸�����   : ����ota �� sys
  8.��    ��   : 2015��11��16��
    ��    ��   : c00318887
    �޸�����   : DTS2015061609864
*****************************************************************************/
VOS_VOID   NAS_MMC_SndMmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_SYS_INFO_IND_STRU            *pstInternalMsg    = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd = VOS_NULL_PTR;

    pstInternalMsg  = (MMCMM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET(pstInternalMsg, 0x00, sizeof(MMCMM_SYS_INFO_IND_STRU));

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstInternalMsg->MsgHeader.ulMsgName         = MMCMM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength
                                = sizeof(MMCMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ulMask = NAS_MMC_GetOptMask_WasSysinfo(pstRrMmSysInfoInd);

    pstInternalMsg->enSysInfoType  = pstRrMmSysInfoInd->enSysInfoType;

    pstInternalMsg->ucCnCommonSize = pstRrMmSysInfoInd->ucCnCommonSize;

    /* aucCnCommonInfo[0] �� aucCnCommonInfo[1] ���� lac[0] ��  Lac[1]*/
    pstInternalMsg->usLac  = (VOS_UINT16)pstRrMmSysInfoInd->aucCnCommonInfo[1];
    pstInternalMsg->usLac |= (VOS_UINT16)(pstRrMmSysInfoInd->aucCnCommonInfo[0]<< NAS_MML_OCTET_MOVE_EIGHT_BITS);

    pstInternalMsg->ucCsInfoSize    = pstRrMmSysInfoInd->ucCsInfoSize;
    pstInternalMsg->ucLRTimerT3212  = pstRrMmSysInfoInd->aucCsInfo[0];

    /* aucCsInfo[1]�����Bit����ǰ�Ƿ�����ע�� */
    if (0 == (pstRrMmSysInfoInd->aucCsInfo[1] & NAS_MML_ATTATCH_IND_BIT_MASK_WAS_SYS_INFO))
    {
        pstInternalMsg->ucAttachDetach = VOS_FALSE;
    }
    else
    {
        pstInternalMsg->ucAttachDetach = VOS_TRUE;
    }

    pstInternalMsg->ucPsInfoSize       = pstRrMmSysInfoInd->ucPsInfoSize;
    pstInternalMsg->ucRac              = pstRrMmSysInfoInd->aucPsInfo[0];

    if (0 == (pstRrMmSysInfoInd->aucPsInfo[1] & NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO))
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_I;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_II;
    }

    if (0 == pstRrMmSysInfoInd->ucPsInfoSize)
    {
        pstInternalMsg->ucGprsSupportInd = VOS_FALSE;
    }
    else
    {
        pstInternalMsg->ucGprsSupportInd = VOS_TRUE;
    }

    pstInternalMsg->PlmnId.ulMcc           = pstRrMmSysInfoInd->PlmnId.ulMcc;
    pstInternalMsg->PlmnId.ulMnc           = pstRrMmSysInfoInd->PlmnId.ulMnc;

    pstInternalMsg->ulCsDrxLength          = pstRrMmSysInfoInd->ulCsDrxLength;
    pstInternalMsg->ulPsDrxLength          = pstRrMmSysInfoInd->ulPsDrxLength;

    pstInternalMsg->ulForbiddenFlg         = ulForbiddenFlg;


    /* ɾ�������û�ָ����ʱ����ulForbiddenFlg����ΪNULL�Ĵ��� */
    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* ��Hplmn��CSע�ᱻ�ܺ󣬷�E5ʱ�����ڷ���ע�� ,E5ʱ��HplmnRejlist����¼ֵ */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        pstInternalMsg->ulForbiddenFlg  = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSpecSrchPlmnFlg,
                                                NAS_MML_NET_RAT_TYPE_WCDMA,
                                                NAS_MMC_REG_DOMAIN_CS);
    }

    pstInternalMsg->ulCellId                = pstRrMmSysInfoInd->ulCellId;

    pstInternalMsg->ucUserSpecificSearchFlg = (VOS_UINT8)ulUserSpecSrchPlmnFlg;

     /* ��barתΪ��bar�ı�־λ */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmGsmSysInfoInd
 ��������  : ��MMת��ϵͳ��Ϣ
 �������  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT8                           ucUserSpecSrchPlmnFlg
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��24��
    ��    ��   : w00166186
    �޸�����   : DTS2011122004483,ָ��������ͣLAU����ͳһ�޸�
  3.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸ı�����
  4.��    ��   : 2013��07��25��
    ��    ��   : l65478
    �޸�����   : ��ǰ����פ��,���û�ָ��������ǰ������ʱ,MM������ע��,GCFʧ��
  5.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��
  6.��    ��   : 2015��11��16��
    ��    ��   : c00318887
    �޸�����   : DTS2015061609864
*****************************************************************************/
VOS_VOID   NAS_MMC_SndMmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_GSM_SYS_INFO_IND_ST          *pstInternalMsg  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo = VOS_NULL_PTR;

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, 
                    "NAS_MMC_SndMmGsmSysInfoInd: ulForbiddenFlg and ulUserSpecSrchPlmnFlg ",
                    ulForbiddenFlg,
                    ulUserSpecSrchPlmnFlg);

    pstInternalMsg  = (MMCMM_GSM_SYS_INFO_IND_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_GSM_SYS_INFO_IND_ST));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    pstInternalMsg->MsgHeader.ulMsgName         = MMCMM_GSM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength
        = sizeof(MMCMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ���CS��Ϣ */
    pstInternalMsg->ucAttachDetach           = pstGrrMmSysInfo->ucAttachDetach;
    pstInternalMsg->ucLRTimerT3212           = pstGrrMmSysInfo->ucLRTimerT3212;
    pstInternalMsg->ucGprsSupportInd         = pstGrrMmSysInfo->ucGprsSupportInd;
    pstInternalMsg->usLac                    = pstGrrMmSysInfo->usLac;

    /* ���PS��Ϣ */
    if (GRRMM_NW_OP_MODE_III == pstGrrMmSysInfo->ucNetworkOperationMode)
    {
        pstInternalMsg->ucNetworkOperationMode = GRRMM_NW_OP_MODE_II;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode = pstGrrMmSysInfo->ucNetworkOperationMode;
    }

    pstInternalMsg->ucRac                    = pstGrrMmSysInfo->ucRac;
    pstInternalMsg->stPlmnId.ulMcc           = pstGrrMmSysInfo->PlmnId.ulMcc;
    pstInternalMsg->stPlmnId.ulMnc           = pstGrrMmSysInfo->PlmnId.ulMnc;

    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* ��Hplmn��CSע�ᱻ�ܺ󣬷�E5ʱ�����ڷ���ע�� ,E5ʱ��HplmnRejlist����¼ֵ */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        pstInternalMsg->ulForbiddenFlg = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSpecSrchPlmnFlg,
                                                NAS_MML_NET_RAT_TYPE_GSM,
                                                NAS_MMC_REG_DOMAIN_CS);

    }

    pstInternalMsg->ucMsrRelease             = pstGrrMmSysInfo->ucMsrRelease;
    pstInternalMsg->ulCellId                 = pstGrrMmSysInfo->usCellId;

    pstInternalMsg->ucUserSpecificSearchFlg  = (VOS_UINT8)ulUserSpecSrchPlmnFlg;

    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstInternalMsg->unAcInfo.ucRestrictType               = pstGrrMmSysInfo->unAcInfo.ucRestrictType;

    /* �����GSM��ֹ���룬֪ͨMM/GMM����ֹ����ע�� */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
     pstInternalMsg->unAcInfo.ucRestrictType            = RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE;
    }
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

     /* ��barתΪ��bar�ı�־λ */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmResumeInd
 ��������  : NAS��MM����ResumeInd��ָʾ
 �������  : RRMM_RESUME_IND_ST                 *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��10��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2013��11��26��
    ��    ��   : w00176964
    �޸�����   : Volte PhaseII��Ŀ����

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    /*��MM���ͻָ�ָʾ,����ԭ������ָ�� */
    MMCMM_RESUME_IND_STRU              *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg  = (MMCMM_RESUME_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RESUME_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucCsSigExistFlg       = VOS_FALSE;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmCoverageLostInd
 ��������  : NAS��MM����coverage lost��ָʾ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmCoverageLostInd(VOS_VOID)
{

    MMCMM_COVERAGE_LOST_IND_STRU       *pstSndMsg           = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCMM_COVERAGE_LOST_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_COVERAGE_LOST_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndMmCoverageLostInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_COVERAGE_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_COVERAGE_LOST_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmWasAcInfoChangeInd
 ��������  : NAS��MM����AC INFO CHANGE��ָʾ
 �������  :
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : W00166186
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID  NAS_MMC_SndMmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU         *pstSndMsg           = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg       = (MMCMM_W_AC_INFO_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_W_AC_INFO_CHANGE_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndMmWasAcInfoChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCMM_W_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ��� */
    pstSndMsg->MsgHeader.ulMsgName         = MMCMM_W_AC_INFO_CHANGE_IND;
    pstSndMsg->enCsRestrictRegisterChange  = NAS_MML_RESTRICTION_NO_CHANGE;
    pstSndMsg->enPsRestrictRegisterChange  = NAS_MML_RESTRICTION_NO_CHANGE;

    /* CSע������ޱ�Ϊ������ */
    if ((VOS_TRUE == ucOldCsResTrictionRegister)
     && (VOS_FALSE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* CSע��Ӳ����ޱ�Ϊ���� */
    if ((VOS_FALSE == ucOldCsResTrictionRegister)
     && (VOS_TRUE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* PSע������ޱ�Ϊ������ */
    if ((VOS_TRUE == ucOldPsResTrictionRegister)
     && (VOS_FALSE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* PSע��Ӳ����ޱ�Ϊ���� */
    if ((VOS_FALSE == ucOldPsResTrictionRegister)
     && (VOS_TRUE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmRelReq
 ��������  : ��MM����CS���������ͷ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmRelReq(VOS_VOID)
{
    /* ��MM����CS���������ͷ���Ϣ */
    MMCMM_REL_REQ_STRU                 *pstSndMmRelMsg      = VOS_NULL_PTR;

    pstSndMmRelMsg  = (MMCMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndMmRelMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmRelReq,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstSndMmRelMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMmRelMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMmRelMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMmRelMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* ��д��Ϣ��� */
    pstSndMmRelMsg->MsgHeader.ulMsgName         = MMCMM_REL_REQ;
    pstSndMmRelMsg->MsgHeader.ulLength          = sizeof(MMCMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMmRelMsg);
    return;
}


/*******************************************************************************
 �� �� ��  : NAS_MMC_SndMmAttachReq
 ��������  : ����ԭ��MMCMM_ATTACH_REQ�Ĺ�������
 �������  : ulOpid       - Opid
              ulAttachType - Attach����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��9��
   ��    ��   : w00166186
   �޸�����   : �½���V7R1 PHASE II,ATTACH/DETACH����
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmAttachReq(
    VOS_UINT32                          ulOpid,
    VOS_UINT32                          ulAttachType
)
{
    MMCMM_ATTACH_REQ_STRU              *pstMsg              = VOS_NULL_PTR;
    MMCMM_ATTACH_REQ_STRU              *pstInternalMsg      = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstInternalMsg  = (MMCMM_ATTACH_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_ATTACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulMsgName           = MMCMM_ATTACH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(MMCMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulOpid                        = ulOpid;
    pstMsg->enAttachType                  = ulAttachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}

/*******************************************************************************
  �� �� ��  : NAS_MMC_SndMmDetachReq
  ��������  : ����ԭ��MMCMM_DETACH_REQ�Ĺ�������
  �������  : ulOpid         -- ������ʶ
              ulDetachType   -- detach����
              enDetachReason -- detachԭ��
  �������  : ��
  �� �� ֵ  :
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2011��7��9��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II,ATTACH/DETACH����
  2.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType,  /* detach���� */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason /* detachԭ�� */
)
{
    MMCMM_DETACH_REQ_STRU              *pstMsg              = VOS_NULL_PTR;
    MMCMM_DETACH_REQ_STRU              *pstInternalMsg      = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstInternalMsg  = (MMCMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_DETACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                          = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                   = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid                 = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulMsgName                     = MMCMM_DETACH_REQ;
    pstMsg->MsgHeader.ulLength                      = sizeof(MMCMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enDetachType                            = enDetachType;
    pstMsg->enDetachReason                          = enDetachReason;
    pstMsg->ulOpid                                  = ulOpid;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmModeChangeReq
 ��������  : ��MM�����ֻ�ģʽ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��10��
   ��    ��   : luokaihui /l00167671
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��4��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ӿ�

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU         *pstMsg             = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCGMM_MODE_CHANGE_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_MODE_CHANGE_REQ_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_MODE_CHANGE_REQ;
    pstMsg->enMsMode                    = enMsMode;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*******************************************************************************
 �� �� ��  : NAS_MMC_SndMmRatChangeInd
 ��������  : ��MM����MMCMM_RAT_CHANGE_IND��Ϣ
 �������  : enNetRatType:Ŀ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

1.��    ��   : 2013��3��27��
  ��    ��   : y00176023
  �޸�����   : DSDS GUNAS II��Ŀ��������
*******************************************************************************/
VOS_VOID NAS_MMC_SndMmRatChangeInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    MMCMM_RAT_CHANGE_IND_STRU          *pstMsg              = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCMM_RAT_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RAT_CHANGE_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmRatChangeInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_RAT_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_RAT_CHANGE_IND;
    pstMsg->enNetRatType                = enNetRatType;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLauReq
 ��������  : ��MM����LAU��Ϣ
 �������  : enLauReqReason - MMC����LAU��ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : �����ɺ��� DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
               ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
               ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmLauReq(
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason
)
{
    MMCMM_LAU_REQ_STRU                  *pstMsg             = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg          = (MMCMM_LAU_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LAU_REQ_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_LAU_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_LAU_REQ;
    pstMsg->enLauReqReason              = enLauReqReason;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLteSysinfoInd
 ��������  : NAS֪ͨmm��LTEϵͳ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��19��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��28��
    ��    ��   : W00166186
    �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndMmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{

    /* ����ԭ������ָ�� */
    MMC_MM_LTE_SYS_INFO_IND_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMC_MM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLteSysinfoInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstLmmSysInfoMsg, sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU));

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId       = MMCMM_LTE_SYS_INFO_IND;
    pstMsg->ulLength        = sizeof(MMC_MM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmAttachInd
 ��������  : MMC��MM֪ͨ��ǰLMM��attach���
 �������  : LMM_MMC_ATTACH_IND_STRU        *pstActionResultInd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU            *pstAttachInd
)
{
    MMCMM_LMM_ATTACH_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_ATTACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_ATTACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmAttachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstAttachInd, sizeof(MMCMM_LMM_ATTACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_ATTACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_ATTACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmTauResultInd
 ��������  : MMC��MM֪ͨ��ǰLMM��TAUע����
 �������  : LMM_MMC_ATTACH_IND_STRU        *pstTauResultInd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstTauResultInd
)
{
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_TAU_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTauResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstTauResultInd, sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_TAU_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_TAU_RESULT_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmSerResultnd
 ��������  : MMC��MM֪ͨ��ǰLMM��service request���
 �������  : LMM_MMC_SERVICE_RESULT_IND_STRU        *pstSerInd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerInd
)
{
    MMCMM_LMM_SERVICE_RESULT_IND_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCMM_LMM_SERVICE_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmSerResultnd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstSerInd, sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_SERVICE_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_SERVICE_RESULT_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmMtDetachInd
 ��������  : MMC��MM֪ͨ��ǰLMM������ȥע����
 �������  : LMM_MMC_DETACH_IND_STRU            *pstDetachInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��5��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseIV����
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
)
{
    MMCMM_LMM_MT_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCMM_LMM_MT_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_MT_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmMtDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstDetachInd, sizeof(MMCMM_LMM_MT_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_MT_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_MT_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmLocalDetachInd
 ��������  : MMC��MM֪ͨ��ǰLMM�ı���ȥע����
 �������  : LMM_MMC_DETACH_IND_STRU            *pstDetachInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��7��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
)
{
    MMCMM_LMM_LOCAL_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCMM_LMM_LOCAL_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstDetachInd, sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_LOCAL_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_LOCAL_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmMoDetachInd
 ��������  : MMC��MM֪ͨ��ǰLMM��UEȥע����
 �������  : LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
)
{
    MMCMM_LMM_MO_DETACH_IND_STRU       *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCMM_LMM_MO_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_MO_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndMmLmmMoDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstDetachCnf, sizeof(MMCMM_LMM_MO_DETACH_IND_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_MO_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_MO_DETACH_IND;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmLmmTimerStateNotify
 ��������  : MMC��MM֪ͨ��ǰLMM�Ķ�ʱ��״̬
 �������  : pstTimerStatusNotify - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��20��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
)
{
    MMCMM_LMM_TIMER_STATE_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ�ڴ���� */
    pstMsg              = (MMCMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTimerStatusNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMsg, pstTimerStatusNotify, sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU));

    /* �޸���Ϣͷ */
    pstMsg->ulLength        = sizeof(MMCMM_LMM_TIMER_STATE_NOTIFY_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_MM;
    pstMsg->ulMsgId         = MMCMM_LMM_TIMER_STATE_NOTIFY;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMmSrvccInfoNotify
 ��������  : ��MM����SRVCC֪ͨ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndMmSrvccInfoNotify(VOS_VOID)
{
    MMCMM_SRVCC_INFO_NOTIFY_STRU       *pstSndMmSrvccMsg      = VOS_NULL_PTR;

    pstSndMmSrvccMsg  = (MMCMM_SRVCC_INFO_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndMmSrvccMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmSrvccInfoNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstSndMmSrvccMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMmSrvccMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMmSrvccMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMmSrvccMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;

    /* ��д��Ϣ��� */
    pstSndMmSrvccMsg->MsgHeader.ulMsgName         = MMCMM_SRVCC_INFO_NOTIFY;
    pstSndMmSrvccMsg->MsgHeader.ulLength          = sizeof(MMCMM_SRVCC_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndMmSrvccMsg);
    return;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

