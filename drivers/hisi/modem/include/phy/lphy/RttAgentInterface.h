/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RttAgentInterface.h
  �� �� ��   : ����
  ��    ��   : x00312156
  ��������   : 2015��1��27��
  ����޸�   :
  ��������   : ����RTT AGENT������ģ��Ľӿڣ�������A��Errlog
  �Ľӿڣ���TLPHY�Ľӿ�

  �����б�   :
  �޸���ʷ   :
------------------------------------------------------------------------------
  1.��    ��   : 	2015��1��27��
    ��    ��   : 	x00312156
    �޸�����   : 	�����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __RTTAGENT_INTERFACE_H__
#define __RTTAGENT_INTERFACE_H__


#ifndef LPS_RTT
#include "vos.h"
#else
#ifndef __DSP_PCLINT__
#define VOS_MSG_HEADER
#endif
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ERRLOG_STATUS_CLOSE   ( 0 )
#define ERRLOG_STATUS_OPEN    ( 1 )

#define TLPHY_ERR_LOG_CTRL_LEVEL_NULL         ( 0 )   /* ErrLog�ȼ�δ����*/
#define TLPHY_ERR_LOG_CTRL_LEVEL_CRITICAL     ( 1 )   /* ErrLog�ȼ�Ϊ���� */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MAJOR        ( 2 )   /* ErrLog�ȼ�Ϊ��Ҫ */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MINOR        ( 3 )   /* ErrLog�ȼ�Ϊ��Ҫ */
#define TLPHY_ERR_LOG_CTRL_LEVEL_WARNING      ( 4 )   /* ErrLog�ȼ�Ϊ��ʾ */

#define TLPHY_OM_SEND_MSG_COUNT               ( 3 )   /*TLPHYÿ�������ش�OM��Ϣ������*/
#define TLPHY_OM_SEND_CONTENT_LENGTH_IN_16BIT ( 2 )   /*TLPHY�ش�OM��Ϣ��Ϣ����*/
#define TLPHY_RTTAGENT_MSG_HEADLEN_IN_8BIT    ( 8 )   /* enMsgType+ulMsgLen ���ֽڳ���*/

#define TLPHY_RTTAGENT_AFCLOCK_STATUS_INFO_LENGTH_IN_16BIT  (2)       /*TLPHY���͸�RTT AGENT��AFC����״̬��Ϣ����*/
#define TLPHY_AGENT_RFICSSI_IND_LENGTH_IN_16BIT             (2)       /*TLPHY�ϱ���AGENT��RFIC�Ĵ�������ֵ��Ϣ����*/
#define UNLIMITED_COUNT_REPORT                              (65535)   /*�ϱ�����Ϊ���޴�*/

#ifndef MAX_CHR_BUFF
#define MAX_CHR_BUFF                          ( 256 )
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32
 ö��˵��  : TLPHY��RTT����֮�����Ϣ����
*****************************************************************************/
enum RTTAGENT_TLPHY_MSGTYPE_ENUM
{
    /* MBX ���͸�AGENT����Ϣ���� */
    MBX_TO_RTTAGENT_REQ = 0,
    /* TPHY���͸��������Ϣ���� */
    TPHY_AGENT_ERRLOG_REQ,                    /* TPHY�ϱ�MAS CHR������̬���� */
    TPHY_AGENT_STORE_OM_REQ,                  /* TPHY�ϱ�OM�������� */
    TPHY_AGENT_SEND_OM_REQ,                   /* TPHY�ϱ�OM�ش����� */
    TPHY_MAS_CHR_CONN_REQ,                    /* TPHY�ϱ�MAS CHR����̬���� */

    /* LPHY���͸��������Ϣ���� */
    LPHY_AGENT_ERRLOG_REQ = 32,               /* LPHY�ϱ�MAS CHR������̬���� */
    LPHY_AGENT_STORE_OM_REQ,                  /* LPHY�ϱ�OM�������� */
    LPHY_AGENT_SEND_OM_REQ,                   /* LPHY�ϱ�OM�ش����� */	
    LPHY_AGENT_PAGING_CRC_INFO,               /* LPHY�ϱ�PAGING CRC��Ϣ */
    LPHY_MAS_CHR_CONN_REQ,                    /* LPHY�ϱ�MAS CHR����̬���� */        
    LPHY_AGENT_RFIC_UNLOCK_INFO,              /* LPHY�ϱ�RFIC ʧ����Ϣ*/

    /*TLPHY ���͸��������Ϣ����*/
	TLPHY_AGENT_SEND_AFCLOCK_STATUS_INFO_CNF = 56,     /* TLPHY�ϱ�AFC����״̬����*/
	TLPHY_AGENT_TXRX_PARA_INFO,                           /* TLPHY�ϱ�TX PWR��Ϣ */
	TLPHY_AGENT_RFICSSI_IND,                           /* TLPHY�ϱ�RFIC�Ĵ�������ֵ */
	TLPHY_AGENT_REPORT_ERROR_INFO,

    /* ������RTT AGENT���͸�TLPHY����Ϣ���� */
    AGENT_TO_TLPHY_INFO_START = 63,

    AGENT_TLPHY_ERRLOG_CTRL_INFO,             /* �����͸�TLPHY ��ERRLOG���� */
    /* �����͸�TPHY ����Ϣ���� */
    AGENT_TPHY_SEND_OM_CNF,                   /* TPHY OM��Ϣ�ش�ȷ�� */

    /* �����͸�LPHY ����Ϣ���� */
    AGENT_LPHY_SEND_OM_CNF,                   /* LPHY OM��Ϣ�ش�ȷ�� */

	AGENT_TLPHY_AFC_STATUS_REQ,                /* �����͸�������AFC����״̬�ϱ�����*/
	AGENT_TLPHY_TXRX_PARA_INFO_REQ,             /* �����͸�TLPHY������Tx Power��Ϣ��ѯ����*/
	AGENT_TLPHY_RFICSSIRD_REQ,                /*AGENT���͸�TLPHY��RFIC�Ĵ�������ֵ��ѯ����*/

    /* װ���ں� */
    TLPHY_TO_EQUIP_NOTIFY,                    /* AGENT -> AGENT */

    AGENT_TLPHY_MSG_BUTT
};
typedef VOS_UINT32 RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : TLPHY_MTA_AFCLOCK_STATUS_ENUM
ö��˵��  : GPS �ο�ʱ��Ƶ������״̬ö��
*****************************************************************************/
enum TLPHY_MTA_AFCLOCK_STATUS_ENUM
{
    TLPHY_MTA_AFCLOCK_UNLOCKED = 0,    /*GPS �ο�ʱ��Ƶ�ʷ�����״̬*/
    TLPHY_MTA_AFCLOCK_LOCKED,          /*GPS �ο�ʱ��Ƶ������״̬*/
    TLPHY_MTA_AFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 TLPHY_MTA_AFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
ö����    : RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM
ö��˵��  : AFC ����״̬�ϱ�����ö��
*****************************************************************************/
enum RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM
{
    RTTAGENT_STOP_REPORT_CONTROL_FLAG = 0,    /* ֹͣ�ϱ����Ʊ�� */
    RTTAGENT_ALLOW_REPORT_CONTROL_FLAG,       /* �����ϱ����Ʊ�� */
    RTTAGENT_REPORT_CONTROL_FLAG_BUTT
};
typedef VOS_UINT16 RTTAGENT_AFCLOCK_STATUS_REPORT_CONTROL_FLAG_ENUM_UINT16;
/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TPHY_ERRLOG_TAS_INFO_STRU
 �ṹ˵��  :TPHY��A��Errlog֮��Ľӿ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;     /* TAS�л���ʱ��� */
    VOS_UINT16         usDpdtState;          /* �л����DPDT״̬��0ֱͨ��1���� */
    VOS_INT16          ssAntValuemain;       /* �л�����������߽����źŲ���ֵ */
    VOS_INT16          ssSwitchDelta;        /* �������߲���ֵDelta */
    VOS_UINT16         usBlankType;          /* �л�ʱ��״̬ */
    VOS_UINT16         usTsEn;               /* �Ƿ���TAS��Ȩ��0����Ȩ��1����Ȩ */
    VOS_UINT16         usAgentSwitchFlag;    /* �Ƿ�Ϊ�����л���0�Ǵ����У�1������ */
    VOS_UINT16         usTasState;           /* �л�ʱ��TAS״̬��HAPPY/UNHAPPY �� */
    VOS_UINT16         usReserve;            /* Ԥ�����������ֽڶ��� */
}TPHY_ERRLOG_TAS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPHY_ERRLOG_TAS_INFO_STRU
 �ṹ˵��  :LPHY��A��Errlog֮��Ľӿ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;      /* TAS�л���ʱ��� */
    VOS_UINT16         usDpdtState;           /* �л����DPDT״̬��0ֱͨ��1���� */
    VOS_INT16          ssAntValuemain;        /* �л�����������߽����źŲ���ֵ */
    VOS_INT16          ssSwitchDelta;         /* �������߲���ֵDelta */
    VOS_UINT16         usBlankType;           /* �л�ʱ��״̬ */
    VOS_UINT16         usTsEn;                /* �Ƿ���TAS��Ȩ��0����Ȩ��1����Ȩ */
    VOS_UINT16         usAgentSwitchFlag;     /* �Ƿ�Ϊ�����л���0�Ǵ����У�1������ */
    VOS_UINT16         usTasState;            /* �л�ʱ��TAS״̬��HAPPY/UNHAPPY �� */
    VOS_UINT16         usReserve;             /* Ԥ�����������ֽڶ��� */
}LPHY_ERRLOG_TAS_INFO_STRU;

typedef struct
{
    VOS_UINT8                ucConnDpdtState;       /* �л����DPDT״̬��
                                                                                        0 : TASֱͨ/MASֱͨ,
                                                                                        1 : TAS����/MASֱͨ,
                                                                                        2 : TASֱͨ/MAS����,
                                                                                        3 : TAS����/MAS����,*/
    VOS_INT8                 ucConnDpdtAlgo;       /* ����̬���С�ä���㷨�� 0 : ���� , 1 : ä�� */
    VOS_INT8                 ucConnMasState;       /* ����̬MAS�㷨�׶�
                                                                                        LTE_ASU_STATE_STABLE   = 0,0 ��̬����������GOOD���޽׶�
                                                                                        LTE_ASU_STATE_TAS  1
                                                                                        LTE_ASU_STATE_MAS  2
                                                                                        LTE_ASU_STATE_XTAS 3
                                                                                        LTE_ASU_STATE_HYST 4     ���ڶ���̬���˽׶��㷨��������*/
    VOS_UINT8                ucCompareAnt;         /*  1st byte: current use,  2nd byte: Target compare
                                                                                           (ex: 0x23 = Current:Ant2, Compare:Ant3)*/
}TLPHY_MAS_CONNECTED_STATE_INFO_STRU;

typedef struct
{
    VOS_UINT32                ulSwitchSlice;         /*  �л�ʱ��� */
    VOS_UINT16                usSwitchDirection;     /* �л����߷���
                                                                                             1st byte: Source,  2nd byte: Target
                                                                                              (ex: 0x23 = ��ant2�е�ant3)    */
    VOS_INT16                 ssSwitchBefSignal;     /* �л�ǰ����RSCP/RSRP*/
    VOS_INT16                 ssSwitchAftSignal;     /* �л������RSCP/RSRP*/
    VOS_INT16                 ssSwitchBefTxPower;    /* �л�ǰ���书��  */
    VOS_INT16                 ssSwitchAftTxPower;    /* �л����书��  */
    VOS_UINT16                usReserve;            /* Ԥ�����������ֽڶ��� */
}TLPHY_MAS_SWITCH_STATE_INFO_STRU;

