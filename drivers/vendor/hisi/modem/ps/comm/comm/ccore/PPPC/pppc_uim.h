/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_uim.h
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��08��08��
  ����޸�   :
  ��������   : pppc_uim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PPPC_UIM_H__
#define __PPPC_UIM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
****************************************************************************/
#include "ppp_inc.h"
#include "UsimPsInterface.h"
#include "CUeSpec.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PPPC_HRPD_MEID_LEN                                    (7)               /* MEID�ֽڳ� */
#define PPPC_HRPD_MEID_BIT_LEN                                (56)              /* MEID�̶�Ϊ56��BIT�� */

#define PPPC_EAP_CIMSI_MCC_MAX_LEN                            (3)               /* MCC�ĳ��ȹ̶�Ϊ3 */
#define PPPC_EAP_CIMSI_MNC_MAX_LEN                            (3)               /* MNC��󳤶� */


#define PPPC_EAP_AUTN_LEN                                     (16)              /* AT_AUTN���� */
#define PPPC_EAP_RAND_LEN                                     (16)              /* AT_RAND���� */

/* �����ļ��Ĵ�С */
#define PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE                  (7)
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE              (256)


#define PPPC_MAX_USIM_FILE_NUM                                (8)               /* UIM �е��ļ���� */
#define PPPC_MAX_USIM_REQSEND_NUM                             (5)               /* һ�η��Ͷ����ļ������������ */
#define PPPC_HRPD_UIMREAD_MAX_RETRY_CNT                       (3)               /* ��ȡ�ļ�ʧ�����Դ��� */
#define PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER_LEN                (3000)            /* �����ļ���ʱ��ʱ�� */

/* �ļ�Mask */
#define PPPC_INIT_USIM_ELEMENT_RUIMID_MASK                    (0x01)            /* 6F31 */
#define PPPC_INIT_USIM_ELEMENT_CST_MASK                       (0x02)            /* 6F32 */
#define PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK                 (0x04)            /* 6F38 */
#define PPPC_INIT_USIM_ELEMENT_USGIND_MASK                    (0x08)            /* 6F42 */
#define PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK                   (0x10)            /* 6F57 */
#define PPPC_INIT_USIM_ELEMENT_EFIMSIM_MASK                   (0x20)            /* 6F22 */
#define PPPC_INIT_USIM_EFIMSI_MASK                            (0x40)            /* 6F07 */
#define PPPC_INIT_USIM_EFAD_MASK                              (0x80)            /* 6FAD */


/* ���� AUTH ������ʹ�õ� ProcessCtrl ֵ */
#define PPPC_HRPD_AUTH_PROCESSCTRL_DEFAULT_PROC               (0x00)
#define PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON               (0x10)

/* �����Ȩ��������NAI��Ϣ��Чʱ��ʹ��IMSI����NAI�Ĺ̶���׺ */
#define PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR                     ("@mycdma.cn")
#define PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_LEN                     (sizeof(PPPC_HRPD_AUTH_NAI_FIX_SUFFIX_STR))

/* �����Ȩ��������NAI��Ϣ��Ч��IMSI��Чʱ��ʹ�ù̶���׮��NAI */
#define PPPC_HRPD_AUTH_NAI_STUB_STR                           ("370021234567801@mycdma.cn")
#define PPPC_HRPD_AUTH_NAI_STUB_LEN                           (sizeof(PPPC_HRPD_AUTH_NAI_STUB_STR))


/***************************SHA-1�㷨��ض��� BEGIN**********************************************/

#define VOS_TRAN(var, num) (((var) << (num)) | ((var) >> (32 - (num))))

/* ����ʵ���Ͻ�����ulong�任���ֽ���
   ����   | a | b | c | d |
   ת��Ϊ | d | c | b | a |
*/

/* С���� */
#define VOS_NUM1 (0xFF00FF00)
#define VOS_NUM2 (0x00FF00FF)
#define VOS_VAR0(index) (pStr->ulNum[index] = (VOS_TRAN(pStr->ulNum[index],24)&VOS_NUM1) \
    |(VOS_TRAN(pStr->ulNum[index],8)&VOS_NUM2))

#define VOS_VAR(index) (pStr->ulNum[index&15] = VOS_TRAN(pStr->ulNum[(index+13)&15]^pStr->ulNum[(index+8)&15] \
    ^pStr->ulNum[(index+2)&15]^pStr->ulNum[index&15],1))

#define VOS_NUM3 (0x5A827999)
#define VOS_NUM4 (0x6ED9EBA1)
#define VOS_NUM5 (0x8F1BBCDC)
#define VOS_NUM6 (0xCA62C1D6)

