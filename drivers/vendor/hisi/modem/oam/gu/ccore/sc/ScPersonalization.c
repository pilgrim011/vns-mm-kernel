/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : ScPersonalization.c
  �� �� ��      : ����
  ��    ��      : w00184875
  ��������      : 2012��04��07��
  ����޸�      :
  ��������      : ��C�ļ�������ScPersonalizationģ���ʵ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2012��04��07��
    ��    ��    : w00184875
    �޸�����    : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ScInterface.h"
#include "ScComm.h"
#include "ScFactory.h"
#include "ScPersonalization.h"
#include "UsimPsInterface.h"
#include "ScCtx.h"
#include "NVIM_Interface.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 �޸���:��Ц�� 00184875;ԭ��:Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_SC_PERSONALIZATION_C
/*lint +e767 �޸���:��Ц�� 00184875;*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : SC_PERS_GetCategoryByStatus
 ��������  : ͨ����״̬��ȡ��ǰ��category
 �������  : enSIMLockStatus: ��ǰ��������״̬

 �������  : ��
 �� �� ֵ  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��09��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_PERSONALIZATION_CATEGORY_ENUM_UINT8 SC_PERS_GetCategoryByStatus(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSIMLockStatus
)
{
    switch (enSIMLockStatus)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            return SC_PERSONALIZATION_CATEGORY_NETWORK;

        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            return SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET;

        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            return SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER;

        default:
            SC_ERROR_LOG("SC_PERS_GetCategoryByStatus: enSIMLockStatus is out of range.");
            break;
    }

    return SC_PERSONALIZATION_CATEGORY_BUTT;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_GetStatusByCategory
 ��������  : ͨ����ǰ��category����Ϣ��ȡ��������״̬
 �������  : pstSimlockCatogory: ��ǰcategory����Ϣ

 �������  : ��
 �� �� ֵ  : SC_VERIFY_SIMLOCK_RESULT_ENUM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��12��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 SC_PERS_GetStatusByCategory(
    SC_SIMLOCK_CATEGORY_STRU *pstSimlockCatogory
)
{
    /* �������PIN״̬������category������������״̬ */
    if (SC_PERSONALIZATION_STATUS_PIN == pstSimlockCatogory->enStatus)
    {
        switch (pstSimlockCatogory->enCategory)
        {
            case SC_PERSONALIZATION_CATEGORY_NETWORK:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

            case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN;

            case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                return SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN;

            default:
                SC_ERROR_LOG("SC_PERS_GetStatusByCategory: pstSimlockCatogory is out of range.");
                return SC_VERIFY_SIMLOCK_RESULT_BUTT;
        }
    }

    if (SC_PERSONALIZATION_STATUS_PUK == pstSimlockCatogory->enStatus)
    {
        switch (pstSimlockCatogory->enCategory)
        {
            case SC_PERSONALIZATION_CATEGORY_NETWORK:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK;

            case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                return SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK;

            case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                return SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK;

            default:
                SC_ERROR_LOG("SC_PERS_GetStatusByCategory: pstSimlockCatogory is out of range.");
                return SC_VERIFY_SIMLOCK_RESULT_BUTT;
        }
    }

    return SC_VERIFY_SIMLOCK_RESULT_BUTT;
}


/*****************************************************************************
 �� �� ��  : SC_PERS_Bcd2Num
 ��������  : �����������ŶΣ���BCD�뵽���ֵ�ת��
 �������  : pucBcdNum: �����BCD��
             ulBcdNumLen:BCD�볤��
 �������  : pucDestNum: ����ת�����������
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��9��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_VOID SC_PERS_Bcd2Num(
    VOS_UINT8                          *pucDestNum,
    const VOS_UINT8                    *pucBcdNum,
    VOS_UINT32                          ulBcdNumLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucFirstNumber;
    VOS_UINT8                           ucSecondNumber;

    for (i = 0; i < ulBcdNumLen; i++)
    {
        /* �ֱ�ȡ���ߵ��ֽ� */
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0f);
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0f);

        if (ucFirstNumber <= 9)
        {
            *pucDestNum++ = ucFirstNumber;
        }

        if (ucSecondNumber <= 9)
        {
            *pucDestNum++ = ucSecondNumber;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_ImsiBcd2Num
 ��������  : �������IMSIת�����������
 �������  : ucLen: IMSI�ĳ��ȣ�9�ֽ�
             pucImsi:IMSI������
 �������  : pucNum: ����ת�����������
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��9��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_ImsiBcd2Num(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                    *pucImsi,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT8                           ucFirstByte;
    VOS_UINT8                           ucTmp;

    ucFirstByte = pucImsi[0];

    /* ���IMSI��һ���ֽڴ���0x08��˵��IMSI���ݲ���ȷ */
    if (SC_IMSI_FIRST_BYTE < ucFirstByte)
    {
        SC_ERROR_LOG("SC_PERS_ImsiBcd2Num: IMSI is wrong.");

        return VOS_ERR;
    }

    ucTmp = (pucImsi[1]>>4) & 0x0F;

    /* ��ת��IMSI�ڶ����ֽ� */
    SC_PERS_Bcd2Num(pucNum, &ucTmp, 1);

    /* ת��IMSI������ֽ� */
    SC_PERS_Bcd2Num(pucNum + 1, pucImsi + 2, ucLen - 2);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_SPBcd2Num
 ��������  : �������SPת�����������
 �������  : ucLen: SP�ĳ��ȣ�1�ֽ�
             pucSP:SP������
 �������  : pucNum: ����ת�����������
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��18��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_SPBcd2Num(
    VOS_UINT8                          *pucNum,
    const VOS_UINT8                    *pucSP,
    VOS_UINT8                           ucLen
)
{
    /* ������� */
    if ((0xFF == *pucSP) || (ucLen > SC_SP_LEN))
    {
        SC_ERROR_LOG("SC_PERS_SPBcd2Num: Para is wrong.");

        return VOS_ERR;
    }

    *pucNum = ((*pucSP)>>4) & 0x0F;

    *(pucNum + 1) = *pucSP & 0x0F;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CheckSimlockCodeLast2Char
 ��������  : ������������������ִ������λ�ĺϷ���
 �������  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- �Ŷ�����
 �������  : VOS_UINT8                              *pucLast2Num    -- ���ִ������λ
 �� �� ֵ  : VOS_UINT32     -- ת�����
                VOS_OK      -- ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��14��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_CheckSimlockCodeLast2Char(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucLast2Num
)
{
    VOS_UINT8                           i           = 0;

    /* ��������λ����Ч��, NET������ */
    if (SC_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB֧�ַ�Χ: 0x00~0x99 */
            if (9 >= pucLast2Num[i])
            {
                continue;
            }
            /* SP֧�ַ�Χ: 0x00~0xFF */
            else if ( (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && (0x0F >= pucLast2Num[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CheckSimlockCodeNum
 ��������  : ������������������ִ��Ϸ��ԣ���������ȷ�ĳ���
 �������  : SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- �Ŷ�����
 �������  : VOS_UINT8                              *pucNum         -- ��������ִ�
             VOS_UINT8                              *pucDepartLen   -- ���ִ���ȷ�ĳ���
 �� �� ֵ  : VOS_UINT32     -- ת�����
                VOS_OK      -- ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��14��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_CheckSimlockCodeNum(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucNum,
    VOS_UINT8                              *pucDepartLen
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucDepartLen;        /* ���ִ���ȷ�ĳ��� */
    VOS_UINT8                          *pucTmpNum;

    pucTmpNum   = pucNum;

    switch(enCategory)
    {
        case SC_PERSONALIZATION_CATEGORY_NETWORK:
            ucDepartLen = SC_NET_CODE_DEPART_LEN;
            break;
        default:
            ucDepartLen = SC_CODE_DEPART_LEN;
            break;
    }

    /* ���PLMN�Ϸ��Լ���λ�� */
    for (i = 0; i < SC_NET_CODE_DEPART_LEN; i++)
    {
        if (9 >= pucTmpNum[i])
        {
            continue;
        }
        else if ( ((SC_NET_CODE_DEPART_LEN - 1) == i)
               && (0x0F == pucTmpNum[i]) )
        {
            for (j = i + 1; j < ucDepartLen; j++)
            {
                pucTmpNum[j - 1] = pucTmpNum[j];
            }
            ucDepartLen = ucDepartLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pucDepartLen           = ucDepartLen;

    /* ��������������������λ�ĺϷ��� */
    if (VOS_OK != SC_PERS_CheckSimlockCodeLast2Char(enCategory, &pucTmpNum[ucDepartLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_SimlockCodeBcd2Num
 ��������  : �����������ŶΣ���BCD�뵽���ֵ�ת��
 �������  : const VOS_UINT8                        *pucBCD         -- ��ת��BCD�Ŷ�
             VOS_UINT8                              *pucDepartLen   -- ת����BCD��ĳ���
             SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory     -- �Ŷ�����
 �������  : VOS_UINT8                              *pucNum         -- ת��������ִ�
 �� �� ֵ  : VOS_UINT32     -- ת�����
                VOS_OK      -- ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��18��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_SimlockCodeBcd2Num(
    VOS_UINT8                              *pucNum,
    VOS_UINT8                              *pucDepartLen,
    const VOS_UINT8                        *pucBCD,
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory
)
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_UINT8                          *pucTmpNum;
    VOS_UINT8                           ucNum;
    VOS_UINT8                           i;

    /*lint -e534*/
    VOS_MemSet(pucNum, 0x00, SC_CODE_DEPART_LEN);
    /*lint +e534*/
    pucTmpNum   = pucNum;

    switch(enCategory)
    {
        case SC_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen       = SC_NET_CODE_LEN;
            break;
        case SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucLen       = SC_NETSUB_CODE_LEN;
            break;
        case SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucLen       = SC_SP_CODE_LEN;
            break;
        default:
            return VOS_ERR;
    }

    for (i = 0; i < ucLen; i++)
    {
        /* �ֱ�ȡ���ߵ��ֽ� */
        ucFirstNum  = (VOS_UINT8)((*(pucBCD + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBCD + i)) >> 4) & 0x0F);

        *pucTmpNum++    = ucFirstNum;
        *pucTmpNum++    = ucSecondNum;
    }

    /* ������λ������Ƶ�����λ(����߶Խ�) */
    pucTmpNum           = &pucNum[SC_CODE_FOURTH_NUM_INDEX];
    ucNum               = pucTmpNum[0];
    pucTmpNum[0]        = pucTmpNum[1];
    pucTmpNum[1]        = pucTmpNum[2];
    pucTmpNum[2]        = ucNum;

    /* �Ըߵ��ֽ�ת�������������������кϷ��Լ�� */
    if (VOS_OK != SC_PERS_CheckSimlockCodeNum(enCategory, pucNum, pucDepartLen))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CheckCode
 ��������  : ���кŶ�У��
 �������  : stSimLockCat:ÿһ�����Ľṹ
             pucIMSI:IMSI��ֺ�����ִ�
             enModemID:Modem ID

 �������  : ��
 �� �� ֵ  : VOS_TRUE:У��ͨ��
             VOS_FALSE:У��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 SC_PERS_CheckCode(
    SC_SIMLOCK_CATEGORY_STRU           *pstSimLockCat,
    VOS_UINT8                          *pucIMSI,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT8                           aucExCode[SC_SP_DEPART_LEN];
    VOS_UINT8                           aucPLMNEx[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucBeginLen;
    VOS_UINT8                           ucEndLen;
    VOS_UINT8                           aucCodeBegin[SC_CODE_DEPART_LEN];
    VOS_UINT8                           aucCodeEnd[SC_CODE_DEPART_LEN];
    VOS_INT32                           lResultBegin;
    VOS_INT32                           lResultEnd;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           i;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf = VOS_NULL_PTR;
    VOS_UINT32                          aucExCmpLen[SC_MAX_SUPPORT_CATEGORY] = {0, SC_NET_SUB_DEPART_LEN, SC_SP_DEPART_LEN};
    VOS_UINT32                          ulSimSvr;
    VOS_UINT32                          ulUsimSvr;

    /* û�м�����غŶ�ƥ��*/
    if (SC_PERSONALIZATION_INDICATOR_INACTIVE == pstSimLockCat->enIndicator)
    {
        SC_INFO1_LOG("SC_PERS_CheckCode: The indicator is not active.",
                     pstSimLockCat->enCategory);

        return VOS_TRUE;
    }

    /* �Ѿ������������غŶ�ƥ�� */
    if (SC_PERSONALIZATION_STATUS_READY == pstSimLockCat->enStatus)
    {
        SC_INFO1_LOG("SC_PERS_CheckCode: The status is not active.",
                     pstSimLockCat->enStatus);

        return VOS_TRUE;
    }

    /* �ж�PI�ļ����ĺϷ��ԣ��Ƿ�֧�� */
    if (pstSimLockCat->enCategory >= SC_MAX_SUPPORT_CATEGORY)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCode: The Category is out of range.",
                      pstSimLockCat->enCategory);

        return VOS_FALSE;
    }

    /*lint -e534*/
    VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);

    VOS_MemSet(aucExCode, 0, SC_SP_DEPART_LEN);
    /*lint +e534*/

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
    {
        /* ������񲻿���ֱ�ӷ���ʧ�� */
        ulSimSvr = SC_COMM_IsUsimServiceAvailable(SIM_SVR_GIDL1,  enModemID);
        ulUsimSvr = SC_COMM_IsUsimServiceAvailable(USIM_SVR_GID1, enModemID);

        if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulSimSvr)
            && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulUsimSvr))
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_IsServiceAvailable is failed.",
                          PS_USIM_SERVICE_NOT_AVAILIABLE);

            return VOS_FALSE;
        }

        /* ��ȡGID1�ļ���ʧ�ܷ��غŶβ�ƥ�� */
        ulResult = SC_COMM_GetUsimmCachedFile(USIMM_USIM_EFGID1_STR, &ulEfLen, &pucEf, USIMM_GUTL_APP, enModemID);

        if (VOS_OK != ulResult)
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_GetCachedFile is failed.",
                          ulResult);

            return VOS_FALSE;
        }

        if (VOS_OK != SC_PERS_SPBcd2Num(aucExCode, pucEf, SC_SP_LEN))
        {
            SC_ERROR1_LOG("SC_PERS_CheckCode: USIMM_GetCachedFile is failed.",
                          ulResult);

            return VOS_FALSE;
        }
    }

    /* �����õĺŶ�������ѭ���Ƚ� */
    for (i = 0; i < pstSimLockCat->ucGroupNum; i++)
    {
        /* ת���Ŷ�Begin, ת��ʧ������Ϊ���ڴ˺Ŷη�Χ�� */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeBegin,
                                                 &ucBeginLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeBegin,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        /* ת���Ŷ�End, ת��ʧ������Ϊ���ڴ˺Ŷη�Χ�� */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeEnd,
                                                 &ucEndLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeEnd,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        /* �Ŷε�Begin��End���Ȳ�һ��, ��Ϊ���ڴ˺Ŷη�Χ�� */
        if (ucBeginLen != ucEndLen)
        {
            continue;
        }

        /* ����PLMN�������չSP�ֽ� */
        if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
        {
            /*lint -e534*/
            VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);

            VOS_MemCpy(&aucPLMNEx[ucBeginLen - aucExCmpLen[pstSimLockCat->enCategory]],
                        aucExCode,
                        SC_SP_DEPART_LEN);
            /*lint +e534*/
        }

        /* ȷ���ȽϺŶγ��Ȳ������8 */
        if ((ucBeginLen > SC_CODE_DEPART_LEN)||(ucEndLen > SC_CODE_DEPART_LEN))
        {
            return VOS_FALSE;
        }

        lResultBegin    = VOS_MemCmp(aucPLMNEx, aucCodeBegin, ucBeginLen);

        lResultEnd      = VOS_MemCmp(aucPLMNEx, aucCodeEnd, ucEndLen);

        /* �Ŷ��ڷ�Χ�� */
        if ((lResultBegin >= 0) && (lResultEnd <= 0))
        {
            return VOS_TRUE;
        }
    }

    SC_ERROR_LOG("SC_PERS_CheckCode: The result is failed.");

    /* ���ƥ��ʧ�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifySimLock
 ��������  : ������������У��
 �������  : enModemID:Modem ID

 �������  : pucSimLockResult:��������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                 enModemID
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf;
    VOS_UINT8                           aucIMSI[SC_IMSI_DEPART_LEN];
    VOS_UINT32                          ulCatIndex;
    SC_PI_FILE_STRU                    *pstPIFile;

    /*�������������������жϴ˵����HUK�Ƿ���Ч(��Ч��Ϊȫ0������δд��HUK)��
      ����Ч�����ղ���������:
      1.�������������������������ƹ�λ����HUK��д�룬������豣֤���岻����ס��������ʹ��;
      2.ĳЩ��Ӫ�̲���������������߿��ܲ��������������ƹ�λ����HUK��д�룬������豣֤���岻����ס��������ʹ��*/
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

        SC_INFO1_LOG("#info:SC_PERS_VerifySimLock:huk not valid,modem is: .", enModemID);

        return SC_ERROR_CODE_NO_ERROR;
    }

    *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_BUTT;

    /* ����PI�ļ������ڴ� */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_VerifySimLock: VOS_MemAlloc is failed.");

        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡPI�ļ�������У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    /* ����ʧ�� */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: SC_COMM_ReadSCFileAndCmpSign is failed.",
                      ulResult);

        return ulResult;
    }

    pucEf   = VOS_NULL_PTR;
    ulEfLen = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �ж��Ƿ�Ϊ������ʽ */
    if (SC_PERS_PLATFORM_C == SC_PERS_SupportPlatform(enModemID))
    {
        if (MODEM_ID_0 != enModemID)
        {
            (VOS_VOID)VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);

            *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

            return SC_ERROR_CODE_NO_ERROR;
        }

        /* 6F22 */
        ulResult = SC_PERS_CDMAVrifySimLock(penVerifySimlockRslt, pstPIFile, enModemID);

        (VOS_VOID)VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);

        return ulResult;
    }
