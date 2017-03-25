/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_sha256.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2015��11��10��
  ����޸�   :
  ��������   : pppc_sha256.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��10��
    ��    ��   : 123
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PPPC_SHA256_H__
#define __PPPC_SHA256_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "PsLib.h"
#include "PsTypeDef.h"
#include "ppp_dbug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PPPC_SHA256_PARA_MAX_NUM        (12)                                    /* SHA256������������� */

/*****************************************************************************
                SHA256�㷨�궨��  FIPS180-2
*****************************************************************************/

#define PPPC_SHA256_BLOCK_SIZE          (64)                                    /* SHA256������С */
#define PPPC_SHA256_MAC_LEN             (32)                                    /* SHA256����ֵ���� */

#define PPPC_SHA256_RORc(x, y) \
    ( ((((unsigned long) (x) & 0xFFFFFFFFUL) >> (unsigned long) ((y) & 31)) | \
       ((unsigned long) (x) << (unsigned long) (32 - ((y) & 31)))) & 0xFFFFFFFFUL)
#define PPPC_SHA256_Ch(x,y,z)       (z ^ (x & (y ^ z)))
#define PPPC_SHA256_Maj(x,y,z)      (((x | y) & z) | (x & y))
#define PPPC_SHA256_S(x, n)         PPPC_SHA256_RORc((x), (n))
#define PPPC_SHA256_R(x, n)         (((x)&0xFFFFFFFFUL)>>(n))
#define PPPC_SHA256_Sigma0(x)       (PPPC_SHA256_S(x, 2) ^ PPPC_SHA256_S(x, 13) ^ PPPC_SHA256_S(x, 22))
#define PPPC_SHA256_Sigma1(x)       (PPPC_SHA256_S(x, 6) ^ PPPC_SHA256_S(x, 11) ^ PPPC_SHA256_S(x, 25))
#define PPPC_SHA256_Gamma0(x)       (PPPC_SHA256_S(x, 7) ^ PPPC_SHA256_S(x, 18) ^ PPPC_SHA256_R(x, 3))
#define PPPC_SHA256_Gamma1(x)       (PPPC_SHA256_S(x, 17) ^ PPPC_SHA256_S(x, 19) ^ PPPC_SHA256_R(x, 10))
/* ����Kֵ  ��K_LOW + K_HIGH�õ�K */
#define PPPC_GET_RND_K(Index)        ((PPPC_SHA256_K_HIGH[(Index)]) + (PPPC_SHA256_K_LOW[(Index)]))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/* the K array Kʵ����K_LOW + K_HIGH�õ��������뿪Դ������ͬ */
static const VOS_UINT32 PPPC_SHA256_K_LOW[64] =
{
    0x00002f98UL, 0x00004491UL, 0x0000fbcfUL, 0x0000dba5UL, 0x0000c25bUL,
    0x000011f1UL, 0x000082a4UL, 0x00005ed5UL, 0x0000aa98UL, 0x00005b01UL,
    0x000085beUL, 0x00007dc3UL, 0x00005d74UL, 0x0000b1feUL, 0x000006a7UL,
    0x0000f174UL, 0x000069c1UL, 0x00004786UL, 0x00009dc6UL, 0x0000a1ccUL,
    0x00002c6fUL, 0x000084aaUL, 0x0000a9dcUL, 0x000088daUL, 0x00005152UL,
    0x0000c66dUL, 0x000027c8UL, 0x00007fc7UL, 0x00000bf3UL, 0x00009147UL,
    0x00006351UL, 0x00002967UL, 0x00000a85UL, 0x00002138UL, 0x00006dfcUL,
    0x00000d13UL, 0x00007354UL, 0x00000abbUL, 0x0000c92eUL, 0x00002c85UL,
    0x0000e8a1UL, 0x0000664bUL, 0x00008b70UL, 0x000051a3UL, 0x0000e819UL,
    0x00000624UL, 0x00003585UL, 0x0000a070UL, 0x0000c116UL, 0x00006c08UL,
    0x0000774cUL, 0x0000bcb5UL, 0x00000cb3UL, 0x0000aa4aUL, 0x0000ca4fUL,
    0x00006ff3UL, 0x000082eeUL, 0x0000636fUL, 0x00007814UL, 0x00000208UL,
    0x0000fffaUL, 0x00006cebUL, 0x0000a3f7UL, 0x000078f2UL
};

static const VOS_UINT32 PPPC_SHA256_K_HIGH[64] =
{
    0x428a0000UL, 0x71370000UL, 0xb5c00000UL, 0xe9b50000UL, 0x39560000UL,
    0x59f10000UL, 0x923f0000UL, 0xab1c0000UL, 0xd8070000UL, 0x12830000UL,
    0x24310000UL, 0x550c0000UL, 0x72be0000UL, 0x80de0000UL, 0x9bdc0000UL,
    0xc19b0000UL, 0xe49b0000UL, 0xefbe0000UL, 0x0fc10000UL, 0x240c0000UL,
    0x2de90000UL, 0x4a740000UL, 0x5cb00000UL, 0x76f90000UL, 0x983e0000UL,
    0xa8310000UL, 0xb0030000UL, 0xbf590000UL, 0xc6e00000UL, 0xd5a70000UL,
    0x06ca0000UL, 0x14290000UL, 0x27b70000UL, 0x2e1b0000UL, 0x4d2c0000UL,
    0x53380000UL, 0x650a0000UL, 0x766a0000UL, 0x81c20000UL, 0x92720000UL,
    0xa2bf0000UL, 0xa81a0000UL, 0xc24b0000UL, 0xc76c0000UL, 0xd1920000UL,
    0xd6990000UL, 0xf40e0000UL, 0x106a0000UL, 0x19a40000UL, 0x1e370000UL,
    0x27480000UL, 0x34b00000UL, 0x391c0000UL, 0x4ed80000UL, 0x5b9c0000UL,
    0x682e0000UL, 0x748f0000UL, 0x78a50000UL, 0x84c80000UL, 0x8cc70000UL,
    0x90be0000UL, 0xa4500000UL, 0xbef90000UL, 0xc6710000UL
};



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
        SHA256 �㷨�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT64                          ullLength;
    VOS_UINT32                          aulState[8];
    VOS_UINT32                          ulCurLen;
    VOS_UINT8                           aucBuf[PPPC_SHA256_BLOCK_SIZE];
    VOS_UINT8                           aucRsv[4];
}PPPC_SHA256_STATE_STRU;

/*****************************************************************************
        SHA256�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;                                  /* ���������� */
    VOS_UINT8                           aucReverse[3];
    VOS_UINT8                          *apucAdrr[PPPC_SHA256_PARA_MAX_NUM];     /* ������ַ */
    VOS_UINT32                          aulLen[PPPC_SHA256_PARA_MAX_NUM];       /* �������� */
}PPPC_SHA256_PARA_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_UINT32 PPPC_EAP_PRF_PRIME
(
   VOS_UINT8                          *pucKey,
   PPPC_SHA256_PARA_STRU              *pstPara,
   VOS_UINT8                          *pucMK,
   VOS_UINT8                           ucMKLen
);
VOS_UINT32 PPPC_HMAC_SHA256
(
   VOS_UINT8                          *pucKey,
   VOS_UINT8                           ucKeyLen,
   PPPC_SHA256_PARA_STRU              *pstPara,
   VOS_UINT8                          *pucMac
);
VOS_UINT32 PPPC_SHA256
(
   PPPC_SHA256_PARA_STRU               *pstPara,
    VOS_UINT8                          *pucMac
);



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

#endif /* end of pppc_sha256.h */

