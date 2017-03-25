/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hids_elf_taf.h
  �� �� ��   : ����
  ��    ��   : h00360002
  ��������   : 2015��12��03��
  ��������   : TAF��elf�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��03��
    ��    ��   : h00360002
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallApi.h"
#include "MnMsgApi.h"
#include "TafAppSsa.h"
#include "TafAppMma.h"
#include "TafApsApi.h"
#include "PsTypeDef.h"
#include "AtInternalMsg.h"
#include "AtCmdMsgProc.h"
#include "AtTimer.h"
#include "TafDrvAgent.h"
#include "AtRabmInterface.h"
#include "PppInterface.h"
#include "AtDipcInterface.h"
#include "AtMtaInterface.h"
#include "TafMtaAgps.h"
#include "AtImsaInterface.h"
#include "TafAppXsmsInterface.h"
#include "AtNdisInterface.h"
#include "MtaRrcInterface.h"
#include "MtaPhyInterface.h"
#include "omerrorlog.h"
#include "TafMtaTimerMgmt.h"
#include "MtcMmaInterface.h"
#include "MtcRrcInterface.h"
#include "MtaMtcInterface.h"
#include "MtcGmmInterface.h"
#include "MtcDebug.h"
#include "MtcRcmInterface.h"
#include "PsRrmInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifndef MN_ELF_APP_REQ_MSG_STRU
#define MN_ELF_APP_REQ_MSG_STRU         VOS_MSG_HEADER                        \
                                        VOS_UINT16           usMsgName;       \
                                        VOS_UINT8            aucReserve1[2];  \
                                        MN_CLIENT_ID_T       clientId;        \
                                        MN_OPERATION_ID_T    opId;            \
                                        VOS_UINT8            aucReserve2[1];
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_ELF_PH_PIN_CMD_TYPE
 ö��˵��  : TAF_PH_PIN_CMD_TYPE����ö��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum TAF_ELF_PH_PIN_CMD_TYPE
{
    ELF_TAF_PIN_CMD_NULL    = 0x00,
    ELF_TAF_PIN_VERIFY      = 0x20,         /*У��PIN��*/
    ELF_TAF_PIN_CHANGE      = 0x24,         /*����PIN�������*/
    ELF_TAF_PIN_DISABLE     = 0x26,         /*��ֹʹ��PIN��*/
    ELF_TAF_PIN_ENABLE      = 0x28,         /*ʹ��PIN��*/
    ELF_TAF_PIN_UNBLOCK     = 0x2c,         /*�����ֹPIN��*/
    ELF_TAF_PIN_QUERY       = 0x30,         /*��ѯPIN��״̬*/
    ELF_TAF_PIN_RemainTime  = 0x31,
    ELF_TAF_PIN2_QUERY      = 0x32,         /*��ѯPIN2��״̬*/
};
typedef VOS_UINT8   TAF_ELF_PH_PIN_CMD_TYPE_UINT8;

/*****************************************************************************
 ö����    : TAF_ELF_PH_PIN_TYPE
 ö��˵��  : TAF_PH_PIN_TYPE����ö��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum TAF_ELF_PH_PIN_TYPE
{
    ELF_TAF_SIM_PIN         = 0,            /*PIN1*/
    ELF_TAF_SIM_PUK         = 1,            /*PUK1*/
    ELF_TAF_SIM_PIN2        = 6,            /*PIN2*/
    ELF_TAF_SIM_PUK2        = 7,            /*PUK2*/
    ELF_TAF_PHSIM_PIN       = 8,            /*PH-SIM PIN*/
    ELF_TAF_PHNET_PIN       = 9,            /*PH-NET PIN*/
    ELF_TAF_PHNET_PUK       = 10,           /*PH-NET PUK*/
    ELF_TAF_PHNETSUB_PIN    = 11,           /*PH-NETSUB PIN*/
    ELF_TAF_PHNETSUB_PUK    = 12,           /*PH-NETSUB PUK*/
    ELF_TAF_PHSP_PIN        = 13,           /*PH-SP PIN*/
    ELF_TAF_PHSP_PUK        = 14,           /*PH-SP PUK*/
    ELF_TAF_SIM_NON         = 255,          /*��ȷ������PIN������ʱ�����ֵ*/
};
typedef VOS_UINT8   TAF_ELF_PH_PIN_TYPE_UINT8;

/*****************************************************************************
 ö����    : TAF_ELF_ME_PERSONALISATION_CMD_TYPE
 ö��˵��  : TAF_ME_PERSONALISATION_CMD_TYPE����ö��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum TAF_ELF_ME_PERSONALISATION_CMD_TYPE
{
    ELF_TAF_ME_PERSONALISATION_SET          = 0X01,     /*�ƶ��豸˽����������*/
    ELF_TAF_ME_PERSONALISATION_VERIFY       = 0X02,     /*�ƶ��豸˽������У��*/
    ELF_TAF_ME_PERSONALISATION_PWD_CHANGE   = 0X03,     /*�����ƶ��豸˽������*/
    ELF_TAF_ME_PERSONALISATION_ACTIVE       = 0X04,     /*�����ƶ��豸˽�й���*/
    ELF_TAF_ME_PERSONALISATION_DEACTIVE     = 0X05,     /*ȥ�����ƶ��豸˽�й���*/
    ELF_TAF_ME_PERSONALISATION_RETRIEVE     = 0X06,     /*��ȡ��ǰ�ƶ��豸˽�������б�*/
    ELF_TAF_ME_PERSONALISATION_QUERY        = 0X07,     /*��ѯ��ǰ�ƶ��豸˽������״̬*/
};
typedef VOS_UINT8   TAF_ELF_ME_PERSONALISATION_CMD_TYPE_UINT8;

/*****************************************************************************
 ö����    : TAF_ELF_ME_PERSONALISATION_TYPE
 ö��˵��  : TAF_ME_PERSONALISATION_TYPE����ö��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum TAF_ELF_ME_PERSONALISATION_TYPE
{
    ELF_TAF_SIM_PERSONALISATION                 = 0x01, /*����*/
    ELF_TAF_NETWORK_PERSONALISATION             = 0x02, /*������*/
    ELF_TAF_NETWORK_SUBSET_PERSONALISATION      = 0x03, /*�������Ӽ�*/
    ELF_TAF_SERVICE_PROVIDE_PERSONALISATION     = 0x04, /*��ҵ��Ӧ��*/
    ELF_TAF_CORPORATE_PERSONALISATION           = 0x05, /*����˾**/
    ELF_TAF_OPERATOR_PERSONALISATION            = 0x06, /*�Զ���:������,�����ն�����ʵ�� */
};
typedef VOS_UINT8   TAF_ELF_ME_PERSONALISATION_TYPE_UINT8;

