/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgSmCommProc.h
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��20��
  ����޸�   :
  ��������   : �ṩ����ģ�鹫���Ķ���ͽӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��20��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2008��6��16��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�ţ�AT2D03830, �޸�en_NV_Item_SMS_SERVICE_Para���д��ش���
  3.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D03741,��̹淶���⣺   1��ö�����Ͷ���   2��ȫ�ֱ������ⲿ����   3���ļ�������ע�����⣻   ��ӡ��Ϣ������   1�����ӵ��Դ�ӡ����
  4.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D04609,CMMS��������ӣ�
  5.��    ��   : 2008��10��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06152��AT2D06151��, USIMM�Ż������SMSP�ļ���ض�д����ʧ��
  6.��    ��   : 2008��12��25��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D07869, SIM���ж���Ϣ�洢���������һ����Ҫ�洢�Ķ������������ģ��д(U)SIM����SMSS�ļ�ʧ��
  7.��    ��   : 2009��3��25��
    ��    ��   : �ܾ� 40661
    �޸�����   : ���ⵥ�� AT2D08875,PS�������Ͷ��ţ�ʧ��
  8.��    ��   : 2009��4��1��
    ��    ��   : �ܾ� 40661
    �޸�����   : ���ⵥ��:AT2D09786, ��AT+CMGD=,4ɾ������ʱ����ʱ�䲻��Ӧ�������Զ����ű���ⲻ������
  9.��    ��   : 2009��05��11��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D11136��PICS������Ϊ��֧��SM�洢��ִ��GCF��������34.2.5.3����������ʧ��
 10.��    ��   : 2009��05��15��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D11703�����ڹ�������,�����ڴ�ʧ��,���µ��帴λ
 11.��    ��   : 2009��7��18��
    ��    ��   : z40661
    �޸�����   : �ն˿������������
 12.��    ��   : 2009��07��24��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13258��ִ��AT&F0�ָ��������ú󣬶��Ź��ܲ�����
 13.��    ��   : 2009��08��02��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13420������SIM��������ù����У�UE��λ�������ò����޷��أ�
 14.��    ��   : 2009��08��7��
    ��    ��   : f62575
    �޸�����   : STK���Ժ���
 15.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
 16.��    ��   : 2009��12��31��
    ��    ��   : f62575
    �޸�����   : PC����׮���룻
 17.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : AT2D16304, STK PP DOWN�������ƺ�SMS��ص�(U)SIM�ļ�REFRESH
 18.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
 19.��    ��   : 2010��04��30��
    ��    ��   : F62575
    �޸�����   : ���ⵥ��AT2D15403
                 ������CMT��ʽ�ϱ���CSMS����Ϊ1ʱ��Ӧ�ò��·�CNMA����ȷ���¶��Ž���,
                 ��������żȲ��ϱ�Ҳ���洢������;
 20.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
******************************************************************************/
#ifndef __MNMSGCOMMPROC_H__
#define __MNMSGCOMMPROC_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "MnMsgApi.h"
#include  "UsimPsInterface.h"
#include  "MnComm.h"

/* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
#include "NasSms.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif
/* Modified by z00161729 for DCM�����������������, 2012-8-20, end */

/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
#include "siappstk.h"
/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

#include "TafMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
/*----------------------------EF ID(31.102)-------------------------------------*/
#define  EF_SMS_INVALID_ID                                  0xFFFF

/*----------------------------EF SMS STATUS(31.102)-----------------------------*/
#define  EF_SMS_STATUS_FREE_SPACE                           0x00                /*��λ��*/
#define  EF_SMS_STATUS_USED_SPACE                           0x01                /*��ʹ�õ�λ��*/
#define  EF_SMS_STATUS_MT_READ                              0x01                /*���յ����Ķ�����Ϣ*/
#define  EF_SMS_STATUS_MT_TO_BE_READ                        0x03                /*���յ�δ�Ķ�����Ϣ*/
#define  EF_SMS_STATUS_MO_TO_BE_SEND                        0x07                /*MOδ���͵���Ϣ*/
#define  EF_SMS_STATUS_MO_SEND_TO_NT                        0x05                /*MO�ѷ��͵��������Ϣ*/
#define  EF_SMS_STATUS_NO_SRR                               0x05                /*δ����״̬�������Ϣ*/
#define  EF_SMS_STATUS_SRR_NOT_RCV                          0x0D                /*����״̬���浫δ�յ�״̬�������Ϣ*/
#define  EF_SMS_STATUS_SRR_RCV_NOT_STOR                     0x15                /*���յ�״̬����δ�洢����Ϣ*/
#define  EF_SMS_STATUS_SRR_RCV_STOR                         0x1D                /*���յ�״̬�����Ҵ洢����Ϣ*/

/*-------------------------EF SMS STATUS REPORT(31.102)-------------------------*/
#define  EF_SMS_STATUS_REPORT_EMPTY                         0x00                /*״̬����Ϊ��*/

#define  MN_MSG_MAX_TPDU_LEN                                232
#define  MN_MSG_TPMR_POS                                    0x01

#define  MN_MSG_EFSMS_LEN                                   176                 /*EFSMS�ļ��ĳ���*/
#define  MN_MSG_EFSMSR_LEN                                  30                  /*EFSMSR�ļ��ĳ���*/

#define  MN_MSG_NO_AVAILABLE_REC                            0xff                /*�鿴USIM��NVIM�п��еļ�¼��*/
#define  MN_MSG_NO_AVAILABLE_SMS_REC                        0xffffffff                /*�鿴USIM��NVIM�п��еļ�¼��*/

#define  MN_MSG_SIM_EXIST                                   1                   /*����SIM��*/
#define  MN_MSG_SIM_NOT_EXIST                               0                   /*������SIM��*/

#define  MN_MSG_MAX_DELETE_REC_NUM                          10                  /*SMAһ���ܹ�ɾ���ļ�¼��Ŀ*/
#define  MN_MSG_MAX_ORG_REC_NUM                             10                  /*�����ڴ���ԭʼ���ŵ�����*/

#define  MN_MSG_MAX_RPDATA_LEN                              248                 /*23040 7.3.1.2 RP DATA (Mobile Station to Network)����*/

#define  MN_MSG_USIM_DEF_REC                                0

#define MN_MSG_SIM_MEM_FULL_SET                             0xFE
#define MN_MSG_SIM_MEM_FULL_UNSET                           0xFF

/*DEVICE ID*/
#define  MN_MSG_DEVICE_NETWORK                              83
#define  MN_MSG_DEVICE_UICC                                 81

#define  MN_MSG_NV_SMSP_VOLUME                              1
#define  MN_MSG_FILE_NONE_REC                               0

#define MN_MSG_PC_REPLAY_MSG_PART1                          (ID_TAF_PC_REPLAY_BASE + 0x01)              /* ΪPC���̻طŶ������Ϣ */
#define MN_MSG_PC_REPLAY_MSG_PART2                          (ID_TAF_PC_REPLAY_BASE + 0x02)              /* ΪPC���̻طŶ������Ϣ */
#define MN_MSG_PC_REPLAY_MSG_PART3                          (ID_TAF_PC_REPLAY_BASE + 0x03)              /* ΪPC���̻طŶ������Ϣ */

#define MN_MSG_USIM_ENVELOPE_RSP_UNKNOWN_ERROR              (0x6F00)            /* �����ͨSIM��MO SMS Ctrl���� */

#ifdef __PS_WIN32_RECUR__
VOS_UINT32 NAS_MSG_RestoreContextData(struct MsgCB * pMsg);
#endif

#define MN_MSG_MAX_CHG_SM_STATE_NUM                         20
/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/*****************************************************************************
 ö����    : MN_MSG_MT_CUSTOMIZE_ENUM
 �ṹ˵��  : ���Ž��ն�������
  1.��    ��   : 2012��11��07��
    ��    ��   : f62575
    �޸�����   : ���Ž��ն��Ʊ�־
                 MN_MSG_MT_CUSTOMIZE_NONE       �޶��ƣ�
                 MN_MSG_MT_CUSTOMIZE_DCM        DCM����
*****************************************************************************/
enum MN_MSG_MT_CUSTOMIZE_ENUM
{
    MN_MSG_MT_CUSTOMIZE_NONE,
    MN_MSG_MT_CUSTOMIZE_DCM,
    MN_MSG_MT_CUSTOMIZE_BUTT
} ;
typedef VOS_UINT8 MN_MSG_MT_CUSTOMIZE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MN_MSG_MO_STATE_ENUM
 �ṹ˵��  : ���ŷ���ʵ��״̬
             MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP: �ȴ�FDN �������
             MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP:  �ȴ�SMS MO CONTROL �������
             MN_MSG_MO_STATE_WAIT_REPORT_IND:    �ȴ����ŷ��������ȷ�Ͻ����
1.��    ��   : 2012��02��23��
  ��    ��   : ��ӳ��/f62575
  �޸�����   : ����MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP״̬
*****************************************************************************/
enum MN_MSG_MO_STATE_ENUM
{
    MN_MSG_MO_STATE_NULL                                    = 0,                /*����*/
    MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP                      = 1,
    MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP                       = 2,                /*�ȴ�USIM��MO SMS CONTROL ������Ӧ��Ϣ*/
    MN_MSG_MO_STATE_WAIT_REPORT_IND                         = 3,                /*�ȴ�����ָʾ*/
    MN_MSG_MO_STATE_MAX
} ;
typedef VOS_UINT8   MN_MSG_MO_STATE_ENUM_U8;

enum MN_MSG_MT_STATE_ENUM
{
    MN_MSG_MT_STATE_NULL                                    = 0,                /*����*/
    MN_MSG_MT_STATE_WAIT_REPORT_REQ                         = 2,                /*�ȴ�����ָʾ*/
    MN_MSG_MT_STATE_MAX
};
typedef VOS_UINT8   MN_MSG_MT_STATE_ENUM_U8;

enum MN_MSG_MO_TYPE_ENUM
{
    MN_MSG_MO_TYPE_MO,
    MN_MSG_MO_TYPE_SMMA,
    MN_MSG_MO_TYPE_BUFFER_STK,
    MN_MSG_MO_TYPE_MAX
};
typedef VOS_UINT8   MN_MSG_MO_TYPE_ENUM_U8;

enum MN_MSG_MO_SEND_FROM_ENUM
{
    MN_MSG_MO_SEND_FROM_CLIENT,
    MN_MSG_MO_SEND_FROM_MEM,
    MN_MSG_MO_SEND_FROM_MAX
};
typedef VOS_UINT8 MN_MSG_MO_SEND_FROM_ENUM_U8;

enum MN_MSG_USIM_ACTION_ENUM
{
    MN_MSG_USIM_READ,
    MN_MSG_USIM_LIST,
    MN_MSG_USIM_WRITE,
    MN_MSG_USIM_DELETE,
    MN_MSG_USIM_WRITE_EFSMSP,
    MN_MSG_USIM_DELETE_EFSMSP,
    MN_MSG_USIM_MODIFYSTATUS,
    MN_MSG_USIM_DELETE_STARPT,
    MN_MSG_USIM_RCVNEWMSG,
    MN_MSG_USIM_RCVSTARPT,
    MN_MSG_USIM_SEND,
    MN_MSG_USIM_RCVMORPT,
    MN_MSG_USIM_SET_EFSMSS,
    MN_MSG_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_USIM_ACTION_ENUM_U8;

enum MN_MSG_SET_USIM_ENUM
{
    MN_MSG_SET_USIM_LIST,
    MN_MSG_SET_USIM_DELETE,
    MN_MSG_SET_USIM_DELETE_BEGIN,
    MN_MSG_SET_USIM_DELETE_STARPT,
    MN_MSG_SET_USIM_DELETE_STARPT_BEGIN,
    MN_MSG_SET_USIM_DELETE_EFSMSP,
    MN_MSG_SET_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_SET_USIM_ENUM_U8;

enum MN_MSG_USIM_POWER_STATE_ENUM
{
    MN_MSG_USIM_POWER_BEGIN,
    MN_MSG_USIM_POWER_WAIT_EFSMSS,
    MN_MSG_USIM_POWER_WAIT_EFSMSP,
    MN_MSG_USIM_POWER_WAIT_EFSMSREC,
    MN_MSG_USIM_POWER_WAIT_EFSMS,
    MN_MSG_USIM_POWER_WAIT_EFSMSR,
    MN_MSG_USIM_POWER_ON
};
typedef VOS_UINT8 MN_MSG_USIM_POWER_STATE_ENUM_U8;

enum MN_MSG_SEND_FAIL_FLAG
{
    MN_MSG_SEND_FAIL_NO_DOMAIN,
    MN_MSG_SEND_FAIL_PS_DOMAIN,
    MN_MSG_SEND_FAIL_CS_DOMAIN,
    MN_MSG_SEND_FAIL_CSPS_DOMAIN
};
typedef VOS_UINT8 MN_MSG_SEND_FAIL_FLAG_U8;

enum MN_MSG_DOMAIN_AVAIL_FLAG
{
    MN_MSG_NO_DOMAIN_AVAIL,
    MN_MSG_PS_DOMAIN_AVAIL,
    MN_MSG_CS_DOMAIN_AVAIL,
    MN_MSG_CSPS_DOMAIN_AVAIL
};
typedef VOS_UINT8 MN_MSG_DOMAIN_AVAIL_FLAG_U8;

enum MN_MSG_RETRY_FLAG
{
    MN_MSG_RETRY_OFF,                                                           /* �ط�����δ���� */
    MN_MSG_RETRY_BEGIN,                                                         /* �ط���ʼ */
    MN_MSG_RETRY_END                                                            /* �ط����� */
};
typedef VOS_UINT8 MN_MSG_RETRY_FLAG_U8;



/*****************************************************************************
 �ṹ��    : MN_MSG_SMS_BUFFER_CAP_STRU
 �ṹ˵��  : MSG�Ķ��ŷ���ʵ�建������
             ucBufferNum �����Ի���Ĵ����Ͷ�����
  1.��    ��   : 2012��09��07��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBufferNum;
    VOS_UINT8                           aucReserved1[3];
}MN_MSG_SMS_BUFFER_CAP_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           ucRecIndex;                             /*����USIM�ļ�¼��*/
    VOS_UINT16                          usEfId;                                 /*�����ļ���ID*/
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType;                           /*������Deleteʱ����Ч*/
    MN_MSG_USIM_ACTION_ENUM_U8          enSmaUsimAction;                        /*��USIM���еĲ������õĺ���*/
}MN_MSG_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bCreateNode;                                  /*�ü�¼�Ƿ��ѱ�ʹ��*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_WRITE_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*�ü�¼�Ƿ��ѱ�ʹ��*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_SET_USIM_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM��״̬*/
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;                           /*��ʶ�Ƿ����ϵ������*/
    VOS_UINT8                           aucReserve[2];
} MN_MSG_USIM_STATUS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*�Ƿ�֧��EFSMSS�ļ�*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage �������*/
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage �������*/
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP �������*/
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*�Ƿ�֧��MO-SMS Control by USIM*/
    VOS_BOOL                            bSmsPpDataFlag;                         /*�Ƿ�֧��Data download via SMS-PP*/
}MN_MSG_USIM_EFUST_INFO_STRU;

 /* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
typedef struct
{
    VOS_UINT8                           ucEfSmssNeedRefreshFlag;                            /*EFSMSS�ļ��Ƿ���Ҫ����*/
    VOS_UINT8                           ucEfSmsNeedRefreshFlag;                             /*SMS Storage �ļ��Ƿ���Ҫ����*/
    VOS_UINT8                           ucEfSmsrNeedRefreshFlag;                        /*SMSR Storage�ļ��Ƿ���Ҫ����*/
    VOS_UINT8                           ucEfSmspNeedRefreshFlag;                            /*SMSP�ļ��Ƿ���Ҫ����*/
}MN_MSG_USIM_EFUST_NEED_REFRESH_STRU;

 /* Added by l00208543 for V9R1 STK����, 2013-07-09, end */


typedef struct
{
    VOS_BOOL                            bUsed;                                  /*�ü�¼�Ƿ���Ч*/
    MN_MSG_SRV_PARAM_STRU               stParm;                                 /*EFSMSP������*/
}MN_MSG_USIM_EFSMSP_DTL_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucLastUsedTpMr;                         /*ǰһ��ʹ�õ�MRֵ*/
    MN_MSG_MEM_FLAG_ENUM_U8             enMemCapExcNotFlag;                     /*�洢���������֪ͨ��־*/
    VOS_UINT8                           aucRFU[253];
}MN_MSG_SMSS_INFO_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState;                           /*MoʱSMA״̬*/
    VOS_BOOL                            bEnvelopePending;                       /*MO SMS CONTROL��������ʱ,�Ƿ����ڵȴ�USIM�Ļظ�*/
    VOS_UINT8                           ucMr;                                   /*Msg Reference*/
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea;                             /*�����λ��,USIM,NVIM���ǲ�����*/
    VOS_UINT32                          ulSaveIndex;                            /*����USIM��NVIM��������*/
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;
    MN_MSG_MO_TYPE_ENUM_U8              enSmsMoType;                            /*�����Ƿ��Ͷ��Ż���SMMA*/
    VOS_UINT8                           aucReserve1[2];
    VOS_BOOL                            bReportFlag;                            /*�����Ƿ���Ҫ�ϱ�,����SMMA��Ч*/
    VOS_BOOL                            bStaRptInd;
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Mobile Station to Network)�����ݻ�23040 7.3.2 RP SMMA������*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve2[3];
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */
} MN_MSG_MO_ENTITY_STRU;

