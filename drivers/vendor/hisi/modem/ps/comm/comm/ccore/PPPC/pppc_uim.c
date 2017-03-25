/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_uim.c
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��08��08��
  ����޸�   :
  ��������   : ��ȡ�͸���UIM����Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pppc_uim.h"
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "pppc_sha1.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPPC_UIM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* �̶����ݼ��� */
PPPC_HRPD_FIXED_DATA_STRU               g_astPppcFixedData[MODEM_ID_BUTT];


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPPC_UIM_SndMsg
 ��������  : ��UIM���͵���Ϣ
 �������  : VOS_UINT32              ulSenderPid,
             VOS_UINT32              ulReceiverPid,
             VOS_VOID               *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  PPPC_UIM_SndMsg
(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_VOID                           *pMsg
)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          ulRslt;


    pstMsg                              = (MsgBlock *)pMsg;

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;

    /*��Ϣ����*/
    ulRslt   = PS_SEND_MSG(ulSenderPid, pstMsg);

    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG1(" PPPC_UIM_SndMsg ulRslt", ulRslt);
        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_GetModemId
 ��������  : ���ModemeId������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : c00199705
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 PPPC_UIM_GetModemId(VOS_VOID)
{
    VOS_UINT16                          usModemId;

    usModemId = PPPC_GetModemId();

    if (usModemId >= MODEM_ID_BUTT)
    {
        PPPC_ERROR_LOG1("Modem ID error", usModemId);
        return MODEM_ID_0;
    }

    return usModemId;
}

/*****************************************************************************
�� �� ��  :PPPC_UIM_ReadFileReq
��������  :��ȡ�ļ�����
�������  :ulSenderPid:���������PID
           pstGetFileInfo �ļ���Ϣ

�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK
���ú���  :

�޸���ʷ      :
 1.��    ��   : 2015��08��08��
   ��    ��   : w00316385
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  PPPC_UIM_ReadFileReq
(
    VOS_UINT32                          ulSenderPid,
    PPPC_GET_FILE_INFO_STRU            *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_CHAR                           *pucFilePathStr ;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usModemId;

    pstMsg          = VOS_NULL_PTR;
    pucFilePathStr  = VOS_NULL_PTR;

    /* ������� */
    if (VOS_NULL_PTR == pstGetFileInfo)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: pstGetFileInfo Is NULL.");
        return VOS_ERR;
    }

    /* �ļ�Idת�ļ�·�� */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstGetFileInfo->usEfId,&pucFilePathStr))
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: USIMM_ChangeDefFileToPath fail.");
        return VOS_ERR;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    /* ������Ϣ�ڴ� */
    pstMsg = (USIMM_READFILE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    /* ��д��Ϣ�� */
    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pucFilePathStr);
    pstMsg->bNeedReadCache              = VOS_TRUE;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen);

    usModemId = PPPC_UIM_GetModemId();
    if (MODEM_ID_0 == usModemId)
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);
    }
    else
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, I1_WUEPS_PID_USIM, pstMsg);
    }

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_ReadFileReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SndUimReadReq
 ��������  : ��UIM���Ͷ�ȡָ���ļ�����Ľӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32   �Ƿ��ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_INIT_SndUimReadReq(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSendInd;
    PPPC_GET_FILE_INFO_STRU             stGetFileInfo;
    VOS_UINT16                          usModemId;
    VOS_UINT16                          ausEfId[PPPC_MAX_USIM_FILE_NUM];

    usModemId = PPPC_UIM_GetModemId();

    /* ���ݿ������͸�ֵ */
    if( PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == PPPC_HRPD_GetUimStatus(usModemId))
    {
        ausEfId[0]            = USIMM_CSIM_EFRUIMID_ID;
        ausEfId[1]            = USIMM_CSIM_EFCSIMST_ID;
        ausEfId[2]            = USIMM_CSIM_EFESNMEID_ID;
        ausEfId[3]            = USIMM_CSIM_EFUSGIND_ID;
        ausEfId[4]            = USIMM_CSIM_EFHRPDUPP_ID;
        ausEfId[5]            = USIMM_CSIM_EFIMSIM_ID;
    }
    else if( PPPC_HRPD_CARD_STATUS_UIM_PRESENT == PPPC_HRPD_GetUimStatus(usModemId))
    {
        ausEfId[0]            = USIMM_CDMA_EFRUIMID_ID;
        ausEfId[1]            = USIMM_CDMA_EFCST_ID;
        ausEfId[2]            = USIMM_CDMA_EFESNMEIDME_ID;
        ausEfId[3]            = USIMM_CDMA_EFUSGIND_ID;
        ausEfId[4]            = USIMM_CDMA_EFHRPDUPP_ID;
        ausEfId[5]            = USIMM_CDMA_EFIMSIM_ID;
    }
    else
    {
        PPPC_WARNING_LOG("Unknow sim card type");
        return VOS_ERR;
    }

    /* USIM�ļ������ֿ����� */
    ausEfId[6]            = USIMM_USIM_EFIMSI_ID;
    ausEfId[7]            = USIMM_USIM_EFAD_ID;

    /* ���Ͷ�ȡ���� */
    ulSendInd = 0;
    while (ulSendInd < PPPC_MAX_USIM_FILE_NUM)
    {
        ulLoop = 0;
        while ((ulLoop < PPPC_MAX_USIM_REQSEND_NUM))
        {
            if (0 == PPPC_HRPD_GetUsimFileMask(usModemId, ulSendInd))
            {
                if ((USIMM_USIM_EFIMSI_ID == ausEfId[ulSendInd])
                     || (USIMM_USIM_EFAD_ID == ausEfId[ulSendInd]))
                {
                    stGetFileInfo.enAppType     = USIMM_GUTL_APP;
                }
                else
                {
                    stGetFileInfo.enAppType     = USIMM_CDMA_APP;
                }
                stGetFileInfo.usEfId        = ausEfId[ulSendInd];
                stGetFileInfo.ucRecordNum   = 0;

                /* ��ȡ */
                ulRslt = PPPC_UIM_ReadFileReq(MSPS_PID_PPPC, &stGetFileInfo);

                /* ����ļ���ȡ������Ƿ�ɹ� */
                if (USIMM_API_SUCCESS != ulRslt)
                {
                    PPPC_WARNING_LOG1("PPPC_INIT_SndUimReadReq,GetFileReq fail,ulEfId",
                                       ausEfId[ulLoop]);
                }
                ulLoop++;
            }
            ulSendInd++;
            if (ulSendInd >= PPPC_MAX_USIM_FILE_NUM)
            {
                return VOS_OK;
            }
        }
        VOS_TaskDelay(100);
    }
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveCst
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead  ��Ϣ����
             PPPC_HRPD_CST_STRU *pstCst
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveCst(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_CST_STRU *pstCst)
{
    if (PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE < pstUsimRead->usEfLen)
    {
        pstCst->ucCstLen = (VOS_UINT8)PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE;
    }
    else
    {
        pstCst->ucCstLen = (VOS_UINT8)pstUsimRead->usEfLen;
    }

    PS_MEM_CPY(pstCst->aucCst, pstUsimRead->aucEf, pstCst->ucCstLen);

    return;
}

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveHrpdupp
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead  ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveHrpdupp
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_UPP_STRU                 *pstHrpdUpp
)
{
    /* 3GPP2 C.S0023-D v2.0 3.4.53 HRPD Access Authentication User Profile Parameters or
       3GPP2 C.S0065-B v2.0 5.2.54 HRPD Access Authentication User Profile Parameters and
       3GPP2 C.S0016-D v2.0 3.5.8.13 HRPD Access Authentication User Profile Parameters */

    /* HRPDUPP Block Len(1byte) + NAI Len(1byte) + AUTH_ALGORITHM&Reserved(1byte) */
    const VOS_UINT8                     ucMinEFLen = 3;
    VOS_UINT8                           ucFileLen;
    VOS_UINT8                           ucNAILen;
    PS_BOOL_ENUM_UINT8                  enIsNAIFormValid = PS_FALSE;
    VOS_UINT8                           ucLoop = 0;
    VOS_UINT8                          *pucNaiData;

    /* ��������� */
    if ((0 != pstUsimRead->stCmdResult.ulResult)
        || (0 != pstUsimRead->stCmdResult.ulErrorCode)
        || (pstUsimRead->usEfLen <= ucMinEFLen))
    {
        PPPC_WARNING_LOG3("Read usim failed. ulResult:%d, ulErrorCode:%d, Eflen:%d.\n",
            pstUsimRead->stCmdResult.ulResult, pstUsimRead->stCmdResult.ulErrorCode, pstUsimRead->usEfLen);
        return;
    }

    /* The first byte is length of HRPD Access Authentication User Profile Parameters Block */
    ucFileLen = pstUsimRead->aucEf[0];
    /* The second byte is length of NAI*/
    ucNAILen  = pstUsimRead->aucEf[1];

    if ((0 == ucFileLen)
        || (0 == ucNAILen)
        || (ucFileLen >= pstUsimRead->usEfLen)
        || (ucNAILen >= ucFileLen))
    {
        PPPC_WARNING_LOG3("Invalid paras. filelen:%d, NAIlen:%d, Eflen:%d.\n",
            ucFileLen, ucNAILen, pstUsimRead->usEfLen);
        return;
    }

    /* The third byte is start of NAI*/
    pucNaiData = pstUsimRead->aucEf + 2;

    /* Check NAI is regular form user@realm, Just check contain '@' char */
    while (ucLoop < ucNAILen)
    {
        if ('@' == pucNaiData[ucLoop])
        {
            enIsNAIFormValid = PS_TRUE;
            break;
        }
        ucLoop++;
    }

    if (PS_FALSE == enIsNAIFormValid)
    {
        PPPC_WARNING_LOG3("Invalid NAI form. filelen:%d, NAIlen:%d, Eflen:%d.\n",
            ucFileLen, ucNAILen, pstUsimRead->usEfLen);
        return;
    }

    pstHrpdUpp->ucHrpdUppLen = ucFileLen;
    PS_MEM_SET(pstHrpdUpp->aucHrpdUpp, 0, PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE);
    PS_MEM_CPY(pstHrpdUpp->aucHrpdUpp, pstUsimRead->aucEf + 1, ucFileLen);

    /* ����NAI��Ϣ���������Ȩʹ�� */
    PPPC_SaveAccessAuthUserNameInfo(pstUsimRead->aucEf);

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveEsnMeid
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_ESN_MEID_STRU  *pstEsnMeid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveEsnMeid
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_ESN_MEID_STRU            *pstEsnMeid
)
{
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.24 */
    /*
    Bytes                   Description                         M/O         Length
    1       Number of bytes for ESN_ME or MEID_ME               M           1 byte
    2       Lowest-order byteLeast significant byte M 1 byte
    3                       :                                   M           1 byte
    4                       :                                   M           1 byte
    5                       :                                   M           1 byte
    6                       :                                   M           1 byte
    7                       :                                   M           1 byte
    8       Highest-order byteMost significant byte             M           1 byte
    */

    ucCount  = pstUsimRead->aucEf[0];

    if (4 == ucCount)
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_ESN;

        pstEsnMeid->u.ulEsn             = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);
    }
    else
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_MEID;

        /* �����MEID����32bit */
        pstEsnMeid->u.stMeid.ulMeidLow  = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);

        /* �����MEID����24bit */
        pstEsnMeid->u.stMeid.ulMeidHigh = (((VOS_UINT32)pstUsimRead->aucEf[7]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[6]) << (8))
                                        | (pstUsimRead->aucEf[5]);
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/