typedef struct
{
    TLPHY_MAS_SWITCH_STATE_INFO_STRU stWholeSwitchState;    /* �����л� */
    TLPHY_MAS_SWITCH_STATE_INFO_STRU stSignalSwitchState;    /* �����л� */
    VOS_UINT16                       usBand;                /* �л���Ƶ�� */
    VOS_UINT16                       usSwitchRoundCnt;      /* �л��Ƚϴ���
                                                                                                    1st byte: Round#,  2nd byte: Count#
                                                                                                    (ex: 0x23 = Round2 Count3)*/

}TLPHY_MAS_CONNECTED_DPDT_INFO_STRU;

typedef struct
{
    VOS_UINT32                ulCompareSlice;       /* �ȽϽ׶ε�ʱ��� */
    VOS_UINT16                usCompareBand;        /* �ȽϽ׶ε�Ƶ�� */
    VOS_INT16                 ssCompareAnt0Signal;  /* �ȽϽ׶�����0����RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt1Signal;  /* �ȽϽ׶�����1����RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt2Signal;  /* �ȽϽ׶�����2����RSCP/RSRP*/
    VOS_INT16                 ssCompareAnt3Signal;  /* �ȽϽ׶�����3����RSCP/RSRP*/
    VOS_UINT16                usReserve;            /* Ԥ�����������ֽڶ��� */
}TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU;

typedef struct
{
    VOS_UINT8                 ucNonConnDpdtStatus; /* �л����DPDT״̬��
                                                                                       0 : TASֱͨ/MASֱͨ,
                                                                                       1 : TAS����/MASֱͨ,
                                                                                       2 : TASֱͨ/MAS����,
                                                                                       3 : TAS����/MAS����,*/
    VOS_UINT8                 ucNonConnMasAlgo;    /* ������̬��״̬ , 1: Searching ,  2: Access, 3 : Idle */
    VOS_UINT8                 ucAgentFlag;         /* �����Ƿ���Ч */
    VOS_UINT8                 ucIdleSwitchStaus;   /*idle �л����Ƿ���happy״̬��0 : Fail , 1 : Success*/
}TLPHY_MAS_NONCONN_STATE_INFO_STRU;

typedef struct
{
    VOS_UINT8                 ucMasAuthorizeFlag;  /*Mas����Ȩ״̬                                                   
                                                                                      0 : TAS��/MAS��,
                                                                                     1 : TAS��/MAS��,
                                                                                     2 : TAS��/MAS��,
                                                                                     3 : TAS��/MAS��,*/
    VOS_UINT8                 ucIdleHappyState; /*  TAS_REPORT_STATE_IDLE_UNHAPPY = 0,
                                                                                     TAS_REPORT_STATE_IDLE_HAPPY   = 1, */
    VOS_UINT8                 ucSignalState;    /* 
                                                                                     TAS_REPORT_STATE_IDLE_POOR = 0,
                                                                                     TAS_REPORT_STATE_IDLE_GOOD = 1,
                                                                                     TAS_REPORT_STATE_CONN_POOR = 0, 
                                                                                     TAS_REPORT_STATE_CONN_GOOD = 1 */
    VOS_UINT8                 ucRsv;                 
}TLPHY_MAS_Current_STATE_INFO_STRU;

typedef struct
{
    TLPHY_MAS_NONCONN_STATE_INFO_STRU           stMasNonConnState;
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
    TLPHY_MAS_CONNECTED_STATE_INFO_STRU         stMasConnState;
    TLPHY_MAS_CONNECTED_DPDT_INFO_STRU          stMasConnDpdt;
    TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU       stMasConnCompare;
    VOS_UINT16                                  usRlfAuthorizeFlag;
    VOS_UINT16                                  usRsv;
}TLPHY_ERRLOG_MAS_INFO_STRU;