/*****************************************************************************
 ö����    : TAF_ELF_PH_ICC_TYPE
 ö��˵��  : TAF_PH_ICC_TYPE����ö��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum TAF_ELF_PH_ICC_TYPE
{
    ELF_TAF_PH_ICC_UNKNOW       = 0,
    ELF_TAF_PH_ICC_SIM          = 1,
    ELF_TAF_PH_ICC_USIM         = 2,
};
typedef VOS_UINT8   TAF_ELF_PH_ICC_TYPE_UINT8;

/*****************************************************************************
 ö����    : OM_ELF_MTA_MSG_TYPE_ENUM
 ö��˵��  : OM��MTA�����Ϣ����ö��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum OM_ELF_MTA_MSG_TYPE_ENUM
{
    ELF_ID_OM_ERR_LOG_CTRL_IND      = 0x9001,
    ELF_ID_OM_ERR_LOG_REPORT_REQ    = 0x9002,
    ELF_ID_OM_ERR_LOG_REPORT_CNF    = 0x9003,
    ELF_ID_OM_FTM_CTRL_IND          = 0x9004,
    ELF_ID_OM_FTM_REPROT_IND        = 0x9005,
    ELF_ID_OM_INFO_CLT_REPORT_REQ   = 0x9010,
    ELF_ID_OM_INFO_CLT_REPORT_CNF   = 0x9011,
};
typedef VOS_UINT32   OM_ELF_MTA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : OM_ELF_ERR_LOG_ALM_STATUS_ENUM
 ö��˵��  : OM ERROR LOG�ϱ����ƿ���ö��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum OM_ELF_ERR_LOG_ALM_STATUS_ENUM
{
    ELF_OM_ERR_LOG_ALM_OFF,
    ELF_OM_ERR_LOG_ALM_ON,
    ELF_OM_ERR_LOG_ALM_BUTT
};
typedef VOS_UINT8   OM_ELF_ERR_LOG_ALM_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : OM_ELF_ERR_LOG_ALM_STATUS_ENUM
 ö��˵��  : OM ERROR LOG�ϱ�����ö��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM
{
    ELF_OM_ERR_LOG_CTRL_LEVEL_NULL,
    ELF_OM_ERR_LOG_CTRL_LEVEL_CRITICAL,
    ELF_OM_ERR_LOG_CTRL_LEVEL_MAJOR,
    ELF_OM_ERR_LOG_CTRL_LEVEL_MINOR,
    ELF_OM_ERR_LOG_CTRL_LEVEL_WARNING
};
typedef VOS_UINT8   OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM_UINT8;
typedef VOS_UINT16   OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : OM_ELF_FTM_CTRL_STATUS_ENUM
 ö��˵��  : ����ģʽ�����ϱ����ƿ���ö��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
enum OM_ELF_FTM_CTRL_STATUS_ENUM
{
    ELF_OM_FTM_CTRL_OFF,
    ELF_OM_FTM_CTRL_ON,
    ELF_OM_FTM_CTRL_BUTT
};
typedef VOS_UINT8   OM_ELF_FTM_CTRL_STATUS_ENUM_UINT8;

/*****************************************************************************
  4 �ṹ�嶨��
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_ELF_NULL_STRU
 �ṹ˵��  : ���ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucReserve[4];
}TAF_ELF_NULL_STRU;



/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_INFO_QRY_CNF_STRU
 �ṹ˵��  :  AT��MN Callģ����ȡCall��Ϣ����Ϣ�ṹ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      clientId;                               /* �û�ID */
    VOS_UINT8                           ucNumOfCalls;                           /* ��������ͨ���ĸ��� */
    VOS_CHAR                            ucReserved;                             /* �����ֶ� */
    MN_CALL_INFO_PARAM_STRU             astCallInfos[MN_CALL_MAX_NUM];           /* ��������ͨ������Ϣ */
} MN_CALL_ELF_INFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_PH_ELF_SET_UUS1_INFO_CNF_STRU
 �ṹ˵��  :  ����UUS1 INFO�ظ���Ϣ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T          ClientId;   /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;       /*����ID*/
    VOS_UINT8               ucReserved; /* �����ֶ� */
    VOS_UINT32              ulRet;      /*�ظ����*/
}TAF_PH_ELF_SET_UUS1_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_PH_ELF_QRY_UUS1_INFO_CNF_STRU
 �ṹ˵��  :  ��ѯUUS1 INFO�ظ���Ϣ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T          ClientId;                               /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;                                   /*����ID*/
    VOS_UINT8               ucReserved;                             /* �����ֶ� */
    VOS_UINT32              ulRet;                                  /*�ظ����*/
    VOS_UINT32              ulActNum;                               /*�û���������1�ĸ���*/
    MN_CALL_UUS1_INFO_STRU  stUus1Info[MN_CALL_MAX_UUS1_MSG_NUM];   /*�û���������1����Ϣ*/
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      aenSetType[MN_CALL_MAX_UUS1_MSG_NUM];  /*Ҫ���õ��û���������1���� */
}TAF_PH_ELF_QRY_UUS1_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_SET_ALS_CNF_STRU
 �ṹ˵��  :  ����ALS�ظ���Ϣ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T          ClientId;   /*�˿ں�*/
    MN_OPERATION_ID_T       OpId;       /*����ID*/
    VOS_UINT8               ucReserved; /* �����ֶ� */
    VOS_UINT32              ulRet;      /*�ظ����*/
}MN_CALL_ELF_SET_ALS_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_QRY_ALS_CNF_STRU
 �ṹ˵��  :  AT��CS AT^ALS�����ѯ�ṹ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                  ClientId;                                   /*�˿ں�*/
    MN_OPERATION_ID_T               OpId;                                       /*����ID*/
    VOS_UINT8                       ucReserved1;                                /* �����ֶ� */
    VOS_UINT32                      ulRet;                                      /*�ظ����*/
    MN_CALL_ALS_LINE_NO_ENUM_U8     enAlsLine;                                  /*��ǰʹ�õ���·��*/
    VOS_UINT8                       aucReserved2[3];                            /* �����ֶ� */
}MN_CALL_ELF_QRY_ALS_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_ECC_NUM_INFO_STRU
 �ṹ˵��  :  CALL��AT�ϱ���ǰ���еĽ����������б��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulEccNumCount;
    MN_CALL_CUSTOM_ECC_NUM_STRU         astCustomEccNumList[MN_CALL_MAX_EMC_NUM];
} MN_CALL_ELF_ECC_NUM_INFO_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_EVT_HOLD_STRU
 �ṹ˵��  :  ���б����¼��ϱ��ṹ���ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucCallId[MN_CALL_MAX_NUM];
    VOS_UINT8                           aucCurcRptCfg[MN_CALL_RPT_CFG_MAX_SIZE];        /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                           aucUnsolicitedRptCfg[MN_CALL_RPT_CFG_MAX_SIZE]; /* �����������õ������ϱ���ʶ */
} MN_CALL_ELF_EVT_HOLD_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_EVT_RETRIEVE_STRU
 �ṹ˵��  :  ���б����¼��ϱ��ṹ���ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucCallId[MN_CALL_MAX_NUM];
    VOS_UINT8                           aucCurcRptCfg[MN_CALL_RPT_CFG_MAX_SIZE];        /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                           aucUnsolicitedRptCfg[MN_CALL_RPT_CFG_MAX_SIZE]; /* �����������õ������ϱ���ʶ */
} MN_CALL_ELF_EVT_RETRIEVE_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_CLPR_GET_CNF_STRU
 �ṹ˵��  :  ��ѯ����Դ����ظ������ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRet;
    AT_APPCTRL_STRU                     stAppCtrl;
    MN_CALL_REDIRECT_INFO               stRedirectInfo;
}MN_CALL_ELF_CLPR_GET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_EVT_CHANNEL_INFO_STRU
 �ṹ˵��  :  MN_CALL_EVT_CHANNEL_INFO_IND�¼���ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;

    VOS_UINT8                           ucIsLocalAlertingFlag;                  /* �Ƿ�Ϊ���ز��Ż�������ʶ1:���ز��Ż�������0:�������*/
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */

    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain;                          /* VOICE DOMAIN */
    VOS_UINT8                           aucRsv[3];
} MN_CALL_ELF_EVT_CHANNEL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_SET_CSSN_CNF_STRU
 �ṹ˵��  :  MN_CALL_EVT_SET_CSSN_CNF�¼��ṹ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_ERROR_CODE_ENUM_UINT32          ulRet;          /*�ظ����*/
    MN_CLIENT_ID_T                      ClientId;       /*�˿ں�*/
    MN_OPERATION_ID_T                   OpId;           /*����ID*/
    VOS_UINT8                           ucReserved;     /* �����ֶ� */
} MN_CALL_ELF_SET_CSSN_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_MODIFY_CNF_STRU
 �ṹ˵��  :  Modify�ظ���Ϣ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;                             /* �˿ں� */
    MN_OPERATION_ID_T                   ucOpId;                                 /* ����ID */
    MN_CALL_ID_T                        ucCallId;                               /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* ������ */
}MN_CALL_ELF_MODIFY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_EVT_MODIFY_STATUS_IND_STRU
 �ṹ˵��  :  Modify״ָ̬ʾ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;                     /* ����ID */
    MN_CALL_ID_T                                    ucCallId;                   /* Call ID */
    MN_CALL_MODIFY_STATUS_ENUM_UINT8                enModifyStatus;             /* ��ǰ��MODIFY�Ĺ���״̬ */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8                enVoiceDomain;              /* VOICE DOMAIN������ʼ����IMS�� */
    MN_CALL_TYPE_ENUM_U8                            enCurrCallType;             /* ��ǰ�������� */
    MN_CALL_TYPE_ENUM_U8                            enExpectCallType;           /* ������������ */
    TAF_CS_CAUSE_ENUM_UINT32                        enCause;                    /* �����룬����MODIFY_PROC_END���쳣ʱ��ʹ�� */
} MN_CALL_ELF_EVT_MODIFY_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_CALL_ELF_ECONF_DIAL_CNF_STRU
 �ṹ˵��  :  Modify�ظ���Ϣ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;                             /* �˿ں� */
    MN_OPERATION_ID_T                   ucOpId;                                 /* ����ID */
    MN_CALL_ID_T                        ucCallId;                               /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* ������ */
}TAF_CALL_ELF_ECONF_DIAL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_CALL_ELF_EVT_ECONF_NOTIFY_IND_STRU
 �ṹ˵��  :  ��ǿ�ͻ����״ָ̬ʾ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;                     /* ����ID */
    VOS_UINT8                                       ucNumOfCalls;               /* ��������ͨ���ĸ��� */
    TAF_CALL_ECONF_INFO_PARAM_STRU                  astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* ��������ͨ������Ϣ */
} TAF_CALL_ELF_EVT_ECONF_NOTIFY_IND_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_CALL_ELF_ECONF_INFO_QRY_CNF_STRU
 �ṹ˵��  :  AT��MN Callģ����ȡ��ǿ�Ͷ෽ͨ����Ϣ����Ϣ�ṹ��ȥ�¼����ͺ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                                          usClientId;         /* �û�ID */
    VOS_UINT8                                               ucNumOfMaxCalls;
    VOS_UINT8                                               ucNumOfCalls;       /* �෽ͨ������߸��� */
    TAF_CALL_ECONF_INFO_PARAM_STRU                          astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* ��������ͨ������Ϣ */
}TAF_CALL_ELF_ECONF_INFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_AT_ELF_MN_CALLBACK_CS_CALL_STRU
 �ṹ˵��  :  ��TAF����AT��MN_CALLBACK_CS_CALL��Ϣ��Ӧ�Ľṹ��
 1.��    ��   : 2015��12��03��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                      usMsgName;                              /* ��Ϣ�� */
    VOS_UINT8                                       aucReserved1[2];
    MN_CLIENT_ID_T                                  clientId;
    VOS_UINT16                                      usLen;
    MN_CALL_EVENT_ENUM_U32                          enUnionStructSelChoice;
    union
    {
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_ORIG;                 /* 0x00 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_CALL_PROC;            /* 0x01 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_ALERTING;             /* 0x02 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_CONNECT;              /* 0x03 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_RELEASED;             /* 0x04 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_INCOMING;             /* 0x05 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_SS_CMD_PROGRESS;      /* 0x06 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_SS_CMD_RSLT;          /* 0x07 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_SS_NOTIFY;            /* 0x08 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_START_DTMF_CNF;       /* 0x09 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_NULL1;                /* �޴���Ϣ,ռλ */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_STOP_DTMF_CNF;        /* 0x0b */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_NULL2;                /* �޴���Ϣ,ռλ */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_CCBS_POSSIBLE;        /* 0x0d */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_TIME_EXPIRED;         /* 0x0e */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_UUS1_INFO;            /* 0x0f */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_GET_CDUR_CNF;         /* 0x10 */
        MN_CALL_ELF_INFO_QRY_CNF_STRU               stMN_CALL_EVT_CLCC_INFO;            /* 0x11 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_ALL_RELEASED;         /* 0x12 */
        TAF_PH_ELF_SET_UUS1_INFO_CNF_STRU           stMN_CALL_EVT_SET_UUS1_INFO_CNF;    /* 0x13 */
        TAF_PH_ELF_QRY_UUS1_INFO_CNF_STRU           stMN_CALL_EVT_QRY_UUS1_INFO_CNF;    /* 0x14 */
        MN_CALL_ELF_SET_ALS_CNF_STRU                stMN_CALL_EVT_SET_ALS_CNF;          /* 0x15 */
        MN_CALL_ELF_QRY_ALS_CNF_STRU                stMN_CALL_EVT_QRY_ALS_CNF;          /* 0x16 */
        MN_CALL_ELF_ECC_NUM_INFO_STRU               stMN_CALL_EVT_ECC_NUM_IND;          /* 0x17 */
        MN_CALL_ELF_EVT_HOLD_STRU                   stMN_CALL_EVT_HOLD;                 /* 0x18 */
        MN_CALL_ELF_EVT_RETRIEVE_STRU               stMN_CALL_EVT_RETRIEVE;             /* 0x19 */
        MN_CALL_ELF_CLPR_GET_CNF_STRU               stMN_CALL_EVT_CLPR_SET_CNF;         /* 0x1a */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_NULL3;                /* �޴���Ϣ,ռλ */
        MN_CALL_ELF_EVT_CHANNEL_INFO_STRU           stMN_CALL_EVT_CHANNEL_INFO_IND;     /* 0x1c */
        MN_CALL_ELF_ECC_NUM_INFO_STRU               stMN_CALL_EVT_XLEMA_CNF;            /* 0x1d */
        MN_CALL_ELF_SET_CSSN_CNF_STRU               stMN_CALL_EVT_SET_CSSN_CNF;         /* 0x1e */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_CALL_ORIG_CNF;        /* 0x1f */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_SUPS_CMD_CNF;         /* 0x20 */
        MN_CALL_INFO_STRU                           stMN_CALL_EVT_NULL4;                /* �޴���Ϣ,ռλ */
        TAF_CALL_EVT_DTMF_CNF_STRU                  stMN_CALL_EVT_START_DTMF_RSLT;      /* 0x22 */
        TAF_CALL_EVT_DTMF_CNF_STRU                  stMN_CALL_EVT_STOP_DTMF_RSLT;       /* 0x23 */
        MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU         stMN_CALL_EVT_QRY_ECALL_INFO_CNF;   /* 0x24 */
        MN_CALL_ELF_MODIFY_CNF_STRU                 stMN_CALL_EVT_CALL_MODIFY_CNF;      /* 0x25 */
        MN_CALL_ELF_MODIFY_CNF_STRU                 stMN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF;    /* 0x26 */
        MN_CALL_ELF_EVT_MODIFY_STATUS_IND_STRU      stMN_CALL_EVT_CALL_MODIFY_STATUS_IND;           /* 0x27 */
        TAF_CALL_EVT_SEND_FLASH_RSLT_STRU           stTAF_CALL_EVT_SEND_FLASH_RSLT;     /* 0x28 */
        TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU       stTAF_CALL_EVT_CALLED_NUM_INFO_IND; /* 0x29 */
        TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU      stTAF_CALL_EVT_CALLING_NUM_INFO_IND;/* 0x2a */
        TAF_CALL_EVT_DISPLAY_INFO_IND_STRU          stTAF_CALL_EVT_DISPLAY_INFO_IND;    /* 0x2b */
        TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU      stTAF_CALL_EVT_EXT_DISPLAY_INFO_IND;/* 0x2c */
        TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU         stTAF_CALL_EVT_CONN_NUM_INFO_IND;   /* 0x2d */
        TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU        stTAF_CALL_EVT_REDIR_NUM_INFO_IND;  /* 0x2e */
        TAF_CALL_EVT_SIGNAL_INFO_IND_STRU           stTAF_CALL_EVT_SIGNAL_INFO_IND;     /* 0x2f */
        TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU        stTAF_CALL_EVT_LINE_CTRL_INFO_IND;  /* 0x30 */
        TAF_CALL_EVT_CALL_WAITING_IND_STRU          stTAF_CALL_EVT_CALL_WAITING_IND;    /* 0x31 */
        TAF_CALL_ELF_ECONF_DIAL_CNF_STRU            stTAF_CALL_ECONF_DIAL_CNF;          /* 0x32 */
        TAF_CALL_ELF_EVT_ECONF_NOTIFY_IND_STRU      stTAF_CALL_EVT_ECONF_NOTIFY_IND;    /* 0x33 */
        TAF_CALL_ELF_ECONF_INFO_QRY_CNF_STRU        stTAF_CALL_EVT_CLCCECONF_INFO;      /* 0x34 */
        TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU       stTAF_CALL_EVT_SEND_BURST_DTMF_CNF; /* 0x35 */
        TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU      stTAF_CALL_EVT_SEND_BURST_DTMF_RSLT;/* 0x36 */
        TAF_CALL_EVT_CCWAC_INFO_IND_STRU            stTAF_CALL_EVT_CCWAC_INFO_IND;      /* 0x37 */
        TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU        stTAF_CALL_EVT_SEND_CONT_DTMF_CNF;  /* 0x38 */
        TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU       stTAF_CALL_EVT_SEND_CONT_DTMF_RSLT; /* 0x39 */
        TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU         stTAF_CALL_EVT_RCV_CONT_DTMF_IND;   /* 0x3a */
        TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU        stTAF_CALL_EVT_RCV_BURST_DTMF_IND;  /* 0x3b */
        TAF_CALL_EVT_CCLPR_GET_CNF_STRU             stTAF_CALL_EVT_CCLPR_GET_CNF;       /* 0x3c */
    }u;

}TAF_AT_ELF_MN_CALLBACK_CS_CALL_STRU;

