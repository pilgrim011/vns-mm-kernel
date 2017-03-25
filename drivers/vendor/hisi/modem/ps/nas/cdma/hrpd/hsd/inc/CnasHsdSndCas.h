/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndCas.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��10��
  ����޸�   :
  ��������   : CnasHsdSndCas.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

******************************************************************************/

#ifndef __CNAS_HSD_SND_CAS_H__
#define __CNAS_HSD_SND_CAS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdCtx.h"
#include  "hsd_mscc_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_CAS_HRPD_MAX_SUBNET_NUM                          (16)


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

extern VOS_VOID CNAS_HSD_SndCasStartReq(MSCC_HSD_START_REQ_STRU *pstMsg);

extern VOS_VOID CNAS_HSD_SndCasPowerOffReq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
);

extern VOS_VOID CNAS_HSD_SndCasStopSysSyncReq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasOocNtf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasPilotSearchSuccNtf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasPilotSearchFailNtf(VOS_VOID);


extern VOS_VOID CNAS_HSD_SndCasSysCfgReq(
    MSCC_HSD_SYS_CFG_REQ_STRU          *pstSysCfg
);


extern VOS_VOID CNAS_HSD_SndCasSuspendReq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasDisableLteNtf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasBsrLteReq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasStopBsrLteReq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasFreqListCnf(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
);

extern VOS_VOID CNAS_HSD_SndCasSubnetIdChkCnf(
    PS_BOOL_ENUM_UINT8                  enIsValidFlag
);

extern VOS_VOID CNAS_HSD_SndCasSuspendRsp(
    CAS_CNAS_HRPD_RSLT_ENUM_UINT16      enRslt
);

extern VOS_VOID CNAS_HSD_SndCasResumeRsp(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_SndCasCFreqLockNtf(MSCC_HSD_CFREQ_LOCK_NTF_STRU   *pstCFreqLockNtf);

extern VOS_VOID CNAS_HSD_SndCasBeginSessionNotify(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndCasEndSessionNotify(VOS_VOID);
VOS_UINT32 CNAS_HSD_SndCasHdrCsqSetReq(
    MSCC_HSD_HDR_CSQ_SET_REQ_STRU      *psrHdrSetReq
);

VOS_UINT32 CNAS_HSD_SndCasSuspendRelReq(VOS_VOID);

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

#endif /* end of CnasHsdSndCas.h */
