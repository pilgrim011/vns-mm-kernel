/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcProcSuspend.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2011��8��03��
  ����޸�   :
  ��������   : MMC������ϵͳ����ʱ����ع���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��08��03��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasComm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmlLib.h"
#include "NasMmcProcSuspend.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
#include "NasMmcSndOm.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
#include "NasMmcSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_SUSPEND_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************�˴�Ϊ��ϵͳ����ʱ�������õĺ�����ȡ********************************************/
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmSysChngTypeToMmcType
 ��������  : ��LMM�ϱ�����ϵͳ��ѡ����ת��ΪMMC�ڲ�����ѡ����
 �������  : MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
 �������  : MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��14��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��04��24��
    ��    ��   : w00166186
    �޸�����   : DTS2012042303735����L CCO��G������ѡ��L����һ��TAUʧ��
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmSysChngTypeToMmcType(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
)
{
    switch ( enSysChngType )
    {
        case MMC_LMM_SUS_TYPE_RSL :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLRESELECT;
            break;

        case MMC_LMM_SUS_TYPE_HO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_HANDOVER;
            break;

        case MMC_LMM_SUS_TYPE_CCO :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE;
            break;

        case MMC_LMM_SUS_TYPE_REDIR :
            *penSuspendCause = MMC_SUSPEND_CAUSE_REDIRECTION;
            break;

        case MMC_LMM_SUS_TYPE_CCO_REVERSE :
            *penSuspendCause = MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK;
            break;

        default:
            *penSuspendCause = MMC_SUSPEND_CAUSE_BUTT;
            break;
    }
    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmSysChngDirToMmcType
 ��������  : ��LMM�ϱ�����ϵͳ��ѡ��������ת��ΪMMC�ڲ�����ѡ����������
 �������  : MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
 �������  : penSuspendDestination:����Ŀ�ķ�
             penSuspendOrigen:������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��14��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
 2. ��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����:���ӹ�����
 3. ��    ��   : 2014��1��26��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ���ӵ�Lte��CDMA����ѡ���ض���
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmSysChngDirToMmcType(
    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
    MMC_SUSPEND_DESTINATION_UINT8      *penSuspendDestination,
    MMC_SUSPEND_ORIGEN_UINT8           *penSuspendOrigen
)
{
    switch ( ulSysChngDir )
    {
        case MMC_LMM_SYS_CHNG_DIR_L2W:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_WCDMA;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_L2G:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_GSM;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;

        case MMC_LMM_SYS_CHNG_DIR_G2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_GSM;
            break;

        case MMC_LMM_SYS_CHNG_DIR_W2L:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_LTE;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_WCDMA;
            break;

        /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
        /* ����L2C case�Ĵ�������ΪLTE��Ŀ�ķ�ΪCDMA */
        case MMC_LMM_SYS_CHNG_DIR_L2C:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_HRPD;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_LTE;
            break;
        /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

        default:
            *penSuspendDestination  = MMC_SUSPEND_DESTINATION_BUTT;
            *penSuspendOrigen       = MMC_SUSPEND_ORIGEN_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmSuspendMsgToGUtype
 ��������  : ��LMM�ϱ�����ϵͳ��ѡ��������ת��ΪMMC�ڲ�����ѡ����������
 �������  : pstLmmSuspendIndMsg:LTE�Ĺ�����Ϣ
 �������  : pstGuSuspendIndMsg:GU�Ĺ�����Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    NAS_MMC_ConvertLmmSuspendMsgToGUtype(
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendIndMsg,
    RRMM_SUSPEND_IND_ST                *pstGuSuspendIndMsg
)
{
    /* ת��L�Ĺ�������ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLmmSuspendIndMsg->ulSysChngType,&(pstGuSuspendIndMsg->ucSuspendCause));

    /* Lģ�£�SUSPEND��������GU�²�ͬ��ת��һ��SUSPEND������ */
    NAS_MMC_ConvertLmmSysChngDirToMmcType(pstLmmSuspendIndMsg->ulSysChngDir,
                                          &(pstGuSuspendIndMsg->ucSuspendDestination),
                                          &(pstGuSuspendIndMsg->ucSuspendOrigen));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndLmmEquPlmn_InterSysChangeLte
 ��������  : ��ϵͳ��Lʱ����LMM���͵�Ч�����б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��01��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  3.��    ��   : 2012��10��23��
    ��    ��   : z00161729
    �޸�����   : DTS2012082401763:��ϵͳ��L֪ͨL��Чplmnʱ��Ҫɾ��forbidden plmn
  4.��    ��   : 2013��12��18��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ

  5.��    ��   : 2014��1��9��
    ��    ��   : w00167002
    �޸�����   : DTS2014010305488:��L��24005��ע��ɹ����û�ָ����46009���û��������
               ���У���W��ANYCELLפ����������绰ҵ�񡣺�W��ϵͳ��ѡ��L�µ�24005
               �����ϣ�LMMֱ�Ӹ�MMC�ϱ�TAU�ɹ���
  6.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
  7.��    ��   : 2015��12��02��
    ��    ��   : j00174725
    �޸�����   : DTS2015102004448
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmEquPlmn_InterSysChangeLte()
{
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId   = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;
    VOS_UINT32                                              ulIsSimPlmnIdInDestBcchPlmnList;
    VOS_UINT32                                              ulIsBcchPlmnIdInDestSimPlmnList;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
    PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();

    ulEplmnValidFlg     = NAS_MML_GetEplmnValidFlg();
    ulRegFlag           = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    ulIsSimPlmnIdInDestBcchPlmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    ulIsBcchPlmnIdInDestSimPlmnList = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                                            stSndEquPlmnInfo.ucEquPlmnNum,
                                                                            stSndEquPlmnInfo.astEquPlmnAddr);

    /* �ֶ�ģʽ�£�����û�ָ�������粻��EPLMN�б��У���֪ͨLMM��ǰ��EPLMN��ϢΪ�û�ָ��������
       ����֪ͨLMM��ǰEPLMN��Ϣ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        if ( (VOS_FALSE == ulIsSimPlmnIdInDestBcchPlmnList)
           && (VOS_FALSE == ulIsBcchPlmnIdInDestSimPlmnList) )
        {
            if ( (VOS_TRUE == ulRegFlag)                                        /* ָ��PLMNע��ɹ� */
              && (VOS_TRUE == ulEplmnValidFlg) )                                /* EPLMN ��־���� */
            {
                /* ��ָ���ѷ������ */
                stSndEquPlmnInfo.ucEquPlmnNum++;
                stSndEquPlmnInfo.ucEquPlmnNum = (stSndEquPlmnInfo.ucEquPlmnNum <= NAS_MML_MAX_EQUPLMN_NUM) ? stSndEquPlmnInfo.ucEquPlmnNum : NAS_MML_MAX_EQUPLMN_NUM;
                stSndEquPlmnInfo.astEquPlmnAddr[stSndEquPlmnInfo.ucEquPlmnNum - 1].ulMcc = pstUserSpecPlmnId->stPlmnId.ulMcc;
                stSndEquPlmnInfo.astEquPlmnAddr[stSndEquPlmnInfo.ucEquPlmnNum - 1].ulMnc = pstUserSpecPlmnId->stPlmnId.ulMnc;
            }
            else
            {
                /* ֻ׼��֪ͨ�û�ָ�������� */
                stSndEquPlmnInfo.ucEquPlmnNum = 1;
                stSndEquPlmnInfo.astEquPlmnAddr[0].ulMcc = pstUserSpecPlmnId->stPlmnId.ulMcc;
                stSndEquPlmnInfo.astEquPlmnAddr[0].ulMnc = pstUserSpecPlmnId->stPlmnId.ulMnc;
            }
        }
    }

    NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
    NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
    NAS_MMC_SndOmEquPlmn();
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSuspendRsp
 ��������  : �����㷢�͹���ظ�
 �������  : enRat:��Ҫ���͵Ľ��뼼��
             enSuspendRslt:������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    NAS_MMC_SndSuspendRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    if ( RRC_NAS_SUSPEND_SUCCESS == enSuspendRslt)
    {
        ulRslt = MMC_LMM_SUCC;
    }
    else
    {
        ulRslt = MMC_LMM_FAIL;
    }

#endif

    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, UEPS_PID_GAS);
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendRsp(enSuspendRslt, WUEPS_PID_WRR);
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendRsp(ulRslt);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRsp:Unexpected Rat Type!");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndResumeRsp
 ��������  : �����㷢�ͻָ��ظ�
 �������  : enRat:��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID    NAS_MMC_SndResumeRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* ����RRMM_RESUME_RSP */
            NAS_MMC_SndAsResumeRsp(WUEPS_PID_WRR);

