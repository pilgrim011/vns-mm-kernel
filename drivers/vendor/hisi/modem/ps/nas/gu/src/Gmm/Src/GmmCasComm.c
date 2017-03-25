/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasComm.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : ��C�ļ�������Gmm Casģ����ͨ�ô�����̵�ʵ��
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 �������ⵥA32D02368�޸�
  3. s46746 2006-03-18 �������ⵥA32D02141�޸�
  4. l40632 2006-04-11 �������ⵥA32D03039�޸�
  5. l40632 2006-04-17 �������ⵥA32D03141�޸�
  6. l40632 2006-04-25 �������ⵥA32D03000�޸�
  7. x51137 2006/4/28 A32D02889
  8. l40632 2006.05.20 �������ⵥA32D03865�޸�
  9. l40632 2006.05.30 �������ⵥA32D03830
  10.l40632 2006.06.29 �������ⵥA32D04514
  11.��    ��   : 2006��10��9��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�A32D05744
  12.��    ��   : 2007��01��13��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�A32D08326
  13.��    ��   : 2007��03��21��
     ��    ��   : luojian 60022475
     �޸�����   : Maps3000�ӿ��޸�
  14.��    ��   : 2007��07��12��
     ��    ��   : hanlufeng 41410
     �޸�����   : A32D12338
  15.��    ��   : 2007��08��19��
     ��    ��   : l60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  16.��    ��   : 2007��09��10��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�A32D12829
  17.��    ��   : 2007-10-26
     ��    ��   : hanlufeng
     �޸�����   : A32D13172
  18.��    ��   : 2007��11��22��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�A32D13475,�޸���ϵͳ�ı��ָ�ɵ�old TLLI�Ϳ���������ԿΪȫ0����
  19.��    ��   : 2007-10-26
     ��    ��   : l00107747
     �޸�����   : A32D13862
  20.��    ��   : 2007��12��14��
     ��    ��   : s46746
     �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
  21.��    ��   : 2007��12��21��
     ��    ��   : l00107747
     �޸�����   : ���ⵥA32D13950,W֧��CS&PS,G�²�֧��PS���л���Wģʽ��GMMû�з�������RAU
  22.��    ��   : 2007��12��28��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
  23.��    ��   : 2008��5��2��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�AT2D03268,û���ж�С���Ƿ�ı��־��ֱ�ӽ�����RAU��Attach
  24.��    ��   : 2008��8��22��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�AT2D05192,cell update�ж�ʱ���ж�����RAI�Ƿ�ı�û�и�ֵ��ȷ
  25.��    ��   : 2008��9��23��
     ��    ��   : o00132663
     �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
  26.��    ��   : 2008��12��18��
     ��    ��   : x00115505
     �޸�����   : �������ⵥ�ţ�AT2D07624,�޸Ŀ�ά�ɲ���Ϣ��TimerStamp
                  �ֶεĶ�ȡ��ʽ��
  27.��    ��   : 2009��04��01��
     ��    ��   : x00115505
     �޸�����   : ���ⵥ��:AT2D10473,Rau�����г����������ص�������֮��û�з���Rau��
  28.��    ��   : 2009��05��14��
     ��    ��   : h44270
     �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
  29.��    ��   : 2009��6��30��
     ��    ��   : s46746
     �޸�����   : AT2D12561,3G2����GPRS��δ�������ܣ�NASָ�ɲ�2�����㷨�󣬲�2���������ݽ����˼���
  30.��    ��   : 2009��7��23��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�AT2D12878��GSM��HPLMN����ʱ���յ�GPRSѰ����PDP����(W��PDP������ͬ����)������Ҫ�ܼ�ʱ��Ӧ
  31.��    ��   : 2011-11-11
     ��    ��   : h44270
     �޸�����   : �����ⵥ�ţ�DTS2010110500099/DTS2010111103124,����GMM��Wģ����GAS����ȥָ����Ϣ
  32.��    ��   : 2011��12��29��
     ��    ��   : l00130025
     �޸�����   : DTS2011082201679/DTS2011121504358,ɾ��LTE��ģʽ�жϺ���
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasCommDef.h"
#include "NasGmmProcLResult.h"
#endif
#include "NasUsimmApi.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASCOMM_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM CAS ͨ�ù��̴���   -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_IsCasGsmMode
 Description    : �жϵ�ǰ����ģʽ�Ƿ�GSM����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   : GMM_TRUE       GSM�������
                  GMM_FALSE      ��GSM�������
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsCasGsmMode (VOS_VOID)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }
    else
    {
        return GMM_FALSE;
    }
}

/*****************************************************************************
 Prototype      : GMM_IsLastRand
 Description    : �ж��´��RAND���ϴμ�¼ֵ�Ƿ����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsLastRand(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucRel = GMM_TRUE;

    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        if (g_GmmAuthenCtrl.aucRandSav[i]
           != g_GmmAuthenCtrl.aucRand[i])
        {
            ucRel = GMM_FALSE;
            break;
        }
    }

    return ucRel;
}

/*****************************************************************************
 Prototype      :
 Description    : ���������ģ��ʹ��ȫ�ֽṹ������ʼ������
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2009��05��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
  4.��    ��   : 2009��09��03��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D14239,detach��ɺ�,�ٴη���ATTATCH REQʱ,GASʹ�þɵ�TLLI������TBF��������,û�м�ʱʹ���µ�TLLI,����MS��������ά����TLLI��һ��,�Ӷ�����GAS��ΪTLLI��ƥ�䶪���˽�������TBF��ָ������,���յ�������ʧ��
  5.��    ��   : 2010��12��18��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ��:DTS2010121800152,GMM�ػ��ز�����״̬����
*****************************************************************************/
VOS_VOID GMM_InitCasGlobalVariable (VOS_VOID)
{
    /* GMM CASȫ�ֽṹ�������� */
    Gmm_MemSet(&gstGmmCasGlobalCtrl, 0, sizeof(GMM_CAS_CTRL_STRU));
    Gmm_MemSet(&gstGmmCasMsgBuf,     0, sizeof(GMM_CAS_MSG_BUFFER_STRU));
    Gmm_MemSet(&gstGmmSuspendCtrl,   0, sizeof(GMM_SUSPEND_CTRL_STRU));


    /* �趨��ʼֵ */
    gstGmmCasGlobalCtrl.ucGmmCasState       = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.ucGmmCasPreState    = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.GmmSrvState         = GMM_IU_PMM_DETACHED;
    gstGmmCasGlobalCtrl.ucBufMsgResFlg      = GMM_FALSE;             /* ���û����Ҫ�ָ��Ĺ�����Ϣ */
    gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg  = GMM_FALSE;             /*��ǿ�Э��ready timer*/
    gstGmmCasGlobalCtrl.ucRauCmpFlg         = GMM_FALSE;             /*��ǲ��ܷ���RAU CMP��Ϣ*/
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;

    gstGmmCasGlobalCtrl.ucRabmResumeFlg     = GMM_TRUE;              /*���RABM RAU���������*/
    gstGmmCasGlobalCtrl.ulReadyTimerValue   = 44000;                 /* 44 s*/
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg  = VOS_FALSE;
    /* ��ʼ��ϵͳTLLIֵ */
    gstGmmCasGlobalCtrl.ulTLLI              = 0xffffffff;            /* ��ЧTLLIֵ */
    gstGmmCasGlobalCtrl.ulOldTLLI           = 0xffffffff;            /* ��ЧTLLIֵ */
    gstGmmCasGlobalCtrl.ucflgTLLI           = GMM_INVALID_TLLI;      /* ��TLLI��Ч��־ */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg     = GMM_FALSE;             /* δ���TLLIָ�� */
    gstGmmCasGlobalCtrl.enRaPrioLevFosSms   = GMM_RA_PRIO_LEV_1;

    g_GmmGlobalCtrl.ulGmmAttachFlg          = GMM_FALSE;

    gstGmmSuspendCtrl.ucSuspendCause        = MMC_SUSPEND_CAUSE_BUTT;

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfUmtsSucc
 Description    : �յ�USIM��UMTS��Ȩ�ɹ����
                  HSS 4100 V200R001 ����
 Input          : USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf �����ṹָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.��    ��    : 2009��03��18��
    ��    ��    : l65478
    �޸�����    : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
  3.��    ��   : 2009��03��31��
    ��    ��   : L65478
    �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
  4.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2013��07��23��
    ��    ��   : y00245242
    �޸�����   : VOLTE�����������µ�USIM�ӿ�
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfUmtsSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* ����ָ��NAS��Ϣ��ָ��*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* �ݴ���Ϣ�е�CKSN����ȫ�ֱ����е�CKSN                         */

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    /* ��¼CKֵ��ȫ�ֱ�����, �����׸������ֽ� */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsCk(),
            &(pAuthCnf->aucCK[1]), 16 );                          /* ����ȫ�ֱ����е�Ck*/

    /* ��¼IKֵ��ȫ�ֱ����У������׸������ֽ� */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsIk(),
            &(pAuthCnf->aucIK[1]), 16 );                          /* ����ȫ�ֱ����е�Ik*/

    /* ���㱣��GSM Kc */
    if (0 == pAuthCnf->aucGsmKc[0]) /* check Kc length */
    {
        NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                                 NAS_MML_GetSimPsSecurityUmtsCk(),
                                 NAS_MML_GetSimPsSecurityGsmKc());
    }
    else
    {
        /* skip the first length byte */
        Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
                &(pAuthCnf->aucGsmKc[1]), 8 );                        /* ����ȫ�ֱ����е�GSM Kc*/
    }
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */


    /* ����CK,IK,Kcֵ��SIM�� */
    if (MMC_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }

    /* ��¼RES */
    GMM_SaveAuthenResult(pAuthCnf);

    /* ֪ͨMMCʵ���Ȩ�����Ϣ */
    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* ����RRMM_NAS_INFO_CHANGE_REQ*/

    /* �޸ļ�Ȩ���̵ı�־�� */
    Gmm_Start_StopedRetransmissionTimer();                  /* ���ڱ�ֹͣ��retransmission timer�������� */
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                  /* GMM Authentication attempt counter��0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    /* ��д��Ȩ��Ӧ��Ϣ */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* ����A&C RESPONSE*/

    /* ����GMM��Ϣ */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    /* RANDֵ�Ƚϸ��� */
    GMM_UpdateAuthenCtrlFlg();

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfGsmSucc
 Description    : �յ�USIM��GSM��Ȩ�ɹ����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
 1.Date        : 2005-11-08
   Author      : Roger Leo
   Modification: Created function
 2.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 3.��    ��   : 2013��07��23��
   ��    ��   : y00245242
   �޸�����   : Ϊ����VOLTE�������µ�USIM�ӿ�
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfGsmSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* ����ָ��NAS��Ϣ��ָ��*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* �ݴ���Ϣ�е�CKSN����ȫ�ֱ����е�CKSN                                 */


    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    /* ��¼Kcֵ��ȫ�ֱ�����, �����׸������ֽ�COPY */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
            &(pAuthCnf->aucGsmKc[1]), 8 );                        /* ����ȫ�ֱ����е�GSM Kc*/
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */


    /* ����IK,CK */
    NAS_MML_SecContext2GTO3G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucCk,
            pAuthCnf->aucCK, 16 );*/                          /* ����ȫ�ֱ����е�Ck*/

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucIk,
            pAuthCnf->aucIK, 16 );*/                          /* ����ȫ�ֱ����е�Ik*/

    /* ����Kc,IK,CKֵ��SIM�� */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }

    /* ��¼SRES */
    GMM_SaveAuthenResult(pAuthCnf);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* ����RRMM_NAS_INFO_CHANGE_REQ*/

    /* ��д��Ȩ��Ӧ��Ϣ */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* ����A&C RESPONSE*/

    /* ����GMM��Ϣ */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    /* RANDֵ�Ƚϸ��� */
    GMM_UpdateAuthenCtrlFlg();

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfFailUmts
 Description    : UMTS��Ȩ:SYNCʧ�ܻ���MACʧ��
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.  ��    ��   : 2006��12��5��
      ��    ��   : luojian 60022475
      �޸�����   : Maps3000�ӿ��޸�
  3.  ��    ��   : 2009��03��31��
      ��    ��   : L65478
      �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
  4.  ��    ��   : 2012��4��20��
      ��    ��   : l00130025
      �޸�����   : DTS2012032004389��Netork����3�α�Ms Auth Rej��T3318/T3320��ʱʱ��û��֪ͨGAS Bar����ǰС��
  5.  ��    ��   : 2012��8��25��
      ��    ��   : m00217266
      �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                  ���浼��Attachʧ�ܵ�ԭ��ֵ
  6.  ��    ��   : 2013��07��23��
      ��    ��   : y00245242
      �޸�����   : Ϊ����VOLTE�������µ�USIM�ӿ�
  7.  ��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfFailUmts(
    USIMM_TELECOM_AUTH_CNF_STRU        *pAuthCnf,
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult
)
{
    NAS_MSG_STRU    *pNasMsg;

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                    /* GMM Authentication attempt counter��1    */

    /* �жϼ�Ȩ���Դ��� */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {/* ���������� */

        if (USIMM_AUTH_MAC_FAILURE == enResult)
        {
            /*�����Ȩʧ�ܵĴ�����*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_MAC_FAILURE);
        }
        else
        {
            /*�����Ȩʧ�ܵĴ�����*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_SYNCH_FAILURE);
        }

        /* ��Ȩʧ�ܴ����������� */
        Gmm_AuCntFail();
        return;
    }

    /* Failure ������� */
    if (USIMM_AUTH_MAC_FAILURE == enResult)
    {/* MAC failure */
        Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE);
    }
    else
    {/* SQN failure */
        /* AUTHENTICATION AND CIPHERING FAILURE���� */
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(
                            NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE,
                            pAuthCnf->aucAuts[0],
                            &(pAuthCnf->aucAuts[1]));
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */

        /* ���÷��ͺ��� */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* ֹͣT3316                                */

        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* ��"RES���ڱ�־ "��Ϊ0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* ��"RAND���ڱ�־ "��Ϊ0                   */

        if (GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        {/* �ϴμ�Ȩʧ��ԭ��ֵ��ͬ��ʧ�� */
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;          /* GMM Authentication attempt counter��0 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

            Gmm_TimerStop(GMM_TIMER_T3320);                 /* ͣT3320 */

            NAS_GMM_SndGasGprsAuthFailNotifyReq();

            Gmm_SndRrmmRelReq(RRC_CELL_BARRED);             /* ����RRMM_ABORT_REQ(RRC connection) */

            Gmm_Start_StopedRetransmissionTimer();          /* ���ڱ�ֹͣ��retransmission timer�������� */
        }
        else
        {/* �ϴμ�Ȩʧ��ԭ��ֵ����ͬ��ʧ�� */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL;
            Gmm_TimerStop(GMM_TIMER_T3318);                 /* ͣT3318(���������) */
            Gmm_TimerStart(GMM_TIMER_T3320);                /* ��T3320 */
            Gmm_Stop_RetransmissionTimer();                 /* ֹͣ�������е�retransmission timer */
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfFailGsm
 Description    : GSM��Ȩʧ��,��������ԭ��
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-01-13
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2013��07��23��
    ��    ��   : y00245242
    �޸�����   : Ϊ����VOLTE�������µ�USIM�ӿ�,�޸ĺ�����νṹ����
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfFailGsm(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    /*NAS_MSG_STRU    *pNasMsg;*/

    GMM_LOG_WARN("GSM authentication failure for unacceptable reason by MS!");
    /* ֱ�ӷ��ͼ�Ȩ��Ӧ��Ϣ������ */
    /*pNasMsg = GMM_MakeAuthenAndCipherResponseMsgGsm
                (GMM_AUTH_AND_CIPH_RES_UNNEEDED);*/
    /*pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(*/
    /*                                    NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,*/
    /*                                    0,*/
    /*                                    VOS_NULL_PTR);*/
    /* ����GMM��Ϣ */
    /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);*/

    return;
}

/*****************************************************************************
 Prototype      : GMM_ExecLlgmmStatusIndCause
 Description    : ��������LL_GMM_STATUS_IND_MSG��Ϣ�е�ԭ��ֵ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ExecLlgmmStatusIndCause(VOS_UINT16 usCause)
{
    switch (usCause)
    {
        case LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP:           /* unsolicited UA response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP:           /* unsolicited DM response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_SABM_N200:            /* SABM�����ط�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_DISC_N200:            /* DISC�����ط�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200:         /* XID�����ظ�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200:       /* ��ѯ�Է��Ƿ���æ״̬����N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_LLC_INIT_RE_EST:              /* LLC����ABM�ؽ� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_PEER_INIT_RE_EST:             /* �Զ˷���ABM�ؽ� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION:          /* ��⵽֡�ܾ����� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RECV_FRMR_RSP:                /* ���յ�FRMR��Ӧ */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL:              /* TLLIָ��ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC ASSIGN command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL:             /* LLC֡���ʹ�������ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC TRIGGER command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL:             /* LLC����ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC SUSPEND command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_RESUME_FAIL:              /* LLC�ָ�ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC RESUME command failed!");
            break;

        default :
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status alert undefined!");
            break;
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2006��10��9��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D05744
  3.��    ��   : 2007��08��19��
    ��    ��   : l60022475
    �޸�����   : �������ⵥ�ţ�A32D12706
  4.��    ��   : 2007-10-26
    ��    ��   : hanlufeng
    �޸�����   : A32D13172
  5.��    ��   : 2007-10-26
    ��    ��   : l00107747
    �޸�����   : A32D13862
  6.��    ��   : 2009-6-3
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D12225,��GPRSС����ѡ��GSMС��,t3312��ʱ��,�ػ�ԭGPRSС��,������normal RAU����������RAU
  7.��    ��   : 2010��8��14��
    ��    ��   : s46746
    �޸�����   : DTS2010073001405,G2W��ϵͳ��ѡ�󣬲����2����ȥָ�ɶ��ǹ����2
  8.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
  9.��    ��   : 2010��12��01��
    ��    ��   : z00161729
    �޸�����  : DTS2010111903590:LAI��RAI��CELL��δ��ֻ������ģʽ�����ı䣬UE����RAU��LAU����˲���
 10.��    ��   : 2011��03��1��
    ��    ��   : w00176964
    �޸�����   : ���ⵥ�ţ�DTS2011022503955, [���������-�������Ż�˫ģ]�����ѿ���ָ���ѹ����У�����
                 �û��б��������ػ��Ȳ�����ֹͣ�������RPLMN�ɹ�������ǰС����ֹ��֧��CS/PS���������
                 ������δ����������Ҫ�ȴ���ʱ����ʱ�����쳣����
 11.��    ��   : 2012��03��17��
    ��    ��   : s46746
    �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
 12.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
 13. ��    ��   : 2012��7��17��
     ��    ��   : z00161729
     �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                  ��������rau
 14.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
 15.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
 16.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32 GMM_SaveGsmSysInfoIndMsgPara(MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo)
{
    GMM_RAI_STRU                *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod  = g_GmmGlobalCtrl.ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST  *ptr;
    VOS_UINT8                   *pucRaiChgFlg;
    VOS_UINT16                   usCellIdNew;
    VOS_UINT8                    ucCsAttachAllow;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg   = GMM_FALSE;

    pucRaiChgFlg = &gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "GMM_SaveGsmSysInfoIndMsgPara:ERROR: MALLOC FAIL!");
        return GMM_FAILURE;                                                     /* ����                                     */
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* ��дRAC */
    pRaiTemp->ucRac = pSysInfo->ucRac;
    /* ��дLAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfo->usLac;                       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfo->usLac >> 8);
    /* ��дPLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */

    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;
    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &stOldRai, pSysInfo->ucNetworkOperationMode))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_TRUE;
    }
    if (GMM_FALSE == Gmm_Compare_Lai(&pRaiTemp->Lai, &stOldRai.Lai))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg = GMM_TRUE;
    }

    /* GPRS֧��ָʾ */
    g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;

    if (0 == pSysInfo->ucGprsSupportInd)
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;
    }

    usCellIdNew = pSysInfo->usCellId;

    if (usCellIdNew != g_GmmGlobalCtrl.SysInfo.usGsmCellId)
    {
        g_GmmGlobalCtrl.SysInfo.usGsmCellId = usCellIdNew;
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_TRUE;             /* ��С����־ */
    }
    else
    {
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_FALSE;
    }

    if (0 != pSysInfo->ucNetworkOperationMode)
    {/* ����ģʽ��Ч */
        ucNetMod = pSysInfo->ucNetworkOperationMode;
    }

    if ((g_GmmGlobalCtrl.SysInfo.ucNtType
        != NAS_MML_GetCurrNetRatType())
      &&(GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {/* ��ϵͳ��С����ϵͳ��Ϣ����Ч���� */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_SaveGsmSysInfoIndMsgPara:WARNING: Inter-System information cannot be handled in the GMM STATE!");
    }
    /* ==>A32D12706 */
    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    /* <==A32D12706 */
    {/* ����ģʽ��� */

        if ((GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg)
         || (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode()))
            {                                                                       /* �û�ģʽΪA,�����Ѿ�ע��                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {
                    /* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                    /* ͬϵͳ��С��ϵͳ��Ϣ���� */
                    Gmm_ComNetModeChangeGsm(pSysInfo);                              /* ��������ģʽ�任�Ĺ�������               */
                    Gmm_MemFree(pRaiTemp);

                    /*���С������ģʽ�ı䣬GMM_RcvGasSysInfoInd���������ߵ�����ָ�����û���Ĵ���
                      �����ڴ˴����Ӵ���
                    */
                    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                    {
                        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
                        {
                            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
                        }
                        else
                        {
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
                        }
                    }

                    if (0 == pSysInfo->ucGprsSupportInd)
                    {
                         NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                    }

                    /* �յ�Gģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, �����Ƿ�֧��GPRS, �����ָ�RABM */
                    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
                    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
                    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
                     || (0 == pSysInfo->ucGprsSupportInd)
                     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
                    {
                        /* ��֧��GPRS��PS bar����û��ָ�ɲ�2, ����RABM, bRatChangeFlgΪFALSE
                           û��ָ�ɲ�2ʱ���������RABM��RABM����SN�������ݣ�SN�ᷢ�͵�LLC��
                           ��LLC��δָ������½��յ����ݻ��ͷ��ڴ浼�½������,��������С���Ὣ��Ϣ���й��� */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_TRUE,
                                                    VOS_TRUE);
                    }
                    else
                    {
                        /* ֧��GPRS, �ָ�RABM, bRatChangeFlgΪFALSE */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_FALSE,
                                                    VOS_TRUE);
                    }

                    return GMM_FAILURE;
                }
            }
        }

        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        /* ����ģʽû�б��������ԭ������ģʽ��Ч */
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
                    /*= GMM_CasGetNetChgTypeByGsm(ucNetMod);*/
    }

    /* Modified by t00212959 for DCM�����������������, 2012-8-16, begin */
    /* ɾ����2Gϵͳ��ϢucDrxTimerMax��ֵ��DrxLen*/
    /* Modified by t00212959 for DCM�����������������, 2012-8-16, end */

    if (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg)
    {
        if (GMM_TRUE == *pucRaiChgFlg)
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_TRUE;
        }
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }

    if (GMM_TRUE == *pucRaiChgFlg)
    {/* RA�ı� */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {/* �����������ڽ����������� */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {/* GMM_REGISTERED_INITIATED״̬ */
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;   /* �洢��Ϣ�׵�ַ�� ulMsgAddrForAttach      */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;/* ����Ϣ������־                           */
                Gmm_MemFree(pRaiTemp);
                return GMM_FAILURE;
            }
            else if ((GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
                     || (GMM_ROUTING_AREA_UPDATING_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_SERVICE_REQUEST_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_REGISTERED_IMSI_DETACH_INITIATED
                     == g_GmmGlobalCtrl.ucState))
            {
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;      /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;   /* ����Ϣ������־                           */
                Gmm_MemFree(pRaiTemp);

                if (0 == pSysInfo->ucGprsSupportInd)
                {
                     NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                }

                return GMM_FAILURE;
            }
            else
            {
            }
        }
    }

    if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
        && (0 != pSysInfo->ucGprsSupportInd))
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
        if (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        }
    }
    else
    {
        /* ��ȡCS ATTACH Allow��־ */
        ucCsAttachAllow                             = NAS_MML_GetCsAttachAllowFlg();
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_FALSE;
        if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            || (MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS == pSysInfo->ulForbiddenFlg))
        {
            if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL_CS_UPDATED;
            }
        }
    }

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfo->ulForbiddenFlg;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    Gmm_MemFree(pRaiTemp);
    return GMM_SUCCESS;
}