/*****************************************************************************
 �ṹ��    : ID_AT_IMSA_CIREG_SET_REQ_ELF_STRU
 �ṹ˵��  : ID_AT_IMSA_CIREG_SET_REQ��Ϣ��Ӧ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_MSG_TYPE_ENUM_UINT32                    usMsgName;                              /* ��Ϣ�� */
    MN_CLIENT_ID_T                                  clientId;                               /* Client ID */
    MN_OPERATION_ID_T                               opId;                                   /* Operation ID */
    VOS_UINT8                                       aucReserve2[1];                         /* ���� */
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32        enCireg;                          /* ��Ϣ���� */
}ID_AT_IMSA_CIREG_SET_REQ_ELF_STRU;

/*****************************************************************************
 �ṹ��    : ID_AT_IMSA_CIREG_QRY_REQ_ELF_STRU
 �ṹ˵��  : ID_AT_IMSA_CIREG_QRY_REQ��Ϣ��Ӧ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_MSG_TYPE_ENUM_UINT32                    usMsgName;                              /* ��Ϣ�� */
    MN_CLIENT_ID_T                                  clientId;                               /* Client ID */
    MN_OPERATION_ID_T                               opId;                                   /* Operation ID */
    VOS_UINT8                                       aucReserve2[1];                         /* ���� */
}ID_AT_IMSA_CIREG_QRY_REQ_ELF_STRU;

/*****************************************************************************
 �ṹ��    : ID_AT_IMSA_CIREP_SET_REQ_ELF_STRU
 �ṹ˵��  : ID_AT_IMSA_CIREP_SET_REQ��Ϣ��Ӧ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_MSG_TYPE_ENUM_UINT32                    usMsgName;                              /* ��Ϣ�� */
    MN_CLIENT_ID_T                                  clientId;                               /* Client ID */
    MN_OPERATION_ID_T                               opId;                                   /* Operation ID */
    VOS_UINT8                                       aucReserve2[1];                         /* ���� */
    AT_IMSA_CIREP_REPORT_ENUM_UINT32                enReport;                          /* ��Ϣ���� */
}ID_AT_IMSA_CIREP_SET_REQ_ELF_STRU;

/*****************************************************************************
 �ṹ��    : ID_AT_IMSA_CIREP_QRY_REQ_ELF_STRU
 �ṹ˵��  : ID_AT_IMSA_CIREP_QRY_REQ��Ϣ��Ӧ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_MSG_TYPE_ENUM_UINT32                    usMsgName;                              /* ��Ϣ�� */
    MN_CLIENT_ID_T                                  clientId;                               /* Client ID */
    MN_OPERATION_ID_T                               opId;                                   /* Operation ID */
    VOS_UINT8                                       aucReserve2[1];                         /* ���� */
}ID_AT_IMSA_CIREP_QRY_REQ_ELF_STRU;



/*****************************************************************************
 �ṹ��    : TAF_XSMS_ELF_APP_AT_CNF_STRU
 �ṹ˵��  : XSMS��AT�ϱ�����Ϣ�ṹ��Ӧ��ӳ��ṹ��
 1.��    ��   : 2015��12��04��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32               enUnionStructSelChoice;
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    VOS_UINT8                                       ucRsv;
    VOS_UINT32                                      ulError;
    union
    {
        TAF_XSMS_INIT_IND_STRU                      stInitInd;                  /* 00 */
        TAF_ELF_NULL_STRU                           stNull1;                    /* ռλ */
        TAF_ELF_NULL_STRU                           stSndCnf;                   /* 02 */
        TAF_ELF_NULL_STRU                           stNull2;                    /* ռλ */
        TAF_XSMS_WRITE_CNF_STRU                     stWriteCnf;                 /* 04 */
        TAF_ELF_NULL_STRU                           stNull3;                    /* ռλ */
        TAF_ELF_NULL_STRU                           stDelCnf;                   /* 06 */
        TAF_XSMS_SEND_SUCC_IND_STRU                 stSndSuccInd;               /* 07 */
        TAF_XSMS_SEND_FAIL_IND_STRU                 stSndFailInd;               /* 08 */
        TAF_XSMS_RCV_IND_STRU                       stRcvInd;                   /* 09 */
        TAF_ELF_NULL_STRU                           stUimFullInd;               /* 10 */
    }u;
}TAF_XSMS_ELF_APP_AT_CNF_STRU;



