/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasMain.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : ��C�ļ�������GmmCasMainģ���ʵ��
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 �������ⵥA32D02368�޸�
  3. x51137 2006/4/28 A32D02889
  4. s46746 2006-05-08 �������ⵥA32D03487�޸�
  5. ��    ��   : 2006��9��19��
     ��    ��   : liurui id:40632
     �޸�����   : �������ⵥ�ţ�A32D05237
  6.��    ��   : 2006��10��9��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D05744
  7.x51137 2006/11/3 A32D06511
  8.��    ��   : 2006��11��20��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D07433
  9.��    ��   : 2007��3��30��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D09854
 10.��    ��   : 2007��10��13��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D13060
 11.��    ��   : 2007��11��22��
    ��    ��   : l00107747
    �޸�����   : ���ⵥ��:A32D13535
 12.��    ��   : 2007��12��2��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D13679,GMM������״̬��������յ�SM����������Ϣ���ظ�ʧ��
 13.��    ��   : 2007��12��28��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
 14.��    ��   : 2008��7��18��
    ��    ��   : luojian 00107747
    �޸�����   : �������ⵥ�ţ�AT2D03887,�޸�CS��Ч���������ģʽ�������
 15.��    ��   : 2008��08��05��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:AT2D04423,�ṩ����Ϣģ���ȡ��ǰPS�Ƿ���õ�API����
 16.��    ��   : 2008��9��23��
    ��    ��   : o00132663
    �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
 17.��    ��   : 2008��9��26��
    ��    ��   : x00115505
    �޸�����   : ���ⵥ��:AT2D05431
 18.��    ��    : 2008��10��15��
    ��    ��    : o00132663
    �޸�����    : ���ⵥ��:AT2D06211,������GMM_GPRS_SUSPENSION״̬ʱ��GMM_TIMER_5S��ʱ����ʱ�Ĵ���
 19.��    ��    : 2009��02��06��
    ��    ��    : o00132663
    �޸�����    : ���ⵥ��:AT2D08277,С����ѡ���µ�����ģʽ�ı��RAU�����쳣��
 20.��    ��   : 2009��05��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
 21.��    ��   : 2009��06��12��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D12345,A/Gb����ģʽ��ͨ��PS���Ͷ��ŷ��͵Ķ����������ȼ���ʵ��ֵ��1
 22.��    ��   : 2009��08��19��
    ��    ��   : x00115505
    �޸�����   : ���ⵥ��:AT2D13829,TLLIά������
 23.��    ��   : 2009��09��12��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�AT2D14432,HPLMN��ʱ������ϵͳ��ѡ�����г�ʱû����������HPLMN����
*****************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "MM_Share.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASMAIN_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/



/*****************************************************************************
   2 ȫ�ֱ�������
******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.1 ����ģ���ڲ�ȫ�ֱ��� ---------------*/
/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.2 ��ģ���ڲ�ȫ�ֱ��� -----------------*/
/*=======================================================*/
GMM_CAS_CTRL_STRU       gstGmmCasGlobalCtrl;        /* GMM CASȫ�ֿ��ƽṹ���� */

GMM_SUSPEND_CTRL_STRU   gstGmmSuspendCtrl;

VOS_UINT8     g_GmmInterRatCellReselect = 0;

/*****************************************************************************
   3 ����ʵ��
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM������Ϣ����        -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_CasMsgProc
 Description    : ˫ģ��ʽ��GMM������Ϣ����ں���
                  HSS 4100 V200R001 ������
                1.���������ϢRRMM_SUSPEND_IND
                2.�������ָ���ϢRRMM_RESUME_IND
                3.����GSM����ģʽ�£�GMM�Ľ�����Ϣ����
                4.����״̬�¶�ʱ����Ϣ���¼�����ת��
                5.����״̬��GMM��Ϣ���¼�����ת��
 Input          : struct MsgCB*     pMsg            �����Ϣָ��
 Output         :
 Return Value   : GMM_FAILURE       ����ʧ�ܣ�
                                    ����û�д������Ϣ����Ҫ������Ϣ���̴���
                  GMM_SUCCESS       ���سɹ�
                                    ����������ɣ�����Ҫ������Ϣ���̴���
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.��    ��    : 2007��3��30��
    ��    ��    : s46746
    �޸�����    : ���ⵥ��:A32D09854
  3.��    ��    : 2007��11��22��
    ��    ��    : l00107747
    �޸�����    : ���ⵥ��:A32D13535
  4.��    ��    : 2008��10��15��
    ��    ��    : o00132663
    �޸�����    : ���ⵥ��:AT2D06211,������GMM_GPRS_SUSPENSION״̬ʱ��GMM_TIMER_5S��ʱ����ʱ�Ĵ���
  5.��    ��   : 2009��5��9��
    ��    ��   : l00130025
    �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
  6.��    ��   : 2011��3��5��
    ��    ��   : ŷ����
    �޸�����   : DTS2011030300897������̬��T3312��ʱ��δ�����Ӧ��ʱ������״̬ȫ�ֱ�����
  7.��    ��   : 2011��8��18��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII���� HO����������LMM��GMM�ظ���ȫ�����Ļظ��Լ�������ʱ����ʱ��Ϣ�Ĵ���
  8.��    ��   : 2011��11��18��
    ��    ��   : w00167002
    �޸�����   : DTS2011110300229:G��CSonlyʱ��������CSʧ��3�κ��û�����ATTACH��
                  ʧ��4�˺��û���RPlmn��������PS���ע�ᡣ��GMM suspend״̬��
                  �յ���������󣬽�GMM״̬Ǩ�Ƶ�����״̬��
  9.��    ��   : 2012��02��29��
    ��    ��   : l00130025
    �޸�����   : DTS2012022906401:L->W Handover SMC��ϵͳ��Ϣǰ�յ�ʱû�д�������RAUʧ��
  10.��    ��   : 2012��3��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:ST����CSFB_MO_HO_SUCC001������L HO
                  ��W��δ�ϱ�ϵͳ��Ϣ��LAU�ɹ��������û��ĵ绰ҵ�񣬵绰ҵ��
                  ���ͷź�GMMδ�����������.
  11.��    ��   : 2012��7��27��
     ��    ��   : l65478
     �޸�����  : DTS2012072305591:L�л���U���һ��RAUʧ�ܣ�PDP drop
  12.��    ��   : 2013��02��08��
     ��    ��   : l00167671
     �޸�����   : DTS2013020607201
  13.��    ��   : 2013��1��22��
     ��    ��   : W00176964
     �޸�����   : DTS2013012105162:OOS�����յ�PS��detach��Ҫ���б���detach

  14.��    ��   : 2013��6��5��
     ��    ��   : w00167002
     �޸�����   : V9R1_SVLTE:�յ�DETACH /ATTACH REQ��Ϣ�������л���
  15.��    ��   : 2013��08��16��
     ��    ��   : l65478
     �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���
  16.��    ��   : 2014��3��28��
     ��    ��   : w00242748
     �޸�����   : DTS2014032508763:W������פ���󣬸ı�֧��LTE��������W��G������ѡ
                  ��GMM����RAU���������������㱨�Ĳ�һ�¡�
*****************************************************************************/
VOS_VOID GMM_CasMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* �ֲ��������� */
    REL_TIMER_MSG           *pTimerMsg;
    MSG_HEADER_STRU         *pNasMsgHeader;

    /* ��Ϣ�������� */
    *pucFollowOn = GMM_FALSE;                               /* Ĭ�ϲ��ٽ���ԭ��Ϣ��ں������� */

    /* Modified by wx270776 for OM�ں�, 2015-7-16, begin */
    if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    /* Modified by wx270776 for OM�ں�, 2015-7-16, end */
    {
        *pucFollowOn = GMM_TRUE;
        return;
    }

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;
    pTimerMsg = (REL_TIMER_MSG*)pMsg;

    /* �����л�״̬�µ���Ϣ */
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:

            GMM_CasMsgProc_GmmSuspendNormalService(pMsg, pucFollowOn);

            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                if (MMCGMM_GSM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_TRUE == GMM_IsCasGsmMode())
                    {
                        /* ������Ϣ�ַ��������������Ϣ */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_GSM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if(MMCGMM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_FALSE == GMM_IsCasGsmMode())
                    {
                        /* ������Ϣ�ַ��������������Ϣ */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (MMCGMM_SUSPEND_IND == pNasMsgHeader->ulMsgName)
                {
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SUSPEND_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
                {
                    GMM_BufferMsgDump();
                    Gmm_TimerStop(GMM_TIMER_SUSPENDED);
                    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_PLMN_SEARCH_INITIATED == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
                   ������פ��������������Attach */
                else if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* �յ�MMCGMM_DETACH_REQ��Ϣ���򲻽��л��� */
                else if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_SUSPENSION_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_SUSPENSION_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
            {
                if (RRMM_SECURITY_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else
            {
                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
             && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
             && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
            {
                if (WUEPS_PID_SM == pMsg->ulSenderPid)
                {
                    if (GMMSM_DATA_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_SMS == pMsg->ulSenderPid)
                {
                    if (PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_RABM == pMsg->ulSenderPid)
                {
                    if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else
                {
                }
            }
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;

        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_RESUME_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_RESUME_IND in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                /* ��ȡ������Ȧ���Ӷ� */
                if (VOS_TRUE == NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(pMsg, pucFollowOn))
                {
                    return;
                }
            }
            else if (VOS_PID_TIMER == pMsg->ulSenderPid)
            {
                if (GMM_TIMER_T3314 == pTimerMsg->ulName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Ready time expired in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
                {
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
                    Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
                    return;
                }
                else if (GMM_TIMER_1S == pTimerMsg->ulName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:GMM_TIMER_5S timer expired in GMM_GPRS_SUSPENSION state");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else
            {
            }

            /* ������Ϣȫ������ */
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;
        default:
            *pucFollowOn = GMM_TRUE;
            break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : GMM_SaveMsg
 ��������  : GMM�����յ�����Ϣ
 �������  : VOS_VOID *pMsg           - �յ�����Ϣָ��
 �������  : VOS_UINT8 *pucFollowOn   - �Ƿ���Ҫ��һ�������־
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��17��
    ��    ��   : ŷ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��10��29��
    ��    ��   : l00167671/�޿���
    �޸�����   : ���ⵥ�ţ�DTS2010100802035,��Ӷ�GMMSM_PDP_DEACTIVATED_IND�Ļ���
  3.��    ��   : 2011��03��3��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ�ţ�DTS2011022800037��G��ping����Ȼ���绰���л���Wʧ�ܺ��λ��˵�G���Ҷϵ绰.ping�������������ָ���
  4. ��    ��   : 2011��7��10��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5. ��    ��   : 2011��12��01��
     ��    ��   : w00166186
     �޸�����   : DTS2011112400118,CS�������̷���PS ATTACH��������ʱ����ERROR
  6. ��    ��   : 2012��4��20��
     ��    ��   : l00130025
     �޸�����   : DTS2012031502528��GMM GPRS Suspension״̬û�д���LuRsltInd��
                  W->G Rej 11->WԭС��ʱ,û����Attach�����º���SMҵ��ʧ��

 7.  ��    ��   : 2012��11��08��
	 ��    ��   : l00167671
     �޸�����   : DTS2012110508357,SUSPENSION״̬ʱ�յ�CS ONLY���������GAS resume indʧ�ܣ�������detach
*****************************************************************************/
VOS_VOID GMM_SaveMsg(VOS_VOID *pMsg, VOS_UINT8 *pucFollowOn)
{
    MSG_HEADER_STRU         *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;

    switch (pNasMsgHeader->ulSenderPid)
    {
    case WUEPS_PID_USIM:
        /*��Ȩ��Ӧ��Ϣ�������־ͣ��ʱ�������������³ɹ�������·�����Ӧ���̣�
          ���˵ȴ������ط���Ȩ*/
        if (USIMM_AUTHENTICATION_CNF == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;         /* ��ȴ���־                               */
            GMM_LOG_NORM("GMM_SaveMsg:Receive USIM AUTHENTICATION CNF,Discard.");
        }
        break;

    case WUEPS_PID_WRR:/*RRC_NAS_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of RRC.");
        break;

    case WUEPS_PID_RABM:/*GMM_RABM_AP_CLASS:
 */
        if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            /*GMM_BufferMsgReceive(pMsg);*/
            /* �л�����W����Ŵ���RABM��Ϣ��G��������RABM */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                /* ����л�֮ǰ�б��жϵ�Detach���̣��򲻻���RABM���ؽ����� */
                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    && ((GMM_DETACH_COMBINED == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL_NETMODE_CHANGE == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_WITH_IMSI == g_GmmGlobalCtrl.ucSpecProcHold)))
                {
                    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                }
                else
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg       = GMM_TRUE;
                    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_SERVICE_REQUEST_DATA_IDLE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                    g_GmmGlobalCtrl.usUplinkDataStatus  = ((GMMRABM_REESTABLISH_REQ_STRU *)pMsg)->usUplinkDataStatus;
                    #endif
                }
            }
            else
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);         /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                GMM_LOG_NORM("GMM_SaveMsg:Receive Rabm Reestablish In 2G,Discard.");
            }
        }
        /* RAU RSP��Ϣ��*/
        else if (ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_RAU_RSP);
        }
        else
        {
        }
        break;

    case WUEPS_PID_MMC:/*MMC_GMM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMCGMM_REGISTER_INITIATION:
            case MMCGMM_REL_REQ:
                *pucFollowOn = GMM_TRUE;
                break;
            case MMCGMM_ATTACH_REQ:
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case MMCGMM_DETACH_REQ:
                NAS_GMM_SaveDetachMsg(pMsg);
                break;

            case MMCGMM_MODE_CHANGE_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default:
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of MMC.");
                break;
        }
        break;

    case WUEPS_PID_MM:
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMGMM_CS_CONNECT_IND:
            case MMGMM_CM_SERVICE_REJECT_IND:
            case MMGMM_AUTHENTICATON_FAILURE_IND:
            case MMGMM_LU_RESULT_IND:

                *pucFollowOn = GMM_TRUE;
                break;

            default:
                 break;
        }
        break;

    case WUEPS_PID_SM:/*GMM_SM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case GMMSM_ESTABLISH_REQ:
            case GMMSM_PDP_DEACTIVATED_IND:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case GMMSM_DATA_REQ:
                /*GMM_BufferMsgReceive(pMsg);*/
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
                Gmm_BufSmDataReqMsg(pMsg);
                break;
            case GMMSM_PDP_STATUS_IND:
                Gmm_RcvSmPdpStatusInd(pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SM.");
                break;
        }
        break;

    case WUEPS_PID_SMS:/*GMM_SMS_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case PMMSMS_EST_REQ:
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
                break;
            case PMMSMS_UNITDATA_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SMS.");
                break;
        }
        break;

    case UEPS_PID_LL:/*LLC_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of LLC.");
        break;
    case UEPS_PID_GAS:/*GAS_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of GAS.");
        break;
    default :
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of others.");
        break;
    }
}

/*****************************************************************************
 �� �� ��  : GMM_SuspendMsgProc
 ��������  : GMM����̬���յ���Ϣ�Ĵ���
 �������  : struct MsgCB* pMsg           - �յ�����Ϣָ��
 �������  : VOS_UINT8     *pucFollowOn   - �Ƿ���Ҫ��һ�������־
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��17��
    ��    ��   : ŷ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��3��5��
    ��    ��   : ŷ����
    �޸�����   : DTS2011030300897������̬��T3312��ʱ��δ�����Ӧ��ʱ������״̬ȫ�ֱ�����
  3.��    ��   : 2011��8��18��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII���� HO����������LMM��GMM�ظ���ȫ�����Ļظ��Լ�������ʱ����ʱ��Ϣ�Ĵ���
  4.��    ��   : 2011��11��22��
    ��    ��   : w00166186
    �޸�����   : DTS2011112301504,BT����W2G_HOʧ��
  5.��    ��   :2014��4��2��
    ��    ��   :w00242748
    �޸�����   :DTS2014040310584:LTE��δ�����罻����ATTACH/TAU����ֹͣT3211/T3212/T3213;
                ֻ�������罻���󣬲Ž�T3211/T3212/T3213ֹͣ��
  6.��    ��   : 2014��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2014122201960:��L��SRVCC HO��G��HO��W,RABM�����ؽ�����������
                 ����RAU�������յ�ϵͳ��Ϣ���ٴη���RAU,��������REL����·������
                 �������޸�Ϊ��HO������������ʱ����ϵͳ��Ϣ��
*****************************************************************************/
VOS_VOID GMM_SuspendMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* �ֲ��������� */
    REL_TIMER_MSG           *pTimerMsg;

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;
        if ((GMM_TIMER_SUSPENDED == pTimerMsg->ulName) || (GMM_TIMER_T3314 == pTimerMsg->ulName) || (GMM_TIMER_TC_DELAY_SUSPEND_RSP == pTimerMsg->ulName) || (GMM_TIMER_T3323 == pTimerMsg->ulName))
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
        else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
            Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
            return;
        }
        /* ����״̬����Ҫ����LMM�İ�ȫ�����Ļظ���Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
        else if (GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
#endif

        else if (GMM_TIMER_HO_WAIT_SYSINFO == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_HO_WAIT_SYSINFO in SUSPENDED_NORMAL_SERVICE state.");
            return;

        }

        else
        {
            GMM_LOG_WARN("GMM_SuspendMsgProc:Receive unexpected timer expired msg.");
            return;
        }
    }

    GMM_SaveMsg((VOS_VOID *)pMsg, pucFollowOn);

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasNetModeChangeByRau
 Description    : ����ģʽ�ı�ʱGMM��Ҫ���е�RAU����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-07-26
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2006��9��19��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D05237
  3.��    ��   : 2006��11��20��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D07433
  4.��    ��   : 2008��7��18��
    ��    ��   : luojian 00107747
    �޸�����   : �������ⵥ�ţ�AT2D03887
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2014��3��14��
    ��    ��   : w00176964
    �޸�����   : DTS2014031207844:dereg_init״̬ʱNMO�ı���LARA�ı�ʱ����24008Э����Ҫ����RAU
*****************************************************************************/
VOS_VOID GMM_CasNetModeChangeByRau(
                GMM_NETMODE_CHG_TYPE ucNetChgTyp,
                VOS_UINT8            ucRaiChgFlg)
{
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsAttachAllow;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }
        break;

    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_TimerStop(GMM_TIMER_T3317);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;
        if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
        {/* ��ǰ����ΪSR_DATA */
            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* �������жϵ�SR����                       */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                           /* ����follow on��־                        */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        /* ��ǰRAU��ֹ�����µ�RAU */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_INITIATED:

        if (GMM_FALSE == ucRaiChgFlg)
        {/* RAδ�ı䣬��ǰRAU��ɺ��ٷ����µ�RAU */
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
            return;
        }
        /* RA�ı䣬��ǰRAU��ֹ�����µ�RAU */
        Gmm_TimerStop(GMM_TIMER_T3310);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        NAS_MML_SetPsAttachAllowFlg( VOS_TRUE );      /* ����ע�������־ */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);

        break;

    case GMM_DEREGISTERED_INITIATED:

        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
         || (GMM_NETMODE_CHG_I_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_II_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_CasNetModeChangeByRau:WARNING: not surpport NetMode Change!");
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "GMM_CasNetModeChangeByRau:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasGetNetChgType
 Description    : �ж���ϵͳ�л�����ģʽ�ĸı�����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.��    ��   : 2006��10��9��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D05744
*****************************************************************************/
VOS_UINT8 GMM_CasGetNetChgType(VOS_UINT8 ucNewNetMod)
{
    GMM_NETMODE_CHG_TYPE   ucNetChgType = GMM_NETMODE_CHG_NULL;

    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_II;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_I;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_I;
        }
        else if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_II;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: Old Netmode is incorrect!");
    }

    return ucNetChgType;
}

/*****************************************************************************
 Prototype      : GMM_ProcedureByNetMode
 Description    : �ж���ϵͳ�л�����ģʽ�ĸı�����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.��    ��   : 2006��10��9��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D05744
  2.��    ��   : 2006��11��20��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D07433
*****************************************************************************/
VOS_VOID GMM_ProcedureByNetMode(VOS_UINT8 ucNetModChangeType)
{
    if (GMM_NETMODE_CHG_I_II == ucNetModChangeType)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((GMM_NETMODE_CHG_I_III == ucNetModChangeType)
          || (GMM_NETMODE_CHG_II_III == ucNetModChangeType))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (GMM_NETMODE_CHG_II_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_II == ucNetModChangeType)
    {
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_ProcedureByNetMode:WARNING: Netmode change type is incorrect!");
    }
}

/*****************************************************************************
 Prototype      : GMM_CasChangSysMode
 Description    : �л���ָ��������ģʽ��2G/3G
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.��    ��    : 2009��03��18��
    ��    ��    : l65478
    �޸�����    : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
*****************************************************************************/
VOS_VOID GMM_CasChangSysMode(VOS_UINT8 ucState)
{
    /* �����������ģʽ��ͬ�������ı䴦�� */
    /*if (ulState == gstGmmCasGlobalCtrl.ulGmmCasPreState)*/
    /*{*/
    /*    return;*/
    /*}*/

    /* ��ģʽ��ϵͳ״̬������ʼ�� */
    if (NAS_MML_NET_RAT_TYPE_GSM == ucState)
    {/* �л���2G����ģʽ */
        /* ϵͳCAS״̬ά�� */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_GSM_AS;

        /* TLLI��ʼ�� */
        gstGmmCasGlobalCtrl.ulTLLI    = 0xffffffff;         /* ��ЧTLLIֵ */
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;         /* ��ЧTLLIֵ */
        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_INVALID_TLLI;   /* ��TLLI��Ч��־ */
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;    /* δ���TLLIָ�� */

        /* READY TIMER��ʼ�� */
        /*gstGmmCasGlobalCtrl.ulReadyTimerValue
            = GMM_TIMER_T3314_VALUE * GMM_TIMER_T3314_CNT*/;                      /* Ĭ��ֵ */
        /*gstGmmCasGlobalCtrl.ulReadyTimerCntMax = GMM_TIMER_T3314_CNT*/;           /* Ĭ��ֵ */
        /* gstGmmCasGlobalCtrl.ulReadyTimerCnt    = 0;  */       /* ���������� */
        gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg = GMM_FALSE;  /* ����Э�̱�־ */

        /* 2G���̱����ͱ�־��λ */
        gstGmmCasGlobalCtrl.ucRabmResumeFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucRauCmpFlg     = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipherAlg = LL_GEA0;      /* �޼����㷨 */

        NAS_GMM_SndMmcCipherInfoInd();

        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucFtsFlg        = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;

        g_GmmGlobalCtrl.ucSigConFlg         = GMM_TRUE;
    }
#if 0
    else if (GMM_CAS_WCDMA_AS == ulState)
    {/* �л���3G����ģʽ */
        /* ϵͳCAS״̬ά�� */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_WCDMA_AS;

        /* TLLI 3G���粻ʹ�ã����ֲ��� */
        /* READY TIMER 3G���粻ʹ�ã����ֲ��� */
        /* 2G���̱����ͱ�־3G���粻ʹ�ã����ֲ��� */
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;
        g_GmmGlobalCtrl.ucSigConFlg         = GMM_FALSE;
    }
    else
    {/* �л���SUSPENDģʽ */
        /* ��GMM CAS״̬ */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
            = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
            = GMM_CAS_SUSPEND;

        /* ׼��������Ϣ���棬֪ͨCM��ģ�����ָʾ */
        Gmm_TimerStart(GMM_TIMER_BUFFER_QUEUE);
        GMM_SndRabmSuspendInd();                /* ֪ͨRABM CAS������Ϣ*/
        return;
    }

    /* ����������Ϣ�󣬲���Ҫ�ϱ�RAU������Ϣ */
    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        return;
    }

    /* inter-system change���RA update���� */
    GMM_CasGetRauType(&ucRauType, ulState);
    GMM_CasExecRauInSysChg(ucRauType);
#endif

    gstGmmCasGlobalCtrl.ucGprsCipherAssign    = VOS_FALSE;  /* �����㷨û��֧�� */
    gstGmmCasGlobalCtrl.ucGprsCipher          = VOS_FALSE;

    NAS_GMM_SndMmcCipherInfoInd();

    return;
}

/**************************************/
/* �����ⲿģ��(RABM,APS)���ýӿ�     */
/**************************************/
/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : ��ȡGMM�ĵ�ǰ��������
                  HSS 4100 V200R001 ����
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : ��ǰפ���Ľ��뼼��
                  GMM_GMM_NET_RAT_TYPE_WCDMA  3G����
                  GMM_GMM_NET_RAT_TYPE_GSM    2G����
                  GMM_GMM_NET_RAT_TYPE_LTE
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
  2.��    ��    : 2011��11��28��
    ��    ��    : z00161729
    �޸�����    : ����Lģ���ж�
*****************************************************************************/
VOS_UINT8 GMM_GetCurNetwork (VOS_VOID)
{
    /* ��ȷ���������ģʽ */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_LTE;
    }
#endif
    else
    {
        /* ����״̬Ĭ������ģʽΪ3G */
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
}

/*****************************************************************************
 Prototype      : GMM_GetTlli
 Description    : ��ȡGMM�ĵ�ǰTLLIֵ
                  HSS 4100 V200R001 ����
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : GMM��ǰʹ�õ�TLLIֵ
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_GetTlli (VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ulTLLI;
}

/*****************************************************************************
 Prototype      : GMM_ServiceStatusForSms
 Description    : ��ȡGMM�ĵ�ǰ�����Ƿ����

 Input          :
 Output         :
 Return Value   : GMM��ǰ�����Ƿ����
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-07-31
    Author      : s46746
    Modification: Created function
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV֧��L�·������޸�
  3.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  4.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
  5.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���
*****************************************************************************/
VOS_UINT32 GMM_ServiceStatusForSms(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ��ǰפ��Lģ�������ж�GMM״̬ */
        return GMM_SMS_SERVICE_AVAILABLE;
    }
    else
#endif
    {
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
         && (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        switch (g_GmmGlobalCtrl.ucState)
        {
            case GMM_ROUTING_AREA_UPDATING_INITIATED:
            case GMM_SERVICE_REQUEST_INITIATED:
            case GMM_REGISTERED_NORMAL_SERVICE:
            case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            case GMM_REGISTERED_IMSI_DETACH_INITIATED:
                return GMM_SMS_SERVICE_AVAILABLE;
            case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
                /* �ڴ�G�л���W,SMS���԰�ҵ��֪ͨGMM,��GMM����һ��RAU���� */
                if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                 && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
                 && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
                {
                    return GMM_SMS_SERVICE_AVAILABLE;
                }
                else
                {
                    return GMM_SMS_SERVICE_UNAVAILABLE;
                }
            default:
                return GMM_SMS_SERVICE_UNAVAILABLE;
        }
    }
}

/*****************************************************************************
 Prototype      : GMM_GetRaPrioForSms
 Description    : ��ȡGMM�ĵ�ǰRadio priority for SMS ֵ
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : GMM��ǰʹ�õ�Radio priority for SMS ֵ
 Calls          :
 Called By      :

 History        :
  1.Date        : 2009-5-13
    Author      : h44270
    Modification: Created function
  2.��    ��   : 2013��6��05��
    ��    ��   : Y00213812
    �޸�����   : DTS2013060507591,COVERITY��FORITY�޸�
*****************************************************************************/
VOS_UINT8 GMM_GetRaPrioForSms (VOS_VOID)
{
    VOS_UINT8   ucRaPrioLevFosSms;

    ucRaPrioLevFosSms = gstGmmCasGlobalCtrl.enRaPrioLevFosSms - 1;
    return ucRaPrioLevFosSms;

}

/*****************************************************************************
 �� �� ��  : GMM_CasMsgProc_GmmSuspendNormalService
 ��������  : GMM��GmmSuspendNormalService״̬�յ���Ϣ�Ĵ���
 �������  : pMsg        - �յ���Ϣ
 �������  : pucFollowOn - follow on��־
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID GMM_CasMsgProc_GmmSuspendNormalService(
    struct MsgCB                       *pMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    /* �ֲ��������� */
    MSG_HEADER_STRU         *pNasMsgHeader;

    RRMM_DATA_IND_FOR_PCLINT_STRU  *pstRrmmDataInd          = VOS_NULL_PTR;
    NAS_MSG_FOR_PCLINT_STRU        *pstNasMsg               = VOS_NULL_PTR;
    LL_NAS_UNITDATA_IND_MSG        *pstLLUnitDataInd        = VOS_NULL_PTR;

    pstRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pMsg;
    pstNasMsg      = &pstRrmmDataInd->RcvNasMsg;
    pstLLUnitDataInd = (LL_NAS_UNITDATA_IND_MSG *)pMsg;

    /* ��Ϣ�������� */
    *pucFollowOn = GMM_FALSE;                                                   /* Ĭ�ϲ��ٽ���ԭ��Ϣ��ں������� */

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;


    if (WUEPS_PID_MMC == pMsg->ulSenderPid)
    {
        if (MMCGMM_RESUME_IND == pNasMsgHeader->ulMsgName)
        {
            GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_RESUME_IND in SUSPENDED_NORMAL_SERVICE state.");
            /* ������Ϣ�ַ��������������Ϣ */
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            GMM_BufferMsgDump();
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }


        /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
           ������פ��������������Attach */
        if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
    }
    else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
    {
        /* ����״̬�յ�REL_IND GMM��Ҫ����:�����֪ͨMMC�������ӱ�־ */
        if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_REL_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }


        /* ͸����SM��ǰDATA_IND��Ϣ */
        if ( (RRMM_DATA_IND == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM     == (pstNasMsg->aucNasMsg[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_DATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
    else if (UEPS_PID_LL == pMsg->ulSenderPid)
    {
        /* LL͸����SM��ǰDATA_IND��Ϣ */
        if ( (ID_LL_UNITDATA_IND    == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM             == (pstLLUnitDataInd->stUnitDataInd.aucPdu[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LL_UNITDATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }

    /* ����״̬����Ҫ����LMM�İ�ȫ�����Ļظ���Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
    else if (PS_PID_MM == pMsg->ulSenderPid)
    {
        if (ID_LMM_GMM_HO_SECU_INFO_CNF == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LMM_GMM_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
#endif
    else
    {
    }

    GMM_SuspendMsgProc(pMsg, pucFollowOn);

    return;

}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
