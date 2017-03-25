/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallCtx.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��9��3��
  ����޸�   :
  ��������   : TafXCallCtx.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��3��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_X_CALL_CTX_H__
#define __TAF_X_CALL_CTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "xcc_xcall_pif.h"
#include "TafCsCallCommDef.h"
#include "hi_list.h"
#include "TafXCallTimerMgmt.h"
#include "AtMnInterface.h"

#include "TafXCallKmcCommType.h"
#include "TafStdlib.h"
#include "TafAppCall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* call id ��1��ʼ */

/* 1X CALL �����и��� */
#define TAF_XCALL_CALL_ENTITY_MAX_NUM                       (2)

#define TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM                    (10)                /* ����ҵ���������ṹ */

#define TAF_XCALL_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define TAF_XCALL_MAX(x, y)\
        (((x)>(y))?(x):(y))


#define TAF_XCALL_MAX_TIMER_ID_NUM                          (10)            /* XCALL�Ķ�ʱ�������� */
#define TAF_XCALL_INVAILD_CALL_ID                           (0)

#define TAF_XCALL_DTMF_BUF_MAX_CNT               (32)                            /* ��໺��DTMF��Ϣ�ĸ��� */

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#define TAF_XCALL_ECC_KS_DATA_MAX_LEN                       (16)                /* ECC KSΪ128bit */
#define TAF_XCALL_MAX_OPID_NUM                              (3)                 /* ���opId��Ŀ */
#define TAF_XCALL_SIGN_DATA_INFO_LEN                        (13)
#define TAF_XCALL_SIGN_DATA_INFO_MAX_LEN                    (22)
#define TAF_XCALL_MEID_INFO_LEN                             (7)
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XCALL_SO_TYPE_ENUM
 �ṹ˵��  : XCALLά����SO
*****************************************************************************/
enum TAF_XCALL_SO_TYPE_ENUM
{
    TAF_XCALL_SO_3_EVRC                 = 0x0003,
    TAF_XCALL_SO_68_EVRC_B              = 0x0044,
    TAF_XCALL_SO_73_EVRC_NW             = 0x0049,

    TAF_XCALL_SO_BUTT                   = 0xFFFF
};
typedef VOS_UINT16 TAF_XCALL_SO_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : TAF_XCALL_CALL_SUB_STATE_ENUM
 �ṹ˵��  : ����ҵ���չ�¼�
*****************************************************************************/
enum TAF_XCALL_SS_PROGRESS_EVT_ENUM
{
    TAF_XCALL_SS_PROG_EVT_REL,                                                  /* �к��б��Ҷ� */

    TAF_XCALL_SS_PROG_EVT_ANS,                                                  /* �к����ڽ���*/

    TAF_XCALL_SS_PROG_EVT_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XCALL_CALL_SUB_STATE_ENUM
 �ṹ˵��  : ����ҵ���������
*****************************************************************************/
enum TAF_XCALL_SS_SUBSEQ_OP_ENUM
{
    TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC,                                            /* ��Ӧ�ò��ϱ������ɹ� */
    TAF_XCALL_SS_SUBSEQ_OP_RPT_FAIL,                                            /* ��Ӧ�ò��ϱ�����ʧ�� */

    TAF_XCALL_SS_SUBSEQ_OP_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8;

/** ****************************************************************************
 ö����    : TAF_XCALL_DIGIT_MODE_ENUM
 �ṹ˵��  : �������ģʽ
 *******************************************************************************/
enum TAF_XCALL_DIGIT_MODE_ENUM
{
    TAF_XCALL_DIGIT_MODE_DTMF           = 0x00,
    TAF_XCALL_DIGIT_MODE_ASCII          = 0x01,
    TAF_XCALL_DIGIT_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 TAF_XCALL_DIGIT_MODE_ENUM_UINT8;

/** ****************************************************************************
 ö����    : TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8
 �ṹ˵��  : ��xcc����Burst DTMF��CONT DTMF�����õȴ���־���ȴ���Ӧ������
 *******************************************************************************/
enum TAF_XCALL_WAIT_XCC_CNF_TYPE
{
    TAF_XCALL_WAIT_NO_XCC_CNF               = 0x00,     /* ��ʼ̬�����ȴ�XCC�ظ� */
    TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF       = 0x01,     /* �ȴ�XCC�ظ�BURST DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF  = 0x02,     /* �ȴ�XCC�ظ�START CONT DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF   = 0x03,     /* �ȴ�XCC�ظ�STOP CONT DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_BUFF
};
typedef VOS_UINT8 TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8;


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 ö����    : TAF_XCALL_VOICE_ENCRYPT_STA_ENUM
 ö��˵��  : �ܻ���Կ����Э�̽׶�״̬ö������
 1.��    ��   : 2015��10��22��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XCALL_VOICE_ENCRYPT_STA_ENUM
{
    TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE,                               /* �ܻ�״̬����ʼ״̬      */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ,                       /* �ȴ��û���ORIG����״̬  */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ,                 /* �ȴ��û����ܻ�����״̬  */
    TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ,                /* �ȴ��û����н���״̬    */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL,                /* �ȴ�TCH�ŵ�ָ�����״̬ */
    TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ,                 /* ��ʱ�ܻ�������״̬    */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP,                    /* �ȴ�KMC���ܻ���Ӧ״̬   */
    TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF,                /* �ȴ��ܻ���SOЭ��״̬    */
    TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE,                         /* �ܻ�����״̬            */