/*****************************************************************************
 Prototype      : GMM_CharToUlong
 Description    : �ֽ�����ת����ULONG��
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc)
{
    VOS_UINT32  ulResult;

    ulResult  = 0;
    /*lint -e701 -e961*/
    ulResult += (*(pucSrc++) << 24);
    ulResult += (*(pucSrc++) << 16);
    ulResult += (*(pucSrc++) << 8);
    ulResult += (*(pucSrc) );
    /*lint +e701 +e961*/
    *ulDst = ulResult;
    return;
}

/*****************************************************************************
 Prototype      : GMM_CreateNewTlli
 Description    : �����µ�TLLIֵ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2.Date        : 2015-07-23
    Author      : wx270776
    Modification: OM Migration
*****************************************************************************/
VOS_VOID GMM_CreateNewTlli(VOS_UINT32 *pulTmsi, VOS_UINT8 ucType)
{
    VOS_UINT32  ulTLLI;
    VOS_UINT32  ulHead5;

    ulTLLI   = *pulTmsi;                /* �õ�PTMSIֵ */
    ulHead5  = ulTLLI >> 27;            /* ȡ��TLLI�ı�־ͷ */
    ulHead5 &= 0x07;                    /* �����Ч����λ */

    /*��дTLLIֵ�ĸ�5λֵ*/
    switch (ucType)
    {
        case GMM_RANDOM_TLLI:
            ulHead5  = 0x0f;            /* 5λֵ�� 01111 */
            /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
            ulTLLI   = VOS_GetSlice();   /* ȡϵͳʱ������Ϊα����� */
            /* Modified by wx270776 for OM�ں�, 2015-7-23, end */
            break;

        case GMM_LOCAL_TLLI:
            ulHead5 |= 0x18;            /* 5λֵ�� 11XXX */
            break;

        case GMM_FOREIGN_TLLI:
            ulHead5 |= 0x10;            /* 5λֵ�� 10XXX */
            break;

        case GMM_AUXILIARY_TLLI:
            ulHead5 = 0x0e;            /* 5λֵ�� 01110 */
            break;

        default :                       /* ����,�ο�3GPP TS23.003���� */
            ulHead5  = 0x00;            /* 5λֵ�� 00000 */
            break;
    }

    /*��дTLLIֵ�ĵ�27λֵ*/
    ulHead5 = ulHead5 << 27;
    ulTLLI &= 0x07ffffff;               /* �����5λ */
    ulTLLI += ulHead5;                  /* ��TTLLIֵ */

    *pulTmsi = ulTLLI;                  /* ���ؽ�� */
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_UseGutiDerivedPtmsi
 ��������  : ��ǰTinֵ��GU P-tmsi�Ƿ�ָʾ��Ҫʹ�� GUTI������P-Tmsi
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��20��
    ��    ��   : l00130025
    �޸�����   : PhaseI ���ⵥ�޸�:DTS2011080305247,GģҪʹ��ӳ���P-TMSI����TLLI

*****************************************************************************/
VOS_UINT32 NAS_GMM_UseGutiDerivedPtmsi ( VOS_VOID )
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    /* ���£�Э��������b)��d) ����VOS_TRUE,�������� VOS_FALSE
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)

    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* ��ȡ��ǰGU��p-Tmsi��ȡֵ */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi�Ƿ���ȷ */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if (VOS_OK == ulGetGutiRst)
    {
        /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            ulRslt = VOS_TRUE;
        }
        /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
        else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType)
               && (GMM_UEID_P_TMSI != (ucUeIdMask & GMM_UEID_P_TMSI) ))
        {
            ulRslt = VOS_TRUE;
        }
        else
        {
            ulRslt = VOS_FALSE;
        }
    }
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

}

