/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccSndImsa.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��01��26��
  ��������   : MSCC����IMSA��Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccSndImsa.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaMsccInterface.h"
#endif
#include "MsccMmcInterface.h"
#include "NasMsccCtx.h"
#include "NasMntn.h"
#include "NasUtranCtrlCtx.h"
#include "NasComm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_IMSA_C

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndImsaSrvInfoNotify
 ��������  : ������Ϣ��IMSA
 �������  : enPsServiceStatus  --PS�ķ���״̬
             ucRoamingValid     --���α���Ƿ���Ч
             ucRoamingFlg       --���α��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��24��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: �������α��
 3.��    ��   : 2016��4��5��
   ��    ��   : z00359541
   �޸�����   : MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���: ����פ��С����Ϣ�͵�ǰ
                �Ƿ������̴�����SERVICE CHANGE IND
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaSrvInfoNotify(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enCurPsServiceSta,
    VOS_UINT8                           ucRoamingValid,    
    VOS_UINT8                           ucRoamingFlg       
)
{
    MSCC_IMSA_SERVICE_CHANGE_IND_STRU  *pstSndMsg    = VOS_NULL_PTR;
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstNwCapInfo = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU             *pstSysInfo   = VOS_NULL_PTR;

    pstSysInfo   = NAS_MSCC_GetCurrSysInfo();

    /* �����ڴ�  */
    pstSndMsg = (MSCC_IMSA_SERVICE_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaSrvInfoNotify: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = UEPS_PID_MSCC;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = PS_PID_IMSA;
    pstSndMsg->ulLength           = sizeof(MSCC_IMSA_SERVICE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgId            = ID_MSCC_IMSA_SERVICE_CHANGE_IND;

    /* set PS service status */
    pstSndMsg->enPsServiceStatus  = (MSCC_IMSA_SERVICE_STATUS_ENUM_UINT8)enCurPsServiceSta;

    /* set PS sim valid */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        pstSndMsg->ucPsSimValid = VOS_FALSE;
    }
    else
    {
        pstSndMsg->ucPsSimValid = VOS_TRUE;
    }

    /* fill RAT */
    pstSndMsg->enRat              = (MSCC_IMSA_RAT_TYPE_ENUM_UINT8)pstSysInfo->st3gppSysInfo.enSysMode;

    pstSndMsg->bitRoamingValid    = ucRoamingValid;
    pstSndMsg->ucRoamingFlg       = ucRoamingFlg;

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        /* by the way, here get lte network capability information */
        pstNwCapInfo              = NAS_MSCC_GetLteNwCapInfo();
    }
    else
    {
        /* by the way, here get GU network capability information */
        pstNwCapInfo              = NAS_MSCC_GetGuNwCapInfo();
    }

    /* fill in network capability infomation */
    pstSndMsg->enEmsInd           = (MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8)pstNwCapInfo->enNwEmcBsCap;
    pstSndMsg->enImsVoPsInd       = (MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8)pstNwCapInfo->enNwImsVoCap;

    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    /* set PLMN identity */
    pstSndMsg->stCampedCellInfo.stPlmnId.ulMcc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMcc;
    pstSndMsg->stCampedCellInfo.stPlmnId.ulMnc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMnc;

    /* set cell identity */
    pstSndMsg->stCampedCellInfo.ulCellId           = pstSysInfo->st3gppSysInfo.ulCellId;

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        /* IMSAҪ��usTac�ĸ�8bit��ϵͳ��Ϣ�е�Tac����8bit��ϵͳ��Ϣ�е�TacCnt */
        pstSndMsg->stCampedCellInfo.usTac          = pstSysInfo->st3gppSysInfo.usLac;
    }
    else
    {
        /* Get LAC */
        pstSndMsg->stCampedCellInfo.usLac          = pstSysInfo->st3gppSysInfo.usLac;
    }

    if ((MSCC_IMSA_NORMAL_SERVICE == pstSndMsg->enPsServiceStatus)
     && (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode))
    /* NORMAL SERVICE����4G�����£�����������Ͳ���Ч */
    {
        pstSndMsg->bitRegSuccProcTypeValid         = VOS_TRUE;
        pstSndMsg->enRegSuccProcType               = NAS_MSCC_GetPsRegSuccProcType();
    }
    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* send message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndImsaCampInfoChangeInd
 ��������  : ������Ϣ��IMSA, ָʾפ����Ϣ(�������λ�CGI��Ϣ)�����ı�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaCampInfoChangeInd(VOS_VOID)
{
    MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU                    *pstSndMsg    = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU                                 *pstSysInfo   = VOS_NULL_PTR;

    pstSysInfo   = NAS_MSCC_GetCurrSysInfo();

    /* �����ڴ�  */
    pstSndMsg = (MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                    sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaCampInfoChangeInd: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(pstSndMsg, 0, sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU));

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = UEPS_PID_MSCC;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = PS_PID_IMSA;
    pstSndMsg->ulLength           = sizeof(MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgId            = ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND;


    /* set PLMN identity */
    pstSndMsg->stPlmnId.ulMcc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.ulMnc     = pstSysInfo->st3gppSysInfo.stPlmnId.ulMnc;

    /* set cell identity */
    pstSndMsg->ulCellId           = pstSysInfo->st3gppSysInfo.ulCellId;

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        if (NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_TDD == pstSysInfo->st3gppSysInfo.enLmmAccessType)
        {
            pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD;
        }
        else
        {
            pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD;
        }

        /* IMSAҪ��usTac�ĸ�8bit��ϵͳ��Ϣ�е�Tac����8bit��ϵͳ��Ϣ�е�TacCnt */
        pstSndMsg->usTac          = pstSysInfo->st3gppSysInfo.usLac;
    }
    else
    {
        if (NAS_MSCC_SYS_MODE_WCDMA == pstSysInfo->st3gppSysInfo.enSysMode)
        {
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD;
            }
            else
            {
                pstSndMsg->enAccessType = MSCC_IMSA_ACCESS_TYPE_UTRAN_TDD;
            }
        }
        else
        {
            pstSndMsg->enAccessType     = MSCC_IMSA_ACCESS_TYPE_GERAN;
        }

        /* Get LAC */
        pstSndMsg->usLac          = pstSysInfo->st3gppSysInfo.usLac;
    }

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* send message */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndImsaStopReq
 ��������  : ��imsa���͹ػ�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��26��
    ��    ��   : f00179208
    �޸�����   : DTS2015052504823�����Ӵ�IMSЭ��ջ�Ĳ�������
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaStopReq(
    MSCC_IMSA_STOP_TYPE_ENUM_UINT32     enStopType
)
{
    MSCC_IMSA_STOP_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_IMSA_STOP_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaStopReq: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_STOP_REQ;

    pstMsg->enStopType       = enStopType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);
	
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndImsaStartReq
 ��������  : ��imsa���Ϳ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��26��
    ��    ��   : f00179208
    �޸�����   : DTS2015052504823�����Ӵ�IMSЭ��ջ�Ĳ�������
*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaStartReq(
    MSCC_IMSA_START_TYPE_ENUM_UINT32    enStartType
)
{
    MSCC_IMSA_START_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_IMSA_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaStartReq: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_START_REQ;

    pstMsg->enStartType      = enStartType;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    NAS_TRACE_HIGH("SEND MSG!");

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndImsaVoiceDomainChangeInd
 ��������  : ��imsa����ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SndImsaVoiceDomainChangeInd(
    MSCC_IMSA_VOICE_DOMAIN_ENUM_UINT32                      enVoiceDomain
)
{
    MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndImsaVoiceDomainChangeInd: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_IMSA;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = UEPS_PID_MSCC;
    pstMsg->ulLength         = sizeof(MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->enVoiceDomain    = enVoiceDomain;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



