
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallEccCipher.h
  �� �� ��   : ����
  ��    ��   : c00177591
  ��������   : 2015��10��22��
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallEccCipher.h"
#include "TafXCallSndApp.h"
#include "v_timer.h"
#include "TafXCallCtx.h"
#include "TafXCallProcEccSrv.h"
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#include "SMAlgorithm.h"
#include "TrueRandom.h"
#endif

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_ECC_CIPHER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherEccInit
 ��������  : ECC������ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_CipherEccInit(VOS_VOID)
{
    ECC_Init();
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherInitVoice
 ��������  : ������ʼ������
 �������  : ��
 �������  : pucKs     --  ��ԿKS
             ulCallDir --  ���з��� VOS_TRUE Ϊ���У�VOS_FALSE Ϊ���С�
 �� �� ֵ  : VOS_TRUE -- ������ʼ���ɹ���VOS_FLASE -- ������ʼ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherInitVoice(
    VOS_UINT8                          *pucKs,
    VOS_UINT32                          ulCallDir
)
{
    if (0 == init_voice(pucKs, ulCallDir))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherGenTmpKey
 ��������  : ������ʱ��Կ��
 �������  : ��
 �������  : pstTmpPubKey  --  ��ʱ��Կ
             pstTmpPrivKey --  ��ʱ˽Կ
 �� �� ֵ  : VOS_TRUE -- ���ɳɹ���VOS_FLASE -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherGenTmpKey(
    TAF_XCALL_KMC_PUB_KEY_STRU         *pstTmpPubKey,
    TAF_XCALL_KMC_PRIV_KEY_STRU        *pstTmpPrivKey
)
{
    VOS_INT32                                               lRet;
    VOS_UINT32                                              ulPreSlice;
    VOS_INT8                                                acLogAscii[TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN];
    VOS_INT8                                                acLogBuf[TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN];
    VOS_INT32                                               lLength;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;
#ifdef DMT
    VOS_UINT8                                               aucPrivKey[] = {0x15, 0xDD, 0x68, 0x6A, 0x59, 0x9B, 0xB5, 0x84, 0x52, 0xA5,
                                                                            0x55, 0x7B, 0xD1, 0xB0, 0x58, 0x99, 0x13, 0xD3, 0x9F, 0x0B,
                                                                            0x68, 0x60, 0xB5, 0xF6};
    VOS_UINT8                                               aucPubKey[]  = {0x62, 0xD7, 0x5B, 0x7B, 0x5D, 0xAC, 0x8C, 0x2E, 0x0C, 0xFE,
                                                                            0xA3, 0xC4, 0xBE, 0xFF, 0x88, 0x53, 0xAB, 0x53, 0x25, 0x67,
                                                                            0x66, 0x3B, 0xE3, 0x2A, 0xA3, 0x4A, 0x3F, 0x44, 0xFE, 0x06,
                                                                            0xBB, 0x5A, 0xF2, 0x4E, 0x49, 0x59, 0x39, 0xC2, 0xE8, 0x10,
                                                                            0x4B, 0x8D, 0x89, 0xD2, 0x25, 0x1A, 0x8C, 0x92};

#endif


    enTestMode = TAF_XCALL_GetVoiceEncryptTestMode();

    if (TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE == enTestMode)
    {
#ifdef DMT
        PS_MEM_CPY(&pstTmpPrivKey->aucKey[0], aucPrivKey, sizeof(aucPrivKey));

        PS_MEM_CPY(&pstTmpPubKey->aucKey[0],  aucPubKey,  sizeof(aucPubKey));

        lRet = TAF_XCALL_ECC_CIPHER_OK;
#else
        lRet = ecc192_genkey(pstTmpPrivKey->aucKey, pstTmpPubKey->aucKey);
#endif
    }
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    else
    {
        ulPreSlice = VOS_GetSlice();

#ifdef DMT
        PS_MEM_CPY(&pstTmpPrivKey->aucKey[0], aucPrivKey, sizeof(aucPrivKey));

        PS_MEM_CPY(&pstTmpPubKey->aucKey[0],  aucPubKey,  sizeof(aucPubKey));

        lRet = TAF_XCALL_ECC_CIPHER_OK;
#else
        lRet = ecc192_genkey(pstTmpPrivKey->aucKey, pstTmpPubKey->aucKey);
#endif

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                     sizeof(acLogBuf),
                                     "ecc192_genkey execute time:%.3f",
                                     TAF_XCALL_CipherGetInterValSecond(ulPreSlice, VOS_GetSlice()));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                     sizeof(acLogBuf),
                                     "ecc192_genkey\nPrivacy.Key = %s\n",
                                     TAF_XCALL_CipherHex2Ascii(pstTmpPrivKey->aucKey, TAF_XCALL_ECC_PRIVAE_KEY_LEN, acLogAscii, sizeof(acLogAscii)));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                      (VOS_UINT32)(sizeof(acLogBuf) - lLength),
                                      "Public.Key = %s\n",
                                      TAF_XCALL_CipherHex2Ascii(pstTmpPubKey->aucKey, TAF_XCALL_ECC_PUBLIC_KEY_LEN, acLogAscii, sizeof(acLogAscii)));
        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);
    }