typedef struct
{
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
    TLPHY_MAS_CONNECTED_STATE_INFO_STRU         stMasConnState;
    TLPHY_MAS_CONNECTED_DPDT_INFO_STRU          stMasConnDpdt;
    TLPHY_MAS_CONNECTED_COMPARE_INFO_STRU       stMasConnCompare;
    VOS_UINT16                                  usRlfAuthorizeFlag;
    VOS_UINT16                                  usRsv;
}TLPHY_CONN_MAS_INFO_STRU;

typedef struct
{
    TLPHY_MAS_NONCONN_STATE_INFO_STRU           stMasNonConnState;
    TLPHY_MAS_Current_STATE_INFO_STRU           stMasCurrentState;
}TLPHY_NONCONN_MAS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RTTAGENT_TLPHY_MSG_STRU
 �ṹ˵��  :RTT AGENT��TLPHY�Ľӿ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;       /* ��Ϣ���� */
    VOS_UINT32                            ulMsgLen;        /* ��Ϣ���ȣcacuContent��ʵ���ֳ��� */
    VOS_UINT8                             aucContent[4];   /* ��Ϣ���� */
}RTTAGENT_TLPHY_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TPHY_AGENT_ERRLOG_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л�������̬�ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;        /* ��Ϣ����ΪTPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                            ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_TPHY_TAS_INFO_STRU) /2*/
    TLPHY_NONCONN_MAS_INFO_STRU           stTphyMasInfo;    /* TPHY�����л��ؼ���Ϣ */
}TPHY_AGENT_ERRLOG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TPHY_MAS_CHR_CONN_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л�����̬�ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;        /* ��Ϣ����ΪTPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                            ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_TPHY_TAS_INFO_STRU) /2*/
    TLPHY_CONN_MAS_INFO_STRU              stTphyMasInfo;    /* TPHY�����л��ؼ���Ϣ */
}TPHY_MAS_CHR_CONN_REQ_STRU;

/*****************************************************************************
 �ṹ��    :LPHY_AGENT_ERRLOG_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л�������̬�ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;        /* ��Ϣ����ΪLPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                             ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_LPHY_TAS_INFO_STRU) /2*/
    TLPHY_NONCONN_MAS_INFO_STRU            stLphyMasInfo;    /* LPHY�����л��ؼ���Ϣ */
}LPHY_AGENT_ERRLOG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :LPHY_MAS_CHR_CONN_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л�����̬�ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;        /* ��Ϣ����ΪLPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                             ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_LPHY_TAS_INFO_STRU) /2*/
    TLPHY_CONN_MAS_INFO_STRU               stLphyMasInfo;    /* LPHY�����л��ؼ���Ϣ */
}LPHY_MAS_CHR_CONN_REQ_STRU;


/*****************************************************************************
 �ṹ��    : TLPHY_AGENT_SEND_OM_REQ_STRU
 �ṹ˵��  :RTT AGENT��TLPHY��OM�ش���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;         /* ��Ϣ����ΪTPHY_AGENT_SEND_OM_REQ��LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                             ulMsgLen;          /* ��Ϣ����Ϊ2 */
    VOS_UINT32                             ulOmSendMsgCount;  /* �ط���OM��Ϣ���� */
}TLPHY_AGENT_SEND_OM_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AGENT_TLPHY_SEND_OM_CNF_STRU
 �ṹ˵��  :RTT AGENT��TLPHY��OM�ش���Ϣȷ�Ͻṹ��
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* ��Ϣ����ΪAGENT_TPHY_SEND_OM_CNF��AGENT_LPHY_SEND_OM_CNF */
    VOS_UINT32                             ulMsgLen;           /* ��Ϣ����Ϊ2 */
    VOS_UINT32                             ulOmRemainMsgCount; /* ʣ���OM��Ϣ���� */
}AGENT_TLPHY_SEND_OM_CNF_STRU;