typedef struct
{
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;
    MN_MSG_RCV_DOMAIN_ENUM_U8           enRcvDomain;
    VOS_UINT8                           aucReserve[1];
    MN_MSG_DCS_CODE_STRU                stDcs;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */
}MN_MSG_MT_ENTITY_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*�Ƿ�ʹ��*/
    MN_MSG_MO_ENTITY_STRU               stMoInfo;                               /*������Ϣ*/
    VOS_UINT8                           aucEfSmContent[MN_MSG_EFSMS_LEN];
}MN_MSG_STORE_MSG_STRU;

/*****************************************************************************
 �ṹ��    : MN_MSG_MO_BUFFER_STRU
 �ṹ˵��  : ���Ͷ��ŵĻ���ṹ��
				ulTotal		������Ķ���������
				pstMoBuffer ����Ķ���ָ�룻
  1.��    ��   : 2012��04��12��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotal;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer;
}MN_MSG_MO_BUFFER_STRU;

typedef struct
{
    VOS_UINT32                          ulRetryPeriod;                          /*�����ط�������*/
    VOS_UINT32                          ulRetryInterval;                        /*�����ط���ʱ����*/
    VOS_UINT8                           ucSmsRetryCmSrvRejNum;
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}MN_MSG_RETRY_INFO_STRU;

typedef struct
{
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Network to Mobile Station*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve[3];
}MN_MSG_RP_ERR_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    MN_MSG_BCD_ADDR_STRU                stOrgAddr;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_DATA_STRU;

typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_ACK_STRU;


typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;                                 /*�������ɾ��*/
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
    VOS_UINT8                           ucRpCauseLen;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
}MN_MSG_RP_ERR_STRU;

enum
{
    MN_MSG_WRITE_EFSMS_CAUSE_OK,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM,
    MN_MSG_WRITE_EFSMS_CAUSE_UNSEPCIFIC,
    MN_MSG_WRITE_EFSMS_CAUSE_MAX
};
typedef VOS_UINT32 MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32;

/*******************************************************************************
 �ṹ��    : MN_MSG_STORAGE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Ż�״̬������մ���ʽ,�洢����,�ļ�ID,��¼���ļ��е�����
*******************************************************************************/
typedef struct
{
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /* action of received status report */
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /* memory store: NVIM or USIM of received msg*/
    VOS_UINT16                          usFileIndex;                            /* file id: EFSMS or EFSMSR */
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulIndex;                                /* index of  status report in file */
}MN_MSG_STORAGE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MSG_FDN_INFO_STRU
 �ṹ˵��  : SMSҵ��ģ��FDNҵ�����Բ����ṹ
             ulFdnStatus        (U)SIM��FDNҵ��ʹ��״̬
             stFdnConfig        ME��FDNҵ��NV����
1.��    ��   : 2012��02��23��
  ��    ��   : f62575
  �޸�����   : ����
2.��    ��   : 2013��6��5��
  ��    ��   : z00161729
  �޸�����  : SVLTE ��usim�ӿڵ����޸�

*****************************************************************************/
typedef struct
{

    TAF_FDN_CONFIG_STRU                 stFdnConfig;
}TAF_MSG_FDN_INFO_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/

/*****************************************************************************
  5 �ӿں�������
*****************************************************************************/
/* Added by f62575 for AT Project��2011-10-03,  Begin*/
extern VOS_UINT8                            g_ucSetEfSmsFail;
extern VOS_UINT8                            g_ucNasSmsPsConcatencateFlag;
#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_UINT8                            g_ucSetEfSmsCapacity;
extern VOS_UINT8                            g_ucSetEfSmssClear;
extern VOS_UINT8                            g_ucSetEfSmspNoRsp;
extern VOS_UINT8                            g_ucSetEfSmsNoResponse;
extern VOS_UINT8                            g_ucDisableMoRetry;
extern MN_MSG_CLASS0_TAILOR_U8              g_enClass0Tailor;
extern VOS_UINT8                            g_ucPpDownloadStub;
#endif
/* Added by f62575 for AT Project��2011-10-03,  End*/



 /* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SetSmsFileRefreshFlag
 ��������  : ����SMS�ļ��Ƿ���Ҫ���µı�ʾ
 �������  : VOS_BOOL mnFileRefreshFlag,
                          VOS_UINT16    usEfId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����

*****************************************************************************/

VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag);
 /* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

 /* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_GetSmsFileRefreshFlag
 ��������  : ����SMS�ļ��Ƿ���Ҫ���µı�ʾ
 �������  : VOS_UINT16    usEfId
 �������  : VOS_BOOL
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId);
 /* Added by l00208543 for V9R1 STK����, 2013-07-09, end */


/***********************************************************************
�� �� ��  : MN_MSG_CheckUsimStatus
��������  : ��鵱ǰUSIM��״̬�Ƿ�����������ͽ��ն���
�������  : ��
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR:USIM��״̬����
            ����:USIM��״̬������

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoState
 ��������  : ��ȡ��ǰ�Ƿ��ж������ڷ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : MN_MSG_MO_STATE_ENUM_U8  - ��ǰ��enSmaMoState״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID);

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SetMoRouteStackType
 ��������  : ����MO MSG��Ϣ������ջ·�ɣ���IMS or PS stack
 �������  : enSendOnStackType  ����Ϣ·������
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : y0024524
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoRouteStackType
 ��������  : ��ȡMO MSG��Ϣ������ջ·�ɣ�IMS or PS stack
 �������  : ��
 �������  : ��
 �� �� ֵ  : MN_MSG_ROUTE_STACK_TYPE_ENUM_UINT32  - ��Ϣ·��ջ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : y0024524
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID);
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMtState
 ��������  : ��ȡ��ǰ�Ƿ��ж�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MN_MSG_MT_STATE_ENUM_U8  - ��ǰ��enSmaMtState״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-21, begin */
VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
);
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-21, end */

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SetMtRouteStackType
 ��������  : ����MT MSG��Ϣ������ջ·�ɣ���IMS or PS stack
 �������  : enSendOnStackType  ����Ϣ·������
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : y0024524
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SetMtRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMtRouteStackType
 ��������  : ��ȡMT MSG��Ϣ������ջ·�ɣ�IMS or PS stack
 �������  : ��
 �������  : ��
 �� �� ֵ  : MN_MSG_ROUTE_STACK_TYPE_ENUM_UINT32  - ��Ϣ·��ջ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : y0024524
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID);
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoEntity
 ��������  : ��ȡ��ǰ���Ͷ��ŵ����״̬
 �������  : ��
 �������  : pstMoEntity:��ǰ���Ͷ��ŵ����״̬
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetMoEntity(
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateMoInfo
 ��������  : ���������������f_stMsgMoEntity����ز���
 �������  : pstMoEntity    - ��ǰ���Ͷ��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
);

/***********************************************************************
�� �� ��  : MN_MSG_GetTpMR
��������  : ��ȡ��ǰEFSMSS�ļ��е�TP-MR��ֵ
�������  : ��
�������  : pucTpMr:��ǰTP-MR��ֵ,��ȡUSIM,NVIM��ʧ�ܺ�,���ڴ���ȡ
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_GetTpMR(
    VOS_UINT8                           *pucTpMr
);

/***********************************************************************
�� �� ��  : MN_MSG_AddTpMR
��������  : ���µ�ǰEFSMSS�ļ��е�TP-MR��ֵ
�������  : ��
�������  : ��
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_AddTpMR(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetStoreMsgIndex
 ��������  : ��ȡ��ǰ�Ƿ��пռ仺�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ������ŵ�λ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��6��29��
    ��    ��   : ��ӳ��
    �޸�����   : STK���⻺���޸�
*****************************************************************************/
VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_SaveStoreMsg
 ��������  : �����Ŵ��뻺��ռ�
 �������  : ulIndex:������ŵ�λ��
             pstMoEntity:������ŵ���ز���
             pucEfSmContent:����EFSMS�ļ��ж��ŵ�����
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_SaveStoreMsg(
    VOS_UINT32                          ulIndex,
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const VOS_UINT8                     *pucEfSmContent
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetStoreMsg
 ��������  : ��ȡ�����е�һ������
 �������  : ��
 �������  : pstStoreMsg:�����е���Ϣ����
 �� �� ֵ  : �������ڵ�����,���ΪMN_MSG_NO_AVAILABLE_REC,�����û�л�����Ϣ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
);

