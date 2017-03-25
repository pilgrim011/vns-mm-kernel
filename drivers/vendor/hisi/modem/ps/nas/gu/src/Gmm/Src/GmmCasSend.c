/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasSend.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : ��C�ļ�������GmmCasSendģ���ʵ��
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 �������ⵥA32D02368�޸�
  3. l40632 2006-04-17 �������ⵥA32D03141�޸�
  4. l40632 2006-04-27 �������ⵥA32D03429�޸�
  5. x51137 2006/4/28 A32D02889
  6. l40632 2006-05-29 �������ⵥA32D03821�޸�
  7. l40632 2006-06-19 �������ⵥA32D04282�޸�
  8. l40632 2006-07-12 �������ⵥA32D03834�޸�
  9.Date        : 2006-09-19
    Author      : s46746
    Modification: ���ⵥ��:A32D06255
 10.Date        : 2006-10-19
    Author      : L47619
    Modification: ���ⵥ��:A32D06916
 11.��    ��   : 2006��02��16��
    ��    ��   : luojian 60022475
    �޸�����   : ���ⵥ��:A32D08391
 12.��    ��   : 2007��05��25��
    ��    ��   : luojian 60022475
    �޸�����   : �������ⵥ��:A32D11232
 13.��    ��   : 2007��09��10��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D12829
 14.��    ��   : 2007��9��27��
    ��    ��   : s46746
    �޸�����   : ������Ч��Ϣ��RRMM_NAS_INFO_CHANGE��Ϣ���õ�
 15.��    ��   : 2007-10-26
    ��    ��   : hanlufeng
    �޸�����   : A32D13172
 20.��    ��   : 2007��12��04��
    ��    ��   : s46746
    �޸�����   : 1.GMMģ�����ATTACH��RAUʱ�������ʱ����������������
                   �ᵼ��LLC��ATTACH��RAU�ӳٷ��ͣ�ʹ��ATTACH��RAUʱ�������
                 2.GMM�ڽ���RAU����ʱ�����DRX�������ı䣬����������Ϣ��
                   ��DRX������������SGSN��RAUʱ�����ܵ������಻ʶ��UE��DR
                   X������  ʹ��RAU���ܳɹ���
 21.��    ��   : 2007��12��14��
    ��    ��   : s46746
    �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
 22.��    ��   : 2008��8��18��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05016���޸�CGREG��״̬�ж�
 23.��    ��   : 2008��9��10��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403���޸�CGREG��״̬
 24.��    ��   : 2008��10��21��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D06285����Ӷ�״̬GMM_REGISTERED_NO_CELL_AVAILABLECGREG���ж�
 25.��    ��   : 2008��12��02��
    ��    ��   : x00115505
    �޸�����   : AT2D06945:CREG��CGREG�����ϱ��޸�
 26.��    ��   : 2009��02��28��
    ��    ��   : o00132663
    �޸�����   : AT2D09507, �ڶ���ʱ��CREG,CGREG�ϱ�2:û��ע�ᣬ��MT������ѰҪע����µ���Ӫ�̡�
 27.��    ��   : 2009��04��11��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D10976/AT2D10989,gstGmmCasGlobalCtrl.ulReadyTimerValueʱ��Ϊ0xffffffff,���µ��帴λ
 28.��    ��   : 2009��6��30��
    ��    ��   : s46746
    �޸�����   : AT2D12561,3G2����GPRS��δ�������ܣ�NASָ�ɲ�2�����㷨�󣬲�2���������ݽ����˼���
 29.��    ��   : 2009��10��27��
    ��    ��   : x00115505
    �޸�����   : AT2D15257:CS detach�����У�PSע��״̬�ı�
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasUtranCtrlInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "NasGmmProcLResult.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASSEND_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/*VOS_UINT8               gaucGmmNasMsgTmp[GMM_NAS_MSG_DATA_MAX];*/                 /* ����NAS��Ϣ����ʱ������ */
/*VOS_UINT8               gaucGmmLlcDataReq[GMM_LLC_MSG_PDULEN_MAX];*/              /* ��LLC����data req����Ϣ�������� */

/* DRX������Split pg cycle code��Ӧ�� */
static VOS_UINT16       gausGmmDrxCycleCodeTab[GMM_DRX_CYCLE_CODE_TAB_MAX] =
{
    71,             /*code as 65*/
    72,             /*code as 66*/
    74,
    75,
    77,
    79,
    80,
    83,
    86,
    88,
    90,
    92,
    96,
    101,
    103,
    107,
    112,
    116,
    118,
    128,
    141,
    144,
    150,
    160,
    171,
    176,
    192,
    214,
    224,
    235,
    256,
    288,
    320,
    352             /*code as 98*/
};


/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM ������Ϣ����       -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_SndLlcDataReq
 Description    : ��TTF��ģ�鷢��LL_UNITDATA_REQ_MSG��Ϣ
                  HSS 4100 V200R001 ����
 Input          : NAS_MSG_STRU            *pstNasL3Msg,     NAS LAYER3��Ϣָ��
                  LL_NAS_UNITDATA_REQ_ST  *pstUnitDataReq   LL_NAS_UNITDATA_REQ��Ϣ����ָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2006��02��16��
    ��    ��   : luojian 60022475
    �޸�����   : ���ⵥ��:A32D08391
  3.��    ��   : 2009��04��11��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D10976/AT2D10989,gstGmmCasGlobalCtrl.ulReadyTimerValueʱ��Ϊ0xffffffff,���µ��帴λ
  4.��    ��   : 2011��04��20��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�DTS2011040804149����V3R1C31B027����RAU��PS ONLY�£�PMM_IDLE̬W2G��ѡ�󣬷���pingδ����RAU���̣��޷���������
  5.��    ��   : 2015��4��7��
    ��    ��   : wx270776
    �޸�����   : ���ⵥ��:DTS2015040701865�����ͨ�ػ��Ż���������Ϣ����
*****************************************************************************/
VOS_VOID GMM_SndLlcDataReq (
    NAS_MSG_STRU                       *pstNasL3Msg,
    LL_NAS_UNITDATA_REQ_ST             *pstUnitDataReq
)
{
    /* ������Ϣ���ݱ��� */
    LL_NAS_UNITDATA_REQ_MSG            *pstDataReqMsg = VOS_NULL_PTR;       /* �����͵���Ϣָ�� */
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;

    /* ��Ϣָ����Ч���ж� */
    if ( (VOS_NULL == pstNasL3Msg)
      || (VOS_NULL == pstUnitDataReq) )
    {
        /* ��Чָ�����ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndLlcDataReq():Error: Invaild pointer");

        return;
    }
    
    ulMsgLen = sizeof(LL_NAS_UNITDATA_REQ_MSG);
    
    /* ��LAYER3 NAS��Ϣ����С��4�ֽڣ�����4�ֽڳ��ȣ�����ȡ��Ϣʵ�ʳ��� */
    if ( (pstNasL3Msg->ulNasMsgSize) > sizeof(pstUnitDataReq->aucPdu) )
    {
        ulMsgLen = sizeof(LL_NAS_UNITDATA_REQ_MSG) + (pstNasL3Msg->ulNasMsgSize - sizeof(pstUnitDataReq->aucPdu)); 
    }

    /* ����������Ϣ */
    pstDataReqMsg = (LL_NAS_UNITDATA_REQ_MSG *)PS_ALLOC_MSG( WUEPS_PID_GMM, ulMsgLen - VOS_MSG_HEAD_LENGTH );
    if (VOS_NULL_PTR == pstDataReqMsg)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndLlcDataReq():Error: Failed in VOS_AllocMsg()");
        return;
    }
    
    /* DOPRA��Ϣͷ�̶��Ĳ��� */
    pstDataReqMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstDataReqMsg->ulReceiverPid        = UEPS_PID_LL;

    /* ��д��Ϣ���Ͳ��� */
    pstDataReqMsg->usMsgType            = ID_LL_UNITDATA_REQ;           /* LL_UNITDATA_REQ ��ϢID */
    pstDataReqMsg->usTransId            = GMM_LLC_TRANSID;              /* �ӽ��̣�������SAPI, GMMʹ��1 */

    /* ����֪ͨ��LL����Ϣ */
    Gmm_MemCpy( &(pstDataReqMsg->stUnitDataReq),
                pstUnitDataReq,
                (sizeof(LL_NAS_UNITDATA_REQ_ST) - sizeof(pstUnitDataReq->aucPdu)) );

    /* ����LAYER3 NAS��Ϣ */
    Gmm_MemCpy( pstDataReqMsg->stUnitDataReq.aucPdu,
                pstNasL3Msg->aucNasMsg,
                pstNasL3Msg->ulNasMsgSize );

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstDataReqMsg);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndLlcDataReq():Error: Failed in VOS_SendMsg()");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_ASSIGN_REQ_MSG��Ϣ
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
LL_GMM_ASSIGN_REQ_MSG *GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI ucAssignFlg)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg = VOS_NULL_PTR;

    pAssignReqMsg = (LL_GMM_ASSIGN_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(LL_GMM_ASSIGN_REQ_MSG) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_MakeLlgmmAssignReqMsg():Error: Failed in VOS_AllocMsg()");
        return pAssignReqMsg;
    }

    pAssignReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pAssignReqMsg->ulReceiverPid   = UEPS_PID_LL;

    /* ��д��Ϣ���� */
    pAssignReqMsg->usMsgType = ID_LL_GMM_ASSIGN_REQ;
    pAssignReqMsg->usTransId = GMM_LLC_TRANSID;

    /* TLLI�Ĳ������� */
    switch (ucAssignFlg)
    {
        case GMM_OP_TLLI_ASSIGN:        /* ָ��new TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLIָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* new TLLIֵ���� */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;                     /* ��ָ���־�Ĳ��� */
            break;

        case GMM_OP_TLLI_MODIFY:        /* �޸�new and old TLLI�������new TLLIָ��� */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLIָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* new TLLIֵ���� */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulOldTLLI;  /* old TLLIֵ���� */
            break;

        case GMM_OP_TLLI_UNASSIGN:      /* ȥָ��old TLLI����ǰ������Чold TLLI�������� */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLIָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* ȥָ���־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;                     /* ȥָ���־�Ĳ��� */
            break;

        case GMM_OP_TLLI_UNASSIGN_SYS:  /* ȥָ��Ĭ��TLLI��old TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLIָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            0xffffffff;                     /* ȥָ���־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* ������0xffffffff */
            break;

        case GMM_OP_TLLI_SYNC:          /* ͬ��LLC��TLLI */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_TLLI;        /* TLLIָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* ��ǰĬ��TLLI */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            0xffffffff;
            break;

        case GMM_OP_TLLI_KC:            /* ָ��Kc�ͼ����㷨 */
            pAssignReqMsg->stLlGmmAssReq.ucMask    =
                            LL_ASSIGN_REQ_MASK_CiphAlg;     /* �����㷨ָ����Ч��־ */
            pAssignReqMsg->stLlGmmAssReq.ulTlliNew =
                            gstGmmCasGlobalCtrl.ulTLLI;     /* ��ǰĬ��TLLI */
            pAssignReqMsg->stLlGmmAssReq.ulTlliOld =
                            gstGmmCasGlobalCtrl.ulOldTLLI;  /* Ĭ��old TLLI */
            break;

        default:
            break;
    }

    /* ��д�����㷨���� */
    pAssignReqMsg->stLlGmmAssReq.ucCiphAlg =
                        gstGmmCasGlobalCtrl.ucGprsCipherAlg;

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        pAssignReqMsg->stLlGmmAssReq.enCiphStartFlg = LL_GMM_CIPH_START;
    }
    else
    {
        pAssignReqMsg->stLlGmmAssReq.enCiphStartFlg = LL_GMM_CIPH_STOP;
    }

    /* ��дKc���� */
    Gmm_MemCpy(pAssignReqMsg->stLlGmmAssReq.aucKc,
                        NAS_MML_GetSimPsSecurityGsmKc(),
                        8);
    /* ��дRAND���� */
    Gmm_MemCpy(pAssignReqMsg->stLlGmmAssReq.ucRand,
                        g_GmmAuthenCtrl.aucRandSav,
                        16);

    return pAssignReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_TRIGGER_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