#if (FEATURE_ON == FEATURE_LTE)
            /* ֪ͨLMM�ָ���� */
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsResumeRsp(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                NAS_MMC_SndLmmResumeNotify();
            }

#endif
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndResumeRsp:Unexpected Rat Type!");
            break;
    }

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_BulidResumeMsg
 ��������  : ����ָ���Ϣ
 �������  : enRat:��Ҫ�Ǹ����뼼�����лָ�
 �������  : pstMsg:��������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID    NAS_MMC_BulidResumeMsg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    switch(enRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_GSM;
            break;
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            pstMsg->ucResumeOrigen = MMC_RESUME_ORIGEN_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BulidResumeMsg:Unexpected Rat Type!");
            return;
    }

    pstMsg->ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    pstMsg->ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendOrigenRatType
 ��������  : ��ȡ����ǰ����������
 �������  : pstEntryMsg :״̬���������Ϣ
 �������  :
 �� �� ֵ  : ����ǰ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��03��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��6��
    ��    ��   : l00324781
    �޸�����   : Iteration 12�޸�

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendOrigenRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;
#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enRat;
    }

    /* ���ݹ���Ŀ�ķ�����ȡ����ǰ���������� */
    switch(stGuSuspendMsg.ucSuspendOrigen)
    {
        case MMC_SUSPEND_ORIGEN_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;
        case MMC_SUSPEND_ORIGEN_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_ORIGEN_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendDestinationRatType
 ��������  : ��ȡ����Ŀ�ķ�����������
 �������  : pstEntryMsg :״̬���������Ϣ
 �������  :
 �� �� ֵ  : ����Ŀ�ķ�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendDestinationRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat   = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Invalid Event Type!");
            return enRat;
    }

    /* ���ݹ���Ŀ�ķ�����ȡ����ǰ���������� */
    switch(stGuSuspendMsg.ucSuspendDestination)
    {
        case MMC_SUSPEND_DESTINATION_GSM:
            enRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case MMC_SUSPEND_DESTINATION_WCDMA:
            enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case MMC_SUSPEND_DESTINATION_LTE:
            enRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendDestinationRatType:Unexpected Rat Type!");
            return enRat;
    }

    return enRat;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendCause
 ��������  : ��ȡ��������
 �������  : pstEntryMsg :״̬���������Ϣ
 �������  :
 �� �� ֵ  : ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