/*****************************************************************************
 �� �� ��  : MN_MSG_FreeStoreMsg
 ��������  : �ͷŻ����е�һ����Ϣ
 �������  : ulIndex:�ͷ���Ϣ������
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_FreeStoreMsg(
    VOS_UINT32                          ulIndex
);

/*****************************************************************************
 �� �� ��  : MN_MSG_ProcMoCtrl
 ��������  : ���ݷ��Ͷ�������,����Envelop ���USIM����
 �������  : pucEfSmContent       - ���ŵ�����
 �������  : ��
 �� �� ֵ  : MN_ERR_NO_ERROR:�������Ͳ����ɹ�
             ����:�������Ͳ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_ProcMoCtrl(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    const VOS_UINT8                     aucRpDataInfo[]
);

/*****************************************************************************
 �� �� ��  : MN_MSG_DestroyMoInfo
 ��������  : ���f_stMsgMoEntity����ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateMtInfo
 ��������  : ����g_stSmaMtEntity����ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_DestroyMtInfo
 ��������  : ���g_stSmaMtEntity����ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateNewUsimNode
 ��������  : ��USIM�����첽����,����USIM�Ľڵ�������,���ô˺����鿴�Ƿ��п��еĽڵ���,
             ����п��нڵ�,����д�ýڵ������Ϣ
 �������  : pstSmaUsimInfo  - �����ڵ������Ϣ
 �������  : pulIndex        - �ڵ���������
 �� �� ֵ  : VOS_TRUE        - �ҵ����е�f_astMsgSetUsimInfo
             VOS_FALSE       - δ�ҵ����е�f_astMsgSetUsimInfo

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_CreateNewUsimNode(
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);

/*����ڴ�������ΪucIndex��USIM�ڵ������Ϣ*/
/*****************************************************************************
 �� �� ��  : MN_MSG_DestroyUsimNode
 ��������  : ����ڴ�������ΪucIndex��USIM�ڵ������Ϣ
 �������  : ulIndex - ����USIM�ڵ�ļ�¼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2007��12��14��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_DestroyUsimNode(
    VOS_UINT32                          ulIndex
);
/***********************************************************************
�� �� ��  : MN_MSG_UpdateUstInfo
��������  : �����ڴ��б�����EFSMSS�ļ����ڵı�־��
�������  : pstSmsUstInfo:EFSMSS�ļ�������
�������  : ��
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_UpdateUstInfo(
);
/***********************************************************************
�� �� ��  : MN_MSG_MoFeatureAvailable
��������  : ��ȡMO���ܿ��ñ�־
�������  : VOS_VOID
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR - MO���ܿ���
            ����            - MO���ܲ�����
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��4��13��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateSmssInfo
��������  : �����ڴ��б�����EFSMSS�ļ����ڵı�־�Լ��ļ�������
�������  : bEfSmssState:�ļ����ڵı�־
            pstSmssInfo:EFSMSS�ļ�������
�������  : ��
�� �� ֵ  :

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_UpdateSmssInfo(
    VOS_BOOL                            bEfSmssState,
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo,
    VOS_UINT32                          ulFileLen
);

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmssInfo
��������  : ��ȡ������USIM��NVIM�е�SMSS������,���Ȼ�ȡ������USIM��EFSMSS�ļ�������
�������  : ��
�������  : pstSmssInfo:��ȡEFSMSS������
�� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
            VOS_FALSE:��ȡʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
);

/*****************************************************************************
 �� �� ��  : MN_MSG_Internal_SendRpt
 ��������  : Э��ջ�ڲ����ô˺�������RP-ACK��RP-ERROR��Ϣ������
 �������  : bRpAck:�Ƿ���RpAck����RpError
             enRpCause:����RpErrorʱ��Ч,����R���ԭ��ֵ
             enTpCause:����RpErrorʱ��Ч,����T���ԭ��ֵ
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
);

/***********************************************************************
�� �� ��  : MN_MSG_GetCurRcvMsgPath
��������  : ��ȡ��ǰ���ն��ŵ�·��
�������  : NONE
�������  : pstCfgParm:��ǰ���ն��ŵ�·��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_GetCurCfgParm(
    MN_MSG_CONFIG_PARM_STRU             *pstCfgParm
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateRegState
��������  : ���µ�ǰCS,PS���ע�����
�������  : ucDomain:��Ҫ���µ���
            bAttachFlag:��ǰ���µı�־
�������  : NONE
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateRegState(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateTotalSmspInfo
��������  : �յ�USIM���͹�����EFSMSP���ļ����ݺ�,�����ڴ���EFSMSP������
�������  : bEfSmspState:EFSMSP�ļ����ڱ�־
            ucNumofSmsp:EFSMSP�ļ��ĸ���
            ucEfLen:EFSMSP�ļ��ĳ���
            pucSmspContent:EFSMSP�ļ�������
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateEachMemSmInfo
��������  : ����USIM�������ڴ��еĶ�������
�������  : ucIndex:���¼�¼��index
            pucEFContent:EFSMS���ļ�����
            ucEFSmsLen:EFSMS�ļ��ĳ���
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateSmsRecNumInfo
��������  : �յ�USIM���͹�����EFSMS���ļ����ݺ�,�����ڴ���EFSMS�ļ�¼�����ļ����ڱ�־
�������  : bEfSmsState:�ļ����ڱ�־
            ucEFSmNum:USIM���ļ���¼��,
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateSmsInfo(
    VOS_BOOL                            bEfSmsState,
    VOS_UINT8                           ucEFSmNum
);

/***********************************************************************
�� �� ��  : MN_MSG_ReadUstInfo
��������  : ��ȡUSIM�������ڴ���ŷ����
�������  : ��
�������  : pstEfUstInfo:USIM�������ڴ��(U)SIM Service Table������
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID   MN_MSG_ReadUstInfo(
    MN_MSG_USIM_EFUST_INFO_STRU         *pstEfUstInfo
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateUsimStateInfo
��������  : ���µ�ǰUSIM������USIM���ϵ��״̬
�������  : enPowerState:USIM�����ϵ�״̬
�������  : ��
�� �� ֵ  :

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateUsimStateInfo(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState
);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMoSaveInfo
 ��������  : ����f_stMsgMoEntity�д洢����ز���
 �������  : enSaveArea     - ���Ͷ��ŵĴ洢����
             ucSaveIndex    - ���Ͷ��ŵĴ洢λ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��05��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_UpdateMoSaveInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea,
    VOS_UINT32                          ulSaveIndex
);

/***********************************************************************
�� �� ��  : MN_MSG_StartMo
��������  : ������һ�����ź�,�����ǰ����Ϣ����,���ô˺�������������Ϣ
�������  : ��
�������  : penSendDomain:��ǰ���Ͷ��ŵķ�����
�� �� ֵ  : VOS_TRUE:���ͻ�����Ϣ�ɹ�
            VOS_FALSE:���ͻ�����Ϣʧ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
);

/***********************************************************************
�� �� ��  : MN_MSG_StartMemNotification
��������  : ���ݵ�ǰ�洢������������Ƿ�Ҫ�����෢���ڴ����֪ͨ
�������  : ��
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_StartMemNotification(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_SendMemAvail
��������  : �����෢���ڴ����֪ͨ
�������  : ��
�������  : ��
�� �� ֵ  :

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_SendMemAvail(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_IsUsimFileExist
��������  : ��ȡUSIM�и��ļ��Ƿ����
�������  : usEfId:USIM�е��ļ�ID
�������  : NONE
�� �� ֵ  : VOS_TRUE:���ļ�����
            VOS_FALSE:���ļ�������
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_BOOL MN_MSG_IsUsimFileExist(
    VOS_UINT16                          usEfId
);

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmsInfo
��������  : ���ڴ��ж�ȡ����USIM�Ķ��Ż��ȡNVIM�еĶ���
�������  : enMemStore:���ŵĴ洢λ��,NVIM��USIM
            ulIndex:��Ҫ��ȡ���ŵ�������
�������  : pucSmsContent:�������ŵ�����
�� �� ֵ  : VOS_UINT32:����ִ�н��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
);

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmsrInfo
��������  : ���ڴ��ж�ȡ����USIM�Ķ���״̬������ȡNVIM�еĶ���״̬����
�������  : enMemStore:���ŵĴ洢λ��,NVIM��USIM
            ulIndex:��Ҫ��ȡ����״̬�����������
�������  : pucSmsrContent:��������״̬���������
�� �� ֵ  : VOS_UINT32:����ִ�н��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsrInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsrContent
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateEachMemSmsrInfo
��������  : ����USIM�������ڴ��еĶ���״̬��������
�������  : ucIndex:���¼�¼��index
            pucEFContent:EFSMSR���ļ�����
            ucEFSmsLen:EFSMSR�ļ��ĳ���
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmsrInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsrLen
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateSmspInfo
��������  : ���±������ڴ��е�USIM�Ķ��Ų���
�������  : ucIndex:��Ҫ���µĶ��Ų�������
            bUsed:�ö��Ų����Ƿ���Ч
            pstScvParm:���µ�����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_UpdateEachMemSmspInfo(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bUsed,
    const MN_MSG_SRV_PARAM_STRU         *pstScvParm
);

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmspInfo
��������  : ��������ΪusSmspIndex�Ķ��Ų���������
�������  : enMemStore:���Ų����Ĵ洢λ��
            usSmspIndex:���Ų���������
�������  : pstSmspPara:�������Ų���������
�� �� ֵ  : MN_ERR_NO_ERROR:��ȡ�ɹ�
            ����:��ȡʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU                *stSrvParm
);

/***********************************************************************
�� �� ��  : MN_MSG_GetSmStorageList
��������  : ��ȡ��ǰUSIM��NVIM�ж��ŵ�storage list
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : pusTotalRec:��ǰ�洢����������
            psUsedRec:��ǰ�洢�������ÿռ�
            pulEachStatusRec:ÿ��״̬�Ķ��ŵļ�¼��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_GetSmStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    VOS_UINT32                          *pulEachStatusRec
);

/***********************************************************************
�� �� ��  : MN_MSG_GetStatus
��������  : ��ȡ����USIM��NVIM�еĶ���״̬
�������  : enMemStore:��Ҫ��ȡ����״̬�Ĵ洢λ��,USIM��NVIM��
            ulIndex:��Ҫ��ȡ����״̬��������
�������  : pucStatus:����ΪulIndex�Ķ���״̬
�� �� ֵ  : MN_ERR_NO_ERROR:��ȡ�ɹ�
            ����:��ȡʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
);

/***********************************************************************
�� �� ��  : MN_MSG_GetAvailSmRecIndex
��������  : ��ȡ����USIM��NVIM�е�һ�����еĶ�������
�������  : enMemStore:��Ҫ��ȡ���ж��������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ���ж���������,�޿��ж���,�򷵻�MSG_NO_AVAILABLE_REC
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_GetAvailSmsrRecIndex
��������  : ��ȡ����USIM��NVIM�еĿ��еĶ���״̬��������
�������  : enMemStore:��Ҫ��ȡ���ж���״̬���������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ���ж���״̬����������,�޿��ж���״̬����,�򷵻�MSG_NO_AVAILABLE_REC
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_GetAvailSmspRecIndex
��������  : ��ȡ����USIM�еĿ��еĶ��Ų�������
�������  : NONE
�������  : NONE
�� �� ֵ  : ���ж��Ų���������,�޿��ж��Ų���,�򷵻�MSG_NO_AVAILABLE_REC
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��01��30��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_GetReplaceSmsrRecIndex
��������  : ��ȡ����USIM��NVIM�е��滻�Ķ���״̬��������,��Ѱ�����ϵ�һ������״̬����������¼
�������  : enMemStore:��Ҫ��ȡ���ж���״̬���������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ���ϵ�һ������״̬����������¼
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_GetUsimPowerState
��������  : ��ȡUSIM��ǰ���ϵ�״̬
�������  : ��
�������  : penPowerState:��ȡUSIM��ǰ���ϵ�״̬
�� �� ֵ  : ��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_GetUsimPowerState(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     *penPowerState
);

VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_GetSmspCapacity
��������  : ��ȡ����ܴ���USIM��NVIM�ж��Ų���������
�������  : enMemStore:��Ҫ��ȡ���������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ��ǰ�洢���Ķ�������
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetSmspCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_GetSmsrCapacity
��������  : ��ȡ������USIM��NVIM�ж���״̬���������
�������  : enMemStore:��Ҫ��ȡ����״̬���������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ��ǰ�洢���Ķ���״̬��������
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
�� �� ��  : MN_MSG_IsValidSmIndex
��������  : �жϵ�ǰ�����Index�ǺϷ��Ļ��ǷǷ���
�������  : enMemStore:��Ҫ�ж��������index�Ĵ洢λ��,USIM��NVIM��
            ucIndex:������ŵ�����
�������  : NONE
�� �� ֵ  : VOS_TRUE:����index�Ϸ�
            VOS_FALSE:����index�Ƿ�
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex
);

/***********************************************************************
�� �� ��  : MN_MSG_IsValidSmspIndex
��������  : �жϵ�ǰ�����Index�ǺϷ��Ļ��ǷǷ���
�������  : ucIndex:������Ų���������
�������  : NONE
�� �� ֵ  : VOS_TRUE:����index�Ϸ�
            VOS_FALSE:����index�Ƿ�
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmspIndex(
    VOS_UINT8                           ucIndex
);

/***********************************************************************
�� �� ��  : MN_MSG_IsEmptySmsp
��������  : �жϵ�ǰ��¼�Ƿ��ǿռ�¼
�������  : usSmsIndex:������Ų���������
�������  : NONE
�� �� ֵ  : VOS_TRUE:���������Ϸ�
            VOS_FALSE:���������Ƿ�
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_BOOL MN_MSG_IsEmptySmsp(
    VOS_UINT8                           ucIndex
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateRcvMsgPath
��������  : ��ȡ��ǰ���ն��ŵ�·��
�������  : ��
�������  : pstRcvPath:��Ҫ���µĽ��ն��ŵ�·��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateRcvMsgPath
��������  : ���µ�ǰ���ն��ŵ�·��
�������  : pstRcvPath:��Ҫ���µĽ��ն��ŵ�·��
�������  : NONE
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�
            ����:����ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
);

/***********************************************************************
�� �� ��  : MN_MSG_GetDeleteReportFlag
��������  : ��ȡ��ǰ����(��list,delete�ȵ�),�Ƿ��Ѿ��ϱ�
�������  : enType:��ǰ����������
�������  : ��
�� �� ֵ  : ��ǰ����(��list,delete�ȵ�),�Ƿ��Ѿ��ϱ�
            VOS_TRUE:�Ѿ��ϱ�
            VOS_FALSE:δ���ϱ�
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��19��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_BOOL  MN_MSG_GetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType
);

/***********************************************************************
�� �� ��  : MN_MSG_SetDeleteReportFlag
��������  : ���õ�ǰ����(��list,delete�ȵ�),�Ƿ��ϱ�
�������  : enType:��ǰ����������
            bReportFlag:�ϱ���־
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��19��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_SetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_BOOL                            bReportFlag
);

/***********************************************************************
�� �� ��  : MN_MSG_GetCurSendDomain
��������  : ��ȡ��ǰ���Ͷ���ʱ,���ŵ�ʵ�ʷ�����
�������  : penHopeSendDomain:��ǰ���Ͷ���ʱ,�����Ķ��ŷ�����
�������  : penRealSendDomain:��ǰ���Ͷ���ʱ,ʵ�ʵĶ��ŷ�����
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
);

/***********************************************************************
�� �� ��  : MN_MSG_GetCurAppMemStatus
��������  : ��ȡ��ǰAPP���ڴ�ʹ��״̬
�������  : NONE
�������  : penMemStatus:��ǰAPP���ڴ�ʹ��״̬
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_GetCurAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             *penMemStatus
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateAppMemStatus
��������  : ����APP���ڴ�ʹ��״̬
�������  : enMemStatus:��Ҫ���µ�APP���ڴ�ʹ��״̬
�������  : NONE
�� �� ֵ  : VOS_TRUE:���³ɹ�
            VOS_FALSE:����ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
);

/***********************************************************************
�� �� ��  : MN_MSG_FindNodeByUsimResult
��������  : �յ���USIM���صĽ����¼ʱ,�ҵ�������¼��ǰ���в����Ľڵ���Ϣf_astMsgSetUsimInfo
�������  : ucRecIndex:����USIM�ļ�¼��
            usEfId:����USIM���ļ�EFID
�������  : pSmaUsimInfo:�ҵ��Ľڵ���Ϣf_astMsgSetUsimInfo
            pucIndex:�ҵ��ڵ���USIM�ڵ��б������
�� �� ֵ  : VOS_TRUE:�ɹ��ҵ�
            VOS_FALSE:δ���ҵ�
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_FindNodeByUsimResult(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT16                          usEfId,
    MN_MSG_USIM_INFO_STRU               *pSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);

/***********************************************************************
�� �� ��  : MN_MSG_GetUsimRec
��������  : ��ȡ��ǰͬһ�����͵Ĳ���(��list,delete�ȵ�),����USIM�ļ�¼��
�������  : ��
�������  : ��
�� �� ֵ  : ��ǰͬһ�����͵Ĳ���(��list,delete�ȵ�),����USIM�ļ�¼��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT8  MN_MSG_GetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType
);

/***********************************************************************
�� �� ��  : MN_MSG_SetUsimRec
��������  : ����������USIM���õļ�¼��,
�������  : enType:��ǰ��������
            ucRec:��Ҫ���õļ�¼��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_SetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_UINT8                           ucRec
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetSmsMoCtrlPend
 ��������  : ���ص�ǰ���Ͷ���ʱ,SMS MO CONTROL����ʱ,�Ƿ����ڵȴ�USIM�Ļظ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��27��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL MN_MSG_GetSmsMoCtrlPend(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateSmaMoState
 ��������  : ���¶��ŷ���ʵ��״̬
 �������  : MN_MSG_MO_STATE_ENUM_U8             enSmaMoState  �����µĶ��ŷ���ʵ��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��22��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
);

/*****************************************************************************
 �� �� ��  : MN_MSG_MoSmsControlEnvelopeReq
 ��������  : SMS MO CONTROL���ܿ���ʱ,�·�Envelope datadownload��USIM��
 �������  : pstAddrObj1: SC Addr
             pstAddrObj2: Dest Addr
             pucLI:       Location Information
 �������  : VOS_TRUE:���سɹ�
             VOS_FALSE:����ʧ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������ ��
  3.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:MN_MSG_MoSmsControlEnvelopeReq����client ID����
*****************************************************************************/
VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
);