#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetPTmsiForTLLI
 ��������  : ��ȡ��ǰҪʹ�õ�P-TMSIֵ
 �������  : VOS_UINT8 *
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��19��
    ��    ��   : l00130025
    �޸�����   : PhaseI ���ⵥ�޸�:DTS2011080305247,GģҪʹ��ӳ���P-TMSI����TLLI
  2.��    ��   : 2013��05��21��
    ��    ��   : l65478
    �޸�����   : DTS2013053002449ϣ������:����֧��LTEʱ,ʹ��GU�µ�ID
 3.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����  :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability

*****************************************************************************/
VOS_UINT32 NAS_GMM_GetPTmsiForTLLI(
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulIsSupportLteCap;
#endif

    /*
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)
    This subclause describes how the RR addressing is managed by GMM.
    For the detailed coding of the different TLLI types and how a TLLI can be derived from a P-TMSI, see 3GPP TS 23.003 [10].
    For an MS not supporting S1 mode, two cases can be distinguished:
    -   a valid P-TMSI is available in the MS; or
    -   no valid P-TMSI is available in the MS.
    i)   valid P-TMSI available
        If the MS has stored a valid P-TMSI, the MS shall derive a foreign TLLI from that P-TMSI and shall use it for transmission of the:
    -   ATTACH REQUEST message of any GPRS combined/non-combined attach procedure; other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI until the ATTACH ACCEPT message or the ATTACH REJECT message is received; and
    -   ROUTING AREA UPDATE REQUEST message of a combined/non-combined RAU procedure if the MS has entered a new routing area, or if the GPRS update status is not equal to GU1 UPDATED. Other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI, until the ROUTING AREA UPDATE ACCEPT message or the ROUTING AREA UPDATE REJECT message is received.
        After a successful GPRS attach or routing area update procedure, independent whether a new P-TMSI is assigned, if the MS has stored a valid P-TMSI then the MS shall derive a local TLLI from the stored P-TMSI and shall use it for addressing at lower layers.
    NOTE 1: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach or routing area update procedure, the network must be prepared to continue accepting LLC frames from the MS still using the foreign TLLI.
    ii) no valid P-TMSI available
        When the MS has not stored a valid P-TMSI, i.e. the MS is not attached to GPRS, the MS shall use a randomly selected random TLLI for transmission of the:
    -   ATTACH REQUEST message of any combined/non-combined GPRS attach procedure.
        The same randomly selected random TLLI value shall be used for all message retransmission attempts and for the cell updates within one attach attempt.
        Upon receipt of an ATTACH REQUEST message, the network shall assign a P-TMSI to the MS. The network derives a local TLLI from the assigned P-TMSI, and transmits the assigned P-TMSI to the MS.
        Upon receipt of the assigned P-TMSI, the MS shall derive the local TLLI from this P-TMSI and shall use it for addressing at lower layers.
    NOTE 2: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach, the network must be prepared to continue accepting LLC frames from the MS still using the random TLLI.
    In both cases the MS shall acknowledge the reception of the assigned P-TMSI to the network. After receipt of the acknowledgement, the network shall use the local TLLI for addressing at lower layers.


    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* �ж�GUPTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);

        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��ʼ����ǰ��P-Tmsi�Ĵ��ڱ�־ */
    ulRslt              = VOS_TRUE;

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* reference to 24.008 4.7.1.4.1 */
    ulIsSupportLteCap = NAS_MML_IsSupportLteCapability();

    /* syscfg���ò�֧��L����L �Ѿ�disable�������guti�л�ȡptimsi */
    if (VOS_FALSE == ulIsSupportLteCap)
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
        }
        else
        {
            ulRslt = VOS_FALSE;
        }

        return ulRslt;
    }

    /* a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI; */
    if ( ( (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
        || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
      && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
    else if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
          && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_FALSE == ulLocalPtmsiFlg)
          && (VOS_OK == ulGetGutiRst))
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*e)  none of the previous cases is fulfilled.*/
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

