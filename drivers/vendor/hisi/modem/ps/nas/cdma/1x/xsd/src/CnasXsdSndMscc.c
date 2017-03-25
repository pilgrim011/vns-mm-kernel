/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSndMscc.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��7��
  ����޸�   :
  ��������   : XSD���͸�MMA����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��7��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdSndMscc.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"

#include "CnasXsdComFunc.h"
#include "CnasCcb.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_MSCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccStartCnf
 ��������  : ��MSCC���Ϳ����ظ�
 �������  : enRslt - �������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��7��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccStartCnf(
    XSD_MSCC_START_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_START_CNF_STRU            *pstStartCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstStartCnf = (XSD_MSCC_START_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_START_CNF_STRU));
    if (VOS_NULL_PTR == pstStartCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstStartCnf->stMsgHeader.ulReceiverPid  = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstStartCnf->stMsgHeader.ulMsgName      = ID_XSD_MSCC_START_CNF;
    pstStartCnf->enRslt                     = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstStartCnf);

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccPowerOffCnf
 ��������  : ��MMA���͹ػ��ظ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��7��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccPowerOffCnf(VOS_VOID)
{
    XSD_MSCC_POWER_OFF_CNF_STRU        *pstPowerOffCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPowerOffCnf = (XSD_MSCC_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_POWER_OFF_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerOffCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstPowerOffCnf->MsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerOffCnf->MsgHeader.ulMsgName           = ID_XSD_MSCC_POWER_OFF_CNF;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstPowerOffCnf);

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMmscSysAcqCnf
 ��������  : ��Mscc����ID_XSD_MMA_SYSTEM_ACQUIRE_CNF��Ϣ
 �������  : XSD_MSCC_ACQUIRED_RESULT_ENUM_UINT32 enRslt
             NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU   *pstSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��27��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

  3.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSysAcqCnf(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU    *pstSysAcqCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysAcqCnf = (XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU));
    if (VOS_NULL_PTR == pstSysAcqCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqCnf->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqCnf->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SYSTEM_ACQUIRE_CNF;
    pstSysAcqCnf->enRslt                        = enRslt;



    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqCnf);

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSysAcqInd
 ��������  : ��MSCC����ID_XSD_MSCC_SYSTEM_ACQUIRE_IND��Ϣ
 �������  : XSD_MSCC_ACQUIRED_RESULT_ENUM_UINT32 enRslt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��12��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSysAcqInd(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU    *pstSysAcqInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysAcqInd = (XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SYSTEM_ACQUIRE_IND;
    pstSysAcqInd->enRslt                        = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqInd);

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSysSrvInfoInd
 ��������  : ��MMA����ID_XSD_MMA_SYSTEM_SERVICE_INFO_IND��Ϣ
 �������  : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pstSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��19��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSysSrvInfoInd(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pstSysInfo
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU           *pstSysInfoInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysInfoInd = (XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSysInfoInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSysInfoInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysInfoInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND;

    /* ���ϵͳ��Ϣ */
    NAS_MEM_CPY_S(&(pstSysInfoInd->stSysSrvInfo), sizeof(pstSysInfoInd->stSysSrvInfo), pstSysInfo, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysInfoInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysInfoInd);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSysAcqStartInd
 ��������  : ��MSCC����ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSysAcqStartInd(VOS_VOID)
{
    XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU                     *pstSysAcqStartInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysAcqStartInd = (XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqStartInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqStartInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqStartInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqStartInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqStartInd);

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildMsccSysInfoInd
 ��������  : ����XSD��MMA��ϵͳ��Ϣ
 �������  : CAS_CNAS_1X_OHM_IND_STRU           *pstCasCnas1xOhmInd
 �������  : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstXsdMmaSysInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildMsccSysInfoInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstCasCnas1xOhmInd,
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstXsdMmaSysInfo
)
{
    pstXsdMmaSysInfo->usBandClass = pstCasCnas1xOhmInd->usBandClass;
    pstXsdMmaSysInfo->usFreq      = pstCasCnas1xOhmInd->usFreq;
    pstXsdMmaSysInfo->usSid       = pstCasCnas1xOhmInd->usSid;
    pstXsdMmaSysInfo->usNid       = pstCasCnas1xOhmInd->usNid;
    pstXsdMmaSysInfo->ucPzid      = pstCasCnas1xOhmInd->ucPacketZoneId;
    pstXsdMmaSysInfo->ucPrevInUse = pstCasCnas1xOhmInd->ucPRevInUse;


    pstXsdMmaSysInfo->enRegInfoIncl            = pstCasCnas1xOhmInd->enRegInfoIncl;
    pstXsdMmaSysInfo->enBaseStationInfoIncl    = pstCasCnas1xOhmInd->enBaseStationInfoIncl;
    pstXsdMmaSysInfo->enServiceInfoIncl        = pstCasCnas1xOhmInd->enServiceInfoIncl;
    pstXsdMmaSysInfo->stRegInfo.usRegZone      = pstCasCnas1xOhmInd->stRegInfo.usRegZone;
    pstXsdMmaSysInfo->stRegInfo.ucRegZoneNum   = pstCasCnas1xOhmInd->stRegInfo.ucRegZoneNum;
    pstXsdMmaSysInfo->stRegInfo.ucZoneTimer    = pstCasCnas1xOhmInd->stRegInfo.ucZoneTimer;
    pstXsdMmaSysInfo->stRegInfo.ucMultiSidFlg  = pstCasCnas1xOhmInd->stRegInfo.ucMultiSidFlg;
    pstXsdMmaSysInfo->stRegInfo.ucMultiNidFlg  = pstCasCnas1xOhmInd->stRegInfo.ucMultiNidFlg;
    pstXsdMmaSysInfo->stRegInfo.usRegDistance  = pstCasCnas1xOhmInd->stRegInfo.usRegDistance;
    pstXsdMmaSysInfo->stRegInfo.ucRegPeriod    = pstCasCnas1xOhmInd->stRegInfo.ucRegPeriod;
    pstXsdMmaSysInfo->stRegInfo.ucHomeReg      = pstCasCnas1xOhmInd->stRegInfo.ucHomeReg;
    pstXsdMmaSysInfo->stRegInfo.ucSidRoamReg   = pstCasCnas1xOhmInd->stRegInfo.ucSidRoamReg;
    pstXsdMmaSysInfo->stRegInfo.ucNidRoamReg   = pstCasCnas1xOhmInd->stRegInfo.ucNidRoamReg;
    pstXsdMmaSysInfo->stRegInfo.ucPowerUpReg   = pstCasCnas1xOhmInd->stRegInfo.ucPowerUpReg;
    pstXsdMmaSysInfo->stRegInfo.ucPowerDownReg = pstCasCnas1xOhmInd->stRegInfo.ucPowerDownReg;
    pstXsdMmaSysInfo->stRegInfo.ucParameterReg = pstCasCnas1xOhmInd->stRegInfo.ucParameterReg;


    pstXsdMmaSysInfo->stBaseStationInfo.usBaseId        = pstCasCnas1xOhmInd->stBaseStationInfo.usBaseId;
    pstXsdMmaSysInfo->stBaseStationInfo.ucBaseClass     = pstCasCnas1xOhmInd->stBaseStationInfo.ucBaseClass;
    pstXsdMmaSysInfo->stBaseStationInfo.lBaseLatitude   = pstCasCnas1xOhmInd->stBaseStationInfo.lBaseLatitude;
    pstXsdMmaSysInfo->stBaseStationInfo.lBaseLongitude  = pstCasCnas1xOhmInd->stBaseStationInfo.lBaseLongitude;

    pstXsdMmaSysInfo->stServiceInfo.ucMaxAltSo            = pstCasCnas1xOhmInd->stServiceInfo.ucMaxAltSo;
    pstXsdMmaSysInfo->stServiceInfo.ucSDBSupported        = pstCasCnas1xOhmInd->stServiceInfo.ucSDBSupported;
    pstXsdMmaSysInfo->stServiceInfo.ucMoQos               = pstCasCnas1xOhmInd->stServiceInfo.ucMoQos;
    pstXsdMmaSysInfo->stServiceInfo.ucConcurrentSupported = pstCasCnas1xOhmInd->stServiceInfo.ucConcurrentSupported;
    pstXsdMmaSysInfo->stServiceInfo.ucMoPosSupported      = pstCasCnas1xOhmInd->stServiceInfo.ucMoPosSupported;


    pstXsdMmaSysInfo->stServiceInfo.ulMcc        = CNAS_XSD_TransformMccToBcd(pstCasCnas1xOhmInd->stServiceInfo.usMcc);
    pstXsdMmaSysInfo->stServiceInfo.usImsi11_12  = CNAS_XSD_TransformImsiToBcd(pstCasCnas1xOhmInd->stServiceInfo.ucImsi11_12);

    /* Ŀǰ������޷��ϱ�MNC���������Ĭ�Ͻ�MNC��ֵ����Ϊ��Чֵ */
    pstXsdMmaSysInfo->stServiceInfo.usMnc        = pstXsdMmaSysInfo->stServiceInfo.usImsi11_12;


    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMscc1xSysTimeInd
 ��������  : ��MMA����ID_XSD_MSCC_1X_SYSTEM_TIME_IND��Ϣ
 �������  : NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pst1xSysTimeInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��4��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMscc1xSysTimeInd(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pst1xSysTimeInfo
)
{
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU   *pst1xSysTimeInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pst1xSysTimeInd = (XSD_MSCC_1X_SYSTEM_TIME_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_1X_SYSTEM_TIME_IND_STRU));
    if (VOS_NULL_PTR == pst1xSysTimeInd)
    {
        return;
    }

    /* �����Ϣ */
    pst1xSysTimeInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pst1xSysTimeInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_1X_SYSTEM_TIME_IND;

    /* ���ϵͳ��Ϣ */
    NAS_MEM_CPY_S(&(pst1xSysTimeInd->stSysTime), sizeof(pst1xSysTimeInd->stSysTime), pst1xSysTimeInfo, sizeof(NAS_MSCC_PIF_1X_SYS_TIME_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pst1xSysTimeInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pst1xSysTimeInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndCdmaCsqSetCnf
 ��������  : ��MMA����CDMACSQ���ý��
 �������  : enRslt - ���ý��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCdmaCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
)
{
    XSD_MSCC_CDMACSQ_SET_CNF_STRU    *pstCdmaCsqCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstCdmaCsqCnf = (XSD_MSCC_CDMACSQ_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_CDMACSQ_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCdmaCsqCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstCdmaCsqCnf->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCdmaCsqCnf->stMsgHeader.ulMsgName        = ID_XSD_MSCC_CDMACSQ_SET_CNF;
    pstCdmaCsqCnf->enRslt                       = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCdmaCsqCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCdmaCsqCnf);

    return;
}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndCdmaCsqInd
 ��������  : �����ϱ�CdmaCsq
 �������  : enRslt - ���ý��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

  3.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCdmaCsqInd(
    VOS_INT16                           sCdmaRssi,
    VOS_INT16                           sCdmaEcIo
)
{
    XSD_MSCC_CDMACSQ_IND_STRU    *pstCdmaCsqInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstCdmaCsqInd = (XSD_MSCC_CDMACSQ_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_CDMACSQ_IND_STRU));
    if (VOS_NULL_PTR == pstCdmaCsqInd)
    {
        return;
    }

    /* �����Ϣ */
    pstCdmaCsqInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCdmaCsqInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND;
    pstCdmaCsqInd->sCdmaRssi                    = sCdmaRssi;
    pstCdmaCsqInd->sCdmaEcIo                    = sCdmaEcIo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCdmaCsqInd);


    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCdmaCsqInd);

    return;

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSysCfgCnf
 ��������  : ��Mscc͸��SysCnf��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSysCfgCnf(
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstRcvMsg
)
{
    XSD_MSCC_SYS_CFG_CNF_STRU          *pstSysCfgCnfMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysCfgCnfMsg = (XSD_MSCC_SYS_CFG_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYS_CFG_CNF_STRU));
    if (VOS_NULL_PTR == pstSysCfgCnfMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstSysCfgCnfMsg->MsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysCfgCnfMsg->MsgHeader.ulMsgName        = ID_XSD_MSCC_SYS_CFG_CNF;
    pstSysCfgCnfMsg->enRst                      = NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS;
    pstSysCfgCnfMsg->usOpId                     = pstRcvMsg->usOpId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgCnfMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysCfgCnfMsg);

    return;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_SndMsccPowerSaveCnf
Description     :   The function is used to send the Power save Cnf to MSCC
Input parameters:   None
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create

    2)��    ��  : 2015��08��20��
      ��    ��  : t00323010
      �޸�����  : DTS2015081904804 clear coverity

*****************************************************************************/

VOS_VOID CNAS_XSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult
)
{
    XSD_MSCC_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf  = VOS_NULL_PTR;

    pstPowerSaveCnf = (XSD_MSCC_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_POWER_SAVE_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerSaveCnf)
    {
        return;
    }

    /* Constructing the Power Save Cnf message */
    pstPowerSaveCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstPowerSaveCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerSaveCnf->stMsgHeader.ulLength            = sizeof(XSD_MSCC_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPowerSaveCnf->stMsgHeader.ulMsgName           = ID_XSD_MSCC_POWER_SAVE_CNF;
    pstPowerSaveCnf->enResult                        = enResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerSaveCnf);

    /* Send the message */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstPowerSaveCnf);

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccHandSetInfoCnf
 ��������  : ��MSCC�����ֻ���Ϣ�ظ�
 �������  : pstHandSetInfo - �ֻ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccHandSetInfoCnf(
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstHandSetInfo
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstInfoCnf  = VOS_NULL_PTR;

    pstInfoCnf = (XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                        sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstInfoCnf)
    {
        return;
    }

    /* Constructing the Power Save Cnf message */
    pstInfoCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstInfoCnf->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstInfoCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstInfoCnf->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstInfoCnf->stMsgHeader.ulLength            = sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInfoCnf->stMsgHeader.ulMsgName           = ID_XSD_MSCC_HANDSET_INFO_QRY_CNF;

    pstInfoCnf->ulInfoType                      = pstHandSetInfo->ulInfoType;
    pstInfoCnf->ucCasState                      = pstHandSetInfo->ucCasState;
    pstInfoCnf->ucCasSubSta                     = pstHandSetInfo->ucCasSubSta;
    pstInfoCnf->ucHighVer                       = pstHandSetInfo->ucHighVer;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInfoCnf);

    /* Send the message */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstInfoCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccRfAvailInd
 ��������  : ��MSCC����RF��Դ�Ƿ����ָʾ
 �������  : VOS_UINT8 : ucRfAvail - RF�Ƿ����
             VOS_TRUE  : ��Ƶ����
             VOS_FALSE : ��Ƶ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��20��
   ��    ��   : h00313353
   �޸�����   : �½�

 2.��    ��   : 2015��08��20��
   ��    ��   : t00323010
   �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *pstRfAvailInd = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength     = sizeof(NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRfAvailInd   = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstRfAvailInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstRfAvailInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstRfAvailInd->stMsgHeader.ulMsgName           = ID_XSD_MSCC_RF_AVAILABLE_IND;
    pstRfAvailInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstRfAvailInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstRfAvailInd->stMsgHeader.ulLength            = ulMsgLength;
    pstRfAvailInd->ucRfAvailFlg                    = ucRfAvail;
    pstRfAvailInd->enRatType                       = NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstRfAvailInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstRfAvailInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSrvAcqCnf
 ��������  : ��MSCC�ظ�ҵ�񴥷������Ľ��
 �������  : enResult : ҵ�񴥷������Ľ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��21��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8                  enResult
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU                              *pstSrvAcqCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength     = sizeof(XSD_MSCC_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSrvAcqCnf    = (XSD_MSCC_SRV_ACQ_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSrvAcqCnf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstSrvAcqCnf) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstSrvAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pstSrvAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSrvAcqCnf->stMsgHeader.ulLength          = ulMsgLength;
    pstSrvAcqCnf->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SRV_ACQ_CNF;

    pstSrvAcqCnf->enResult                      = enResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSrvAcqCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSrvAcqCnf);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSidNidInd
 ��������  : ��MSCC����SID��Ϣָʾ
 �������  : usSid -- ��ǰϵͳSID
             usNid -- ��ǰϵͳNID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

  3.��    ��   : 2015��12��15��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE �޸ģ�SID_IND�޸�ΪSID_NID_IND
*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSidNidInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid
)
{
    MSCC_XSD_SID_NID_IND_STRU              *pstSidNidInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSidNidInd = (MSCC_XSD_SID_NID_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD, sizeof(MSCC_XSD_SID_NID_IND_STRU));

    if (VOS_NULL_PTR == pstSidNidInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstSidNidInd, sizeof(MSCC_XSD_SID_NID_IND_STRU), 0, sizeof(MSCC_XSD_SID_NID_IND_STRU));

    /* �����Ϣ */
    pstSidNidInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSidNidInd->stMsgHeader.ulSenderPid     = UEPS_PID_XSD;
    pstSidNidInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSidNidInd->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSidNidInd->stMsgHeader.ulLength        = sizeof(MSCC_XSD_SID_NID_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSidNidInd->stMsgHeader.ulMsgName       = ID_XSD_MSCC_SID_NID_IND;

    pstSidNidInd->usSid                       = usSid;
    pstSidNidInd->usNid                       = usNid;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSidNidInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSidNidInd);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccEmcCallBackNtf
 ��������  : ��MSCC�ϱ�������CallBackģʽ״̬
 �������  : ulIsInCallBack : ��ǰ�Ƿ���CallBackģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��08��20��
   ��    ��   : t00323010
   �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccEmcCallBackInd(
    MSCC_XSD_EMC_CALLBACK_MODE_ENUM_UINT32                  enCallBackState
)
{
    XSD_MSCC_EMC_CALLBACK_IND_STRU                         *pstCallBackInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength     = sizeof(XSD_MSCC_EMC_CALLBACK_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCallBackInd    = (XSD_MSCC_EMC_CALLBACK_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstCallBackInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstCallBackInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstCallBackInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCallBackInd->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pstCallBackInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCallBackInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCallBackInd->stMsgHeader.ulLength          = ulMsgLength;
    pstCallBackInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_EMC_CALLBACK_IND;

    pstCallBackInd->enCallBackState               = enCallBackState;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCallBackInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCallBackInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccSetCSidListCnf
 ��������  : ��MSCC�ϱ��˳�������CallBack���
 �������  : ulResult : �˳�CallBackģʽ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��08��20��
   ��    ��   : t00323010
   �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSetCSidListCnf(
    VOS_UINT32                                              ulResult
)
{
    XSD_MSCC_SET_CSIDLIST_CNF_STRU                         *pstCSidListCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                         = sizeof(XSD_MSCC_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCSidListCnf                      = (XSD_MSCC_SET_CSIDLIST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstCSidListCnf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstCSidListCnf) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstCSidListCnf->stMsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstCSidListCnf->stMsgHeader.ulSenderPid                 = UEPS_PID_XSD;
    pstCSidListCnf->stMsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstCSidListCnf->stMsgHeader.ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCSidListCnf->stMsgHeader.ulLength                    = ulMsgLength;
    pstCSidListCnf->stMsgHeader.ulMsgName                   = ID_XSD_MSCC_SET_CSIDLIST_CNF;

    pstCSidListCnf->ulRslt                                  = ulResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCSidListCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCSidListCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccServiceAvailableInd
 ��������  : ��MSCC���ͷ������ָʾ
 �������  : ulResult : �˳�CallBackģʽ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��25��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��08��20��
   ��    ��   : t00323010
   �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccSyncServiceAvailableInd(
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvAvailInd
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvAvailableInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength        = sizeof(XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSrvAvailableInd = (XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSrvAvailableInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstSrvAvailableInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstSrvAvailableInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSrvAvailableInd->stMsgHeader.ulSenderPid     = UEPS_PID_XSD;
    pstSrvAvailableInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSrvAvailableInd->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSrvAvailableInd->stMsgHeader.ulLength        = ulMsgLength;
    pstSrvAvailableInd->stMsgHeader.ulMsgName       = ID_XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND;

    pstSrvAvailableInd->usFreq                      = pstSrvAvailInd->usFreq;
    pstSrvAvailableInd->usBandClass                 = pstSrvAvailInd->usBandClass;
    pstSrvAvailableInd->usSid                       = pstSrvAvailInd->usSid;
    pstSrvAvailableInd->usNid                       = pstSrvAvailInd->usNid;
    pstSrvAvailableInd->enServiceStatus             = pstSrvAvailInd->enServiceStatus;
    pstSrvAvailableInd->ucRoamingInd                = pstSrvAvailInd->ucRoamingInd;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSrvAvailableInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSrvAvailableInd);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMsccUeStatusInd
 ��������  : ����MSCC UE STATUS IND
 �������  : enCasState     ��״̬
             enCasSubState  ��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_SndMsccUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
)
{
    XSD_MSCC_UE_STATE_IND_STRU         *pstUeStatus  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstUeStatus = (XSD_MSCC_UE_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                    sizeof(XSD_MSCC_UE_STATE_IND_STRU));
    if (VOS_NULL_PTR == pstUeStatus)
    {
        return;
    }

    /* �����Ϣ */
    pstUeStatus->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstUeStatus->ulSenderPid        = UEPS_PID_XSD;
    pstUeStatus->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstUeStatus->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstUeStatus->ulLength           = sizeof(XSD_MSCC_UE_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstUeStatus->enMsgId            = ID_XSD_MSCC_CDMA_UE_STATUS_IND;
    pstUeStatus->ucUeMainState      = ucUeMainState;
    pstUeStatus->ucUeSubState       = ucUeSubState;

    pstUeStatus->aucReserve[0]      = 0;
    pstUeStatus->aucReserve[1]      = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstUeStatus);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstUeStatus);

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndMscc1xNoSrvInd
 ��������  : ��MSCC֪ͨXSD�޷�����ã�MSCC�յ�����Ϣ��MMA֪ͨ1X�޷���MMA�����޷�����ʱ�ϱ���ʱ��
             ���ó���:IDLE̬���յ�CAS_CNAS_1X_SYSTEM_DETERMIN_IND��Ϣ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��08��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_SndMscc1xNoSrvInd(VOS_VOID)
{
    XSD_MSCC_1X_NO_SERVICE_IND_STRU    *pst1xNoSrvInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pst1xNoSrvInd = (XSD_MSCC_1X_NO_SERVICE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                    sizeof(XSD_MSCC_1X_NO_SERVICE_IND_STRU));
    if (VOS_NULL_PTR == pst1xNoSrvInd)
    {
        return;
    }

    /* �����Ϣ */
    pst1xNoSrvInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pst1xNoSrvInd->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pst1xNoSrvInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pst1xNoSrvInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pst1xNoSrvInd->stMsgHeader.ulLength          = sizeof(XSD_MSCC_1X_NO_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;;
    pst1xNoSrvInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_1X_NO_SERVICE_IND;

    NAS_MEM_SET_S(pst1xNoSrvInd->aucReserve, sizeof(pst1xNoSrvInd->aucReserve), 0, sizeof(pst1xNoSrvInd->aucReserve));


    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pst1xNoSrvInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pst1xNoSrvInd);

    return;

}

#endif





/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

