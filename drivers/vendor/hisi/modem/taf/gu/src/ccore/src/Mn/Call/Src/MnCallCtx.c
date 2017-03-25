
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MNCallCtx.c
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��03��03��
  ����޸�   :
  ��������   : MN CALL CTX�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallCtx.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-17, begin */
#include "MnCallMgmt.h"
#include "MnCallTimer.h"
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-17, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MMC CTX,���ڱ���MMC״̬��,������ */
MN_CALL_CONTEXT_STRU                    g_stMnCallCtx;


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCtx
 ��������  : ��ȡ��ǰCALL��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰcall��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��3��
   ��    ��   : s62952
   �޸�����   : �����ɺ���

*****************************************************************************/
MN_CALL_CONTEXT_STRU*  MN_CALL_GetCtx( VOS_VOID )
{
    return &(g_stMnCallCtx);
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCustomCfgInfo
 ��������  : ��ȡCALL�б������Զ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CALL�б������Զ���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��3��
   ��    ��   : s62952
   �޸�����   : �����ɺ���

*****************************************************************************/
MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg);
}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallRedialCfg
 ��������  : ��ȡCALL�ز����ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����CALL�����ز�������Ϣ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��2��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
TAF_CALL_REDIAL_CFG_STRU *MN_CALL_GetCallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stCallRedialCfg);
}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCcwaCtrlMode
 ��������  : ��ȡ���еȴ��Ŀ���ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_CCWA_CTRL_MODE_ENUM_U8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CALL_CCWA_CTRL_MODE_ENUM_U8 TAF_CALL_GetCcwaCtrlMode(VOS_VOID)
{
    return MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCcwaCtrlMode
 ��������  : ���ú��еȴ��Ŀ���ģʽ
 �������  : TAF_CALL_CCWA_CTRL_MODE_ENUM_U8    enCcwaCtrlMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CALL_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
)
{
    MN_CALL_GetCustomCfgInfo()->enCcwaCtrlMode = enCcwaCtrlMode;

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetAppCfgInfo
 ��������  : ��ȡCALL�б����AP���õ���Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_APP_CFG_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CALL_APP_CFG_INFO_STRU* MN_CALL_GetAppCfgInfo(VOS_VOID)
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stAppCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCcwaiMode
 ��������  : ����CCWAI��mode
 �������  : TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CALL_SetCcwaiMode(
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode
)
{
    MN_CALL_GetAppCfgInfo()->enCcwaiMode = enCcwaiMode;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCcwaiMode
 ��������  : ��ȡCCWAI��mode
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CALL_CCWAI_MODE_ENUM_UINT8 TAF_CALL_GetCcwaiMode(VOS_VOID)
{
    return MN_CALL_GetAppCfgInfo()->enCcwaiMode;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCcwaiMode
 ��������  : ��ȡCCWAI��mode
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CALL_CCWAI_MODE_ENUM_UINT8 TAF_GetCcwaiMode(VOS_VOID)
{
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;

    enCcwaiMode = TAF_CALL_GetCcwaiMode();

    TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_GetCcwaiMode ", enCcwaiMode);

    return enCcwaiMode;
}

/*****************************************************************************
 �� �� ��  : TAF_SetCcwaCtrlMode
 ��������  : ���ú��еȴ��Ŀ���ģʽ
 �������  : TAF_CALL_CCWA_CTRL_MODE_ENUM_U8    enCcwaCtrlMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-3-16
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
)
{
    TAF_CALL_SetCcwaCtrlMode(enCcwaCtrlMode);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetAtaReportOkAsyncFlag
 ��������  : ��ȡata�Ƿ��첽�ϱ�ok��ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ata�Ƿ��첽�ϱ�ok

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : ��������
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID)
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetAtaReportOkAsyncFlag
 ��������  : ����ata�Ƿ��첽�ϱ�ok��ʶ
 �������  : ucAtaReportOkAsyncFlag - ata�Ƿ��첽�ϱ�ok
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag
                           = ucAtaReportOkAsyncFlag;
    return;
}



/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallRedialSupportFlg
 ��������  : ��ȡ�Ƿ�֧�ֺ����ؽ����ܱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ֧�ֺ����ؽ�����
             VOS_FALSE - ��֧�ֺ����ؽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��2��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID)
{
    return (MN_CALL_GetCallRedialCfg()->ucCallRedialSupportFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCallRedialForDiscSupportFlg
 ��������  : ��ȡ�Ƿ�֧�ֻ���disconnectԭ��ֵ�ĺ����ؽ����ܱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ֧�ֻ���disconnectԭ��ֵ�ĺ����ؽ�����
                        VOS_FALSE - ��֧�ֻ���disconnectԭ��ֵ�ĺ����ؽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_GetCallRedialForDiscSupportFlg(VOS_VOID)
{
    return (MN_CALL_GetCallRedialCfg()->stCallRedialDiscCfg.ucCallRedialForDiscSupportFlg);
}

/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_CALL_GetEcallRedialCfg
 ��������  : ��ȡeCall�ز����ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����eCall�����ز�������Ϣ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��2��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
MN_CALL_REDIAL_CFG_STRU *TAF_CALL_GetEcallRedialCfg(VOS_VOID)
{
    return &(MN_CALL_GetCustomCfgInfo()->stCallRedialCfgInfo.stEcallRedialCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetEcallRedialSupportFlg
 ��������  : ��ȡeCall�Ƿ�֧�ֺ����ز�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ֧�ֺ����ؽ�����
             VOS_FALSE - ��֧�ֺ����ؽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��2��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetEcallRedialSupportFlg(VOS_VOID)
{
    return (TAF_CALL_GetEcallRedialCfg()->ucCallRedialSupportFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetEcallMsdTransStatus
 ��������  : ��ȡ����eCall MSD���ݴ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����eCall MSD���ݴ���״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 TAF_CALL_GetEcallMsdTransStatus(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetEcallMsdTransStatus
 ��������  : ����eCall MSD����״̬
 �������  : enEcallTransStatus -- eCall MSD����״̬
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 enEcallTransStatus)
{
    MN_CALL_GetCtx()->stEcallCtx.enEcallTransStatus = enEcallTransStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetWaitingMtEcallFlag
 ��������  : ��ȡ�ȴ�MT eCall��־λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���صȴ�MT eCall��־λ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetWaitingMtEcallFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetWaitingMtEcallFlag
 ��������  : ���µȴ�MT eCall flag��־
 �������  : ucWaitMtEcallFlag -- �ȴ�mt eCall��־λ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_SetWaitingMtEcallFlag(VOS_UINT8 ucWaitMtEcallFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucWaitMtEcallFlag = ucWaitMtEcallFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetInternalHangUpFlag
 ��������  : �����ڲ��һ���־
 �������  : ucInternalHangUpFlag -- �ڲ��һ����
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_SetInternalHangUpFlag(VOS_UINT8 ucInternalHangUpFlag)
{
    MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag = ucInternalHangUpFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetInternalHangUpFlag
 ��������  : ��ȡ�ڲ��һ���־
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ڲ��һ���־

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetInternalHangUpFlag(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ucInternalHangUpFlag);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_ResetEcallPeriodRemainTimerLen
 ��������  : reset�ز�ʱ��
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_ResetEcallPeriodRemainTimerLen(VOS_VOID)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = \
        TAF_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_UpdateEcallPeriodRemainTimerLen
 ��������  : ����eCall periodʣ��ʱ��
 �������  : ulEcallPeriodTimerLen ���� eCall periodʣ��ʱ��

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_UpdateEcallPeriodRemainTimerLen(VOS_UINT32 ulEcallPeriodTimerLen)
{
    MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen = ulEcallPeriodTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_UpdateEcallPeriodRemainTimerLen
 ��������  : ��ȡeCall periodʣ��ʱ��
 �������  : ��

 �������  : ��
 �� �� ֵ  : ulEcallPeriodTimerLen ���� eCall periodʣ��ʱ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT32 TAF_CALL_GetEcallPeriodRemainTimerLen(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stEcallCtx.ulEcallPeriodTimerLen);
}
#endif

/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_CALL_GetRedialSupportFlg
 ��������  : ��ȡ�����ز�֧�ֱ�־
 �������  : ucCallId -- ���б�ʶ
 �������  : ��
 �� �� ֵ  : ���غ����ز���־
             VOS_TURE  - ֧���ز�
             VOS_FALSE - ��֧���ز�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��8��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT32 TAF_CALL_GetRedialSupportFlg(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulRedialSupportFlg;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        ulRedialSupportFlg = (VOS_UINT32)TAF_CALL_GetEcallRedialSupportFlg();
    }
    else
#endif
    {
        ulRedialSupportFlg = (VOS_UINT32)MN_CALL_GetCallRedialSupportFlg();
    }

    return ulRedialSupportFlg;
}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
/*lint -restore */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetBufferedMsg
 ��������  : ��ȡ��ǰCALL�����setup��Ϣ��rel��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CALL�б����setup��Ϣ��rel��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMnCallBufferedMsg);
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ClearBufferedMsg
 ��������  : ��ջ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    PS_MEM_SET(pstMsgBuff, 0x0, sizeof(MN_CALL_MSG_BUFF_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetDiscCause
 ��������  : ��������disconnect�Ҷ�ԭ��ֵ
 �������  : enDiscCause -- disconnectԭ��ֵ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetDiscCause(NAS_CC_CAUSE_VALUE_ENUM_U32 enDiscCause)
{
    MN_CALL_GetCtx()->enDiscCause= enDiscCause;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDiscCause
 ��������  : ��ȡ����disconnect�Ҷ�ԭ��ֵ

 �������  : enDiscCause -- disconnectԭ��ֵ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_CC_CAUSE_VALUE_ENUM_U32 TAF_CALL_GetDiscCause(VOS_VOID)
{
    return (MN_CALL_GetCtx()->enDiscCause);
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_CALL_SetSrvccState
 ��������  : ����SRVCC״̬

 �������  : enSrvccState -- SRVCC״̬

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState)
{
    MN_CALL_GetCtx()->enSrvccState = enSrvccState;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetSrvccState
 ��������  : ��ȡSRVCC״̬

 �������  : enSrvccState -- SRVCC״̬

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID)
{
    return (MN_CALL_GetCtx()->enSrvccState);
}
#endif

/*****************************************************************************
 �� �� ��  : MN_CALL_InitCtx
 ��������  : ��ʼ��ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��23��
   ��    ��   : y00245242
   �޸�����   : ����SRVCC���洦��
 3.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : NAS���������Ż�
*****************************************************************************/
VOS_VOID MN_CALL_InitCtx(VOS_VOID)
{
    PS_MEM_SET(MN_CALL_GetCtx(), 0x0, sizeof(g_stMnCallCtx));

    #if (FEATURE_ON == FEATURE_IMS)
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);

    TAF_CALL_SetCcwaiMode(VOS_TRUE);
    TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);
    TAF_WARNING_LOG2(WUEPS_PID_TAF, "MN_CALL_InitCtx ", TAF_CALL_CCWA_CTRL_BY_NW, VOS_TRUE);
#endif

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-16, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-16, end */
    TAF_CALL_SetDiscCause(NAS_CC_CAUSE_NW_SECTION_BEGIN);
}



/* Modified by z00234330 for PCLINT����, 2014-07-03, begin */
/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCallStatusControl
 ��������  : ������������֧��״̬

 �������  : ucCallStatus -- ����֧��״̬

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��03��
   ��    ��   : z00234330
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl = ucCallStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCallStatusControl
 ��������  : ��ȡ���������Ƿ�֧��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetMultiSimCallStatusControl
 ��������  : ���ö࿨����֧��״̬

 �������  : ucMultiSimCallStatus -- �࿨����֧��״̬

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��03��
   ��    ��   : z00234330
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl = ucMultiSimCallStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetMultiSimCallStatusControl
 ��������  : ��ȡ�࿨���������Ƿ�֧��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_SetVpCfgState
 ��������  : ���ÿ��ӵ绰����֧��״̬

 �������  : enVpStateStatus -- ���ӵ绰֧��״̬

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��03��
   ��    ��   : z00234330
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState = enVpStateStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetVpCfgState
 ��������  : ��ȡ���ӵ绰�Ƿ�֧��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState;
}


/* Modified by z00234330 for PCLINT����, 2014-07-03, end */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



