/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmAuth.c
  Author       : s46746
  Version      : V200R001
  Date         : 2005-08-16
  Description  : ��C�ļ�������MMģ��AuthProc��ģ���ʵ��
  Function List:
        1) MM_AuthProc
        2) MM_HandleGsmAuthenFail
        3) MM_RcvGsmAuthenticationCnf
        4) MM_RcvSimAuthCnf
        7) MM_SimAuth
        8) MM_SndGsmAuthenReq
        9) MM_UsimGsmAuth

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2. s46746 2006-02-09 �������ⵥA32D03324�޸�
  3. s46746 2006-03-07 �������ⵥA32D02191�޸�
  4.��    ��   : 2006��12��5��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07740
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Inc.h"
#include "MmAuth.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_AUTH_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 Prototype      : MM_AuthProc
 Description    : ������Ȩ������ڣ��� SIM ���� USIM GSM ��Ȩ���д���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :

 Called By      :
 History        : ---
 1.Date        : 2005-08-16
   Author      : s46746
   Modification: Created function
 2.��    ��   : 2006��12��5��
   ��    ��   : s46746
   �޸�����   : ���ⵥ��:A32D07740
 3.��    ��   : 2010��11��19��
   ��    ��   : s46746
   �޸�����   : ���ⵥ��:DTS2010111604811,��Ȩ�����н��յ���ͬ��Ȩ��Ϣ����
 4.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

 5.��    ��   : 2014��10��20��
   ��    ��   : w00167002
   �޸�����   : DTS2014102000868:�ڼ�Ȩ�ɹ���Ÿ���CKSN
  6.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*****************************************************************************/
VOS_VOID MM_GsmAuthProc()
{

    /* ��Ȩ��Ӧ��Ϣ�ṹ */
    MM_MSG_AUTHENTICATION_RSP_STRU      stMsg;

    /* ����Ȩ�������(Rand,Cksn)���浽ȫ�ֱ����� */
    PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
               g_MmMsgAuthReq.MmIeRAND.aucRandValue,
               16 * sizeof(VOS_UINT8)
               );


    /* ��ʼ�� Msg ���� */
    PS_MEM_SET(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    /* �ɵ� Rand ��Ч */
    if (MM_AUTHEN_RAND_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg)
    {
        if ((MM_FALSE == Mm_ComRandJudge()))  /* ��ǰ RAND ��ɵ���ͬ */
        {
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_AuthProc: NORMAL: Rand same as the rand of last auth.");

            /* �ж�ǰ���� RAND �Ƿ���ͬ */
            if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
            {
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat  = MM_AUTHEN_RAND_REPEAT;
            }
            /* RES �� SRES ����,���ұ��μ�Ȩ�������ϴ���ͬ */
            else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg)
                    && (AUTHENTICATION_REQ_GSM_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
            {
                /* ֱ�ӽ��ϴε� SRES ���͵������ */
                PS_MEM_CPY(stMsg.MmIeAuthRspPara.aucSgnfcntRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);

                NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

                /* ����AUTHENTICATION RESPONSE */
                Mm_ComMsgAuthRspSnd(&stMsg);

                return;
            }
            else
            {

            }
        }
        else
        {
            /* ���� RAND ���ϴβ�ͬ��������Ӧ��־ */
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_REPEAT;
        }
    }

    /* ���浱ǰ RAND */
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                16 * sizeof(VOS_UINT8)
                );

    /* ���� RAND ���ڱ�ʶ�����RES���ڱ�־ */
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg  = MM_AUTHEN_RAND_PRESENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg   = MM_AUTHEN_RES_ABSENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg  = MM_AUTHEN_RES_ABSENT;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        
        /* ���ú��� MM_UsimGsmAuth ���д��� */
        MM_UsimGsmAuth();
        
        if (VOS_TRUE == NAS_MML_IsNeedSetUsimDoneGsmAuthFlg())
        {
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_AuthProc: SetUsimDoneGsmCsAuthFlg to ture");
        
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        }
    }
    else if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* ���ú��� MM_SimAuth ���д��� */
        MM_SimAuth();
    }
    else /* �쳣���, ��Ȩ���󱻶��� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_AuthProc: ERROR: Sim type is unexpeted!");
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_UsimGsmAuth
 Description    : USIM����2G�����¶� GSM ��Ȩ������Ϣ�Ĵ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_UsimGsmAuth()
{

    /* ���� GSM ��Ȩ���� */
    MM_SndGsmAuthenReq();

    return;
}

/*****************************************************************************
 Prototype      : MM_SimAuth
 Description    : SIM���ĶԼ�Ȩ������Ϣ�Ĵ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      : AuthProc
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
 2.��    ��   : 2013��10��31��
   ��    ��   : l65478
   �޸�����   : DTS2013103002259:SIM��W���յ���ȨMM����ʧ��
*****************************************************************************/
VOS_VOID MM_SimAuth()
{
    /* 24.008 If a SIM is inserted in the MS, the MS shall ignore
       the Authentication Parameter AUTN IE if included in the
       AUTHENTICATION REQUEST message and shall proceed as in
       case of a GSM authentication challenge */
    /* ���� GSM ��Ȩ���� */
    MM_SndGsmAuthenReq();

    return;
}

/*****************************************************************************
 Prototype      : MM_SndGsmAuthenReq
 Description    : ������෢�� GSM ��Ȩ����
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-09-06
    Author      : s46746
    Modification: Created function
  2.��    ��  : 2006��11��25��
    ��    ��  : luojian id:60022475
    �޸�����  : ���ⵥ��:A32D06583
  3.��    ��  : 2012��12��26��
    ��    ��  : ���� id:00214637
    �޸�����  : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������
  4.��    ��  : 2013��6��4��
    ��    ��  : w00242748
    �޸�����  : USIMM_AuthReq�޸�ΪNAS_USIMMAPI_AuthReq�����߻���ݵ�ǰģʽ�Զ�
                ����
  5.��    ��  : 2013��11��30��
    ��    ��  : l65478
    �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��

  6.��    ��  : 2014��1��3��
    ��    ��  : s00261364
    �޸�����  : mmģ��Converity�澯����
*****************************************************************************/
VOS_VOID MM_SndGsmAuthenReq()
{
    VOS_UINT8        ucTempOpId = 0;

    /* ����ȫ�ֱ�־,��ʾ�ȴ����� USIM/SIM ����Ȩ��Ӧ */
    g_MmGlobalInfo.ucRcvAgentFlg |= MM_RCV_AUTH_CNF_FLG;


    ucTempOpId = g_MmGlobalInfo.AuthenCtrlInfo.ucOpId;

    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId++;



    /* �� SIM/USIM ������ GSM ���ͼ�Ȩ���� */
    NAS_USIMMAPI_AuthReq(WUEPS_PID_MM,
                    AUTHENTICATION_REQ_GSM_CHALLENGE,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                    VOS_NULL,
                    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId
                    );

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_SndGsmAuthenReq: NORMAL: Send GSM CHALLENGE Auth Req!");

    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_GSM_CHALLENGE;

    /* �������� TIMER */
    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);

    return;
}

/*****************************************************************************
 Prototype      : MM_RcvSimAuthCnf
 Description    : ���յ� USIM/SIM ���Լ�Ȩ����ķ�����Ϣ
 Input          : Msg ָ����յ� USIM/SIM ���ļ�Ȩ�����Ϣ
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_RcvSimAuthCnf(VOS_VOID* pMsg)
{
    /* ���� USIM/SIM ���͵ļ�Ȩ��Ӧ */
    if (MM_TRUE == MM_RcvGsmAuthenticationCnf(pMsg)) /* ���ռ�Ȩ��Ӧ���� */
    {
        /* ֹͣ������ʱ�� */
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

        /* �Լ�Ȩ������� */
        if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst)
        {
            /* ��Ȩ�ɹ����� */
            Mm_ComAuthenRcvUsimCnfSuccess();
        }
        else
        {
            /* ��Ȩʧ�ܴ��� */
            MM_HandleGsmAuthenFail();

        }
    }
    else /* �쳣������� */
    {
        MM_HandleGsmAuthenFail();

        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvSimAuthCnf: ERROR: Rcv Gsm Auth cnf error!");
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_RcvGsmAuthenticationCnf
 Description    : ���յ� USIM/SIM ���� GSM ���ͼ�Ȩ����ķ�����Ϣ
 Input          : pMsg ָ����յ� USIM/SIM ���ļ�Ȩ�����Ϣ
 Output         :
 Return Value   : MM_TRUE  ��ȷ�ļ�Ȩ��Ӧ
                  MM_FALSE ����ļ�Ȩ��Ӧ
 Calls          :
 Called By      :
 History        : ---
 1.Date        : 2005-09-06
   Author      : s46746
   Modification: Created function
 2.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 3.��    ��  : 2013��7��22��
   ��    ��  : y00245242
   �޸�����  : VoIP�����������µ�USIM�ӿ�
 4.��    ��   : 2014��4��175��
   ��    ��   : s00246516
   �޸�����   : DTS2014041700472:ʹ��2G SIM����PAD��̬�ϳ��ּ�Ȩ������ܾ�
 5.��    ��   : 2014��10��20��
   ��    ��   : w00167002
   �޸�����   : DTS2014102000868:�ڼ�Ȩ�ɹ���Ÿ���CKSN
*****************************************************************************/
VOS_UINT8 MM_RcvGsmAuthenticationCnf(VOS_VOID* pMsg)
{
    /* �����Ȩǰ�õ�ȫ�ֱ�־ ucRcvAgentFlg */
    if (MM_RCV_AUTH_CNF_FLG
        != ( MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        /* �����ϲ㴦�� */
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Auth cnf is unexpected!");

        return MM_FALSE;
    }
    else
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    }

    /* �� USIM/SIM �ļ�Ȩ��Ϣд��ȫ�ֱ��� g_AgentUsimAuthCnf �� */
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, begin */
    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, end */

    /* ���� g_AgentUsimAuthCnf �еļ�Ȩ��� */
    if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst) /* ��Ȩ�ɹ� */
    {
        /* ���� SRES ���� */
        PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucRes,
                    g_AgentUsimAuthCnf.aucResponse, 4);

        /* ���� SRES ���ڱ�־ */
        g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_PRESENT;

        g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;

        /* g_AgentUsimAuthCnf.ucKcLength Ϊ�� */
        if (MM_CONST_NUM_0 == g_AgentUsimAuthCnf.ucKcLength)
        {
            /* �쳣����������ϲ㴦�� */
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Sim didn't return Kc at GSM Auth!");

            return MM_FALSE;
        }
        else
        {
            /* �� KC ���浽ȫ�ֱ��� */
            NAS_MML_SetSimCsSecurityGsmKc(g_AgentUsimAuthCnf.aucKc);
        }

        /* ���ú��� NAS_MML_SecContext2GTO3G ��� IK��CK */
        NAS_MML_SecContext2GTO3G(g_AgentUsimAuthCnf.aucIntegrityKey, g_AgentUsimAuthCnf.aucCipheringKey,
                                 g_AgentUsimAuthCnf.aucKc);

        /* �� IK��CK �洢��ȫ�ֱ����� */
        NAS_MML_SetSimCsSecurityUmtsCk(g_AgentUsimAuthCnf.aucCipheringKey);
        NAS_MML_SetSimCsSecurityUmtsIk(g_AgentUsimAuthCnf.aucIntegrityKey);

        NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

    }

    return MM_TRUE;
}

/*****************************************************************************
 Prototype      : MM_HandleGsmAuthenFail
 Description    : USIM/SIM �� GSM ���ͼ�Ȩʧ�ܵĴ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-09-06
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_HandleGsmAuthenFail()
{

    /*MM_MSG_AUTHENTICATION_FAIL_STRU     stMsg;

    VOS_MemSet(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_FAIL_STRU));

    stMsg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;

    Mm_ComMsgAuthFailSnd(&stMsg);*/     /* ���� AUTHENTICATION FAILURE ��Ϣ */

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "MM_HandleGsmAuthenFail: WARNING: Gsm Auth Fail!");

    return;
}



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
