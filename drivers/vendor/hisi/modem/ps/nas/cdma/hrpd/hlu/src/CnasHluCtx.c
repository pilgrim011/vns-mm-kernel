/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHluCtx.c
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��12��16��
  ����޸�   :
  ��������   : context of HLU process
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��16��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasHluCtx.h"
#include "CnasHluComm.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Global Variable declaration
*****************************************************************************/
/* Global Ctxt to store current AT Location details. */
CNAS_HLU_CTX_STRU                       g_stCnasHluLocCtxt;


/* Moved RANHAndoff value to global context */



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/


CNAS_HLU_CTX_STRU *CNAS_HLU_GetLocCtxAddr(VOS_VOID)
{
    return (&g_stCnasHluLocCtxt);
}



VOS_UINT16 CNAS_HLU_GetCurrSid(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stLocCtx.stLocVal.usSID);
}



VOS_UINT16 CNAS_HLU_GetCurrNid(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stLocCtx.stLocVal.usNID);
}



VOS_UINT8 CNAS_HLU_GetCurrPcktZoneId(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stLocCtx.stLocVal.ucPacketZoneID);
}



VOS_UINT8 CNAS_HLU_GetLocMsgTransId(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stLocCtx.ucTransID);
}



VOS_UINT8 CNAS_HLU_GetBLobTransId
(
    VOS_VOID
)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stBLOBCtx.ucTransID);
}



VOS_VOID CNAS_HLU_GetCurrLocValHToN(
    VOS_UINT8                          *pucLocValue,
    VOS_BOOL                            bIsHandOff,
    const CNAS_HLU_LOC_VALUE_STRU      *pstHandOffLocVal
)
{
    CNAS_HLU_LOC_VALUE_STRU             stCurrLocVal;
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;

    /* Reserve bit in SID is already reset before stroring locationValue,
       while AT received last LocationAssignment. */

    NAS_MEM_SET_S(&stCurrLocVal, sizeof(stCurrLocVal), 0x0, sizeof(CNAS_HLU_LOC_VALUE_STRU));

    if (CNAS_HLU_IS_EQUAL(VOS_TRUE, bIsHandOff)
     && CNAS_HLU_IS_VALID_PTR(pstHandOffLocVal))
    {
        usSID = pstHandOffLocVal->usSID;
        usNID = pstHandOffLocVal->usNID;

        stCurrLocVal.ucPacketZoneID = pstHandOffLocVal->ucPacketZoneID;

        /* Reset the reserve bit in SID, As HLU received this value from AT. */
        CNAS_HLU_ClearBitInDByte(&usSID, 16);
    }
    else
    {
        usSID = CNAS_HLU_GetCurrSid();
        usNID = CNAS_HLU_GetCurrNid();

        stCurrLocVal.ucPacketZoneID = CNAS_HLU_GetCurrPcktZoneId();
    }

    stCurrLocVal.usSID = CNAS_HLU_HTONS(usSID);
    stCurrLocVal.usNID = CNAS_HLU_HTONS(usNID);

    NAS_MEM_CPY_S(pucLocValue, CNAS_HLU_CDMA2000_HRPD_LOC_LEN, (VOS_UINT8 *)&stCurrLocVal, CNAS_HLU_CDMA2000_HRPD_LOC_LEN);
}



VOS_VOID CNAS_HLU_GetCurrStrgBlobHToN(
    VOS_UINT8                          *pucstrgBlob
)
{
    CNAS_HLU_STRG_BLOB_STRU             stCurrStrgBlob;
    VOS_UINT16                          usBLOBtype;
    VOS_UINT8                           ucBLOBLen;
    VOS_UINT8                          *pucStrgBLOB;

    NAS_MEM_SET_S(&stCurrStrgBlob, sizeof(stCurrStrgBlob), 0x0, sizeof(CNAS_HLU_STRG_BLOB_STRU));

    usBLOBtype  = CNAS_HLU_GetCurrBlobType();
    ucBLOBLen   = CNAS_HLU_GetCurrBlobLen();
    pucStrgBLOB = CNAS_HLU_GetLocCtxAddr()->stBLOBCtx.aucStorageBLOB;

    stCurrStrgBlob.usStrgBLOBtype  = CNAS_HLU_HTONS(usBLOBtype);
    stCurrStrgBlob.ucStrgBLOBLen   = ucBLOBLen;

    NAS_MEM_CPY_S(stCurrStrgBlob.aucStorageBLOB, sizeof(stCurrStrgBlob.aucStorageBLOB), pucStrgBLOB, ucBLOBLen);

    NAS_MEM_CPY_S(pucstrgBlob, (ucBLOBLen + 3), (VOS_UINT8 *)&stCurrStrgBlob, ucBLOBLen + 3);
}