/*****************************************************************************
 �ṹ��    :  MN_CALL_ELF_APP_REQ_MSG_STRU
 �ṹ˵��  :  ��AT����TAF��APP����������Ϣ��Ӧ�Ľṹ��
 1.��    ��   : 2015��12��05��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MN_CALL_APP_REQ_ENUM_UINT32                     enUnionStructSelChoice;
    MN_CLIENT_ID_T                                  clientId;
    MN_OPERATION_ID_T                               opId;
    MN_CALL_ID_T                                    callId;
    union
    {
        TAF_ELF_NULL_STRU                           stNull1;                    /* ռλ */
        MN_CALL_ORIG_PARAM_STRU                     stOrig;                     /* 0x1 */
        MN_CALL_END_PARAM_STRU                      stEnd;                      /* 0x2 */
        MN_CALL_ANS_PARAM_STRU                      stAns;                      /* 0x3 */
        TAF_CALL_DTMF_PARAM_STRU                    stStartDtmf;                /* 0x4 */
        TAF_CALL_DTMF_PARAM_STRU                    stStopDtmf;                 /* 0x5 */
        MN_CALL_SUPS_PARAM_STRU                     stCallMgmtCmd;              /* 0x6 */
        TAF_ELF_NULL_STRU                           stGetInfoReq;               /* 0x7 */
        TAF_ELF_NULL_STRU                           stGetCdurReq;               /* 0x8 */
        MN_CALL_UUS1_PARAM_STRU                     stSetUus1Info;              /* 0x9 */
        TAF_ELF_NULL_STRU                           stGEtUus1Info;              /* 0xa */
        MN_CALL_SET_ALS_PARAM_STRU                  stSetAls;                   /* 0xb */
        TAF_ELF_NULL_STRU                           stQryAls;                   /* 0xc */
        TAF_ELF_NULL_STRU                           stMaxReq;                   /* 0xd */
        MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU         stEccNumReq;                /* 0xe */
        TAF_ELF_NULL_STRU                           stTafAgentMnGetCallInfo;    /* 0xf */
        TAF_ELF_NULL_STRU                           stClprGetReq;               /* 0x10 */
        TAF_ELF_NULL_STRU                           stXlemaReq;                 /* 0x11 */
        MN_CALL_SET_CSSN_REQ_STRU                   stCssnReq;                  /* 0x12 */
        TAF_ELF_NULL_STRU                           stEcallInfoReq;             /* 0x13 */
        TAF_ELF_NULL_STRU                           stFlashReq;                 /* ռλ */
        TAF_ELF_NULL_STRU                           stBurstDtmfReq;             /* ռλ */
        TAF_ELF_NULL_STRU                           stCustomDialReq;            /* ռλ */
        MN_CALL_MODIFY_REQ_STRU                     stModifyReq;                /* 0x17 */
        MN_CALL_MODIFY_REQ_STRU                     stRemoteModifyReq;          /* 0x18 */
        TAF_CALL_ECONF_DIAL_REQ_STRU                stEconfDial;                /* 0x19 */
        TAF_ELF_NULL_STRU                           stEconfCallInfo;            /* 0x1a */
    }u;
} MN_CALL_ELF_APP_REQ_MSG_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SEND_PARM_STRU
 �ṹ˵��  :  MN_MSG_SEND_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SEND_PARM_STRU                           stSndParm;
}MN_ELF_MSG_SEND_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SEND_FROMMEM_PARM_STRU
 �ṹ˵��  :  MN_MSG_SEND_FROMMEM_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SEND_FROMMEM_PARM_STRU                   stSndFormmenParm;
}MN_ELF_MSG_SEND_FROMMEM_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SEND_ACK_PARM_STRU
 �ṹ˵��  :  MN_MSG_SEND_ACK_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SEND_ACK_PARM_STRU                       stSndAckParm;
}MN_ELF_MSG_SEND_ACK_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_WRITE_PARM_STRU
 �ṹ˵��  :  MN_MSG_WRITE_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_WRITE_PARM_STRU                          stWriteParm;
}MN_ELF_MSG_WRITE_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_READ_PARM_STRU
 �ṹ˵��  :  MN_MSG_READ_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_READ_PARM_STRU                           stReadParm;
}MN_ELF_MSG_READ_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_LIST_PARM_STRU
 �ṹ˵��  :  MN_MSG_LIST_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_LIST_PARM_STRU                           stListParm;
}MN_ELF_MSG_LIST_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_DELETE_PARAM_STRU
 �ṹ˵��  :  MN_MSG_DELETE_PARAM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_DELETE_PARAM_STRU                        stDelParm;
}MN_ELF_MSG_DELETE_PARAM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_DELETE_TEST_STRU
 �ṹ˵��  :  MN_MSG_LIST_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_LIST_PARM_STRU                           stListPara;
}MN_ELF_MSG_DELETE_TEST_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_WRITE_SRV_PARAM_STRU
 �ṹ˵��  :  MN_MSG_WRITE_SRV_PARAM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_WRITE_SRV_PARAM_STRU                     stWriteSrvParm;
}MN_ELF_MSG_WRITE_SRV_PARAM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_READ_COMM_PARAM_STRU
 �ṹ˵��  :  MN_MSG_READ_COMM_PARAM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_READ_COMM_PARAM_STRU                     stReadCommParm;
}MN_ELF_MSG_READ_COMM_PARAM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_MODIFY_STATUS_PARM_STRU
 �ṹ˵��  :  MN_MSG_MODIFY_STATUS_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_MODIFY_STATUS_PARM_STRU                  stModifyStatus;
}MN_ELF_MSG_MODIFY_STATUS_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SET_RCVMSG_PATH_PARM_STRU
 �ṹ˵��  :  MN_MSG_SET_RCVMSG_PATH_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU                stSetRcvPath;
}MN_ELF_MSG_SET_RCVMSG_PATH_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_GET_RCVMSG_PATH_PARM_STRU
 �ṹ˵��  :  MN_MSG_GET_RCVMSG_PATH_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_GET_RCVMSG_PATH_PARM_STRU                stGetRcvPath;
}MN_ELF_MSG_GET_RCVMSG_PATH_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_GET_STORAGE_STATUS_PARM_STRU
 �ṹ˵��  :  MN_MSG_GET_STORAGE_STATUS_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_GET_STORAGE_STATUS_PARM_STRU             stGetStorageStatus;
}MN_ELF_MSG_GET_STORAGE_STATUS_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SET_MEMSTATUS_PARM_STRU
 �ṹ˵��  :  MN_MSG_SET_MEMSTATUS_PARM_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SET_MEMSTATUS_PARM_STRU                  stSetMemStatus;
}MN_ELF_MSG_SET_MEMSTATUS_PARM_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_SET_LINK_CTRL_STRU
 �ṹ˵��  :  MN_MSG_SET_LINK_CTRL_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_SET_LINK_CTRL_STRU                       stSetLinkCtrl;
}MN_ELF_MSG_SET_LINK_CTRL_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_APP_REQ_MSG_STRU
 �ṹ˵��  :  MN_MSG_APP_REQ_MSG_STRU�ṹ����Ϣ����Ϊ�������ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       aucContent[4];
}MN_ELF_MSG_APP_REQ_MSG_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_MSG_STUB_MSG_STRU
 �ṹ˵��  :  MN_ELF_MSG_STUB_MSG_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_MSG_STUB_MSG_STRU                            stStubMsg;
}MN_ELF_MSG_STUB_MSG_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_CBA_CBMI_RANGE_LIST_STRU
 �ṹ˵��  :  TAF_CBA_CBMI_RANGE_LIST_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_CBA_CBMI_RANGE_LIST_STRU                    stCbmiRangeList;
}TAF_ELF_CBA_CBMI_RANGE_LIST_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_REGISTERSS_REQ_STRU
 �ṹ˵��  :  TAF_SS_REGISTERSS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_REGISTERSS_REQ_STRU                      stSsRegReq;
}TAF_ELF_SS_REGISTERSS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_ERASESS_REQ_STRU
 �ṹ˵��  :  TAF_SS_ERASESS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_ERASESS_REQ_STRU                         stSsEraseReq;
}TAF_ELF_SS_ERASESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_ACTIVATESS_REQ_STRU
 �ṹ˵��  :  TAF_SS_ACTIVATESS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_ACTIVATESS_REQ_STRU                      stSsActReq;
}TAF_ELF_SS_ACTIVATESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_DEACTIVATESS_REQ_STRU
 �ṹ˵��  :  TAF_SS_DEACTIVATESS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_DEACTIVATESS_REQ_STRU                    stSsDeactReq;
}TAF_ELF_SS_DEACTIVATESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_INTERROGATESS_REQ_STRU
 �ṹ˵��  :  TAF_SS_INTERROGATESS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_INTERROGATESS_REQ_STRU                   stSsInterrogateReq;
}TAF_ELF_SS_INTERROGATESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_REGPWD_REQ_STRU
 �ṹ˵��  :  TAF_SS_REGPWD_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_REGPWD_REQ_STRU                          stSsRegPwdReq;
}TAF_ELF_SS_REGPWD_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_PROCESS_USS_REQ_STRU
 �ṹ˵��  :  TAF_SS_PROCESS_USS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_PROCESS_USS_REQ_STRU                     stSsProcUssReq;
}TAF_ELF_SS_PROCESS_USS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_SS_ERASECC_ENTRY_REQ_STRU
 �ṹ˵��  :  TAF_SS_ERASECC_ENTRY_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_SS_ERASECC_ENTRY_REQ_STRU                   stSsEraseCCEntryReq;
}TAF_ELF_SS_ERASECC_ENTRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  ELF_USSD_TRANS_MODE_STRU
 �ṹ˵��  :  USSD_TRANS_MODE_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    USSD_TRANS_MODE_STRU                            stUssdMode;
}ELF_USSD_TRANS_MODE_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU       stSetPrimPdp;
}TAF_ELF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU       stGetPrimPdp;
}TAF_ELF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU        stSetSecPdp;
}TAF_ELF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU        stGetSecPdp;
}TAF_ELF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_TFT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_TFT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_TFT_INFO_REQ_STRU                    stSetTftInfo;
}TAF_ELF_PS_SET_TFT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_TFT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_TFT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_TFT_INFO_REQ_STRU                    stGetTftInfo;
}TAF_ELF_PS_GET_TFT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_UMTS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU               stSetUmtsQosInfo;
}TAF_ELF_PS_SET_UMTS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_UMTS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU               stGetUmtsQosInfo;
}TAF_ELF_PS_GET_UMTS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU           stSetUmtsQosMinInfo;
}TAF_ELF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU           stGetUmtsQosMinInfo;
}TAF_ELF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU       stGetDynamicUmtsQosInfo;
}TAF_ELF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_PDP_STATE_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_PDP_STATE_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_PDP_STATE_REQ_STRU                   stSetPdpState;
}TAF_ELF_PS_SET_PDP_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PDP_STATE_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PDP_STATE_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PDP_STATE_REQ_STRU                   stGetPdpState;
}TAF_ELF_PS_GET_PDP_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CALL_MODIFY_REQ_STRU
 �ṹ˵��  :  TAF_PS_CALL_MODIFY_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CALL_MODIFY_REQ_STRU                     stCallModifyReq;
}TAF_ELF_PS_CALL_MODIFY_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CALL_ANSWER_REQ_STRU
 �ṹ˵��  :  TAF_PS_CALL_ANSWER_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CALL_ANSWER_REQ_STRU                     stCallAnswerReq;
}TAF_ELF_PS_CALL_ANSWER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CALL_HANGUP_REQ_STRU
 �ṹ˵��  :  TAF_PS_CALL_HANGUP_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CALL_HANGUP_REQ_STRU                     stCallHangupReq;
}TAF_ELF_PS_CALL_HANGUP_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU            stGetPdpIpAddr;
}TAF_ELF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU            stGetPdpCtxInfo;
}TAF_ELF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_ANSWER_MODE_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU            stSetAnswerMode;
}TAF_ELF_PS_SET_ANSWER_MODE_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_ANSWER_MODE_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU            stGetAnswerMode;
}TAF_ELF_PS_GET_ANSWER_MODE_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                             stHeader;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU           stGetDynamicPrimPdp;
}TAF_ELF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                             stHeader;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU            stGetDynamicSecPdp;
}TAF_ELF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU            stGetDynamicTft;
}TAF_ELF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_EPS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_EPS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU                stSetEpsQos;
}TAF_ELF_PS_SET_EPS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_EPS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_EPS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU                stGetEpsQos;
}TAF_ELF_PS_GET_EPS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU        stGetDynamicEpsQos;
}TAF_ELF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CALL_ORIG_REQ_STRU
 �ṹ˵��  :  TAF_PS_CALL_ORIG_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CALL_ORIG_REQ_STRU                       stCallOrigReq;
}TAF_ELF_PS_CALL_ORIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CALL_END_REQ_STRU
 �ṹ˵��  :  TAF_PS_CALL_END_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CALL_END_REQ_STRU                        stCallEndReq;
}TAF_ELF_PS_CALL_END_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU          stGetDGprsActType;
}TAF_ELF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_PPP_DIAL_ORIG_REQ_STRU
 �ṹ˵��  :  TAF_PS_PPP_DIAL_ORIG_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU                   stPPPDialOrigReq;
}TAF_ELF_PS_PPP_DIAL_ORIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_DSFLOW_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_DSFLOW_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU                 stGetDsflowInfo;
}TAF_ELF_PS_GET_DSFLOW_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CLEAR_DSFLOW_REQ_STRU
 �ṹ˵��  :  TAF_PS_CLEAR_DSFLOW_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU                    stClearDsflow;
}TAF_ELF_PS_CLEAR_DSFLOW_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CONFIG_DSFLOW_RPT_REQ_STRU
 �ṹ˵��  :  TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU               stConfigDsflowRpt;
}TAF_ELF_PS_CONFIG_DSFLOW_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU
 �ṹ˵��  :  TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU            stNbnsFuncReq;
}TAF_ELF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU;