#endif
    if (TAF_XCALL_ECC_CIPHER_OK == lRet)
    {
        pstTmpPubKey->ucKeyLen = TAF_XCALL_ECC_PUBLIC_KEY_LEN;
        pstTmpPrivKey->ucKeyLen = TAF_XCALL_ECC_PRIVAE_KEY_LEN;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherEncrypt
 ��������  :
 �������  : TAF_XCALL_CIPHER_ENCRYPTION_STRU -- �ӽ������ݼ���Կ��Ϣ
 �������  :

 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherEncrypt(
    TAF_XCALL_CIPHER_ENCRYPTION_STRU    *pstEncryption
)
{
    VOS_INT32                                               lEncrptLen;
    VOS_UINT32                                              ulPreSlice;
    VOS_INT8                                                acLogAscii[TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN];
    VOS_INT8                                                acLogBuf[TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN];
    VOS_INT32                                               lLength;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                          stPlainTextInfo;
#endif

    enTestMode= TAF_XCALL_GetVoiceEncryptTestMode();

    if (TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE == enTestMode)
    {
        lEncrptLen = ecc192_encrypt(pstEncryption->pucCipherData,
                                    pstEncryption->ucCipherDataLen,
                                    pstEncryption->aucPlainData,
                                    pstEncryption->ucPlainDataLen,
                                    pstEncryption->aucPubKey);
    }
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    else
    {
        /* �ڵ��ü���֮ǰ���������ģ������ڼ��ܺ������ú��������ݱ��ƻ� */
        PS_MEM_SET(&stPlainTextInfo, 0, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));
        stPlainTextInfo.ucNumLen = (VOS_UINT8)TAF_XCALL_MIN(pstEncryption->ucPlainDataLen, TAF_XCALL_IDENTITY_COMBINE_MAX_LEN);
        PS_MEM_CPY(&stPlainTextInfo.aucContent[0], &pstEncryption->aucPlainData[0], stPlainTextInfo.ucNumLen);

        ulPreSlice = VOS_GetSlice();
        lEncrptLen = ecc192_encrypt(pstEncryption->pucCipherData,
                                    pstEncryption->ucCipherDataLen,
                                    pstEncryption->aucPlainData,
                                    pstEncryption->ucPlainDataLen,
                                    pstEncryption->aucPubKey);

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                     sizeof(acLogBuf),
                                     "ecc192_encrypt execute time:%.3f",
                                     TAF_XCALL_CipherGetInterValSecond(ulPreSlice, VOS_GetSlice()));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);

        if (lEncrptLen > 0)
        {
            lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                         sizeof(acLogBuf),
                                         "ecc192_encrypt\npin  = %s\n",
                                         TAF_XCALL_CipherHex2Ascii(stPlainTextInfo.aucContent, stPlainTextInfo.ucNumLen, acLogAscii, sizeof(acLogAscii)));

            if (lLength <= 0)
            {
                return VOS_FALSE;
            }

            lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                          (VOS_UINT32)(sizeof(acLogBuf) - lLength),
                                          "pout  = %s\n",
                                          TAF_XCALL_CipherHex2Ascii(pstEncryption->pucCipherData, (VOS_UINT32)lEncrptLen, acLogAscii, sizeof(acLogAscii)));

            if (lLength <= 0)
            {
                return VOS_FALSE;
            }

            TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);
        }
    }