/*****************************************************************************
 �� �� ��  : MN_MSG_SmsPPEnvelopeReq
 ��������  : �յ�Class 2 ��PIDΪUSIM DataDownLad����ʱ,��Ҫ�·�Envelope datadownload��USIM��
 �������  : pstAddr:     SC Addr
             pucTpduData: SMS TPDU (SMS-DELIVER)
             ulTpduLen:   SMS TPDU (SMS-DELIVER) Length
 �������  : ��
 �� �� ֵ  : VOS_TRUE; ���سɹ�
             VOS_FALSE:����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
);

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
/***********************************************************************
�� �� ��  : MN_MSG_SendSmma
��������  : ����SMMA��Ϣ������
�������  : clientId       - ����������Client��ID
            opId           - Operation ID, ��ʶ���β���
            bReportFlag    - �ϱ���־
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 1.��    ��   : 2013��7��10��
   ��    ��   : y00245242
   �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ
************************************************************************/
VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */


/***********************************************************************
�� �� ��  : MN_MSG_WriteSmssFile
��������  : �����ڴ�,USIM�к�NVIM������SMSS�ļ�ֵ,����USIM,NVIM�Ƿ���³ɹ�,
            �ڴ��и��³ɹ�,���ȸ���USIM�е�EFSMSS������
�������  : pstSmssInfo:��Ҫ����EFSMSS������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��01��20��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
);

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
);

#else
/***********************************************************************
�� �� ��  : MN_MSG_WriteSmsFile
��������  : �����ڴ�,USIM�к�NVIM������SMS�ļ�ֵ
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
            bCreateNode:�Ƿ񴴽��ڵ�
            pstSmaUsimInfo:��USIM��д����Ϣʱ,USIM�ڵ�������Ϣ
            pucContentInfo:��Ҫ���������
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�,
            ����:ʧ���Լ�ʧ�ܵ�ԭ��ֵ
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);
#endif


/***********************************************************************
�� �� ��  : MN_MSG_WriteSmsrFile
��������  : �����ڴ�,USIM�к�NVIM������EFSMSR�ļ�ֵ
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
            pstSmaUsimInfo:��USIM��д����Ϣʱ,USIM�ڵ�������Ϣ
            pucContentInfo:��Ҫ���������
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�,
            ����:ʧ���Լ�ʧ�ܵ�ԭ��ֵ
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsrFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);

/***********************************************************************
�� �� ��  : MN_MSG_WriteSmspFile
��������  : �����ڴ�,USIM�к�NVIM������SMS�ļ�ֵ
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
            pstSmaUsimInfo:��USIM��д����Ϣʱ,USIM�ڵ�������Ϣ
            pstSrvParm:��Ҫ���������
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�,
            ����:����ʧ���Լ�ʧ�ܵ�ԭ��ֵ
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU          *stSrvParm
);

/***********************************************************************
�� �� ��  : MN_MSG_RecoverOrgSrvParm
��������  : ɾ����д���Ų���,USIM����ʧ��,��Ҫ���ڴ��еĶ��Ų����ָ�����
�������  : ucIndex:�ָ����Ų������������
�������  : pstSrvParm:��Ҫ�ָ��Ķ��Ų���������
�� �� ֵ  : ��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSrvParm(
    VOS_UINT8                           ucIndex,
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSrvParam
);

/***********************************************************************
�� �� ��  : MN_MSG_RecoverOrgSm
��������  : ɾ����д����,USIM����ʧ��,��Ҫ���ڴ��еĶ��Żָ�����
�������  : ucIndex:�ָ����Ŵ��������
�������  : pucSmsContent:��Ҫ�ָ��Ķ��ŵ�����
�� �� ֵ  : ��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSm(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmContent
);

/***********************************************************************
�� �� ��  : MN_MSG_RecoverOrgSmsr
��������  : ɾ����д����״̬����ʱ,USIM����ʧ��,��Ҫ���ڴ��еĶ���״̬����ָ�����
�������  : ucIndex:�ָ�����״̬������������
�������  : pucSmsrContent:��Ҫ�ָ��Ķ���״̬���������
�� �� ֵ  : ��
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSmsr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmsrContent
);

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateEFSmContent
 ��������  : ����SC Addr��TPDU����һ������,���Ÿ�ʽΪUSIM����EFSMS�ĸ�ʽ
 �������  : pstScAddr:�������ĵĵ�ַ
             pstRawData:TPDU������
             ucStatus:���ŵ�״̬
 �������  : pucContent:��������,USIM����EFSMS�ĸ�ʽ
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
);

/*****************************************************************************
 �� �� ��  : MN_MSG_ParseEFSmContent
 ��������  : �����Ÿ�ʽΪUSIM����EFSMS�ĸ�ʽ����ΪSCAddr��TPDU
 �������  : pucContent:��������,USIM����EFSMS�ĸ�ʽ
 �������  : pstScAddr:�������ĵĵ�ַ
             pstRawData:TPDU������
             ucStatus:���ŵ�״̬
 �� �� ֵ  : MN_ERR_NO_ERROR:�����ɹ�
             ����:����ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_ParseEFSmContent(
    const VOS_UINT8                     *pucContent,
    MN_MSG_BCD_ADDR_STRU                *pstScAddr,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData,
    VOS_UINT8                           *pucStatus
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetAppStatus
 ��������  : ����USIM���еĶ���״̬��ȡ��APP�ṩ�Ķ���״̬
 �������  : ucStatus:USIM���Ķ���״̬
 �������  : penStatus:APP�Ķ���״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetAppStatus(
    VOS_UINT8                           ucStatus,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetPsStatus
 ��������  : ����APP�ṩ�Ķ���״̬��ȡUSIM���еĶ���״̬
 �������  : enStatus:APP�Ķ���״̬
 �������  : pucStatus:USIM���Ķ���״̬

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetPsStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    VOS_UINT8                           *pucStatus
);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateTotalSmsrInfo
��������  : �յ�USIM���͹�����EFSMSR���ļ����ݺ�,�����ڴ���EFSMSR������
�������  : bEfSmspState:EFSMSR���ļ��Ƿ����
            ucSmsrRec:EFSMSR���ļ�����
            ucEfLen:EFSMSR�ļ��ĳ���
            pucSmspContent:EFSMSR�ļ�������
�������  : ��
�� �� ֵ  :

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmsrInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucSmsrRec,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucSmspContent
);

/***********************************************************************
�� �� ��  : MN_MSG_GetSmsrStorageList
��������  : ��ȡ��ǰUSIM��NVIM��SMS��storage list
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : pusTotalRec:��ǰ�洢����������
            psUsedRec:��ǰ�洢�������ÿռ�
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
);

/***********************************************************************
�� �� ��  : MN_MSG_GetSmspStorageList
��������  : ��ȡ��ǰUSIM��NVIM�ж��Ų�����storage list
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : pusTotalRec:��ǰ�洢����������
            psUsedRec:��ǰ�洢�������ÿռ�
�� �� ֵ  : ��
************************************************************************/
VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU                *pstSrvParam
);