/*****************************************************************************
�ṹ��    : AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU
�ṹ˵��  : RTT AGENTת����TLPHY��ERRLOG������Ϣ
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* ��Ϣ����ΪAGENT_TLPHY_ERRLOG_CTRL_INFO */
    VOS_UINT32                             ulMsgLen;           /* ��Ϣ����Ϊ2 */
    VOS_UINT16                             usErrLogCtrlFlag;   /* ERRLOG�򿪱�ʶ��0�رգ�1�� */
    VOS_UINT16                             usAlmLevel;         /* ERRLOG�ϱ����� */
}AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TLPHY_MTA_AFCLOCK_STATUS_RPT_STRU
 �ṹ˵��  : TLPHY �ϱ���RTT AGENT��AFC����״̬��Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //��Ϣ����
    VOS_UINT32                                ulMsgLen;  //��Ϣ����
    TLPHY_MTA_AFCLOCK_STATUS_ENUM_UINT16      enStatus;  //����״̬
    VOS_UINT16                                ausReserved1[1];
}TLPHY_AGENT_AFCLOCK_STATUS_RPT_STRU;

/*****************************************************************************
 �ṹ��    : TLPHY_AGENT_REPORT_ERROR_RPT_STRU
 �ṹ˵��  : TLPHY �ϱ���RTT AGENT�����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulCount;  //ERROR COUNT;
}TLPHY_REPORT_ERROR_MESSAGE_STRU;

typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //��Ϣ����
    VOS_UINT32                                ulMsgLen;  //��Ϣ����
    TLPHY_REPORT_ERROR_MESSAGE_STRU           stMessage;
}TLPHY_AGENT_REPORT_ERROR_RPT_STRU;


/*****************************************************************************
 �ṹ��    : AGENT_TLPHY_AFCLOCK_STATUS_RPT_NTF_STRU
 �ṹ˵��  : ��RTT Agent�·���TLPHY��AFC����״̬��ѯ��Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType; //��Ϣ����
    VOS_UINT32                                ulMsgLen;  //��Ϣ����
    VOS_UINT16                                usReportCtrolFlag;   //0:ֹͣ�ϱ���1:�����ϱ������޴��ϱ�ʱ��Ҫ�·�ֹͣ�ϱ�ʱ��ֹͣ�ϱ����������DSP�ϱ������ﵽ������ʱ��ֹͣ�ϱ�
    VOS_UINT16                                usReportCount;       //�ϱ�����������0xffff�����޴��ϱ�
    VOS_UINT16                                usReportDuration;    //�ϱ��������msΪ��λ������Ϊ10ms�����������ϱ���������1ʱ��Ч
    VOS_UINT16                                ausReserved[1];
}AGENT_TLPHY_AFCLOCK_STATUS_RPT_NTF_STRU;

/*****************************************************************************
 �ṹ��    : AGENT_TLPHY_RFICSSIRD_REQ_STRU
 �ṹ˵��  : ��RTT Agent�·���TLPHY��RFIC SSI�Ĵ���ֵ��ѯ��Ϣ�ṹ��

 1.��    �� : 2015��11��12��
   ��    �� : l00314907
   �������� : �½�
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                                ulMsgLen;
    VOS_UINT16                                usChannelNo;    /* RFICͨ���� */
    VOS_UINT16                                usRficReg;      /* �Ĵ�����ַ */
}AGENT_TLPHY_RFICSSIRD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TLPHY_AGENT_RFICSSIRD_IND_STRU
 �ṹ˵��  : TLPHY�ϱ���RTT Agent��RFIC SSI�Ĵ���ֵ��Ϣ�ṹ��

 1.��    �� : 2015��11��12��
   ��    �� : l00314907
   �������� : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32        enMsgType;   //��Ϣ����
    VOS_UINT32                                ulMsgLen;    //��Ϣ����
    VOS_UINT32                                ulRegValue;  //�Ĵ�������ֵ
}TLPHY_AGENT_RFICSSIRD_IND_STRU;
/*****************************************************************************
�ṹ��    : TLPHY_AGENT_PAGING_CRC_STRU
�ṹ˵��  :LPHY���͸�RTT AGENT��PAGING CRC��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* ��Ϣ����ΪTPHY_AGENT_SEND_OM_REQ��LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                            ulMsgLen;          /* ��Ϣ����Ϊ16bit ���ȣ�6*/
    INT32                                 lRsrp;             /* Paging crc failʱ��RSRPֵ*/
    INT32                                 lRsrq;             /* Paging crc failʱ��RSRQֵ*/
    INT16                                 sSnrR0;            /* Paging crc failʱ����0��SNRֵ*/
    INT16                                 sSnrR1;            /* Paging crc failʱ����1��SNRֵ*/
}TLPHY_AGENT_PAGING_CRC_STRU;