#endif
    if (lEncrptLen > 0)
    {
        pstEncryption->ucEncrptionLen = (VOS_UINT16)lEncrptLen;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherDecrypt
 ��������  :
 �������  : TAF_XCALL_CIPHER_ENCRYPTION_STRU -- �ӽ������ݼ���Կ��Ϣ
 �������  :

 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherDecrypt(
    TAF_XCALL_CIPHER_DECRYPTION_STRU    *pstEncryption
)
{
    VOS_INT32                                               lEncrptLen;
    VOS_UINT32                                              ulPreSlice;
    VOS_INT8                                                acLogAscii[TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN];
    VOS_INT8                                                acLogBuf[TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN];
    VOS_INT32                                               lLength;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    TAF_XCALL_KMC_PRIV_KEY_STRU                             stTmpPrivKey;
    TAF_XCALL_KMC_MSG_CIPHER_STRU                           stCipher;
#endif


    enTestMode= TAF_XCALL_GetVoiceEncryptTestMode();

    if (TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE == enTestMode)
    {
        lEncrptLen = ecc192_decrypt(pstEncryption->pucPlainData,
                                    pstEncryption->ucPlainDataLen,
                                    pstEncryption->aucCipherData,
                                    pstEncryption->ucCipherDataLen,
                                    pstEncryption->aucCipherKey);
    }
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    else
    {
        /* �ڵ��ý���֮ǰ����ʱ˽Կ�������ڼ��ܺ������ú����ݱ��ƻ� */
        PS_MEM_SET(&stTmpPrivKey, 0, sizeof(TAF_XCALL_KMC_PRIV_KEY_STRU));
        stTmpPrivKey.ucKeyLen = (VOS_UINT8)TAF_XCALL_MIN(pstEncryption->ucCipherKeyLen, TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN);
        PS_MEM_CPY(&stTmpPrivKey.aucKey[0], &pstEncryption->aucCipherKey[0], stTmpPrivKey.ucKeyLen);

        /* �ڵ��ý���֮ǰ���������ģ������ڼ��ܺ������ú����ݱ��ƻ� */
        PS_MEM_SET(&stCipher, 0, sizeof(TAF_XCALL_KMC_MSG_CIPHER_STRU));
        stCipher.usCipherLen = (VOS_UINT8)TAF_XCALL_MIN(pstEncryption->ucCipherDataLen, TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN);
        PS_MEM_CPY(&stCipher.aucCipher[0], &pstEncryption->aucCipherData[0], stCipher.usCipherLen);

        ulPreSlice = VOS_GetSlice();
        lEncrptLen = ecc192_decrypt(pstEncryption->pucPlainData,
                                    pstEncryption->ucPlainDataLen,
                                    pstEncryption->aucCipherData,
                                    pstEncryption->ucCipherDataLen,
                                    pstEncryption->aucCipherKey);

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                     sizeof(acLogBuf),
                                     "ecc192_decrypt execute time:%.3f",
                                     TAF_XCALL_CipherGetInterValSecond(ulPreSlice, VOS_GetSlice()));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);

        if (lEncrptLen > 0)
        {
            lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                         sizeof(acLogBuf),
                                         "ecc192_decrypt\npin  = %s\n",
                                         TAF_XCALL_CipherHex2Ascii(&(stCipher.aucCipher[0]), stCipher.usCipherLen, acLogAscii, sizeof(acLogAscii)));

            if (lLength <= 0)
            {
                return VOS_FALSE;
            }

            lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                          (VOS_UINT32)(sizeof(acLogBuf) - lLength),
                                          "Privacy.Key = %s\n",
                                          TAF_XCALL_CipherHex2Ascii(&(stTmpPrivKey.aucKey[0]), stTmpPrivKey.ucKeyLen, acLogAscii, sizeof(acLogAscii)));
            if (lLength <= 0)
            {
                return VOS_FALSE;
            }

            lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                          (VOS_UINT32)(sizeof(acLogBuf) - lLength),
                                          "pout  = %s\n",
                                          TAF_XCALL_CipherHex2Ascii(pstEncryption->pucPlainData, (VOS_UINT32)lEncrptLen, acLogAscii, sizeof(acLogAscii)));
            if (lLength <= 0)
            {
                return VOS_FALSE;
            }

            TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);
        }
    }