#endif

    /* ����USIMM_GetCachedFile��ȡIMSI */
    ulResult = SC_COMM_GetUsimmCachedFile(USIMM_USIM_EFIMSI_STR, &ulEfLen, &pucEf, USIMM_GUTL_APP, enModemID);

    /* ����ʧ�� */
    if (USIMM_API_SUCCESS != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: USIMM_GetCachedFile is failed.",
                      ulResult);

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ��BCDת��Ϊ���� */
    ulResult = SC_PERS_ImsiBcd2Num((VOS_UINT8)ulEfLen, pucEf, aucIMSI);

    if (VOS_OK != ulResult)
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_VerifySimLock: SC_PERS_ImsiBcd2Num is failed.",
                      ulResult);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ѭ��category���кŶ�У�� */
    for (ulCatIndex = 0; ulCatIndex < SC_MAX_SUPPORT_CATEGORY; ulCatIndex++)
    {
        ulResult = SC_PERS_CheckCode(&pstPIFile->astSimlockCategory[ulCatIndex],
                                     aucIMSI,
                                     enModemID);

        if (VOS_FALSE == ulResult)
        {
            *penVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[ulCatIndex]);
            break;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_AsciiNum2DecNum
 ��������  : SCģ�������ַ���ת��Ϊʮ�������ִ�
 �������  : VOS_UINT8     *pucAsciiNum -- ��ת���ַ�����
             VOS_UINT32     ulLen       -- �ַ����鳤��
 �������  : VOS_UINT8     *pucDecNum   -- תת�����ʮ�������ִ�
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��01��
    ��    ��   : d00212987
    �޸�����   : Imei �޸����ⵥ�޸���������
*****************************************************************************/
VOS_VOID SC_PERS_AsciiNum2DecNum(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucDecNum,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex         = 0;

    /* ����ָ���ɵ����߱�֤��ΪNULL, �ô������ж� */
    /* ֻ�ж� "0" ~ "9" */

    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        /* �ж��Ƿ������� */
        if ( ('0' <= pucAsciiNum[ulIndex]) && ('9' >= pucAsciiNum[ulIndex]) )
        {
            pucDecNum[ulIndex] = pucAsciiNum[ulIndex] - '0';
        }
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_ReadCMPIMEI
 ��������  : IMEI��У�顣
 �������  : enModemID    : ��0 ���߿� 1

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_ReadCMPIMEI(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT8                           aucScImei [SC_RSA_ENCRYPT_LEN]  = {0};
    VOS_UINT8                           aucPubImei[SC_IMEI_LEN + 1] = {0};
    VOS_UINT8                           aucNvImei [SC_IMEI_NV_LEN]  = {0};
    VOS_UINT32                          ulPubLen = SC_IMEI_LEN;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucImeiNum[SC_IMEI_NV_LEN] = {0};

    /* HUK �Ƿ�д��*/
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        SC_INFO1_LOG("#info:SC_PERS_ReadCMPIMEI:huk not valid,modem is: .", enModemID);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ��ȡIMEI-FILE������ǩ��У�� */
    SC_INFO1_LOG("#info:SC_PERS_ReadCMPIMEI: modem id is: .", enModemID);
    if (MODEM_ID_0 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I0,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I1,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemID)
    {
        ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_IMEI_I2,
                                                aucScImei,
                                                SC_RSA_ENCRYPT_LEN);
    }
#endif
#endif
    else
    {
        SC_ERROR_LOG("SC_PERS_ReadCMPIMEI: modem id  error.");
        return SC_ERROR_CODE_MODEM_ID_FAIL;
    }

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* IMEI ���Ľ��� */
    ulResult = SC_COMM_RsaDecrypt(aucScImei, SC_RSA_ENCRYPT_LEN, aucPubImei, &ulPubLen);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    /* ����AT�����·���������ֱ�ӱ��浽�ļ��У��ٴν��ܵõ����������ַ�����
       NV���ȡ�ĵ���������ʮ�������ִ������ڲ�һ�£�ͳһת����ʮ�������ִ�  */
    SC_PERS_AsciiNum2DecNum(aucPubImei, aucImeiNum, ulPubLen);

    /* ��ȡNV������IMEI �Ƚ� */
    ulResult = NV_ReadEx(enModemID, en_NV_Item_IMEI, aucNvImei, SC_IMEI_NV_LEN);
    if (NV_OK != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_ReadCMPIMEI: NV_Read Imei is failed.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    /* �ж�����IMEI�Ƿ����, IMEI ���ĳ��� 15λ */
    if (VOS_OK != VOS_MemCmp(aucImeiNum, aucNvImei, SC_IMEI_LEN))
    {
        SC_ERROR_LOG("SC_PERS_ReadCMPIMEI: MemCmp Imei is failed.");

        return SC_ERROR_CODE_CMP_IMEI_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
�� �� ��  : SC_PERS_IsIMEIValid
��������  : ���IMEI�Ƿ���Ч
�������  : pucNvImei : NV IMEIֵ
�������  : ��
�� �� ֵ  : VOS_FALSE/VOS_TRUE

�޶���¼  :
1.��    ��  : 2015��12��1��
  ��    ��  : d00212987
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SC_PERS_IsIMEIValid(
    VOS_UINT8                           *pucNvImei
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < SC_IMEI_LEN; ucIndex++)
    {
        if (0x00 != pucNvImei[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CheeckImei2ReplaceFlg
 ��������  : Check�Ƿ���Ҫ����modem0 IMEI�滻modem2��
 �������  : enModemID: ��0 ���߿�1

 �������  : NA
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
VOS_BOOL SC_PERS_CheeckImei2ReplaceFlg(
    MODEM_ID_ENUM_UINT16                enModemID)
{

    VOS_BOOL                            bRpelaceFlg = VOS_FALSE;
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    NV_SC_PERS_CTRL_STRU                stNVScpersCtrl;
    VOS_UINT8                           aucNvImei [SC_IMEI_NV_LEN]  = {0};
    VOS_UINT32                          ulResult;

    VOS_MemSet(&stNVScpersCtrl, 0, sizeof(NV_SC_PERS_CTRL_STRU));

    if (MODEM_ID_2 == enModemID)
    {
        /* ��ȡNV������IMEI */
        ulResult = NV_ReadEx(enModemID, en_NV_Item_IMEI, aucNvImei, SC_IMEI_NV_LEN);
        if (NV_OK != ulResult)
        {
            SC_ERROR1_LOG("SC_PERS_CheeckImei2ReplaceFlg: NV_Read Imei is failed.", ulResult);

            return bRpelaceFlg;
        }

        /* �ж�IMEI2�Ƿ���Ч */
        if (VOS_TRUE == SC_PERS_IsIMEIValid(aucNvImei))
        {
            return bRpelaceFlg;
        }

        /* ��ȡnv���ж��Ƿ����滻���� */
        ulResult = NV_Read(en_NV_Item_NV_SC_PERS_CTRL_CFG, &stNVScpersCtrl, sizeof(NV_SC_PERS_CTRL_STRU));
        if (NV_OK != ulResult)
        {
            SC_NORMAL_LOG("SC_PERS_CheeckImei2ReplaceFlg: read nv imei0 replace imei2 fail !");

            return bRpelaceFlg;
        }

        /* ����Imei 0�滻Imei 2���� */
        if (SC_IMEI0_REPLACE_IMEI2_FLG == stNVScpersCtrl.usImei0ReplaseImei2)
        {
            bRpelaceFlg = VOS_TRUE;

            SC_NORMAL_LOG("SC_PERS_CheeckImei2ReplaceFlg: Imei 0 replace 2!");
        }
    }
#endif
#endif

    return bRpelaceFlg;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifyIMEI
 ��������  : Android��̬�£��ṩ��NAS���IMEI�Ƿ���֤ͨ��API��
 �������  : enModemID: ��0 ���߿�1

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyIMEI(MODEM_ID_ENUM_UINT16 enModemID)
{
/* �Զ�ȡIMEI�͸���ʧ�������һ����ܣ�COMM��ȡ���Σ�ֻҪ��һ�γɹ����أ����򷵻�ȫ0 */
    VOS_UINT32                          ulLoop   = 0;
    SC_ERROR_CODE_ENUM_UINT32           enResult = SC_ERROR_CODE_OTHER_ERROR;
    MODEM_ID_ENUM_UINT16                enModemTempID;

    enModemTempID = enModemID;

    if (VOS_TRUE == SC_PERS_CheeckImei2ReplaceFlg(enModemID))
    {
        /* ��Ҫʹ��IMEI0�滻IMEI2 */
        enModemTempID = MODEM_ID_0;
    }

    for(ulLoop=0; ulLoop<SC_MAX_CMP_IMEI; ulLoop++)
    {
        enResult = SC_PERS_ReadCMPIMEI(enModemTempID);

        if (SC_ERROR_CODE_NO_ERROR == enResult)
        {
            return SC_ERROR_CODE_NO_ERROR;
        }
    }

    return enResult;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_NoVerifyNvReadImei
 ��������  : ��ȡ����NV���IMEI
             ˵��:����IMEI�ĺϷ�����У�飬ֱ��ȥ��NV,������NV_Read�ӿڣ�SC_PERS_NoVerifyNvReadImei�ӿ���modem2 IMEIûд������£���ȡmodem0
 �������  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv ����

 �������  : *pItem    : ��ȡNV ����
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_NoVerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemTempID;

    enModemTempID = enModemID;

    if (VOS_TRUE == SC_PERS_CheeckImei2ReplaceFlg(enModemID))
    {
        /* ��Ҫʹ��IMEI0�滻IMEI2 */
        enModemTempID = MODEM_ID_0;
    }

    /* ��ȡNV */
    ulResult = NV_ReadEx(enModemTempID, usID, pItem, ulLength);
    if (NV_OK != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_NoVerifyNvReadImei: NV_Read fail.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifyNvReadImei
 ��������  : ��ȡ����NV���IMEI,����IMEI��֤(����ֵΪ:SC_ERROR_CODE_NO_ERROR,��ȡ��NV���ݿ��ã����򲻿���)
             ˵��:��У��IMEI�ŵĺϷ��ԣ�Ȼ���ٶ�ȡNV�����IMEI�ŷǷ�����ȫ0 IMEI,������modem2 imei ûд������£���ȡmodem0
 �������  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv ����

 �������  : *pItem    : ��ȡNV ����
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32

 �޸���ʷ      :
  1.��    ��   : 2013��5��25��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    /* IMEI У�� */
    ulResult = SC_PERS_VerifyIMEI(enModemID);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR_LOG("SC_PERS_VerifyNvReadImei: Verify IMEI fail.");

        /*lint -e534*/
        VOS_MemSet(pItem, 0, ulLength);
        /*lint +e534*/

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ��ȡNV */
    ulResult = SC_PERS_NoVerifyNvReadImei(enModemID, usID, pItem, ulLength);
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_VerifyNvReadImei: NV_Read fail.", ulResult);

        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CheckCryptoCKUKPwd
 ��������  : CK/UK�����У��
 �������  : pucPwd: ��������
             ucLen: ���볤��
             enSIMLockStatus: ��������״̬
             enCategory: ��ǰ���ڵ����

 �������  : ��
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_CheckCryptoCKUKPwd(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSIMLockStatus,
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8 enCategory
)
{
    SC_CK_FILE_STRU                     stCKFile;
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucCryptoPwd[SC_CRYPTO_PWD_LEN];

    /* ��ȡCK-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_CK,
                                            (VOS_UINT8*)&stCKFile,
                                            sizeof(SC_CK_FILE_STRU));

    /* ��������ΪSC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ���������������������� */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_CK,
                                         pucPwd,
                                         ucLen,
                                         aucCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    /* ��������ΪSC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* ��������PIN */
    if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN == enSIMLockStatus))
    {
        lResult = VOS_MemCmp(aucCryptoPwd,
                             stCKFile.astCKCategory[enCategory].aucCKCryptoPwd,
                             SC_CRYPTO_PWD_LEN);
    }
    /* ��������PUK */
    else if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK == enSIMLockStatus)
        || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK == enSIMLockStatus))
    {
        lResult = VOS_MemCmp(aucCryptoPwd,
                             stCKFile.astCKCategory[enCategory].aucUKCryptoPwd,
                             SC_CRYPTO_PWD_LEN);
    }
    else
    {
        lResult = VOS_ERR;
    }

    /* �������ıȶ�ʧ�� */
    if (VOS_OK != lResult)
    {
        SC_ERROR1_LOG("SC_PERS_CheckCryptoCKUKPwd: VOS_MemCmp is failed.", lResult);

        return SC_ERROR_CODE_UNLOCK_KEY_INCORRECT;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_UpdateSimlockStatus
 ��������  : ��������У��������PI�ļ��е���������״̬
 �������  : enResult: ����У��Ľ��
             pstSimlockCategory: ���������������Ϣ
             penVerifySimlockRslt: ��ǰ��������״̬

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��12��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_VOID SC_PERS_UpdateSimlockStatus(
    SC_ERROR_CODE_ENUM_UINT32               enResult,
    SC_SIMLOCK_CATEGORY_STRU               *pstSimlockCategory,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8    *penVerifySimlockRslt
)
{
    /* ����У��ɹ� */
    if (SC_ERROR_CODE_NO_ERROR == enResult)
    {
        /* ��������������״̬��ͬʱ��������Ϊ���ֵ */
        if (SC_PERSONALIZATION_STATUS_PIN == pstSimlockCategory->enStatus)
        {
            pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_READY;
        }
        else
        {
            pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_PIN;
        }

        pstSimlockCategory->ucRemainUnlockTimes = pstSimlockCategory->ucMaxUnlockTimes;
    }
    else
    {
        /* PIN״̬��ʧ�� */
        if ((SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN == *penVerifySimlockRslt)
            || (SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN == *penVerifySimlockRslt)
            || (SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN == *penVerifySimlockRslt))
        {
            /*������������ʣ�����-1*/
            pstSimlockCategory->ucRemainUnlockTimes -= 1;

            /* ���ʣ�����Ϊ0������ΪPUK */
            if (0 == pstSimlockCategory->ucRemainUnlockTimes)
            {
                pstSimlockCategory->enStatus = SC_PERSONALIZATION_STATUS_PUK;
            }
        }
        else
        {
            /*PUK״̬��ִ��ʧ��*/
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_UnLock
 ��������  : ������UNBLOC����
 �������  : pcPwd: ��������
             ucLen: ���볤��
             enModemID:Modem ID
 �������  : pucSimLockResult:�������������������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UnLock(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT32                                              ulResult;
    VOS_UINT32                                              ulResultLater;
    SC_PI_FILE_STRU                                        *pstPIFile;
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;

    /* ����SC_VerifySimLock��ȡ��������״̬ */
    ulResult = SC_PERS_VerifySimLock(penVerifySimlockRslt, enModemID);

    /* ��������ΪSC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_VerifySimLock is failed.", ulResult);

        return ulResult;
    }

    /* �����ǰ��������״̬��SC_VERIFY_SIMLOCK_RESULT_READY */
    if (SC_VERIFY_SIMLOCK_RESULT_READY == *penVerifySimlockRslt)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: The status is wrong.", *penVerifySimlockRslt);

        return SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL;
    }

    /* �Խ����볤�����ж� */
    if (SC_PERS_PWD_LEN != ucLen)
    {
        SC_ERROR1_LOG("SC_PERS_UnLock: ucLen is not 16!", ucLen);

        return SC_ERROR_CODE_OTHER_ERROR;
    }

    /* ����PI�ļ������ڴ� */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_UnLock: VOS_MemAlloc is failed.");
        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡPI-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    /* ��������ΪSC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ������������״̬��ȡcategory */
    enCategory = SC_PERS_GetCategoryByStatus(*penVerifySimlockRslt);
    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER < enCategory)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_GetCategoryByStatus return bad enCategory.", enCategory);

        return SC_ERROR_CODE_PARA_FAIL;
    }

    /* ����У�� */
    ulResult = SC_PERS_CheckCryptoCKUKPwd(pucPwd,
                                          ucLen,
                                          *penVerifySimlockRslt,
                                          enCategory);

    /* ����У��������PI�ļ���״̬ */
    SC_PERS_UpdateSimlockStatus(ulResult,
                                &pstPIFile->astSimlockCategory[enCategory],
                                penVerifySimlockRslt);

    /* ��������PI�ļ� */
    ulResultLater = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstPIFile,
                                            sizeof(SC_PI_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResultLater)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_COMM_WriteSecretFile is failed.", ulResultLater);

        return ulResultLater;
    }

    /* ����SC_VerifySimLock��ȡ��������״̬ */
    ulResultLater = SC_PERS_VerifySimLock(penVerifySimlockRslt, enModemID);

    if (SC_ERROR_CODE_NO_ERROR != ulResultLater)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_UnLock: SC_PERS_VerifySimLock is failed.", ulResultLater);

        return ulResultLater;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : SC_PERS_ErasePIFile
 ��������  : ��PI�ļ��г�CATEGORY��������������ֶ�ȫ������
 �������  : pstPiFile:PI�ļ��������ڴ��еĵ�ַ

 �������  : NA
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��7��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_VOID SC_PERS_ErasePIFile(SC_PI_FILE_STRU *pstPiFile)
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;
    VOS_UINT32                                              i;

    for (i = 0; i < SC_MAX_SUPPORT_CATEGORY; i++)
    {
        enCategory = (SC_PERSONALIZATION_CATEGORY_ENUM_UINT8)i;

        /*lint -e534*/
        VOS_MemSet((VOS_VOID*)&pstPiFile->astSimlockCategory[i], 0, sizeof(SC_SIMLOCK_CATEGORY_STRU));
        /*lint +e534*/

        pstPiFile->astSimlockCategory[i].enCategory = enCategory;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_EraseCKFile
 ��������  : ��CK�ļ������������ֶ�ȫ������
 �������  : pstCkFile:CK�ļ��������ڴ��еĵ�ַ

 �������  : NA
 �� �� ֵ  : NA
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��12��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
VOS_VOID SC_PERS_EraseCKFile(SC_CK_FILE_STRU *pstCkFile)
{
    /*lint -e534*/
    VOS_MemSet(pstCkFile, 0, sizeof(SC_CK_FILE_STRU));
    /*lint +e534*/

    return;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_UpdatePIFile
 ��������  : ��PI�ļ��ж�ӦCATEGORY�����ݰ�AT�������������޸�
 �������  : pstPiFile:PI�ļ��������ڴ��еĵ�ַ
             pstWriteSimLockData: ��д��PI-FILE��SIMLOCK��Ϣ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32���͵�SC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��9��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdatePIFile(
    SC_PI_FILE_STRU                    *pstPiFile,
    SC_WRITE_SIMLOCK_DATA_STRU         *pstWriteSimLockData
)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT32                          ulRsaDecryptLen;
    VOS_INT                             lHashLen;
    VOS_UINT8                           aucRsaDecrypt[SC_HASH_LEN];
    VOS_UINT8                           aucHash[SC_HASH_LEN];

    if (SC_MAX_SUPPORT_CATEGORY <= pstWriteSimLockData->enCategory)
    {
        SC_ERROR_LOG("SC_PERS_UpdatePIFile: Catogory is not support.");

        return SC_ERROR_CODE_LOCK_CODE_INVALID;
    }

    /* ��ʹ��AK-File�еĹ�Կ��aucSimlockRsaData���н��� */
    ulRsaDecryptLen = SC_HASH_LEN;

    ulResult = SC_COMM_RsaDecrypt(pstWriteSimLockData->aucSimlockRsaData,
                                  SC_RSA_ENCRYPT_LEN,
                                  aucRsaDecrypt,
                                  &ulRsaDecryptLen);

    /* �������RSA����ʧ�ܣ����ش���ԭ��ֵ */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdatePIFile: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    /* ͨ��MD5�㷨�������������������ĺŶ����ݵ�ժҪ */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pstWriteSimLockData->astLockCode,
                          SC_MAX_CODE_NUM*sizeof(SC_PH_LOCK_CODE_STRU),
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR*)aucHash,
                          &lHashLen);

    /* ���ͨ������MD5ժҪʧ�ܣ����ؼ���HASHʧ�� */
    if ((VOS_OK != lResult) || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR1_LOG("SC_PERS_UpdatePIFile: mdrv_crypto_hash is failed.", ulResult);

        return SC_ERROR_CODE_GENERATE_HASH_FAIL;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    /* ����PC�������޷�ģ��RSA����(��ΪRSA��Ҫ˽Կ�͹�Կ�ԣ���˽Կ�޷���ȡ���޷�ģ����ʵ��RSA��������)��
        ����������߼���PC�����ϲ�ִ�� */
    /* ���RSA���ܺ�MD5�����ժҪ���Ȳ���ȣ��������߱Ƚϲ���ȷ��� */
    if (VOS_OK != VOS_MemCmp(aucRsaDecrypt, aucHash, SC_HASH_LEN))
    {
        SC_ERROR_LOG("SC_PERS_UpdatePIFile: VOS_MemCmp is failed.");

        return SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL;
    }
#endif

    /* ����������������ĺŶ�����д��PI�ļ����ڴ��� */
    /*lint -e534*/
    VOS_MemCpy(pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].astLockCode,
               pstWriteSimLockData->astLockCode,
               sizeof(SC_PH_LOCK_CODE_STRU) * SC_MAX_CODE_NUM);
    /*lint +e534*/

    /* ��AT������enIndicator/ucGroupNum/ucMaxUnlockTimesд�룬���������ʣ����� */
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enIndicator          = pstWriteSimLockData->enIndicator;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucGroupNum           = pstWriteSimLockData->ucGroupNum;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucMaxUnlockTimes     = pstWriteSimLockData->ucMaxUnlockTimes;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].ucRemainUnlockTimes  = pstWriteSimLockData->ucMaxUnlockTimes;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enCategory           = pstWriteSimLockData->enCategory;
    pstPiFile->astSimlockCategory[pstWriteSimLockData->enCategory].enStatus             = SC_PERSONALIZATION_STATUS_PIN;

    /* �������ɵ�PI�ļ�д���ļ�ϵͳ */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                       (VOS_UINT8*)pstPiFile,
                                       sizeof(SC_PI_FILE_STRU));

    SC_INFO1_LOG("SC_PERS_UpdatePIFile: SC_COMM_WriteSecretFile result is:", ulResult);

    return ulResult;

}

/*****************************************************************************
 �� �� ��  : SC_PERS_UpdateCKUKPwd
 ��������  : �����ڴ���CK��UK���벢д��CK�ļ�
 �������  : pucEncryptPwd:AT��������˽Կ���ܹ�������
             enIndicator:ָ��category�����������Ƿ񼤻�
 �������  : pucPwd:CK�ļ�����Ҫ�޸ĵ�������ڴ��ַ
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32���͵�SC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��9��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdateCKUKPwd(
    VOS_UINT8                                              *pucPwd,
    VOS_UINT8                                              *pucEncryptPwd,
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulPwdDecryptLen;
    VOS_UINT32                          ulCipherLen;
    VOS_UINT8                           aucPwdDecrypt[SC_PERS_PWD_LEN] = {0};
    VOS_UINT8                           aucCipherData[SC_CRYPTO_PWD_LEN];
    VOS_UINT8                           ucLoop;

    ulPwdDecryptLen = SC_PERS_PWD_LEN;

    /* ��ʹ��AK-File�еĹ�Կ��pucEncryptPwd���н��� */
    ulResult = SC_COMM_RsaDecrypt(pucEncryptPwd,
                                  SC_RSA_ENCRYPT_LEN,
                                  aucPwdDecrypt,
                                  &ulPwdDecryptLen);

    /* �������RSA����ʧ�ܣ����ش���ԭ��ֵ */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKUKPwd: SC_COMM_RsaDecrypt is failed.", ulResult);

        return ulResult;
    }

    if (SC_PERSONALIZATION_INDICATOR_ACTIVE == enIndicator)
    {
        /* �жϽ��ܺ�����������Ƿ�Ϊ��ֵΪ"0"~"9"������ */
        for (ucLoop = 0; ucLoop < SC_PERS_PWD_LEN; ucLoop++)
        {
            if (0x09 < aucPwdDecrypt[ucLoop])
            {
                SC_ERROR_LOG("SC_PERS_UpdateCKUKPwd: aucPwdDecrypt is incorrect!");

                return SC_ERROR_CODE_OTHER_ERROR;
            }
        }
    }

    /* ������������ */
    ulCipherLen = SC_CRYPTO_PWD_LEN;

    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_CK,
                                         aucPwdDecrypt,
                                         (VOS_UINT8)ulPwdDecryptLen,
                                         aucCipherData,
                                         ulCipherLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKUKPwd: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* ���������������д�ص�CK�ļ��ڴ��� */
    /*lint -e534*/
    VOS_MemCpy(pucPwd, aucCipherData, ulCipherLen);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_UpdateCKFile
 ��������  : ��CK�ļ��ж�ӦCK/UK��������ݰ�AT�������������޸�
 �������  : pstCkFile:CK�ļ��������ڴ��еĵ�ַ
             pstWriteSimLockData: ��д��CK-File����Ϣ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32���͵�SC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��9��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UpdateCKFile(
    SC_CK_FILE_STRU                    *pstCkFile,
    SC_WRITE_SIMLOCK_DATA_STRU         *pstWriteSimLockData
)
{
    VOS_UINT32                          ulResult;

    /* ��AT���������PIN�����RSA���ܺ���AES ECB�㷨������д��CK�ļ����ڴ��� */
    ulResult = SC_PERS_UpdateCKUKPwd(pstCkFile->astCKCategory[pstWriteSimLockData->enCategory].aucCKCryptoPwd,
                                     pstWriteSimLockData->aucLockRsaPin,
                                     pstWriteSimLockData->enIndicator);

    /* ����CK���ɹ�������ʧ��ԭ�� */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_PERS_UpdateCKUKPwd is failed.", ulResult);

        return ulResult;
    }

    /* ��AT���������PUK�����RSA���ܺ���AES ECB�㷨������д��CK�ļ����ڴ��� */
    ulResult = SC_PERS_UpdateCKUKPwd(pstCkFile->astCKCategory[pstWriteSimLockData->enCategory].aucUKCryptoPwd,
                                     pstWriteSimLockData->aucLockRsaPuk,
                                     pstWriteSimLockData->enIndicator);

    /* ����UK���ɹ�������ʧ��ԭ�� */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_PERS_UpdateCKUKPwd is failed.", ulResult);

        return ulResult;
    }

    /* �����µ�CK�ļ���ǩ���ļ� */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_CK,
                                       (VOS_UINT8*)pstCkFile,
                                       sizeof(SC_CK_FILE_STRU));

    SC_ERROR1_LOG("SC_PERS_UpdateCKFile: SC_COMM_WriteSecretFile result is:", ulResult);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_WriteSimLockData
 ��������  : NAS�յ�AT^SIMLOCKDATAWRITE���ͨ���ýӿ�д��SIMLOCK��Ϣ
 �������  : pstWriteSimLockData: ��д��PI-FILE��CK-File��SIMLOCK��Ϣ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32���͵�SC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��7��
    ��    ��   : h59254
    �޸�����   : AP-Modem����������Ŀ��������
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_WriteSimLockData(SC_WRITE_SIMLOCK_DATA_STRU *pstWriteSimLockData)
{
    VOS_UINT32                          ulResult;
    SC_PI_FILE_STRU                    *pstSimlockInfo;
    SC_CK_FILE_STRU                     stCkFile;
    VOS_UINT32                          ulFlag;

    ulFlag = VOS_FALSE;

    /* ��Ȩδ���ֱ�ӷ������У��δ��� */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_PERS_WriteSimLockData: SC_CTX_GetFacAuthStatus is not done.");
        /* �������У��δ��� */
        return SC_ERROR_CODE_IDENTIFY_NOT_FINISH;
    }

    /* ����PI�ļ��Ƚϴ�ΪPI�ļ������ڴ� */
    pstSimlockInfo = (SC_PI_FILE_STRU *)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT, sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstSimlockInfo)
    {
        SC_ERROR_LOG("SC_PERS_WriteSimLockData: VOS_MemAlloc is failed.");

        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡPIFile�ļ����ݲ��Ƚ�ǩ���ļ����� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstSimlockInfo,
                                            sizeof(SC_PI_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /* ���ñ��Ϊ�� */
        ulFlag = VOS_TRUE;
    }

    /* ��ȡCKFile�ļ����ݲ��Ƚ�ǩ���ļ����� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_CK,
                                            (VOS_UINT8*)&stCkFile,
                                            sizeof(SC_CK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /* ���ñ��Ϊ�� */
        ulFlag = VOS_TRUE;
    }

    /* PI��CK�ļ���ȡ��Ƚ�ǩ������ȷ����Ҫ�������ļ����������� */
    if (VOS_TRUE == ulFlag)
    {
        /* ���֮ǰ����PI��CK�ļ���ȡʧ�ܻ�ǩ���Ƚ�ʧ�ܣ���PI�ļ��г�CATEGORY��������ֶ�ȫ������ */
        SC_PERS_ErasePIFile(pstSimlockInfo);

        /* CK�ļ�����ȫ������ */
        SC_PERS_EraseCKFile(&stCkFile);
    }

    /* д����������ǰ���Ƚ��в�����Ч�Լ��(���enCategory��enIndicator��ucGroupNum��ucMaxUnlockTimes��
       �Ŷ����ݲ����Ϸ��Լ��) */
    if ((pstWriteSimLockData->enCategory >= SC_MAX_SUPPORT_CATEGORY)
     || (pstWriteSimLockData->enIndicator >= SC_PERSONALIZATION_INDICATOR_BUTT)
     || (pstWriteSimLockData->ucGroupNum > SC_MAX_CODE_NUM)
     || ( (SC_PERSONALIZATION_INDICATOR_ACTIVE == pstWriteSimLockData->enIndicator)
       && (0 == pstWriteSimLockData->ucMaxUnlockTimes)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_WriteSimLockData: Parameter check fail!");
        return SC_ERROR_CODE_OTHER_ERROR;
    }

    /* ��������������д��CK�ļ��Ļ����� */
    ulResult = SC_PERS_UpdateCKFile(&stCkFile, pstWriteSimLockData);

    /* ���д��ʧ�ܣ����ش���ԭ��ֵ���ͷ��ڴ� */
    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_PERS_WriteSimLockData: SC_PERS_UpdateCKFile is failed.", ulResult);

        return ulResult;
    }

    /* ��������������д��PI�ļ����� */
    ulResult = SC_PERS_UpdatePIFile(pstSimlockInfo, pstWriteSimLockData);

    /* �ͷ��ڴ棬���ز������ */
    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstSimlockInfo);
    /*lint +e534*/

    SC_INFO1_LOG("SC_PERS_WriteSimLockData: SC_PERS_UpdatePIFile result is:", ulResult);

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : SC_PERS_GetSimlockInfo
 ��������  : NASͨ���ýӿڻ�ȡSIMLOCK��Ϣ
 �������  : pstSimlockInfo:��ȡSIMLOCK��Ϣ�����ݽṹ���ɵ����������ڴ�
 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��09��
    ��    ��   : d00212987
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_GetSimlockInfo(SC_SIMLOCK_INFO_STRU *pstSimlockInfo)
{
    VOS_UINT32                          ulResult;

    /* ��ȡPI-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                            (VOS_UINT8*)pstSimlockInfo,
                                            sizeof(SC_SIMLOCK_INFO_STRU));

    SC_INFO1_LOG("SC_PERS_GetSimlockInfo: SC_COMM_ReadSCFileAndCmpSign result is:", ulResult);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_SimlockUnlock
 ��������  : ����Simlock��������
 �������  : enCategory         -- ������������
             *pucPwd            -- ��������
 �������  : ��
 �� �� ֵ  : VOS_OK     -- �����ɹ�
             VOS_ERR    -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 SC_PERS_SimlockUnlock(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucPwd)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRslt;
    SC_PI_FILE_STRU                    *pstPIFile;
    VOS_UINT32                          ulResult;

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER < enCategory)
    {
        SC_ERROR_LOG("SC_PERS_SimlockUnlock: Category error.");

        return VOS_ERR;
    }


    /* ����PI�ļ������ڴ� */
    pstPIFile = (SC_PI_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                                               sizeof(SC_PI_FILE_STRU));

    if (VOS_NULL_PTR == pstPIFile)
    {
        SC_ERROR_LOG("SC_PERS_SimlockUnlock: VOS_MemAlloc is failed.");
        /* �����ڴ�����ʧ�� */
        return VOS_ERR;
    }

    /* ��ȡPI-FILE������ǩ��У��,��������ΪSC_ERROR_CODE_NO_ERROR */
    if (SC_ERROR_CODE_NO_ERROR != SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_PI,
                                                               (VOS_UINT8*)pstPIFile,
                                                               sizeof(SC_PI_FILE_STRU)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SC_COMM_ReadSCFileAndCmpSign is failed.");

        return VOS_ERR;
    }

    /* ��Ӧ��enCategory����δ����SIMLCOK���� */
    if (SC_PERSONALIZATION_INDICATOR_ACTIVE != pstPIFile->astSimlockCategory[enCategory].enIndicator)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SimLock not active.");

        return VOS_OK;
    }

    /* ��Ӧ��enCategory����SIMLCOK�Ѿ���֤ͨ�� */
    if (SC_PERSONALIZATION_STATUS_READY == pstPIFile->astSimlockCategory[enCategory].enStatus)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SimLock PIN status is ready.");

        return VOS_OK;
    }

    enVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[enCategory]);

    /* ����У�� */
    ulResult    = SC_PERS_CheckCryptoCKUKPwd(pucPwd,
                                             SC_PERS_PWD_LEN,
                                             enVerifySimlockRslt,
                                             enCategory);
    /* ����У��������PI�ļ���״̬ */
    SC_PERS_UpdateSimlockStatus(ulResult,
                                &pstPIFile->astSimlockCategory[enCategory],
                                &enVerifySimlockRslt);

    /* ��������PI�ļ� */
    if (VOS_OK != SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_PI,
                                          (VOS_UINT8*)pstPIFile,
                                          sizeof(SC_PI_FILE_STRU)))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_PERS_SimlockUnlock: SC_COMM_WriteSecretFile is failed.");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstPIFile);
    /*lint +e534*/

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID SC_DEBUG(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                          ulOmDbgIndex;

    (VOS_VOID)SC_INFO1_LOG("\nSC_DEBUG: Data Len: = %d\n", ulDataLen);

    for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++)
    {
        (VOS_VOID)SC_NORMAL_ASCII_LOG(*((VOS_UINT8*)pucData + ulOmDbgIndex));
    }

    (VOS_VOID)SC_NORMAL_LOG("\r\n");

    return ;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_SupportPlatform
 ��������  : �жϵ�ǰmodem�Ƿ�֧�ֵ�����ʽ
 �������  : enModemID:Modem ID

 �������  : ��G/��C
 �� �� ֵ  : SC_PERS_PLATFORM_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��07��
    ��    ��   : d00212987
    �޸�����   : CDMA����������Ŀ��������
*****************************************************************************/
SC_PERS_PLATFORM_ENUM_UINT32 SC_PERS_SupportPlatform(
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT32                          ulResult;
    SC_PERS_SUPPORT_PLATFORM_STRU       stSupportPlatform;

    (VOS_VOID)VOS_MemSet(&stSupportPlatform, 0, sizeof(SC_PERS_SUPPORT_PLATFORM_STRU));

    /* ��ȡModem��ǰ���뼼��nv�� */
    ulResult = NV_ReadEx(enModemID,
                         en_NV_Item_SC_PERS_Support_Platform_Cfg,
                         &stSupportPlatform,
                         sizeof(SC_PERS_SUPPORT_PLATFORM_STRU));

    if ((NV_OK == ulResult) && (SC_PERS_PLATFORM_C == stSupportPlatform.enScPersModem))
    {
        return SC_PERS_PLATFORM_C;
    }

    SC_INFO1_LOG("SC_PERS_SupportPlatform: read nv 4007 is: ", stSupportPlatform.enScPersModem);

    /* NV��ʧ��Ĭ�Ϸ���֧��G���� */
    return SC_PERS_PLATFORM_G;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_ChangeNum
 ��������  : ����Э��ƻ�ԭ��ֵ
 �������  : ulSrcValude  -- BCD�볤��
             ulCodeMode   -- BCD���ŵ�λ��

 �������  : ��
 �� �� ֵ  : VOS_UINT32 -����Э�黹ԭ����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��28��
    ��    ��   :
    �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SC_PERS_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
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
 �� �� ��  : SC_PERS_CDMAImsiBcd2Num
 ��������  : ��IMSI��ȡPLMN
 �������  : enModemID:Modem ID

 �������  :  ucLen     : IMSI����
             *pucImsi   : IMSIֵ
             *pucNum    : ת��������PLMN

 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��07��
    ��    ��   : d00212987
    �޸�����   : CDMA����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMAImsiBcd2Num(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                    *pucImsi,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT32                          ulMCC     = 0; /* ���Ҵ��� */
    VOS_UINT32                          ulMNC     = 0; /* ������� */
    VOS_UINT32                          i;

/*
    6F22��ʽ��
    00 AA AA BB BB BB CC 80 DD DD

    ����DD DD
    MCCΪ460��NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 ת����2�ֽ�С�˸�ʽ16����Ϊ��67 01

    ����CC
    MNCΪ03��NUM = 10 * 10 + 3 - 11 = 92��ת����1�ֽ�16����Ϊ5C
*/
    ulMCC     = pucImsi[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucImsi[9] << 8));
    ulMCC     = SC_PERS_ChangeNum(ulMCC,3);       /* ���Ҵ��� */

    ulMNC     = pucImsi[6];
    ulMNC     = SC_PERS_ChangeNum(ulMNC,2);       /* ������� */

    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucNum,      "%03d", ulMCC);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucNum + 3,  "%02d", ulMNC);

    /* ����CW�����·��ķǿɼ��ַ����˴���Ҫת�� */
    for (i=0; i<SC_CDMA_PLMN_LEN; i++)
    {
        pucNum[i] = pucNum[i] - '0';
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SC_PERS_CDMACheckCode
 ��������  : ������������У��
 �������  : enModemID:Modem ID

 �������  : pucSimLockResult:��������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��07��
    ��    ��   : d00212987
    �޸�����   : CDMA����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMACheckCode(
    SC_SIMLOCK_CATEGORY_STRU           *pstSimLockCat,
    VOS_UINT8                          *pucIMSI,
    MODEM_ID_ENUM_UINT16                enModemID
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucExCode[SC_SP_DEPART_LEN];
    VOS_UINT8                           aucPLMNEx[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucBeginLen;
    VOS_UINT8                           ucEndLen;
    VOS_UINT8                           aucCodeBegin[SC_CODE_DEPART_LEN];
    VOS_UINT8                           aucCodeEnd[SC_CODE_DEPART_LEN];
    VOS_INT32                           lResultBegin;
    VOS_INT32                           lResultEnd;

    /* û�м�����غŶ�ƥ��*/
    if (SC_PERSONALIZATION_INDICATOR_INACTIVE == pstSimLockCat->enIndicator)
    {
        SC_INFO1_LOG("SC_PERS_CDMACheckCode: The indicator is not active.",
                     pstSimLockCat->enCategory);

        return VOS_TRUE;
    }

    /* �Ѿ������������غŶ�ƥ�� */
    if (SC_PERSONALIZATION_STATUS_READY == pstSimLockCat->enStatus)
    {
        SC_INFO1_LOG("SC_PERS_CDMACheckCode: The status is not active.",
                     pstSimLockCat->enStatus);

        return VOS_TRUE;
    }

    /* �ж�PI�ļ����ĺϷ��ԣ��Ƿ�֧�� */
    if (pstSimLockCat->enCategory >= SC_MAX_SUPPORT_CATEGORY)
    {
        SC_ERROR1_LOG("SC_PERS_CDMACheckCode: The Category is out of range.",
                      pstSimLockCat->enCategory);

        return VOS_FALSE;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(aucPLMNEx, pucIMSI, SC_IMSI_DEPART_LEN);
    SC_DEBUG(aucPLMNEx, SC_IMSI_DEPART_LEN);

    (VOS_VOID)VOS_MemSet(aucExCode, 0, SC_SP_DEPART_LEN);
    /*lint +e534*/

    if (SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == pstSimLockCat->enCategory)
    {
        return VOS_FALSE;
    }

    /* �����õĺŶ�������ѭ���Ƚ� */
    for (i = 0; i < pstSimLockCat->ucGroupNum; i++)
    {
        /* ת���Ŷ�Begin, ת��ʧ������Ϊ���ڴ˺Ŷη�Χ�� */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeBegin,
                                                 &ucBeginLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeBegin,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        SC_DEBUG(aucCodeBegin, ucBeginLen);

        /* ת���Ŷ�End, ת��ʧ������Ϊ���ڴ˺Ŷη�Χ�� */
        if (VOS_OK != SC_PERS_SimlockCodeBcd2Num(aucCodeEnd,
                                                 &ucEndLen,
                                                 pstSimLockCat->astLockCode[i].aucPhLockCodeEnd,
                                                 pstSimLockCat->enCategory))
        {
            continue;
        }

        SC_DEBUG(aucCodeEnd, ucEndLen);

        /* �Ŷε�Begin��End���Ȳ�һ��, ��Ϊ���ڴ˺Ŷη�Χ�� */
        if (ucBeginLen != ucEndLen)
        {
            continue;
        }

        /* ȷ���ȽϺŶγ��Ȳ������8 */
        if ((ucBeginLen > SC_CODE_DEPART_LEN)||(ucEndLen > SC_CODE_DEPART_LEN))
        {
            return VOS_FALSE;
        }

        lResultBegin    = VOS_MemCmp(aucPLMNEx, aucCodeBegin, ucBeginLen);
        lResultEnd      = VOS_MemCmp(aucPLMNEx, aucCodeEnd, ucEndLen);

        /* �Ŷ��ڷ�Χ�� */
        if ((lResultBegin >= 0) && (lResultEnd <= 0))
        {
            return VOS_TRUE;
        }
    }

    SC_ERROR_LOG("SC_PERS_CheckCode: The result is failed.");

    /* ���ƥ��ʧ�� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : SC_PERS_CDMAVrifySimLock
 ��������  : ������������У��
 �������  : enModemID:Modem ID

 �������  : pucSimLockResult:��������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��07��
    ��    ��   : d00212987
    �޸�����   : CDMA����������Ŀ��������
*****************************************************************************/
VOS_UINT32 SC_PERS_CDMAVrifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    SC_PI_FILE_STRU                     *pstPIFile,
    MODEM_ID_ENUM_UINT16                 enModemID
)
{
    VOS_UINT32                          ulEfLen = 0;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;
    VOS_UINT8                           aucIMSI[SC_IMSI_DEPART_LEN];
    VOS_UINT8                           ucCardStatus;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulCatIndex;

    /* ����USIMM_GetCachedFile��ȡIMSI */
    ulResult = SC_COMM_GetUsimmCachedFile(USIMM_CDMA_EFIMSIM_STR, &ulEfLen, &pucEf, USIMM_CDMA_APP, enModemID);

    /* ����ʧ�� */
    if (USIMM_API_SUCCESS != ulResult)
    {
        SC_ERROR1_LOG("SC_PERS_CDMAVrifySimLock: USIMM_GetCachedFile is failed.", ulResult);

        /* ��ȡ��ǰ�û���CDMA���ò��������������� */
        (VOS_VOID)USIMM_GetCardTypeByAppType(&ucCardStatus, VOS_NULL_PTR, USIMM_CDMA_APP);

        if (USIMM_CARD_SERVIC_AVAILABLE != ucCardStatus)
        {
            SC_ERROR_LOG("SC_PERS_CDMAVrifySimLock: CDMA App is not AVAILABLE.");

            return SC_ERROR_CODE_OTHER_ERROR;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ��BCDת��Ϊ���� */
    ulResult = SC_PERS_CDMAImsiBcd2Num((VOS_UINT8)ulEfLen, pucEf, aucIMSI);

    if (VOS_OK != ulResult)
    {
        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN;

        SC_ERROR1_LOG("SC_PERS_CDMAVrifySimLock: SC_PERS_ImsiBcd2Num is failed.",
                      ulResult);

        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ѭ��category���кŶ�У�� */
    for (ulCatIndex = 0; ulCatIndex < SC_MAX_SUPPORT_CATEGORY; ulCatIndex++)
    {

        ulResult = SC_PERS_CDMACheckCode(&pstPIFile->astSimlockCategory[ulCatIndex],
                                         aucIMSI,
                                         enModemID);

        if (VOS_FALSE == ulResult)
        {
            *penVerifySimlockRslt = SC_PERS_GetStatusByCategory(&pstPIFile->astSimlockCategory[ulCatIndex]);
            break;
        }

        *penVerifySimlockRslt = SC_VERIFY_SIMLOCK_RESULT_READY;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