    TAF_XCALL_VOICE_ENCRYPT_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_XCALL_K0_UPATE_STA_ENUM
 ö��˵��  : KMC��Կ����״̬ö�ٱ�
 1.��    ��   : 2015��10��22��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XCALL_K0_UPATE_STA_ENUM
{
    TAF_XCALL_K0_UPATE_STA_INACTIVE,                                    /* KMC��Կ���³�ʼ״̬     */
    TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP,                                /* �ȴ�KMC��Կ������Ӧ״̬ */

    TAF_XCALL_K0_UPATE_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_K0_UPATE_STA_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_XCALL_REMOTE_CTRL_STA_ENUM
 ö��˵��  : KMCԶ�̿��Ʋ���״̬ö�ٱ�
 1.��    ��   : 2015��10��22��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XCALL_REMOTE_CTRL_STA_ENUM
{
    TAF_XCALL_REMOTE_CTRL_STA_INACTIVE,                                 /* Զ�̿��Ʋ�����ʼ̬             */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP,                /* �ȴ��û��İ�ȫ��Ϣ������Ӧ״̬ */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP,            /* �ȴ��û�������������Ӧ״̬     */
    TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT,                    /* �ȴ���Զ�̿�����Ӧ���ͽ��״̬ */

    TAF_XCALL_REMOTE_CTRL_STA_BUTT
};
typedef VOS_UINT32 TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32;
#endif

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
 �ṹ��    : TAF_XCALL_CLIENT_INFO_STRU
 �ṹ˵��  : X CALL����/�����û�����Ϣ
 1.��    ��   : 2014��9��03��
   ��    ��   : y00213812
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;                             /* ������в�����ģ��AT/STK */
    VOS_UINT16                          usClientId;                             /* Client ID */
    VOS_UINT8                           ucOpId;                                 /* Op ID */
    VOS_UINT8                           ucReserved;
}TAF_XCALL_CLIENT_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_XCALL_DTMF_BUFFER_STRU
�ṹ˵��  : XCALLģ�����ڱ���BURST DTMF��CONT DTMF��Ϣ
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : ������
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16 �޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDtmfCnt;          /* �����BURST DTMF��CONT DTMF��Ϣ���� */
    VOS_UINT8                           aucReserved1[3];
    HI_LIST_S                           stList;
} TAF_XCALL_DTMF_BUFFER_STRU;


/*****************************************************************************
�ṹ��    : TAF_XCALL_FLASH_INFO_STRU
�ṹ˵��  : XCALLģ�����ڱ���flash��Ϣ
  1.��    ��   : 2015��01��14��
    ��    ��   : m00312079
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    VOS_UINT8                           ucIsEmcCall;
    VOS_UINT8                           aucReserved[3];
} TAF_XCALL_FLASH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_CALL_ENTITY_STRU
 �ṹ˵��  : X CALL�ĺ���ʵ����Ϣ
             Ϊ�˱����Ժ�����CS CALL���Ż���X CALL����ʵ���еĶ��������MnCallApi.h���ж��壬�������¶���һ��
 1.��    ��   : 2014��9��03��
   ��    ��   : L60609
   �޸�����   : ����
 2.��    ��   : 2015��8��18��
   ��    ��   : l00324781
   �޸�����   : DTS2015081708770�޸�
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* �Ƿ��ѱ�ʹ�� */
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;                           /* ����/�����û�����Ϣ */

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo;
    VOS_UINT8                           ucIsAlertAnsByPass;                     /* MT */
    VOS_UINT8                           ucConRef;                               /* Connect Reference */
    VOS_UINT8                           ucConnectId;                            /* Connect Id */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* ������еķ��� */
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucIsL2ErrReOrig;
    VOS_UINT8                           ucReOrigCount;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */

    MN_CALL_DISC_DIR                    stDiscDir;                              /* �ҶϺ��еķ��� */

    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number ���к��� */
    MN_CALL_SUBADDR_STRU                stCallSubNumber;                        /* Call SubAddress */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number ���к��� */
    MN_CALL_SUBADDR_STRU                stCalledSubAddr;                        /* Called SubAddress */
    MN_CALL_BCD_NUM_STRU                stRedirectNumber;                       /* Redirect Number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Redirect Call SubAddress */
    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;                /* �ȴ�XCC��Burst DTMF��Cont Burst�ظ���Ϣ */
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;

    VOS_UINT8                           ucTchAssignInd;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode;                          /* ��ǰ���е�privacy mode */

    TAF_XCALL_DTMF_BUFFER_STRU          stDtmfBuffer;                           /* BURST DTMF��CONT DTMF�Ļ�����Ϣ,����һ������*/

    TAF_XCALL_FLASH_INFO_STRU           stFlashInfo;

    VOS_INT16                           sRssi;
    VOS_UINT16                          usReserved;
}TAF_XCALL_CALL_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_CS_ERR_CODE_MAP_STRU
 �ṹ˵��  : TAF XCAL��XCCԭ��ֵ�Ķ�Ӧ�ṹ
  1.��    ��   : 2014��9��17��
    ��    ��   : L60609
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;
}TAF_XCALL_CS_ERR_CODE_MAP_STRU;


/*****************************************************************************
 �ṹ��    : MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU
 �ṹ˵��  : ����ע�Ĳ���ҵ������¼� �ṹ
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�

****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallId;           /* �����¼��ĺ���ID */
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;              /* �¼������� */
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;         /* �յ����¼��ĺ������� */
    VOS_UINT8                                               ucRsved;
}TAF_XCALL_SUPS_CMD_KEY_EVT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_SUPS_CMD_MGMT_STRU
 �ṹ˵��  : ����ҵ�����ṹ
 1.��    ��   : 2014��9��20��
   ��    ��   : L60609
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNumOfKeyEvt;                      /* ��ע���¼����� */
    VOS_UINT8                               aucRsved[3];
    TAF_XCALL_SUPS_CMD_KEY_EVT_STRU         astKeyEvts[TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM];  /* ��ע���¼� */
}TAF_XCALL_SUPS_CMD_MGMT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_CONFIG_STRU
 �ṹ˵��  : �û�������Ϣ�ṹ
 1.��    ��   : 2014��9��20��
   ��    ��   : Y00213812
   �޸�����   : ����
 2.��    ��   : 2015��8��18��
   ��    ��   : l00324781
   �޸�����   : DTS2015081708770����NV������
*****************************************************************************/
typedef struct
{
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode;

    VOS_UINT8                           ucRsved;

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSoInitType;

    VOS_UINT32                          ulEmcRedialPeriod;      /* �������ز���ʱ��ʱ�� */
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* Stop Cont DTMF��Start Cont DTMF�����ʱ������ʱ��ʱ������λ:ms */
    VOS_UINT32                          ulCallBackEnableFlg;
}TAF_XCALL_CONFIG_STRU;

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �ṹ��    : TAF_XCALL_ECC_SRV_CAP_STRU
 �ṹ˵��  : ECC��������������Ϣ��
             ע: ECCҵ��״̬����ECCҵ������֧�ֵ�����£�����Ч��

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEccSrvCap;        /* ECC��������: TRUE -- ֧��ECC����FALSE -- ��֧��ECC���� */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC����״̬: TRUE -- ECC����򿪣�FALSE -- ECC����ر� */
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_ECC_SRV_CAP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_ECC_PUB_KEY_INFO_STRU
 �ṹ˵��  : ECC��Կ��Ϣ��������ԿK0�Լ���Ӧ�İ汾��

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
}TAF_XCALL_ECC_PUB_KEY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_KS_INFO_STRU
 �ṹ˵��  : KS��Ϣ��������ԿKS�Լ�KS����

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKsLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucKs[TAF_XCALL_ECC_KS_DATA_MAX_LEN];
}TAF_XCALL_KS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_ENCRYPT_VOICE_DATA_CTX
 �ṹ˵��  : �ܻ���ص����������Ľṹ����

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usDelayEncVoiceReqTimerLen;             /* ��ʱ�ܻ�������ʱ�� */
    VOS_UINT16                                              usRemoteCtrlAnswerTimerLen;             /* Զ�̿���Ӧ��ʱ�� */
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                         stEccSrvCapInfo;                        /* ECC����������Ϣ */
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                         stEccPubKeyInfo;                        /* ECC��Կ��Ϣ */
    TAF_STD_TIME_ZONE_TYPE_STRU                             stLastInfoEraseTime;                    /* ECC��ȫ��Ϣ����ʱ�� */
    TAF_STD_TIME_ZONE_TYPE_STRU                             stLastPassworResetTime;                 /* ECC�������ò���ʱ�� */
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode;                             /* ��ǰ����ģʽ*/
}TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_KS_NEGOTIATE_CTX
 �ṹ˵��  : �ܻ���KSЭ�̹����е����������ݶ���

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enVoiceEncState;                        /* �ܻ�����ԿЭ�̹����е�״̬ */
    TAF_XCALL_KMC_PUB_KEY_STRU                              stTmpPubKey;                            /* ��ʱ��Կ */
    TAF_XCALL_KMC_PRIV_KEY_STRU                             stTmpPrivKey;                           /* ��ʱ˽Կ */
    TAF_ECC_CALL_BCD_NUM_STRU                               stCallNum;
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType;
    TAF_XCALL_KS_INFO_STRU                                  stKsInfo;                               /* KS���� */
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    VOS_UINT8                                               ucCallId;                               /* ��¼��ǰ����call id��ʶ */
    VOS_UINT8                                               aucReserved[1];
    TAF_CCA_CTRL_STRU                                       stCcaCtrl;
}TAF_XCALL_KS_NEGOTIATE_CTX;


/*****************************************************************************
 �ṹ��    : TAF_XCALL_REMOTE_CTRL_CTX
 �ṹ˵��  : KMCԶ�̿��������е������Ķ���

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enRemoteCtrlState;
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType;
    VOS_UINT8                                               ucReserved;
    TAF_STD_TIME_ZONE_TYPE_STRU                             stTimeStamp;
    TAF_CCA_CTRL_STRU                                       stCcaCtrl;
}TAF_XCALL_REMOTE_CTRL_CTX;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_PUBLIC_KEY_UPDATE_CTX
 �ṹ˵��  : KMC��Կ���������е������Ķ���
 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enK0UpdateState;    /*  */
    VOS_UINT16                                              usWaitXsmsCnfOpId;
    VOS_UINT8                                               ucPubKeyVerNum;
    VOS_UINT8                                               aucPubKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
    VOS_UINT8                                               aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
    VOS_UINT8                                               ucReserved;
}TAF_XCALL_PUBLIC_KEY_UPDATE_CTX;


/*****************************************************************************
 �ṹ��    : TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX_STRU
 �ṹ˵��  : ���ŷ�������OPID������������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOpIdSeqNum;                         /* opId���к� */
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_ENC_VOICE_CTX_STRU
 �ṹ˵��  : �����������������ݽṹ

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX                   stOpIdMgmtCtx;      /* OPID���������Ķ��� */
    TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX                   stEncVoiceInfoCtx;  /* �ܻ�������Ϣ�����Ķ��� */
    TAF_XCALL_KS_NEGOTIATE_CTX                              stNegotiateCtx;     /* �ܻ�KSЭ�������е������� */
    TAF_XCALL_REMOTE_CTRL_CTX                               stRemoteCtrlCtx;    /* KMCԶ�̿��������е������� */
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                         stPubKeyUpdateCtx;  /* ��Կ���������е������� */
}TAF_XCALL_ENCRYPT_VOICE_CTX_STRU;
#endif