#endif

    if (lEncrptLen > 0)
    {
        pstEncryption->ucEncrptionLen = (VOS_UINT8)lEncrptLen;
        return VOS_TRUE;
    }

    return  VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherVerify
 ��������  :
 �������  : TAF_XCALL_CIPHER_ENCRYPTION_STRU --  ǩ�����ݼ���Կ��Ϣ
 �������  :

 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherVerify(
    TAF_XCALL_CIPHER_VERIFY_STRU        *pstVerifyData
)
{
    VOS_INT32                                               lRet;
    VOS_UINT32                                              ulPreSlice;
    VOS_INT8                                                acLogAscii[TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN];
    VOS_INT8                                                acLogBuf[TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN];
    VOS_INT32                                               lLength;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    TAF_XCALL_KMC_PUB_KEY_STRU                              stPubKey;
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;
    VOS_UINT8                                               ucSignDataLen;
    VOS_UINT8                                               auSigntureData[TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN];
#endif

    enTestMode= TAF_XCALL_GetVoiceEncryptTestMode();

    if (TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE == enTestMode)
    {
        lRet = ecc192_verify(pstVerifyData->aucPubKey,
                             pstVerifyData->auSigntureData,
                             pstVerifyData->ucSigntureDataLen,
                             pstVerifyData->auSigntureInfo,
                             pstVerifyData->ucSigntureInfoLen);
    }
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    else
    {
        /* �ڵ���ǩ����֤֮ǰ�����ݹ�Կ��ǩ����Ϣ��ǩ�����ݣ�������ǩ����֤�������ú����ݱ��ƻ� */
        PS_MEM_SET(&stPubKey, 0, sizeof(TAF_XCALL_KMC_PUB_KEY_STRU));
        stPubKey.ucKeyLen = (VOS_UINT8)TAF_XCALL_MIN(pstVerifyData->ucPubKeyLen, TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);
        PS_MEM_CPY(&stPubKey.aucKey[0], &pstVerifyData->aucPubKey[0], stPubKey.ucKeyLen);

        PS_MEM_SET(&stSignInfo, 0, sizeof(TAF_XCALL_KMC_MSG_SIGN_INFO_STRU));
        stSignInfo.ucSignInfoLen = (VOS_UINT8)TAF_XCALL_MIN(pstVerifyData->ucSigntureInfoLen, TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN);
        PS_MEM_CPY(&stSignInfo.aucSignInfo[0], &pstVerifyData->auSigntureInfo[0], pstVerifyData->ucSigntureInfoLen);

        PS_MEM_SET(auSigntureData, 0, sizeof(VOS_UINT8) * TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN);
        ucSignDataLen = (VOS_UINT8)TAF_XCALL_MIN(pstVerifyData->ucSigntureDataLen, TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN);
        PS_MEM_CPY(&auSigntureData[0], &pstVerifyData->auSigntureData[0], ucSignDataLen);

        ulPreSlice = VOS_GetSlice();
        lRet = ecc192_verify(pstVerifyData->aucPubKey,
                             pstVerifyData->auSigntureData,
                             pstVerifyData->ucSigntureDataLen,
                             pstVerifyData->auSigntureInfo,
                             pstVerifyData->ucSigntureInfoLen);

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                      sizeof(acLogBuf),
                                      "ecc192_verify execute time:%.3f",
                                      TAF_XCALL_CipherGetInterValSecond(ulPreSlice, VOS_GetSlice()));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);

        lLength = TAF_XCALL_GET_DATA((VOS_CHAR *)acLogBuf,
                                     TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN,
                                     "ecc192_verify\nKMCPubKey   = %s\n",
                                     TAF_XCALL_CipherHex2Ascii(&(stPubKey.aucKey[0]), stPubKey.ucKeyLen, acLogAscii, sizeof(acLogAscii)));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                      (VOS_UINT32)(TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN - lLength),
                                      "pin = %s\n",
                                      TAF_XCALL_CipherHex2Ascii(&(auSigntureData[0]), ucSignDataLen, acLogAscii, sizeof(acLogAscii)));

        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        lLength += TAF_XCALL_GET_DATA((VOS_CHAR *)(acLogBuf + lLength),
                                      (VOS_UINT32)(TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN - lLength),
                                      "Sign  = %s\n",
                                      TAF_XCALL_CipherHex2Ascii(&(stSignInfo.aucSignInfo[0]), stSignInfo.ucSignInfoLen, acLogAscii, sizeof(acLogAscii)));
        if (lLength <= 0)
        {
            return VOS_FALSE;
        }

        TAF_XCALL_SndEncryptedVoiceDataInd(acLogBuf, (VOS_UINT32)lLength);
    }