LL_GMM_TRIGGER_REQ_MSG *GMM_MakeLlgmmTriggerReqMsg(VOS_UINT8 ucCause)
{
    LL_GMM_TRIGGER_REQ_MSG   *pTriggerReqMsg = VOS_NULL_PTR;

    pTriggerReqMsg = (LL_GMM_TRIGGER_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(LL_GMM_TRIGGER_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pTriggerReqMsg)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_MakeLlgmmTriggerReqMsg():Error: Failed in VOS_AllocMsg()");
        return pTriggerReqMsg;
    }


    pTriggerReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTriggerReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pTriggerReqMsg->usMsgType = ID_LL_GMM_TRIGGER_REQ;

    /* ��д��Ϣ���� */
    pTriggerReqMsg->stLlGmmTrigReq.ulTlli  = gstGmmCasGlobalCtrl.ulTLLI;
    pTriggerReqMsg->stLlGmmTrigReq.ucCause = ucCause;
    pTriggerReqMsg->stLlGmmTrigReq.ucRsv   = 0;

    return pTriggerReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_SUSPEND_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
*****************************************************************************/
LL_GMM_SUSPEND_REQ_MSG *GMM_MakeLlgmmSuspendReqMsg(VOS_VOID)
{
    LL_GMM_SUSPEND_REQ_MSG   *pSuspendReqMsg = VOS_NULL_PTR;

    pSuspendReqMsg = (LL_GMM_SUSPEND_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_SUSPEND_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pSuspendReqMsg)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_MakeLlgmmSuspendReqMsg():Error: Failed in VOS_AllocMsg()");
        return pSuspendReqMsg;
    }


    pSuspendReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSuspendReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pSuspendReqMsg->usMsgType = ID_LL_GMM_SUSPEND_REQ;

    /* ��д��Ϣ���� */
    pSuspendReqMsg->aucReserve[0] = 0;
    pSuspendReqMsg->aucReserve[1] = 0;
    pSuspendReqMsg->aucReserve[2] = 0;
    pSuspendReqMsg->aucReserve[3] = 0;

    return pSuspendReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_RESUME_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-06
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
*****************************************************************************/
LL_GMM_RESUME_REQ_MSG *GMM_MakeLlgmmResumeReqMsg(VOS_UINT32  ulResumeType)
{
    LL_GMM_RESUME_REQ_MSG   *pResumeReqMsg = VOS_NULL_PTR;

    pResumeReqMsg = (LL_GMM_RESUME_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_RESUME_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pResumeReqMsg)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_MakeLlgmmResumeReqMsg():Error: Failed in VOS_AllocMsg()");
        return pResumeReqMsg;
    }


    pResumeReqMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pResumeReqMsg->ulReceiverPid   = UEPS_PID_LL;
    pResumeReqMsg->usMsgType = ID_LL_GMM_RESUME_REQ;

    /* ��д��Ϣ���� */
    pResumeReqMsg->ulResumeType = ulResumeType;

    return pResumeReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : ����GRRGMM_ASSIGN_REQ��Ϣ
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
GRRGMM_ASSIGN_REQ_ST *GMM_MakeGrrmmAssignReqMsg(VOS_UINT32 ulCause)
{
    GRRGMM_ASSIGN_REQ_ST    *pReqMsg;

    pReqMsg = (GRRGMM_ASSIGN_REQ_ST*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                        sizeof(GRRGMM_ASSIGN_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pReqMsg)
    {
        GMM_LOG_ERR("GMM_MakeGrrmmAssignReqMsg():Error: Failed in VOS_AllocMsg()");
        return pReqMsg;
    }

    pReqMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pReqMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pReqMsg->MsgHeader.ulMsgName  = GRRGMM_ASSIGN_REQ;

    /* ��д��Ϣ���� */
    pReqMsg->ulTlli     = gstGmmCasGlobalCtrl.ulTLLI;
    pReqMsg->ulOldTlli  = gstGmmCasGlobalCtrl.ulOldTLLI;

    pReqMsg->ulTlliCause = ulCause;

    return pReqMsg;
}

/*****************************************************************************
 Prototype      :
 Description    : ��2Gʱ����ٵ�RR���ӽ����ɹ���Ϣ
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
VOS_VOID GMM_SndRrmmEstCnfGsm(VOS_UINT8 ucRrmmEstOpid)
{
    RRMM_EST_CNF_STRU     *pRrEstCnf;
    VOS_UINT32             ulRet;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(RRMM_EST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pRrEstCnf)
    {
        /*��ӡ������Ϣ*/
        GMM_LOG_ERR("GMM_SndRrmmEstReqGsm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* ��дEST CNF��Ϣ���� */
    pRrEstCnf->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pRrEstCnf->MsgHeader.ulSenderPid     = WUEPS_PID_WRR;  /* ģ��WRRC���� */
    pRrEstCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pRrEstCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;   /* GMM���� */

    pRrEstCnf->MsgHeader.ulMsgName   = RRMM_EST_CNF;        /* ģ�ⷢ����Ϣ���� */

    pRrEstCnf->ulCnDomainId = RRC_NAS_PS_DOMAIN;
    pRrEstCnf->ulOpId       = ucRrmmEstOpid;
    pRrEstCnf->ulResult     = RRC_EST_SUCCESS;

    /* 2G�����£�����EST CNF��GMM��Ϣ���� */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pRrEstCnf);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndRrmmEstReqGsm():Error: Failed in VOS_SendMsg()");
        return;
    }
    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ��2Gʱ����ٵ�RR���ӽ����ɹ���Ϣ
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
  2.Date        : 2006-09-19
    Author      : s46746
    Modification: ���ⵥ��:A32D06255
*****************************************************************************/
VOS_VOID GMM_SndRrmmEstReqGsm(VOS_UINT8 ucRrmmEstOpid, NAS_MSG_STRU *pMsg)
{
    /*S_UINT8              ucCiphInd;*/
    /*VOS_UINT32             ulRet;*/
    GMM_SndRrmmEstCnfGsm(ucRrmmEstOpid);

#if 0
    /* ��RRMM_EST_REQ�е�NAS��Ϣ���ݷ���LLC */
    if ( (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
       /*||(GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)*/
       ||(0x20 == (g_GmmGlobalCtrl.ucState & 0xF0)) )
    {
        if (0 == gstGmmCasGlobalCtrl.ucGprsCipherAlg)
        {
            ucCiphInd = 0; /*0-LLC������*/
        }
        else
        {
            ucCiphInd = 1; /*1-LLC����*/
        }
    }
    else
    {
        ucCiphInd = 0; /*0-LLC������*/
    }

    /* ��LLC������Ϣ */
    GMM_SndLlcDataReq(LL_RADIO_PRI_1,/*RRC_NAS_MSG_PRIORTY_HIGH,*/ /* ��3G�ĺ����ӿ�ʹ�� */
                      ucCiphInd,
                      (VOS_UINT16)pMsg->ulNasMsgSize,
                      pMsg->aucNasMsg);
#endif

    GMM_SndRrmmDataReqGsm(pMsg);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ��2Gʱ����ٵ�RR�����ͷ���Ϣ
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
  2.Date        : 2007-10-26
    Author      : hanlufeng
    Modification: A32D13172
*****************************************************************************/
VOS_VOID GMM_SndRrmmRelReqGsm()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* ��дEST CNF��Ϣ���� */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulSenderPid      = WUEPS_PID_WRR;  /* ģ��WRRC���� */
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_GMM;   /* GMM���� */

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;    /* ģ�ⷢ����Ϣ���� */

    RrRelInd.ulCnDomainId               = RRC_NAS_PS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    /*ֱ�ӵ���GMM������ϢRRMM_REL_IND�ĺ���*/
    Gmm_RcvRrmmRelInd(&RrRelInd);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ��2Gʱ��LLC������������Ϣ
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
  2.Date        : 2006-09-19
    Author      : s46746
    Modification: ���ⵥ��:A32D06255
  3.��    ��    : 2009��03��18��
    ��    ��    : l65478
    �޸�����    : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
  4.��    ��    : 2015��4��9��
    ��    ��    : wx270776
    �޸�����    : ���ⵥ��:DTS2015040701865�����ͨ�ػ��Ż��������ж��Ƿ�Я��enNeedCnf��־��
                  ��Я����LL��gmm����Ϣ���͵�����󣬻�֪ͨ��GMM.�����ڹػ�ʱ��
                  PS��DETACH��Ϣ���͵�������LL֪ͨ��GMM��GMM������ΪPS��DETACH
                  ��ɣ���MMC�ظ��ػ�������ӿ�ػ��ٶȡ�
*****************************************************************************/
VOS_VOID GMM_SndRrmmDataReqGsm(
    NAS_MSG_STRU                       *pMsg
)
{
    VOS_UINT8                           ucCiphInd;
    PS_BOOL_ENUM_UINT8                  enNeedCnf;
    VOS_UINT16                          usMui;     
    LL_NAS_UNITDATA_REQ_ST              stUnitDataReq;

    /* ��ȡ���ܷ�ʽ */
    ucCiphInd       = NAS_GMM_GetCiphInd(pMsg);    
    enNeedCnf       = VOS_FALSE;
    usMui           = 0;
    PS_MEM_SET(&stUnitDataReq, 0x00, sizeof(LL_NAS_UNITDATA_REQ_ST));

    if(0 != gstGmmCasGlobalCtrl.ucGprsCipherAlg)
    {
        if(VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipherAssign)
        {
            GMM_AssignGsmKc();
        }
    }

    /* GSM�£��ڹػ�PS��DETACHʱ����ҪЯ��NeedCnf��־ */
    if (VOS_TRUE == NAS_GMM_IsPowerOffPsDetachMsg(pMsg))
    {
        (VOS_VOID)NAS_GMM_IncreaseMui();
        enNeedCnf   = VOS_TRUE;                
        usMui       = NAS_GMM_GetMui();
        NAS_GMM_SetPowerOffDetachPsMui(usMui);
    }

    /* �����Ϣ�ṹ�� */
    stUnitDataReq.ulTlli              = gstGmmCasGlobalCtrl.ulTLLI;
    stUnitDataReq.ucRadioPri          = LL_RADIO_PRI_1;
    stUnitDataReq.ucCiphInd           = ucCiphInd;
    stUnitDataReq.enNeedCnf           = enNeedCnf;
    stUnitDataReq.usMui               = usMui;
    stUnitDataReq.usPduLen            = (VOS_UINT16)pMsg->ulNasMsgSize;

    /* ����DATA REQ��Ϣ��LLC */
    GMM_SndLlcDataReq(pMsg, &stUnitDataReq);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttachStatus
 ��������  : ��ȡGMM��ע��״̬
 �������  : ��
 �������  : RRC_NAS_ATTACH_STATUS_ENUM_UINT32 ע��״̬
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : l00130025
    �޸�����   : DTS2011082201679/DTS2011121504358,W/G��ע��״̬û�и���
*****************************************************************************/
RRC_NAS_ATTACH_STATUS_ENUM_UINT32  NAS_GMM_GetAttachStatus(VOS_VOID)
{
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        return RRC_NAS_ATTACH;
    }
    else
    {
        return RRC_NAS_NOT_ATTACH;
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_GetPTmsiRAI_GUL
 ��������  : GUL��ģʱ����ȡPTMSI-GUL
 �������  : ��
 �������  : aucPtmsi    ��ȡ����PTMSI
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��8��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��25��
   ��    ��   : l65478
   �޸�����   : DTS2012041402691,���ӽ���ID���ʹ���
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetPTmsi_GUL(
    VOS_UINT8                           aucPtmsi[RRC_NAS_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    VOS_UINT8                           ucPtmsiValidFlg;

    ucPtmsiValidFlg          = GMM_UEID_P_TMSI;


    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();
    ulLocalPtmsiFlg     = VOS_FALSE;

    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    ulGetGutiRst            = NAS_GMM_MapPtmsiFromGUTI();
    enTinType               = NAS_MML_GetTinType();

    /* 4.7.3.1.1 GPRS attach procedure initiation (GMM_MAPPED_INFO_FROM_EPS_STRU)
       If the MS supports S1 mode, the MS shall handle the P-TMSI or IMSI IE as follows
    */
    if ( (NAS_MML_TIN_TYPE_GUTI == enTinType) && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else if ( ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType) || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
           && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*If the TIN is deleted,and the MS doesnot holds a valid P-TMSI and a RAI,and the MS holds a valid GUTI, the MS shall map the GUTI into the P-TMSI  */
    else if ( (NAS_MML_TIN_TYPE_INVALID  == enTinType)
           && (VOS_FALSE            == ulLocalPtmsiFlg)
           && (VOS_OK               == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType) && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    else
    {
        ucPtmsiValidFlg = GMM_UEID_INVALID;
        PS_MEM_SET(aucPtmsi, 0xff, NAS_MML_MAX_PTMSI_LEN);
    }

    return ucPtmsiValidFlg;

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetOldRai
 ��������  : GUL��ģʱ����ȡRAI
 �������  : ��
 �������  : aucPtmsi    ��ȡ����PTMSI
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��14��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_GMM_GetOldRai(
    GMM_RAI_STRU                       *pstGmmRai
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    GMM_RAI_STRU                       *pstMappedRai = VOS_NULL_PTR;
    VOS_UINT32                          ulGetGutiRst;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;

#if (FEATURE_ON == FEATURE_LTE)
    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    ucUeIdMask         = NAS_GMM_GetUeIdMask();
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    ulGetGutiRst            = NAS_GMM_MapRaiFromGUTI();
    enTinType               = NAS_MML_GetTinType();
    pstMappedRai            = NAS_GMM_GetMappedRaiAddr();

    if ( ((NAS_MML_TIN_TYPE_GUTI  == enTinType)
        && (VOS_OK  == ulGetGutiRst))
      || ((NAS_MML_TIN_TYPE_INVALID == enTinType)
        && (VOS_OK  == ulGetGutiRst)
        && (VOS_FALSE == ulLocalPtmsiFlg)) )
    {
        (VOS_VOID)VOS_MemCpy(pstGmmRai, pstMappedRai, sizeof(GMM_RAI_STRU));
        return;
    }
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &(pstGmmRai->Lai.PlmnId));

    pstGmmRai->ucRac          = pstLastSuccRai->ucRac;
    pstGmmRai->Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    pstGmmRai->Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetPTmsiRAI
 ��������  : ��ȡPTMSI��RAI
 �������  : ��
 �������  : NAS_INFO_PTMSI_RAI_STRU *pstPmsiRai,��ǰP-TMSI_RAI
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : l00130025
    �޸�����   : DTS2011082201679/DTS2011121504358,W/G��ע��״̬û�и���
  2.��    ��   : 2012��3��8��
    ��    ��   : w00176964
    �޸�����   : DTS2012031308021:GUL ��ģʱ��ȡPTMSI����
  3.��    ��   : 2012��5��14��
    ��    ��   : w00166186
    �޸�����   : DTS2012042406661:��WAS����NAS INFOʱ��old rai���

*****************************************************************************/
VOS_VOID  NAS_GMM_GetPTmsiRAI(
    NAS_INFO_PTMSI_RAI_STRU            *pstPtmsiRai
)
{

    GMM_RAI_STRU                      stGmmRai;
    NAS_MML_PLMN_ID_STRU              stPlmnId;

    /* ��ȡOLD RAI */
    NAS_GMM_GetOldRai(&stGmmRai);

    NAS_GMM_ConvertPlmnIdToMmcFormat(&stGmmRai.Lai.PlmnId, &stPlmnId);

    pstPtmsiRai->stPlmnId.ulMcc = stPlmnId.ulMcc;
    pstPtmsiRai->stPlmnId.ulMnc = stPlmnId.ulMnc;

    pstPtmsiRai->usLac = ((VOS_UINT16)stGmmRai.Lai.aucLac[1]
                       |(VOS_UINT16)((VOS_UINT16) stGmmRai.Lai.aucLac[0]<<8));

    pstPtmsiRai->ucRac = stGmmRai.ucRac;

#if (FEATURE_ON == FEATURE_LTE)
    (VOS_VOID)NAS_GMM_GetPTmsi_GUL(pstPtmsiRai->aucPtmsi);

#else
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus()  )
    {
        PS_MEM_SET(pstPtmsiRai->aucPtmsi, (VOS_CHAR)0xff, NAS_MML_MAX_PTMSI_LEN);
    }
    else
    {
        PS_MEM_CPY(pstPtmsiRai->aucPtmsi, NAS_MML_GetUeIdPtmsi(), NAS_MML_MAX_PTMSI_LEN);
    }
#endif


    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ��2Gʱ��GRR��NAS INFO CHANGE��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2006��12��5��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
  4.��    ��   : 2007��05��25��
    ��    ��   : luojian 60022475
    �޸�����   : �������ⵥ��:A32D11232
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2011��12��29��
    ��    ��   : l00130025
    �޸�����   : DTS2011082201679/DTS2011121504358,�л�ģʽ�����˺�W/G��ע��״̬û����NASͬ��
  7.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
  8.��    ��   : 2014��4��24��
    ��    ��   : s00217060
    �޸�����   : ��Lģ��ȡӳ��İ�ȫ������֮��֪ͨGUģ
*****************************************************************************/
VOS_VOID NAS_GMM_SndGasInfoChangeReq(VOS_UINT32 ulMask)
{
    GRRMM_NAS_INFO_CHANGE_REQ_STRU     *pSndMsg;
    GAS_NAS_INFO_ST                    *pNasInfo;

    pSndMsg = (GRRMM_NAS_INFO_CHANGE_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(GRRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);


    if (VOS_NULL_PTR == pSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndGasInfoChangeReq():Error: Failed in VOS_AllocMsg");
        return;
    }

    /* NAS��Ϣ������Ϣ������д */
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pSndMsg->MsgHeader.ulMsgName       = GRRMM_NAS_INFO_CHANGE_REQ;

    pNasInfo = &(pSndMsg->stNasInfo);

    PS_MEM_SET(pNasInfo, 0x0, sizeof(GAS_NAS_INFO_ST));
    pNasInfo->ulCnDomainId = RRC_NAS_PS_DOMAIN;             /* ��CN���־ */

    /* Attach״̬ȡֵ */
    if (RRC_NAS_MASK_ATTACH == (ulMask & RRC_NAS_MASK_ATTACH))
    {
        pNasInfo->bitOpAttach = VOS_TRUE;

        pNasInfo->ulAttach = NAS_GMM_GetAttachStatus();

    }

    /* ȡ��DRX���Ⱥ͵�ǰSplitPgCycleֵ */
    if (RRC_NAS_MASK_DRX == (ulMask & RRC_NAS_MASK_DRX))
    {
        pNasInfo->bitOpDrxLength = VOS_TRUE;

        /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
        pNasInfo->ulDrxLength = (VOS_UINT32)NAS_MML_GetNonDrxTimer();
        pNasInfo->ulSplitPgCycle = GMM_CasGetSplitCycle(NAS_MML_GetSplitPgCycleCode());
        /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */
    }

    /* CK ��Ϣ�����ı� */
    if (RRC_NAS_MASK_SECURITY_KEY == (ulMask & RRC_NAS_MASK_SECURITY_KEY))
    {
        pNasInfo->bitOpSecurityKey = VOS_TRUE;

        Gmm_MemCpy(pNasInfo->stSecurityKey.aucKc,
                   NAS_MML_GetSimPsSecurityGsmKc(),
                   NAS_MML_GSM_KC_LEN);
    }

    /* P_TMSI��RAI��ֵ */
    if (RRC_NAS_MASK_PTMSI_RAI == (ulMask & RRC_NAS_MASK_PTMSI_RAI))
    {
        pNasInfo->bitOpPTmsiRai = VOS_TRUE;

        NAS_GMM_GetPTmsiRAI(&(pNasInfo->stPtmsiRai));

    }

    if (RRC_NAS_MASK_DEL_KEY == (ulMask & RRC_NAS_MASK_DEL_KEY))
    {
        pNasInfo->bitOpDelKey = VOS_TRUE;
    }

    /* GMM����״̬��� */
    if (NAS_GSM_MASK_GSM_GMM_STATE == (ulMask & NAS_GSM_MASK_GSM_GMM_STATE))
    {
        pNasInfo->bitOpGmmState = VOS_TRUE;

        pNasInfo->ucGsmGmmState = GMM_CasGetGmmState();
    }

    /* NAS_GSM_MASK_READY_TIMER��� */
    if (NAS_GSM_MASK_READY_TIMER == (ulMask & NAS_GSM_MASK_READY_TIMER))
    {
        pNasInfo->bitOpReadyTime    = VOS_TRUE;

        pNasInfo->ulReadyTimerValue = gstGmmCasGlobalCtrl.ulReadyTimerValue;
    }

    /* GMM��ǰMS GPRSģʽ��� */
    if (NAS_GSM_MASK_MS_GPRS_MODE == (ulMask & NAS_GSM_MASK_MS_GPRS_MODE))
    {
        pNasInfo->bitOpGprsMode = VOS_TRUE;

        pNasInfo->ucMsGprsMode  = GMM_CasGetMsGprsMode();
    }


    /* GMM��ǰNAS_GSM_MASK_MAPPED_SECURITY_KEY��� */
    if (NAS_GSM_MASK_MAPPED_SECURITY_KEY == (ulMask & NAS_GSM_MASK_MAPPED_SECURITY_KEY))
    {
        pNasInfo->bitOpIdleMappedLSecurity = VOS_TRUE;

        Gmm_MemCpy(pNasInfo->stSecurityKey.aucKc,
                   NAS_MML_GetSimPsSecurityGsmKc(),
                   NAS_MML_GSM_KC_LEN);
    }

    /* ��GAS����INFO_CHANGE_REQ */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_GMM, pSndMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "GMM_SndGasInfoChangeReq():Error: Failed in GMM_SndGasMsg()");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : 2G������֪ͨGASģ��GMM��Ϣ����
                  HSS 4100 V200R001 ����
                  GMM��Ϣ���̰���:
                  GMM ATTACH
                  GMM RAU
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-11-21
    Author      : l00107747
    Modification: Created function
  2.��    ��   : 2014��05��22��
    ��    ��   : W00242748
    �޸�����   : DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS
*****************************************************************************/
VOS_VOID NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ENUM_UINT16 usProcType,
                                  RRMM_GMM_PROC_FLAG_ENUM_UINT16 usProcFlag)
{
    RRMM_GMM_PROC_NOTIFY_STRU          *pstGmmProcNotify;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceivePid;

    pstGmmProcNotify = (RRMM_GMM_PROC_NOTIFY_STRU *)PS_ALLOC_MSG(
                    WUEPS_PID_GMM,
                    sizeof(RRMM_GMM_PROC_NOTIFY_STRU)
                    - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstGmmProcNotify)
    {
        /*��ӡ������Ϣ*/
        GMM_LOG_ERR("GMM_SndRrmmGmmProcNotify():Error: Failed in VOS_AllocMsg()");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstGmmProcNotify + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RRMM_GMM_PROC_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ú����ڱ�����ʱ������GU�� */
    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType() )
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else
    {
        ulReceivePid = WUEPS_PID_WRR;
    }

    /* ��дGRRGMM_GPRS_PROC_FINISHED_IND��Ϣ���� */
    pstGmmProcNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGmmProcNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstGmmProcNotify->stMsgHeader.ulMsgName       = RRMM_GMM_PROC_NOTIFY;
    pstGmmProcNotify->usGmmProcFlag               = usProcFlag;
    pstGmmProcNotify->usGmmProcType               = usProcType;

    /* 2G�����£�����GMM��Ϣ */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstGmmProcNotify);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndRrmmGmmProcNotify():Error: Failed in VOS_SendMsg()");
        return;
    }
}

/*****************************************************************************
�� �� ��  : GMM_SndRrmmGmmProcAns
��������  : ����RRMM_GMM_PROC_ENQԭ��
�������  : ��
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��: 2014��05��23��
  ��    ��: w00242748
  �޸�����: DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS

*****************************************************************************/
VOS_VOID NAS_GMM_SndRrmmGmmProcAns(VOS_VOID)
{
    RRMM_GMM_PROC_ANS_STRU             *pstGmmProcAns;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceivePid;
    RRMM_GMM_PROC_CONN_TYPE_ENUM_UINT16 enConnType;

    pstGmmProcAns = (RRMM_GMM_PROC_ANS_STRU *)PS_ALLOC_MSG(
                    WUEPS_PID_GMM,
                    sizeof(RRMM_GMM_PROC_ANS_STRU)
                    - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstGmmProcAns)
    {
        /*��ӡ������Ϣ*/
        GMM_LOG_ERR("GMM_SndRrmmGmmProcAns():Error: Failed in VOS_AllocMsg()");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstGmmProcAns + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RRMM_GMM_PROC_ANS_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ú����ڱ�����ʱ������GU�� */
    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType() )
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else
    {
        ulReceivePid = WUEPS_PID_WRR;
    }

    enConnType = RRMM_GMM_PROC_CONN_TYPE_NO_CONN;

    if ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_ATTACH_SIG_CONN;
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_RAU_SIG_CONN;
    }
    else if ( GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState )
    {
        enConnType = RRMM_GMM_PROC_CONN_TYPE_PS_SERVICE_CONN;
    }
    else
    {

    }

    /* ��дGRRGMM_GPRS_PROC_FINISHED_IND��Ϣ���� */
    pstGmmProcAns->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGmmProcAns->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstGmmProcAns->stMsgHeader.ulMsgName       = RRMM_GMM_PROC_ANS;
    pstGmmProcAns->enGmmConnType               = enConnType;

    /* 2G�����£�����GMM��Ϣ */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstGmmProcAns);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndRrmmGmmProcAns():Error: Failed in VOS_SendMsg()");
        return;
    }
}



/*****************************************************************************
 Prototype      : GMM_SndRabmRauInd
 Description    : ��RABM����GMMRABM_ROUTING_AREA_UPDATE_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2006-10-19
    Author      : L47619
    Modification: ���ⵥ��A32D06916
*****************************************************************************/
VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause, VOS_UINT8 ucResult)
{
    GMMRABM_ROUTING_AREA_UPDATE_IND_MSG *pRauInd;
    VOS_UINT32          ulRet;

    pRauInd = (GMMRABM_ROUTING_AREA_UPDATE_IND_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(GMMRABM_ROUTING_AREA_UPDATE_IND_MSG)
                - VOS_MSG_HEAD_LENGTH );
    if (VOS_NULL_PTR == pRauInd)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndRabmRauInd():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* ��д��Ϣ���� */
    pRauInd->ulTLLI        = gstGmmCasGlobalCtrl.ulTLLI;
    pRauInd->ucGmmRauCause = ucRauCause;
    pRauInd->ucResult      = ucResult;
    Gmm_MemSet(&pRauInd->aucRecvNPDUNumListIE[0],
                    0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN);
    if ( (0 < g_GmmRauCtrl.ucNpduCnt)
      && (RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN > g_GmmRauCtrl.ucNpduCnt) )
    {/* N-PDU NUMBER ��Ч */
        pRauInd->aucRecvNPDUNumListIE[0] = 0x26;        /*N-PDU IEI*/
        pRauInd->aucRecvNPDUNumListIE[1] = g_GmmRauCtrl.ucNpduCnt;
        Gmm_MemCpy(&pRauInd->aucRecvNPDUNumListIE[2],
                   &g_GmmRauCtrl.aucNpduNum[0],
                    g_GmmRauCtrl.ucNpduCnt);                                     /* ��дN-PDU NUMBER                         */
    }
    /*else
    {*/ /* N-PDU NUMBER ��Ч */
    /*    VOS_MemSet(&pRauInd->aucRecvNPDUNumListIE[0],
                    0, RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN);
    }*/

    /* ��дDOPRA��Ϣͷ */
    pRauInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pRauInd->MsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pRauInd->MsgHeader.ulMsgName   = ID_GMM_RABM_ROUTING_AREA_UPDATE_IND;

    PS_MEM_SET(pRauInd->aucReserve,0x00,sizeof(pRauInd->aucReserve));

    /* ��RABM������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pRauInd);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GMM_SndRabmRauInd():Error: Failed in VOS_SendMsg()");
    }

    return;
}


/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_SUSPEND_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndLlcSuspendReq(VOS_VOID)
{
    LL_GMM_SUSPEND_REQ_MSG  *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;
    /* TLLI��Ч���ж� */
    /*if (GMM_LOCAL_TLLI != gstGmmCasGlobalCtrl.ucflgTLLI)*/
    /*{*/ /*û��LOCAL TLLI��˵��û�����ATTACH*/
     /*û��ATTACH���ǲ����ܴ���LLC���ݴ���*/
     /*û�����ݴ��䣬����Ҫ����LLC*/
    /*    GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: Is not GMM_LOCAL_TLLI");*/
    /*    return;*/
    /*}*/
    /* ������Ϣ */
    pSendMsg = GMM_MakeLlgmmSuspendReqMsg();
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: message make unsuccessfully!");
        return;
    }

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcSuspendReq():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_ABORT_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-12-12
    Author      : s46746
    Modification: Created function
  2.��    ��   : 2009��06��30��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��AT2D12655,�������LLC�������͵Ĵ���
*****************************************************************************/
VOS_VOID Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType)
{
    LL_GMM_ABORT_REQ_MSG    *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;

    pSendMsg = (LL_GMM_ABORT_REQ_MSG*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                sizeof(LL_GMM_ABORT_REQ_MSG) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pSendMsg)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("Gmm_SndLlcAbortReq():Error: Failed in VOS_AllocMsg()");
        return;
    }

    pSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSendMsg->ulReceiverPid   = UEPS_PID_LL;
    pSendMsg->usMsgType       = ID_LL_GMM_ABORT_REQ;
    pSendMsg->enClearDataType = ucClearDataType;

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("Gmm_SndLlcAbortReq():Error: Send msg fail!");
    }

    return;
}