#else

    /* LTE����ʱ��ֻ��Ҫ�ж� GU P-Tmsi�Ƿ���Ч */
    return ulLocalPtmsiFlg;
#endif

}

/*****************************************************************************
 �� �� ��  : GMM_UpdateSysTlli
 ��������  : ���TLLI������Ч��,������Ĭ��TLLI���ͺ���ֵ
 �������  : TlliType
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  2.��    ��   : 2011��8��19��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:DTS2011080305247,GģҪʹ��ӳ���P-TMSI����TLLI
  3.��    ��   : 2013��5��20��
    ��    ��   : s00217060
    �޸�����   : coverity��foritfy�޸�

*****************************************************************************/
VOS_VOID GMM_UpdateSysTlli(GMM_TLLI_TYPE TlliType)
{
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];

    /* ��ڲ������ */
    if ( (GMM_RANDOM_TLLI != TlliType)
      && (GMM_FOREIGN_TLLI != TlliType)
      && (GMM_LOCAL_TLLI != TlliType) )
    {
        GMM_LOG_ERR("GMM_UpdateSysTlli():Error: TlliType is not correct.");
        return;
    }

    /* Added by s00217060 for coverity��foritfy�޸� , 2013-05-20, begin */
    /* ��ʼ�� */
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));
    /* Added by s00217060 for coverity��foritfy�޸� , 2013-05-20, end */

    /* û�д�����Ч��PTMSI, ����RANDOM TLLI */
    if (VOS_FALSE == NAS_GMM_GetPTmsiForTLLI(aucPtmsi))
    {
        GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, GMM_RANDOM_TLLI);

        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_RANDOM_TLLI;

        return;
    }

    /* �����µ�TLLIֵ */
    GMM_CharToUlong(&gstGmmCasGlobalCtrl.ulTLLI, aucPtmsi);


    GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, TlliType);

    gstGmmCasGlobalCtrl.ucflgTLLI = TlliType;

    return;
}