/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_PDP_AUTH_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU               stSetPdpAuth;
}TAF_ELF_PS_SET_PDP_AUTH_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PDP_AUTH_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU               stGetPdpAuth;
}TAF_ELF_PS_GET_PDP_AUTH_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_PDP_DNS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_PDP_DNS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_PDP_DNS_INFO_REQ_STRU                stSetPdpDns;
}TAF_ELF_PS_SET_PDP_DNS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_PDP_DNS_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_PDP_DNS_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_PDP_DNS_INFO_REQ_STRU                stGetPdpDns;
}TAF_ELF_PS_GET_PDP_DNS_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_TRIG_GPRS_DATA_REQ_STRU
 �ṹ˵��  :  TAF_PS_TRIG_GPRS_DATA_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_TRIG_GPRS_DATA_REQ_STRU                  stTrigGprsData;
}TAF_ELF_PS_TRIG_GPRS_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_LTECS_REQ_STRU
 �ṹ˵��  :  TAF_PS_LTECS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_LTECS_REQ_STRU                           stLtecsReq;
}TAF_ELF_PS_LTECS_REQ_STRU;



/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_SET_AUTHDATA_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_SET_AUTHDATA_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU               stSetAuthDataInfo;
}TAF_ELF_PS_SET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_AUTHDATA_INFO_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_AUTHDATA_INFO_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_AUTHDATA_INFO_REQ_STRU               stGetAuthDataInfo;
}TAF_ELF_PS_GET_AUTHDATA_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PS_GET_NEGOTIATION_DNS_REQ_STRU
 �ṹ˵��  :  TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stHeader;
    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU             stGetNegotiationDns;
}TAF_ELF_PS_GET_NEGOTIATION_DNS_REQ_STRU;