/*****************************************************************************
 �ṹ��    : TAF_XCALL_CTX_STRU
 �ṹ˵��  : X CALL����������Ϣ
 1.��    ��   : 2014��9��09��
   ��    ��   : L60609
   �޸�����   : ����
 2.��    ��   : 2014��11��17��
   ��    ��   : w00176964
   �޸�����   : 1X����5����
 3.��    ��   : 2015��10��22��
   ��    ��   : y00245242
   �޸�����   : 1X����19����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
    TAF_XCALL_CONFIG_STRU               stConfig;
    TAF_XCALL_TIMER_CTX_STRU            astTimerCtx[TAF_XCALL_MAX_TIMER_ID_NUM];

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ENCRYPT_VOICE_CTX_STRU    stEncVoiceCtx;
#endif
}TAF_XCALL_CTX_STRU;


/*****************************************************************************
�ṹ��    : TAF_XCALL_DTMF_NODE_UNION
�ṹ˵��  : CALLģ��DTMF������Ϣ���ݽṹ������Cont DTMF��Burst DTMF
1.��    ��   : 2015��7��29��
  ��    ��   : l00324781
  �޸�����   : Iter16����

*****************************************************************************/
typedef union
{
    TAF_CALL_BURST_DTMF_PARA_STRU   stBurstDtmf;
    TAF_CALL_CONT_DTMF_PARA_STRU    stContDtmf;
}TAF_XCALL_DTMF_NODE_UNION;

/*****************************************************************************
�ṹ��    : TAF_XCALL_DTMF_NODE_STRU
�ṹ˵��  : CALLģ��DTMF��������ڵ�ṹ������Cont DTMF��Burst DTMF
1.��    ��   : 2015��7��29��
  ��    ��   : l00324781
  �޸�����   : Iter16����

*****************************************************************************/
typedef struct
{
    TAF_XCALL_DTMF_NODE_UNION                    unDtmf;        /* ����Buffer,Burst DTMF��CONT DTMF */
    AT_MN_MSGTYPE_ENUM_UINT16                    enMsgType;     /* �������Ϣ���� */
    VOS_UINT8                                    aucRsved[2];
    HI_LIST_S                                    stList;
} TAF_XCALL_DTMF_NODE_STRU;

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
TAF_XCALL_CTX_STRU* TAF_XCALL_GetCtxAddr(VOS_VOID);

VOS_VOID TAF_XCALL_InitCtx(VOS_VOID);

VOS_UINT32 TAF_XCALL_AllocCallId(
    VOS_UINT8                      *pucCallId
);