/*****************************************************************************
 Prototype      : GMM_GetPtmsiFromMsgIe
 Description    : ��ָ����ϢIE�еõ�PTMSI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
*****************************************************************************/
VOS_UINT32 GMM_GetPtmsiFromMsgIe(VOS_UINT8 *pData)
{
    VOS_UINT32  ulNewTlli = 0;
    VOS_UINT32  ulRslt;

    /* �ж�IE���������Ƿ���Ч */
    if ( (5 != *(pData))                                    /*����ֵ�Ƿ�*/
      || (0x04 != (*(pData+1) & 0x07) )                     /*���Ͳ�ƥ��*/
        )
    {/* ������Ч */
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe:WARNING: Wrong length or type in IE data");
        return GMM_FALSE;
    }

    /* ����GMMϵͳ��������PTMSIֵ */
    NAS_MML_SetUeIdPtmsi((pData + 2));
    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;

    GMM_CharToUlong(&ulNewTlli,
                    NAS_MML_GetUeIdPtmsi());  /*�����µ�TLLIֵ*/

    /* ����local TLLIֵ */
    GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);          /*����TLLI*/

    /* ָ��new TLLI */
    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
    ulRslt = GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI);
    if (GMM_FALSE == ulRslt)
    {
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe():Error: new TLLI assigned failed!");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/

#if (FEATURE_ON == FEATURE_PTM)
    /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
    NAS_GMM_SndAcpuOmChangePtmsi();
#endif

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_FreeOldTlli
 Description    : �ͷ�old TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2011-11-11
    Author      : h44270
    Modification: ���ⵥ�ţ�DTS2010110500099/DTS2010111103124,����GMM��Wģ����GAS����ȥָ����Ϣ
*****************************************************************************/
VOS_VOID GMM_FreeOldTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLC�ͷ�old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreeOldTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRR�ͷ�old TLLI */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_OLD_TLLI);
        if (VOS_NULL_PTR == pGasAssignMsg)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: making GAS message wrongly!");
            return;
        }
        /* ����ԭ�ﵽGRR */
        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
        if (VOS_OK != ulRet)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: Send msg fail!");
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_FreeSysTlli
 Description    : �ͷ�ϵͳĬ��TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2. ��    ��   : 2010��10��29��
     ��    ��   : l00167671/�޿���
     �޸�����   : ���ⵥ�ţ�DTS2010100802035,��ӻָ�LLC
*****************************************************************************/
VOS_VOID GMM_FreeSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLC�ͷ�old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN_SYS);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ��TLLIδָ���־ */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {

        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* �ָ�LLC���ݴ��� */
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignNewTlli
 Description    : ָ��new TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignNewTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* �滻ϵͳĬ��TLLI */
    gstGmmCasGlobalCtrl.ulOldTLLI = gstGmmCasGlobalCtrl.ulTLLI;
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* �޸�TLLI���ͱ�־ */

    /* ֪ͨLLCָ��new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_AssignModifyTlli
 Description    : �޸�TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-05-20
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignModifyTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* �滻ϵͳĬ��TLLI */
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* �޸�TLLI���ͱ�־ */

    /* ֪ͨLLCָ��new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_AssignSysTlli
 Description    : ָ��ͬ����ǰϵͳ��TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-15
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2011��12��8��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2011111603445,���յ�ϵͳ��Ϣ���Ҳ�2�Ѿ�ָ�ɺ���ָܻ�RABM
*****************************************************************************/
VOS_VOID GMM_AssignSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    GMM_OP_TLLI              TlliOpMode;
    VOS_UINT32               ulRet;

    /* �ж�TLLI�������� */
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        TlliOpMode = GMM_OP_TLLI_ASSIGN;                    /* ����ָ��TLLI */
    }
    else
    {
        TlliOpMode = GMM_OP_TLLI_SYNC;                      /* ͬ����ǰTLLI */
    }

    /* ֪ͨLLCͬ��ϵͳTLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(TlliOpMode);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (GMM_OP_TLLI_ASSIGN == TlliOpMode)
    {
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_TRUE;     /* TLLIָ����ɱ�־ */

        /* �ָ�RABM, bRatChangeFlgΪFALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making GAS message wrongly!");
        return;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignGsmKc
 Description    : ָ��GSM Kc
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-27
    Author      : Roger Leo
    Modification: Created function
  2.��    ��    : 2009��03��18��
    ��    ��    : l65478
    �޸�����    : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
*****************************************************************************/
VOS_VOID GMM_AssignGsmKc(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLCָ��Kc�ͼ����㷨 */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_KC);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: making LLC message wrongly!");
        return;
    }
    /* ���ü����㷨�Ѿ�ָ�� */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_TRUE;

    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: Send msg fail!");
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_SaveAuthenResult
 Description    : ����USIM����Ȩ���
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2013��07��23��
    ��    ��   : y00245242
    �޸�����   : Ϊ����VOLTE�������µ�USIM�ӿ�
*****************************************************************************/
VOS_VOID GMM_SaveAuthenResult(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    VOS_UINT8   i;
    VOS_UINT8  *pucAuthRes;

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    pucAuthRes = &(pAuthCnf->aucAuthRes[0]);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */

    /* ����GSM��Ȩ��� */
    if (GMM_UMTS_AUTHEN_UNSUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* û����չ���� */
        for (i=1; i<5; i++)
        {
            if (i > *(pucAuthRes))
            {
                g_GmmAuthenCtrl.aucRes[i-1] = 0xFF;         /* �����Чֵ */
            }
            else
            {
                /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-9, begin */
                g_GmmAuthenCtrl.aucRes[i-1] = *((pucAuthRes + i));
                /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-9, end */
            }
        }
        return;
    }

    /* ����RES�Ļ������� */
    if (4 > *(pucAuthRes))
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                   (pucAuthRes + 1),
                  *(pucAuthRes) );                          /* ����RES */

        for ( i=*(pucAuthRes); i<4; i++ )
        {
            g_GmmAuthenCtrl.aucRes[i] = 0xFF;
        }

        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* ��RES(EXTERN)�ĳ��ȣ�0:aucResExt������   */
    }
    else
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                (pucAuthRes + 1), 4 );                      /* ����RES */
        g_GmmAuthenCtrl.ucResExtLen =
               *(pucAuthRes) - 4;                           /* ��RES(EXTERN)�ĳ��ȣ�0:aucResExt������   */
    }

    /* ����RES��չ���� */
    if (0 < g_GmmAuthenCtrl.ucResExtLen)
    {
        if (12 < g_GmmAuthenCtrl.ucResExtLen)
        {
            g_GmmAuthenCtrl.ucResExtLen = 12;               /* ������Ч��RES Extension���� */
        }
        Gmm_MemCpy(g_GmmAuthenCtrl.aucResExt,
               (pucAuthRes + 5),
               g_GmmAuthenCtrl.ucResExtLen );               /* ����RES Extension */
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_UpdateAuthenCtrlFlg
 Description    : ���¼�Ȩ���ƽṹ�еı�־
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.��    ��    : 2007��01��13��
    ��    ��    : s46746
    �޸�����    : �������ⵥ�ţ�A32D08326
*****************************************************************************/
VOS_VOID GMM_UpdateAuthenCtrlFlg(VOS_VOID)
{
    VOS_UINT8   i;

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                       /* ��ʧ���ڴ�Ϊ��*/
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_TRUE;
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_TRUE;         /* �趨��ʧ���ڴ治Ϊ��*/

        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* ������һ�ε�RANDֵ*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }
        Gmm_TimerStart(GMM_TIMER_T3316);                    /* ����T3316*/
    }
    else
    {                                                       /* ��ʧ���ڴ治Ϊ��*/
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* ������һ�ε�RANDֵ*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }

        Gmm_TimerStart(GMM_TIMER_T3316);                    /* ����T3316*/
    }

    return;
}


/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRegNmlServ
 Description    : ��GMM_REGISTERED_NORMAL_SERVICE״̬��
                   ����GRRMM_PAGING_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2012��3��1��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�
  4.��    ��   : 2014��9��5��
    ��    ��   : w00167002
    �޸�����   : GCF.2.3.1.6 ʧ���޸ģ����յ� GAS��PAGING INDʱ������T3314����
                 �յ�LL�·������ݲ�������
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRegNmlServ(GRRMM_PAGING_IND_ST *pMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ����������                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* ����������IMSIѰ��������ATTACH         */
        }
        Gmm_PagingInd_common();
    }
    else
    {
        /* ���յ�PAGING INDʱ������READY״̬�����յ�LLC INFOMʱ���� */

        if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }


        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
         )
        {
            GMM_LOG_INFO("GMM_RcvGsmPagingAtRegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
    /*}*/
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtDeregInit
 Description    : ��GMM_DEREGISTERED_INITIATED״̬��
                   ����GRRMM_PAGING_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtDeregInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* ����Ϣ������ı�־                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;  /* ����RRMM_PAGING _IND�׵�ַ               */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* �ȴ���Ȩ��Ӧ                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* ͣ������ʱ��                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* ���ԭ��ȴ���־                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* ����״̬��ΪGU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                Gmm_Attach_Prepare();                                           /* ȫ�ֱ�������������Ϊattach����׼��     */
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRauInit
 Description    : ��GMM_ROUTING_AREA_UPDATING_INITIATED״̬��
                   ����GRRMM_PAGING_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRauInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* ����Ϣ������ı�־                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                  return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;       /* ����RRMM_PAGING _IND�׵�ַ              */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_PagingInd_common();
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPaging_RegPlmnSrch
 Description    : ��GMM_REGISTER_PLMN_SEARCH״̬��
                   ����GRRMM_PAGING_IND��Ϣ
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2009-07-20
    Author      : s46746
    Modification: Created function
  2.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
*****************************************************************************/
VOS_VOID GMM_RcvGsmPaging_RegPlmnSrch(GRRMM_PAGING_IND_ST *pMsg)
{
    if (GAS_IMSI != pMsg->ucMSIDType)
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PAGING);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PAGING;
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AuthType
 Description    : ������ǰ��Ȩ��������
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
 1.Date        : 2005-11-08
   Author      : Roger Leo
   Modification: Created function
 2.��    ��   : 2011��01��18��
   ��    ��   : lijun 00171473
   �޸�����   : W������SIM���յ������3G��ȨӦ�ð�2G��Ȩ����
 3.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*****************************************************************************/
VOS_UINT8 GMM_AuthType(VOS_UINT8 ucAutnFlag)
{
    VOS_UINT8                               usAuthTypeRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enCurRat;

    usAuthTypeRet = GMM_AUTH_FAILURE;
    enCurRat = NAS_MML_GetCurrNetRatType();
    switch (enCurRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:/*��UMTS������*/
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*��������USIM��*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;                      /*UMTS��Ȩ*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM_AUTH_UNACCEPTABLE;     /*GSM authentication unacceptable*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*��������SIM��*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                }
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*��������USIM��*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;          /*UMTS��Ȩ*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM;           /*GSM��Ȩ*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*��������SIM��*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                }
            }
            break;

        default:
            break;
    }

    /* ϵͳ���������UMTS��Ȩ */
    if ((GMM_FALSE == g_GmmAuthenCtrl.ucUmtsAuthFlg) && (GMM_AUTH_UMTS == usAuthTypeRet))
    {
        usAuthTypeRet = GMM_AUTH_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: perform the GSM authentication challenge");
    }

    return usAuthTypeRet;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RauCompleteHandling
 ��������  : RAU�����У��յ�RAU ACCEPT����Ҫ�ȴ�WRR��RABM�Ļظ���Ϣ��
             ���յ����лظ���Ϣ�󣬻ظ�����RAU COMPLETE��Ϣ����֪ͨMMC��ģ�顣
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��4��12��
    ��    ��   : l65478
    �޸�����   : AT2D18389,�ڳ�ʼС������ʱ��GMMӦ��֪ͨLLC����NULL֡
  3.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
  4.��    ��   : 2012��3��16��
    ��    ��   : s46746
    �޸�����   : DTS2012030603347:GSM��,GMM��������ע��,��PS�ɹ�,5�δ���CSע��,CS����ע��ʧ��,
                 �����ָ�GPRSʧ�ܵ����ֽ�������RAU,�γ�ע��ѭ��
  5.��    ��   : 2012��4��03��
    ��    ��   : l65478
    �޸�����   : DTS2012032603732:��RAUʧ��ʱ��ȴ��ӡ��RAU�ɹ�
  6.��    ��   : 2012��4��26��
    ��    ��   : l65478
    �޸�����   : DTS2012041707074:������RAU PS�ɹ�,CSʧ��ʱ,���һ��RAU ACCEPTû��֪ͨMM/MMCע����
  7.��    ��   : 2012��12��22��
    ��    ��   : l00171473
    �޸�����   : DTS2012122200186:����2G�Ĵ�����ʱû���ж�2G
  8.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  9.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_RauCompleteHandling( VOS_VOID )
{
    NAS_MSG_STRU                            *pSendNasMsg;
    GMM_MSG_RESOLVE_STRU                    stAttachAcceptIe;
    NAS_MSG_FOR_PCLINT_STRU                 stNasMsg;

    Gmm_MemSet(&stAttachAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));
    Gmm_MemSet(&stNasMsg, 0, sizeof(NAS_MSG_STRU));

    /* ����RAU complete��Ϣ */
    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_FALSE;
        pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);



        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            /* ֻ��ǰ����й�RAU suspend���˴�resume�������� */
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                             /* �ָ�LLC���ݴ��� */
                }
            }

            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
            GMM_InitCellUpdate(GMM_FALSE);                                                   /* С�����£���Ч�µ�READY TIMER */
        }


        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RauCompleteHandling:INFO: specific procedure ended");
    }

    /* RABM����RSP��Ϣ�����¼������:
       1��NORMAL RAU�ɹ�
       2��ϵͳ����ѡ/�л��ɹ�
       3��ϵͳ����ѡ/�л�ʧ��

       GMM��ATTEMP COUNTER����5����������¼������:
       1��RAUʧ��
       2������RAUʧ��
       3������RAUֻ��PS�ɹ�
       ����GMM��֪ͨMM/MMCע����ʱ,Ӧ��ֻ���ڵ��������֪ͨ�ɹ�,
       �����������Ӧ��֪ͨʧ��,������Ϊ���յ�ע����ʱ�Ѿ�֪ͨ,���Դ˴���������*/
    if (5 <= g_GmmRauCtrl.ucRauAttmptCnt)
    {
        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || ( (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
           && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == gstGmmSuspendCtrl.ucPreState)))
        {
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                           NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                           &stNasMsg,
                                           &stAttachAcceptIe);

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE);

            /*  �¼��ϱ� */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
    }

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_LOG_INFO("GMM_RauSuccessInterSys:Gmm rau success for intersystem change.");

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_ResumeSuccess();
    }

    /*����follow on ������������¼� */
    NAS_GMM_HandleDelayedEvent();
}