/*****************************************************************************
 �� �� ��  : MN_MSG_DeleteMultiSm
 ��������  : ɾ����������,NVIM:ֱ��ɾ��NVIM�еĶ���,USIM,�·�ɾ�����USIM��
 �������  : clientId        - ����������Client��ID
             opId            - Operation ID, ��ʶ���β���
             enMemStore      - ��ǰ���ŵĴ洢λ��
             enDeleteType    - ɾ������
 �������  : pbDeleteAll     - �Ƿ���ɾ�����ж���
             pucDeleteCount  - ����ɾ���ĸ���
 �� �� ֵ  : MN_ERR_NO_ERROR - ɾ���ɹ����·����USIM�ɹ�
             ����             - ɾ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_DeleteMultiSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT32                          *pulDeleteCount
);

/*****************************************************************************
 �� �� ��  : MN_MSG_DeleteMultiStaRpt
 ��������  : ɾ����������״̬����,NVIM:ֱ��ɾ��NVIM�еĶ���״̬����,USIM,�·�ɾ�����USIM��
 �������  : clientId        - ����������Client��ID
             opId            - Operation ID, ��ʶ���β���
             enMemStore      - ��ǰ���ŵĴ洢λ��
 �������  : pbDeleteAll     - �Ƿ���ɾ�����ж���״̬����
             pucDeleteCount  - ����ɾ���ĸ���
 �� �� ֵ  : MN_ERR_NO_ERROR - ɾ���ɹ����·����USIM�ɹ�
             ����             - ɾ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_MSG_DeleteMultiStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT8                           *pucDeleteCount
);


/*****************************************************************************
 �� �� ��  : MSG_BuildDeliverEvtParm
 ��������  : ����Deliver�¼��ϱ��Ľṹ
 �������  : pstCfgParm:���ŵ�ǰ�Ľ���·��
             pstScAddr:�������ĵ�ַ
             pstRawData:���ŵ�TPDU��ֵ
 �������  : pstDeliverEvt:Deliver�¼��ϱ��Ľṹ

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MSG_BuildDeliverEvtParm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_EVT_INFO_STRU        *pstDeliverEvt
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetBCopId
 ��������  : �㲥�ϱ�ʱ,��ȡOPID��ֵ
 �������  : ��
 �������  : ��

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_GetUsimParmReq
��������  : ����USIM��ȡ����ļ��Ĳ���
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
);

/***********************************************************************
�� �� ��  : MN_MSG_Init
��������  : ��ʼ������ģ��ľ�̬����
�������  : None
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��15��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_SmInit(VOS_VOID);

VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID );

/***********************************************************************
�� �� ��  : MN_MSG_SmCfgDataInit
��������  : TAFģ���յ�USIM����λ������Ϣ��,���ô˺�����ʼ��SMģ�����
            �������λ,����USIM���������ȡUSIM�е�SM��ز���,����ȡNVIM��
            SM��ز���
�������  : ucUsimState:USIM���Ƿ���λ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
);

/***********************************************************************
�� �� ��  : MN_MSG_GetLinkCtrlParam
��������  : ��ȡ�м�Э����·�����ԵĿ��Ʊ�־
�������  : ��
�������  : ��
�� �� ֵ  : �м�Э����·�����ԵĿ��Ʊ�־
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��7��21��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID);

/***********************************************************************
�� �� ��  : MN_MSG_UpdateLinkCtrlParam
��������  : �����м�Э����·�����ԵĿ��Ʊ�־
�������  : setValue - �м�Э����·�����ԵĿ��Ʊ�־
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR - ���ò����ɹ�
            ����            - ���ò���ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��7��21��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32 MN_MSG_UpdateLinkCtrlParam(
    MN_MSG_LINK_CTRL_U8                 setValue
);

/*****************************************************************************
 �� �� ��  : MN_MSG_InitSmsServiceData
 ��������  : ��ʼ������ҵ��������ݽṹ
 �������  : MN_MSG_CONFIG_PARM_STRU  *pstServicePara  ����ҵ��������ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��11��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara);


/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateNeedSendUsim
 ��������  : ������Ҫ���͵�USIM�Ľṹ
 �������  : ulInedx - ��Ҫ���µķ���USIM�Ľṹ
 �������  : ��

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_UpdateNeedSendUsim(
    VOS_UINT32                          ulInedx,
    VOS_BOOL                            bUpdateStatus
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetNeedSendUsim
 ��������  : ������Ҫ���͵�USIM�Ľṹ
 �������  : ��
 �������  : pulRealRec - ��ǰʵ�ʵĶ�������
             pbNeedSendUsim - �Ƿ���Ҫ֪ͨUSIM�޸Ķ���״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetNeedSendUsim(
    VOS_UINT32                          *pulRealRec,
    VOS_BOOL                            *pbNeedSendUsim
);

/*****************************************************************************
*  Prototype       : MN_MSG_FailToWriteEfsms
*  Description     : ����дSIM����EFSMS�ļ�ʧ�ܺ�,MS��Э��Ҫ��ظ�����RP-ERROR���޸�EFSMSS�ļ���
*  Input           : enMemStore  --- �����洢ʧ�ܵĴ洢��������
                     ucFailCause --- ��ǰ�洢ʧ�ܵ�ԭ��
                        �洢������
                        �洢�������ã�
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-04-12
*     Author       : ��ӳ��
*     Modification : Created function
*****************************************************************************/
VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
);