/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveRuimid
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_RUIMID_STRU    *pstRuimid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveRuimid(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_RUIMID_STRU *pstRuimid)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.17 */
    /*
    Bytes                   Description                         M/O         Length
    1                   Number of bytes                          M          1 byte
    2                   Lowest-order byte                        M          1 byte
    3                           :                                M          1 byte
    4                           :                                M          1 byte
    5                           :                                M          1 byte
    6                           :                                O          1 byte
    7                           :                                O          1 byte
    8                   Highest-order byte                       O          1 byte
    */

    ucCount                          = pstUsimRead->aucEf[0];

    pstRuimid->ucNumbytes            = ucCount;

    if (ucCount <= 4)
    {
        for (ulLoop = 0; ulLoop < ucCount; ulLoop++)
        {
            pstRuimid->ulRUIMIDLow  |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 1]) << (8 * ulLoop));
        }
    }
    else
    {
        pstRuimid->ulRUIMIDLow       = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                      | (pstUsimRead->aucEf[1]);

        /* �����ֽ� */
        for (ulLoop = 0; ulLoop < (VOS_UINT8)(ucCount - 4); ulLoop++)
        {
            pstRuimid->ulRUIMIDHigh |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 5]) << (8 * ulLoop));
        }
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveUsgInd
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead  ��Ϣ����
             VOS_UINT8 *pucSlotCycleIndex             SlotCycleIndex
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsgInd(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_USGIND_STRU *pstUsgind)
{
    /* C.S0065 5.2.14 */
    /*
    Byte 1:     b8 b7 b6 b5 b4 b3 b2 b1
                                     *  b1=0: ESN_ME is used for CAVE Authentication and MS Identification.
                                        b1=1: UIM_ID is used for CAVE Authentication and MS Identification.
                                  *     b2=0: MEID MEID_ME is used for MS Identification.
                                        b2=1: SF_EUIMID is used for MS Identification.
                *  *  *  *  *  *        RFU
    */

    pstUsgind->ucUsgInd       = pstUsimRead->aucEf[0] & 0x03;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_Uim_ChangeNum
 ��������  : ����Э��ƻ�ԭ��ֵ
 �������  : ulSrcValude  -- BCD���ŵ�λ��
             ulCodeMode   -- BCD�볤��

 �������  : ��
 �� �� ֵ  : VOS_UINT32 -����Э�黹ԭ����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 PPPC_Uim_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
{
    VOS_UINT32                          ulTempl   = 0;
    VOS_UINT32                          ulDstValue = 0;

    if (ulCodeMode >= 3)
    {
        ulTempl = ulSrcValude / 100;        /*��λ*/
        if (ulTempl + 1 <= 9)
        {
            ulDstValue += (ulTempl + 1) * 100;
        }
    }

    if (ulCodeMode >= 2)
    {
        ulTempl = (ulSrcValude / 10)  % 10; /*ʮλ*/
        if ( ulTempl+1 <= 9)
        {
            ulDstValue += (ulTempl+1 ) * 10;
        }
    }

    if (ulCodeMode >= 1)
    {
        ulTempl = ulSrcValude % 10;         /*��λ*/
        if (ulTempl +1 <= 9)
        {
            ulDstValue += ulTempl +1;
        }
    }

    return ulDstValue;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_NumToStr
 ��������  : ������תΪ����'/0'���ַ�����
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_UIM_NumToStr(VOS_UINT8 *pucArr, VOS_UINT32 ulNum, VOS_UINT8 ucLen)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulTmp;

    ulTmp = ulNum;

    for (ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        pucArr[ucLen - ucIndex - 1] = ulTmp % 10 + '0';
        ulTmp /= 10;
    }
}

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveIMSI
 ��������  : ����USIM��IMSI����Ϣ
 �������  : VOS_UINT8 *pucCIMSI     ����IMSI�ļ�����
             VOS_UINT8 *pucStrCIMSI  ��IMSI
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_INIT_SaveIMSI
(
    VOS_UINT8                           *pucCIMSI,
    PPPC_HRPD_UIM_INFO_STRU             *pstUimInfo
)
{
    VOS_UINT32                          ulMCC     = 0; /* ���Ҵ��� */
    VOS_UINT32                          ulMNC     = 0; /* ������� */
    VOS_UINT32                          ulMSIN_A  = 0; /* �ƶ��û���ݵ�0 - 3λ*/
    VOS_UINT32                          ulMSIN_B  = 0; /* �ƶ��û���ݵ�4 - 10λ*/
    VOS_UINT32                          ulMSIN_B1 = 0; /* �ƶ��û���ݵ�4 - 6λ*/
    VOS_UINT32                          ulMSIN_B2 = 0; /* �ƶ��û���ݵ�7λ*/
    VOS_UINT32                          ulMSIN_B3 = 0; /* �ƶ��û���ݵ�8 - 10λ*/
    VOS_UINT8                          *pucStrCIMSI = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucCIMSI) || (VOS_NULL_PTR == pstUimInfo))
    {
        return VOS_ERR;
    }

    /*
        6F22��ʽ��
        00 AA AA BB BB BB CC 80 DD DD

        00����CLASS=0
        AA AA����MINǰ3λ����
        BB BB BB����MIN��7λ����
        CC����MNC����
        80����IMSI_M_PROGRAMMED=1��IMSI_M_ADD_NUM=0

        DD DD����MCC����
        ����CDMA2000Э����6F22�ĸ�ʽ����1���ֽں͵�7���ֽڶ��ø㶨���������Ǳ�־λ�����á�

        ����AA AA����
        1����MIN��ǰ3λΪ�������ݣ��ָ��3����λ�����ֱ�����ΪD1��D2��D3
        2����������NUM = D1 * 100 + D2 * 10 + D3 - 111����D1��D2��D3�г���0������10���㣩
        3����NUMת��Ϊ2�ֽ�С�˸�ʽ16���ƣ�λ��������ǰ����0����AA AA�������

        ����BB BB BB����
        1����MIN��4-6λΪ���ݣ�����AA AA�ļ��㲽��1��2���NUM����NUMת��Ϊ10bit��2���ƣ�������0��
        2����MIN��7λ����ȡ���������ձ�׼10����ת2���Ƶļ��㷽���������4bit��2���ƣ�������0��(�����������0������10����)
        3����MIN��8-10λΪ���ݣ�����AA AA�ļ��㲽��1��2���NUM����NUMת��Ϊ10bit��2���ƣ�������0��
        4����ǰ3���ļ�������Ĺ�24bit��2������ƴ������ת����3�ֽ�С�˸�ʽ16��������BB BB BB�������

        ����CC����
        1����MNC�ָ��2����λ�����ֱ�����ΪD1��D2
        2����������NUM = D1 * 10 + D2 - 11����D1��D2�г���0������10���㣩
        3����NUMת��Ϊ1�ֽ�16���ơ�CC�������

        ����DD DD����
        1����MCCΪ���ݣ�����AA AA�ļ��㷽���������2�ֽ�С�˸�ʽ16���ƣ���ΪDD DD

        ���ӣ�
        ��֪IMSI�ţ�460036591141482
        ��IMSI�У�
        MCC��460
        MNC��03
        MIN��6591141482

        ����AA AA
        MINǰ3λ659��NUM = 6 * 100 + 5 * 10 + 9 - 111 = 548 ת����2�ֽ�С�˸�ʽ16����Ϊ��24 02

        ����BB BB BB
        MIN��4-6λ114��NUM = 1 * 100 + 1 * 10 + 4 - 111 = 3 ת����10bit��2����Ϊ��0000000011
        MIN��7λ1��ת��Ϊ4bit��2����Ϊ��0001
        MIN��8-10λ482��NUM = 4 * 100 + 8 * 10 + 2 - 111 = 371 ת����10bit��2����Ϊ��0101110011
        24bit��2������Ϊ��000000001100010101110011��ת����3�ֽ�С�˸�ʽ16����Ϊ��73 C5 00

        ����CC
        MNCΪ03��NUM = 10 * 10 + 3 - 11 = 92��ת����1�ֽ�16����Ϊ5C

        ����DD DD
        MCCΪ460��NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 ת����2�ֽ�С�˸�ʽ16����Ϊ��67 01

        ���˵õ�6F22�ļ�����ӦΪ
        00 24 02 73 C5 00 5C 80 67 01
        460036591141482
    */
    ulMCC     = pucCIMSI[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucCIMSI[9] << 8));
    ulMCC     = PPPC_Uim_ChangeNum(ulMCC,3);       /* ���Ҵ��� */

    ulMNC     = pucCIMSI[6];
    ulMNC     = PPPC_Uim_ChangeNum(ulMNC,2);       /* ������� */

    ulMSIN_A  = pucCIMSI[1];
    ulMSIN_A  = 0x0000FFFF & ( ulMSIN_A | (pucCIMSI[2] << 8));
    ulMSIN_A  = PPPC_Uim_ChangeNum(ulMSIN_A, 3);   /* �ƶ��û���ݵ�0 - 3λ*/

    ulMSIN_B  = pucCIMSI[3];
    ulMSIN_B  = 0x0000FFFF & (ulMSIN_B | (pucCIMSI[4] << 8));
    ulMSIN_B  = 0x00FFFFFF & (ulMSIN_B | (pucCIMSI[5] << 16));

    ulMSIN_B1 = ulMSIN_B >> 14;
    ulMSIN_B1 = PPPC_Uim_ChangeNum(ulMSIN_B1, 3); /* �ƶ��û���ݵ�4 - 6λ */

    ulMSIN_B2 = (ulMSIN_B & 0x3c00)>>10;         /* �ƶ��û���ݵ�7λ */
    ulMSIN_B2 = ulMSIN_B2 % 10;

    ulMSIN_B3 = ulMSIN_B & 0x3FF;
    ulMSIN_B3 = PPPC_Uim_ChangeNum(ulMSIN_B3, 3);  /* �ƶ��û���ݵ�8 - 10λ */

    pucStrCIMSI = pstUimInfo->aucImsi;

    PPPC_UIM_NumToStr(pucStrCIMSI,      ulMCC,      3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 3,  ulMNC,      2);
    PPPC_UIM_NumToStr(pucStrCIMSI + 5,  ulMSIN_A,   3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 8,  ulMSIN_B1,  3);
    PPPC_UIM_NumToStr(pucStrCIMSI + 11, ulMSIN_B2,  1);
    PPPC_UIM_NumToStr(pucStrCIMSI + 12, ulMSIN_B3,  3);


    pstUimInfo->ucImsiLen = PS_CUE_IMSI_MAX_SIZE;

	return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveUsimAD
 ��������  : ����USIM��AD����Ϣ
 �������  : VOS_UINT8 *pucCIMSI     ����IMSI�ļ�����
             VOS_UINT8 *pucStrCIMSI  ��IMSI
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��08��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimAD
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo
)
{
    const VOS_UINT8                     ucMinEFLen = 4;                         /* EFAD�ļ�����Ϊ3+X,X>=1����Ч */
    const VOS_UINT8                     ucMncLenOffset = 3;                     /* EFAD�ļ��е��ĸ��ֽ�ΪMNC���� */
    const VOS_UINT8                     ucMncDefaultLen = 2;                    /* MNCĬ��Ϊ2λ */
    const VOS_UINT8                     ucMncSpecialLen = 3;                    /* ���ֹ���MNCΪ��λ */
    VOS_UINT8                           ucMcnLen;

    /* 6FAD�ļ������51011-f40 10.3.18 */

    /* ��������� */
    if ((0 != pstUsimRead->stCmdResult.ulResult)
        || (0 != pstUsimRead->stCmdResult.ulErrorCode)
        || (pstUsimRead->usEfLen < ucMinEFLen))
    {
        PPPC_WARNING_LOG3("Read usim failed. ulResult:, ulErrorCode:, Eflen:.\n",
            pstUsimRead->stCmdResult.ulResult, pstUsimRead->stCmdResult.ulErrorCode, pstUsimRead->usEfLen);
        return;
    }

    /* EFAD�ļ��е��ĸ��ֽ�ΪMNC���� */
    ucMcnLen = pstUsimRead->aucEf[ucMncLenOffset];

    /* MNC����ֻ��Ϊ2����3 */
    if (ucMncSpecialLen != ucMcnLen)
    {
        ucMcnLen = ucMncDefaultLen;
    }

    pstUsimInfo->ucMncLen = ucMcnLen;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveUsimIMSI
 ��������  : ����USIM��IMSI����Ϣ
 �������  : VOS_UINT8 *pucCIMSI     ����IMSI�ļ�����
             VOS_UINT8 *pucStrCIMSI  ��IMSI
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��08��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimIMSI
(
    VOS_UINT8                          *pucIMSI,
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo
)
{
    VOS_UINT8                            ucImsiNum;
    VOS_UINT32                           ulLoop;
    VOS_UINT8                            ucMaxImsiData;

    ucMaxImsiData               = pucIMSI[0];
    if ( ucMaxImsiData > (8) )
    {
        PPPC_WARNING_LOG1("PPPC_INIT_SaveUsimIMSI, IMSI Oversize!", ucMaxImsiData);
        ucMaxImsiData           = 8;
    }

    ucImsiNum                   = 0;

    /* ȡ��һ���ֽڵĸ���λ, ��4λ�������� */
    pstUsimInfo->aucImsi[ucImsiNum]     = (( pucIMSI[1] >> 4 ) & 0x0F) + 0x30;
    ucImsiNum++;

    /* ȡ�����ֽ� */
    for ( ulLoop = 1 ; ulLoop < ucMaxImsiData; ulLoop++ )
    {
        pstUsimInfo->aucImsi[ucImsiNum] = (pucIMSI[ulLoop+1] & 0x0F) + 0x30 ;
        ucImsiNum++;

        pstUsimInfo->aucImsi[ucImsiNum] = ((pucIMSI[ulLoop+1] >> 4 ) & 0x0F) + 0x30;
        ucImsiNum++;
    }

    /* ����ȡ����IMSI���һ���ֽ��Ƿ���Ч���ִ��Ƿ���Ч */
    if ( 0x39 < pstUsimInfo->aucImsi[ucImsiNum - 1] || 0x30 > pstUsimInfo->aucImsi[ucImsiNum - 1])
    {
        pstUsimInfo->aucImsi[ucImsiNum - 1]= 0;
        ucImsiNum--;
    }

    pstUsimInfo->ucImsiLen = ucImsiNum;
}

/*****************************************************************************
 �� �� ��  : PPPC_INIT_SaveUsimInfo
 ��������  : ����USIM���ļ�����Ϣ
 �������  : USIMM_READFILE_CNF_STRU  *pstUsimRead  ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimInfo(USIMM_READFILE_CNF_STRU  *pstUsimRead)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimInfo;
    VOS_UINT32                          ulRslt;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;
    VOS_UINT16                          usModemId;
    USIMM_CARDAPP_ENUM_UINT32           enApptype;

    usModemId                           = PPPC_UIM_GetModemId();
    stFilePath                          = pstUsimRead->stFilePath;
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstUsimInfo                         = PPPC_HRPD_GetUsimDataAddr(usModemId);
    enApptype                           = pstUsimRead->stCmdResult.enApptype;

    ulRslt  = USIMM_ChangePathToDefFileID(enApptype, stFilePath.ulPathLen, stFilePath.acPath, &enDefFileID);

    /* ���ļ�·��ת��ΪID */
    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("PPPC_INIT_SaveUsimInfo: USIMM_ChangePathToDefFileID fail.");
        return;
    }

    /* ������Ҫ��ȡ���ļ�ID,�����Ӧ�Ķ�����־λ */
    switch(enDefFileID)
    {
        case USIMM_CSIM_EFRUIMID_ID :
        case USIMM_CDMA_EFRUIMID_ID :

            /* ������� */
            PPPC_INIT_SaveRuimid(pstUsimRead, &(pstUimInfo->stRuimid));

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
            break;

        case USIMM_CSIM_EFCSIMST_ID :
        case USIMM_CDMA_EFCST_ID :

            /* ������� */
            PPPC_INIT_SaveCst(pstUsimRead, &(pstUimInfo->stEfCst));

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_CST_MASK);
            break;

        case USIMM_CSIM_EFESNMEID_ID :
        case USIMM_CDMA_EFESNMEIDME_ID :

            /* ������� */
            PPPC_INIT_SaveEsnMeid(pstUsimRead, &(pstUimInfo->stEsnMeid));

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
            break;

        case USIMM_CSIM_EFUSGIND_ID :
        case USIMM_CDMA_EFUSGIND_ID :

            /* ������� */
            PPPC_INIT_SaveUsgInd(pstUsimRead, &(pstUimInfo->stUsgind));

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
            break;

        case USIMM_CSIM_EFHRPDUPP_ID :
        case USIMM_CDMA_EFHRPDUPP_ID :

            /* ������� */
            PPPC_INIT_SaveHrpdupp(pstUsimRead, &(pstUimInfo->stHrpdUpp));

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
            break;

        case USIMM_CSIM_EFIMSIM_ID :
        case USIMM_CDMA_EFIMSIM_ID :

            /* ������� */
            PPPC_INIT_SaveIMSI(pstUsimRead->aucEf, pstUimInfo);

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK);
            break;

        case USIMM_USIM_EFIMSI_ID:

            /* ������� */
            PPPC_INIT_SaveUsimIMSI(pstUsimRead->aucEf, pstUsimInfo);

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_EFIMSI_MASK);
            break;
        case USIMM_USIM_EFAD_ID:

            /* ������� */
            PPPC_INIT_SaveUsimAD(pstUsimRead, pstUsimInfo);

            /* ��ȡ�ɹ���־λ */
            PPPC_HRPD_AddUsimFileSucMask(usModemId, PPPC_INIT_USIM_EFAD_MASK);
            break;
        default:
            PPPC_WARNING_LOG1("PPPC_INIT_SaveUsimInfo, pstUsimRead->usEfId error, File:0x%x\n", enDefFileID);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetpEsnByMeid
 ��������  : ͨ��MEID��ȡpESN
 �������  : PPPC_HRPD_MEID_STRU *pucMeid
             VOS_UINT32 *pulEsn
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_GetpEsnByMeid(PPPC_HRPD_MEID_STRU *pstMeid, VOS_UINT32 *pulEsn)
{
    VOS_UINT8                           aucValue[20];
    VOS_UINT8                           aucMeidTemp[PPPC_HRPD_MEID_LEN];
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulpEsn;
    PPPC_SHA1_PARA_STRU                 stPara;

    if ((VOS_NULL_PTR == pstMeid) || (VOS_NULL_PTR == pulEsn))
    {
        return VOS_ERR;
    }

    /* 56��bit����MEID��Ϣ */
    aucMeidTemp[0]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x00FF0000) >> (16));
    aucMeidTemp[1]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x0000FF00) >> (8));
    aucMeidTemp[2]  = (VOS_UINT8)( pstMeid->ulMeidHigh & 0x000000FF );
    aucMeidTemp[3]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0xFF000000) >> (24));
    aucMeidTemp[4]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x00FF0000) >> (16));
    aucMeidTemp[5]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x0000FF00) >> (8));
    aucMeidTemp[6]  = (VOS_UINT8)( pstMeid->ulMeidLow  & 0x000000FF);

    PS_MEM_SET(aucValue, 0, sizeof(aucValue));

    stPara.ucNum        = 1;
    stPara.apucAdrr[0]  = aucMeidTemp;
    stPara.aulLen[0]    = PPPC_HRPD_MEID_LEN;

    if (VOS_OK != PPPC_SHA1(&stPara, aucValue))
    {
        PPPC_WARNING_LOG("Error When sha1 in PPPC_GetpEsnByMeid!");
        return VOS_ERR;
    }

    /* 1.  The upper 8 bits of pseudo-ESN shall be set to 0x80.

       2.  The lower 24 bits of pseudo-ESN shall be the 24 least significant bits of the
    SHA-1 digest of the MEID. See [10] for the specification of the SHA-1
    algorithm.
    */
    ulTmp   = ((aucValue[17] << 16)
             | (aucValue[18] << 8)
             | aucValue[19]);

    ulpEsn          = ulTmp | 0x80000000;

    *pulEsn         = ulpEsn;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_InitEsnMeidWhenB1B2Eq00
 ��������  :
            C.S0065��Э���У��������� 6F42 ���ݼ� EF(USGIND)ʱ������B1B2��ֵΪ'00'ʱ��
            �����C.S0073Э��2.3.1.4�½��еı��������ʹ��MEID��ΪMEID��ʹ��pESN��ΪESN

            ����MEID����ʹ��MEID����pESN��ΪESN��������ֱ��ʹ��ESN��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq00(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* �ж��Ƿ�Я��MEID�����У���ʹ��MEID���������pESN */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* ����MEID����SHA-1�㷨���pEsn, ����ҪESN�ĳ���ʹ�� */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* ��αESN��ֵ��Esn����֤����ҪESN�ĳ����¼���ʹ�� */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_InitEsnMeidWhenB1B2Eq01
 ��������  :
            C.S0065��Э���У��������� 6F42 ���ݼ� EF(USGIND)ʱ������B1B2��ֵΪ'01'ʱ��
            �����C.S0073Э��2.3.1.4�½��еı��������ʹ��MEID��ΪMEID��ʹ��pUIMID��ΪESN

            ����EUIMID����ʹ��EUIMID����pUIMID��ΪESN��������ֱ��ʹ��pUIMID��ΪESN��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq01(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* �ж��Ƿ�Я��EUIMID�����У�����������pUIMID��ΪESNʹ�� */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* ����MEID����SHA-1�㷨���pEsn, ����ҪESN�ĳ���ʹ�� */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* ��αESN��ֵ��Esn����֤����ҪESN�ĳ����¼���ʹ�� */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    /* �ж��Ƿ�Я��MEID�����У����ʹ��MEID */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_InitEsnMeidWhenB1B2Eq10
 ��������  :
            C.S0065��Э���У��������� 6F42 ���ݼ� EF(USGIND)ʱ������B1B2��ֵΪ'10'ʱ��
            �����C.S0073Э��2.3.1.4�½��еı��������ʹ��EUIMID��ΪMEID��ʹ��pESN��ΪESN

            ����MEID����ʹ��MEID����pESN��ΪESN��������ֱ��ʹ��ESN��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq10(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* �ж��Ƿ�Я��MEID�����У�����������pESN��ΪESNʹ�� */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* ����MEID����SHA-1�㷨���pEsn, ����ҪESN�ĳ���ʹ�� */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* ��αESN��ֵ��Esn����֤����ҪESN�ĳ����¼���ʹ�� */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    /* �ж��Ƿ�Я��EUIMID�����У����ʹ��EUIMID��ΪMEID */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPPC_InitEsnMeidWhenB1B2Eq11
 ��������  :
            C.S0065��Э���У��������� 6F42 ���ݼ� EF(USGIND)ʱ������B1B2��ֵΪ'11'ʱ��
            �����C.S0073Э��2.3.1.4�½��еı��������ʹ��EUIMID��ΪMEID��ʹ��pUIMID��ΪESN

            ����EUIMID����ʹ��EUIMID����pUIMID��ΪESN��������ֱ��ʹ��UIMID��ΪESN��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq11(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* �ж��Ƿ�Я��EUIMID�����У���ʹ��EUIMID��ΪMEID�����������pUIMID��ΪESNʹ�� */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* ����MEID����SHA-1�㷨���pEsn, ����ҪESN�ĳ���ʹ�� */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* ��αESN��ֵ��Esn����֤����ҪESN�ĳ����¼���ʹ�� */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : PPPC_InitEsnMeidByUim
 ��������  :

 3GPP2 C.S0065-B v2.0
 5.2.33  EFUSGIND (UIM_ID/SF_EUIMID Usage Indicator)

     This EF indicates whether the UIM_ID or ESN_ME is used as the 'ESN' value for
     CAVE authentication and MS identification, as per Section 4.6.1 of [46].
     This EF also indicates whether the SF_EUIMID or MEID_ME shall be used as the
     MEID field over the air when Service n34 is available.

     b1=0:   ESN_ME is used for CAVE Authentication and MS Identification.
     b1=1:    UIM_IDUIMID is used for CAVE Authentication and MS Identification.
     b2=0:    MEID MEID_ME is used for MS Identification.
     b2=1:    SF_EUIMID is used for MS Identification.

 C.S0073-A v1.0
 2.3.1.4  Method of Measurement

     Table 2 MEID and ESN fields in Extended Status Response Message
    -----------------------------------------------------------------------------------------
     No. | Mobile station support |         R-UIM            | Fields of Status Response Message
         |   of R-UIM             |     Configuration        |   MEID     |  ESN
    -----------------------------------------------------------------------------------------
     6.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '00'  |            |
    -----------------------------------------------------------------------------------------
     7.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '01'  |            |
    -----------------------------------------------------------------------------------------
     8.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '10'  |            |
    -----------------------------------------------------------------------------------------
     9.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '11'  |            |
    -----------------------------------------------------------------------------------------

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidByUim(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);

    /* ��B1Ϊ'0'��B2Ϊ'0'��ʹ��MEID/pESN */
    if (0x00 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq00();
    }
    /* ��B1Ϊ'1'��B2Ϊ'0'��ʹ��MEID/pUIMID */
    else if (0x01 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq01();
    }
    /* ��B1Ϊ'0'��B2Ϊ'1'��ʹ��SF_EUIMID/pESN */
    else if (0x02 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq10();
    }
    /* ��B1Ϊ'1'��B2Ϊ'1'��ʹ��SF_EUIMID/pUIMID */
    else if (0x03 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq11();
    }
    else
    {
        /* �����쳣�������ο���ˣ��ö���ʱ��ʼ����Ĭ��ֵ0 */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_GetCIMSI
 ��������  : ��ȡCSIM��IMSI
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��IMSI
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UIM_GetCIMSI(VOS_UINT8 aucIMSI[])
{
    VOS_UINT8                          *pucIMSI;
    VOS_UINT16                          usModemId;
    PPPC_HRPD_UIM_INFO_STRU            *pstUimData;

    usModemId                           = PPPC_UIM_GetModemId();

    pstUimData = PPPC_HRPD_GetUimDataAddr(usModemId);
    pucIMSI = pstUimData->aucImsi;
    if(0 == *pucIMSI)
    {
        PPPC_WARNING_LOG("Dont have IMSI");
        return VOS_ERR;
    }

    PS_MEM_CPY(aucIMSI, pucIMSI, PS_CUE_IMSI_MAX_SIZE);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_GetUsimIMSI
 ��������  : ��ȡUSIM��IMSI
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��IMSI
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��08��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UIM_GetUsimIMSI(VOS_UINT8 aucIMSI[])
{
    VOS_UINT8                          *pucIMSI;
    VOS_UINT16                          usModemId;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimData;

    usModemId                           = PPPC_UIM_GetModemId();

    pstUsimData = PPPC_HRPD_GetUsimDataAddr(usModemId);
    pucIMSI = pstUsimData->aucImsi;
    if(0 == pstUsimData->ucImsiLen)
    {
        PPPC_WARNING_LOG("Dont have IMSI");
        return VOS_ERR;
    }

    PS_MEM_CPY(aucIMSI, pucIMSI, PS_CUE_IMSI_MAX_SIZE);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_UimClearnReadTimer
 ��������  : ��������ļ���ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_UimClearnReadTimer(VOS_VOID)
{
    PPPC_HRPD_FIXED_DATA_STRU          *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetFixedDataAddr(usModemId);

    /* ��������ļ���ʱ�� */
    pstUimInfo->stUimReadTimer.hTimer = VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : PPPC_InitFixedData
 ��������  : ��ʼ��FidData�е�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  PPPC_InitFixedData(VOS_VOID)
{
    PPPC_HRPD_FIXED_DATA_STRU          *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetFixedDataAddr(usModemId);

    PS_MEM_SET(pstUimInfo, 0, sizeof(PPPC_HRPD_FIXED_DATA_STRU));
}

/*****************************************************************************
 �� �� ��  : PPPC_ReadFixedData
 ��������  : ��SIM���ж�ȡ�������Լ�NVIM�ж��������ݵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  PPPC_ReadFixedData(VOS_VOID)
{
    PPPC_HRPD_UIM_STATUS_ENUM_UINT8     enUimStatus;
    VOS_UINT32                          ulUimFileReqMask;
    VOS_UINT32                          ulUimFileSuccMask;
    VOS_UINT32                          ulUimReadRetryCnt;
    HTIMER*                             phUimReadTimer;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();

    /* ����п������ȡ����Ϣ */
    enUimStatus     = PPPC_HRPD_GetUimStatus(usModemId);
    if ((PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == enUimStatus)
        || (PPPC_HRPD_CARD_STATUS_UIM_PRESENT == enUimStatus))
    {
        ulUimFileReqMask  = PPPC_HRPD_GetUsimFileReqMask(usModemId);
        ulUimFileSuccMask = PPPC_HRPD_GetUsimFileSucMask(usModemId);

        /* �����Ҫ���Ŀ��ļ���ʾ */
        if (0 == ulUimFileReqMask)
        {
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_CST_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
            PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK);

            /* ��USIM��ȥ��ȡUSIM��IMSI */
            if (PS_TRUE == PPPC_HRPD_GetUsimStatus(usModemId))
            {
                PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_EFIMSI_MASK);
                PPPC_HRPD_AddUsimFileReqMask(usModemId, PPPC_INIT_USIM_EFAD_MASK);
            }

            ulUimFileReqMask  = PPPC_HRPD_GetUsimFileReqMask(usModemId);
        }

        /* ���Ͷ�UIM��Ϣ */
        if (ulUimFileSuccMask != ulUimFileReqMask)
        {
            PPPC_INIT_SndUimReadReq();
        }
    }
    else
    {
        /* ���ÿ�״̬ */
        PPPC_HRPD_SetUimStatus(usModemId, PPPC_HRPD_UIM_STATUS_ABSENT);
    }

    /* ����3s��ʱ����������ļ�ʧ�����·�����ļ����������ж�ʱ����ͣ����ʱ��������*/
    phUimReadTimer    = PPPC_HRPD_UimReadTimer(usModemId);
    if (VOS_NULL_PTR != *phUimReadTimer)
    {
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, 0);
        ulRet = VOS_StopRelTimer((HTIMER*)phUimReadTimer);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Stop UimRead timer fail!", ulRet);
            return VOS_ERR;
        }
        PPPC_HRPD_UimClearnReadTimer();
    }

    ulUimReadRetryCnt = PPPC_HRPD_UimReadRetryCnt(usModemId);

    if (ulUimReadRetryCnt < PPPC_HRPD_UIMREAD_MAX_RETRY_CNT)
    {
        (VOS_VOID)VOS_StartRelTimer((HTIMER*)phUimReadTimer,
            MSPS_PID_PPPC, PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER_LEN,
            0, PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        ulUimReadRetryCnt++;
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, ulUimReadRetryCnt);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_MD5Active
 ��������  : MD5�㷨�Ƿ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��8��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID)
{
    VOS_UINT8                           ucType;
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();
    pstUimInfo      = PPPC_HRPD_GetUimDataAddr(usModemId);
    ucType          = pstUimInfo->stEfCst.aucCst[1];


    /*  b1Ϊ0˵����֧��MD5�㷨��b2Ϊ0˵��MD5�㷨δ���� */
    if ((0 == (ucType & 0x01)) || (0 == (ucType & 0x02)))
    {
        return PS_FALSE;
    }

    /* UIM��6F57�ļ�ȫΪ0��F */
    if (0 == pstUimInfo->stHrpdUpp.ucHrpdUppLen)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_RunCaveAuthReq
 ��������  : ��UIM����RUN CAVE����
 �������  : VOS_UINT32 ulRandu
 �������  : ��
 �� �� ֵ  : VOS_UINT32   �Ƿ��ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usModemId;

    usModemId       = PPPC_UIM_GetModemId();
    pstTerminalInfo = PPPC_HRPD_GetTerminalInfoAddr(usModemId);

    /* ������Ϣ�ڴ沢��ʼ�� */
    /* ������Ϣ�ڴ� */
    pstMsg = (USIMM_AUTHENTICATION_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_RunCaveAuthReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.enMsgName               = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.enAppType               = USIMM_CDMA_APP;
    pstMsg->stMsgHeader.ulSendPara              = 0;

    /* ��д��Ϣ�� */
    pstMsg->enAuthType                          = USIMM_RUNCAVE_AUTH;
    pstMsg->uAuth.stRunCaveAuth.ucRandType      = USIMM_RUNCAVE_RAND;
    pstMsg->uAuth.stRunCaveAuth.ucDigLen        = 0;
    pstMsg->uAuth.stRunCaveAuth.ucProcessCtrl   = PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON;

    /* ��� RANDU 24bit */
    pstMsg->uAuth.stRunCaveAuth.aucRand[3]      = (VOS_UINT8)( ulRandu & 0x000000FF );
    pstMsg->uAuth.stRunCaveAuth.aucRand[2]      = (VOS_UINT8)(( ulRandu & 0x0000FF00 ) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucRand[1]      = (VOS_UINT8)(( ulRandu & 0x00FF0000 ) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucRand[0]      = (VOS_UINT8)(( ulRandu & 0xFF000000 ) >> 24);

    /* ���ݽ����������Digit���� */
    /* Ĭ��ֵΪ0 */
    pstMsg->uAuth.stRunCaveAuth.aucDigits[0]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[1]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[2]    = 0;

    /* ���ESN������ */
    pstMsg->uAuth.stRunCaveAuth.aucEsn[0]       =
                  (VOS_UINT8)(pstTerminalInfo->ulEsn & 0x000000FF);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[1]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x0000FF00) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[2]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x00FF0000) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[3]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0xFF000000) >> 24);

    if (MODEM_ID_0 == usModemId)
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);
    }
    else
    {
        ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, I1_WUEPS_PID_USIM, pstMsg);
    }

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_RunCaveAuthReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPPC_UsimmReadFileCnfProc
 ��������  : PPPCģ���ȡ�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��25��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulEFID;
    VOS_UINT16                          usModemId;
    VOS_UINT32                          ulRet;
    HTIMER*                             phUimReadTimer;

    usModemId = PPPC_UIM_GetModemId();
    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    /* �����ɹ�,�ű���USIM����Ϣ */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        PPPC_INIT_SaveUsimInfo(pstMsg);
    }
    else
    {
        /* Ҫ��ȡ���ļ�ʧ�� */
        PPPC_WARNING_LOG1("PPPC_UsimmGetFileRspMsgProc, ulResult", pstMsg->stCmdResult.ulResult);
    }

    /* ������еĿ��ļ�����ȡ��� */
    if (PPPC_HRPD_GetUsimFileReqMask(usModemId) == PPPC_HRPD_GetUsimFileSucMask(usModemId))
    {
        /* ���ݿ��ļ���ʼ�� ESN */
        PPPC_InitEsnMeidByUim();

        /* �����ʱ�� */
        phUimReadTimer      = PPPC_HRPD_UimReadTimer(usModemId);
        PPPC_HRPD_SetUimReadRetryCnt(usModemId, 0);
        if (VOS_NULL_PTR != *phUimReadTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)phUimReadTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop UimRead timer fail!", ulRet);
            }
            PPPC_HRPD_UimClearnReadTimer();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_PihUsimStatusIndProc
 ��������  : �յ�PIHģ���ϱ��Ŀ�״ָ̬ʾ��Ϣ��Ԥ����
 �������  : USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg)
{
    VOS_UINT8                           ucSimType;
    PS_BOOL_ENUM_UINT8                  enUsimStatu;


    if (USIMM_CARD_USIM == pstUsimMsg->stUsimSimInfo.enCardType)
    {
        enUsimStatu = PS_TRUE;
    }
    else
    {
        enUsimStatu = PS_FALSE;
    }

    switch (pstUsimMsg->stCsimUimInfo.enCardType)
    {
        case USIMM_CARD_UIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_UIM_PRESENT;
            break;

        case USIMM_CARD_CSIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_CSIM_PRESENT;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = PPPC_HRPD_UIM_STATUS_ABSENT;
            break;
    }

    if (MAPS_PIH_PID == pstUsimMsg->ulSenderPid)
    {
        PPPC_HRPD_SetUimStatus(MODEM_ID_0, ucSimType);
        PPPC_HRPD_SetUsimStatus(MODEM_ID_0, enUsimStatu);
    }
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else
    {
        PPPC_HRPD_SetUimStatus(MODEM_ID_1, ucSimType);
        PPPC_HRPD_SetUsimStatus(MODEM_ID_1, enUsimStatu);
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_BuildNAIByIMSI
 ��������  : ����IMSI��������Ȩʹ�õ�NAI��Ϣ
 �������  : VOS_UINT32 ulNAIBuffLen
 �������  : VOS_UINT8 *pucNAIBuff
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��02��
    ��    ��   : c00338085
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UIM_BuildNAIByIMSI(VOS_UINT8 *pucNAIBuff, VOS_UINT32 ulNAIBuffLen)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT16                          usModemId;
    VOS_UINT32                          ulNAIDataLen;

    usModemId                           = PPPC_UIM_GetModemId();
    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr(usModemId);

    if (0 != pstUimInfo->ucImsiLen)
    {
        ulNAIDataLen = (pstUimInfo->ucImsiLen + PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN);

        /* ʹ��IMSI��������ʽΪIMSI@mycdma.cn��NAI */
        if (ulNAIBuffLen > ulNAIDataLen)
        {
            VOS_StrNCpy((VOS_CHAR *)pucNAIBuff, (VOS_CHAR *)pstUimInfo->aucImsi, pstUimInfo->ucImsiLen);
            VOS_StrNCpy((VOS_CHAR *)(pucNAIBuff + pstUimInfo->ucImsiLen), PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR, PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN);
            pucNAIBuff[ulNAIDataLen] = '\0';

            return VOS_OK;
        }
    }
    else
    {
        /* �̶�ʹ��д����NAI */
        if (ulNAIBuffLen > PPPC_HRPD_AUTH_NAI_STUB_LEN)
        {
            VOS_StrNCpy((VOS_CHAR *)pucNAIBuff, PPPC_HRPD_AUTH_NAI_STUB_STR, PPPC_HRPD_AUTH_NAI_STUB_LEN);
            pucNAIBuff[PPPC_HRPD_AUTH_NAI_STUB_LEN] = '\0';

            return VOS_OK;
        }
    }

    pucNAIBuff[0] = '\0';
    PPPC_WARNING_LOG2("Build NAI Fail. NAIBuffLen:%d, ImsiLen:%d.\n", ulNAIBuffLen, pstUimInfo->ucImsiLen);

    return VOS_ERR;
}

/*****************************************************************************
  �� �� ��  : PPPC_UIM_SendEapAuthReq
  ��������  : �򿨷���EAP��Ȩ����
  �������  : pucRand        AT_RAND
              pucAutn        AT_AUTN
              ucIdentifier   ͸������
  �������  : ��
  �� �� ֵ  : VOS_UINT32
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UIM_SendEapAuthReq
(
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucIdentifier
)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    VOS_UINT16                          usModemId;


    /* �ڲ����ã���֤��ηǿ� */

    /* ������Ϣ�ڴ� */
    pstMsg   = (USIMM_AUTHENTICATION_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_AUTHENTICATION_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*�����Ϣ����*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_AUTHENTICATION_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    usModemId = PPPC_UIM_GetModemId();
    if (MODEM_ID_0 == usModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara            = (VOS_UINT32)ucIdentifier;

    pstMsg->enAuthType                        = USIMM_3G_AUTH;

    pstMsg->uAuth.st3GAuth.stAutn.ucDataLen  = PPPC_EAP_AUTN_LEN;
    pstMsg->uAuth.st3GAuth.stRand.ucDataLen  = PPPC_EAP_RAND_LEN;

    PS_MEM_CPY(pstMsg->uAuth.st3GAuth.stAutn.aucData, pucAutn, PPPC_EAP_AUTN_LEN);
    PS_MEM_CPY(pstMsg->uAuth.st3GAuth.stRand.aucData, pucRand, PPPC_EAP_AUTN_LEN);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_UIMEAP_AUTH_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
  �� �� ��  : PPPC_UIM_GetImsiMncLen
  ��������  : ��ȡMNC����
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT8
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2016��1��25��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 PPPC_UIM_GetImsiMncLen(VOS_VOID)
{
    VOS_UINT16                          usModemId;
    PPPC_HRPD_USIM_INFO_STRU           *pstUsimData;
    VOS_UINT8                           ucMncLen;
    const VOS_UINT8                     ucMncDefaultLen = 2;                    /* MNCĬ��Ϊ2λ */
    const VOS_UINT8                     ucMncSpecialLen = 3;                    /* ���ֹ���MNCΪ��λ */

    usModemId                           = PPPC_UIM_GetModemId();

    pstUsimData = PPPC_HRPD_GetUsimDataAddr(usModemId);

    ucMncLen = pstUsimData->ucMncLen;

    /* MNC�ĳ���ֻ����2��3�����������ֵ��ʹ��Ĭ��ֵ2 */
    if (ucMncSpecialLen != ucMncLen)
    {
        ucMncLen = ucMncDefaultLen;
    }

    return ucMncLen;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
