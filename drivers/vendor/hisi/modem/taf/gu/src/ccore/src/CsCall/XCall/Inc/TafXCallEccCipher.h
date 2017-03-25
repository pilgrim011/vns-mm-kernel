
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallEccCipher.h
  �� �� ��   : ����
  ��    ��   : c00177591
  ��������   : 2015��10��22��
  ��������   : TafXCallEccCipher.c��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00177591
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_ECC_CIPHER_H__
#define __TAF_X_CALL_ECC_CIPHER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafXCallKmcCommType.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_ECC_CIPHER_OK                   (0)
#define TAF_XCALL_ECC_VERIFY_OK                   (1)

#define TAF_XCALL_ECC_MAX_SLICE_VALUE                       (0xFFFFFFFF)


#define TAF_XCALL_ECC_PUBLIC_KEY_LEN                        (48)
#define TAF_XCALL_ECC_PRIVAE_KEY_LEN                        (24)
#define TAF_XCALL_ECC_NIBBLE_NUM_OF_CHAR                    (2)
#define TAF_XCALL_ECC_TEN                                   (10)
#define TAF_XCALL_ECC_ASCII_OF_ZERO                         ('0')
#define TAF_XCALL_ECC_ASCII_OF_LETTER                       ('A')
#define TAF_XCALL_ECC_MAX_ASCII_OUTPUT_LEN                  (256)
#define TAF_XCALL_ECC_MAX_LOG_OUTPUT_LEN                    (512)
#define TAF_XCALL_GET_DATA                                  VOS_nsprintf

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
�ṹ��      : TAF_XCALL_CIPHER_ENCRYPTION_STRU
�ṹ˵��    : �ӽ������ݼ���Կ��Ϣ
  1.��    ��   : 2015��10��23��
    ��    ��   : c00177591
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPubKeyLen;        /*��Կ����*/
    VOS_UINT8                           ucPlainDataLen;     /*�������ݳ���*/
    VOS_UINT8                           ucCipherDataLen;    /*�������ݳ���*/
    VOS_UINT8                           aucReserved1[1];

    VOS_UINT16                          ucEncrptionLen;     /*�������ݳ���*/
    VOS_UINT8                           aucReserved2[2];

    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];     /*��Կ*/
    VOS_UINT8                           aucPlainData[TAF_XCALL_MAX_PLAIN_DATA_LEN];           /*��������*/
    VOS_UINT8                          *pucCipherData;                                        /*��������*/
}TAF_XCALL_CIPHER_ENCRYPTION_STRU;

/*****************************************************************************
�ṹ��      : TAF_XCALL_CIPHER_ENCRYPTION_STRU
�ṹ˵��    : �ӽ������ݼ���Կ��Ϣ
  1.��    ��   : 2015��10��23��
    ��    ��   : c00177591
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCipherKeyLen;     /*��Կ����*/
    VOS_UINT8                           ucPlainDataLen;     /*�������ݳ���*/
    VOS_UINT8                           ucCipherDataLen;    /*�������ݳ���*/
    VOS_UINT8                           ucEncrptionLen;     /*�������ݳ���*/

    VOS_UINT8                           aucCipherKey[TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN]; /*��Կ*/
    VOS_UINT8                           aucCipherData[TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN];      /*��������*/
    VOS_UINT8                          *pucPlainData;                                           /*��������*/
}TAF_XCALL_CIPHER_DECRYPTION_STRU;

/*****************************************************************************
�ṹ��      : TAF_XCALL_CIPHER_VERIFY_STRU
�ṹ˵��    : ǩ�����ݼ���Կ��Ϣ
  1.��    ��   : 2015��10��23��
    ��    ��   : c00177591
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPubKeyLen;        /*��Կ����*/
    VOS_UINT8                           ucSigntureDataLen;  /*ǩ������*/
    VOS_UINT8                           ucSigntureInfoLen;  /*ǩ����Ϣ����*/

    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];        /*��Կ*/
    VOS_UINT8                           auSigntureData[TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN];     /*ǩ��*/
    VOS_UINT8                           auSigntureInfo[TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN];     /*ǩ����Ϣ*/
}TAF_XCALL_CIPHER_VERIFY_STRU;

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
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT32 TAF_XCALL_CipherInitVoice(
    VOS_UINT8                          *pucKs,
    VOS_UINT32                          ulCallDir
);

VOS_VOID TAF_XCALL_CipherEccInit(VOS_VOID);

VOS_UINT32 TAF_XCALL_CipherGenTmpKey(
    TAF_XCALL_KMC_PUB_KEY_STRU         *pstTmpPubKey,
    TAF_XCALL_KMC_PRIV_KEY_STRU        *pstTmpPrivKey
);

VOS_UINT32 TAF_XCALL_CipherEncrypt(
    TAF_XCALL_CIPHER_ENCRYPTION_STRU    *pstEncryptionDta
);

VOS_UINT32 TAF_XCALL_CipherDecrypt(
    TAF_XCALL_CIPHER_DECRYPTION_STRU    *pstEncryptionData
);

VOS_UINT32 TAF_XCALL_CipherVerify(
    TAF_XCALL_CIPHER_VERIFY_STRU        *pstVerifyData
);

VOS_UINT32 TAF_XCALL_CipherGetRandom(
    VOS_UINT32                          ulRandomLen,
    VOS_UINT8                          *pucRandom
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_FLOAT TAF_XCALL_CipherGetInterValSecond(
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulCurSlice
);

VOS_INT8 *TAF_XCALL_CipherHex2Ascii(
    VOS_UINT8                          *pucInput,
    VOS_UINT32                          ulInputLen,
    VOS_INT8                           *pscOutput,
    VOS_UINT32                          ulOutptuLen
);
#endif

#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT*/
#endif /*FEATURE_UE_MODE_CDMA*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __TAF_X_CALL_ECC_CIPHER_H__ */