/*****************************************************************************
 �ṹ��    :  GAS_ELF_AT_CMD_STRU
 �ṹ˵��  :  GAS_AT_CMD_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    GAS_AT_CMD_STRU                                 stGasAtCmd;
}GAS_ELF_AT_CMD_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_GPIOPL_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_GPIOPL_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��07��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_GPIOPL_SET_REQ_STRU                   stGpioplSetReq;
}DRV_ELF_AGENT_GPIOPL_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_DATALOCK_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_DATALOCK_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_DATALOCK_SET_REQ_STRU                 stDatalockSetReq;
}DRV_ELF_AGENT_DATALOCK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_TMODE_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_TMODE_SET_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       ucUpdateFlag;
}DRV_ELF_AGENT_TMODE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_FCHAN_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_FCHAN_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_FCHAN_SET_REQ_STRU                    stFchanSetReq;
}DRV_ELF_AGENT_FCHAN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_DRV_AGENT_RXDIV_SET_STRU
 �ṹ˵��  :  AT_DRV_AGENT_RXDIV_SET_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_DRV_AGENT_RXDIV_SET_STRU                     stRxdivSet;
}AT_ELF_DRV_AGENT_RXDIV_SET_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_SIMLOCK_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_SIMLOCK_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_SIMLOCK_SET_REQ_STRU                  stSimlockReq;
}DRV_ELF_AGENT_SIMLOCK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  SPY_ELF_TEMP_THRESHOLD_PARA_STRU
 �ṹ˵��  :  SPY_TEMP_THRESHOLD_PARA_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    SPY_TEMP_THRESHOLD_PARA_STRU                    stTempPara;
}SPY_ELF_TEMP_THRESHOLD_PARA_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_TSELRF_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_TSELRF_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_TSELRF_SET_REQ_STRU                   stTseLrf;
}DRV_ELF_AGENT_TSELRF_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_CUSTOM_CARDLOCK_STATUS_STRU
 �ṹ˵��  :  TAF_CUSTOM_CARDLOCK_STATUS_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_CUSTOM_CARDLOCK_STATUS_STRU                 stCardLockStatus;
}TAF_ELF_CUSTOM_CARDLOCK_STATUS_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_SPWORD_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_SPWORD_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_SPWORD_SET_REQ_STRU                   stSpwordSetReq;
}DRV_ELF_AGENT_SPWORD_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_PSTANDBY_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_PSTANDBY_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_PSTANDBY_REQ_STRU                     stPstandbyInfo;
}DRV_ELF_AGENT_PSTANDBY_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_HUK_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_HUK_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_HUK_SET_REQ_STRU                      stHukSetReq;
}DRV_ELF_AGENT_HUK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_FACAUTHPUBKEY_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU            stFacAuthPubkeySetReq;
}DRV_ELF_AGENT_FACAUTHPUBKEY_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_IDENTIFYEND_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_IDENTIFYEND_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_IDENTIFYEND_SET_REQ_STRU              stIdentifyEndSetReq;
}DRV_ELF_AGENT_IDENTIFYEND_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU         stSimlockDataWriteSetReq;
}DRV_ELF_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_PHONEPHYNUM_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU              stPhonePhynumSetReq;
}DRV_ELF_AGENT_PHONEPHYNUM_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_PORTCTRLTMP_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU              stPortCtrlTmpSetReq;
}DRV_ELF_AGENT_PORTCTRLTMP_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_PORTATTRIBSET_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU            stPortAttribSetReq;
}DRV_ELF_AGENT_PORTATTRIBSET_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_OPWORD_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_OPWORD_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_OPWORD_SET_REQ_STRU                   stOpwordSetReq;
}DRV_ELF_AGENT_OPWORD_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_SARREDUCTION_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_SARREDUCTION_SET_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT16                                      usSarReduction;
}DRV_ELF_AGENT_SARREDUCTION_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU
 �ṹ˵��  :  TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU              stSimLockMaxTimes;
}TAF_ELF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_AP_SIMST_SET_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_AP_SIMST_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_AP_SIMST_SET_REQ_STRU                 stApSimStSetReq;
}DRV_ELF_AGENT_AP_SIMST_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_HVPDH_REQ_STRU
 �ṹ˵��  :  DRV_AGENT_HVPDH_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_HVPDH_REQ_STRU                        stHvpdhReq;
}DRV_ELF_AGENT_HVPDH_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  DRV_ELF_AGENT_ANTSWITCH_SET_STRU
 �ṹ˵��  :  DRV_AGENT_ANTSWITCH_SET_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    DRV_AGENT_ANTSWITCH_SET_STRU                    stAntSwitchSetPara;
}DRV_ELF_AGENT_ANTSWITCH_SET_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_NDIS_PDNINFO_CFG_REQ_STRU
 �ṹ˵��  :  ID_AT_NDIS_PDNINFO_CFG_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    VOS_UINT8                                       ucClientId;
    VOS_UINT8                                       ucSysMode;
    VOS_UINT16                                      usMsgSize;
    VOS_UINT32                                      ulEventId;
    AT_NDIS_PDNINFO_CFG_REQ_STRU                    stNdisCfgReq;
}AT_ELF_NDIS_PDNINFO_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_NDIS_PDNINFO_REL_REQ_STRU
 �ṹ˵��  :  ID_AT_NDIS_PDNINFO_REL_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    VOS_UINT8                                       ucClientId;
    VOS_UINT8                                       ucSysMode;
    VOS_UINT16                                      usMsgSize;
    VOS_UINT32                                      ulEventId;
    AT_NDIS_PDNINFO_REL_REQ_STRU                    stNdisRelReq;
}AT_ELF_NDIS_PDNINFO_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_NDIS_PDNINFO_CFG_CNF_STRU
 �ṹ˵��  :  ID_AT_NDIS_PDNINFO_CFG_CNF��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    VOS_UINT8                                       ucClientId;
    VOS_UINT8                                       ucSysMode;
    VOS_UINT16                                      usMsgSize;
    VOS_UINT32                                      ulEventId;
    AT_NDIS_PDNINFO_CFG_CNF_STRU                    stPdnCfgCnf;
}AT_ELF_NDIS_PDNINFO_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_NDIS_PDNINFO_REL_CNF_STRU
 �ṹ˵��  :  ID_AT_NDIS_PDNINFO_REL_CNF��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    VOS_UINT8                                       ucClientId;
    VOS_UINT8                                       ucSysMode;
    VOS_UINT16                                      usMsgSize;
    VOS_UINT32                                      ulEventId;
    AT_NDIS_PDNINFO_REL_CNF_STRU                    stPdnRelCnf;
}AT_ELF_NDIS_PDNINFO_REL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  USIMM_ELF_RACCESS_REQ_STRU
 �ṹ˵��  :  TAF_MSG_MMA_USIM_RESTRICTED_ACCESS��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    USIMM_RACCESS_REQ_STRU                          stCommand;
}USIMM_ELF_RACCESS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MSG_PARA_READ_STRU
 �ṹ˵��  :  TAF_MSG_PARA_READ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       ucPara;
}TAF_ELF_MSG_PARA_READ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PH_PIN_DATA_STRU
 �ṹ˵��  :  TAF_MSG_MMA_OP_PIN_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_ELF_PH_PIN_CMD_TYPE_UINT8                   CmdType;
    TAF_ELF_PH_PIN_TYPE_UINT8                       PinType;
    TAF_UINT8                                       aucOldPin[TAF_PH_PINCODELENMAX +1];
    TAF_UINT8                                       aucNewPin[TAF_PH_PINCODELENMAX +1];
}TAF_ELF_PH_PIN_DATA_STRU;


/*****************************************************************************
 �ṹ��    :  TAF_ELF_ME_PERSONALISATION_DATA_STRU
 �ṹ˵��  :  TAF_MSG_MMA_ME_PERSONAL_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_ELF_ME_PERSONALISATION_CMD_TYPE_UINT8       CmdType;
    TAF_ELF_ME_PERSONALISATION_TYPE_UINT8           MePersonalType;
    TAF_UINT8                                       aucOldPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_UINT8                                       aucNewPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_ME_PERSONALISATION_SET_UN                   unMePersonalisationSet;
}TAF_ELF_ME_PERSONALISATION_DATA_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PH_QRY_USIM_INFO_STRU
 �ṹ˵��  :  TAF_MSG_MMA_USIM_INFO��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_ELF_PH_ICC_TYPE_UINT8                       Icctype;
    VOS_UINT8                                       ucReserved;
    TAF_PH_USIM_FILE_ENUM_U16                       enEfId;
    TAF_UINT32                                      ulRecNum;
    TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU           stPnnQryIndex;
}TAF_ELF_PH_QRY_USIM_INFO_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_PH_QRY_CPNN_INFO_STRU
 �ṹ˵��  :  TAF_MSG_MMA_CPNN_INFO��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_ELF_PH_ICC_TYPE_UINT8                       Icctype;
}TAF_ELF_PH_QRY_CPNN_INFO_STRU;

/*****************************************************************************
 �ṹ��    :  MN_ELF_PH_SET_CPIN_REQ_STRU
 �ṹ˵��  :  MN_PH_SET_CPIN_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MN_PH_SET_CPIN_REQ_STRU                         stSetCPinReq;
}MN_ELF_PH_SET_CPIN_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU
 �ṹ˵��  :  TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU           stCopsFormatType;
}TAF_ELF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MMA_USIM_STUB_SET_REQ_STRU
 �ṹ˵��  :  TAF_MMA_USIM_STUB_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_MMA_USIM_STUB_SET_REQ_STRU                  stUsimStub;
}TAF_ELF_MMA_USIM_STUB_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MMA_REFRESH_STUB_SET_REQ_STRU
 �ṹ˵��  :  TAF_MMA_REFRESH_STUB_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_MMA_REFRESH_STUB_SET_REQ_STRU               stRefreshStub;
}TAF_ELF_MMA_REFRESH_STUB_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU
 �ṹ˵��  :  TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��09��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU            stAutoReselStub;
}TAF_ELF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_CPOS_REQ_STRU
 �ṹ˵��  :  AT_MTA_CPOS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_CPOS_REQ_STRU                            stCposSetReq;
}AT_ELF_MTA_CPOS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_APSEC_REQ_STRU
 �ṹ˵��  :  AT_MTA_APSEC_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_APSEC_REQ_STRU                           stApSecSetReq;
}AT_ELF_MTA_APSEC_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SIMLOCKUNLOCK_REQ_STRU
 �ṹ˵��  :  AT_MTA_SIMLOCKUNLOCK_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SIMLOCKUNLOCK_REQ_STRU                   stSimlockUnlockSetReq;
}AT_ELF_MTA_SIMLOCKUNLOCK_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_QRY_NMR_REQ_STRU
 �ṹ˵��  :  AT_MTA_QRY_NMR_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_QRY_NMR_REQ_STRU                         stQryNmrReq;
}AT_ELF_MTA_QRY_NMR_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU
 �ṹ˵��  :  AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU            stReselOffsetCfgNtf;
}AT_ELF_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_WRR_AUTOTEST_QRY_PARA_STRU
 �ṹ˵��  :  AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU               stAtCmd;
}AT_ELF_MTA_WRR_AUTOTEST_QRY_PARA_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_WRR_CELLINFO_QRY_REQ_STRU
 �ṹ˵��  :  ID_AT_MTA_WRR_CELLINFO_QRY_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT32                                      ulAtCmdCellInfo;
}AT_ELF_MTA_WRR_CELLINFO_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_FREQLOCK_CTRL_STRU
 �ṹ˵��  :  MTA_AT_WRR_FREQLOCK_CTRL_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    MTA_AT_WRR_FREQLOCK_CTRL_STRU                   stFreqLock;
}MTA_ELF_AT_WRR_FREQLOCK_CTRL_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_WRR_RRC_VERSION_SET_REQ_STRU
 �ṹ˵��  :  ID_AT_MTA_WRR_RRC_VERSION_SET_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       ucRRCVersion;
}AT_ELF_MTA_WRR_RRC_VERSION_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_WRR_CELLSRH_SET_REQ_STRU
 �ṹ˵��  :  ID_AT_MTA_WRR_CELLSRH_SET_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       ucCellSrh;
}AT_ELF_MTA_WRR_CELLSRH_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_BODY_SAR_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_BODY_SAR_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_BODY_SAR_SET_REQ_STRU                    stBodySarSetReq;
}AT_ELF_MTA_BODY_SAR_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_CURC_SET_NOTIFY_STRU
 �ṹ˵��  :  AT_MTA_CURC_SET_NOTIFY_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_CURC_SET_NOTIFY_STRU                     stAtCmd;
}AT_ELF_MTA_CURC_SET_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_UNSOLICITED_RPT_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU             stAtCmd;
}AT_ELF_MTA_UNSOLICITED_RPT_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_UNSOLICITED_RPT_QRY_REQ_STRU
 �ṹ˵��  :  AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU             stAtCmd;
}AT_ELF_MTA_UNSOLICITED_RPT_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_NCELL_MONITOR_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_NCELL_MONITOR_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_NCELL_MONITOR_SET_REQ_STRU               stAtCmd;
}AT_ELF_MTA_NCELL_MONITOR_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_REFCLKFREQ_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_REFCLKFREQ_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_REFCLKFREQ_SET_REQ_STRU                  stRefClockReq;
}AT_ELF_MTA_REFCLKFREQ_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_HANDLEDECT_SET_REQ_STRU
 �ṹ˵��  :  ID_AT_MTA_HANDLEDECT_SET_REQ��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    VOS_UINT8                                       ucHandleType;
}AT_ELF_MTA_HANDLEDECT_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_ECID_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_ECID_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_ECID_SET_REQ_STRU                        stEcidSetReq;
}AT_ELF_MTA_ECID_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SET_DPDTTEST_FLAG_REQ_STRU
 �ṹ˵��  :  AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU               stAtCmd;
}AT_ELF_MTA_SET_DPDTTEST_FLAG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SET_DPDT_VALUE_REQ_STRU
 �ṹ˵��  :  AT_MTA_SET_DPDT_VALUE_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SET_DPDT_VALUE_REQ_STRU                  stAtCmd;
}AT_ELF_MTA_SET_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_QRY_DPDT_VALUE_REQ_STRU
 �ṹ˵��  :  AT_MTA_QRY_DPDT_VALUE_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU                  stAtCmd;
}AT_ELF_MTA_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_RRC_PROTECT_PS_REQ_STRU
 �ṹ˵��  :  AT_MTA_RRC_PROTECT_PS_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_RRC_PROTECT_PS_REQ_STRU                  stAtCmd;
}AT_ELF_MTA_RRC_PROTECT_PS_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_PHY_INIT_REQ_STRU
 �ṹ˵��  :  AT_MTA_PHY_INIT_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_PHY_INIT_REQ_STRU                        stPhyInit;
}AT_ELF_MTA_PHY_INIT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SET_GSM_FREQLOCK_REQ_STRU
 �ṹ˵��  :  AT_MTA_SET_GSM_FREQLOCK_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU                stGFreqLockInfo;
}AT_ELF_MTA_SET_GSM_FREQLOCK_REQ_STRU;


/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU         stMBMSServiceOption;
}AT_ELF_MTA_MBMS_SERVICE_OPTION_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_MBMS_PREFERENCE_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_MBMS_PREFERENCE_SET_REQ_STRU             stMBMSCastMode;
}AT_ELF_MTA_MBMS_PREFERENCE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU        stMBMSUnsolicitedCfg;
}AT_ELF_MTA_MBMS_UNSOLICITED_CFG_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU       stPowerConsumption;
}AT_ELF_MTA_LOW_POWER_CONSUMPTION_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_MBMS_INTERESTLIST_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU           stMBMSInterestList;
}AT_ELF_MTA_MBMS_INTERESTLIST_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU          stMBMSServiceState;
}AT_ELF_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_LTE_WIFI_COEX_SET_REQ_STRU
 �ṹ˵��  :  AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU               stIsmCoex;
}AT_ELF_MTA_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SET_FR_REQ_STRU
 �ṹ˵��  :  AT_MTA_SET_FR_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SET_FR_REQ_STRU                          stAtMtaSetFrReq;
}AT_ELF_MTA_SET_FR_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  AT_ELF_MTA_SET_UE_CENTER_REQ_STRU
 �ṹ˵��  :  AT_MTA_SET_UE_CENTER_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_ELF_APP_REQ_MSG_STRU
    AT_MTA_SET_UE_CENTER_REQ_STRU                   stSetUeCenterInfo;
}AT_ELF_MTA_SET_UE_CENTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_CPOS_CNF_STRU
 �ṹ˵��  :  MTA_AT_CPOS_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_CPOS_CNF_STRU                            stMtaAtCposCnf;
}MTA_ELF_AT_CPOS_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_CGPSCLOCK_CNF_STRU
 �ṹ˵��  :  MTA_AT_CGPSCLOCK_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_CGPSCLOCK_CNF_STRU                       stMtaAtCgpsClockCnf;
}MTA_ELF_AT_CGPSCLOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_CPOSR_IND_STRU
 �ṹ˵��  :  MTA_AT_CPOSR_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_CPOSR_IND_STRU                           stCposrInd;
}MTA_ELF_AT_CPOSR_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_XCPOSRRPT_IND_STRU
 �ṹ˵��  :  MTA_AT_XCPOSRRPT_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_XCPOSRRPT_IND_STRU                       stXcposrRptInd;
}MTA_ELF_AT_XCPOSRRPT_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_APSEC_CNF_STRU
 �ṹ˵��  :  MTA_AT_APSEC_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_APSEC_CNF_STRU                           stApSecCnf;
}MTA_ELF_AT_APSEC_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SIMLOCKUNLOCK_CNF_STRU
 �ṹ˵��  :  MTA_AT_SIMLOCKUNLOCK_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU                   stSimlockUnlockCnf;
}MTA_ELF_AT_SIMLOCKUNLOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_QRY_NMR_CNF_STRU
 �ṹ˵��  :  MTA_AT_QRY_NMR_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_QRY_NMR_CNF_STRU                         stQryNmrCnf;
}MTA_ELF_AT_QRY_NMR_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_AUTOTEST_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU                stQryCnf;
}MTA_ELF_AT_WRR_AUTOTEST_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_CELLINFO_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_CELLINFO_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU                stQryCnf;
}MTA_ELF_AT_WRR_CELLINFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_MEANRPT_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_MEANRPT_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU                 stQryCnf;
}MTA_ELF_AT_WRR_MEANRPT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_FREQLOCK_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_FREQLOCK_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU                stQryCnf;
}MTA_ELF_AT_WRR_FREQLOCK_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_RRC_VERSION_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU             stSetCnf;
}MTA_ELF_AT_WRR_RRC_VERSION_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_CELLSRH_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_CELLSRH_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                 stSetCnf;
}MTA_ELF_AT_WRR_CELLSRH_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_FREQLOCK_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU                stQryCnf;
}MTA_ELF_AT_WRR_FREQLOCK_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_RRC_VERSION_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU             stQryCnf;
}MTA_ELF_AT_WRR_RRC_VERSION_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_WRR_CELLSRH_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_WRR_CELLSRH_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU                 stQryCnf;
}MTA_ELF_AT_WRR_CELLSRH_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_RESULT_CNF_STRU
 �ṹ˵��  :  MTA_AT_RESULT_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RESULT_CNF_STRU                          stResultCnf;
}MTA_ELF_AT_RESULT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_CURC_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_CURC_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_CURC_QRY_CNF_STRU                        stQryCurcCnf;
}MTA_ELF_AT_CURC_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_UNSOLICITED_RPT_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU             stSetUnsolicitedRptCnf;
}MTA_ELF_AT_UNSOLICITED_RPT_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_UNSOLICITED_RPT_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RESULT_ENUM_UINT32                       enResult;
    AT_MTA_RPT_QRY_TYPE_ENUM_UINT32                 enUnionStructSelChoice;
    union
    {
        VOS_UINT8                                   ucTimeRptFlg;                           /* time�Ƿ������ϱ���ʶ */
        VOS_UINT8                                   ucCtzvRptFlg;                           /* ctzr�Ƿ������ϱ���ʶ */
        AT_MTA_CSSN_RPT_FLG_STRU                    stCssnRptFlg;                           /* cssn�Ƿ������ϱ���ʶ�ṹ�� */
        VOS_UINT8                                   ucCusdRptFlg;                           /* cusd�Ƿ������ϱ���ʶ�ṹ�� */
    }u;
    VOS_UINT8                           aucReserve[2];
}MTA_ELF_AT_UNSOLICITED_RPT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_IMEI_VERIFY_QRY_CNF_STRU
 �ṹ˵��  :  ID_MTA_AT_IMEI_VERIFY_QRY_CNF��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    VOS_UINT32                                      ulImeiVerify;
}MTA_ELF_AT_IMEI_VERIFY_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_CGSN_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_CGSN_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_CGSN_QRY_CNF_STRU                        stCgsnCnf;
}MTA_ELF_AT_CGSN_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_NCELL_MONITOR_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_NCELL_MONITOR_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU               stQryCnf;
}MTA_ELF_AT_NCELL_MONITOR_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_NCELL_MONITOR_IND_STRU
 �ṹ˵��  :  MTA_AT_NCELL_MONITOR_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_NCELL_MONITOR_IND_STRU                   stMtaAtInd;
}MTA_ELF_AT_NCELL_MONITOR_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_REFCLKFREQ_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_REFCLKFREQ_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU                  stRefClkFreqCnf;
}MTA_ELF_AT_REFCLKFREQ_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_REFCLKFREQ_IND_STRU
 �ṹ˵��  :  MTA_AT_REFCLKFREQ_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_REFCLKFREQ_IND_STRU                      stRefClkFreqInd;
}MTA_ELF_AT_REFCLKFREQ_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_HANDLEDECT_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_HANDLEDECT_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_HANDLEDECT_SET_CNF_STRU                  stSetCnf;
}MTA_ELF_AT_HANDLEDECT_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_HANDLEDECT_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_HANDLEDECT_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU                  stQryCnf;
}MTA_ELF_AT_HANDLEDECT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_PS_TRANSFER_IND_STRU
 �ṹ˵��  :  MTA_AT_PS_TRANSFER_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_PS_TRANSFER_IND_STRU                     stPsTransferInd;
}MTA_ELF_AT_PS_TRANSFER_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_ECID_SET_CNF_STRU
 �ṹ˵��  :  MTA_AT_ECID_SET_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RESULT_ENUM_UINT32                       enResult;
    VOS_UINT8                                       aucCellInfoStr[MTA_ECID_CELLINFO_MAX_STRLEN];
}MTA_ELF_AT_ECID_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_RF_LCD_MIPICLK_CNF_STRU
 �ṹ˵��  :  MTA_AT_RF_LCD_MIPICLK_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU                  stQryMipiCnf;
}MTA_ELF_AT_RF_LCD_MIPICLK_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_RF_LCD_MIPICLK_IND_STRU
 �ṹ˵��  :  MTA_AT_RF_LCD_MIPICLK_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU                  stMipClkInd;
}MTA_ELF_AT_RF_LCD_MIPICLK_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_DPDTTEST_FLAG_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU               stMtaAtQryCnf;
}MTA_ELF_AT_SET_DPDTTEST_FLAG_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_DPDT_VALUE_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_DPDT_VALUE_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU                  stMtaAtQryCnf;
}MTA_ELF_AT_SET_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_QRY_DPDT_VALUE_CNF_STRU
 �ṹ˵��  :  MTA_AT_QRY_DPDT_VALUE_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU                  stMtaAtQryCnf;
}MTA_ELF_AT_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_RRC_PROTECT_PS_CNF_STRU
 �ṹ˵��  :  MTA_AT_RRC_PROTECT_PS_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_RRC_PROTECT_PS_CNF_STRU                  stMtaAtPortectPSCnf;
}MTA_ELF_AT_RRC_PROTECT_PS_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_PHY_INIT_CNF_STRU
 �ṹ˵��  :  MTA_AT_PHY_INIT_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_PHY_INIT_CNF_STRU                        stSndAtPhyInitCnf;
}MTA_ELF_AT_PHY_INIT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_GSM_FREQLOCK_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_GSM_FREQLOCK_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU                stSetGFreqLockCnf;
}MTA_ELF_AT_SET_GSM_FREQLOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_FEMCTRL_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_FEMCTRL_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_FEMCTRL_CNF_STRU                     stSetCnf;
}MTA_ELF_AT_SET_FEMCTRL_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_FEMCTRL_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_FEMCTRL_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_XPASS_INFO_IND_STRU                      stXpassInfoInd;
}MTA_ELF_AT_XPASS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU     stQryCnf;
}MTA_ELF_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU      stQryCnf;
}MTA_ELF_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU           stQryCnf;
}MTA_ELF_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_EMBMS_STATUS_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_EMBMS_STATUS_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU                stQryCnf;
}MTA_ELF_AT_EMBMS_STATUS_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_MBMS_SERVICE_EVENT_IND_STRU
 �ṹ˵��  :  MTA_AT_MBMS_SERVICE_EVENT_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_MBMS_SERVICE_EVENT_IND_STRU              stMtaAtInd;
}MTA_ELF_AT_MBMS_SERVICE_EVENT_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU       stQryCnf;
}MTA_ELF_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_LTE_WIFI_COEX_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU               stCoexCnf;
}MTA_ELF_AT_LTE_WIFI_COEX_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_FR_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_FR_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_FR_CNF_STRU                          stMtaAtSetFrCnf;
}MTA_ELF_AT_SET_FR_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_TRANSMODE_QRY_CNF_STRU
 �ṹ˵��  :  MTA_AT_TRANSMODE_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_TRANSMODE_QRY_CNF_STRU                   stTransModeQryCnf;
}MTA_ELF_AT_TRANSMODE_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_SET_UE_CENTER_CNF_STRU
 �ṹ˵��  :  MTA_AT_SET_UE_CENTER_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_SET_UE_CENTER_CNF_STRU                   stMtaAtUECenterSetCnf;
}MTA_ELF_AT_SET_UE_CENTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_AT_QRY_UE_CENTER_CNF_STRU
 �ṹ˵��  :  MTA_AT_QRY_UE_CENTER_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��10��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgId;
    AT_APPCTRL_STRU                                 stAppCtrl;
    MTA_AT_QRY_UE_CENTER_CNF_STRU                   stMtaAtUECenterQryCnf;
}MTA_ELF_AT_QRY_UE_CENTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  AGPS_ELF_SHAPE_DATA_STRU
 �ṹ˵��  :  AGPS_SHAPE_DATA_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucRsv[3];                      /* ����λ */

    AGPS_POSITION_ESTIMAT_ENUM_UINT8            enUnionStructSelChoice;            /* λ�ù���ʹ�õķ��� */
    union
    {
        AGPS_ELLIP_POINT_STRU                   stEllipPoint;                   /* ellipsoid_point */
        AGPS_ELLIP_POINT_UNCERT_CIRCLE_STRU     stEllipPointUncertCircle;       /* ellipsoid_point_uncert_circle */
        AGPS_ELLIP_POINT_UNCERT_ELLIP_STRU      stEllipPointUncertEllip;        /* ellipsoid_point_uncert_ellipse */
        AGPS_ELLIP_POINT_ALTI_STRU              stEllipPointAlti;               /* ellipsoid_point_alt */
        AGPS_ELLIP_POINT_ALTI_ELLIP_STRU        stEllipPointAltiEllip;          /* ellipsoid_point_alt_uncertellipse */
        AGPS_ELLIP_ARC_STRU                     stEllipArc;                     /* ellips_arc */
    } u;
} AGPS_ELF_SHAPE_DATA_STRU;