VOS_BOOL CNAS_HLU_IsCurrLocTypeValid(VOS_VOID)
{
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;

    ucLocType = CNAS_HLU_GetLocCtxAddr()->stLocCtx.ucLocType;
    ucLocLen  = CNAS_HLU_GetLocCtxAddr()->stLocCtx.ucLocLen;

    if ((CNAS_HLU_CDMA2000_HRPD_LOC_TYPE == ucLocType)
        && (CNAS_HLU_CDMA2000_HRPD_LOC_LEN == ucLocLen))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}




VOS_BOOL CNAS_HLU_IsCurrBlobTypeValid(VOS_VOID)
{
    VOS_UINT16                          usStrgBLOBtype;
    VOS_UINT8                           ucStrgBLOBLen;

    usStrgBLOBtype = CNAS_HLU_GetCurrBlobType();
    ucStrgBLOBLen  = CNAS_HLU_GetCurrBlobLen();

    if ((0x0000 != usStrgBLOBtype)&& (0x00 != ucStrgBLOBLen))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_UINT8 CNAS_HLU_GetCurrBlobLen
(
    VOS_VOID
)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stBLOBCtx.ucStrgBLOBLen);
}



VOS_UINT16 CNAS_HLU_GetCurrBlobType(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->stBLOBCtx.usStrgBLOBtype);
}


VOS_UINT8 CNAS_HLU_GetRANHandoff(VOS_VOID)
{
    return ((CNAS_HLU_GetLocCtxAddr())->ucRANHandoff);
}



VOS_VOID CNAS_HLU_SetRANHandoff(
    VOS_UINT8                           ucRANHandOff
)
{
   ((CNAS_HLU_GetLocCtxAddr())->ucRANHandoff) = ucRANHandOff;

    return;
}



VOS_VOID CNAS_HLU_SetHandOffOpId(VOS_VOID)
{
    VOS_UINT8                           ucMsgId;
    VOS_UINT8                          *pucHandOffMsgId;

    pucHandOffMsgId = &(CNAS_HLU_GetLocCtxAddr()->ucOpId);

    /* For the first time, ucMsgId will be 0.
       ucOpId is set to 0 in CNAS_HLU_InitPid. */
    ucMsgId = *pucHandOffMsgId;
    ucMsgId = (ucMsgId + 1) % 256;

    /* for the case when:
       Before entering this function ucMsgId is 255,
       (255 + 1) % 256 = 0, but we have to start from 1. */
    if (0 == ucMsgId)
    {
        ucMsgId = 1;
    }

    *pucHandOffMsgId = ucMsgId;

    return;
}



VOS_UINT8 CNAS_HLU_GetHandOffOpId(VOS_VOID)
{
    return (CNAS_HLU_GetLocCtxAddr()->ucOpId);
}


CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16 CNAS_HLU_GetProtocolType(VOS_VOID)
{
    return (CNAS_HLU_GetLocCtxAddr()->enProtocolType);
}


VOS_VOID CNAS_HLU_SetProtocolType(CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16 enProtocolType)
{
    (CNAS_HLU_GetLocCtxAddr()->enProtocolType) = enProtocolType;
}

/*****************************************************************************
 �� �� ��  : CNAS_HLU_GetHandOffFlg
 ��������  : ��ȡ��ǰ�Ƿ���HandOff���̵ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE  : ����HandOff����
             VOS_FALSE : ������HandOff����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��21��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HLU_GetHandOffFlg( VOS_VOID )
{
    return CNAS_HLU_GetLocCtxAddr()->ucHandOffFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HLU_SetHandOffFlg
 ��������  : ���õ�ǰ�Ƿ���HandOff���̵ı�־
 �������  : VOS_UINT8
             VOS_TRUE  : ����HandOff����
             VOS_FALSE : ������HandOff����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��21��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HLU_SetHandOffFlg(
    VOS_UINT8                           ucHandOffFlg
)
{
    CNAS_HLU_GetLocCtxAddr()->ucHandOffFlg  = ucHandOffFlg;

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif






