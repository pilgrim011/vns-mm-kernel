/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSndMscc.h
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��7��
  ����޸�   :
  ��������   : CnasXsdSndMma.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��7��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XSD_SND_MSCC_H__
#define __CNAS_XSD_SND_MSCC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "xsd_mscc_pif.h"
#include  "cas_1x_idlectrl_proc_nas_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XSD_SndMsccPowerOffCnf(VOS_VOID);
VOS_VOID CNAS_XSD_SndMsccStartCnf(
    XSD_MSCC_START_RESULT_ENUM_UINT32    enRslt
);


VOS_VOID CNAS_XSD_SndMsccSysAcqCnf(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
);

VOS_VOID CNAS_XSD_SndMsccSysAcqInd(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
);

VOS_VOID CNAS_XSD_SndMsccSysSrvInfoInd(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstSysInfo
);

VOS_VOID CNAS_XSD_SndMsccSysAcqStartInd(VOS_VOID);

VOS_VOID CNAS_XSD_BuildMsccSysInfoInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstCasCnas1xOhmInd,
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstXsdMmaSysInfo
);

VOS_VOID CNAS_XSD_SndMscc1xSysTimeInd(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pst1xSysTimeInfo
);
VOS_VOID CNAS_XSD_SndCdmaCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8    enRslt
);

VOS_VOID CNAS_XSD_SndCdmaCsqInd(
    VOS_INT16                           sCdmaRssi,
    VOS_INT16                           sCdmaEcIo
);
VOS_VOID CNAS_XSD_SndMsccSysCfgCnf(
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstRcvMsg
);


VOS_VOID CNAS_XSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult
);

extern VOS_VOID CNAS_XSD_SndMsccHandSetInfoCnf(
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstHandSetInfo
);

VOS_VOID CNAS_XSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
);

VOS_VOID CNAS_XSD_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8                  enResult
);

VOS_VOID CNAS_XSD_SndMsccEmcCallBackInd(
    MSCC_XSD_EMC_CALLBACK_MODE_ENUM_UINT32                  enCallBackState
);

VOS_VOID CNAS_XSD_SndMsccSetCSidListCnf(
    VOS_UINT32                                              ulResult
);

VOS_VOID CNAS_XSD_SndMsccSidNidInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid
);

VOS_VOID CNAS_XSD_SndMsccSyncServiceAvailableInd(
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvInfo
);

VOS_VOID CNAS_XSD_SndMsccUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
);


VOS_VOID CNAS_XSD_SndMscc1xNoSrvInd(VOS_VOID);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasXsdSndMscc.h */