#endif

    if (TAF_XCALL_ECC_VERIFY_OK != lRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherGetRandom
 ��������  :
 �������  : ulRandomLen --  ������������
             pucRandom -- ������������
 �������  :

 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_CipherGetRandom(
    VOS_UINT32                          ulRandomLen,
    VOS_UINT8                          *pucRandom
)
{
#ifdef DMT
    VOS_UINT8                           aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
                                                                                            0x0F, 0xED, 0xCB, 0xA9, 0x87, 0x65, 0x43, 0x21};

    PS_MEM_CPY(pucRandom, aucRandomData, sizeof(aucRandomData));
#else
    VOS_INT32 lRet;

    lRet = TrueRandom(pucRandom,(VOS_INT32)ulRandomLen);

    if (ulRandomLen != lRet)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherGetInterValSecond
 ��������  :
 �������  : ulStartSlice   -- �����slice
             ulCurSlice     -- ��ǰslice
 �������  :

 �� �� ֵ  : VOS_FLOAT      -- ���ؼ��s
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_FLOAT TAF_XCALL_CipherGetInterValSecond(
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulCurSlice
)
{
    VOS_UINT32                          ulRunSliceNum;

    if (ulCurSlice < ulStartSlice)/* ���Ƿ�ת���� */
    {
        ulRunSliceNum = TAF_XCALL_ECC_MAX_SLICE_VALUE - ulStartSlice + ulCurSlice + 1;
    }
    else
    {
        ulRunSliceNum = ulCurSlice - ulStartSlice;
    }

    return (VOS_FLOAT)((ulRunSliceNum*1.0f)/VOS_GetSliceUnit());
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_CipherGetInterValSecond
 ��������  :
 �������  : pucInput    -- ��������ָ��
             ulInputLen  -- �������ݳ���
             pucOutput   -- �����������
             ulOutptuLen -- �������
 �������  :

 �� �� ֵ  : VOS_UINT8   -- �����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_INT8 *TAF_XCALL_CipherHex2Ascii(
    VOS_UINT8                          *pucInput,
    VOS_UINT32                          ulInputLen,
    VOS_INT8                           *pscOutput,
    VOS_UINT32                          ulOutptuLen
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_INT8                           *pscTmp = VOS_NULL_PTR;
    VOS_INT8                            aucNibble[TAF_XCALL_ECC_NIBBLE_NUM_OF_CHAR];

    if (pucInput == NULL
        || pscOutput == NULL
        || ulInputLen*2 > ulOutptuLen)
    {
        return VOS_NULL_PTR;
    }

    pscTmp = pscOutput;
    for (i = 0; i < ulInputLen; i++)
    {
        aucNibble[0] = (pucInput[i] & 0xF0) >> 4;
        aucNibble[1] = pucInput[i] & 0x0F;

        for (j = 0; j < TAF_XCALL_ECC_NIBBLE_NUM_OF_CHAR; j++)
        {
            if (aucNibble[j] < TAF_XCALL_ECC_TEN)
            {
                aucNibble[j] += TAF_XCALL_ECC_ASCII_OF_ZERO;
            }
            else
            {
                aucNibble[j] += (TAF_XCALL_ECC_ASCII_OF_LETTER - TAF_XCALL_ECC_TEN);
            }

            *pscTmp++ = aucNibble[j];
        }
    }

    *pscTmp = '\0';

    return pscOutput;
}
#endif

#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT*/
#endif /*FEATURE_UE_MODE_CDMA*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
