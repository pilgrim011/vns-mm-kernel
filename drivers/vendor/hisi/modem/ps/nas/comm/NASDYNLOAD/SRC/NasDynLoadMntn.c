/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasDynLoadMntn.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2015��8��27��
  ����޸�   :
  ��������   : ��̬���صĿ�ά�ɲ���ش���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasDynLoadMntn.h"
#include "gunas_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_DYNLOAD_MNTN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogRegisterInfo
 ��������  : ��ӡע����Ϣ
 �������  : enRatType:���뼼��
             ulPid    :PID
             ulInit   :��ʼ��������ַ
             ulUnload :ж�غ�����ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogRegisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit,
    VOS_UINT32                          ulUnload
)
{
    NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogRegisterInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_REGISTER;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulInit                      = ulInit;
    pstMsg->ulUnload                    = ulUnload;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogDeregisterInfo
 ��������  : ��ӡȥע����Ϣ
 �������  : enRatType:���뼼��
             ulPid    :PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogDeregisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid
)
{
    NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogDeregisterInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_DEREGISTER;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogExcuteInitInfo
 ��������  : ��ӡ����ģ��ĳ�ʼ����Ϣ
 �������  : pstDynloadCbRatInfo :��������н��뼼���ĳ�ʼ����ж�غ�����Ϣ
             enRatType           :���뼼��
             ulPid               :PID
             ulInit              :��ʼ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogExcuteInitInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit
)
{
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogExcuteInitInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulInit                      = ulInit;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogExcuteUnloadInfo
 ��������  : ��ӡ����ģ���ж����Ϣ
 �������  : pstDynloadCbRatInfo :��������н��뼼���ĳ�ʼ����ж�غ�����Ϣ
             enRatType           :���뼼��
             ulPid               :PID
             ulUnload            :ж�غ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogExcuteUnloadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulUnload
)
{
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU                *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogExcuteUnloadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD;

    pstMsg->enRatType                   = enRatType;
    pstMsg->ulPid                       = ulPid;
    pstMsg->ulUnload                    = ulUnload;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogStartDrvLoadInfo
 ��������  : ���õ�����ǰ���й����������Է�����
 �������  : NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo
             VOS_RATMODE_ENUM_UINT32             enRatType
             VOS_UINT32                          ulPid
             VOS_UINT32                          ulUnload
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogStartDrvLoadInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU                *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogStartDrvLoadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD;
    pstMsg->enRatMode                   = enRatType;

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LogFinishDrvLoadInfo
 ��������  : ���õ���������й����������Է�����
 �������  : NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogFinishDrvLoadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_INT32                           lLoadResult
)
{
    NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC, sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_LogFinishDrvLoadInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD;
    pstMsg->lLoadResult                 = lLoadResult;

    PS_MEM_CPY(pstMsg->astNasDynloadCbRatInfo, pstDynloadCbRatInfo, VOS_RATMODE_BUTT*sizeof(NAS_DYNLOAD_CB_RAT_INFO_STRU));

    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_Dynload_SoftReBoot_WithLineNoAndFileID
 ��������  : ��̬����ģ���������ø�λ����
 �������  : ulLineNO,
             ulFileID,
             stCnasRebootInfo

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_Dynload_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_DYNLOAD_REBOOT_INFO_STRU       *pstRebootInfo
)
{
    VOS_UINT32                                              ulSlice;
    VOS_UINT32                                              ulTaskTcb;
    NAS_REBOOT_MOD_ID_ENUM_UINT32                           ulModuleId;
    VOS_RATMODE_ENUM_UINT32                                 enRatMode;

    ulSlice   = VOS_GetSlice();

    if (UEPS_PID_MSCC == pstRebootInfo->ulPid)
    {
        ulModuleId = NAS_REBOOT_MOD_ID_DYNLOAD;
    }
    else
    {
        ulModuleId = NAS_REBOOT_MOD_ID_BUTT;
    }

    ulTaskTcb = VOS_GetTCBFromPid(pstRebootInfo->ulPid);

    enRatMode = pstRebootInfo->enRatMode;

    mdrv_om_system_error( (VOS_INT)(ulModuleId | enRatMode),
                          (VOS_INT)ulTaskTcb,
                          (VOS_INT)((ulFileID << 16) | ulLineNO),
                          (VOS_CHAR *)(&ulSlice),
                          sizeof(ulSlice) );
    return;

}





/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