/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_RESUME_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-05
    Author      : Roger Leo
    Modification: Created function
  2.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
*****************************************************************************/
VOS_VOID GMM_SndLlcResumeReq(VOS_UINT32  ulResumeType)
{
    LL_GMM_RESUME_REQ_MSG   *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32               ulRet;
    /* TLLI��Ч���ж� */
    /*if (GMM_LOCAL_TLLI != gstGmmCasGlobalCtrl.ucflgTLLI)*/
    /*{*/ /*û��LOCAL TLLI��˵��LLCû�����ݴ���*/
     /*�������LLC��Ҳ�Ͳ���Ҫ�ָ�LLC����*/
    /*    GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Is not GMM_LOCAL_TLLI");*/
    /*  return;*/
    /*}*/
    /* ������Ϣ */
    pSendMsg = GMM_MakeLlgmmResumeReqMsg(ulResumeType);
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Message make unsuccessfully!");
        return;
    }

    if (LL_GMM_RESUME_TYPE_SIGNAL != ulResumeType)
    {
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcResumeReq():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ����LL_GMM_TRIGGER_REQ��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-14
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndLlcTriggerReq(VOS_UINT8 ucCause)
{
    LL_GMM_TRIGGER_REQ_MSG   *pSendMsg = VOS_NULL_PTR;
    VOS_UINT32                ulRet;

    pSendMsg = GMM_MakeLlgmmTriggerReqMsg(ucCause);
    if (VOS_NULL_PTR == pSendMsg)
    {
        GMM_LOG_ERR("GMM_SndLlcTriggerReq():Error: Failed in GMM_MakeLlgmmTriggerReqMsg()");
        return;
    }


    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pSendMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_SndLlcTriggerReq():Error: Send msg fail!");
    }

    return;
}


