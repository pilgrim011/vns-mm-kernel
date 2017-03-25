/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_sha1.c
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2015��11��10��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��10��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "pppc_sha1.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_UTIL_SHA1_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */


/*****************************************************************************
 �� �� ��  : PPPC_SHA1_Init
 ��������  : ����SHA-1�㷨��ʼ������
 �������  : PPPC_HRPD_SHA1_STRU* pstSha1
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  PPPC_SHA1_Init(PPPC_HRPD_SHA1_STRU* pstSha1)
{
    /* SHA1 initialization constants */
    pstSha1->aulState[0] = 0x67452301;
    pstSha1->aulState[1] = 0xEFCDAB89;
    pstSha1->aulState[2] = 0x98BADCFE;
    pstSha1->aulState[3] = 0x10325476;
    pstSha1->aulState[4] = 0xC3D2E1F0;

    pstSha1->aulCount[0] = 0;
    pstSha1->aulCount[1] = 0;

    return ;
}

/*****************************************************************************
 �� �� ��  : PPPC_SHA1_Transform
 ��������  : SHA-1�㷨����
 �������  : VOS_UINT32 aulState[5]
             VOS_UINT8  aucBuf[64]
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SHA1_Transform(VOS_UINT32 aulState[5], VOS_UINT8 aucBuf[64])
{
    VOS_UINT32                              ulAlph;
    VOS_UINT32                              ulBeta;
    VOS_UINT32                              ulGamm;
    VOS_UINT32                              ulDelt;
    VOS_UINT32                              ulEpsi;
    VOS_CHAR64_TO_LONG16                   *pStr;
    static VOS_UINT8                        aucArray[64];


    pStr    = (VOS_CHAR64_TO_LONG16 *)aucArray;
    PS_MEM_CPY(pStr, aucBuf, 64);

    ulAlph  = aulState[0];
    ulBeta  = aulState[1];
    ulGamm  = aulState[2];
    ulDelt  = aulState[3];
    ulEpsi  = aulState[4];

    /*lint -save -e778*/
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi, 0);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt, 1);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm, 2);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta, 3);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph, 4);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi, 5);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt, 6);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm, 7);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta, 8);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph, 9);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,10);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,11);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,12);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,13);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,14);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,15);
    OPERA1(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,16);
    OPERA1(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,17);
    OPERA1(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,18);
    OPERA1(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,19);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,20);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,21);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,22);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,23);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,24);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,25);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,26);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,27);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,28);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,29);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,30);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,31);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,32);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,33);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,34);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,35);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,36);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,37);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,38);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,39);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,40);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,41);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,42);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,43);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,44);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,45);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,46);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,47);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,48);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,49);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,50);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,51);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,52);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,53);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,54);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,55);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,56);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,57);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,58);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,59);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,60);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,61);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,62);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,63);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,64);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,65);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,66);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,67);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,68);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,69);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,70);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,71);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,72);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,73);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,74);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,75);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,76);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,77);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,78);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,79);
    /*lint -restore*/

    aulState[0] += ulAlph;
    aulState[1] += ulBeta;
    aulState[2] += ulGamm;
    aulState[3] += ulDelt;
    aulState[4] += ulEpsi;

    return ;
}

