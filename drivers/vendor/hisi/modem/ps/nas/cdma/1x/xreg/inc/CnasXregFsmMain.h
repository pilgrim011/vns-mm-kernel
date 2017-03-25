/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregFsmMain.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��7��8��
  ����޸�   :
  ��������   : CnasXregFsmMain.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��8��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XREG_FSM_MAIN_H__
#define __CNAS_XREG_FSM_MAIN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


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

extern VOS_UINT32 CNAS_XREG_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvSwitchOnRslt_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvStartReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_XREG_RcvPowerOffReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvAccessInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegedDataInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_RcvRegCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_SIDNIDRegTimeout_Reged(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XREG_ZoneRegTimeout_Reged(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_XREG_WriteNvimInfo_PowerOff(VOS_VOID);

extern VOS_VOID CNAS_XREG_ProcPowerOffReq(VOS_VOID);

extern VOS_UINT32 CNAS_XREG_RcvPwrOffTimeOut_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

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

#endif /* end of CnasXregFsmMain.h */