/*****************************************************************************
 �ṹ��    :  AGPS_ELF_LOCATION_PARA_STRU
 �ṹ˵��  :  AGPS_LOCATION_PARA_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpTime              : 1;
    VOS_UINT32                                  bitOpDirection         : 1;
    VOS_UINT32                                  bitOpSpare             : 30;

    VOS_UINT32                                  ulTime;                         /* time, ��GPS TOW������ͬ, INTEGER(0..14399999) */
    VOS_UINT8                                   ucDirection;                    /* direction, ӳ�䵽ˮƽ���������, INTEGER(0..359) */
    VOS_UINT8                                   aucReserved[3];
    AGPS_ELF_SHAPE_DATA_STRU                    stShapeData;                    /* shape_data */
} AGPS_ELF_LOCATION_PARA_STRU;

/*****************************************************************************
 �ṹ��    :  AGPS_ELF_LOCATION_INFO_STRU
 �ṹ˵��  :  AGPS_LOCATION_INFO_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpTimeOfFix         : 1;
    VOS_UINT32                                  bitOpSpare             : 31;

    AGPS_ELF_LOCATION_PARA_STRU                 stLocationPara;                 /* location_parameters,λ����Ϣ */
    VOS_UINT32                                  ulTimeOfFix;                    /* time_of_fix, ��ǰ����㲻ʹ�� */
} AGPS_ELF_LOCATION_INFO_STRU;