VOS_UINT32 TAF_XCALL_IsAllowMoCallInCurrentStatus(
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID TAF_XCALL_CreateMoCallEntity(
    VOS_UINT8                           ucCallId,
    MN_CALL_APP_REQ_MSG_STRU           *pstOrigPara
);

VOS_VOID TAF_XCALL_CreateMtCallEntity(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
);

VOS_VOID TAF_XCALL_FreeCallEntity(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailCallId(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailVoiceCallSo(
    VOS_UINT16                          usSo
);

VOS_VOID TAF_XCALL_UpdateCallState(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_XCALL_UpdateCallType(
    VOS_UINT8                           ucCallId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

VOS_VOID TAF_XCALL_UpdateCallDir(
    VOS_UINT8                           ucCallId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

VOS_VOID TAF_XCALL_UpdateSo(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
);

VOS_VOID TAF_XCALL_UpdateConnectId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_XCALL_UpdateConnectRef(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef
);

VOS_VOID TAF_XCALL_UpdateAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsAlertAnsByPass
);

VOS_VOID TAF_XCALL_UpdateCcCause(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCcCause
);

VOS_VOID TAF_XCALL_UpdateDiscCallDir(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID TAF_XCALL_UpdateCallingNum(
    VOS_UINT8                                               ucCallId,
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
);

TAF_XCALL_SUPS_CMD_MGMT_STRU* TAF_XCALL_GetSupsCmdMgmt(VOS_VOID);

TAF_XCALL_CLIENT_INFO_STRU* TAF_XCALL_GetClientInfo(
    VOS_UINT8                           ucCallId
);

TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_GetSo(
    VOS_UINT8                           ucCallId
);

MN_CALL_STATE_ENUM_U8 TAF_XCALL_GetCallState(
    VOS_UINT8                           ucCallId
);

MN_CALL_TYPE_ENUM_U8 TAF_XCALL_GetCallType(
    VOS_UINT8                           ucCallId
);

VOS_UINT8 TAF_XCALL_GetAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_GetCcCause(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_GetCallIdFromConnectId(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID TAF_XCALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_GetNotIdleStateCalls(
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_UpdateClientInfo(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

TAF_XCALL_CALL_ENTITY_STRU* TAF_XCALL_GetCallEntityAddr(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_MapXccCauseToCsCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
);

VOS_UINT32 TAF_XCALL_ExistCallInstance(VOS_VOID);

VOS_VOID TAF_XCALL_RegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
);

VOS_VOID TAF_XCALL_DeRegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
);


VOS_VOID TAF_XCALL_GetSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                   *penEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                      *penSubseqOp
);

VOS_VOID TAF_XCALL_UpdateDigitMode(
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
);

TAF_XCALL_CONFIG_STRU* TAF_XCALL_GetConfigInfo(VOS_VOID);

VOS_VOID TAF_XCALL_SetWaitForXCCDTMFCnfFlag(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
);

TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8 TAF_XCALL_GetWaitForXCCDTMFCnfFlag(
    VOS_UINT8       ucCallId
);

VOS_UINT32 TAF_XCALL_IsMtCallInstanceExist(VOS_VOID);

TAF_XCALL_TIMER_CTX_STRU*  TAF_XCALL_GetTimerCtxAddr( VOS_VOID );

MN_CALL_DIR_ENUM_U8 TAF_XCALL_GetCallDir(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_TranlatePlusToCallNum(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);

#if 0
VOS_VOID TAF_XCALL_TranlateCallNumToPlus(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);
#endif


VOS_VOID TAF_XCALL_GetEccNumList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
);

/*  �޸�����:
   1. Buffer����������XCallProcAppŲ��XCallCtx.c��
   2. Cont DTMF��Burst DTMF����һ������
*/

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern VOS_VOID TAF_XCALL_ProcDtmfBuffer(VOS_UINT8 ucCallId);

extern VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
);

extern HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8   ucCallId);





TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);

TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);


VOS_UINT32 TAF_XCALL_GetStartAndStopContDtmfIntervalLen(VOS_VOID);

VOS_UINT32 TAF_XCALL_GetAllUsedCallId(
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_InitEncVoiceCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceKeyNegotiateCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceRemoteCtrlCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceOpIdMgmtCtx(VOS_VOID);

VOS_VOID TAF_XCALL_InitEncVoiceParaInfoCtx(VOS_VOID);

TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX* TAF_XCALL_GetEncVoiceInfoCtxAddr(VOS_VOID);

TAF_XCALL_ENCRYPT_VOICE_CTX_STRU* TAF_XCALL_GetVoiceEncryptCtxAddr(VOS_VOID);

TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX* TAF_XCALL_GetOpIdMgmtCtxAddr(VOS_VOID);

TAF_XCALL_REMOTE_CTRL_CTX* TAF_XCALL_GetRemoteCtrlCtxAddr(VOS_VOID);

TAF_XCALL_KS_NEGOTIATE_CTX* TAF_XCALL_GetKsNegotiateCtxAddr(VOS_VOID);

TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptNegotiateState(VOS_VOID);

TAF_XCALL_ECC_PUB_KEY_INFO_STRU* TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber( VOS_VOID );

TAF_XCALL_ECC_SRV_CAP_INFO_STRU* TAF_XCALL_GetVoiceEncryptCapCfgPara( VOS_VOID );

TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime( VOS_VOID );

TAF_STD_TIME_ZONE_TYPE_STRU* TAF_XCALL_GetVoiceEncryptPassWordResetSysTime( VOS_VOID );

VOS_UINT16 TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen( VOS_VOID );

VOS_UINT16 TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen(VOS_VOID);

TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32 TAF_XCALL_GetVoiceEncryptTestMode( VOS_VOID );

TAF_XCALL_PUBLIC_KEY_UPDATE_CTX* TAF_XCALL_GetPubKeyUpdateCtxAddr( VOS_VOID );

VOS_VOID TAF_XCALL_InitEncVoiceKmcUpdateCtx(VOS_VOID);
#endif
VOS_VOID TAF_XCALL_UpdatePrivacyMode(
    VOS_UINT8                           ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyMode
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

#endif /* end of TafXCallCtx.h */