/*****************************************************************************
�ṹ��    : TLPHY_AGENT_PAGING_CRC_STRU
�ṹ˵��  :LPHY���͸�RTT AGENT��PAGING CRC��Ϣ
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* ��Ϣ����ΪTPHY_AGENT_SEND_OM_REQ��LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                            ulMsgLen;          /* ��Ϣ����Ϊ16bit ���ȣ�6*/
    UINT32                                aulRfeInfo[MAX_CHR_BUFF];
}TLPHY_AGENT_RFIC_INFO_STRU;
typedef struct
{
    INT16                             sRsrp;
    INT16                             sRsrq;
}EMU_CHR_RPT_PARA_STRU;

/*****************************************************************************
�ṹ��    : MBX_TLPHY_CHR_RPT_PARA
�ṹ˵��  : TLPHY�ϱ���MBX�����ϱ���CHR�Ľṹ��֧����չ
*****************************************************************************/

typedef struct
{
    UINT16                            usCellId;
    UINT16                            usDlFreqInfo;
    UINT16                            usUlFreqInfo;
    UINT16                            usBandInd;
    EMU_CHR_RPT_PARA_STRU             stEmuRptPara;
}TLPHY_CHR_RPT_PARA_STRU;

/*****************************************************************************
�ṹ��    : TLPHY_AGENT_TXRX_PARA_STRU
�ṹ˵��  :LPHY���͸�RTT AGENG������TX PWR��Ϣ
*****************************************************************************/
typedef struct
{
	VOS_MSG_HEADER
	RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* ��Ϣ���� */
	VOS_UINT32                            ulMsgLen;          /* ��Ϣ����Ϊ */
    TLPHY_CHR_RPT_PARA_STRU               stRptPara;
	VOS_UINT32                            ulTimeStamp;       /* NAS�·�����ǰ���һ�����з��Ͷ�Ӧ��ʱ��� */
    VOS_INT32                             lUlTxPwr;          /* NAS�·�����ǰ���һ�����з��Ͷ�Ӧ�ķ��͹��� */
}TLPHY_AGENT_TXRX_PARA_STRU;


/*****************************************************************************
�ṹ��    : AGENT_TLPHY_TXRX_INFO_REQ_STRU
�ṹ˵��  :LPHY���͸�RTT AGENG������TX PWR��Ϣ
*****************************************************************************/
typedef struct
{
	RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;         /* ��Ϣ���� */
	VOS_UINT32                            ulMsgLen;          /* ��Ϣ����Ϊ2 */
	VOS_UINT32                            ulTxPowerReqCnt;       /* RTT Agent��TLPHY����TX PWR������� */
}AGENT_TLPHY_TXRX_INFO_REQ_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RTTAGENT_INTERFACE_H__ */
