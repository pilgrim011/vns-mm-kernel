/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaSecure.c
  �� �� ��   : ����
  ��    ��   : ���Ͻ�/00198894
  ��������   : 2012��8��30��
  ����޸�   :
  ��������   : ����MTAģ�鰲ȫ��غ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��30��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafMtaSecure.h"
#include "TafMtaMain.h"
#include "ScInterface.h"
#include "SysNvId.h"
#include "TafNvInterface.h"
#include "NVIM_Interface.h"
#include "TafMtaComm.h"
#include "mdrv.h"
#include "TafSdcCtx.h"
#include "NasUsimmApi.h"
#include "NasMsccPifInterface.h"
#include "TafMmaFsmPhoneMode.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "omnvinterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 �޸���: ���Ͻ� 00198894; ԭ��: Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_SECURE_C
/*lint +e767 �޸���: ���Ͻ� 00198894; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MTA_ConvertScErr
 ��������  : ת��SCģ�鷵�صĴ�����
 �������  : enErrCode  -- SCģ�鷵�صĴ�����
 �������  : ��
 �� �� ֵ  : MTA_AT_RESULT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_ConvertScErr(
    SC_ERROR_CODE_ENUM_UINT32           enErrCode
)
{
    switch(enErrCode)
    {
        case SC_ERROR_CODE_NO_ERROR:
            return MTA_AT_RESULT_NO_ERROR;

        case SC_ERROR_CODE_OPEN_FILE_FAIL:
        case SC_ERROR_CODE_READ_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR;

        case SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL:
        case SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

        case SC_ERROR_CODE_DK_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT;

        case SC_ERROR_CODE_UNLOCK_KEY_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT;

        case SC_ERROR_CODE_RSA_ENCRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL;

        case SC_ERROR_CODE_RSA_DECRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL;

        case SC_ERROR_CODE_GET_RAND_NUMBER_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL;

        case SC_ERROR_CODE_IDENTIFY_FAIL:
        case SC_ERROR_CODE_IDENTIFY_NOT_FINISH:
            return MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL;

        case SC_ERROR_CODE_WRITE_HUK_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL;

        case SC_ERROR_CODE_NV_READ_FAIL:
        case SC_ERROR_CODE_NV_WRITE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;

        case SC_ERROR_CODE_LOCK_CODE_INVALID:
        case SC_ERROR_CODE_CREATE_KEY_FAIL:
        case SC_ERROR_CODE_GENERATE_HASH_FAIL:
        case SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL:
        case SC_ERROR_CODE_ALLOC_MEM_FAIL:
        case SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL:
        case SC_ERROR_CODE_BUTT:
        default:
            /* ���������Լ��������󣬷���OTHER_ERROR */
            return MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtApSecSetReq
 ��������  : ����ATģ�鷢�͵�ID_AT_MTA_APSEC_SET_REQ��Ϣ
 �������  : VOS_VOID *pMsg     -- ATģ�鷢�͵���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��30��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : V7R1C50 ISDB ��ȫ�洢��Ŀ�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtApSecSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_APSEC_REQ_STRU              *pstApSecReq;
    MTA_AT_APSEC_CNF_STRU               stApSecCnf;
    VOS_UINT32                          ulResult;

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstApSecReq     = (AT_MTA_APSEC_REQ_STRU*)pstAtMtaReqMsg->aucContent;

    /* ����SCģ���ṩ�İ�ȫ����������� */
    ulResult        = SC_APSEC_ParseSecPacket(&pstApSecReq->ulSPLen,
                                              pstApSecReq->aucSecPacket);
    if (VOS_OK == ulResult)
    {
        /* �����ɹ��������صİ�ȫ������͸�ATģ�� */
        stApSecCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stApSecCnf.ulSPLen  = pstApSecReq->ulSPLen;
        PS_MEM_CPY(stApSecCnf.aucSecPacket, pstApSecReq->aucSecPacket, MTA_SEC_PACKET_MAX_LEN);
    }
    else
    {
        /* ����ʧ�ܣ����ض�Ӧ�Ĵ����� */
        PS_MEM_SET(&stApSecCnf, 0x00, sizeof(MTA_AT_APSEC_CNF_STRU));
        stApSecCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_APSEC_SET_CNF,
                      sizeof(MTA_AT_APSEC_CNF_STRU),
                      (VOS_UINT8*)&stApSecCnf );

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSimlockUnlockSetReq
 ��������  : ����ATģ�鷢�͵�ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ��Ϣ
 �������  : VOS_VOID *pMsg     -- ATģ�鷢�͵���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : STK�������Լ�DCM���󿪷���Ŀ�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSimlockUnlockSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_SIMLOCKUNLOCK_REQ_STRU      *pstSimlockUnlockReq;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU       stSimlockUnlockCnf;
    VOS_UINT32                          ulResult;

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSimlockUnlockReq     = (AT_MTA_SIMLOCKUNLOCK_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* ����SCģ���ṩ������������������ */
    ulResult        = SC_PERS_SimlockUnlock(pstSimlockUnlockReq->enCategory,
                                            pstSimlockUnlockReq->aucPassword);
    if (VOS_OK == ulResult)
    {
        /* �����ɹ������ؽ����ATģ�� */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        /* ����ʧ�ܣ����ؽ����ATģ�� */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,
                      sizeof(MTA_AT_SIMLOCKUNLOCK_CNF_STRU),
                      (VOS_UINT8*)&stSimlockUnlockCnf );

    return;
}