/*****************************************************************************
*  Prototype       : MN_MSG_UpdateSendFailFlag
*  Description     : ���µ�ǰ����ʧ�ܵ���
*  Input           : enSendFailFlag --- ��ǰ����ʧ�ܵ���;
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 VOS_VOID MN_MSG_UpdateSendFailFlag(
 	MN_MSG_SEND_FAIL_FLAG_U8			enSendFailFlag
 );

/*****************************************************************************
 �� �� ��  : MN_MSG_GetRetryPeriod
 ��������  : ��ȡ��ǰ�����ط�ʱ�����ں�ʱ����
 �������  : ��
 �������  :  ��ǰ�����ط�ʱ������
 �� �� ֵ  :��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
);

/*****************************************************************************
*  Prototype       : MN_MSG_GetSendFailFlag
*  Description     : ��ȡ��ǰ����ʧ�ܵ���
*  Input           : ��;
*  Output          :
*  Return Value    : ��ǰ����ʧ�ܵ���
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID);

/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : MSG_RcvSmsRpRpt
 ��������  : �����յ�NAS��SMSģ�鷢�͵�RP-Report
 �������  : pRcvMsg:�յ����ݵ�����,����ΪЭ��24011��RP-REPORT������
             ucRcvLen:�յ����ݵĳ���
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_RcvSmsRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg);

/*****************************************************************************
 �� �� ��  : MN_MSG_SaveRpErrInfo
 ��������  : �������һ�����������rP-Error��Ϣ,��ʱ����ʱ���޿�����ʱ,ȡ����Ϣ�ϱ�
 �������  : ucDataLen:������������ݳ���
             pucData:�������������
 �������  :  ��
 �� �� ֵ  :��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetRpErrInfo
 ��������  : ��ȡ���һ�����������rP-Error��Ϣ,��ʱ����ʱ���޿�����ʱ,ȡ����Ϣ�ϱ�
 �������  : ��
 �������  : pstRpErrInfo:���һ�����������������Ϣ
 �� �� ֵ  :��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : MN_MSG_GetClass0Tailor
 ��������  : ��ȡClass0����ʵ�ַ�ʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :Class0����ʵ�ַ�ʽ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_SetClass0Tailor
 ��������  : ����Class0����ʵ�ַ�ʽ
 �������  : enClass0Tailor Class0����ʵ�ַ�ʽ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��31��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetRealPrefSendDomain
 ��������  : ��ȡ��ǰʵ�ʵ����ȷ�����
 �������  : enHopeDomain:��ǰ��ʵ�ʷ�����
             enHopeDomain:��ǰ���������ȷ�����
 �������  : ��
 �� �� ֵ  :��ǰʵ�ʵ����ȷ�����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

��ǰ���֧��CS+PS���Ͷ���,���CS����ʧ��,���´η��Ͷ���ʱ���ȴ�PS����,��֮
��Ȼ,��ʱʵ�ʵ����ȷ�����ʱPS�����ȷ���
*****************************************************************************/
MN_MSG_SEND_DOMAIN_ENUM_U8  MN_MSG_GetRealPrefSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeDomain
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMtTpPidAndDcs
 ��������  : ��ȡ��ǰ���յ����ŵ�TP-PID��TP-DCS
 �������  : ��
 �������  : MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid ��ǰ���յ����ŵ�TP-PID
             MN_MSG_DCS_CODE_STRU                *pstDcs ��ǰ���յ����ŵ�TP-DCS������õ�DCS�ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_GetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid,
    MN_MSG_DCS_CODE_STRU                *pstDcs
);

