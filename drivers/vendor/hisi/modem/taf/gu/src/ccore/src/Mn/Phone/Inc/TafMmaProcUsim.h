/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaProcUsim.h
  �� �� ��   : ����
  ��    ��   : s00261364
  ��������   : 2014��4��17��
  ����޸�   :
  ��������   : TafMmaProcUsim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��17��
    ��    ��   : s00261364
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _TAF_MMA_PROC_USIM_H
#define _TAF_MMA_PROC_USIM_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"

#include "TafMmaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_MMA_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define TAF_MMA_EFRUIMID_OCTET_LEN_FIVE                    (5)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* �Ƶ�TafMmaCtx.h�� */

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
#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_MMA_UpdateCallMode( VOS_VOID );

#endif

VOS_VOID    TAF_MMA_SetWaitSimFilesCnfFlg(
    TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
);

TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_MMA_GetWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ClearAllWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ReadSimCphsOperNameFile(VOS_VOID);

VOS_VOID TAF_MMA_ReadSpnFile(VOS_VOID);

VOS_UINT32 TAF_MMA_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ReadOplFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadPnnFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFile(VOS_VOID);
VOS_UINT32 TAF_MMA_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
);
VOS_VOID  TAF_MMA_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
);
VOS_VOID TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn(VOS_VOID);

VOS_VOID   TAF_MMA_ReadCphsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_MMA_UsimRefreshIndFileListChangedMsgProc(USIMM_STKREFRESH_IND_STRU *pUsimTafMsg);
VOS_VOID TAF_MMA_ReadIccIdFileCnf(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadPnnFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadOplFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID MMA_ReadSpnFileCnf(
    TAF_PH_USIM_SPN_CNF_STRU           *pMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID TAF_MMA_RcvCustomerServiceProfileFile(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);

VOS_VOID TAF_MMA_USIMRefreshFileProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReadImsimFile( VOS_VOID );

VOS_VOID TAF_MMA_ReadRuimidFile( VOS_VOID );
VOS_VOID TAF_MMA_RcvUsimmReadRuimidFile(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg
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

#endif