/**********************************************************
 �� �� ��  : TAF_MTA_RcvQryImeiVerifyReq
 ��������  : IMEI У��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��23��
    ��    ��   : Y00213812
    �޸�����   : ��������
*************************************************************/
VOS_VOID TAF_MTA_RcvQryImeiVerifyReq(VOS_VOID *pMsg)
{
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulImeiVerify;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;

    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    ulImeiVerify = VOS_TRUE;

    /* ��PID��ȡMODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* ����SC�ӿڽ���IMEIУ�飬������ִ��ʧ�ܣ�����IMEIУ��ʧ�ܴ��� */
    enScResult = SC_PERS_VerifyIMEI(enModemId);
    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        ulImeiVerify = VOS_FALSE;
    }

    /* ���ؿ����ϢID_MTA_AT_IMEI_VERIFY_QRY_CNF��ATģ�� */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_IMEI_VERIFY_QRY_CNF,
                      sizeof(VOS_UINT32),
                      (VOS_UINT8*)&ulImeiVerify );

    return;
}

/**********************************************************
 �� �� ��  : TAF_MTA_RcvQryCgsnReq
 ��������  : IMEI У��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��23��
    ��    ��   : Y00213812
    �޸�����   : ��������
*************************************************************/
VOS_VOID TAF_MTA_RcvQryCgsnReq(VOS_VOID *pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;
    MTA_AT_CGSN_QRY_CNF_STRU            stCgsnCnf;

    /* ��ʼ�� */
    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    PS_MEM_SET(&stCgsnCnf, 0x00, sizeof(MTA_AT_CGSN_QRY_CNF_STRU));

    /* ��PID��ȡMODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* ����SC�ӿڶ�ȡIMEI���� */
    (VOS_VOID)SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, stCgsnCnf.aucImei, NV_ITEM_IMEI_SIZE);

    /* ���ؿ����ϢID_MTA_AT_IMEI_VERIFY_QRY_CNF��ATģ�� */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_CGSN_QRY_CNF,
                      sizeof(MTA_AT_CGSN_QRY_CNF_STRU),
                      (VOS_UINT8*)&stCgsnCnf );

    return;
}