MMC_SUSPEND_CAUSE_ENUM_UINT8    NAS_MMC_GetSuspendCause(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause = MMC_SUSPEND_CAUSE_BUTT;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            stGuSuspendMsg   = *(RRMM_SUSPEND_IND_ST*)(pstEntryMsg->aucEntryMsgBuffer);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            enSuspendCause   = stGuSuspendMsg.ucSuspendCause;
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return enSuspendCause;
    }

    return enSuspendCause;
}

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsInterSysReselectToHrpd
 ��������  : �ж��Ƿ���ѡ��HRPD
 �������  : pstEntryMsg :״̬���������Ϣ
 �������  :
 �� �� ֵ  : VOS_TRUE,�ǣ�VOS_FALSE������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsInterSysReselectToHrpd(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg      = VOS_NULL_PTR;
#endif
    RRMM_SUSPEND_IND_ST                 stGuSuspendMsg;

    /* ������Ϣ���ͣ�ת�������Ϣ */
    switch (pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            return VOS_FALSE;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND):
            pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

            /* ת��L�Ĺ�����ϢΪGU�� */
            NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stGuSuspendMsg);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendOrigenRatType:Invalid Event Type!");
            return VOS_FALSE;
    }

    if (MMC_SUSPEND_DESTINATION_HRPD == stGuSuspendMsg.ucSuspendDestination)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMsccInterSysCauseToMmcFormat
 ��������  : ��mscc��ʽ�Ĺ���ԭ��ֵת��Ϊmmc��ʽ�Ĺ���ԭ��ֵ
 �������  : enMsccSuspendCause:mscc��ʽ�Ĺ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32:mmc��ʽ�Ĺ���ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��27��
    ��    ��   : y00346957
    �޸�����   : �����ɺ���

*****************************************************************************/
MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32 NAS_MMC_ConvertMsccInterSysCauseToMmcFormat(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enMsccSuspendCause
)
{
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32                       enInterSysCause;

    switch (enMsccSuspendCause)
    {
        case NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT:
            enInterSysCause = MMC_LMM_SUS_TYPE_RSL;
            break;

        case NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR:
            enInterSysCause = MMC_LMM_SUS_TYPE_REDIR;
            break;

        case NAS_MSCC_PIF_INTERSYS_CAUSE_HO:
            enInterSysCause = MMC_LMM_SUS_TYPE_HO;
            break;

        default:
            enInterSysCause = MMC_LMM_SUS_TYPE_BUTT;
    }

    return enInterSysCause;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_StartResumeTimer_InterSysCellResel
 ��������  : ƴƬ��CLģʽ�£���ϵͳ�л�����LTE��ѡ���ض���HRPD�����У�MME�յ��ڲ�ģ��MM��GMM��SuspendRsp��Ϣ����
           : ���ݲ�ͬ�л����ͣ�������ͬʱ����ʱ��
 �������  : ��
 �������  :
 �� �� ֵ  : VOS_TRUE,��LTE��HRPD���л���VOS_FALSE������LTE��HRPD���л�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_StartResumeTimer_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND, TI_NAS_MMC_WAIT_CMMCA_RESUME_IND_LEN);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
        /* �ض��򣬶�ʱ��ʱ��Ϊ180s */
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN);
        }
        /* ��ѡ����ʱ��ʱ��Ϊ35s  */
        else /* (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg())) */
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF, TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN);
        }
#endif

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel
 ��������  : ƴƬ��CLģʽ�£���ϵͳ�л�����LTE��ѡ���ض���HRPD�����У�MME�յ��ڲ�ģ��MM��GMM��ResumeRsp��Ϣ����
           : ���ݲ�ͬ�л����ͣ����Ͳ�ͬ���͵Ĺ��������Ϣ
 �������  : ��
 �������  :
 �� �� ֵ  : VOS_TRUE,��LTE��HRPD���л���VOS_FALSE������LTE��HRPD���л�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel(VOS_VOID)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    if (MMC_RESUME_ORIGEN_HRPD == NAS_MMC_GetResumeOrign_InterSysCellResel())
    {
        /* ֪ͨLMM��ǰ�Ѿ��ָ� */
        NAS_MMC_SndLmmResumeNotify();

        /* ����״̬���ɹ��Ľ�� */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

        if (MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
        else /* ����ѡ�����ض��� */
        {
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_REDIRECTION, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);
        }
#endif

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
#endif
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMmcInterSysCauseToMsccFormat
 ��������  : ��MMC��ʽ�Ĺ���ԭ��ֵת��ΪMSCC��ʽ�Ĺ���ԭ��ֵ
 �������  : enMmcSuspendCause:MMC��ʽ�Ĺ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32:MSCC��ʽ�Ĺ���ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��05��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32 NAS_MMC_ConvertMmcInterSysCauseToMsccFormat(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enMmcSuspendCause
)
{
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;

    switch (enMmcSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT;
            break;

        case MMC_SUSPEND_CAUSE_REDIRECTION:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR;
            break;

        case MMC_SUSPEND_CAUSE_HANDOVER:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_HO;
            break;

        default:
            enInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT;
    }

    return enInterSysCause;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