/*****************************************************************************
 �ṹ��    :  MTA_ELF_RRC_POSITION_CNF_STRU
 �ṹ˵��  :  MTA_RRC_POSITION_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;            /*_H2ASN_Skip*/

    VOS_UINT8                                           aucRsv[3];              /* ����λ */
    AGPS_POSITION_RESULT_TYPE_ENUM_UINT8                enUnionStructSelChoice;     /* �����Ϣ���� */
    union
    {
        AGPS_ELF_LOCATION_INFO_STRU                     stLocationInfo;         /* location,λ����Ϣ */
        AGPS_GPS_MEASURE_INFO_STRU                      stGpsMeasInfo;          /* GPS_meas,GPS������Ϣ */
        AGPS_POSITION_GPS_ADDITION_ASSIST_REQ_STRU      stAssistDataReq;        /* GPS_assist_req,������������ */
        AGPS_POSITION_ERR_STRU                          stPosErr;               /* pos_err,λ�ô�����Ϣ */
    }u;
}MTA_ELF_RRC_POSITION_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  RRC_ELF_MTA_QRY_NMR_CNF_STRU
 �ṹ˵��  :  RRC_MTA_QRY_NMR_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     MsgHeader;          /* ��Ϣͷ    */     /*_H2ASN_Skip*/

    VOS_UINT32                                          enUnionStructSelChoice;
    union
    {
        RRC_MTA_UTRAN_NMR_STRU                          stUtranNMRData;
        RRC_MTA_GSM_NMR_STRU                            stGsmNMRData;
    }u;
} RRC_ELF_MTA_QRY_NMR_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  RRC_ELF_MTA_PLMN_FREQ_QRY_CNF_STRU
 �ṹ˵��  :  RRC_MTA_PLMN_FREQ_QRY_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��15��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stMsgHeader;            /*_H2ASN_Skip*/
    VOS_RATMODE_ENUM_UINT32                             enUnionStructSelChoice;                              /* ģʽ���� *//* _H2ASN_Replace VOS_UINT32 enRatType; */
    union
    {
        RRC_MTA_GSM_PLMN_FREQ_LIST_STRU                 stGsmFreqList;          /* GSM��Ƶ���б� */
        RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU               stWcdmaFreqList;        /* WCDMA��Ƶ���б� */
        RRC_MTA_LTE_PLMN_FREQ_LIST_STRU                 stLteFreqList;          /* LTE��Ƶ���б� */
    }u;
} RRC_ELF_MTA_PLMN_FREQ_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_ERROR_LOG_CTRL_IND_STRU
 �ṹ˵��  :  OM_ERROR_LOG_CTRL_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    VOS_UINT16                                          usModemID;
    OM_ELF_ERR_LOG_ALM_STATUS_ENUM_UINT8                ucAlmStatus;  /* �򿪻��߹ر�ERRLOG�ϱ����� 0:close 1:open */
    OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM_UINT8                ucAlmLevel;   /* �ϱ����� */
}OM_NAS_ELF_ERROR_LOG_CTRL_IND_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_ERR_LOG_REPORT_REQ_STRU
 �ṹ˵��  :  OM_ERR_LOG_REPORT_REQ_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    VOS_UINT16                                          usModemID;
    VOS_UINT8                                           aucRsv[2];
}OM_NAS_ELF_ERR_LOG_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_ERR_LOG_HEADER_STRU
 �ṹ˵��  :  OM_ERR_LOG_HEADER_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32                    ulMsgModuleId;
    VOS_UINT16                                          usModemId;
    NAS_ERR_LOG_ALM_ID_ENUM_U16                         usAlmId;
    OM_ELF_ERR_LOG_CTRL_LEVEL_ENUM_UINT16               usAlmLevel;
    NAS_ERR_LOG_ALM_TYPE_ENUM_U16                       usAlmType;
    VOS_UINT32                                          usAlmLowSlice;
    VOS_UINT32                                          usAlmHighSlice;
    VOS_UINT32                                          ulAlmLength;
}OM_NAS_ELF_ERR_LOG_HEADER_STRU;

/*****************************************************************************
 �ṹ��    :  NAS_ELF_ERR_LOG_MNTN_EVENT_STRU
 �ṹ˵��  :  NAS_ERR_LOG_MNTN_EVENT_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_NAS_ELF_ERR_LOG_HEADER_STRU                      stHeader;
    VOS_UINT32                                          ulCount;
}NAS_ELF_ERR_LOG_MNTN_EVENT_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_ERR_LOG_REPORT_CNF_STRU
 �ṹ˵��  :  OM_ERR_LOG_REPORT_CNF_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    OM_ERR_LOG_MSG_TYPE_ENUM_UINT32                     ulMsgType;
    VOS_UINT32                                          ulMsgSN;
    VOS_UINT32                                          ulRptlen;       /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    NAS_ELF_ERR_LOG_MNTN_EVENT_STRU                     stContent;      /* �������� */
}OM_NAS_ELF_ERR_LOG_REPORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_FTM_CTRL_IND_STRU
 �ṹ˵��  :  OM_FTM_CTRL_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    VOS_UINT16                                          usModemID;
    OM_ELF_FTM_CTRL_STATUS_ENUM_UINT8                   ucActionFlag; /* �򿪻��߹رչ���ģʽ�ϱ����� 0:close 1:open*/
    VOS_UINT8                                           aucRsv[1];
}OM_NAS_ELF_FTM_CTRL_IND_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_FTM_HEADER_STRU
 �ṹ˵��  :  OM_FTM_HEADER_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32                    ulMsgModuleId;
    VOS_UINT16                                          usModemId;
    NAS_ERR_LOG_FTM_PROJECT_ID_ENUM_U8                  usProjectId;
    VOS_UINT8                                           aucReserve[1];
    VOS_UINT32                                          ulProjectLength;
}OM_NAS_ELF_FTM_HEADER_STRU;

/*****************************************************************************
 �ṹ��    :  NAS_ELF_FTM_PTMSI_RPT_EVENT_STRU
 �ṹ˵��  :  NAS_FTM_PTMSI_RPT_EVENT_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    OM_NAS_ELF_FTM_HEADER_STRU                          stHeader;
    VOS_UINT8                                           aucPtmsi[NAS_FTM_MAX_PTMSI_LEN];    /* ptmsi������ */
}NAS_ELF_FTM_PTMSI_RPT_EVENT_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_FTM_REPROT_IND_STRU
 �ṹ˵��  :  OM_FTM_REPROT_IND_STRU�ṹ���ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    OM_ERR_LOG_MSG_TYPE_ENUM_UINT32                     ulMsgType;
    VOS_UINT32                                          ulMsgSN;
    VOS_UINT32                                          ulRptlen;      /* ����ģʽ�ϱ������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    NAS_ELF_FTM_PTMSI_RPT_EVENT_STRU                    stContent;     /* ����ģʽ�ϱ������� */
}OM_NAS_ELF_FTM_REPROT_IND_STRU;

/*****************************************************************************
 �ṹ��    :  NAS_ELF_ERR_LOG_ALM_MNTN_STRU
 �ṹ˵��  :  NAS_ERR_LOG_ALM_MNTN��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                          ulMsgName;
    NAS_ELF_ERR_LOG_MNTN_EVENT_STRU                     stContent;                          /* ��Ϣ���� */
}NAS_ELF_ERR_LOG_ALM_MNTN_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_INFO_CLT_REPORT_REQ_STRU
 �ṹ˵��  :  OM_INFO_CLT_REPORT_REQ_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    VOS_UINT16                                          usModemID;
    OM_INFO_CLT_SCENE_TYPE_ENUM_UINT16                  enSceneType;
    VOS_UINT32                                          ulMsgLen;
    MNTN_PLMN_ID_STRU                                   stContent;
}OM_NAS_ELF_INFO_CLT_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  OM_NAS_ELF_INFO_CLT_REPORT_CNF_STRU
 �ṹ˵��  :  OM_INFO_CLT_REPORT_CNF_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��16��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    OM_ELF_MTA_MSG_TYPE_ENUM_UINT32                     ulMsgName;
    OM_ERR_LOG_MSG_TYPE_ENUM_UINT32                     ulMsgType;
    VOS_UINT32                                          ulMsgSN;
    VOS_UINT32                                          ulRptLen;      /* ���������ϱ������ݳ���,���ulRptLenΪ0,aucContent���ݳ���ҲΪ0 */
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU             stContent; /* ���������ϱ������� */
} OM_NAS_ELF_INFO_CLT_REPORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MTC_CDMA_STATE_IND_STRU
 �ṹ˵��  :  TAF_MTC_CDMA_STATE_IND_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��17��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stHeader;
    TAF_MTC_CDMA_STATE_IND_STRU                         stSetCdmaConnSt;
} TAF_ELF_MTC_CDMA_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MTC_MODEM_CONN_STATUS_IND_STRU
 �ṹ˵��  :  TAF_MTC_MODEM_CONN_STATUS_IND_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��17��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stHeader;
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU                  stModemConnSt;
} TAF_ELF_MTC_MODEM_CONN_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    :  TAF_ELF_MTC_MODEM_CONN_STATUS_IND_STRU
 �ṹ˵��  :  TAF_ELF_MTC_USIMM_STATUS_IND_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��17��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stHeader;
    TAF_MTC_USIMM_STATUS_IND_STRU                       stUsimmState;
} TAF_ELF_MTC_USIMM_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTC_ELF_BEGIN_SESSION_IND_STRU
 �ṹ˵��  :  MTC_BEGIN_SESSION_IND_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��17��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stHeader;
    MTC_BEGIN_SESSION_IND_STRU                          stSessionInfo;
} MTC_ELF_BEGIN_SESSION_IND_STRU;

/*****************************************************************************
 �ṹ��    :  MTC_ELF_END_SESSION_IND_STRU
 �ṹ˵��  :  MTC_END_SESSION_IND_STRU��Ϣ��ӳ��ṹ��
 1.��    ��   : 2015��12��17��
   ��    ��   : h00360002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                     stHeader;
    MTC_END_SESSION_IND_STRU                            stEndSessionInfo;
} MTC_ELF_END_SESSION_IND_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