/*lint +e958*/

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtNvwrSecCtrlSetReq
 ��������  : ����ATģ�鷢�͵�ID_AT_MTA_NVWRSECCTRL_SET_REQ��Ϣ
 �������  : VOS_VOID *pMsg     -- ATģ�鷢�͵���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��04��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtNvwrSecCtrlSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_NVWRSECCTRL_SET_REQ_STRU    *pstNvwrSecCtrlReq;
    MTA_AT_RESULT_CNF_STRU              stNvwrSecCtrlCnf;
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    IMEI_STRU                           stImeiSrc;
    IMEI_STRU                           stImeiPara;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulImeiLen;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImeiStr[TAF_NVIM_ITEM_IMEI_SIZE + 1];

    /* �ֲ�������ʼ�� */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstNvwrSecCtrlReq       = (AT_MTA_NVWRSECCTRL_SET_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* SC�ṩ��RSA��װ��Ҫ�����߽����ܺ�����Ԥ�ڳ��ȴ��� */
    ulImeiLen               = MTA_IMEI_LEN;

    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));
    PS_MEM_SET(&stNvwrSecCtrlCnf, 0x00, sizeof(stNvwrSecCtrlCnf));
    PS_MEM_SET(&stImeiSrc, 0x00, sizeof(stImeiSrc));
    PS_MEM_SET(&stImeiPara, 0x00, sizeof(stImeiPara));
    PS_MEM_SET(aucImeiStr, 0x00, sizeof(aucImeiStr));

    /* �������û��HUK������ȫУ�� */
    if (VOS_TRUE == mdrv_efuse_check_huk_valid())
    {
        /* �����Ѿ�д��HUK��δ�·���ȫ�����򷵻�ʧ�� */
        if (VOS_TRUE != pstNvwrSecCtrlReq->ucSecStrFlg)
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* ��PID��ȡMODEMID */
        enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

        /* ����SC�ӿڶ�ȡIMEI���� */
        ulResult = SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, stImeiSrc.aucImei, TAF_NVIM_ITEM_IMEI_SIZE);

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* �쳣�����ؽ����ATģ�� */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* ����SCģ��ӿ�, �����Ľ���RSA���� */
        ulResult = SC_FAC_RsaDecrypt(pstNvwrSecCtrlReq->aucSecString,
                                     AT_RSA_CIPHERTEXT_LEN,
                                     aucImeiStr,
                                     &ulImeiLen);

        if (MTA_IMEI_LEN != ulImeiLen)
        {
            ulResult = SC_ERROR_CODE_RSA_DECRYPT_FAIL;
        }

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* �쳣�����ؽ����ATģ�� */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* �����ַ���ת��Ϊ���ִ� */
        if (VOS_OK != TAF_MTA_AcNums2DecNums(aucImeiStr, stImeiPara.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* У��IMEI�� */
        if (0 != PS_MEM_CMP(stImeiPara.aucImei, stImeiSrc.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* �޸İ�ȫ����NV */
    if (NV_OK == NV_Read(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        stNvwrSecCtrlNV.ucSecType = pstNvwrSecCtrlReq->ucSecType;

        if (NV_OK == NV_Write(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
        {
            /* ���óɹ� */
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_NO_ERROR;

            /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* NV�޸�ʧ�� */
    stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_ERROR;

    /* ���ؿ����ϢID_MTA_AT_APSEC_SET_CNF��ATģ�� */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                      sizeof(stNvwrSecCtrlCnf),
                      (VOS_UINT8*)&stNvwrSecCtrlCnf );

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#ifdef DMT
VOS_UINT32 CAS_GetpEsnByMeid(VOS_UINT8 *pucMeid, VOS_UINT32 *pulEsn)
{
    *pulEsn = 0x80c16f14;

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvMeidSetReq
 ��������  : MTAԤ�����д���^MEID��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��23��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvMeidSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    AT_MTA_MEID_SET_REQ_STRU           *pstMeidSetReq   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stMeifSetCnf;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT32                          ulEsn;

    PS_MEM_SET(&stMeId, 0x00, sizeof(NV_MEID_STRU));
    PS_MEM_SET(&stPEsn, 0x00, sizeof(NV_PESN_STRU));
    PS_MEM_SET(&stEsnMeId, 0x00, sizeof(NV_ESN_MEID_STRU));
    PS_MEM_SET(&stMeifSetCnf, 0x00, sizeof(stMeifSetCnf));

    pstSetReq           = (AT_MTA_MSG_STRU *)pMsg;
    pstMeidSetReq       = (AT_MTA_MEID_SET_REQ_STRU *)pstSetReq->aucContent;

    PS_MEM_CPY(stMeId.aucMeID, pstMeidSetReq->aucMeid, AT_MTA_MEID_DATA_LEN * sizeof(VOS_UINT8));

    /* ����meid����pesn */
    if (VOS_OK != CAS_GetpEsnByMeid(pstMeidSetReq->aucMeid, &ulEsn))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():Cal PESN Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stPEsn.aucPEsn[0] = ((VOS_UINT8)ulEsn & 0xFF);
    stPEsn.aucPEsn[1] = ((VOS_UINT8)(ulEsn>>8) & 0xFF);
    stPEsn.aucPEsn[2] = ((VOS_UINT8)(ulEsn>>16) & 0xFF);
    stPEsn.aucPEsn[3] = ((VOS_UINT8)(ulEsn>>24) & 0xFF);

    if (NV_OK != NV_Write(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    if (NV_OK != NV_Write(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_PESN NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    /* �����ϵ�NV�� */
    stEsnMeId.enEsnMeIDFlag = MEID_ME_ENABLE_FLAG;
    stEsnMeId.aucEsn[0]     = PESN_NV_DATA_LEN;
    PS_MEM_CPY(&(stEsnMeId.aucEsn[1]), stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    stEsnMeId.aucMeID[0]    = MEID_NV_DATA_LEN_NEW;
    PS_MEM_CPY(&(stEsnMeId.aucMeID[1]), stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

    if (NV_OK != NV_Write(en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(stEsnMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_ESN_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stMeifSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_MTA_AT_MEID_SET_CNF,
                     sizeof(stMeifSetCnf),
                     (VOS_UINT8*)&stMeifSetCnf );

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvMeidQryReq
 ��������  : MTAԤ�����д���^MEID��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvMeidQryReq(
    VOS_VOID                           *pMsg
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimCardStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8                          enCsimStatus;
    MTA_AT_MEID_QRY_CNF_STRU                                stMeifQryCnf;
    AT_MTA_MSG_STRU                                        *pstQryReq       = VOS_NULL_PTR;
    TAF_SDC_SIM_TYPE_ENUM_UINT8                             enCsimType;

    PS_MEM_SET(&stMeifQryCnf, 0x00, sizeof(stMeifQryCnf));

    pstQryReq = (AT_MTA_MSG_STRU *)pMsg;

#ifdef DMT
    enCsimStatus = TAF_SDC_USIM_STATUS_UNVALID;
#else
    enCsimStatus = TAF_SDC_GetCsimStatus();
#endif

    enCsimType   = TAF_SDC_GetCsimType();

    /* ����coverity�澯 */
    if (TAF_SDC_USIM_STATUS_BUTT == enCsimStatus)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq: Csim Status is BUTT!");
    }

    if (TAF_SDC_SIM_TYPE_BUTT == enCsimType)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq: Csim Type is BUTT!");
    }
    /* ����coverity�澯 */

    enCsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enCsimStatus, enCsimType);

    if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        /* ��ȡ���ļ�6f31 */
        TAF_MTA_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCsimCardStatus)
    {
        /* ��ȡ���ļ�6f31 */
        TAF_MTA_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID);
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq():Card State Error!");

        stMeifQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;

        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_MEID_QRY_CNF,
                         sizeof(stMeifQryCnf),
                         (VOS_UINT8*)&stMeifQryCnf);

        return;
    }

    /* ������ʱ��������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UIMID_READ_CNF, TI_TAF_MTA_WAIT_UIMID_READ_CNF_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF,
                                    (VOS_UINT8*)&(pstQryReq->stAppCtrl),
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndReadUsimmFileReq
 ��������  : MTA���Ͷ�������
 �������  : USIMM_CARDAPP_ENUM_UINT32           ulEventType
             USIMM_DEF_FILEID_ENUM_UINT32        enFileId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_SndReadUsimmFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp,
    VOS_UINT16                          enFileId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      enCardApp,
                                      enFileId,
                                      0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(UEPS_PID_MTA, 0, &stGetFileInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRcvUsimGetFileRsp
 ��������  : �յ���ȡUIM_ID�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : z00316370
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRcvUsimGetFileRsp(
    VOS_VOID                           *pMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_MEID_QRY_CNF_STRU            stMeifQryCnf;

    PS_MEM_SET(&stMeifQryCnf, 0x0, sizeof(stMeifQryCnf));

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UIMID_READ_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRcvUsimGetFileRsp: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRcvUsimGetFileRsp: get command buffer failed!");
        return;
    }

    pstUsimmReadCnfMsg = (USIMM_READFILE_CNF_STRU*)pMsg;

    TAF_MTA_RcvUsimmReadUimidFileCnf(pstUsimmReadCnfMsg, stMeifQryCnf.aucEFRUIMID);

    /* ����Ϊ0����ʾUIMID��Ч */
    if (0 == stMeifQryCnf.aucEFRUIMID[0])
    {
        stMeifQryCnf.enResult = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMeifQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MEID_QRY_CNF,
                     sizeof(stMeifQryCnf),
                     (VOS_UINT8*)&stMeifQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvUsimmReadUimidFileCnf
 ��������  : ����UIM_ID�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : z00316370
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID  TAF_MTA_RcvUsimmReadUimidFileCnf(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg,
    VOS_UINT8                          *paucEFRUIMID
)
{
    VOS_UINT32                          enEfId;

    PS_MEM_SET(paucEFRUIMID, 0xff, sizeof(VOS_UINT8) * MTA_AT_EFRUIMID_OCTET_LEN_EIGHT);

    if (VOS_OK != USIMM_ChangePathToDefFileID(pstUsimmReadCnfMsg->stCmdResult.enApptype,
                                              pstUsimmReadCnfMsg->stFilePath.ulPathLen,
                                              pstUsimmReadCnfMsg->stFilePath.acPath,
                                              &enEfId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    /* the EFRUIMID may have 5 or 8 bytes */
    if ((MTA_AT_EFRUIMID_OCTET_LEN_EIGHT != pstUsimmReadCnfMsg->usEfLen)
     && (MTA_AT_EFRUIMID_OCTET_LEN_FIVE  != pstUsimmReadCnfMsg->usEfLen))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID length FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    PS_MEM_CPY(paucEFRUIMID,
               pstUsimmReadCnfMsg->aucEf,
               pstUsimmReadCnfMsg->usEfLen);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitUIMIDReadExpired
 ��������  : ��ȡUIM_ID��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : z00316370
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitUIMIDReadExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_MEID_QRY_CNF_STRU            stMeifQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitUIMIDReadExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMeifQryCnf, 0x0, sizeof(stMeifQryCnf));

    stMeifQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MEID_QRY_CNF,
                     sizeof(stMeifQryCnf),
                     (VOS_UINT8*)&stMeifQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