/*****************************************************************************
  �� �� ��  : NAS_GMM_GetGmmCasGlobalCtrl
  ��������  : ��ȡȫ�ֱ���gstGmmCasGlobalCtrl�ĵ�ַ
  �������  : ��
  �������  : ��
  �� �� ֵ  : GMM_CAS_CTRL_STRU*
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
GMM_CAS_CTRL_STRU* NAS_GMM_GetGmmCasGlobalCtrl(VOS_VOID)
{
    return &(gstGmmCasGlobalCtrl);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetMui
  ��������  : ��ȡȫ�ֱ���usMui��ֵ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usMui);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_IncreaseMui
  ��������  : usMui����
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_IncreaseMui(VOS_VOID)
{
    return ((NAS_GMM_GetGmmCasGlobalCtrl()->usMui)++);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetPowerOffDetachPsMui
  ��������  : ��ȡȫ�ֱ���usPowerOffDetachPsMui��ֵ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetPowerOffDetachPsMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_SetPowerOffDetachPsMui
  ��������  : ����usPowerOffDetachPsMui��ֵ
  �������  : VOS_UINT16                usMui
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_SetPowerOffDetachPsMui(
    VOS_UINT16                          usMui
)
{
    NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui = usMui;

    return;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_IsPowerOffPsDetachMsg
  ��������  : �ж��Ƿ���PS�ػ�DETACH��Ϣ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_TRUE: �ǹػ�PS DETACH��Ϣ
              VOS_FALSE:
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsPowerOffPsDetachMsg(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT32                          ulUsimMMApiIsTestCard;
    ulUsimMMApiIsTestCard             = NAS_USIMMAPI_IsTestCard();

    /* �����ǰ�ǹػ����̣���Я��NeedCnf��־ */
    if ( (GMM_MSG_LEN_DETACH_REQUEST    <= pstNasL3Msg->ulNasMsgSize)
      && (GMM_PD_GMM                    == pstNasL3Msg->aucNasMsg[0])
      && (GMM_MSG_DETACH_REQUEST        == pstNasL3Msg->aucNasMsg[1])
      && ((GMM_GPRS_DETACH_POWEROFF     == pstNasL3Msg->aucNasMsg[2])
       || (GMM_COMBINED_DETACH_POWEROFF == pstNasL3Msg->aucNasMsg[2]))
      && (VOS_FALSE                     == ulUsimMMApiIsTestCard    ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetCiphInd
  ��������  : ��ȡCiphInd
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT8
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���:ԭ���߼����к�����װ
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetCiphInd(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT8                           ucCiphInd;

    if (VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        ucCiphInd = 0;
    }
    else
    {
        if (GMM_PD_GMM == pstNasL3Msg->aucNasMsg[0])
        {
            switch(pstNasL3Msg->aucNasMsg[1])
            {
                case 0x01:
                case 0x04:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1c:
                case 0x15:
                case 0x16:
                case 0x08:
                case 0x0B:
                    ucCiphInd = 0;
                    break;

                default:
                    ucCiphInd = 1;
                    break;
            }
        }
        else
        {
             ucCiphInd = 1;
        }
    }

    return ucCiphInd;
}

/*lint -restore */
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