/*****************************************************************************
 Prototype      : GMM_SndMmcSuspendRsp
 Description    : ��MMC����MMCGMM_SUSPEND_RSP ��Ϣ
                  HSS 4121 V100R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-04-05
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_SndMmcSuspendRsp(VOS_VOID)
{
    MMCGMM_SUSPEND_RSP_ST              *pstMsg;
    MMCGMM_SUSPEND_RSP_ST              *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_SUSPEND_RSP_ST);

    pstInternalMsg  = (MMCGMM_SUSPEND_RSP_ST*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_SUSPEND_RSP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*****************************************************************************
 Prototype      :
 Description    : ���DRX�����е�Split pg cycleֵ
                  ����Split pg cycle code�б�����Ӧ��Split pg cycle
                  HSS 4121 V100R001 ����
 Input          :
 Output         :
 Return Value   : VOS_UINT32
                  704           ��Ч��no DRX
                  ����ֵ        ��Ч��Split pg cycle

 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-06-14
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_CasGetSplitCycle(VOS_UINT8 ucSplitCode)
{
    VOS_UINT32      ulSplitCycle = 0;

    /* ��Ч��no DRX */
    if (0 == ucSplitCode)
    {
        return 704;
    }

    /* code 1 to 64 */
    if (65 > ucSplitCode)
    {
        ulSplitCycle = ucSplitCode;
        return ulSplitCycle;
    }

    /* ����split cycle��split code����ȡ�� */
    if (GMM_DRX_CYCLE_CODE_NUMBER < ucSplitCode)
    {
        ulSplitCycle = 32;              /* Ĭ����Чֵ */
    }
    else
    {
        ulSplitCycle = gausGmmDrxCycleCodeTab[ucSplitCode-65];
    }

    return ulSplitCycle;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SndMmcResumeRsp
 ��������  : GMM��mmc����resume rsp
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_SndMmcResumeRsp(VOS_VOID)
{
    MMCGMM_RESUME_RSP_ST               *pstMsg;
    MMCGMM_RESUME_RSP_ST               *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_RESUME_RSP_ST);

    pstInternalMsg  = (MMCGMM_RESUME_RSP_ST*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_RESUME_RSP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_SndRabmSysSrvChgInd
 ��������  : ����ID_GMM_RABM_SYS_SRV_CHG_IND��RABM
 �������  : enSysMode          - ��ǰϵͳģʽ
             bRatChangeFlg      - ��ϵͳ�л���־
             bDataSuspendFlg    - �����־
             ucRebuildRabFlag   - RAB�Ƿ���Ҫ�ؽ�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II ����:֧��GUL��ϵͳHO CCO

  3.��    ��   : 2011��8��19��
    ��    ��   : w00167002
    �޸�����   : V7R1 Phase II ����:�����ֶ�����

*****************************************************************************/
VOS_VOID NAS_GMM_SndRabmSysSrvChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    VOS_BOOL                            bRatChangeFlg,
    VOS_BOOL                            bDataSuspendFlg,
    VOS_UINT8                           ucRebuildRabFlag
)
{
    GMM_RABM_SYS_SRV_CHG_IND_STRU      *pstSysSrvChgInd;

    /* ������Ϣ */
    pstSysSrvChgInd = (GMM_RABM_SYS_SRV_CHG_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_GMM,
                            sizeof(GMM_RABM_SYS_SRV_CHG_IND_STRU));
    if (VOS_NULL_PTR == pstSysSrvChgInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,
            "NAS_GMM_SndRabmSysSrvChgInd: Memory alloc failed.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSysSrvChgInd + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(GMM_RABM_SYS_SRV_CHG_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSysSrvChgInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysSrvChgInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstSysSrvChgInd->stMsgHeader.ulMsgName       = ID_GMM_RABM_SYS_SRV_CHG_IND;

    /* ��д��Ϣ���� */
    pstSysSrvChgInd->enSysMode          = enSysMode;
    pstSysSrvChgInd->bRatChangeFlg      = bRatChangeFlg;
    pstSysSrvChgInd->bDataSuspendFlg    = bDataSuspendFlg;

    pstSysSrvChgInd->ucRebuildRabFlag   = ucRebuildRabFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstSysSrvChgInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,
            "NAS_GMM_SndRabmSysSrvChgInd: Send message failed.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SndGasGprsAuthFailNotifyReq
 ��������  : ����3�μ�Ȩ����ʱ��֪ͨGAS,�ο�T3302��ʱ����Bar����ǰС��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : l00130025
    �޸�����   : DTS2012032004389��Netork����3�α�Ms Auth Rej��T3318/T3320��ʱʱ��û��֪ͨGAS Bar����ǰС��,
                 ���Э��TS 24.008 4.3.2.6.1 & 4.7.7.6,Ts43.022 3.5.5
                 If the MS deems that the network has failed the authentication check,
                 then it shall request RR or RRC to release the RR connection and the PS signalling connection, if any,
                 and bar the active cell or cells (see 3GPP TS 25.331 [23c] and 3GPP TS 44.018 [84]).
*****************************************************************************/
VOS_VOID  NAS_GMM_SndGasGprsAuthFailNotifyReq(VOS_VOID)
{

    RRMM_AUTH_FAIL_NOTIFY_REQ_STRU      *pMsg;
    VOS_UINT32                           ulRet;

    if (NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
		return;
	}

    pMsg = (RRMM_AUTH_FAIL_NOTIFY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                  sizeof(RRMM_AUTH_FAIL_NOTIFY_REQ_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;

    pMsg->MsgHeader.ulMsgName       = RRMM_AUTH_FAIL_NOTIFY_REQ;

    pMsg->ulT3302TimerLen           = g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);

    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM,"NAS_GMM_SndGasGprsAuthFailNotifyReq:ERROR: Send msg Fail.");
    }

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
