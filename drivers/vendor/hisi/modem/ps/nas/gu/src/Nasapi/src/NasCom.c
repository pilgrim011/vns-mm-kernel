/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : NasCom.c
  Description  : NAS��������
  Function List: NAS_EventReport

  History:
      1.  s46746   2008.04.29 �°�����

*******************************************************************************/
#include "vos.h"
#include "NasComm.h"
#include "MM_Inc.h"
#include "NasMmlCtx.h"
#include "SmInclude.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_COM_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/* ��RABM_TIMER_NAME_FD_FLUX_DETECT��ʱ��Ϊ32k��ʱ�� */
/* ��ǰĬ�Ϲ�32Kʱ�ӣ����������±���ȷָ�� */
NAS_TIMER_PRECISION_STRU g_stNasTimerPrcision[]=
{
   {WUEPS_PID_MMA,  MMA_TIMER_FOR_PC_REPLAY,            VOS_TIMER_NO_PRECISION},
};

/*lint -e651*/
NAS_CONVERT_MTC_SESSION_STRU             g_stNasConvertMtcSessiontype[] =
{
    {RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL, MTC_SESSION_TYPE_CS_MO_NORMAL_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL, MTC_SESSION_TYPE_CS_MO_EMERGENCY_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_SS, MTC_SESSION_TYPE_CS_MO_SS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_SMS, MTC_SESSION_TYPE_CS_MO_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL, MTC_SESSION_TYPE_CS_MT_NORMAL_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK, MTC_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_SS, MTC_SESSION_TYPE_CS_MT_SS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_SMS, MTC_SESSION_TYPE_CS_MT_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_LAU, MTC_SESSION_TYPE_CS_LAU, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_DETACH, MTC_SESSION_TYPE_CS_DETACH, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB, MTC_SESSION_TYPE_CS_MO_NORMAL_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB, MTC_SESSION_TYPE_CS_MO_EMERGENCY_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_CS_MT_CSFB, MTC_SESSION_TYPE_CS_MT_CSFB, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL, MTC_SESSION_TYPE_PS_CONVERSAT_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_STREAM_CALL, MTC_SESSION_TYPE_PS_STREAM_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL, MTC_SESSION_TYPE_PS_INTERACT_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL, MTC_SESSION_TYPE_PS_BACKGROUND_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, MTC_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_MO_SMS, MTC_SESSION_TYPE_PS_MO_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_MT_SMS, MTC_SESSION_TYPE_PS_MT_SMS, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_ATTACH, MTC_SESSION_TYPE_PS_ATTACH, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_RAU, MTC_SESSION_TYPE_PS_RAU, 0, 0},
    {RRC_NAS_SESSION_TYPE_PS_DETACH, MTC_SESSION_TYPE_PS_DETACH, 0, 0},
};
/*lint +e651*/


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_GetTimerPrecision
 ��������  : ��ȡ��ʱ�����ȷ�Χ
 �������  : Pid       -- ������ʱ����PID
             ulName    -- ��ʱ����
 �������  : ��
 �� �� ֵ  : VOS_TIMER_PRECISION_ENUM_UINT32 -- ��ʱ�����ȷ�Χ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��4��
    ��    ��   : w00167002
    �޸�����   : DTS2013090403562:NAS��ʱ��������Ҫ����32K��ʱ������MM/MMA/SMS
                ģ���ѭ����ʱ���޸�Ϊ��ѭ����ʱ����

                ��ʱ����Ϊ���֣�26M��ʱ����32K��ʱ����
                 26M��ʱ����ϵͳ�����٣��Ƽ�ʹ�ã�����DRX˯��ʱ��ֹͣ���������ܼ�ʱ��׼��
                 32K��ʱ����ϵͳ�����󣬲��Ƽ�ʹ�ã�����ʱ׼ȷ��
                 ��ѡ���޾���Ҫ��ʱ(VOS_TIMER_NO_PRECISION)������26M��ʱ��
                 �����о���Ҫ��ģ�����32K��ʱ����
             ��ʱ��ѡ������:
               1����IDLE̬�¶�ʱ����Ҫ��ʱ�������Ǿ�ȷ��ʱ�ģ����������쳣������ʱ����
                  �Լ���Ƶ�Ҫ����Զ�ʱ�ģ� Э�鶨ʱ���б�����Զ�ʱ�ģ�����˵�������
                  ��ʱ����ͨ��GCF������ �����ඨʱ����ʹ��32K��ʱ����
               2������IDLE��ʱ��������Ҫ���Զ�ʱ�ģ��ҵ�26M��ʱ����
               3����IDLE̬�Ķ�ʱ����ʹ��26M��ʱ��
*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 NAS_GetTimerPrecision(
    VOS_PID                             Pid,
    VOS_UINT32                          ulName
)
{
    VOS_UINT32                      i;
    VOS_TIMER_PRECISION_ENUM_UINT32 ulPrecision;

    /* Ĭ��Ϊ�о���Ҫ�󣬹���32Kʱ���� */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for(i=0; i<( sizeof(g_stNasTimerPrcision)/sizeof(NAS_TIMER_PRECISION_STRU) ); i++)
    {
        if (  (Pid == g_stNasTimerPrcision[i].ulPid)
            &&( (ulName == g_stNasTimerPrcision[i].ulTimerName)
              ||(NAS_TIMER_ALL == g_stNasTimerPrcision[i].ulTimerName)))
        {
            ulPrecision = g_stNasTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*****************************************************************************
 Function   : NAS_StartRelTimer
 Description: NAS������ʱ������.
 Input      : Pid       -- process ID of application
              ulLength  -- expire time. the metrics is millsecond
              ulName    -- timer name to be pass to application as a parameter
              ulParam   -- additional parameter to be pass to application
              ucMode    -- timer work mode
                           VOS_RELTIMER_LOOP  -- start periodically
                           VOS_RELTIMER_NOLOO -- start once time
              ulPrecision -- Timer Precision
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
 HISTORY    :
      1.  ��    ��   : 2011��06��24��
          ��    ��   : c00173809
          �޸�����   : �������ⵥ�ţ�DTS2011051202669��SM��T3380,T3390��ʱ��Ϣ��������ȷ��
      2. ��    ��   : 2013��06��28��
         ��    ��   : l00167671
         �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
*****************************************************************************/
VOS_UINT32 NAS_StartRelTimer(HTIMER *phTm, VOS_PID Pid, VOS_UINT32 ulLength,
    VOS_UINT32 ulName, VOS_UINT32 ulParam, VOS_UINT8 ucMode)
{
    VOS_UINT32                          ulRet;
    NAS_TIMER_OPERATION_STRU            stTimer;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    if ( ulLength >= VOS_TIMER_MAX_LENGTH )
    {
        ulLength = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_GetTimerPrecision(Pid, ulName);

    ulRet = VOS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode, ulPrecision);

    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = Pid;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;

    if ((WUEPS_PID_MMA == Pid) || (WUEPS_PID_RABM == Pid))
    {
        stTimer.MsgHeader.ulMsgName = ulParam;
    }
    else if (WUEPS_PID_SM == Pid)
    {
        if (0xff == ulParam)
        {
            stTimer.MsgHeader.ulMsgName = ulParam;
        }
        else
        {
            stTimer.MsgHeader.ulMsgName = ulName;
        }
    }
    else
    {
        stTimer.MsgHeader.ulMsgName = ulName;
    }

    stTimer.ulTimeAction        = NAS_TIMER_OPERATION_START;
    stTimer.ulTimeLen           = ulLength;

    DIAG_TraceReport(&stTimer);

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    NAS_TIMER_EventReport(stTimer.MsgHeader.ulMsgName,Pid, NAS_OM_EVENT_TIMER_OPERATION_START);
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

    return ulRet;
}

/*****************************************************************************
 Function   : NAS_StartRelTimer
 Description: MM��ֹͣ��ʱ������.
 Input      : Pid       -- process ID of application
              ulName    -- timer name to be pass to application as a parameter
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
   1. ��    ��   : 2013��06��28��
     ��    ��   : l00167671
     �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
 2. ��    ��   : 2013��07��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013071705401
*****************************************************************************/
VOS_UINT32 NAS_StopRelTimer(VOS_PID Pid, VOS_UINT32 ulName, HTIMER *phTm)
{
    VOS_UINT32                          ulRet;
    NAS_TIMER_OPERATION_STRU            stTimer;

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;

    if ((VOS_NULL_PTR != phTm)
     && (VOS_NULL_PTR != *phTm))
    {
        if ( VOS_OK != VOS_GetRelTmRemainTime(phTm, &ulTimerRemainLen ) )
        {
            ulTimerRemainLen = 0;
        }
    }

    if ((0 != ulTimerRemainLen) && (VOS_FALSE == g_ucSmTimerFiveExpireFlag))
    {
        NAS_TIMER_EventReport(ulName, Pid, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

    ulRet = VOS_StopRelTimer(phTm);


    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = Pid;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;

    stTimer.MsgHeader.ulMsgName = ulName;

    stTimer.ulTimeAction        = NAS_TIMER_OPERATION_STOP;
    stTimer.ulTimeLen           = 0x0;

    DIAG_TraceReport(&stTimer);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_ConvertCustomMsRelToPsUeRel
 ��������  : ��NV���ж��Ƶ�Э��汾ת��Ϊ�����ж����Э��汾��
 �������  : enCustomMsRel
 �������  : ��
 �� �� ֵ  : ת����Э��汾
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��15��
   ��    ��   : z40661
   �޸�����  :NV��NAS_Support_3GPP_Relase(8288)���õ�Э��汾ΪR7���뵱ǰUE֧�ֵ�Э��汾��һ��
 3.��    ��   : 2015��6��4��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_INT8 NAS_ConvertCustomMsRelToPsUeRel(
    NAS_MML_3GPP_REL_ENUM_UINT8         enCustomMsRel
)
{
    VOS_INT8                            cVersion;

    switch (enCustomMsRel)
    {
        case NAS_MML_3GPP_REL_R4:
            cVersion = PS_PTL_VER_R4;
            break;

        case NAS_MML_3GPP_REL_R5:
            cVersion = PS_PTL_VER_R5;
            break;

        case NAS_MML_3GPP_REL_R6:
            cVersion = PS_PTL_VER_R6;
            break;

        case NAS_MML_3GPP_REL_R7:
            cVersion = PS_PTL_VER_R7;
            break;

        case NAS_MML_3GPP_REL_R8:
            cVersion = PS_PTL_VER_R8;
            break;

        case NAS_MML_3GPP_REL_R9:
            cVersion = PS_PTL_VER_R9;
            break;

        case NAS_MML_3GPP_REL_R10:
            cVersion = PS_PTL_VER_R10;
            break;

        case NAS_MML_3GPP_REL_R11:
            cVersion = PS_PTL_VER_R11;
            break;

        default:
            cVersion = PS_UE_REL_VER;
            break;
    }

    return cVersion;
}

/*****************************************************************************
 �� �� ��  : NAS_Common_Get_Supported_3GPP_Version
 ��������  : ��ȡ��ǰ�����罻����Э��汾
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��05��10��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��06��17��
    ��    ��   : o00132663
    �޸�����   : �����ն˿����������޸�
  3.��    ��   : 2011��07��26��
    ��    ��   : z00161729
    �޸�����   : MMC_Com.c�ļ�ɾ���ƶ�
  5.��    ��   : 2012��03��15��
    ��    ��   : s46746
    �޸�����   : ����R7��R8������Ϣ��Ԫ,ʹ��Э��汾����
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2015��7��4��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId)
{
    VOS_INT8                           cVersion;
    VOS_INT8                           cVersionFromNV;
    NAS_MML_MS_3GPP_REL_STRU          *pstMs3GppRel     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;
    NAS_MML_NETWORK_3GPP_REL_STRU     *pstNetwork3GppRel= VOS_NULL_PTR    ;

    cVersion            = PS_PTL_VER_R11;
    pstMs3GppRel        = NAS_MML_GetMs3GppRel();
    enRatType           = NAS_MML_GetCurrNetRatType();
    pstNetwork3GppRel   = NAS_MML_GetNetwork3GppRel();

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        cVersionFromNV = NAS_ConvertCustomMsRelToPsUeRel(pstMs3GppRel->enMsGsmRel);

        if (cVersionFromNV > PS_PTL_VER_R11)
        {
            cVersion = PS_PTL_VER_R11;
        }
        else
        {
            cVersion = cVersionFromNV;
        }

        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
        {
            switch (pstMs3GppRel->enMsMscRel)
            {
                case PS_CUSTOM_REL_VER_R97:
                    cVersion = PS_PTL_VER_PRE_R99;
                    break;

                case PS_CUSTOM_REL_VER_AUTO:
                    if (GRRMM_MSC_RELEASE98_OR_OLDER == pstNetwork3GppRel->enNetMscRel)
                    {
                        cVersion = PS_PTL_VER_PRE_R99;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {/* PS DOMAIN */
            switch ( pstMs3GppRel->enMsSgsnRel)
            {
                case PS_CUSTOM_REL_VER_R97:
                    cVersion = PS_PTL_VER_PRE_R99;
                    break;

                case PS_CUSTOM_REL_VER_AUTO:
                    if (GRRMM_SGSN_RELEASE98_OR_OLDER == pstNetwork3GppRel->enNetSgsnRel)
                    {
                        cVersion = PS_PTL_VER_PRE_R99;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else
    {/* WCDMA */
        cVersionFromNV = NAS_ConvertCustomMsRelToPsUeRel(pstMs3GppRel->enMsWcdmaRel);

        if (cVersionFromNV > PS_PTL_VER_R11)
        {
            cVersion = PS_PTL_VER_R11;
        }
        else
        {
            cVersion = cVersionFromNV;
        }
    }


    return cVersion;
}


/*****************************************************************************
 �� �� ��  : NAS_ImsiToImsiStr
 ��������  : ��ȫ�ֱ�����Imsiת�����ִ���ʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��  : 2009��7��3��
   ��    ��  : h44270
   �޸�����  : creat function
*****************************************************************************/
VOS_VOID NAS_ImsiToImsiStr(VOS_CHAR  *pcImsi)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucImsi;

    pucImsi = NAS_MML_GetSimImsi();

    for (i = 1; i < 9; i++)
    {
        /*lint -e961*/
        if (1 == i)
        {
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        else
        {
            *pcImsi++ = (pucImsi[i] & 0x0f) + 0x30;
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        /*lint +e961*/
    }
}


/*****************************************************************************
 �� �� ��  : NAS_PreventTestImsiRegFlg
 ��������  : ��NV���ʱ���ж���ǰ��IMSI�Ƿ��ǲ��ԺŶΣ��ǵĻ�����VOS_TRUE,
              ��������£�������VOS_FALSE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��7��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_BOOL NAS_PreventTestImsiRegFlg(VOS_VOID)
{
    VOS_CHAR                            *pcLabImsi1="00101";
    VOS_CHAR                            *pcLabImsi2="00102";
    VOS_CHAR                            *pcLabImsi3="00201";
    VOS_INT                             iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;
    VOS_UINT32                          ulResult;
    NAS_PREVENT_TEST_IMSI_REG_STRU      stTestImsiFlg;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stTestImsiFlg.ucStatus = VOS_FALSE;
    stTestImsiFlg.ucActFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_PREVENT_TEST_IMSI_REG, &ulLength);
    if (ulLength > sizeof(stTestImsiFlg))
    {
        return VOS_FALSE;
    }
    ulResult = NV_Read(en_NV_Item_PREVENT_TEST_IMSI_REG,
                       &stTestImsiFlg,
                       ulLength);
    if (NV_OK != ulResult)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_PreventTestImsiRegFlg:WARNING: Read en_NV_Item_PREVENT_TEST_IMIS_REG Err");
        return VOS_FALSE;
    }

    /* stTestImsiFlg.ucStatus = 0; */
    /* stTestImsiFlg.ucActFlg = 0; */

    /* ��NV��������£��ж��Ƿ�������ĺŶ� */
    if ((VOS_TRUE == stTestImsiFlg.ucStatus)
     && (VOS_TRUE == stTestImsiFlg.ucActFlg))
    {
        NAS_ImsiToImsiStr(acTmpImsi);

        iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcLabImsi1, 5);
        iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcLabImsi2, 5);
        iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcLabImsi3, 5);

        if ((0 == iImsiCmpRslt1)
          ||(0 == iImsiCmpRslt2)
          ||(0 == iImsiCmpRslt3))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_ConvertSessionTypeToMTCFormat
 ��������  : ��NAS Session Typeת����MTC��Session Type
 �������  : RRC_NAS_SESSION_TYPE_ENUM_UINT8
 �������  : MTC_SESSION_TYPE_ENUM_UINT8
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 NAS_ConvertSessionTypeToMTCFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType,
    MTC_SESSION_TYPE_ENUM_UINT8        *penMtcSessionType
)
{
    VOS_UINT32                          ulMaxIndex;
    VOS_UINT32                          i;

    ulMaxIndex  = sizeof(g_stNasConvertMtcSessiontype) / sizeof(NAS_CONVERT_MTC_SESSION_STRU);

    for (i = 0; i < ulMaxIndex; i++)
    {
        if (enNasSessionType == g_stNasConvertMtcSessiontype[i].enNasSessionType)
        {
            *penMtcSessionType = g_stNasConvertMtcSessiontype[i].enMtcSessionType;
            return VOS_OK;
        }
    }

    *penMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_ConvertSessionTypeToMTCFormat:ERROR: Convert session type err!");

    return VOS_ERR;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

