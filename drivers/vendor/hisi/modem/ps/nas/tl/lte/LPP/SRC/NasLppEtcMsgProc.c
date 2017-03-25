/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasLppEtcMsgProc.c
  �� �� ��   : ����
  ��    ��   : LIFUXIN
  ��������   : 2015��7��30��
  ����޸�   :
  ��������   : LPP ģ����ڲ���Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��1��
    ��    ��   : LIFUXIN
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
//#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "EtcLppInterface.h"
#include  "NasLppSendMsg.h"
#include  "NasLppEtcMsgProc.h"

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPETCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPETCMSGPROC_C


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LPP_SndMtaResetGnssPositionInfo
 Description     : reset GNSS�ĸ�������
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_SndMtaResetGnssPositionInfo(VOS_VOID)
{
    LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU    *pstResetGnssAssistData  = NAS_LPP_NULL_PTR;
    NAS_LPP_NORM_LOG("NAS_LPP_SndMtaResetGnssPositionInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndMtaResetGnssPositionInfo_ENUM, LNAS_LPP_Func_Enter);

    pstResetGnssAssistData = (LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU));
    if (NAS_LPP_NULL_PTR == pstResetGnssAssistData)
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstResetGnssAssistData, sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU), 0, sizeof(LPP_MTA_RESET_GNSS_ASSIST_DATA_STRU));

    /*��Ϣͷ*/
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstResetGnssAssistData, ID_LPP_MTA_GNSS_RESET_ASSIST_DATA);

    NAS_LPP_SND_MSG(pstResetGnssAssistData);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvLppEtcResetPostitionInfoInd
 Description     : ETCģ���LPP���͵�reset positioning info�Ĵ���
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-9-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RcvLppEtcResetPostitionInfoInd( ETC_LPP_RESET_POSTION_INFO_STRU *pRcvMsg )
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_Func_Enter);

    switch(pRcvMsg->enRestType)
    {
        case ETC_LPP_RESET_TYPE_GNSS:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset GNSS Information!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_ResetGnssInfo);
            NAS_LPP_SndMtaResetGnssPositionInfo();
            break;

        case ETC_LPP_RESET_TYPE_OTDOA:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset OTDOA Information!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEtcResetPostitionInfoInd_ENUM, LNAS_LPP_ResetOtdoaInfo);

            /*��λOTDOA�ĸ�����Ϣ*/
            /*��ձ��ش����ĸ�����Ϣ*/
            NAS_LPP_MEM_SET_S(&(NAS_LPP_GetLppEntityCtx()->stMeasResult.stOtdoaMeasRslt),
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU),
                            0,
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));

            NAS_LPP_MEM_SET_S(&(NAS_LPP_GetLppEntityCtx()->stLppConfig.stOtdoaAssisCfg),
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU),
                            0,
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));

            /*����running���õ�transactionIndex��sessionTransactionIndx*/
            pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstLocTechmap)
            {
                /*��LRRC���Ͳ���ֹͣ*/
                NAS_LPP_SndOtdoaMeasReq(pstLocTechmap->ucSessionIndx,
                                              pstLocTechmap->ucSessionTranIndx,
                                              LPP_LRRC_LCS_MEAS_CMD_REL);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EtcMsgDistr
 Description     : ETCģ���LPPģ���Լ�������Ϣ�Ĵ�����ں���
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-9-1  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EtcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_EtcMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EtcMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        /*�յ�����ID_ETC_LPP_RESET_POSTION_INFO_IND��Ϣ*/
        case ID_ETC_LPP_RESET_POSTION_INFO_IND:
            NAS_LPP_RcvLppEtcResetPostitionInfoInd((ETC_LPP_RESET_POSTION_INFO_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EtcMsgDistr:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_EtcMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
            break;
    }

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