/*****************************************************************************
 �� �� ��  : PPPC_SHA1_Update
 ��������  : SHA-1�㷨����
 �������  : PPPC_HRPD_SHA1_STRU    *pstSha1
             VOS_UINT8              *pData
             VOS_UINT32              ulLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SHA1_Update
(
    PPPC_HRPD_SHA1_STRU                *pstSha1,
    VOS_UINT8                          *pData,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndexI;
    VOS_UINT32                          ulIndexJ;

    ulIndexJ = pstSha1->aulCount[0];
    if ((pstSha1->aulCount[0] += ulLen << 3) < ulIndexJ)
    {
        pstSha1->aulCount[1] += (ulLen>>29) + 1;
    }

    ulIndexJ = (ulIndexJ >> 3) & 63;
    if ((ulIndexJ + ulLen) > 63)
    {
        ulIndexI = 64 - ulIndexJ;

        PS_MEM_CPY(&pstSha1->aucBuffer[ulIndexJ], pData, ulIndexI);

        PPPC_SHA1_Transform(pstSha1->aulState, pstSha1->aucBuffer);
        /*lint -e440*/
        for ( ; (ulIndexI + 63) < ulLen; ulIndexI += 64)
        {
            PPPC_SHA1_Transform(pstSha1->aulState, &pData[ulIndexI]);
        }
        /*lint +e440*/
        ulIndexJ = 0;
    }
    else
    {
        ulIndexI = 0;
    }

    PS_MEM_CPY(&pstSha1->aucBuffer[ulIndexJ], &pData[ulIndexI], ulLen - ulIndexI);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SHA1_Final
 ��������  : SHA-1�㷨����
 �������  : VOS_UINT8               aucDigest[20]
             PPPC_HRPD_SHA1_STRU    *pstSha1
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SHA1_Final
(
    VOS_UINT8                           aucDigest[20],
    PPPC_HRPD_SHA1_STRU                *pstSha1
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           aucFinalcount[8];

    for (ulIndex = 0; ulIndex < 8; ulIndex++)
    {
        /* Endian independent */
        aucFinalcount[ulIndex] =
            (VOS_UINT8)((pstSha1->aulCount[((ulIndex >= 4) ? 0 : 1)] >> ((3-(ulIndex & 3)) * 8) ) & 255);
    }

    PPPC_SHA1_Update(pstSha1, (VOS_UINT8 *)"\200", 1);

    while ((pstSha1->aulCount[0] & 504) != 448)
    {
        PPPC_SHA1_Update(pstSha1, (VOS_UINT8 *)"\0", 1);

        /*lint !e840*/
    }

    /* Should cause a SHA1Transform() */
    PPPC_SHA1_Update(pstSha1, aucFinalcount, 8);

    if (aucDigest)
    {
        for (ulIndex = 0; ulIndex < 20; ulIndex++)
        {
            aucDigest[ulIndex] = (VOS_UINT8)((pstSha1->aulState[ulIndex>>2] >> ((3-(ulIndex & 3)) * 8) ) & 255);
        }
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : PPPC_SHA1
 ��������  : SHA-1�㷨����
 �������  : stPara             Ҫ���ܵ�����
 �������  : pucMac             ���ܺ�Ľ��
 �� �� ֵ  : �ɹ� VOS_OK   ʧ�� VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_SHA1
(
    PPPC_SHA1_PARA_STRU                *pstPara,
    VOS_UINT8                          *pucMac
)
{
    PPPC_HRPD_SHA1_STRU                 stCtx;
    VOS_UINT8                           ucIndex;

    PPPC_SHA1_Init(&stCtx);
    for (ucIndex = 0; ucIndex < pstPara->ucNum; ucIndex++)
    {
        PPPC_SHA1_Update(&stCtx, pstPara->apucAdrr[ucIndex], pstPara->aulLen[ucIndex]);
    }
    PPPC_SHA1_Final(pucMac, &stCtx);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HMAC_SHA1
 ��������  : HMAC_SHA1�㷨����
 �������  : pucKey      ����ʹ�õ���ԿKey
             ucKeyLen    ��ԿKey����
             stPara      ��Ҫ���ܵ�����
 �������  : pucMac      ���ܵĽ��
 �� �� ֵ  : �ɹ�  VOS_OK    ʧ��  VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HMAC_SHA1
(
    VOS_UINT8                          *pucKey,
    VOS_UINT8                           ucKeyLen,
    PPPC_SHA1_PARA_STRU                *pstPara,
    VOS_UINT8                          *pucMac
)
{
    VOS_UINT8                           aucTempKey[PPPC_SHA1_MAC_LEN];
    VOS_UINT8                           aucKeyXorPad[PPPC_SHA1_BLOCK_SIZE];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucTempMac[PPPC_SHA1_MAC_LEN];
    PPPC_SHA1_PARA_STRU                 stTempPara;

    /*
       the HMAC_SHA1 transform looks like:

       SHA1(K XOR opad, SHA1(K XOR ipad, text))

       where K is an n byte key
       ipad is the byte 0x36 repeated 64 times
       opad is the byte 0x5c repeated 64 times
       and text is the data being protected
    */


    /* if key is longer than 64 bytes reset it to key = SHA1(key) */
    PS_MEM_SET(aucTempKey, 0x00, sizeof(aucTempKey));

    stTempPara.ucNum        = 1;
    stTempPara.apucAdrr[0]  = pucKey;
    stTempPara.aulLen[0]    = ucKeyLen;
    if (ucKeyLen > PPPC_SHA1_BLOCK_SIZE)
    {
        if (VOS_OK != PPPC_SHA1(&stTempPara, aucTempKey))
        {
            PPPC_WARNING_LOG("Error When run HMAC_SHA256 in SHA256!");
            return VOS_ERR;
        }
        pucKey   = aucTempKey;
        ucKeyLen = PPPC_SHA1_MAC_LEN;
    }

    /* XOR key with ipad values */
    PS_MEM_SET(aucKeyXorPad, 0x00, sizeof(aucKeyXorPad));

    PS_MEM_CPY(aucKeyXorPad, pucKey, ucKeyLen);

    for (ucIndex = 0; ucIndex < PPPC_SHA1_BLOCK_SIZE; ucIndex++)
    {
        aucKeyXorPad[ucIndex] ^= 0x36;
    }

    /* SHA1(K XOR ipad | text) */
    stTempPara.ucNum        = pstPara->ucNum + 1;
    stTempPara.apucAdrr[0]  = aucKeyXorPad;
    stTempPara.aulLen[0]    = PPPC_SHA1_BLOCK_SIZE;
    for (ucIndex = 0; ucIndex < pstPara->ucNum; ucIndex++)
    {
        stTempPara.apucAdrr[ucIndex + 1]    = pstPara->apucAdrr[ucIndex];
        stTempPara.aulLen[ucIndex + 1]      = pstPara->aulLen[ucIndex];
    }

    if (VOS_OK != PPPC_SHA1(&stTempPara, aucTempMac))
    {
        PPPC_WARNING_LOG("Error When sha1 in hmac!");
        return VOS_ERR;
    }

    /* XOR key with opad values */
    PS_MEM_SET(aucKeyXorPad, 0x00, sizeof(aucKeyXorPad));

    PS_MEM_CPY(aucKeyXorPad, pucKey, ucKeyLen);

    for (ucIndex = 0; ucIndex < PPPC_SHA1_BLOCK_SIZE; ucIndex++)
    {
        aucKeyXorPad[ucIndex] ^= 0x5c;
    }

    /*  SHA1(K XOR opad | aucTempMac) */

    stTempPara.ucNum        = 2;
    stTempPara.apucAdrr[0]  = aucKeyXorPad;
    stTempPara.aulLen[0]    = PPPC_SHA1_BLOCK_SIZE;
    stTempPara.apucAdrr[1]  = aucTempMac;
    stTempPara.aulLen[1]    = PPPC_SHA1_MAC_LEN;

    if (VOS_OK != PPPC_SHA1(&stTempPara, pucMac))
    {
        PPPC_WARNING_LOG("Error When sha256 in hmac!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPPC_SHA1_GET_BE32
 ��������  : ��С��ת������
 �������  : ulVal      Ҫת����ֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ת�����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
static VOS_UINT32 PPPC_SHA1_GET_BE32(VOS_UINT32 ulVal)
{
    return ((ulVal & 0xff) << 24) | ((ulVal & 0xff00) << 8) |
        ((ulVal & 0xff0000) >> 8) | (ulVal >> 24);
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PRF
 ��������  : PRF�㷨����
 �������  : pucKey      ������ԿKey
             ucKeyLen    ��ԿKey����
             ucMacLen    ���ܽ������
 �������  : pucMac      ���ܺ�Ľ��
 �� �� ֵ  : �ɹ� VOS_OK   ʧ�� VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_PRF
(
    VOS_UINT8                          *pucKey,
    VOS_UINT8                           ucKeyLen,
    VOS_UINT8                          *pucMac,
    VOS_UINT8                           ucMacLen
)
{
    VOS_UINT8                           aucXkey[64];
    VOS_UINT32                          aucT0[5];
    VOS_UINT32                          aucT1[5];
    VOS_UINT32                          ulIndexi;
    VOS_UINT32                          ulIndexj;
    VOS_INT32                           ilIndexk;
    VOS_UINT32                          ulNum;
    VOS_UINT8                          *pucPos = pucMac;
    VOS_UINT32                          ulCarry;

    PS_MEM_SET(aucXkey, 0, 64);
    PS_MEM_SET(aucT1, 0, sizeof(VOS_UINT32) * 5);

    if (ucKeyLen < sizeof(aucXkey))
    {
        PS_MEM_SET(aucXkey + ucKeyLen, 0, sizeof(aucXkey) - ucKeyLen);
    }
    else
    {
        ucKeyLen = sizeof(aucXkey);
    }

    /* FIPS 186-2 + change notice 1 */

    PS_MEM_CPY(aucXkey, pucKey, ucKeyLen);

    aucT0[0] = 0x67452301;
    aucT0[1] = 0xEFCDAB89;
    aucT0[2] = 0x98BADCFE;
    aucT0[3] = 0x10325476;
    aucT0[4] = 0xC3D2E1F0;

    ulNum = ucMacLen / 40;
    for (ulIndexj = 0; ulIndexj < ulNum; ulIndexj++)
    {
        /* XSEED_j = 0 */
        for (ulIndexi = 0; ulIndexi < 2; ulIndexi++) {
            /* XVAL = (XKEY + XSEED_j) mod 2^b */

            /* w_i = G(t, XVAL) */
            PS_MEM_CPY(aucT1, aucT0, 20);
            PPPC_SHA1_Transform(aucT1, aucXkey);
            aucT1[0] = PPPC_SHA1_GET_BE32(aucT1[0]);
            aucT1[1] = PPPC_SHA1_GET_BE32(aucT1[1]);
            aucT1[2] = PPPC_SHA1_GET_BE32(aucT1[2]);
            aucT1[3] = PPPC_SHA1_GET_BE32(aucT1[3]);
            aucT1[4] = PPPC_SHA1_GET_BE32(aucT1[4]);
            PS_MEM_CPY(pucPos, aucT1, 20);

            /* XKEY = (1 + XKEY + w_i) mod 2^b */
            ulCarry = 1;
            for (ilIndexk = 19; ilIndexk >= 0; ilIndexk--) {
                ulCarry += aucXkey[ilIndexk] + pucPos[ilIndexk];
                aucXkey[ilIndexk] = ulCarry & 0xff;
                ulCarry >>= 8;
            }

            pucPos += PPPC_SHA1_MAC_LEN;
        }
    }

    return VOS_OK;

}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