#define OPERA0(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR0(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA1(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA2(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM4+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA3(a,b,c,d,e,f) e+=(((b|c)&d)|(b&c))+VOS_VAR(f)+VOS_NUM5+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA4(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM6+VOS_TRAN(a,5);b=VOS_TRAN(b,30);


/*******************************SHA-1�㷨��ض��� END******************************************/
#define USIMM_AUTH_IK_LEN               (16)                                    /* IK���� */
#define USIMM_AUTH_CK_LEN               (16)                                    /* CK���� */
#define USIMM_AUTH_AUTS_LEN             (14)                                    /* AUTS���� */
#define USIMM_AUTH_RES_LEN              (16)                                    /* RES��󳤶� */


/*******************************************************************************
                             ��ȡFixedData����ַ
*******************************************************************************/
#define PPPC_HRPD_GetFixedDataAddr(usModemId)       (&(g_astPppcFixedData[usModemId]))

#define PPPC_HRPD_GetUimStatus(usModemId)           ((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUimStatus)         /* ��ȡUIM���ڱ�� */
#define PPPC_HRPD_SetUimStatus(usModemId, enStatus) (((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUimStatus) = (enStatus))    /* ����UIM���ڱ�� */
#define PPPC_HRPD_GetUsimStatus(usModemId)          ((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUsimStatus)         /* ��ȡUSIM���ڱ�� */
#define PPPC_HRPD_SetUsimStatus(usModemId, enStatus)    (((PPPC_HRPD_GetFixedDataAddr(usModemId))->enUsimStatus) = (enStatus))    /* ����USIM���ڱ�� */

/* ��ȡUIM���ݵ�ַ */
#define PPPC_HRPD_GetUimDataAddr(usModemId)         (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimData))

/* ��ȡUSIM���ݵ�ַ */
#define PPPC_HRPD_GetUsimDataAddr(usModemId)         (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUsimData))

/* ��ȡNVIM���ݵ�ַ */
#define PPPC_HRPD_GetNvimDataAddr(usModemId)        (&((PPPC_HRPD_GetFixedDataAddr(usModemId))->stNvimData))

/* Terminal info */
#define PPPC_HRPD_GetTerminalInfoAddr(usModemId)    (&((PPPC_HRPD_GetNvimDataAddr(usModemId))->stTerminalInfo))

/* USIM����ȡ��ʾ */
#define PPPC_HRPD_GetUsimFileReqMask(usModemId)            ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileReqMask)    /* ��������Ҫ�����ı��λ */
#define PPPC_HRPD_GetUsimFileSucMask(usModemId)            ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileSucMask)    /* �����ļ��ɹ���־λ */
#define PPPC_HRPD_AddUsimFileSucMask(usModemId, ulFileMask)  ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileSucMask |= (ulFileMask))     /* ��Ӷ�ȡUSIM���ļ��ɹ���־λ */
#define PPPC_HRPD_AddUsimFileReqMask(usModemId, ulFileMask)  ((PPPC_HRPD_GetFixedDataAddr(usModemId))->ulUimFileReqMask |= (ulFileMask))     /* �����Ҫ��ȡUSIM���ļ���־λ */
#define PPPC_HRPD_GetUsimFileMask(usModemId, ulInd)          ((((PPPC_HRPD_GetUsimFileSucMask(usModemId)) & (PPPC_HRPD_GetUsimFileReqMask(usModemId))) >> ulInd) % 2) /* ��ȡָ�����ļ��Ķ�����־λ */
#define PPPC_HRPD_UimReadRetryCnt(usModemId)               ((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.ulRetryCnt)   /* �����ļ�ʧ�����Դ��� */
#define PPPC_HRPD_SetUimReadRetryCnt(usModemId, ulCnt)       ((PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.ulRetryCnt = ulCnt)   /* ���ö����ļ�ʧ�����Դ��� */
#define PPPC_HRPD_UimReadTimer(usModemId)                  ((&(PPPC_HRPD_GetFixedDataAddr(usModemId))->stUimReadTimer.hTimer))   /* �����ļ���ʱ�� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*******************************************************************************
* Name        : PPPC_HRPD_MEID_STRU
*
* Description : MEIDһ��56��bit
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}PPPC_HRPD_MEID_STRU;

/*******************************************************************************
 * Name        : PPPC_HRPD_UIM_STATUS_ENUM
 *
 * Description : UIM��״̬
 *******************************************************************************/
enum PPPC_HRPD_UIM_STATUS_ENUM
{
    PPPC_HRPD_UIM_STATUS_ABSENT         = 0,
    PPPC_HRPD_CARD_STATUS_UIM_PRESENT   = 1,
    PPPC_HRPD_CARD_STATUS_CSIM_PRESENT  = 2,
    PPPC_HRPD_UIM_STATUS_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_UIM_STATUS_ENUM_UINT8;

/*******************************************************************************
 * Name        : PPPC_HRPD_ESN_MEID_TYPE_ENUM
 *
 * Description : ESN or MEID ����
 *******************************************************************************/
enum PPPC_HRPD_ESN_MEID_TYPE_ENUM
{
    PPPC_HRPD_ESN_MEID_TYPE_ESN      = 0,
    PPPC_HRPD_ESN_MEID_TYPE_MEID        ,

    PPPC_HRPD_ESN_MEID_TYPE_BUTT
};
typedef VOS_UINT8 PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8;


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
/*******************************************************************************
* Name        : PPPC_USIMM_AUTH_DATA_STRU
*
* Description : ��Ȩ����
*******************************************************************************/
typedef struct
{
    USIMM_AUTH_TYPE_ENUM_UINT32         enAuthType;
    USIMM_AUTH_DATA_UNION               unAuthPara;
}PPPC_USIMM_AUTH_DATA_STRU;

/*******************************************************************************
* Name        : PPPC_USIM_READ_REQ_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3] ;                        /* ���ֽڶ��룬����        */
    VOS_UINT8                           ucFileNum;                              /* ��Ҫ��ȡ��File��Ŀ      */
    VOS_UINT16                          ausEfId[PPPC_MAX_USIM_FILE_NUM];        /* ��Ҫ��ȡ���ļ����      */
}PPPC_USIM_READ_REQ_STRU;

/*******************************************************************************
* Name        : PPPC_GET_FILE_INFO_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}PPPC_GET_FILE_INFO_STRU;


/*******************************************************************************
* Name        : PPPC_HRPD_CST_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCstLen;
    VOS_UINT8                           aucCst[PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE];
} PPPC_HRPD_CST_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_ESN_MEID_STRU
*
* Description : ������ESN��MEID����ͬʱ����
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_ESN_MEID_TYPE_ENUM_UINT8  enEsnMeidType;                          /* ESN or MEID */
    VOS_UINT8                           aucReserve[3];

    union
    {
        VOS_UINT32                      ulEsn;                                  /* �ӿ������������ESN */
        PPPC_HRPD_MEID_STRU             stMeid;                                 /* �ӿ������������MEID 56��bit */
    }u;
} PPPC_HRPD_ESN_MEID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_RUIMID_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumbytes;                             /* ��Ч��Bytes���� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRUIMIDLow;                            /* Low 32 bit of RUIMID */
    VOS_UINT32                          ulRUIMIDHigh;                           /* High 24 bit of RUIMID */
} PPPC_HRPD_RUIMID_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_USGIND_STRU
*
* Description :
*               Bit 0:
*                  FALSE: ESN_ME is used for CAVE Authentication and MS Identification
*                  TRUE: IDUIMID is used for CAVE Authentication and MS Identification
*
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsgInd;

    VOS_UINT8                           aucReserve[3];
}PPPC_HRPD_USGIND_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UPP_STRU
*
* Description :
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdUppLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHrpdUpp[PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE];
} PPPC_HRPD_UPP_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : ��UIM���ж�������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiLen;                              /* IMSI ռ�õĳ��� */
    VOS_UINT8                           aucImsi[PS_CUE_IMSI_MAX_SIZE];          /* MS��IMSI��ʶ */
    PPPC_HRPD_CST_STRU                  stEfCst;                                /* CDMAҵ��� */
    PPPC_HRPD_ESN_MEID_STRU             stEsnMeid;                              /* ESN or MEID */
    PPPC_HRPD_RUIMID_STRU               stRuimid;                               /* RUIMID */
    PPPC_HRPD_USGIND_STRU               stUsgind;                               /* USGIND */
    PPPC_HRPD_UPP_STRU                  stHrpdUpp;                              /* HRPD UPP */
    VOS_UINT8                           aucReserve[4];
} PPPC_HRPD_UIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_NVIM_TERMINAL_INFO_STRU
*
* Description : �ֻ������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsn;                                  /* ESN */
    PPPC_HRPD_MEID_STRU                 stMeid;                                 /* MEID */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} PPPC_HRPD_NVIM_TERMINAL_INFO_STRU;


/*******************************************************************************
* Name        : PPPC_HRPD_UIM_INFO_STRU
*
* Description : ��UIM���ж�������Ϣ
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU   stTerminalInfo;                         /* �ֻ������Ϣ */
} PPPC_HRPD_NVIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_READFILE_TIMER_STRU
*
* Description : �����ļ���ʱ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32               ulRetryCnt;                                        /* ��ȡ�ļ��������Դ��� */
    HTIMER                   hTimer;                                            /* ���ļ���ʱ��ʱ�� */
} PPPC_HRPD_READFILE_TIMER_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_USIM_INFO_STRU
*
* Description : �� USIM �ж�������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiLen;                              /* IMSI ռ�õĳ��� */
    VOS_UINT8                           aucImsi[PS_CUE_IMSI_MAX_SIZE];          /* MS��IMSI��ʶ */
    VOS_UINT8                           ucMncLen;                               /* MNC���� */
    VOS_UINT8                           aucRsv[3];
}PPPC_HRPD_USIM_INFO_STRU;

/*******************************************************************************
* Name        : PPPC_HRPD_FIXED_DATA_STRU
*
* Description : ��һ�ο����󣬱��ֲ�������ݣ�
*               ÿ��Deactiveʱ�����Ըò������ݽ��г�ʼ���������ڹػ�ʱ���ͷ�
*******************************************************************************/
typedef struct
{
    PPPC_HRPD_UIM_INFO_STRU             stUimData;                              /* �� UIM �ж����Ĳ��� */
    PPPC_HRPD_USIM_INFO_STRU            stUsimData;                             /* �� USIM �ж����Ĳ��� */
    PPPC_HRPD_NVIM_INFO_STRU            stNvimData;                             /* �� NVIM �ж����Ĳ��� */
    VOS_UINT32                          ulUimFileReqMask;                       /* ��������Ҫ�����ı��λ */
    VOS_UINT32                          ulUimFileSucMask;                       /* �����ļ��ɹ����λ */
    PPPC_HRPD_READFILE_TIMER_STRU       stUimReadTimer;                         /* �����ļ���ʱ�� */
    PS_BOOL_ENUM_UINT8                  enUimStatus;                            /* UIM���ڱ��,PS_TRUE:����,PS_FALSE:������ */
    PS_BOOL_ENUM_UINT8                  enUsimStatus;                           /* USIM���ڱ��,PS_TRUE:����,PS_FALSE:������ */
    VOS_UINT8                           aucReserve[2];
}PPPC_HRPD_FIXED_DATA_STRU;

/****************************** EAP����Ȩ������� ***************************/
enum PPPC_USIMM_AUTH_RESULT_ENUM
{
    PPPC_USIMM_AUTH_SUCCESS             = 0x00,        /*��Ȩ�ɹ�*/
    PPPC_USIMM_AUTH_MAC_FAILURE         = 0x01,        /*MACʧ��*/
    PPPC_USIMM_AUTH_SYNC_FAILURE        = 0x02,        /*��ͬ��ʧ��*/
    PPPC_USIMM_AUTH_OTHER_FAILURE       = 0x03,        /*����ʧ��*/
    PPPC_USIMM_AUTH_RESULT_BUTT
};
typedef VOS_UINT8 PPPC_USIMM_AUTH_RESULT_ENUM_UINT8;

/****************************** EAP����Ȩ���ؽṹ�� ***************************/
typedef struct
{
    PPPC_USIMM_AUTH_RESULT_ENUM_UINT8   enResult;
    VOS_UINT8                           aucIK[USIMM_AUTH_IK_LEN];               /* IK ����:16bytes */
    VOS_UINT8                           aucCK[USIMM_AUTH_CK_LEN];               /* CK ����:16bytes */
    VOS_UINT8                           aucAuts[USIMM_AUTH_AUTS_LEN];           /* AUTS ����:14bytes */
    VOS_UINT8                           aucAuthRes[USIMM_AUTH_RES_LEN];         /* RES ����:4~16bytes */
    VOS_UINT8                           ucAuthRseLen;
    VOS_UINT8                           ucIdentifier;                           /*͸������ */
    VOS_UINT8                           aucRsv[3];
}PPPC_EAP_AUTH_RESULT_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg);
VOS_VOID PPPC_InitFixedData(VOS_VOID);
VOS_UINT32 PPPC_UIM_GetCIMSI(VOS_UINT8 aucIMSI[]);
VOS_UINT32 PPPC_UIM_GetUsimIMSI(VOS_UINT8 aucIMSI[]);
VOS_VOID PPPC_HRPD_UimClearnReadTimer(VOS_VOID);
VOS_UINT32  PPPC_ReadFixedData(VOS_VOID);
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID);
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu);
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg);
VOS_UINT32 PPPC_UIM_BuildNAIByIMSI(VOS_UINT8 *pucNAIBuff, VOS_UINT32 ulNAIBuffLen);
VOS_UINT32 PPPC_UIM_SendEapAuthReq
(
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucIdentifier
);
VOS_UINT8 PPPC_UIM_GetImsiMncLen(VOS_VOID);





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

#endif /* end of pppc_uim.h */