/*****************************************************************************
 �� �� ��  : MN_MSG_SetMtTpPidAndDcs
 ��������  : ���浱ǰ���յ����ŵ�TP-PID��TP-DCS�����Ž���ʵ��
 �������  : ��
 �������  : MN_MSG_TP_PID_TYPE_ENUM_U8          enPid ��ǰ���յ����ŵ�TP-PID
             MN_MSG_DCS_CODE_STRU                stDcs ��ǰ���յ����ŵ�TP-DCS������õ�DCS�ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_SetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_DCS_CODE_STRU                stDcs
);


VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
);


/*****************************************************************************
 �� �� ��  : MN_MSG_InitRcvPath
 ��������  : ��ʼ�����Ž���·��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��29��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID );

/***  All the following functions are defined in MnMsgReqProc.c  ***/
extern VOS_UINT32  MSG_ChangeSmStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_USIM_ACTION_ENUM_U8          enAction,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsContent,
    VOS_UINT8                           *pucChangeNum
);

VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);
VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);

VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable);

VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
);

VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg);


VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg);

VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg);

/*****************************************************************************
 �� �� ��  : MN_MSG_MoCtrlAllowedWithModification
 ��������  : MO SMS CONTROL���̵���Ӧ��Ϣ��ALLOWED MODIFY�����¶������Ļ�Ŀ
             �ĺ���
 �������  : SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��17��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_MoCtrlAllowedWithModification(
    SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : ��ȡGMM�ĵ�ǰ��������
                  HSS 4100 V200R001 ����
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : GMM��������
                  GMM_RABM_CURNET_3G    3G����
                  GMM_RABM_CURNET_2G    2G����
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/VOS_UINT8 GMM_GetCurNetwork (VOS_VOID);

VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf );

/*****************************************************************************
 �� �� ��  : MN_MSG_SendMsgToSms
 ��������  : ���Ͷ��ŵ�SMSģ��
 �������  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : 2012082906141 ������ݿ�STK����Ⱥ��ʧ�����⣬ɾ�����bRetryFlag

*****************************************************************************/
VOS_VOID MN_MSG_SendMsgToSms(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl
 ��������  : ����USIM��MO SMS CONTROL��Ӧ��Ϣȷ�Ͼܾ������ͻ��޸ķ��Ͷ���
 �������  : SI_STK_ENVELOPEDWON_CNF_STRU          *pstEnvelope
             MN_MSG_MO_ENTITY_STRU               *pstMoEntity
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);

/*****************************************************************************
 �� �� ��  : MN_MSG_RcvUsimMoControlRsp
 ��������  : ����MO SMS CONTROL����USIMģ�����Ӧ��Ϣ
 �������  : SI_STK_ENVELOPEDWON_CNF_STRU          *pstEnvelope
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��15��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_RcvUsimMoControlRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);

/*****************************************************************************
 �� �� ��  : MN_MSG_RcvUsimEnvelopRsp
 ��������  : ������յ�USIM���͹�����SetFileRsp��ԭ��
 �������  : pstEnvelope:USIM���͹����������ļ�������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��08��07��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : AT2D16304, ���Ӷ�RP-ACK�д�TPDU���ֵĴ���
*****************************************************************************/
VOS_VOID  MN_MSG_RcvUsimEnvelopRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);

/*****************************************************************************
 �� �� ��  : MN_MSG_SendFdnCheckInfo
 ��������  : ���Ͷ���FDN�����Ϣ��(U)SIMģ��
 �������  : MN_MSG_MO_ENTITY_STRU *pstMoEntity ���ŷ���ʵ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR                 FDN������ݷ��ͳɹ�
                ������                          FDN������ݷ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_SendFdnCheckInfo(MN_MSG_MO_ENTITY_STRU *pstMoEntity);

/*****************************************************************************
 �� �� ��  : MN_MSG_CheckMoSmsCtrl
 ��������  : ���Ͷ��������е�MO SMS CONTROL���
 �������  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity    ���ŷ�����Ϣ�ṹ
 �������  : VOS_BOOL                           *pCheckMoCtrl   �Ƿ���MO SMS CONTROL
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR                 MO SMS CONTROL���ִ����ȷ
                ������                          MO SMS CONTROL���ִ��ʧ�ܣ���Ҫ�ܾ��û��Ķ��ŷ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : 2012082906141 ������ݿ�STK����Ⱥ��ʧ�����⣬�޸ĺ�������������
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoSmsCtrl(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckMoCtrl
);

/* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : MN_MSG_IsLteNeedSmsRetry
 ��������  : �ж�L���Ƿ���Ҫ�����ط�
 �������  : enErrCause - L LMM_SMS_ERR_IND�ظ���ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ������Ҫ�ط�
             VOS_FALSE - ���������ط�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��14��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_MSG_IsLteNeedSmsRetry(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause
);

#endif
/* Modified by z00161729 for DCM�����������������, 2012-8-14, end */

VOS_UINT32  MN_MSG_IsGuNeedSmsRetry(
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause
);

/*****************************************************************************
 �� �� ��  : MN_MSG_InitMoBuffer
 ��������  : ���淢�Ͷ���ʵ���ʼ��
 �������  : ��
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoBufferCap
 ��������  : ��ȡ���淢�Ͷ���ʵ������
 �������  : ��
 �������  : ��
 ����ֵ    : ���淢�Ͷ���ʵ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID);

/*****************************************************************************
 �� �� ��  : MN_MSG_CheckMoMsg
 ��������  : ��ȡָ��״̬�ķ��Ͷ�Ϣʵ��
 �������  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  Ҫ��ȡ�Ķ���ʵ��״̬
 �������  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity �����͵Ķ���ʵ��
             VOS_BOOL                           *pbBufferEntity �Ƿ񻺴�ʵ��
             VOS_UINT32                         *pulIndex       ����ʵ������
 ����ֵ    : VOS_UINT32
                MN_ERR_NO_ERROR                 �ҵ���ָ���ķ��Ͷ�Ϣʵ��
                ������                          û���ҵ�ָ���ķ��Ͷ�Ϣʵ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_GetSpecificStatusMoEntity(
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus,
    VOS_BOOL                           *pbBufferEntity,
    VOS_UINT32                         *pulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateSpecificMoEntityStatus
 ��������  : ���·��Ͷ�Ϣʵ��״̬
 �������  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  ����ʵ��״̬
             VOS_BOOL                            bBufferEntity �Ƿ񻺴�ʵ��
             VOS_UINT32                          ulIndex       ����ʵ������
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_UpdateSpecificMoEntityStatus(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus
);

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateMoEntity
 ��������  : ���·��Ͷ�Ϣʵ��״̬
 �������  : VOS_BOOL                            bBufferEntity �Ƿ񻺴�ʵ��
             VOS_UINT32                          ulIndex       ����ʵ������
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity �����͵Ķ���ʵ��
             VOS_UINT8                           aucEfSmContent[] �����͵Ķ���
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateSpecificMoEntityStatus
 ��������  : ��շ��Ͷ�Ϣʵ��״̬
 �������  : VOS_BOOL                            bBufferEntity �Ƿ񻺴�ʵ��
             VOS_UINT32                          ulIndex       ����ʵ������
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_DestroySpecificMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex
);

/*****************************************************************************
 �� �� ��  : MN_MSG_CheckMoMsg
 ��������  : ���Ͷ���ʵ��ı��ؼ�飬����FDN ��MO SMS CONTROL
 �������  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity �����͵Ķ���ʵ��
             VOS_UINT8                           aucEfSmContent[] �����͵Ķ�������
 �������  : VOS_BOOL                           *pbRequireCheck �Ƿ�Ҫ��ȴ������
             VOS_BOOL                           *pbBufferEntity �����Ͷ����Ƿ񻺴�
 ����ֵ    : VOS_UINT32
                MN_ERR_NO_ERROR                 ���ִ����ȷ
                ������                          ���ִ��ʧ�ܣ���Ҫ�ܾ��û��Ķ��ŷ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoMsg(
    VOS_UINT8                           aucEfSmContent[],
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbRequireCheck,
    VOS_BOOL                           *pbBufferEntity
);

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMtCustomizeInfo
 ��������  : ��ȡ���Ž�����Ӫ�̶�������
 �������  : MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize  ���Ž�����Ӫ�̶�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize);

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMemExceedFlag
 ��������  : ���¶��Ŵ洢�����־
 �������  : MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag  �洢�����־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag);

/*****************************************************************************
 �� �� ��  : MN_MSG_SetTpRd
 ��������  : ��λ����ʵ����SUBMIT��Ϣ��TP-RD
 �������  : MN_MSG_MO_ENTITY_STRU *pstMoEntity ����ʵ�����ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity);

VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
);
VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID);
VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
);
MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID);


VOS_UINT8 MN_MSG_StartLinkCtrl(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __MNMSGCOMMPROC_H__ */

