/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgSmCommProc.c
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��19��
  ����޸�   :
  ��������   : ʵ��smsģ�鹫��������,�����¼��ϱ�,��NVIM,USIM�Ľ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��19��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2008��6��16��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�ţ�AT2D03830, �޸�en_NV_Item_SMS_SERVICE_Para���д��ش���
  3.��    ��   : 2008��6��16��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�ţ�AT2D03832, EFSMSP�ļ���������ȫFF����Ч��ַ���������
  4.��    ��   : 2008��6��16��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �洢����Ϣ�豸��ʱ���޸Ľ��ն���Ϣ����ʽΪ���洢��û�з���SMMA��Ϣ
  5.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�ţ�AT2D04859,����SMS������PS�����ȣ��ڵ绰�������޷����Ͷ���
  6.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D04609,CMMS��������ӣ�
  7.��    ��   : 2008��8��14��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D04545, SMS���ATģ���MNģ���������븴�Ӷȳ���Ҫ����ֵ20
  8.��    ��   : 2008��8��21��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D05119
  9.��    ��   : 2008��8��25��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D04608
 10.��    ��   : 2008��8��29��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D05344, ����Ϣģ���ʼ�����̽��������SDT�����뵥�巴���������ӺͶϿ�����,Э��ջ���ظ��ϱ���ʼ������¼�;
 11.��    ��   : 2008��09��08��
    ��    ��   : f62575
    �޸�����   : ���ⵥAT2D05583,CBS����ģ�����PC-lint����
 12.��    ��   : 2008��09��11��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D05684, SMSP�ļ���������޸�
 13.��    ��   : 2008��09��26��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D05700, UE�յ����ź�, TAF�ϱ���Ӧ�õĶ��ų��Ȳ������⡣
 14.��    ��   : 2008��10��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06152��AT2D06151��, USIMM�Ż������SMSP�ļ���ض�д����ʧ��
 15.��    ��   : 2008��10��20��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06072, SIM���д��ڱ������Ķ���Ϣ�󣬸�����¼���ɶ�д��
 16.��    ��   : 2008-11-17
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D06843, ����״̬����Ķ���ɾ�����ϱ��ӿ����ն˹������󲻷�����
 17.��    ��   : 2008��12��25��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D07869, SIM���ж���Ϣ�洢���������һ����Ҫ�洢�Ķ������������ģ��д(U)SIM����SMSS�ļ�ʧ��
 18.Date         : 2009-01-12
    Author       : f62575
    Modification : ���ⵥ��:AT2D07548, �������Ĳ�ѯ����ʧ����Ҫ����׼ȷԭ��
 19.��    ��   : 2009��02��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D08974, ����ʱ���ڴ�ӡPR��ַ,����Ϣ���ĵ�ַ����
 20.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D07942��AT2D09557��, �������ĺ����ϱ�ʱ��ϳ�
 21.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D08974, ���Ŵ�ӡ�������
 22.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D10320, PDU��ʽд�����������������ݲ�����ȫһ�µģ�
 23.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D10321, SMMA�ظ��������⣻
 24.��    ��   : 2009��3��30��
    ��    ��   : f62575
    �޸�����   : AT2D10546, ����״̬������TP-PI��TP-PID��TP-DCS�ȿ�ѡ���Ȼ���ȡʧ�ܣ�
 25.��    ��   : 2009��3��30��
    ��    ��   : f62575
    �޸�����   : AT2D10538, ���Ͷ������������USIM���У���ȡʱ�ᵱ��һ������״̬���棻
 26.��    ��   : 2009��4��1��
    ��    ��   : �ܾ� 40661
    �޸�����   : ���ⵥ��:AT2D09786, ��AT+CMGD=,4ɾ������ʱ����ʱ�䲻��Ӧ�������Զ����ű���ⲻ������
 27.��    ��   : 2009��4��7��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�� AT2D06392, ��֧�ֶ��ź�״̬�����NV�洢��ش���ͨ���꿪�عر�
 28.��    ��   : 2009-04-22
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D11256, �򿪺�̨���ٲ��ϵ��壬�޷����յ����š�
 29.��    ��   : 2009��05��11��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D11136��PICS������Ϊ��֧��SM�洢��ִ��GCF��������34.2.5.3����������ʧ��
 30.��    ��   : 2009��05��15��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D11703�����ڹ�������,�����ڴ�ʧ��,���µ��帴λ
 31.��    ��   : 2009��7��18��
    ��    ��   : z40661
    �޸�����   : �ն˿������������
 32.��    ��   : 2009��07��24��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13258��ִ��AT&F0�ָ��������ú󣬶��Ź��ܲ�����
 33.��    ��   : 2009��08��02��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13420������SIM��������ù����У�UE��λ�������ò����޷��أ�
 34.��    ��   : 2009��08��7��
    ��    ��   : f62575
    �޸�����   : STK���Ժ���
 35.��    ��   : 2009��08��20��
    ��    ��   : f62575
    �޸�����   : CLASS0����ŵ��ϱ���ʽ�ο�27005Э�飬��ϸ�����ο��������������_Individual05.SRS.Class0����ʵ�ַ�ʽ.doc��
 36.��    ��   : 2009��08��25��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D14054����EF_USIM_UST���á�EF_USIM_UST���õ�ʵ�ִ������Ʒ���ṩ������һ��
 37.��    ��   : 2009��9��02��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D14189, ִ��GCFЭ��34123������16.1.2��16.2.2ʧ��
 38.��    ��   : 2009��10��16��
     ��    ��   : f62575
     �޸�����   : ���ⵥ��:AT2D15127, ������ΪPS ONLY��������ΪCS PREFER�����ձ��
                  �������ȳ��Դ�CS���ͣ�
 39.��    ��   : 2009��10��23��
     ��    ��   : f62575
     �޸�����   : ���ⵥ��:AT2D15225, ���ö����ط����ܺ�����޷���PS�������⣻
 40.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
 41.��    ��   : 2009��12��9��
     ��    ��   : f62575
     �޸�����   : ���ⵥ��:AT2D15782, ���Ŵ洢����ʱ���յ�����״̬���������ظ�RP-ACK��Ϣ��
                                  ������ͬ����»ظ�RP-ERROR(����ԭ��ֵ22�ڴ�����һ��)��
 42.��    ��   : 2009��12��11��
     ��    ��   : f62575
     �޸�����   : ���ⵥ��:AT2D15875, �����ϵ�ʱ���յ�����״̬�����޸�Ϊ�洢��SIM����
 43.��    ��   : 2009��12��31��
     ��    ��   : f62575
     �޸�����   : PC����׮���룻
 44.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : AT2D16304, STK PP DOWN�������ƺ�SMS��ص�(U)SIM�ļ�REFRESH
 45.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
 46.��    ��   : 2010��4��15��
    ��    ��   : f62575
    �޸�����   : AT2D18539, SMSP�ļ��������ʱ, �������ĵ�ַ��ȡʧ��;
 47.��    ��   : 2010��04��30��
    ��    ��   : F62575
    �޸�����   : ���ⵥ��AT2D15403
                 ������CMT��ʽ�ϱ���CSMS����Ϊ1ʱ��Ӧ�ò��·�CNMA����ȷ���¶��Ž���,
                 ��������żȲ��ϱ�Ҳ���洢������;
 48.��    ��   : 2010��6��10��
    ��    ��   : f62575
    �޸�����   : DTS2010061000153, �رմ�SMSP�ļ��ļ��л�ȡTP-DCS,TP-VP��TP-PID�Ĺ���;
 49.��    ��   : 2010��7��14��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2010071302170: PP DOWNLODAD���������ڴ�й©
 50.��    ��   : 2010��6��30��
    ��    ��   : ��ӳ��
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "MmaAppLocal.h"


#include "mdrv.h"
#include "mnmsgcbencdec.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"
#include "MnComm.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"

#include "MnMsgSendSpm.h"
#include "TafStdlib.h"

#if ( VOS_WIN32 == VOS_OS_VER )
#include "wchar.h"
#else
#endif
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID        PS_FILE_ID_MNMSG_SM_COMM_PROC_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

VOS_UINT32 MN_MSG_CheckMemAvailable(VOS_VOID);
#define MN_MSG_EF_FIRST_RECORD                              (1)

/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
MN_MSG_USIM_EFUST_NEED_REFRESH_STRU stUsimFilesNeedRefreshFlag;
/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

#define MN_MSG_USIM_FILL_BYTE                               0xff

#define MN_MSG_EFSMSP_ADDR_UNIT_LEN                         12
#define MN_MSG_MIN_SRV_PARM_LEN                             28                  /*EFSMSP�ļ����ٵĳ���*/
#define MN_MSG_MAX_ACTION_NODE_NUM                          60                  /*USIM�����ڵ���*/
#define MN_MSG_MAX_USIM_SMS_NUM                             255                 /*USIM�ж��ŵ��������*/
#define MN_MSG_MAX_USIM_SMSR_NUM                            255                 /*USIM�ж��ű�����������*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         500                 /*NVIM�ж��ŵ��������*/
#else
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         0                   /*NVIM�ж��ŵ��������*/
#endif

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
#define MN_MSG_MAX_NVIM_SMSR_REC_NUM                        255                 /*NVIM�ж��ű�����������*/
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

VOS_CHAR *g_pucSmsFileOnFlash                               = VOS_NULL_PTR;

/* SIM CARD TYPE */
#define MN_MSG_CARD_TYPE_USIM     1
#define MN_MSG_CARD_TYPE_SIM      2

#define TAF_MSG_MIN_DESTINATION_ADDRESS_LEN                 (2)
#define TAF_MSG_MAX_DESTINATION_ADDRESS_LEN                 (11)



/*�洢flash�����ļ����*/
FILE                                   *gfpSmsFlash;

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmsrState;                           /* USIM���Ƿ����EfSmsr�ı�־*/
    VOS_UINT8                           ucSmsrRealRecNum;                       /* ��USIM��õ�SMSRʵ�ʼ�¼�� */
    VOS_UINT8                           ucSmsrCurRecNum;                        /* �޿��еļ�¼ʱ,�洢��λ��*/
    VOS_UINT8                           aucEfSmsrList[MN_MSG_MAX_USIM_SMSR_NUM * MN_MSG_EFSMSR_LEN]; /* ����EfSmsr*/
}MN_MSG_USIM_EFSMSR_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmsState;                            /* USIM���Ƿ����EfSms�ı�־*/
    VOS_UINT8                           ucSmsRealRecNum;                        /* ��USIM��õ�SMSʵ�ʼ�¼�� */
    VOS_UINT8                           aucEfSmsList[MN_MSG_MAX_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* ����EfSms*/
    VOS_UINT8                           aucReserve[3];
}MN_MSG_USIM_EFSMS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssState;                           /*USIM���Ƿ����EfSmss�ı�־*/
    VOS_UINT32                          ulFileLen;
    MN_MSG_SMSS_INFO_STRU               stEfSmssInfo;                           /*EFSMSS������*/
    VOS_UINT8                           aucReserve[1];
}MN_MSG_USIM_SMSS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmspState;                           /*USIM���Ƿ����EfSmsp�ı�־*/
    VOS_UINT8                           ucSmspRealRecNum;                       /*EFSMSP�ļ�¼��Ŀ*/
    VOS_UINT8                           aucReserve[3];
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    astEachEfSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];/*��һ��ΪĬ��ֵ*/
}MN_MSG_USIM_EFSMSP_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucList;                                 /*�б����ʱ,����USIM���ܼ�¼��*/
    VOS_UINT8                           ucDelete;                               /*ɾ������ʱ,����USIM���ܼ�¼��*/
    VOS_UINT8                           ucDeleteBegin;                          /*ɾ���������ż�¼ʱ,һ�������USIM����10��,ÿ����USIM���Ϳ�ʼ��¼��*/
    VOS_UINT8                           aucReserve[1];
    VOS_BOOL                            bDeleteReportFlag;                      /*ɾ�����Ž���Ƿ��Ѿ��ϱ���Ӧ��*/
    VOS_UINT8                           ucDeleteStaRpt;                         /*ɾ������״̬����ʱ,����USIM���ܼ�¼��*/
    VOS_UINT8                           ucDeleteStaRptBegin;                    /*ɾ����������״̬��¼ʱ,һ�������USIM����10��,ÿ����USIM���Ϳ�ʼ��¼��*/
    VOS_UINT8                           aucReserve2[2];
    VOS_BOOL                            bDeleteStaRptReportFlag;                /*ɾ������״̬����Ƿ��Ѿ��ϱ���Ӧ��*/
    VOS_UINT8                           ucDeleteEfSmsp;                         /*ɾ�������ļ�EFSMSPʱ,����USIM���ܼ�¼��*/
    VOS_UINT8                           aucReserve3[3];
    VOS_BOOL                            bDeleteEfSmspReportFlag;                /*ɾ�����Ų�������Ƿ��Ѿ��ϱ���Ӧ��*/
}MN_MSG_SET_USIM_REC_STRU;

typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_MO_SMS_CTRL_STRU;

/*****************************************************************************
 Structure      : NAS_MSG_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����MSG��ص�ȫ�ֱ���
 Message origin :
 Note: �ýṹ�Ѿ���Ҫ55k���ڴ棬����ȫ�ֱ��������NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST��
       �Է��ڴ�����ʧ�ܵ���ϵͳ��λ��
 2.��    ��   : 2011��11��08��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DCM&DEVICE��DCM���Ž��ն�����������enMtCustomize
*****************************************************************************/
#define MN_MSG_BUFFER_SMS_SEG_NUM                             1                 /*USIM�ж��ŵ��������*/
typedef struct
{
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
    VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
    MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
    MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST������*/
    MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag;
    MN_MSG_CLASS0_TAILOR_U8          g_enMsgClass0Tailor;
    VOS_UINT8                        ucMoSmsCtrlFlag;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8   enMtCustomize;
    MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    MN_MSG_STORE_MSG_STRU            f_stMsgSmSaved[MN_MSG_BUFFER_SMS_SEG_NUM]; /**/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST;

typedef struct
{
    MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl;
    MN_OPERATION_ID_T                f_tMsgOpId;
    VOS_UINT8                        f_ucMsgInterTpMr;
    VOS_UINT8                        ucSmsRealRecNum;                        /* ��USIM��õ�SMSʵ�ʼ�¼�� */
    VOS_BOOL                         bEfSmsState;                            /* USIM���Ƿ����EfSms�ı�־*/
    VOS_BOOL                         f_bMsgCsRegFlag;
    VOS_BOOL                         f_bMsgPsRegFlag;

    MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
    MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
    MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
    MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
    MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
    VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST;

#define MN_MSG_SEG_USIM_SMS_NUM                                             10
typedef struct
{
    VOS_UINT8                           ucSeqNum;                               /*����������Ϣ���͵���ţ���0��ʼ����*/
    VOS_UINT8                           ucMsgNum;                               /*��ǰ��Ϣ����Ч���ŵ�����*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucEfSmsList[MN_MSG_SEG_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* ����EfSms*/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST;

/*****************************************************************************
 Structure      : NAS_MSG_SDT_MSG_ST
 Description    : PC�طŹ��̣�����MSG��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART1_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART2_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART3_ST;

/*****************************************************************************
  4 ��������
*****************************************************************************/
LOCAL MN_MSG_MO_BUFFER_STRU            f_stMsgMoBuffer;
LOCAL MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
LOCAL MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
LOCAL MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST������*/
LOCAL MN_MSG_USIM_EFSMSR_INFO_STRU     f_stMsgEfSmsrInfo;                      /*USIM������ļ�����Ϣ*/
LOCAL MN_MSG_USIM_EFSMS_INFO_STRU      f_stMsgEfSmsInfo;
LOCAL MN_MSG_USIM_EFSMSP_INFO_STRU     f_stMsgEfSmspInfo;
LOCAL MN_MSG_USIM_SMSS_INFO_STRU       f_stMsgEfSmssInfo;
LOCAL MN_OPERATION_ID_T                f_tMsgOpId;
LOCAL VOS_UINT8                        f_ucMsgInterTpMr;
LOCAL MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
LOCAL MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
LOCAL MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
LOCAL MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
LOCAL MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
LOCAL VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
LOCAL VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
LOCAL VOS_UINT8                        f_aucMsgNvimSmStatus[MN_MSG_MAX_NVIM_SMS_REC_NUM];/*���ڴ��б���NVIM�ж��ŵ�״̬*/
LOCAL VOS_UINT16                       f_usMsgNvimSmsCurReNum = 0;
#endif

LOCAL MN_MSG_MO_SMS_CTRL_STRU          f_stMsgMoSmsCtrlInfo;
LOCAL VOS_UINT8                        f_ucMsgNvimSmsrCurReNum = 0;
LOCAL VOS_BOOL                         f_bMsgCsRegFlag = VOS_FALSE;
LOCAL VOS_BOOL                         f_bMsgPsRegFlag = VOS_FALSE;
LOCAL MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl = MN_MSG_LINK_CTRL_ENABLE;
LOCAL VOS_BOOL                         f_bNeedSendUsim[MN_MSG_MAX_USIM_SMS_NUM];
LOCAL MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;
LOCAL MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
LOCAL SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
MN_MSG_CLASS0_TAILOR_U8                g_enMsgClass0Tailor;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                              g_ucSetEfSmspNoRsp = 0;
VOS_UINT8                              g_ucDisableMoRetry = 0;
#endif


/*lint -save -e958 */

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/
#ifdef __PS_WIN32_RECUR__

/*****************************************************************************
 �� �� ��  : NAS_MSG_RestoreContextData_Part1
 ��������  : �ָ�MSGȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��05��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
  3.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
  4.��    ��   : 2011��11��08��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012111201995��DCM���Ž��ն�������
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part1(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;
    VOS_UINT32                                     ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU                  stMtCustomize;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART1_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART1 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgCfgParm, &pstOutsideCtx->f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
        PS_MEM_CPY(&f_stEfUstInfo, &pstOutsideCtx->f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
        PS_MEM_CPY(f_astMsgOrgSmspInfo,
                   pstOutsideCtx->f_astMsgOrgSmspInfo,
                   (sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM));

        f_stMsgEfSmssInfo.bEfSmssState = f_stEfUstInfo.bEfSmssFlag;
        f_stMsgEfSmspInfo.bEfSmspState = f_stEfUstInfo.bEfSmspFlag;
        f_stMsgEfSmsrInfo.bEfSmsrState = f_stEfUstInfo.bEfSmsrFlag;
        f_stMsgEfSmsInfo.bEfSmsState   = f_stEfUstInfo.bEfSmsFlag;

        PS_MEM_CPY(f_aucMsgOrgSmsrContent,
                   pstOutsideCtx->f_aucMsgOrgSmsrContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));
        f_enMsgSendFailFlag = pstOutsideCtx->f_enMsgSendFailFlag;
        g_enMsgClass0Tailor = pstOutsideCtx->g_enMsgClass0Tailor;

        PS_MEM_CPY(&f_stMsgRetryInfo, &pstOutsideCtx->f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
        PS_MEM_CPY(&f_stMsgRpErrInfo, &pstOutsideCtx->f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

        stMtCustomize.ucActFlag     = MN_MSG_NVIM_ITEM_ACTIVE;
        stMtCustomize.enMtCustomize = pstOutsideCtx->enMtCustomize;
        ulRet                       = NV_Write(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                                               &stMtCustomize,
                                               sizeof(stMtCustomize));
        if (NV_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MSG_RestoreContextData_Part1: Fail to write en_NV_Item_SMS_MO_RETRY_PERIOD.");
        }

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part1 data is restored.");
    }
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : NAS_MSG_RestoreContextData_Part2
 ��������  : �ָ�MSGȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��04��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part2(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART2_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART2== pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        f_enMsgLinkCtrl = pstOutsideCtx->f_enMsgLinkCtrl;
        f_tMsgOpId = pstOutsideCtx->f_tMsgOpId;
        f_ucMsgInterTpMr = pstOutsideCtx->f_ucMsgInterTpMr;

        f_stMsgEfSmssInfo.stEfSmssInfo.ucLastUsedTpMr = f_ucMsgInterTpMr;

        f_stMsgEfSmsInfo.ucSmsRealRecNum = pstOutsideCtx->ucSmsRealRecNum;
        f_stMsgEfSmsInfo.bEfSmsState = pstOutsideCtx->bEfSmsState;
        f_bMsgCsRegFlag = pstOutsideCtx->f_bMsgCsRegFlag;
        f_bMsgPsRegFlag = pstOutsideCtx->f_bMsgPsRegFlag;

        PS_MEM_CPY(&f_stMsgUsimStatusInfo, &pstOutsideCtx->f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
        PS_MEM_CPY(&f_stMsgMoEntity, &pstOutsideCtx->f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgMtEntity,  &pstOutsideCtx->f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgSetUsimRec, &pstOutsideCtx->f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
        PS_MEM_CPY(f_astMsgSetUsimInfo, pstOutsideCtx->f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
        PS_MEM_CPY(f_aucMsgOrgSmContent,
                   pstOutsideCtx->f_aucMsgOrgSmContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN));

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part2 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : NAS_MSG_RestoreContextData_Part3
 ��������  : �ָ�MSGȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ��������ⵥ�ţ�AT2D16941������ʱ���ط�
*****************************************************************************/
VOS_UINT32 NAS_MSG_RestoreContextData_Part3(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART3_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART3 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgEfSmsInfo.aucEfSmsList[(pstOutsideCtx->ucSeqNum * MN_MSG_EFSMS_LEN)],
                   pstOutsideCtx->aucEfSmsList,
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part3 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MSG_SndOutsideContextData_Part1
 ��������  : ��MSG�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��05��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��10��28��
    ��    ��   : f62575
    �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
  3.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
  4.��    ��   : 2011��11��08��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012111201995��DCM���Ž��ն�������
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part1()
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART1_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART1_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part1:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART1;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgCfgParm, &f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stEfUstInfo, &f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgOrgSmspInfo,
               f_astMsgOrgSmspInfo,
               sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmsrContent,
               f_aucMsgOrgSmsrContent,
               (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));

    pstOutsideCtx->f_enMsgSendFailFlag = f_enMsgSendFailFlag;
    pstOutsideCtx->g_enMsgClass0Tailor = g_enMsgClass0Tailor;

    pstOutsideCtx->ucMoSmsCtrlFlag     = f_stMsgMoSmsCtrlInfo.ucActFlg;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRetryInfo,&f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

    pstOutsideCtx->enMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;
    MN_MSG_GetMtCustomizeInfo(&pstOutsideCtx->enMtCustomize);

    DIAG_TraceReport(pSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSG_SndOutsideContextData_Part2
 ��������  : ��MSG�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��03��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  Note:
      MSG�ı���ռ�ڴ�̫����Ҫ�ֿ����ͣ����������ڴ��ʧ�ܣ����µ��帴λ��
  2.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part2()
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART2_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART2_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART2;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->f_enMsgLinkCtrl  = f_enMsgLinkCtrl;
    pstOutsideCtx->f_tMsgOpId       = f_tMsgOpId;

    MN_MSG_GetTpMR(&pstOutsideCtx->f_ucMsgInterTpMr);
    pstOutsideCtx->ucSmsRealRecNum  = f_stMsgEfSmsInfo.ucSmsRealRecNum;

    pstOutsideCtx->bEfSmsState      = f_stMsgEfSmsInfo.bEfSmsState;
    pstOutsideCtx->f_bMsgCsRegFlag  = f_bMsgCsRegFlag;
    pstOutsideCtx->f_bMsgPsRegFlag  = f_bMsgPsRegFlag;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgUsimStatusInfo, &f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMoEntity, &f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMtEntity,  &f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgSetUsimRec, &f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgSetUsimInfo, f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmContent,
               f_aucMsgOrgSmContent,
               MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSG_SndOutsideContextData_Part3
 ��������  : ��MSG�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2010��2��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ��������ⵥ�ţ�AT2D16941������ʱ���ط�
*****************************************************************************/
VOS_VOID NAS_MSG_SndOutsideContextData_Part3()
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;
    VOS_UINT8                                     ucLoop;
    VOS_UINT8                                     ucRemainMsgNum;
    VOS_UINT8                                     ucSendMsgNum;
    VOS_UINT8                                     ucTotalSegNum;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART3_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART3_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid        = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid          = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength             = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST) + 4;
    pSndMsgCB->usMsgID              = MN_MSG_PC_REPLAY_MSG_PART3;
    pSndMsgCB->usReserved           = 0;

    pstOutsideCtx                   = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->ucSeqNum         = 0;
    pstOutsideCtx->aucReserved[0]   = 0;
    pstOutsideCtx->aucReserved[1]   = 0;
    ucTotalSegNum                   = (f_stMsgEfSmsInfo.ucSmsRealRecNum + (MN_MSG_SEG_USIM_SMS_NUM - 1))/
                                      MN_MSG_SEG_USIM_SMS_NUM;
    for (ucLoop = 0; ucLoop < ucTotalSegNum; ucLoop++)
    {
        ucSendMsgNum = (VOS_UINT8)(pstOutsideCtx->ucSeqNum * MN_MSG_SEG_USIM_SMS_NUM);
        ucRemainMsgNum = f_stMsgEfSmsInfo.ucSmsRealRecNum - ucSendMsgNum;
        if (ucRemainMsgNum > MN_MSG_SEG_USIM_SMS_NUM)
        {
            pstOutsideCtx->ucMsgNum = MN_MSG_SEG_USIM_SMS_NUM;
        }
        else
        {
            pstOutsideCtx->ucMsgNum = ucRemainMsgNum;
        }
        PS_MEM_CPY(pstOutsideCtx->aucEfSmsList,
                   &f_stMsgEfSmsInfo.aucEfSmsList[(ucSendMsgNum * MN_MSG_EFSMS_LEN)],
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        DIAG_TraceReport(pSndMsgCB);
        pstOutsideCtx->ucSeqNum++;
    }

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintConfigParmStru
��������  : ��ӡMN_MSG_CONFIG_PARM_STRU�ṹ����
�������  : pstCfg MN_MSG_CONFIG_PARM_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintConfigParmStru(
    MN_MSG_CONFIG_PARM_STRU             *pstCfg
)
{
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvSmAct ", pstCfg->enRcvSmAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enSmMemStore ", pstCfg->enSmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvStaRptAct ", pstCfg->enRcvStaRptAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enStaRptMemStore ", pstCfg->enStaRptMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enCbmMemStore ", pstCfg->enCbmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enAppMemStatus ", pstCfg->enAppMemStatus);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintMsgEntityStru
��������  : ��ӡMN_MSG_MO_ENTITY_STRU�ṹ����
�������  : pstEntity MN_MSG_MO_ENTITY_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintMsgEntityStru(
    MN_MSG_MO_ENTITY_STRU               *pstEntity
)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: mo status          ", pstEntity->enSmaMoState);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: clientId           ", pstEntity->clientId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: opId               ", pstEntity->opId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bEnvelopePending   ", (VOS_INT32)pstEntity->bEnvelopePending);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucMr               ", pstEntity->ucMr);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSendDomain       ", pstEntity->enSendDomain);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSaveArea         ", pstEntity->enSaveArea);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ulSaveIndex        ", (VOS_INT32)pstEntity->ulSaveIndex);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enTpduType         ", pstEntity->enTpduType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSmsMoType        ", pstEntity->enSmsMoType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bReportFlag        ", (VOS_INT32)pstEntity->bReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucRpDataLen        ", pstEntity->ucRpDataLen);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bStaRptInd        ", (VOS_INT32)pstEntity->bStaRptInd);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintMsgEntityStru
��������  : ��ӡMN_MSG_STORE_MSG_STRU�ṹ����
�������  : pstSmSaved MN_MSG_STORE_MSG_STRU�ṹ����
            ulSmNum    ��Ҫ��ӡ����Ϣ�ĸ���
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintStoreMsgStru(
    MN_MSG_STORE_MSG_STRU               *pstSmSaved,
    VOS_UINT32                          ulSmNum
)
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;

    for (ulLoop1 = 0; ulLoop1 < ulSmNum; ulLoop1++)
    {
        MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: index, Used flag", (VOS_INT32)ulLoop1, (VOS_INT32)pstSmSaved->bUsed);
        MN_MSG_PrintMsgEntityStru(&pstSmSaved->stMoInfo);
        for (ulLoop2 = 0; ulLoop2 < MN_MSG_EFSMS_LEN; ulLoop2++)
        {
            MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: SMS content", (VOS_INT32)ulLoop2, (VOS_INT32)pstSmSaved->aucEfSmContent[ulLoop2]);
        }
        pstSmSaved++;
    }

}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmsrInfoStru
��������  : ��ӡMN_MSG_USIM_EFSMSR_INFO_STRU�ṹ����
�������  : pstUsimSmsr MN_MSG_USIM_EFSMSR_INFO_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmsrInfoStru(
    MN_MSG_USIM_EFSMSR_INFO_STRU        *pstUsimSmsr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr State flag", (VOS_INT32)pstUsimSmsr->bEfSmsrState);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr volume", pstUsimSmsr->ucSmsrRealRecNum);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr ocuppy", pstUsimSmsr->ucSmsrCurRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        /*Refer 31102 4.2.32 first byte is Zero, then this record is idle.*/
        MN_INFO_LOG2("MN_MSG_PrintSmsrInfoStru: index, SMS index related",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSmsr->aucEfSmsrList[(MN_MSG_EFSMSR_LEN * ulLoop)]);
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmsInfoStru
��������  : ��ӡMN_MSG_USIM_EFSMS_INFO_STRU�ṹ����
�������  : pstUsimSms MN_MSG_USIM_EFSMS_INFO_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmsInfoStru(
    MN_MSG_USIM_EFSMS_INFO_STRU         *pstUsimSms
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms State flag", (VOS_INT32)pstUsimSms->bEfSmsState);
    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms volume", pstUsimSms->ucSmsRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        MN_INFO_LOG2("MN_MSG_PrintSmsInfoStru: index, Sms Status",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSms->aucEfSmsList[(ulLoop * MN_MSG_EFSMS_LEN)]);
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmspInfoStru
��������  : ��ӡMN_MSG_USIM_EFSMS_INFO_STRU�ṹ����
�������  : pstUsimSmsp MN_MSG_USIM_EFSMSP_INFO_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmspInfoStru(
    MN_MSG_USIM_EFSMSP_INFO_STRU        *pstUsimSmsp
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSmsp;

    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp State flag", (VOS_INT32)pstUsimSmsp->bEfSmspState);
    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp volume", pstUsimSmsp->ucSmspRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_EFSMSP_NUM; ulLoop++)
    {
        pstSmsp = &pstUsimSmsp->astEachEfSmspInfo[ulLoop];
        MN_INFO_LOG2("MN_MSG_PrintSmspInfoStru: index, bUsed flag",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstSmsp->bUsed);
        /*��ӡMN_MSG_USIM_EFSMSP_DTL_INFO_STRU����*/
        MN_MSG_PrintSrvParamStru(&pstUsimSmsp->astEachEfSmspInfo[ulLoop].stParm);
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmssInfoStru
��������  : ��ӡMN_MSG_USIM_SMSS_INFO_STRU�ṹ����
�������  : pstUsimSmss MN_MSG_USIM_SMSS_INFO_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmssInfoStru(
    MN_MSG_SMSS_INFO_STRU          *pstUsimSmss
)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: ucLastUsedTpMr", pstUsimSmss->ucLastUsedTpMr);
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: enMemCapExcNotFlag", pstUsimSmss->enMemCapExcNotFlag);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintEfUstInfo
��������  : ��ӡ��̬����f_stEfUstInfo
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
************************************************************************/
VOS_VOID MN_MSG_PrintEfUstInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmssFlag", (VOS_INT32)f_stEfUstInfo.bEfSmssFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsrFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsrFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmspFlag", (VOS_INT32)f_stEfUstInfo.bEfSmspFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bMoSmsCtrlFlag", (VOS_INT32)f_stEfUstInfo.bMoSmsCtrlFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bSmsPpDataFlag", (VOS_INT32)f_stEfUstInfo.bSmsPpDataFlag);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintMsgMoEntity
��������  : ��ӡ��̬����f_stMsgMoEntity
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintMsgMoEntity(VOS_VOID)
{
    MN_MSG_PrintMsgEntityStru(&f_stMsgMoEntity);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintMsgMtEntity
��������  : ��ӡ��̬����f_stMsgMoEntity
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintMsgMtEntity(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgMtEntity: f_stMsgMtEntity.enSmaMtState is ",
                 f_stMsgMtEntity.enSmaMtState);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmsrInfo
��������  : ��ӡ��̬����f_stMsgEfSmsrInfo
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmsrInfo(VOS_VOID)
{
    MN_MSG_PrintSmsrInfoStru(&f_stMsgEfSmsrInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmsInfo
��������  : ��ӡ��̬����f_stMsgEfSmsInfo
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmsInfo(VOS_VOID)
{
    MN_MSG_PrintSmsInfoStru(&f_stMsgEfSmsInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmspInfo
��������  : ��ӡ��̬����f_stMsgEfSmspInfo
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmspInfo(VOS_VOID)
{
    MN_MSG_PrintSmspInfoStru(&f_stMsgEfSmspInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSmssInfo
��������  : ��ӡ��̬����f_stMsgEfSmssInfo
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSmssInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfo: bEfSmssState", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    MN_MSG_PrintSmssInfoStru(&f_stMsgEfSmssInfo.stEfSmssInfo);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintInterTpMr
��������  : ��ӡ��̬����f_ucMsgInterTpMr
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintInterTpMr(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintInterTpMr: TpMr", f_ucMsgInterTpMr);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintCfgParm
��������  : ��ӡ��̬����f_stMsgCfgParm
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintCfgParm(VOS_VOID)
{
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintUsimStatusInfo
��������  : ��ӡ��̬����f_stMsgCfgParm
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintUsimStatusInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: ucUsimStatus", f_stMsgUsimStatusInfo.ucUsimStatus);
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSetUsimRec
��������  : ��ӡ��̬����f_stMsgSetUsimRec
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSetUsimRec(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucList", f_stMsgSetUsimRec.ucList);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDelete", f_stMsgSetUsimRec.ucDelete);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteBegin", f_stMsgSetUsimRec.ucDeleteBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRpt", f_stMsgSetUsimRec.ucDeleteStaRpt);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRptBegin", f_stMsgSetUsimRec.ucDeleteStaRptBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteStaRptReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteStaRptReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteEfSmsp", f_stMsgSetUsimRec.ucDeleteEfSmsp);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteEfSmspReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteEfSmspReportFlag);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintOpId
��������  : ��ӡ��̬����f_tMsgOpId
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintOpId(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintOpId: f_tMsgOpId", f_tMsgOpId);
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintDomainRegFlag
��������  : ��ӡSMT��PS���CS���ע���־
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��8��13��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintDomainRegFlag(
    VOS_VOID
)
{
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgCsRegFlag ", (VOS_INT32)f_bMsgCsRegFlag);
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgPsRegFlag ", (VOS_INT32)f_bMsgPsRegFlag);
}


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
MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetLinkCtrlParam:f_enMsgLinkCtrl ", f_enMsgLinkCtrl);
    return f_enMsgLinkCtrl;
}

/***********************************************************************
�� �� ��  : MN_MSG_SetLinkCtrl
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
)
{
    if (setValue >= MN_MSG_LINK_CTRL_BUTT)
    {
        MN_ERR_LOG("MN_MSG_SetLinkCtrl: invalid set value.");
        return MN_ERR_INVALIDPARM;
    }

    f_enMsgLinkCtrl = setValue;
    return MN_ERR_NO_ERROR;
}

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST  == FEATURE_ON)
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : MSG_InitFlashMsg
 ��������  : ��ʼ��FLASH�洢���ʵ�ME����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��20��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
                  DTS2011091503912, FLASH�ļ�����������²�����¼��ȡ����
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID MSG_InitFlashMsg(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRealSmsNum;
    VOS_UINT32                          ulFileSize;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucContent[MN_MSG_EFSMS_LEN];

    /* ���FLASH �ļ������ڣ��򲻶�ȡFLASH���ż�¼ */
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_NORM_LOG("MSG_InitFlashMsg: SmsFile not exist.");
        return;
    }

    /* ��ʼ������ME����״̬Ϊ���� */
    PS_MEM_SET(f_aucMsgNvimSmStatus, 0X00, sizeof(f_aucMsgNvimSmStatus));

    PS_MEM_SET(aucContent, 0xff, sizeof(aucContent));

    /* ��ȡFLASH�����ļ����� */
    ulRet = MN_GetFileSize(gfpSmsFlash, &ulFileSize);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_InitFlashMsg: Get File Size error.");

        return;
    }

    /* ����FLASH�����ļ����Ȼ�ȡ��ЧME�������� */
    ulRealSmsNum = ulFileSize / MN_MSG_EFSMS_LEN;
    if (f_usMsgNvimSmsCurReNum < ulRealSmsNum)
    {
        ulRealSmsNum = f_usMsgNvimSmsCurReNum;
    }

    /* FLASH�еĶ�����Ŵ�0��ʼ�����ȡ��ָ������ */
    for (ulIndex = 0; ulIndex < ulRealSmsNum; ulIndex++)
    {
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex, aucContent);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MSG_InitFlashMsg: Read FLASH SMS Error");
        }
        else
        {
            f_aucMsgNvimSmStatus[ulIndex] = aucContent[0];
        }
    }

    return;
}
#else

/*****************************************************************************
 �� �� ��  : MN_MSG_DeliverMsgNotSupport
 ��������  : �ж�UE��֧�ֵĶ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
                  DTS2011091503912, NV_Read�ӿ��Ѿ���֧��ME���ţ��˴����ܲ�����
*****************************************************************************/

LOCAL VOS_VOID MSG_InitNvMsg(VOS_VOID)
{
    /* NV_Read�ӿ��Ѿ���֧��ME���ţ�����˺�����ζ���쳣 */
    MN_WARN_LOG("MSG_InitNvMsg: Get File Size error.");

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : MSG_InitMeMsg
 ��������  : ME���ų�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
                  DTS2011091503912, FLASH�ļ�����������²�����¼��ȡ����
*****************************************************************************/
VOS_VOID MSG_InitMeMsg(VOS_VOID)
{

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    MSG_InitFlashMsg();
#else
    MSG_InitNvMsg();
#endif

}
#endif


/***********************************************************************
�� �� ��  : MSG_GetNvimParmInfo
��������  : ��NVIM�л�ȡ������NVIM�еĶ���Ϣ������Ϣ
�������  : None
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��15��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2009��12��11��
   ��    ��   : f62575
   �޸�����   : ���ⵥ��:AT2D15875, �����ϵ�ʱ���յ�����״̬�����޸�Ϊ�洢��SIM����
 3.��    ��   : 2011��3��21��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011031800199���ƶ�����ҵ�������ʼ�����̵�MN_MSG_SmInit

 4.��    ��   : 2011��12��23��
   ��    ��   : w00167002
   �޸�����   : DTS2011091503912:ME�����ļ�������ʱ��δ���Ǵ��쳣�����
                 ��װ��ʼ����ȡ���ź�����
  5.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
************************************************************************/
LOCAL VOS_VOID MSG_GetNvimParmInfo(VOS_VOID)
{
    VOS_UINT32                                      ulRet;
    MN_MSG_NVIM_RETRY_PERIOD_STRU                   stNvimRetryPeriod;
    MN_MSG_NVIM_RETRY_INTERVAL_STRU                 stNvimRetryInterval;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU                  stClass0Tailor;
    TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU           stNvimRetryCmSrvRejCfg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;

    MN_INFO_LOG("MSG_GetNvimParmInfo: Step into function.");


    PS_MEM_SET(&stNvimRetryPeriod,0,sizeof(stNvimRetryPeriod));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_PERIOD, &stNvimRetryPeriod, sizeof(stNvimRetryPeriod));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryPeriod.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryPeriod = 1000 *stNvimRetryPeriod.ulRetryPeriod;    /* ��Ҫת��Ϊ�� */
    }
    else
    {
        f_stMsgRetryInfo.ulRetryPeriod = 0;
    }

    PS_MEM_SET(&stNvimRetryInterval,0,sizeof(stNvimRetryInterval));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_INTERVAL, &stNvimRetryInterval, sizeof(stNvimRetryInterval));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryInterval.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryInterval = 1000 *stNvimRetryInterval.ulRetryInterval;/* ��Ҫת��Ϊ�� */
    }
    else
    {
        /* ���ںͼ����һ��δ����,��Ĭ��Ϊ���߶�û�м��� */
        f_stMsgRetryInfo.ulRetryPeriod = 0;
        f_stMsgRetryInfo.ulRetryInterval = 0;
    }
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_PERIOD,f_stMsgRetryInfo.ulRetryPeriod);
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_INTERVAL,f_stMsgRetryInfo.ulRetryInterval);

    PS_MEM_SET(&stClass0Tailor,0,sizeof(stClass0Tailor));

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_CLASS0_TAILOR, &ulLength);

    ulRet = NV_Read(en_NV_Item_SMS_CLASS0_TAILOR, &stClass0Tailor, ulLength);
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stClass0Tailor.ucActFlg))
    {
        g_enMsgClass0Tailor = stClass0Tailor.enClass0Tailor;
    }
    else
    {
        g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MSG_InitMeMsg();
#endif

    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    if (ulLength > sizeof(stNvimRetryCmSrvRejCfg))
    {
        f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
        return;
    }

    PS_MEM_SET(&stNvimRetryCmSrvRejCfg, 0x0, sizeof(stNvimRetryCmSrvRejCfg));

    ulRet = NV_Read(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG,
                    &stNvimRetryCmSrvRejCfg,
                    sizeof(stNvimRetryCmSrvRejCfg));

    if (NV_OK != ulRet)
    {
       f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
       return;
    }

    if (stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum > TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM)
    {
        stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum = TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM;
    }

    f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum;

    PS_MEM_CPY(f_stMsgRetryInfo.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum);
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReadAddressFromUsim
 ��������  : ��ȡ(U)SIM���д洢�ĵ�ַ���ڴ棻
 �������  : pucAddrStr ��ַ�׵�ַ
             bRpAddr    ָʾ��ַ�ַ����ı����ʽ: TP���TPDU��ʽ�ĵ�ַ��RP���ַ����
                 VOS_TRUE   RP��ĵ�ַ����, �ο�Э��23040 9.1.2.5 Address fields
                 VOS_FALSE  TP��ĵ�ַ����, �ο�RP��ĵ�ַ��Refer to 24011 8.2.5.1
 �������  : pstBcdAddr MN_MSG_BCD_ADDR_STRU�ṹ�ĵ�ַ
 �� �� ֵ  : ��ַ��ȡ���: MN_ERR_NO_ERROR��ȡ�ɹ�;
                            ����,��ȡʧ��;
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��13��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ

*****************************************************************************/
VOS_UINT32  MN_MSG_ReadAddressFromUsim(
    const VOS_UINT8                     *pucAddrStr,
    VOS_BOOL                            bRpAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
)
{
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulRet;

    ulAddrLen = pucAddrStr[0];

    if (MN_MSG_USIM_FILL_BYTE != ulAddrLen)
    {
        ulRet = MN_MSG_DecodeAddress(pucAddrStr,
                                     bRpAddr,
                                     &stAsciiAddr,
                                     &ulAddrLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
        ulRet = TAF_STD_ConvertAsciiAddrToBcd(&stAsciiAddr, pstBcdAddr);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    else
    {
        PS_MEM_SET(pstBcdAddr, 0x00, sizeof(MN_MSG_BCD_ADDR_STRU));
    }

    return MN_ERR_NO_ERROR;
}

/***********************************************************************
�� �� ��  : MSG_ParseSmsp
��������  : ��EFSMSP�ļ������ݽ���ΪMN_MSG_SRV_PARM_STRU����Ľṹ
�������  : ucLen:EFSMSP�ļ��ĳ���
            pucSmspContent:EFSMSP�ļ�������
�������  : pbSrvParmPresent:���ļ����Ƿ��в�����Ч
            pstSrvParm:�����������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��15��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2010��4��15��
   ��    ��   : f62575
   �޸�����   : AT2D18539, SMSP�ļ��������ʱ, �������ĵ�ַ��ȡʧ��;
 3.��    ��   : 2010��6��10��
   ��    ��   : f62575
   �޸�����   : DTS2010061000153, �رմ�SMSP�ļ��ļ��л�ȡTP-DCS,TP-VP��TP-PID�Ĺ���;
 4.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
 5.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
 6.��    ��   : 2013��08��23��
   ��    ��   : f62575
   �޸�����   : DTS2011051605439������ģ��������³�ʼ����TP-VP��TP-DCS
 7.��    ��   : 2014��9��16��
   ��    ��   : z00161729
   �޸�����   : DTS2014091200106:�й�����4G����0x6f42��������ĺ�����ڣ���indicationָʾbitΪ1����ʾû�У��ֻ����ε������޷���ȡ���������ģ������˶���
************************************************************************/
LOCAL VOS_VOID MSG_ParseSmsp(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                     *pucSmspContent,
    VOS_BOOL                            *pbSrvParmPresent,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    if (ucLen < MN_MSG_MIN_SRV_PARM_LEN)
    {
        *pbSrvParmPresent = VOS_FALSE;
        return;
    }

    *pbSrvParmPresent = VOS_TRUE;

    /*alpha identifier data:*/
    pstSrvParam->stAlphaIdInfo.ulLen = ucLen - MN_MSG_MIN_SRV_PARM_LEN;
    PS_MEM_CPY(pstSrvParam->stAlphaIdInfo.aucData,
               pucSmspContent,
               pstSrvParam->stAlphaIdInfo.ulLen);

    ulPos       = pstSrvParam->stAlphaIdInfo.ulLen;

    /*parameter idicator data:*/
    /*lint -e961*/
    pstSrvParam->ucParmInd = pucSmspContent[ulPos++];
    /*lint +e961*/

    /*TP-destination address data:*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_FALSE,
                                           &pstSrvParam->stDestAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get Destination.");
            PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP-service centre address data:*/
    /* �ڽ����������ĺ���ǰ�����ж�һ�¶������ĺ��볤���ֽڣ����������Ч��
       �Ͱ�ind�ı�ʾbit��Ϊ���ڶ������ĺ��룬9061 nv�������
       24011 8.2.5.2 Destination address element
       In the case of MO transfer, this element contains the destination Service Centre address.
       The RP Destination Address information element is coded as shown in figure 8.6/3GPP TS 24.011.
       The RP Destination Address is a type 4 information element. In the mobile station to network
       direction the minimum value of the length octet is 2 and the maximum value is 11. In the network to mobile station direction,
       the value of the length octet of the element is set to 0.*/
    if ((MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetScAddrIgnoreScIndication)
     && (pucSmspContent[ulPos] >= TAF_MSG_MIN_DESTINATION_ADDRESS_LEN)
     && (pucSmspContent[ulPos] <= TAF_MSG_MAX_DESTINATION_ADDRESS_LEN))
    {
        pstSrvParam->ucParmInd &= ~MN_MSG_SRV_PARM_MASK_SC_ADDR;
    }

    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_TRUE,
                                           &pstSrvParam->stScAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get service centre.");
            PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-PID:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
        {
            pstSrvParam->ucPid = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucPid = 0;
        }
    }
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-DCS:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
        {
            pstSrvParam->ucDcs = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucDcs = 0;
        }
    }
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
         /*TP-VP:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
        {
            /*lint -e961*/
            pstSrvParam->ucValidPeriod = pucSmspContent[ulPos++];
            /*lint +e961*/
        }
        else
        {
            pstSrvParam->ucValidPeriod = 0;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    return;
}

/***********************************************************************
�� �� ��  : MSG_GetUsimFileReq
��������  : ����USIM��ȡ����ļ�������ʧ�ܺ�,���δ������������,���������
�������  : usEfId:�����ȡ�ļ���ID
�������  : ��
�� �� ֵ  : VOS_UINT32:��USIM��������Ľ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : VOS_TaskDelay����
  3.��    ��   : 2011��11��26��
    ��    ��   : f62575
    �޸�����   : DTS2011112100079 EFSMSP�ļ����ڵ�0�������¼����ʱ��
                 ����������Ķ�ȡʧ�����⣬ֻ��ȡĿǰʹ�õ��ĵ�һ����¼��
************************************************************************/
LOCAL VOS_UINT32 MSG_GetUsimFileReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

    ulRet = USIMM_API_WRONG_PARA;

    switch (usEfId)
    {
        case USIMM_USIM_EFUST_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
#if ( VOS_WIN32 == VOS_OS_VER )
            if (0 == g_ucSetEfSmspNoRsp)
            {
                ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
            }
#else
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
#endif

            break;
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            ulRet = MN_MSG_SndUsimGetMaxRecReq(usEfId);
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        default:
            break;
    }

    return ulRet;
}

/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SetSmsFileRefreshFlag
 ��������  : ����SMS�ļ��Ƿ���Ҫ���µı�ʾ
 �������  : VOS_UINT16    usEfId, VOS_UINT8 ucFileRefreshFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����

  2.��    ��   : 2015��03��14��
    ��    ��   : y00245242
    �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
 VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSP_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSR_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag = ucFileRefreshFlag;
             break;

       default:
            MN_WARN_LOG("MN_MSG_SetSmsFileRefreshFlag: The input file name is invalid.");
            break;
    }
}
/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_GetSmsFileRefreshFlag
 ��������  : ����SMS�ļ��Ƿ���Ҫ���µı�ʾ
 �������  : VOS_UINT16    usEfId
 �������  : VOS_UINT8
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag;

        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag;

        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag;

        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag;

       default:
            MN_WARN_LOG("MN_MSG_GetSmsFileRefreshFlag: The input file name is invalid.");
            return VOS_FALSE;
    }
}
/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

/***********************************************************************
�� �� ��  : MN_MSG_GetUsimParmReq
��������  : ����USIM��ȡ����ļ��Ĳ���
�������  : usEfId:�����ȡ�ļ���ID
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2009��10��28��
   ��    ��   : f62575
   �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���
 3.��    ��   : 2010��2��23��
   ��    ��   : f62575
   �޸�����   : ���ⵥ�ţ����Ӷ��Ź��������طŹ���
 4.��    ��   : 2013��7��9��
   ��    ��   : l00208543
   �޸�����   :  V9R1 STK������Ŀ
************************************************************************/
VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

     /* Modified by l00208543 for V9R1 STK����, 2013-07-09, begin  */
     /* ��ȡ�ļ������������仯�����ļ����ھͶ�ȡ��Ϊ�ļ���������Ҫ���²Ŷ�ȡ */

    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmssFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                        break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmspFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            /* fall through */
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsrFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
        /* Modified by l00208543 for V9R1 STK����, 2013-07-09, end */

            /* fall through */
       default:
            /*���нڵ㶼����ʧ��,�����ϵ����*/
            f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;

            /*��Ӧ���ϱ���ʼ�����*/
            MN_MSG_SmInitFinish(MN_CLIENT_ALL);

            #ifndef __PS_WIN32_RECUR__

            if ( (VOS_TRUE == g_ucMnOmConnectFlg)
              && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
            {
                NAS_MSG_SndOutsideContextData_Part1();
                NAS_MSG_SndOutsideContextData_Part2();
                NAS_MSG_SndOutsideContextData_Part3();
            }
            #endif

            break;
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReadMsgNvimInfo
 ��������  : ��ȡ����NVIM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��1��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID )
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageEnable;

    MN_MSG_GetSmsServicePara(&f_stMsgCfgParm, &enMeStorageEnable);
    MN_MSG_MtSpecificFeatureInit();

    MN_MSG_CloseSmsCapabilityFeatureInit();
}

/***********************************************************************
�� �� ��  : MN_MSG_SmInit
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
 2.��    ��   : 2009��12��9��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D15782, ���Ŵ洢����ʱ���յ�����״̬���������ظ�RP-ACK��Ϣ��
                                 ������ͬ����»ظ�RP-ERROR(����ԭ��ֵ22�ڴ�����һ��)��
 3.��    ��   : 2011��02��09��
   ��    ��   : w00166186
   �޸�����   : ���Ӷ�FLASH�洢���ŵĴ���
 4.��    ��   : 2011��3��21��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011031800199���ƶ�����ҵ�������ʼ�����̵�MN_MSG_SmInit
 5.��    ��   : 2011��6��10��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011061006066, EM���ڶ��Ŷ�������
 6.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���ӹرն��Ź��ܶ���
 7.��    ��   : 2012��3��2��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : C50_IPC Project, ���ų�ʼ����������FDN�������û�ȡ
 8.��    ��   : 2013��7��13��
   ��    ��   : l00208543
   �޸�����   : STK������Ŀ��MSG_GetNvimParmInfo�޸�Ϊʼ�յ���
 9.��    ��   : 2013��10��18��
   ��    ��   : w00167002
   �޸�����   : NETSCAN:��CNMI���õ�MT type���ʹ����TAF����<MT>=3���յ�CLASS3
                 ����ʱ�򣬰���+CMT��ʽ�ϱ���
                ��ʼ��TAF MSGģ���б����<MT>=0,��ATģ�鱣��һ��;
10.��    ��   : 2014��03��04��
   ��    ��   : f62575
   �޸�����   : DTS2013091009786 ֧��ͨ����Ʒ��̬�Ͱ汾����FLASH�ļ���Ŀ¼
************************************************************************/
VOS_VOID MN_MSG_SmInit(VOS_VOID)
{
    VOS_UINT32                          i;

    PS_MEM_SET(&f_stMsgEfSmsrInfo,0X00,sizeof(f_stMsgEfSmsrInfo));
    PS_MEM_SET(&f_stMsgEfSmsInfo,0X00,sizeof(f_stMsgEfSmsInfo));
    PS_MEM_SET(&f_stMsgEfSmssInfo,0X00,sizeof(f_stMsgEfSmssInfo));
    PS_MEM_SET(&f_stMsgEfSmspInfo,0X00,sizeof(f_stMsgEfSmspInfo));

    PS_MEM_SET(&f_stEfUstInfo,0X00,sizeof(f_stEfUstInfo));
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    PS_MEM_SET(f_aucMsgNvimSmStatus,0X00,MN_MSG_MAX_NVIM_SMS_REC_NUM);
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if(VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_NORM_LOG("MN_MSG_SmInit:Open SmsFile Fail.\n");
        }
    }
#endif
#endif
    f_ucMsgNvimSmsrCurReNum= 0;

    f_stMsgEfSmssInfo.stEfSmssInfo.enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
    f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;
    f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;


    f_stMsgCfgParm.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    f_stMsgCfgParm.enMtType         = MN_MSG_CNMI_MT_NO_SEND_TYPE;

    MN_MSG_ReadMsgNvimInfo();

    f_ucMsgInterTpMr = 1;
    for (i = 0; i < MN_MSG_MAX_USIM_SMS_NUM; i++ )
    {
        f_bNeedSendUsim[i] = VOS_FALSE;
    }
    PS_MEM_SET(&f_stMsgRetryInfo,0,sizeof(f_stMsgRetryInfo));
    g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;

    MN_MSG_InitMoBuffer();
    MN_MSG_DestroyMoInfo();
    MN_MSG_DestroyMtInfo();

    PS_MEM_SET(f_aucMsgOrgSmContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);
    PS_MEM_SET(f_aucMsgOrgSmsrContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN);
    PS_MEM_SET(f_astMsgOrgSmspInfo,(VOS_CHAR)0XFF,MN_MSG_MAX_USIM_EFSMSP_NUM * sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_MSG_DestroyUsimNode(i);
    }

    PS_MEM_SET(&f_tMsgOpId,0X00,sizeof(f_tMsgOpId));
    PS_MEM_SET(&f_stMsgSetUsimRec,0X00,sizeof(f_stMsgSetUsimRec));
    f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;

    /*��ʼ��USIM�е���ز���*/
    MN_MSG_InitParm();

    MN_MSG_GetFdnMeCfg();

    /*��ʼ����ʱ����ز���*/
    MN_MSG_InitAllTimers();

    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */
    MSG_GetNvimParmInfo();
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, end */

}


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
MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetMoState: f_stMsgMoEntity.enSmaMoState is ", f_stMsgMoEntity.enSmaMoState);
    return f_stMsgMoEntity.enSmaMoState;
}

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
VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMoEntity.enMsgSignallingType = enMsgSignallingType;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoRouteStackType
 ��������  : ��ȡMO MSG��Ϣ������ջ·�ɣ�IMS or PS stack
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  - ��Ϣ·��ջ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : y0024524
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID)
{
    return f_stMsgMoEntity.enMsgSignallingType;
}
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
MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID)
{
    return f_stMsgMtEntity.enSmaMtState;
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-21, begin */
/*****************************************************************************
 �� �� ��  : TAF_MSG_SetMtState
 ��������  : ����MT ״̬
 �������  : enSendOnStackType  MT״̬
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
)
{
    f_stMsgMtEntity.enSmaMtState = enSmaMtState;
}

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
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMtEntity.enMsgSignallingType = enMsgSignallingType;
}

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
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID)
{
    return f_stMsgMtEntity.enMsgSignallingType;
}
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
)
{
    PS_MEM_CPY(pstMoEntity,&f_stMsgMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));
}

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
    �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
  3.��    ��   : 2011��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2011102003157:��ػ�ʱShell���쳣��ӡ;����Ϣ����Ч����ָʾ
                  ��0xff����Ϊ0xffffffff��
  4.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : 2012082906141 ������ݿ�STK����Ⱥ��ʧ������
*****************************************************************************/
VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    /*��ȡ��ǰ���л��棻*/
    for(i = 0; i < f_stMsgMoBuffer.ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_FALSE == pstMoBuffer->bUsed)
        {
            ulIndex = i;
            break;
        }
    }

    return ulIndex;
}

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
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_SaveStoreMsg: Invalid enulIndex. ");
        return;
    }

    /*���������Ѵ���һ��SMMA��Ϣ��������ǰ�������SMMA��Ϣ*/
    if (MN_MSG_MO_TYPE_SMMA == pstMoEntity->enSmsMoType)
    {
        for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
        {
            pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
            if (VOS_FALSE == pstMoBuffer->bUsed)
            {
                if (MN_MSG_MO_TYPE_SMMA == pstMoBuffer->stMoInfo.enSmsMoType)
                {
                    return;
                }
            }
        }
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_TRUE;
    PS_MEM_CPY(&pstMoBuffer->stMoInfo, pstMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(pstMoBuffer->aucEfSmContent, pucEfSmContent, MN_MSG_EFSMS_LEN);
}

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

  2.��    ��   : 2011��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2011102003157:��ػ�ʱShell���쳣��ӡ;����Ϣ����Ч����ָʾ
                  ��0xff����Ϊ0xffffffff��
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
)
{
    VOS_UINT32                          i;

    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_TRUE == pstMoBuffer->bUsed)
        {
            PS_MEM_CPY(pstStoreMsg, pstMoBuffer,sizeof(MN_MSG_STORE_MSG_STRU));

            ulSaveIndex = i;
            break;
        }
    }
    return ulSaveIndex;
}

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
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_FreeStoreMsg: Invalid enulIndex. ");
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_FALSE;
    PS_MEM_SET(&pstMoBuffer->stMoInfo, 0X00, sizeof(MN_MSG_MO_ENTITY_STRU));
}

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
  2.��    ��   : 2013��6��17��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE
  3.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
)
{
    PS_MEM_CPY(&f_stMsgMoEntity,pstMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
    /* ���¶���ҵ���Ƿ���ڱ�־ */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

            /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

    return;
}

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
)
{
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != f_stMsgMoEntity.enSmaMoState)
    {
        return;
    }

    f_stMsgMoEntity.enSaveArea  = enSaveArea;
    f_stMsgMoEntity.ulSaveIndex = ulSaveIndex;
    return;
}

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
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
)
{
    f_stMsgMoEntity.enSmaMoState = enSmaMoState;
}

/***********************************************************************
�� �� ��  : MN_MSG_MoRetryFlag
��������  : ��ȡ�����ش����ܱ��
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE ��ǰ�����˶����ش����ܣ�VOS_FALSE ��ǰû�������ش����ܣ�
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2009��09��01��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��8��3��
   ��    ��   : z60575
   �޸�����   : TQE�޸�
************************************************************************/
VOS_UINT32 MN_MSG_MoRetryFlag(
    VOS_VOID
)
{
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);
    if (0 != stRetryInfo.ulRetryPeriod)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
/***********************************************************************
�� �� ��  : TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo
��������  : Destroy MOʱ������SMSҵ���Ƿ���ڱ�־
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��03��01��
   ��    ��   : s00217060
   �޸�����   : CS��ҵ��״̬�仯ʱ֪ͨMTC
************************************************************************/
VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo(VOS_VOID)
{
    /*
        ��ͬʱ�շ����ŵ������MO Destroyʱ���п��ܻ���MT���̴���
        Destroy IMS��MOʱ,������IMS��MT����,��IMS��־��ΪFALSE
        Destroy CS��MOʱ,������CS��MT����,��CS��־��ΪFALSE
        Destroy PS��MOʱ,������PS��MT����,��PS��־��ΪFALSE
   */

    /* MT״̬ΪNULL��������еı�־ */
    if (MN_MSG_MT_STATE_NULL == f_stMsgMtEntity.enSmaMtState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, end */

        return;
    }

    /* Destroy IMS��MOʱ,������IMS��MT����,��IMS��־��ΪFALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMtEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
    else
    {
        /* Destroy CS��MOʱ,������CS��MT����,��CS��־��ΪFALSE */
        if ( (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
          && (MN_MSG_RCV_DOMAIN_CS != f_stMsgMtEntity.enRcvDomain) )

        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

            /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, end */
        }
        /* Destroy PS��MOʱ,������PS��MT����,��PS��־��ΪFALSE */
        else if ( (MN_MSG_SEND_DOMAIN_PS == f_stMsgMoEntity.enSendDomain)
               && (MN_MSG_RCV_DOMAIN_PS != f_stMsgMtEntity.enRcvDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
}

/***********************************************************************
�� �� ��  : TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo
��������  : Destryoy MTʱ������SMSҵ���Ƿ���ڱ�־
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��09��23��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��03��01��
   ��    ��   : s00217060
   �޸�����   : CS��ҵ��״̬�仯ʱ֪ͨMTC
************************************************************************/
VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo(VOS_VOID)
{
    /*
        ��ͬʱ�շ����ŵ������MT Destroyʱ���п��ܻ���MO���̴���
        Destroy IMS��MTʱ,������IMS��MO����,��IMS��־��ΪFALSE
        Destroy CS��MTʱ,������CS��MO����,��CS��־��ΪFALSE
        Destroy PS��MTʱ,������PS��MO����,��PS��־��ΪFALSE
   */

    /* MO״̬ΪNULL��������еı�־ */
    if (MN_MSG_MO_STATE_NULL == f_stMsgMoEntity.enSmaMoState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, end */
        return;
    }

    /* Destroy IMS��MTʱ,������IMS��MO����,��IMS��־��ΪFALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMoEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
    }
    else
    {
        /* Destroy CS��MTʱ,������CS��MO����,��CS��־��ΪFALSE */
        if ( (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
          && (MN_MSG_SEND_DOMAIN_CS != f_stMsgMoEntity.enSendDomain) )
        {

            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

            /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, end */
        }

        /* Destroy PS��MTʱ,������PS��MO����,��PS��־��ΪFALSE */
        else if ( (MN_MSG_RCV_DOMAIN_PS == f_stMsgMtEntity.enRcvDomain)
               && (MN_MSG_SEND_DOMAIN_PS != f_stMsgMoEntity.enSendDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }

}
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

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
  2.��    ��   : 2013��6��17��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE
  3.��    ��   : 2013��7��15��
    ��    ��   : y00245242
    �޸�����   : ���Ӷ�MO��ջ·�ɳ�ʼ����defaultΪTAF_MSG_SIGNALLING_TYPE_BUTT

  4.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
  5.��    ��   : 2013��09��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ�����������
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
    /* ����ҵ���ʶʱ��Ҫ�õ�MOʵ����Ϣ��Ҫ�����ʵ����Ϣ���ڸ��±�ʶ���� */
    TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo();

    f_stMsgMoEntity.enSmaMoState = MN_MSG_MO_STATE_NULL;
    f_stMsgMoEntity.bEnvelopePending = VOS_FALSE;
    f_stMsgMoEntity.bReportFlag = VOS_FALSE;
    f_stMsgMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
    f_stMsgMoEntity.ulSaveIndex = 0x00;
    f_stMsgMoEntity.enSmsMoType = MN_MSG_MO_TYPE_MAX;
    f_stMsgMoEntity.opId = 0x00;
    f_stMsgMoEntity.clientId = 0x00;
    f_stMsgMoEntity.ucMr = 0x00;
    f_stMsgMoEntity.ucRpDataLen = 0X00;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    f_stMsgMoEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
    f_stMsgMoEntity.enSendDomain        = MN_MSG_SEND_DOMAIN_NO;
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */

    PS_MEM_SET(f_stMsgMoEntity.aucRpDataInfo,0X00,MN_MSG_MAX_RPDATA_LEN);
    PS_MEM_SET(&f_stMsgRpErrInfo,0,sizeof(f_stMsgRpErrInfo));

    /* ��ǰû�������ط����������ʧ�ܼ�¼
       ������Ժ����������̵�Ӱ�� */
    ulRet = MN_MSG_MoRetryFlag();
    if (TAF_TRUE != ulRet)
    {
        MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);
    }
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

}

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
  2.��    ��   : 2013��6��17��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE
  3.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
*****************************************************************************/
VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID)
{
    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_WAIT_REPORT_REQ;

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
    /* ���¶���ҵ���Ƿ���ڱ�־ */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

            /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
            TAF_SendMtcCsSrvInfoInd();
#endif
            /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

    return;
}

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
  2.��    ��   : 2013��6��17��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE
  3.��    ��   : 2013��7��15��
    ��    ��   : y00245242
    �޸�����   : ���ӳ�ʼ��MTջ·�ɳ�ʼ����defaultΪTAF_MSG_SIGNALLING_TYPE_BUTT
  4.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID)
{
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */

    /* ����ҵ���ʶʱ��Ҫ�õ�MTʵ����Ϣ��Ҫ�����ʵ����Ϣ���ڸ��±�ʶ���� */
    TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo();

    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_NULL;

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    f_stMsgMtEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    f_stMsgMtEntity.enRcvDomain  = MN_MSG_RCV_DOMAIN_BUTT;

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */
}


/*****************************************************************************
 �� �� ��  : MN_MSG_CreateNewUsimNode
 ��������  : ��USIM�����첽����,����USIM�Ľڵ�������,���ô˺����鿴�Ƿ��п��еĽڵ���,
             ����п��нڵ�,����д�ýڵ������Ϣ
 �������  : pstSmaUsimInfo  - �����ڵ������Ϣ
 �������  : pulIndex        - �ڵ���������
 �� �� ֵ  : VOS_OK        - �ҵ����е�f_astMsgSetUsimInfo
             VOS_ERR       - δ�ҵ����е�f_astMsgSetUsimInfo

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
)
{
    VOS_UINT32                          i;

    MN_INFO_LOG("MN_MSG_CreateNewUsimNode: step into function.");
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_NORM_LOG1("MN_MSG_CreateNewUsimNode: f_astMsgSetUsimInfo[i].bUsed is ", (VOS_INT32)f_astMsgSetUsimInfo[i].bUsed);
        if (VOS_FALSE == f_astMsgSetUsimInfo[i].bUsed)
        {
            PS_MEM_SET(&f_astMsgSetUsimInfo[i].stUsimInfo,0X00,sizeof(MN_MSG_USIM_INFO_STRU));
            PS_MEM_CPY(&f_astMsgSetUsimInfo[i].stUsimInfo,pstSmaUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
            *pulIndex = i;
            f_astMsgSetUsimInfo[i].bUsed = VOS_TRUE;
            return VOS_OK;
        }
    }
    /*�������ߵ�����*/
    MN_ERR_LOG("MN_MSG_CreateNewUsimNode: failed to create action node.");;
    return VOS_ERR;
}

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
)
{
    if (ulIndex >= MN_MSG_MAX_ACTION_NODE_NUM)
    {
        MN_ERR_LOG("MN_MSG_DestroyUsimNode: Invalid enulIndex. ");
        return;
    }
    PS_MEM_SET(&f_astMsgSetUsimInfo[ulIndex],0X00,sizeof(MN_MSG_USIM_INFO_STRU));
}

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
 2.��    ��   : 2010��10��29��
   ��    ��   : lijun 00171473
   �޸�����   : DTS2010102300072, �ر�E5�Ķ��Ź���
 3.��    ��   : 2011��6��16��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : ���ⵥ��DTS2011062201273 MO SMS CONTROL
 4.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
 5.��    ��   : 2012��4��5��
   ��    ��   : l00171473
   �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
 6.��    ��   : 2013��6��5��
   ��    ��   : w00242748
   �޸�����   : svlte��usim�ӿڵ���
 7.��    ��   : 2013��7��29��
   ��    ��   : y00245242
   �޸�����   : �����µ�USIM�ӿ�
************************************************************************/
VOS_VOID MN_MSG_UpdateUstInfo()
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* E5�رն��Ź��� */
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
    f_stEfUstInfo.bEfSmsFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);
    f_stEfUstInfo.bEfSmssFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);

    /* PS RECUR��Ϊ����ͨ����ʱ����ʱ������ʼ�����̹ر�SMSR�ļ���ȡ���� E5�رն��Ź��� */
#ifdef __PS_WIN32_RECUR__
    f_stEfUstInfo.bEfSmsrFlag = VOS_FALSE;
#else
    f_stEfUstInfo.bEfSmsrFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSR);
#endif

    f_stEfUstInfo.bEfSmspFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSP);

    f_stEfUstInfo.bMoSmsCtrlFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_MOSMS_CONTROL);

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsPpDownlodSupportFlg)
    {
        f_stEfUstInfo.bSmsPpDataFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_DATA_DL_SMSPP);
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

}

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
 2.��    ��   : 2010��10��29��
   ��    ��   : lijun 00171473
   �޸�����   : DTS2010102300072, �ر�E5�Ķ��Ź���

  3.��    ��   : 2011��2��26��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C31�汾֧��SMS���ܺ�򿪶��ŷ��͹���
  4.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���ӹرն��Ź��ܶ���

************************************************************************/
VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID)
{
    VOS_UINT8                           ucActFlg;

    MN_MSG_GetCloseSMSFeature(&ucActFlg);

    /* �رն��Ź��� */
    if (MN_MSG_NVIM_ITEM_ACTIVE == ucActFlg)
    {
        return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
    }

    if (VOS_TRUE == gstMmaValue.stEfustServiceCfg.ucForbidSndMsg)
    {
        if ((VOS_TRUE != f_stEfUstInfo.bEfSmsFlag)
         && (VOS_TRUE != f_stEfUstInfo.bEfSmspFlag))
        {
            return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
        }
    }

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
�� �� ��  : MN_MSG_UpdateSmssInfo
��������  : �����ڴ��б�����EFSMSS�ļ����ڵı�־�Լ��ļ�������
�������  : bEfSmssState:�ļ����ڵı�־
            pstSmssInfo:EFSMSS�ļ�������
�������  : ��
�� �� ֵ  : ��

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
)
{
    f_stMsgEfSmssInfo.bEfSmssState = bEfSmssState;
    f_stMsgEfSmssInfo.ulFileLen = ulFileLen;
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));
}

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
)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        *pucTpMr = stSmssInfo.ucLastUsedTpMr;
    }
    else
    {
        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        *pucTpMr = f_ucMsgInterTpMr;
        f_ucMsgInterTpMr++;
        /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
    }
}

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
VOS_VOID MN_MSG_AddTpMR(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        /*����TP-MR��ֵ������USIM��NVIM��*/
        stSmssInfo.ucLastUsedTpMr++;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmssInfo
��������  : ��ȡ������USIM��NVIM�е�SMSS������,���Ȼ�ȡ������USIM��EFSMSS�ļ�������
�������  : ��
�������  : pstSmssInfo:��ȡEFSMSS������
�� �� ֵ  : VOS_OK:��ȡ�ɹ�
            VOS_ERR:��ȡʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
************************************************************************/
VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;

    MN_NORM_LOG1("MN_MSG_ReadSmssInfo: EF SMSS is available in SIM ", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSS_PARA_LEN);
    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        PS_MEM_CPY(pstSmssInfo,&f_stMsgEfSmssInfo.stEfSmssInfo,sizeof(MN_MSG_SMSS_INFO_STRU));
    }
    else
    {
        ulRet = NV_Read(en_NV_Item_SMS_EFSMSS_Para, &stSmssContent, MN_MSG_EFSMSS_PARA_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmssInfo:Read NVIM Smss Error");
            return VOS_ERR;
        }
        pstSmssInfo->ucLastUsedTpMr = (stSmssContent.aucSmsEfsmssPara)[0];
        if (MN_MSG_SIM_MEM_FULL_SET == (stSmssContent.aucSmsEfsmssPara)[1])
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_SET;
        }
        else
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
        }
    }
    MN_MSG_PrintSmssInfoStru(pstSmssInfo);
    return VOS_OK;
}

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
  2.��    ��   : 2013��7��15��
    ��    ��   : y00245242
    �޸�����   : �ڷ���RP REPORT֮ǰ����ȡ·��ջ��ʶ
  3.��    ��   :2014��9��28��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
)
{
    VOS_UINT8                           ucSendLen;
    VOS_UINT8                           aucSendData[MN_MSG_MAX_LEN];
    VOS_UINT32                          ulRet;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    VOS_UINT8                           ucIdx = 0;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    PS_MEM_SET(aucSendData,0X00,MN_MSG_MAX_LEN);
    if (VOS_TRUE == bRpAck)
    {
        PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
        stRpAck.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ACK;
        stRpAck.bRpUserDataExist = VOS_FALSE;
        MN_MSG_EncodeRpAck(&stRpAck,aucSendData,&ucSendLen);
    }
    else
    {
        PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));
        stRpErr.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ERR;
        stRpErr.ucRpCauseLen = 1;
        stRpErr.stRpCause.bDiagnosticsExist = VOS_FALSE;
        stRpErr.stRpCause.enRpCause = enRpCause;
        stRpErr.bRpUserDataExist = VOS_TRUE;
        stRpErr.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        /*lint -e961*/
        stRpErr.aucRpUserData[ucIdx++] = MN_MSG_TP_MTI_DELIVER_REPORT;          /*TP-Message type indicator*/
        stRpErr.aucRpUserData[ucIdx++] = enTpCause;                             /*Tp Cause*/
        stRpErr.aucRpUserData[ucIdx++] = 0;
        /*lint +e961*/
        stRpErr.ucRpUserDataLen = ucIdx;
        MN_MSG_EncodeRpErr(&stRpErr,aucSendData,&ucSendLen);

        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_SMS_MT_FAIL,
                        &(enRpCause),
                        sizeof(MN_MSG_RP_CAUSE_ENUM_U8));
    }

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    enMsgSignallingType = MN_MSG_GetMtRouteStackType();
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    ulRet = MN_MSG_SendSmsRpReportReq(aucSendData,ucSendLen, enMsgSignallingType);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpReportReq Send Msg Failed");
    }
}

/*****************************************************************************
 �� �� ��  : MSG_RequireDelete
 ��������  : �ж϶��Ŵ洢״̬��ɾ�������Ƿ�ƥ�䣬ƥ�����Ǵ�ɾ����Ϣ
                                                 �����Ǵ�ɾ����Ϣ
 �������  : enDeleteType    - ɾ������
             ucStatus        - ����Ϣ�洢״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE         -  ���Ŵ洢״̬��ɾ������ƥ��
             VOS_FALSE        -  ���Ŵ洢״̬��ɾ�����Ͳ�ƥ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��19��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_BOOL MSG_RequireDelete(
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_UINT8                           ucStatus
)
{
    VOS_BOOL                            bDeleteFlag = VOS_FALSE;

    if (MN_MSG_DELETE_ALL == enDeleteType)
    {
        bDeleteFlag = VOS_TRUE;
    }
    else if (MN_MSG_DELETE_READ == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_UNREAD == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_SEND_TO_NT == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_NOT_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_TO_BE_SEND == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else
    {
        bDeleteFlag = VOS_FALSE;
    }

    return bDeleteFlag;
}


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
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulSmCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;
    VOS_BOOL                            bDeleteFlag;
    VOS_UINT32                          ulDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteBegin;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    *pbDeleteAll = VOS_TRUE;
    ulSmCapacity = MN_MSG_GetSmCapacity(enMemStore);
    for (i = ucBeginIndex; i < ulSmCapacity; i++)
    {
        ulRet = MN_MSG_GetStatus(enMemStore,i,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            ulRet = MN_ERR_NO_ERROR;
            continue;
        }

        bDeleteFlag = MSG_RequireDelete(enDeleteType, ucStatus);
        if (VOS_TRUE == bDeleteFlag)
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            aucSmContent[0] = EF_SMS_STATUS_FREE_SPACE;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = ulFileId;
            stSmaUsimInfo.enDeleteType = enDeleteType;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
            ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
            if (MN_MSG_MEM_STORE_SIM == enMemStore)
            {
                PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
                stWriteUsimInfo.stUsimInfo.clientId = clientId;
                stWriteUsimInfo.stUsimInfo.opId = opId;
                stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
                stWriteUsimInfo.stUsimInfo.enDeleteType = enDeleteType;
                stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)i;
                stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
                stWriteUsimInfo.bCreateNode = VOS_TRUE;
                ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

            }
            else
            {
                ulRet = MN_MSG_WriteSmsFile(enMemStore,&i,VOS_NULL_PTR,aucSmContent);
            }
#endif
            ulDeleteCount++;
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ulDeleteCount))
            {
                break;
            }
            bDeleteFlag = VOS_FALSE;
        }
    }

    if (0 == ulDeleteCount)
    {
        *pbDeleteAll = VOS_TRUE;
        *pulDeleteCount = 0;
        return MN_ERR_NO_ERROR;
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*�����Ѿ���APP�ϱ�ɾ�����*/
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteBegin = 0;
        return ulRet;
    }

    *pulDeleteCount = ulDeleteCount;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE, (VOS_UINT8)ulDeleteCount);

        /*�ж��Ƿ��Ѿ�ɾ�����*/
        if (i < ulSmCapacity)
        {
            /*δ��ȫ��ɾ��,����ɾ���������Ϣ,����δ����APP�ϱ�ɾ�����*/
            *pbDeleteAll = VOS_FALSE;
        }

        /*����δ����APP�ϱ�ɾ�����*/
        f_stMsgSetUsimRec.ucDeleteBegin = (VOS_UINT8)(i + 1);
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_FALSE;
    }

    return MN_ERR_NO_ERROR;
}

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
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulSmsrCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    ulSmsrCapacity = MN_MSG_GetSmsrCapacity(enMemStore);
    PS_MEM_SET(aucSmsrContent,0X00,MN_MSG_EFSMSR_LEN);

    for (i = ucBeginIndex; i < ulSmsrCapacity; i++)
    {
        ulRet = MN_MSG_ReadSmsrInfo(enMemStore, i, aucSmsrContent);
        if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
        {
            aucSmsrContent[0] = EF_SMS_STATUS_REPORT_EMPTY;
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_ALL;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_STARPT;
            ulRet = MN_MSG_WriteSmsrFile(enMemStore,&stSmaUsimInfo,aucSmsrContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            ucDeleteCount++;
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ucDeleteCount))
            {
                break;
            }
        }
    }
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT, ucDeleteCount);
    }
    *pucDeleteCount = ucDeleteCount;
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*�����Ѿ���APP�ϱ�ɾ�����*/
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
        return ulRet;
    }
    /*�ж��Ƿ��Ѿ�ɾ�����*/
    if (i >= ulSmsrCapacity)
    {
        *pbDeleteAll = VOS_TRUE;
        if ((MN_MSG_MEM_STORE_SIM == enMemStore)
         && (ucDeleteCount > 0))
        {
            /*����δ����APP�ϱ�ɾ�����*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = (VOS_UINT8)(i + 1);
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
        }
        else
        {
            /*�����Ѿ���APP�ϱ�ɾ�����*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        }
    }
    else
    {
        /*δ��ȫ��ɾ��,����ɾ���������Ϣ,����δ����APP�ϱ�ɾ�����*/
        *pbDeleteAll = VOS_FALSE;
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
    }
    return MN_ERR_NO_ERROR;
}

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
)
{
    f_stMsgEfSmsInfo.bEfSmsState = bEfSmsState;
    f_stMsgEfSmsInfo.ucSmsRealRecNum = ucEFSmNum;
}

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
)
{
    f_stMsgUsimStatusInfo.enPowerState = enPowerState;
}


/***********************************************************************
�� �� ��  : MN_MSG_StartMo
��������  : ������һ�����ź�,�����ǰ����Ϣ����,���ô˺�������������Ϣ
�������  : ��
�������  : penSendDomain:��ǰ���Ͷ��ŵķ�����
�� �� ֵ  : VOS_OK:���ͻ�����Ϣ�ɹ�
            VOS_ERR:���ͻ�����Ϣʧ��

���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��11��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2010��6��30��
   ��    ��   : ��ӳ��
   �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
 3.��    ��   : 2011��6��24��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011062201273 MO SMS CONTROL
 4.��    ��   : 2011��10��11��
   ��    ��   : k66584
   �޸�����   : DTS2011093003995,������ŷ���ǰ���¹�������ʵ��
 2.��    ��   : 2011��12��25��
   ��    ��   : w00167002
   �޸�����   : DTS2011102003157:��ػ�ʱShell���쳣��ӡ;
                ����Ϣ����Ч����ָʾ��0xff����Ϊ0xffffffff;
                ɾ����ǰ����Ϊ0XFF�ͷ��ص��жϡ�
************************************************************************/
VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
)
{
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    VOS_UINT32                          ulRet;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;

    PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*1.��ȡ���绺�����Ϣ*/
    PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
    ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);


    /*1.1��������Ϣ����ΪSMMA��Ϣ�����жϵ�ǰ�Ƿ���Ҫ����*/
    if ((MN_MSG_NO_AVAILABLE_SMS_REC != ulStoreIndex)
     && (MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType))
    {

        /*��ȡ��ǰUE�Ĵ洢״̬*/
        ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
        if (VOS_ERR == ulRet)
        {
            MN_WARN_LOG("MN_MSG_StartMo: Fail to read SMSS information.");
            return ulRet;
        }
        MN_NORM_LOG1("MN_MSG_StartMo: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

        /*����ǰUE�Ĵ洢״̬Ϊ�洢�豸���У�ֱ�ӷ���*/
        if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
        {
            MN_MSG_FreeStoreMsg(ulStoreIndex);
            PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
            ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        }
        else
        {
            /*����ǰUE�洢�豸״̬���ܽ��ն��ţ�ֱ�ӷ���*/
            ulRet = MN_MSG_CheckMemAvailable();
            if (VOS_OK != ulRet)
            {
                MN_MSG_FreeStoreMsg(ulStoreIndex);
                PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
                ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
            }
        }
    }

    if ((MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
     || (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stStoreMsg.stMoInfo.enSmaMoState)
     || (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stStoreMsg.stMoInfo.enSmaMoState))
    {

        MN_NORM_LOG("MN_MSG_StartMo: no buffer to send.");
        return VOS_ERR;
    }

    /*2. �жϵ�ǰ�Ƿ���ڿ��÷�����*/
    MN_MSG_GetCurSendDomain(stStoreMsg.stMoInfo.enHopeSendDomain,&enSendDomain);
    *penSendDomain = enSendDomain;
    if (MN_MSG_SEND_DOMAIN_NO == enSendDomain)
    {
        MN_WARN_LOG("MN_MSG_StartMo:No Avail Send Domain");
        return VOS_ERR;
    }

    /*3.�������Ͷ���ʱ��ز���*/
    /* ���µ�ǰʵ�ʷ����� */
    enHopeSendDomain = stStoreMsg.stMoInfo.enHopeSendDomain;
    stStoreMsg.stMoInfo.enHopeSendDomain = MN_MSG_GetRealPrefSendDomain(enSendDomain,enHopeSendDomain);
    MN_MSG_CreateMoInfo(&stStoreMsg.stMoInfo);
    MN_MSG_SendMsgToSms(&stStoreMsg.stMoInfo);
    MN_MSG_FreeStoreMsg(ulStoreIndex);

    /*�˴����STK����SMMA��Ϣ���⣻*/
    if (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
    {
        MN_MSG_StartMemNotification();
    }

    return VOS_OK;
}


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
VOS_VOID MN_MSG_StartMemNotification(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    MN_INFO_LOG("MN_MSG_StartMemNotification: into function.");
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*��ȡ��ǰUE�Ĵ洢״̬*/
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_ERR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_StartMemNotification: Fail to read SMSS information.");
        return;
    }
    MN_NORM_LOG1("MN_MSG_StartMemNotification: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

    /*����ǰUE�Ĵ洢״̬Ϊ�洢�豸���У�ֱ�ӷ���*/
    if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
    {
        return;
    }

    ulRet = MN_MSG_CheckMemAvailable();
    if (VOS_OK == ulRet)
    {
        MN_MSG_SendMemAvail();
    }

}


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
 2.��    ��   : 2013��7��3��
   ��    ��   : y00245242
   �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ
 3.��    ��   : 2014��7��29��
   ��    ��   : w00242748
   �޸�����   : DTS2014052806022:���ļ�6F43ָʾSIM���ڴ�������ʵ�ʿ�����
                ����SIM���ڴ滹��������������ʱ��Ҫ֪ͨ���統ǰ�ܽ��ܶ��ţ�
                ��SVLTE��modem��Ӧ֪ͨ(��modem PS only����֧�ַ��Ͷ���)��
************************************************************************/
VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    if (MN_MSG_SEND_DOMAIN_NO == enRealDomain)
    {       
        MN_WARN_LOG("MN_MSG_SendSmma: enRealDomain IS MN_MSG_SEND_DOMAIN_NO.");
        
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

    if ( (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
      && (MN_MSG_SEND_DOMAIN_PS == enRealDomain) )
    {
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
    ulRet = MN_MSG_SendSmsSmmaReq(enRealDomain, enMsgSignallingType);
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */
    if (VOS_ERR == ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_INTERNAL;
        return ulRet;
    }

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    stMoEntity.clientId = clientId;
    stMoEntity.opId = opId;
    stMoEntity.enSendDomain= enRealDomain;
    stMoEntity.enSaveArea = MN_MSG_MEM_STORE_NONE;
    stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
    stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
    stMoEntity.bReportFlag = bReportFlag;
    stMoEntity.ucRpDataLen = 0;
    stMoEntity.enSmaMoState = MN_MSG_MO_STATE_WAIT_REPORT_IND;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-29, begin */
    stMoEntity.enMsgSignallingType = enMsgSignallingType;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-29, end */
    MN_MSG_CreateMoInfo(&stMoEntity);
    return ulRet;
}

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
 2.��    ��   : 2010��6��30��
   ��    ��   : ��ӳ��
   �޸�����   : ���ⵥ��DTS2010071500596��STK���ŵĶ��ƻ���
 3.��    ��   : 2011��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2011102003157:��ػ�ʱShell���쳣��ӡ;����Ϣ����Ч����ָʾ
                  ��0xff����Ϊ0xffffffff��
 4.��    ��   : 2013��7��15��
    ��    ��   : y00245242
    �޸�����   : ��ȡ��Ϣ·�ɱ�ʶ��ȷ��SMMA·��
 5.��    ��   : 2013��09��24��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ
 6.��    ��   : 2015��4��13��
   ��    ��   : s00217060
   �޸�����   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND�е�client id���ԣ��ز�����δ���
************************************************************************/
VOS_VOID MN_MSG_SendMemAvail(VOS_VOID)
{
    MN_MSG_MO_STATE_ENUM_U8             enMoState;
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;
    /* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
    /* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */

    PS_MEM_SET(&stMoEntity, 0x00, sizeof(stMoEntity));

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    enMoState = MN_MSG_GetMoState();
    if ((MN_MSG_SEND_DOMAIN_NO == enRealDomain)
     || (MN_MSG_MO_STATE_WAIT_REPORT_IND == enMoState))
    {

        ulSaveIndex = MN_MSG_GetStoreMsgIndex();

        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
        {

            MN_WARN_LOG("MN_MSG_SendMemAvail,Type:From Mem, No Enough Buffer");
            return;
        }
        /*������õ���Ϣ���뻺��*/
        stMoEntity.bReportFlag = VOS_FALSE;
        stMoEntity.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        stMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
        stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
        stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
        stMoEntity.ucRpDataLen = 0;
        PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
        MN_MSG_SaveStoreMsg(ulSaveIndex,&stMoEntity,aucSmContent);
    }
    else
    {
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
        /* Here send SMMA request to SPM module */
#if (FEATURE_IMS == FEATURE_ON)
        /* ���IMS�����Ҫ��SPMģ������ѡ�񣬷���ֱ����NAS���� */
        TAF_MSG_SendSpmSmmaInd();
#else
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
        (VOS_VOID)MN_MSG_SendSmma(stMoEntity.clientId, stMoEntity.opId, VOS_FALSE, TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */
#endif
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */
    }
}

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
)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stMsgEfSmsInfo.bEfSmsState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stMsgEfSmspInfo.bEfSmspState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stMsgEfSmsrInfo.bEfSmsrState)
            {
                return VOS_TRUE;
            }
            break;
        default:
            MN_INFO_LOG("MN_MSG_IsUsimFileExist:No EF File ID");
            break;
    }

    return VOS_FALSE;
}

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
)
{
    PS_MEM_CPY(pstEfUstInfo,&f_stEfUstInfo,sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    MN_MSG_PrintEfUstInfo();
}

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmsInfo
��������  : ���ڴ��ж�ȡ����USIM�Ķ��Ż��ȡNVIM�еĶ���
�������  : enMemStore:���ŵĴ洢λ��,NVIM��USIM
            ulIndex:��Ҫ��ȡ���ŵ�������
�������  : pucSmsContent:�������ŵ�����
�� �� ֵ  : MN_ERR_NO_ERROR:����ִ�гɹ�
            ����:����ִ�гɹ�
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2010��01��27��
   ��    ��   : w00166186
   �޸�����   : ���Ӷ�FLASH��д�Ĵ���
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
)
{
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)&& (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    VOS_UINT32                          ulRet;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsInfo: USIMM_USIM_EFSMS_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[ulIndex*MN_MSG_EFSMS_LEN] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmContent, (f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex*MN_MSG_EFSMS_LEN)), MN_MSG_EFSMS_LEN);
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[ulIndex] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex,pucSmContent);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmsInfo:Write FLASH Error");
            PS_MEM_SET(f_aucMsgNvimSmStatus, 0x00, sizeof(f_aucMsgNvimSmStatus));
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_READ, ulRet);
            return ulRet;
        }
#else
        if(NV_OK != NV_Read(en_NV_Item_SMS_Content,pucSmContent, MN_MSG_EFSMS_LEN))
        {
           MN_ERR_LOG("MN_MSG_ReadSmsInfo:Read NVIM Sms Error");
           return MN_ERR_CLASS_SMS_NVIM;
        }
#endif

    }
#endif
    else
    {
       MN_NORM_LOG("MN_MSG_ReadSmsInfo: Memory type is not support.");
       return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;
}

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
 2.��    ��   : 2014��07��07��
   ��    ��   : z00234330
   �޸�����   : coverity����
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucEfSmsStatus;

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }

    PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)),
               pucEFContent,
               ucEFSmsLen);

    ulRet = MN_MSG_ParseEFSmContent(pucEFContent, &stScAddr, &stRawData, &ucEfSmsStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        *(f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)) = EF_SMS_STATUS_FREE_SPACE;
    }

    return;
}

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmsrInfo
��������  : ���ڴ��ж�ȡ����USIM�Ķ���״̬������ȡNVIM�еĶ���״̬����
�������  : enMemStore:���ŵĴ洢λ��,NVIM��USIM
            ulIndex:��Ҫ��ȡ����״̬�����������
�������  : pucSmsrContent:��������״̬���������
�� �� ֵ  : MN_ERR_NO_ERROR:����ִ�гɹ�
            ����:ִ��ʧ��
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
)
{
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsrInfo: USIMM_USIM_EFSMSR_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_REPORT_EMPTY == (f_stMsgEfSmsrInfo.aucEfSmsrList[ulIndex*MN_MSG_EFSMSR_LEN]))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmsrContent, (f_stMsgEfSmsrInfo.aucEfSmsrList+ (ulIndex*MN_MSG_EFSMSR_LEN)), MN_MSG_EFSMSR_LEN);
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (ulIndex >= MN_MSG_MAX_NVIM_SMSR_REC_NUM)
            {
                return MN_ERR_CLASS_SMS_INVALID_REC;
            }
            if(NV_OK != NV_Read(en_NV_Item_SMS_Status,pucSmsrContent, ulLen))
            {
               MN_ERR_LOG("MN_MSG_ReadSmsrInfo:Read NVIM Smsr Error");
               return MN_ERR_CLASS_SMS_NVIM;
            }

            if (EF_SMS_STATUS_REPORT_EMPTY == *pucSmsrContent)
            {
                return MN_ERR_CLASS_SMS_EMPTY_REC;
            }
        }

        return MN_ERR_NO_ERROR;

    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else
    {
        MN_NORM_LOG("MN_MSG_ReadSmsrInfo: Memory type is not support.");
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;

}

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
)
{
    if (ucIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
    {
        return;
    }
    PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (ucIndex * ucEFSmsrLen)),
               pucEFContent,
               ucEFSmsrLen);
    return;
}

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
)
{
    VOS_UINT32                          i;

    f_stMsgEfSmsrInfo.bEfSmsrState = bEfSmspState;
    f_stMsgEfSmsrInfo.ucSmsrRealRecNum = ucSmsrRec;
    for (i = 0; i < ucSmsrRec; i++)
    {
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (MN_MSG_EFSMSR_LEN * i)),
                   (pucSmspContent + (usEfLen * i)),
                   MN_MSG_EFSMSR_LEN);
    }
}

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
)
{

    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return;
    }
    f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed = bUsed;
    PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].stParm,
               pstScvParm,
               sizeof(MN_MSG_SRV_PARAM_STRU));

    return;
}

/***********************************************************************
�� �� ��  : MN_MSG_ReadSmspInfo
��������  : ��������ΪulIndex�Ķ��Ų���������
�������  : enMemStore:���Ų����Ĵ洢��,NVIM��USIM
            ulIndex:���Ų���������
�������  : pstSmspPara:�������Ų���������
�� �� ֵ  : MN_ERR_NO_ERROR:��ȡ�ɹ�
            ����:��ȡʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
 3.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
 4.��    ��   : 2013��08��23��
   ��    ��   : f62575
   �޸�����   : DTS2011051605439������ģ��������³�ʼ����TP-VP��TP-DCS
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    VOS_BOOL                            bSrvParmPresent = VOS_FALSE;
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }

    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            /* Modified by f62575 for AT Project��2011-10-17,  Begin*/
            MN_WARN_LOG1("MN_MSG_ReadSmspInfo: ErrCode ", (VOS_INT32)ulRet);
            if (MN_ERR_CLASS_SMS_UPDATE_USIM != ulRet)
            {
                return ulRet;
            }

            MN_MSG_GetUsimPowerState(&enPowerState);
            if (enPowerState <= MN_MSG_USIM_POWER_WAIT_EFSMSP)
            {
                return MN_ERR_CLASS_SMS_UPDATE_USIM;
            }
            /* Modified by f62575 for AT Project��2011-10-17,  End*/
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmspInfo: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (VOS_TRUE != f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].bUsed)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));
    }
    else
    {
        if (NV_OK != NV_Read(en_NV_Item_SMS_EFSMSP_Para, &stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            MN_ERR_LOG("MN_MSG_ReadSmspInfo:Read NVIM Smsp Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);

        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        MSG_ParseSmsp(MN_MSG_MAX_EF_LEN,aucSmspContent,&bSrvParmPresent,pstSrvParam);
        if (VOS_FALSE == bSrvParmPresent)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
    }
    return MN_ERR_NO_ERROR;
}

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
 2.��    ��   : 2013��08��23��
   ��    ��   : f62575
   �޸�����   : DTS2011051605439������ģ��������³�ʼ����TP-VP��TP-DCS
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
)
{
    VOS_UINT32                          i;
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;

    PS_MEM_SET(&stSrvParm, 0, sizeof(MN_MSG_SRV_PARAM_STRU));

    MN_INFO_LOG("MN_MSG_UpdateTotalSmspInfo: step into function.");
    f_stMsgEfSmspInfo.bEfSmspState = bEfSmspState;
    MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: ucNumofSmsp", ucNumofSmsp);
    if (ucNumofSmsp < MN_MSG_MAX_USIM_EFSMSP_NUM)
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = ucNumofSmsp;
    }
    else
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = MN_MSG_MAX_USIM_EFSMSP_NUM;
    }

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                   sizeof(stSrvParm));

        MSG_ParseSmsp(ucEfLen,
                      (pucSmspContent +  (i * ucEfLen)),
                      &bValid,
                      &stSrvParm);
        MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: bValid", (VOS_INT32)bValid);
        if (VOS_TRUE == bValid)
        {
            f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed = VOS_TRUE;
            PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                       &stSrvParm,
                       sizeof(MN_MSG_SRV_PARAM_STRU));
        }
    }
}

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
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;

    *pulTotalRec            = 0;
    *pulUsedRec             = 0;
    *pulEachStatusRec       = 0;
    *(pulEachStatusRec + 1) = 0;
    *(pulEachStatusRec + 2) = 0;
    *(pulEachStatusRec + 3) = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++)
        {
            ucStatus = *(f_stMsgEfSmsInfo.aucEfSmsList + (i * MN_MSG_EFSMS_LEN));
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*pulEachStatusRec)++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        *pulTotalRec = f_usMsgNvimSmsCurReNum;
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            ucStatus = f_aucMsgNvimSmStatus[i];
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec))++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#endif
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmStorageList: Memory type is not support.");
    }
}

/***********************************************************************
�� �� ��  : MN_MSG_GetSmsrStorageList
��������  : ��ȡ��ǰUSIM��NVIM�ж���״̬�����storage list
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
 2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
************************************************************************/
VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    *pulUsedRec = 0;
    *pulTotalRec = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY != f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                (*pulUsedRec)++;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            *pulTotalRec = MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
            {
                PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
                if (NV_OK == NV_Read(en_NV_Item_SMS_Status, aucSmsrContent, ulLen))
                {
                    MN_ERR_LOG("MN_MSG_GetSmsrStorageList:Read NVIM Smsr Error");
                    if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
                    {
                        (*pulUsedRec)++;
                    }
                }
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmsrStorageList: Memory type is not support.");
    }

}

/***********************************************************************
�� �� ��  : MN_MSG_GetSmspStorageList
��������  : ��ȡ��ǰUSIM��NVIM�ж��Ų�����storage list
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
�������  : pulTotalRec:��ǰ�洢����������
            pulUsedRec:��ǰ�洢�������ÿռ�
            pstSrvParam:���Ų����б�
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
 3.��    ��   : 2013��08��23��
   ��    ��   : f62575
   �޸�����   : DTS2011051605439������ģ��������³�ʼ����TP-VP��TP-DCS
************************************************************************/
VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    MN_MSG_SRV_PARAM_STRU               stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;
    MN_MSG_SRV_PARAM_STRU               *pTmpSrvParm;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;

    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0XFF,MN_MSG_MAX_EF_LEN);
    *pulUsedRec = 0;
    pstSrvParam->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmspInfo.ucSmspRealRecNum;
        pTmpSrvParm = pstSrvParam;
        for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
        {
            if (VOS_TRUE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pTmpSrvParm,
                           &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                           sizeof(MN_MSG_SRV_PARAM_STRU));
            }
            else
            {
                pTmpSrvParm->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
            }
            pTmpSrvParm++;
        }
    }
    else
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        *pulTotalRec  = 1;
        if (NV_OK == NV_Read(en_NV_Item_SMS_EFSMSP_Para,&stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);
            /*����NVIM����Alpha Identifier,��һ���ֽڱ�ʾParameter Indicators*/
            MSG_ParseSmsp(MN_MSG_MIN_SRV_PARM_LEN,aucSmspContent,&bValid,&stSrvParm);
            if (VOS_TRUE == bValid)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pstSrvParam,&stSrvParm,sizeof(stSrvParm));
            }
        }
        else
        {
            MN_ERR_LOG("MN_MSG_GetSmspStorageList:Read NVIM Smsp Error");
        }
    }
}

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
 2.��    ��   : 2011��3��21��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011031800199����ȡSM��Ϣ״̬���ӵ��ú�������ֵ�ж�
************************************************************************/
VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
)
{
    VOS_UINT32                          ulPos;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        ulPos = MN_MSG_EFSMS_LEN * ulIndex;
        *pucStatus = f_stMsgEfSmsInfo.aucEfSmsList[ulPos];

        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        else
        {
            return MN_ERR_NO_ERROR;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        *pucStatus = f_aucMsgNvimSmStatus[ulIndex];
        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        return MN_ERR_NO_ERROR;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetStatus: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}


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
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    MN_NORM_LOG("MN_MSG_GetAvailSmRecIndex: Step into function.");
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++ )
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: USIM ", (VOS_INT32)i, (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: NVIM ", (VOS_INT32)i, (f_aucMsgNvimSmStatus[i] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[i] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;
}

/***********************************************************************
�� �� ��  : MN_MSG_GetAvailSmsrRecIndex
��������  : ��ȡ����USIM��NVIM�еĿ��еĶ���״̬��������
�������  : enMemStore:��Ҫ��ȡ���ж���״̬���������Ĵ洢λ��,USIM��NVIM��
�������  : NONE
�� �� ֵ  : ���ж���״̬����������,�޿��ж���״̬����,�򷵻�MN_MSG_NO_AVAILABLE_SMS_REC
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��1��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : ���ⵥ��:DTS2011060803050 STATUS REPORT in ME
 3.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY == f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                ulIndex = i;
                break;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
       if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
       {
           PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
           ulLen = MN_MSG_EFSMSR_LEN;
           for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
           {
               if(NV_OK == NV_Read(en_NV_Item_SMS_Status,aucSmsrContent, ulLen))
               {
                   if (EF_SMS_STATUS_REPORT_EMPTY == aucSmsrContent[0])
                   {
                       ulIndex = i;
                       break;
                   }
               }
               else
               {
                   MN_ERR_LOG("MN_MSG_GetAvailSmsrRecIndex:Read NVIM Smsr Error");
               }
           }
       }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmsrRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;

}

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
VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex = MN_MSG_NO_AVAILABLE_REC;

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
        {
            ucIndex = i;
            break;
        }
    }
    return  ucIndex;
}

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
 2.��    ��   : 2011��7��1��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : ���ⵥ��:DTS2011060803050 STATUS REPORT in ME
 3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
************************************************************************/
VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{

    VOS_UINT32                          ulSaveIndex;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (0 == f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_MSG_NO_AVAILABLE_SMS_REC;
        }

        f_stMsgEfSmsrInfo.ucSmsrCurRecNum = (f_stMsgEfSmsrInfo.ucSmsrCurRecNum + 1) %
                                        (f_stMsgEfSmsrInfo.ucSmsrRealRecNum);
        ulSaveIndex = f_stMsgEfSmsrInfo.ucSmsrCurRecNum;
    }

/*->f62575 PC-LINT error ��Э��ջ��֧��NVIM�洢���� begin*/
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            f_ucMsgNvimSmsrCurReNum = (f_ucMsgNvimSmsrCurReNum + 1) % MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            ulSaveIndex = f_ucMsgNvimSmsrCurReNum;
        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    }
/*->f62575 PC-LINT error ��Э��ջ��֧��NVIM�洢���� end */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetReplaceSmsrRecIndex: enMemStore is ", enMemStore);
    }

    return ulSaveIndex;

}

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
)
{
    *penPowerState = f_stMsgUsimStatusInfo.enPowerState;
    MN_INFO_LOG1("MN_MSG_GetUsimPowerState: f_stMsgUsimStatusInfo.enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}

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
 2.��    ��   : 2012��12��11��
   ��    ��   : L00171473
   �޸�����   : DTS2012121802573, TQE����
************************************************************************/
VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID)
{
    VOS_UINT8                           ucCardStatus;


    ucCardStatus = USIMM_CARD_SERVIC_BUTT;

    /*��ǰ��USIM������λ*/
    MN_NORM_LOG1("MN_MSG_CheckUsimStatus:Usim Status is ", f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MN_MSG_SIM_NOT_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
    {
        (VOS_VOID)MMA_GetUsimStatusFromUsim(&ucCardStatus, VOS_NULL_PTR);
        if (USIMM_CARD_SERVIC_SIM_PIN == ucCardStatus)/*USIMM_CARD_SERVIC_ENUM*/
        {
            return MN_ERR_CLASS_SMS_NEED_PIN1;
        }
        else if (USIMM_CARD_SERVIC_SIM_PUK == ucCardStatus)
        {
            return MN_ERR_CLASS_SMS_NEED_PUK1;
        }
        else if (USIMM_CARD_SERVIC_UNAVAILABLE == ucCardStatus)/*USIMM_CARD_SERVIC_UNAVAILABLE,  313(U)SIM failure*/
        {
            return MN_ERR_CLASS_SMS_UNAVAILABLE;
        }
        /*USIMM_CARD_SERVIC_NET_LCOK,�ֻ��м�¼���ض���HOME PLMN��������SIM����HOME PLMN�����ֻ�NV��ָ���ģ���Ҫ����������*/
        /*USIMM_CARD_SERVIC_IMSI_LCOK,�ֻ��м�¼���ض�����IMSI����ָ��IMSI��SIM�������ֻ���Ҫ����������*/
        /*�������ִ���ԭ��ֵ�Ĵ���Ŀǰ������ȷ����ʱ���޿�����*/
        else
        {
            return MN_ERR_CLASS_SMS_NOUSIM;
        }
    }

    MN_NORM_LOG1("MN_MSG_CheckUsimStatus: SMS power status:", (VOS_INT32)f_stMsgUsimStatusInfo.ucUsimStatus);
    /*USIM�������ϵ������*/
    if (MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
    {
        return MN_ERR_CLASS_SMS_UPDATE_USIM;
    }

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
�� �� ��  : MN_MSG_GetSmCapacity
��������  : ��ȡ����ܴ���USIM��NVIM�ж��ŵ�����
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
VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsInfo.ucSmsRealRecNum;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return f_usMsgNvimSmsCurReNum;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmCapacity: enMemStore is ", enMemStore);
        return 0;
    }
}

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
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmspInfo.ucSmspRealRecNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return MN_MSG_NV_SMSP_VOLUME;
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmspCapacity: enMemStore is ", enMemStore);
        return MN_MSG_FILE_NONE_REC;
    }
}

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
 2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
************************************************************************/
VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            return MN_MSG_MAX_NVIM_SMSR_REC_NUM;
        }
        else
        {
            return 0;
        }

    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
        return 0;
    }

}

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
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex < f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return VOS_TRUE;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex < f_usMsgNvimSmsCurReNum)
        {
            return VOS_TRUE;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
    }
    return VOS_FALSE;
}

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
)
{
    if (ucIndex < f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

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
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/***********************************************************************
�� �� ��  : MN_MSG_GetCurRcvMsgPath
��������  : ��ȡ��ǰ���ŵ���ز���
�������  : NONE
�������  : pstCfgParm:��ǰ���ŵ���ز���
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
)
{
    PS_MEM_CPY(pstCfgParm,&f_stMsgCfgParm,sizeof(MN_MSG_CONFIG_PARM_STRU));
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}

/***********************************************************************
�� �� ��  : MN_MSG_UpdateRegState
��������  : ���µ�ǰCS,PS���ע�����
�������  : pstRcvPath:��Ҫ���µĽ��ն��ŵ�·��
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
)
{
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register domain: ", ucDomain);
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register state: ", (VOS_INT32)bAttachFlag);
    if (MN_MSG_SEND_DOMAIN_PS == ucDomain)
    {
        f_bMsgPsRegFlag = bAttachFlag;
    }
    else
    {
        f_bMsgCsRegFlag = bAttachFlag;
    }
}

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
 2.��    ��   : 2012��12��11��
   ��    ��   : L00171473
   �޸�����   : DTS2012121802573, TQE����
 3.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
 4.��    ��   : 2013��10��17��
   ��    ��   : w00167002
   �޸�����   : NETSCAN:��CNMI���õ�MT type���ʹ����TAF����<MT>=3���յ�CLASS3
                ����ʱ�򣬰���+CMT��ʽ�ϱ���
************************************************************************/
VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
)
{
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == pstRcvPath->enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == pstRcvPath->enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == pstRcvPath->enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == pstRcvPath->enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == f_stMsgCfgParm.enAppMemStatus))
        {
            f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
            f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
            f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
            f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
            f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


            /* ����MT��Ϣ����<MT>=3���յ�CLASS3����ʱ�򣬰���+CMT��ʽ�ϱ� */
            f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

            MN_INFO_LOG("MN_MSG_UpdateRcvMsgPath():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = pstRcvPath->enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = pstRcvPath->enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = pstRcvPath->enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = pstRcvPath->enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = f_stMsgCfgParm.enAppMemStatus;

    if (NV_OK != NV_Write(en_NV_Item_SMS_SERVICE_Para,
                          (stSmsSrvParam.aucSmsServicePara),
                          MN_MSG_SRV_PARAM_LEN))
    {

        MN_ERR_LOG("MN_MSG_UpdateRcvMsgPath:Fail to write RcvMsgPath To NVIM!");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
    f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
    f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
    f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
    f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


    /* ����MT��Ϣ����<MT>=3���յ�CLASS3����ʱ�򣬰���+CMT��ʽ�ϱ� */
    f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

    return MN_ERR_NO_ERROR;
}

/***********************************************************************
�� �� ��  : MN_MSG_GetRcvMsgPath
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
 2.��    ��   : 2013��10��17��
   ��    ��   : w00167002
   �޸�����   : NETSCAN:��CNMI���õ�MT type���ʹ����TAF����<MT>=3���յ�CLASS3
                ����ʱ�򣬰���+CMT��ʽ�ϱ���
************************************************************************/
VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
)
{
    PS_MEM_SET(pstRcvPath,0,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU));
    pstRcvPath->enRcvSmAct = f_stMsgCfgParm.enRcvSmAct;
    pstRcvPath->enSmMemStore = f_stMsgCfgParm.enSmMemStore;
    pstRcvPath->enRcvStaRptAct = f_stMsgCfgParm.enRcvStaRptAct;
    pstRcvPath->enStaRptMemStore = f_stMsgCfgParm.enStaRptMemStore;
    pstRcvPath->enSmsServVersion = f_stMsgCfgParm.enSmsServVersion;

    pstRcvPath->enCnmiMtType     = f_stMsgCfgParm.enMtType;

}

/***********************************************************************
�� �� ��  : MSG_PreferedGetCurSendDomain
��������  : PS���CS�����ȷ���ʱ,��ȡ��ǰ���ŵ�ʵ�ʷ�����
�������  : penHopeSendDomain:��ǰ���Ͷ���ʱ,���������Ķ��ŷ�����
�������  :
�� �� ֵ  : ��ǰ���Ͷ���ʱ,ʵ�ʵĶ��ŷ�����
���ú���  :
��������  :
�޸���ʷ      :
 1.��    ��   : 2009��7��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
PS�����ȷ���
                 CSPS������ʧ��   CS����ʧ��    PS����ʧ��    CSPS�򶼷���ʧ��
CS�����         CS����           CS����        CS����        CS����
PS�����         PS����           PS����        PS����        PS����
CSPS�򶼿���     PS����           PS����        CS����        CS����
CSPS�򶼲�����   �޿�����           �޿�����        �޿�����        �޿�����

CS�����ȷ���
                 CSPS������ʧ��   CS����ʧ��    PS����ʧ��    CSPS�򶼷���ʧ��
CS�����         CS����           CS����        CS����        CS����
PS�����         PS����           PS����        PS����        PS����
CSPS�򶼿���     CS����           PS����        CS����        CS����
CSPS�򶼲�����   �޿�����           �޿�����        �޿�����        �޿�����
  2.��    ��   : 2009��10��16��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D15127, ������ΪPS ONLY��������ΪCS PREFER�����ձ��
                 �������ȳ��Դ�CS���ͣ�
  3.��    ��   : 2009��10��23��
     ��    ��   : f62575
     �޸�����   : ���ⵥ��AT2D15225:, ���ö����ط����ܺ�����޷���PS�������⣻
  4.��    ��   : 2011��3��29��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011030500602������CS����õ��жϱ�׼��UE������Ϊ��PS
                 ONLY, IMSI��CS����Ч��CS��δ��BAR����¿��Գ����ط���֧����PS���ط�����
************************************************************************/
LOCAL MN_MSG_SEND_DOMAIN_ENUM_U8 MSG_PreferedGetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    MN_MSG_DOMAIN_AVAIL_FLAG_U8         enDomainAvail = MN_MSG_NO_DOMAIN_AVAIL;
    VOS_BOOL                            bCsDomainAvailable;

    ulPsAvailable = GMM_ServiceStatusForSms();
    if ((VOS_TRUE == f_bMsgPsRegFlag)
     && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
    {
        enDomainAvail |= MN_MSG_PS_DOMAIN_AVAIL;
    }

    MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
    if (VOS_TRUE == bCsDomainAvailable)
    {
        enDomainAvail |= MN_MSG_CS_DOMAIN_AVAIL;
    }

    if (MN_MSG_CS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* ��ǰ��CS����� */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
    }
    else if (MN_MSG_PS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* ��ǰ��PS����� */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
    }
    else if (MN_MSG_NO_DOMAIN_AVAIL == enDomainAvail)
    {
        /* ��ǰCSPS�򶼲����� */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    }
    else
    {
        /* ��ǰCSPS�򶼿��� */
        if ( (MN_MSG_SEND_FAIL_CSPS_DOMAIN == f_enMsgSendFailFlag)
          || (MN_MSG_SEND_FAIL_PS_DOMAIN == f_enMsgSendFailFlag))
        {
            /*CSPS�򶼷���ʧ��,��Ȼͨ��CS���������*/
            /*PS����ʧ��,ͨ��CS���������*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
        else if(MN_MSG_SEND_FAIL_CS_DOMAIN == f_enMsgSendFailFlag)
        {
            /*CS����ʧ��,ͨ��PS���������*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
        else
        {
            /* CSPS��û�з���ʧ��,���ݵ�ǰ���ý��з��� */
            if(MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
            }
            else
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
            }
        }
    }

    return enRealSendDomain;
}

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
 2.��    ��   : 2011��3��29��
   ��    ��   : ��ӳ��/f62575
   �޸�����   : DTS2011030500602������CS����õ��жϱ�׼��UE������Ϊ��PS
                ONLY, IMSI��CS����Ч��CS��δ��BAR����¿��Գ����ط���֧����PS���ط�����
 3.��    ��   : 2012��5��7��
   ��    ��   : z00161729
   �޸�����   : GUL BG�����޸�
************************************************************************/
VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    VOS_UINT32                          bCsDomainAvailable;

    *penRealSendDomain = MN_MSG_SEND_DOMAIN_NO ;

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
    {
        /* ����ָ�����������û������ţ�L�����棬�ظ�error ind�����������ط������ٴδ��������� ��
           �˴������ж�f_bMsgPsRegFlagΪVOS_TRUE */
        *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        return;
     }
#endif

    ulPsAvailable = GMM_ServiceStatusForSms();
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :f_bMsgPsRegFlag is ", (VOS_INT32)f_bMsgPsRegFlag);
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :ulPsAvailable is ", (VOS_INT32)ulPsAvailable);
    if (MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
    {
        if ((VOS_TRUE == f_bMsgPsRegFlag)
         && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
    }
    else if (MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
    {
        MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
        if (VOS_TRUE == bCsDomainAvailable)
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
    }
    else if ( (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
           || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain))
    {
        *penRealSendDomain = MSG_PreferedGetCurSendDomain(enHopeSendDomain);
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetCurSendDomain hoped domain: ", enHopeSendDomain);
    }
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :send domain is ", (VOS_INT32)*penRealSendDomain);
}

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
)
{
    *penMemStatus = f_stMsgCfgParm.enAppMemStatus;
    MN_INFO_LOG1("MN_MSG_GetCurAppMemStatus: f_stMsgCfgParm.enAppMemStatus is ", f_stMsgCfgParm.enAppMemStatus);
}

/***********************************************************************
�� �� ��  : MN_MSG_UpdateAppMemStatus
��������  : ����APP���ڴ�ʹ��״̬
�������  : enMemStatus:��Ҫ���µ�APP���ڴ�ʹ��״̬
�������  : NONE
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�
            MN_ERR_CLASS_SMS_NVIM:����ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��12��06��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��11��
   ��    ��   : L00171473
   �޸�����   : DTS2012121802573, TQE����
 3.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
************************************************************************/
VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == f_stMsgCfgParm.enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == f_stMsgCfgParm.enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == f_stMsgCfgParm.enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enCbmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == enMemStatus))
        {
            f_stMsgCfgParm.enAppMemStatus = enMemStatus;
            MN_INFO_LOG("MN_MSG_UpdateAppMemStatus():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = f_stMsgCfgParm.enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = f_stMsgCfgParm.enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = f_stMsgCfgParm.enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enCbmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = enMemStatus;

    ulRet = NV_Write(en_NV_Item_SMS_SERVICE_Para,
                     &stSmsSrvParam,
                     MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_UpdateAppMemStatus:Write NV Failed");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enAppMemStatus = enMemStatus;

    return MN_ERR_NO_ERROR;
}


/***********************************************************************
�� �� ��  : MN_MSG_FindNodeByUsimResult
��������  : �յ���USIM���صĽ����¼ʱ,�ҵ�������¼��ǰ���в����Ľڵ���Ϣf_astMsgSetUsimInfo
�������  : ucRecIndex:����USIM�ļ�¼��
            usEfId:����USIM���ļ�EFID
�������  : pstSmaUsimInfo:�ҵ��Ľڵ���Ϣf_astMsgSetUsimInfo
            pucIndex:�ҵ��ڵ���USIM�ڵ��б������
�� �� ֵ  : VOS_OK:�ɹ��ҵ�
            VOS_ERR:δ���ҵ�
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
    MN_MSG_USIM_INFO_STRU               *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
)
{
    VOS_UINT32                          i;
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        if (VOS_TRUE == f_astMsgSetUsimInfo[i].bUsed)
        {
            if ((ucRecIndex == f_astMsgSetUsimInfo[i].stUsimInfo.ucRecIndex)
             && (usEfId == f_astMsgSetUsimInfo[i].stUsimInfo.usEfId))
            {
                PS_MEM_CPY(pstSmaUsimInfo,&f_astMsgSetUsimInfo[i].stUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
                *pulIndex = i;
                return VOS_OK;
            }
        }
    }
    return VOS_ERR;
}

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
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        return f_stMsgSetUsimRec.ucList;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        return f_stMsgSetUsimRec.ucDelete;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteBegin;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRpt;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    }
    else
    {
        return f_stMsgSetUsimRec.ucDeleteEfSmsp;
    }
}

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
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        return f_stMsgSetUsimRec.bDeleteReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.bDeleteStaRptReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        return f_stMsgSetUsimRec.bDeleteEfSmspReportFlag;
    }
    else
    {
        return VOS_TRUE;
    }
}

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
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        f_stMsgSetUsimRec.bDeleteReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = bReportFlag;
    }
    else
    {
        return ;
    }
}

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
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        f_stMsgSetUsimRec.ucList = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        f_stMsgSetUsimRec.ucDelete = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteBegin = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRpt = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = ucRec;
    }
    else
    {
        f_stMsgSetUsimRec.ucDeleteEfSmsp = ucRec;
    }
}

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
  1.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
  2.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  3.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������ ��
  4.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:MN_MSG_MoSmsControlEnvelopeReq����client ID����
  5.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��MN_GetLaiForMoCtrl=>TAF_SDC_GetCurrentLai
  6.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
*****************************************************************************/
VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    SI_STK_ENVELOPE_STRU                stENStru;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stENStru, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stENStru.enEnvelopeType     = SI_STK_ENVELOPE_SMSCRTL;
    stENStru.DeviceId.ucSDId    = SI_STK_DEV_TERMINAL;
    stENStru.DeviceId.ucDDId    = SI_STK_DEV_UICC;

    stENStru.uEnvelope.MOSMSCtrl.OP_Addr1 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Addr2 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Local = 1;

    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucNumType    = pstRpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucLen        = pstRpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.pucAddr      = pstRpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucNumType    = pstTpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucLen        = pstTpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.pucAddr      = pstTpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.LocInfo.pucATSLI   = aucLI;

    /* ��ȡENVELOPE��Ϣ����: ����С����Ϣ */
    TAF_SDC_Get3GppCurrentLai(aucLI, &stENStru.uEnvelope.MOSMSCtrl.LocInfo.ulLen);


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stENStru);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_MoSmsControlEnvelopeReq: Usim Returns Error");
        return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
    }
    else
    {
        return MN_ERR_NO_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SmsPPEnvelopeReq
 ��������  : �յ�Class 2 ��PIDΪUSIM DataDownLad����ʱ,��Ҫ�·�Envelope datadownload��USIM��
 �������  : pstAddr:     SC Addr
             pucTpduData: SMS TPDU (SMS-DELIVER)
 �������  : ��
 �� �� ֵ  : VOS_TRUE; ���سɹ�
             VOS_FALSE:����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��7��14��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2010071302170: PP DOWNLODAD���������ڴ�й©
  3.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������ ��
  4.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:SI_STK_EnvelopeDownload�ӿ�����client ID
  5.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
*****************************************************************************/
VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
)
{
    SI_STK_ENVELOPE_STRU stDataDownLoad;
    SI_STK_SMS_PP_DOWNLOAD_STRU *pstPPDown;
    VOS_UINT32 ulRet = VOS_ERR;
    VOS_UINT32 ulOffset;

    if(SI_STK_DATA_MAX_LEN <(pstAddr->ucBcdLen+ulTpduLen))
    {
        return VOS_ERR;
    }

    PS_MEM_SET(&stDataDownLoad, 0, sizeof(stDataDownLoad));

    stDataDownLoad.enEnvelopeType   = SI_STK_ENVELOPE_PPDOWN;
    stDataDownLoad.DeviceId.ucSDId  = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId  = SI_DEVICE_UICC;

    pstPPDown = &stDataDownLoad.uEnvelope.PPDown;
    /*��д�������ĵ�ַ*/
    pstPPDown->OP_Addr = 1;
    pstPPDown->Addr.ucNumType = pstAddr->addrType;
    pstPPDown->Addr.ucLen     = pstAddr->ucBcdLen;

    PS_MEM_CPY(stDataDownLoad.aucData, pstAddr->aucBcdNum, pstPPDown->Addr.ucLen);

    pstPPDown->Addr.pucAddr = stDataDownLoad.aucData;

    ulOffset = pstPPDown->Addr.ucLen;

    /*��д����PDU����*/
    pstPPDown->OP_TPDU = 1;
    pstPPDown->TPDU.ulLen = ulTpduLen;

    PS_MEM_CPY(&stDataDownLoad.aucData[ulOffset], pucTpduData, pstPPDown->TPDU.ulLen);

    pstPPDown->TPDU.pucTPDU = &stDataDownLoad.aucData[ulOffset];


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, MN_CLIENT_ID_BROADCAST,&stDataDownLoad);

/*
    ����USIM�ṩ��envelope data download�����������·���USIM
    if �������سɹ�
        ���� TAF_OK
    else
        ���� MN_ERR
*/

    return ulRet;
}

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
 2.��    ��   : 2012��8��10��
   ��    ��   : y00213812
   �޸�����   : DTS2012082204471, TQE����
 3.��    ��   : 2012��12��26��
   ��    ��   : ���� id:00214637
   �޸�����  : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������ ��
 4.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
************************************************************************/
VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucWriteData[MN_MSG_MAX_EF_LEN];
    VOS_UINT32                          ulUsimIndex = 0;
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSS_ID;
    }
    ulRet       = 0;

    PS_MEM_SET(aucWriteData,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0x00,MN_MSG_EFSMSS_PARA_LEN);

    aucWriteData[0] = pstSmssInfo->ucLastUsedTpMr;
    if (MN_MSG_MEM_FULL_SET == pstSmssInfo->enMemCapExcNotFlag)
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_SET;
    }
    else
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_UNSET;
    }

    /*�ȸ����ڴ��е���Ϣ*/
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));

    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmssFile:Add Usim Node Failed");
            return ;
        }
        PS_MEM_SET(&stUsimInfo,0X00, sizeof(stUsimInfo));


        stUsimInfo.opId = 0;
        stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stUsimInfo.ucRecIndex = MN_MSG_USIM_DEF_REC;
        stUsimInfo.enSmaUsimAction = MN_MSG_USIM_SET_EFSMSS;

        /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
        ulRet = MN_MSG_CreateNewUsimNode(&stUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:CreateNewUsimNode Error");
        }
        /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/
    }
    else
    {
        PS_MEM_CPY(&stSmssContent, (VOS_VOID*)aucWriteData, MN_MSG_MAX_EF_LEN);
        ulRet = NV_Write(en_NV_Item_SMS_EFSMSS_Para,(VOS_VOID*)&stSmssContent,MN_MSG_MAX_EF_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:Write NVIM Error");
        }
    }
}

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)\
  && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
/***********************************************************************
�� �� ��  : MN_MSG_WriteSmsFile
��������  : �����ڴ�,USIM�к�NVIM������SMS�ļ�ֵ
�������  : enMemStore:��ǰ�Ĵ洢��,USIM��NVIM
            pulMeIndex:��FLASHд�����ǵ�����ֵ
            pstWriteUsimInfo:��USIM��д����Ϣʱ,USIM�ڵ�������Ϣ
            pucContentInfo:��Ҫ���������
�������  : ��
�� �� ֵ  : MN_ERR_NO_ERROR:���³ɹ�,
            ����:ʧ���Լ�ʧ�ܵ�ԭ��ֵ
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��02��11��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    ulRet       = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_NULL_PTR == pstWriteUsimInfo)
        {
            return MN_ERR_NULLPTR;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == pstWriteUsimInfo->bCreateNode)
        {
            /*����USIMʱ,��Ҫ��ԭʼ�Ķ��ű�������*/
            ucOrgIndex = pstWriteUsimInfo->stUsimInfo.ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(&(pstWriteUsimInfo->stUsimInfo),&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*�����ڴ��е���Ϣ*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (VOS_NULL_PTR == pulMeIndex)
        {
            return MN_ERR_NULLPTR;
        }

        ulRet = MN_MSG_WriteMsgInFlashByIndex(*pulMeIndex,pucContentInfo);

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write FLASH Error");
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_WRITE, ulRet);
            return ulRet;
        }
        else
        {
            /*�����ڴ���NVIM�еĶ���״̬*/
            f_aucMsgNvimSmStatus[*pulMeIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}
#else
/***********************************************************************
�� �� ��  : MN_MSG_WriteSmsFile
��������  : �����ڴ�,USIM�к�NVIM������SMS�ļ�ֵ
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
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == bCreateNode)
        {
            /*����USIMʱ,��Ҫ��ԭʼ�Ķ��ű�������*/
            ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*�����ڴ��е���Ϣ*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_Content,
                              (VOS_VOID*)pucContentInfo,
                              MN_MSG_EFSMS_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        else
        {
            /*�����ڴ���NVIM�еĶ���״̬*/
            f_aucMsgNvimSmStatus[pstSmaUsimInfo->ucRecIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}

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
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType   = TAF_SDC_GetSimType();
    ulRet       = 0;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        /*����USIMʱ,��Ҫ��ԭʼ�Ķ���״̬���汣������*/
        ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
        PS_MEM_SET((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),0X00,MN_MSG_EFSMSR_LEN);
        PS_MEM_CPY((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),
                   (f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   MN_MSG_EFSMSR_LEN);
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsrFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*�����ڴ��е���Ϣ*/
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMSR_LEN);
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if(MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (NV_OK != NV_Write(en_NV_Item_SMS_Status,pucContentInfo,MN_MSG_EFSMSR_LEN))
            {
                MN_ERR_LOG("MN_MSG_WriteSmsrFile:Write NVIM Error");
                return MN_ERR_CLASS_SMS_NVIM;
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsrFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;

}

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
 2.��    ��   : 2013��05��20��
   ��    ��   : m00217266
   �޸�����   : nv����
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU         *pstSrvParam
)
{
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAlphaIdLen;
    VOS_UINT32                          ulAddrlen;
    VOS_UINT32                          ulPos = 0;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stSmspContent;
    VOS_UINT8                           ucLen;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstEfSmspRec;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }
    ulRet       = 0;

    MN_INFO_LOG("MN_MSG_WriteSmspFile: step into function.");

    PS_MEM_SET(&stSmspContent,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    pstEfSmspRec = &f_stMsgEfSmspInfo.astEachEfSmspInfo[pstSmaUsimInfo->ucRecIndex];
    ucLen = (VOS_UINT8)(MN_MSG_MIN_SRV_PARM_LEN + pstEfSmspRec->stParm.stAlphaIdInfo.ulLen);

    /*Alpha Identifier*/
    if (pstSrvParam->stAlphaIdInfo.ulLen > pstEfSmspRec->stParm.stAlphaIdInfo.ulLen)
    {
        ulAlphaIdLen = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;
    }
    else
    {
        ulAlphaIdLen = pstSrvParam->stAlphaIdInfo.ulLen;
    }

    PS_MEM_CPY(aucSmspContent,pstSrvParam->stAlphaIdInfo.aucData,ulAlphaIdLen);

    /*���α�����ALPHAID�������ALPHAID�����������ĳ���Ϊ�̶�ֵ�����û������ʵ�����ݳ����޹�*/
    ulPos = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;

    /*Parameter Indicators*/
    MN_INFO_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->ucParmInd", pstSrvParam->ucParmInd);
    /*lint -e961*/
    aucSmspContent[ulPos++] = pstSrvParam->ucParmInd;
    /*lint +e961*/

    /*TP Destination Address*/
    MN_NORM_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->stDestAddr.ucBcdLen", pstSrvParam->stDestAddr.ucBcdLen);
    PS_MEM_SET(&aucSmspContent[ulPos], (VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
     && (0 != pstSrvParam->stDestAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU*)&pstSrvParam->stDestAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_FALSE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TS Service Centre Address*/
    PS_MEM_SET(&aucSmspContent[ulPos],(VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
     && (0 != pstSrvParam->stScAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU *)&pstSrvParam->stScAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_TRUE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP Protocol Identifier*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucPid;
        /*lint +e961*/
    }

    /*TP Data Coding Scheme*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucDcs;
        /*lint +e961*/
    }

    /*TP Validity Period*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucValidPeriod;
        /*lint +e961*/
    }
    PS_MEM_CPY(&stSmspContent, aucSmspContent, MN_MSG_MAX_EF_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile:Add Usim Node Failed");
            if (MN_MSG_USIM_DELETE_EFSMSP == pstSmaUsimInfo->enSmaUsimAction)
            {
                f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = VOS_TRUE;
            }
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*�����ڴ��е���Ϣ*/
        if (MN_MSG_SRV_PARM_TOTALABSENT == ((pstSrvParam->ucParmInd) & MN_MSG_SRV_PARM_TOTALABSENT))
        {
            pstEfSmspRec->bUsed = VOS_FALSE;
        }
        else
        {
            pstEfSmspRec->bUsed = VOS_TRUE;
        }

        /*���ϵĶ��ŷ��������������*/
        PS_MEM_CPY(&f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex],
                   pstEfSmspRec,
                   sizeof(f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex]));

        PS_MEM_CPY(&pstEfSmspRec->stParm, pstSrvParam, sizeof(pstEfSmspRec->stParm));
        pstEfSmspRec->stParm.stAlphaIdInfo.ulLen = ulAlphaIdLen;
    }
    else
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_EFSMSP_Para,stSmspContent.aucSmsEfsmspPara,MN_MSG_MAX_EF_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmspFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
    }

    return MN_ERR_NO_ERROR;
}


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
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pstSrvParam,0X00,sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    PS_MEM_CPY(pstSrvParam,&f_astMsgOrgSmspInfo[ucIndex],sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
}

/***********************************************************************
�� �� ��  : MN_MSG_RecoverOrgSm
��������  : ɾ����д����,USIM����ʧ��,��Ҫ���ڴ��еĶ��Żָ�����
�������  : ucIndex:�ָ����Ŵ��������
�������  : pucSmContent:��Ҫ�ָ��Ķ��ŵ�����
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
)
{
    if (ucIndex >= MN_MSG_MAX_ORG_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_CPY(pucSmContent,
              (f_aucMsgOrgSmContent + (ucIndex * MN_MSG_EFSMS_LEN)),
              MN_MSG_EFSMS_LEN);
}

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
)
{
    if (ucIndex >= MN_MSG_MAX_DELETE_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSmsr:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
    PS_MEM_CPY(pucSmsrContent,
               (f_aucMsgOrgSmsrContent + (ucIndex * MN_MSG_EFSMSR_LEN)),
               MN_MSG_EFSMSR_LEN);
}

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
 2.��    ��   : 2013��7��13��
   ��    ��   : l00208543
   �޸�����   : STK������Ŀ��ɾ��MSG_GetNvimParmInfo�ĵ���

************************************************************************/
VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_INFO_LOG("MN_MSG_SmCfgDataInit:Step into function.");

    /* Deleted by l00208543 for V9R1 STK����, 2013-7-11, begin */
    /* Deleted by l00208543 for V9R1 STK����, 2013-7-11, end */

    MN_INFO_LOG1("MN_MSG_SmCfgDataInit:enUsimStatus is ", (VOS_INT32)enUsimStatus);
    MN_INFO_LOG1("MN_MSG_SmCfgDataInit: current enUsimStatus is ",f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MNPH_USIM_STATUS_AVILABLE == enUsimStatus)
    {
        if (MN_MSG_SIM_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
        {
            MN_NORM_LOG("MN_MSG_CfgDataInit:Rcv Usim Exist Flag Again");
            if ((MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
             && (MN_MSG_USIM_POWER_BEGIN != f_stMsgUsimStatusInfo.enPowerState))
            {
                MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
                MN_NORM_LOG("MN_MSG_CfgDataInit:Stop Timer");
            }
        }
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;

        MN_MSG_UpdateUstInfo();

        /*��ȡUSIM��ز���*/
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
        }
    }
    else
    {
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_CreateEFSmContent
 ��������  : ����SC Addr��TPDU����һ������,���Ÿ�ʽΪUSIM����EFSMS�ĸ�ʽ
 �������  : pstScAddr:�������ĵĵ�ַ
             pstRawData:TPDU������
             ucStatus:���ŵ�״̬
 �������  : pucContent:��������,USIM����EFSMS�ĸ�ʽ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2008��01��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��02��02��
    ��    ��   : s62952
    �޸�����   : ���ⵥ�ţ�AT2D08614
*****************************************************************************/
VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
)
{
    VOS_UINT32                          ulWriteSet = 0;

    PS_MEM_SET(pucContent, (VOS_CHAR)0xff, MN_MSG_EFSMS_LEN);
    *pucContent = ucStatus;
    if (pstScAddr->ucBcdLen > 0)
    {
        *(pucContent + 1 ) = (pstScAddr->ucBcdLen + 1);
        *(pucContent + 2 ) = pstScAddr->addrType;
        PS_MEM_CPY(pucContent + 3,pstScAddr->aucBcdNum ,pstScAddr->ucBcdLen);
        ulWriteSet = 1 + pstScAddr->ucBcdLen + 2;
    }
    else
    {
        *(pucContent + 1 ) = 0;
        ulWriteSet = 1 + 1;
    }

    if (ulWriteSet >=  MN_MSG_EFSMS_LEN)
    {
        return;
    }
    if (pstRawData->ulLen > (MN_MSG_EFSMS_LEN - ulWriteSet))
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,MN_MSG_EFSMS_LEN - ulWriteSet);
    }
    else
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,pstRawData->ulLen);
    }
}

/*****************************************************************************
 �� �� ��  : MSG_DecodeScAddress
 ��������  : ����RP-OA���ݽṹ����ɶ�Ӧ��BCD�����ݽṹ
             Refer to 24011 8.2.5.1
 �������  : RP��ĵ�ַ��Refer to 24011 8.2.5.1
 �������  : pstAsciiAddr MN_MSG_ASCII_ADDR_STRU�ṹ��ʾ�ĵ�ַ
             pulLen RP-OA RP-DA������Ϣ��ռ��OCTET�ĸ���
 �� �� ֵ  : ������ MN_ERR_NO_ERROR����ɹ�
                      ����           ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��09��26��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ

*****************************************************************************/
VOS_UINT32 MSG_DecodeScAddress(
    const VOS_UINT8                     *pucAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;

    if ((VOS_NULL_PTR == pucAddr)
     || (VOS_NULL_PTR == pstBcdAddr)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_DecodeScAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_MSG_DecodeAddress(pucAddr, VOS_TRUE, &stAsciiAddr, pulLen);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        pstBcdAddr->ucBcdLen = (VOS_UINT8)(stAsciiAddr.ulLen + 1)/2;
        /* ����Э��23040 9.1.2.5 ��ַ�������ʽ������ʾ
            bit7   bit6    -   bit4             bit3    -   bit0
             1      type of number      Numbering-plan-identification */
        pstBcdAddr->addrType = 0x80;
        pstBcdAddr->addrType |= (stAsciiAddr.enNumPlan & 0x0f);
        pstBcdAddr->addrType |= (VOS_UINT8)((stAsciiAddr.enNumType << 4) & 0x70);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
        ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)stAsciiAddr.aucAsciiNum,
                                    pstBcdAddr->aucBcdNum,
                                    &pstBcdAddr->ucBcdLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : MSG_GetTpduLen
 ��������  : ��ȡ����/��������/����״̬�����TPDU���ȣ��������������Ĳ���
 �������  : pstTsDataInfo   - ���ŵ�TEXT��ʽ���ݽṹָ��
 �������  : pulLen:����/��������/����״̬�����TPDU����
 �� �� ֵ  : MN_ERR_NO_ERROR:��ȡ�ɹ�
             ����:��ȡʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��03��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MSG_GetTpduLen(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    VOS_UINT32                          *pulLen
)
{
    MN_MSG_RAW_TS_DATA_STRU             *pstTmpRawData;
    VOS_UINT32                          ulRet;

    pstTmpRawData = (MN_MSG_RAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_RAW_TS_DATA_STRU));
    if (VOS_NULL_PTR == pstTmpRawData)
    {
        MN_ERR_LOG("MSG_GetTpduLen: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstTmpRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_GetTpduLen: Fail to encode msg.");
    }
    else
    {
        *pulLen = pstTmpRawData->ulLen;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpRawData);
    return ulRet;
}

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
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulScaLen;
    VOS_UINT8                           ucFo;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    VOS_UINT8                           ucSmStatus;
    MN_MSG_TPDU_TYPE_ENUM_U8            aucMtiMapTpduType[4] = {MN_MSG_TPDU_DELIVER,
                                                                MN_MSG_TPDU_SUBMIT,
                                                                MN_MSG_TPDU_COMMAND,
                                                                MN_MSG_TPDU_MAX};

    *pucStatus = *pucContent;
    if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
    {
        return MN_ERR_CLASS_SMS_EMPTY_REC;
    }
    ulRet = MSG_DecodeScAddress((pucContent + 1), pstScAddr, &ulScaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid SC address.");
        return ulRet;
    }

    ucFo = *(pucContent + (1 + ulScaLen));
    pstRawData->enTpduType = aucMtiMapTpduType[(ucFo & 0x03)];
    if (MN_MSG_TPDU_COMMAND == pstRawData->enTpduType)
    {
         /*��������Ͷ���״̬�����TP-MTI��Ϊ4������ͨ��SMS�ķ���״̬��ȷ���Ƿ�Ϊ����״̬����*/
         ucSmStatus = ((*pucStatus)& EF_SMS_STATUS_MO_SEND_TO_NT);
         if (EF_SMS_STATUS_MO_SEND_TO_NT != ucSmStatus)
         {
            pstRawData->enTpduType = MN_MSG_TPDU_STARPT;
         }
    }

    if (MN_MSG_TPDU_MAX == pstRawData->enTpduType)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid TPDU type.");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    pstRawData->ulLen = MN_MSG_EFSMS_LEN - (1 + ulScaLen);
    PS_MEM_CPY(pstRawData->aucData,
               (pucContent + (1 + ulScaLen)),
               pstRawData->ulLen);

    while (0 != pstRawData->ulLen)
    {
        if (MN_MSG_USIM_FILL_BYTE == pstRawData->aucData[pstRawData->ulLen - 1])
        {
            pstRawData->ulLen--;
        }
        else
        {
            break;
        }
    }

    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        MN_ERR_LOG("MN_MSG_ParseEFSmContent: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    ulRet = MN_MSG_Decode(pstRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to decode message.");
        return ulRet;
    }

    /*��ȡ��Ϣ����ʵ���Ƚ�ȡ�����ֶ�*/
    ulRet = MSG_GetTpduLen(pstTsDataInfo, &pstRawData->ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to get message length.");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
    return ulRet;
}

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
)
{
    if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & 0x07))
    {
        *penStatus = MN_MSG_STATUS_MO_NOT_SENT;
    }
    else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & 0x05))
    {
        *penStatus = MN_MSG_STATUS_MO_SENT;
    }
    else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & 0x03))
    {
        *penStatus = MN_MSG_STATUS_MT_NOT_READ;
    }
    else if (EF_SMS_STATUS_MT_READ == (ucStatus & 0x01))
    {
        *penStatus = MN_MSG_STATUS_MT_READ;
    }
    else
    {
        *penStatus = MN_MSG_STATUS_MAX;
    }
}

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
)
{
    if (MN_MSG_STATUS_MT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_READ;
    }
    else if (MN_MSG_STATUS_MT_NOT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_TO_BE_READ;
    }
    else if (MN_MSG_STATUS_MO_NOT_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_TO_BE_SEND;
    }
    else if (MN_MSG_STATUS_MO_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_SEND_TO_NT;
    }
    else
    {
        *pucStatus = EF_SMS_STATUS_FREE_SPACE;
    }
}

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
)
{
    PS_MEM_SET(pstDeliverEvt,0X00,sizeof(MN_MSG_DELIVER_EVT_INFO_STRU));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stScAddr,
               pstScAddr,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stScAddr));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stTsRawData,
               pstRawData,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stTsRawData));
    pstDeliverEvt->enMemStore = pstCfgParm->enSmMemStore;
    pstDeliverEvt->enRcvSmAct = pstCfgParm->enRcvSmAct;
}

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
MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID)
{
    return f_tMsgOpId++;
}

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
)
{
    if (ulInedx >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }
    f_bNeedSendUsim[ulInedx] = bUpdateStatus;
}

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
)
{
    *pulRealRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
    PS_MEM_CPY(pbNeedSendUsim,f_bNeedSendUsim,sizeof(VOS_BOOL)*MN_MSG_MAX_USIM_SMS_NUM);
}

/***********************************************************************
�� �� ��  : MN_MSG_CheckMemFull
��������  : �ж϶��Ŵ洢�ռ��Ƿ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE      �洢�ռ���
            ����        �洢�ռ�δ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : f62575
    �޸�����   : DTS2012111201995 �����ɺ���
  2.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
************************************************************************/
LOCAL VOS_UINT32 MN_MSG_CheckMemFull(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bUnavailableFlag;
    VOS_BOOL                            bSmUnavailableFlag;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;

    MN_INFO_LOG("MN_MSG_CheckMemFull: step into function.");

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    /* ��ȡ�û��Ķ��Ž��մ洢���� */
    MN_MSG_GetCurCfgParm(&stCfgParm);

    /* ���û����õĶ��Ŵ洢��ʽΪ��MODEM�洢������APP���Ž��չ����Ƿ���� */
    if (MN_MSG_RCVMSG_ACT_STORE != stCfgParm.enRcvSmAct)
    {
        ulRet = MN_MSG_AppStorageUnavailable(stCfgParm.enRcvSmAct,
                                            stCfgParm.enAppMemStatus,
                                            &bUnavailableFlag);
    }
    /* ���û����õĶ��Ŵ洢��ʽΪMODEM�洢�������û����õĴ洢�����Ƿ���� */
    else
    {
        ulRet = MN_MSG_UeStorageUnavailable(stCfgParm.enSmMemStore, &bUnavailableFlag);
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    ulRet = MN_MSG_UeStorageUnavailable(MN_MSG_MEM_STORE_SIM, &bSmUnavailableFlag);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    /* �����û�ָ���洢�ռ�����(U)SIM��������·��ض��Ŵ洢�ռ��� */
    if ((VOS_TRUE == bUnavailableFlag)
     && (VOS_TRUE == bSmUnavailableFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
*  Prototype       : MN_MSG_FailToWriteEfsms
*  Description     : ������������Ķ���дSIM����EFSMS�ļ�ʧ�ܺ�,MS��Э��Ҫ��ظ�����RP-ERROR���޸�EFSMSS�ļ���
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
   2.��    ��   : 2011��3��21��
     ��    ��   : ��ӳ��/f62575
     �޸�����   : DTS2011031800199����������洢��������SM��û�ж�ME�洢�����ʾ����
   3.��    ��   : 2012��11��08��
     ��    ��   : f62575
     �޸�����   : DTS2012111201995 �� ɾ������ucClassType������ԭ��ֵ���£�
   4.��    ��   : 2012��12��08��
     ��    ��   : f62575
     �޸�����   : DTS2012120608883 �� USIM���洢����ʱ�ն���DCM��֧ҲҪ�޸�EFSMSS�������־
*****************************************************************************/
VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
)
{
    VOS_UINT32                          ulRet;
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;

    /* ����Э��51010 34.2.5.3 SIM���洢�����쳣�ظ�����ԭ��ֵ9240��UE����ͬ
       SM�洢���� */
    if ((MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL != enFailCause)
     && (MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM != enFailCause))
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        return;
    }

    /* �˴��Ƿ���Ҫ�жϴ�ȷ�� */
    if (MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL == enFailCause)
    {
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportMemExceed(bcOpId, enMemStore);
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        enTpCause = MN_MSG_TP_CAUSE_SIM_FULL;
    }
    else
    {
        enTpCause = MN_MSG_TP_CAUSE_MEMORY_FULL;
    }

     /*The MS shall return a "protocol error, unspecified" error message
    (see 3GPP TS 24.011 [6]) if the short message cannot be stored in the
    (U)SIM and there is other short message storage available at the MS.
    If all the short message storage at the MS is already in use, the MS
    shall return "memory capacity exceeded". */
    ulRet = MN_MSG_CheckMemFull();
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_MEMORY_EXCEEDED,
                                enTpCause);

        MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

    }
    else
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                enTpCause);

        enMtCustomize       = MN_MSG_MT_CUSTOMIZE_NONE;
        MN_MSG_GetMtCustomizeInfo(&enMtCustomize);
        if (MN_MSG_MT_CUSTOMIZE_DCM == enMtCustomize)
        {
            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);
        }
    }

    return;
}

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
    MN_MSG_SEND_FAIL_FLAG_U8            enSendFailFlag
)
{
    f_enMsgSendFailFlag = enSendFailFlag;
}

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
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID)
{
    return f_enMsgSendFailFlag;
}

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
  2.��    ��   : 2012��01��04��
    ��    ��   : f62575
    �޸�����   : DTS2013010400027, ֧��GCF���������Զ�ʶ��
  3.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿڵ���
*****************************************************************************/
VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
)
{
    VOS_UINT32                          bTestCard;

#if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucDisableMoRetry)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
        return;
    }
#endif

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
    }
    else
    {
        PS_MEM_CPY(pstRetryInfo, &f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    }

    return;
}

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
  2.��    ��   : 2013��07��11��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg)
{
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    PS_MEM_CPY(&f_stMsgRpErrInfo, pstMsg, sizeof(f_stMsgRpErrInfo));
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
}

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
  2.��    ��   : 2013��07��11��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstRpErrInfo)
{
    PS_MEM_CPY(pstRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));
}

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
  2.��    ��   : 2012��01��04��
    ��    ��   : f62575
    �޸�����   : DTS2013010400027, ֧��GCF���������Զ�ʶ��
  3.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿڵ���
*****************************************************************************/
MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID)
{
    VOS_UINT32                          bTestCard;

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        return MN_MSG_CLASS0_VIVO;
    }
    else
    {
        return g_enMsgClass0Tailor;
    }
}

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
VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor)
{
    g_enMsgClass0Tailor = enClass0Tailor;
}

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
)
{
    if (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }


    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }

    return enHopeDomain;
}

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
)
{
    *penPid = f_stMsgMtEntity.enPid;
    PS_MEM_CPY(pstDcs, &f_stMsgMtEntity.stDcs, sizeof(f_stMsgMtEntity.stDcs));
}

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
)
{
    f_stMsgMtEntity.enPid = enPid;
    PS_MEM_CPY(&f_stMsgMtEntity.stDcs, &stDcs, sizeof(f_stMsgMtEntity.stDcs));
}

/*****************************************************************************
 �� �� ��  : MSG_UpdateUsimForList
 ��������  : LIST����ʱ�����USIM�ж���״̬
 �������  : clientId     -   �ϱ��ͻ��˿ں�
             ucChangeNum  -   ����ĸ���
             enMemStore   -   ��ǰ�洢��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MSG_UpdateUsimForList(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT8                           ucChangeNum,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            MN_OPERATION_ID_T                   bcOpId;
#endif

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_LIST,ucChangeNum);
    }
    else
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        /*�㲥�ϱ�NVIM�ж����ѷ����˸ı�*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
#endif
    }
}

/*lint -e438 -e830*/

/*****************************************************************************
 �� �� ��  : MN_MSG_RptMsg
 ��������  : �ϱ��������ݸ�APPģ��
 �������  : clientId         - �ϱ�Client
             opId             - �ϱ�OpId
             ucListStatus     - �б�״̬
             ulLeftReportNum  - ʣ���ϱ�����
             pstList           - �б�����
             pstListRptEvt     - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��9��27��
     ��    ��   : w00167002
     �޸�����   : DTS2013092100149:ɾ��C��TASKDELAY������V9�͹���ʱ���ᵼ��
                   TASKDELAY��δ�����ѣ�����AT��Ϣû�лظ���
                   ɾ����ʱ��TI_MN_MSG_LIST_WAIT_APP_READY �޸�ΪAT�ֶ��ϱ���
                   ͬʱ��SMS���ϱ�ʣ���SMS.
*****************************************************************************/
VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucEventNum  = 0;
    VOS_UINT32                          ulCapality;
    static VOS_UINT32                   ulBeginIdx = 0;
    VOS_UINT8                           ucListStatus;
    static VOS_UINT8                    ucChangeNum = 0;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    /* ��ȡ���б����״̬ */
    ucListStatus = EF_SMS_STATUS_FREE_SPACE;
    if (MN_MSG_STATUS_NONE != pstList->enStatus)
    {
        MN_MSG_GetPsStatus(pstList->enStatus, &ucListStatus);
    }

    ulCapality = MN_MSG_GetSmCapacity(pstList->enMemStore);

    PS_MEM_CPY( &(pstListRptEvt->stReceivedListPara), pstList, sizeof(MN_MSG_LIST_PARM_STRU) );

    /* �������ϱ�����,�ﵽ�б����޺�������ʱ���˳� */
    for (; ulBeginIdx < ulCapality; ulBeginIdx++)
    {
        ulRet = MN_MSG_GetStatus(pstList->enMemStore,ulBeginIdx,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        if ((MN_MSG_STATUS_NONE == pstList->enStatus)
         || (ucListStatus == ucStatus))
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(pstList->enMemStore,ulBeginIdx,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            ulRet = MN_MSG_ParseEFSmContent(aucSmContent,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stScAddr,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stTsRawData,
                                            &ucStatus);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            MN_MSG_GetAppStatus(ucStatus,&pstListRptEvt->astSmInfo[ucEventNum].enStatus);
            pstListRptEvt->astSmInfo[ucEventNum].ulIndex = ulBeginIdx;
            ucEventNum++;

            if ((VOS_TRUE == pstList->bChangeFlag)
             && (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus))
            {
                ulRet = MSG_ChangeSmStatus(pstList->enMemStore,
                                           clientId,
                                           opId,
                                           MN_MSG_USIM_LIST,
                                           ulBeginIdx,
                                           aucSmContent,
                                           &ucChangeNum);

                if (MN_ERR_NO_ERROR == ulRet )
                {
                    ucChangeNum++;
                }
            }
        }

        if ((ulLeftReportNum != ucEventNum)
         && (MN_MSG_MAX_REPORT_EVENT_NUM != ucEventNum))
        {
            continue;
        }

        /* �б������ɺ�ֱ���ϱ�,����������ʱ���ȴ���ʱ����ʱ���ϱ� */
        if (ulLeftReportNum == ucEventNum)
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_TRUE;
            pstListRptEvt->ulReportNum = ulLeftReportNum;
            ulBeginIdx = 0;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
            if (ucChangeNum > 0)
            {
                /* ����USIM�ļ��ж���״̬ */
                if (MN_MSG_MEM_STORE_SIM == pstList->enMemStore)
                {
                    MSG_UpdateUsimForList(clientId,ucChangeNum,pstList->enMemStore);
                }
                #if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
                else if (MN_MSG_MEM_STORE_NV == pstList->enMemStore)
                {
                    /*�㲥�ϱ�NVIM�ж����ѷ����˸ı�*/
                    bcOpId = MN_MSG_GetBCopId();
                    MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
                }
                #endif
                else
                {
                }
            }
            ucChangeNum = 0;
        }
        else
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_FALSE;
            pstListRptEvt->ulReportNum = MN_MSG_MAX_REPORT_EVENT_NUM;
            ulLeftReportNum = ulLeftReportNum - MN_MSG_MAX_REPORT_EVENT_NUM;
            ucEventNum = 0;
            /* �˴�+1��ԭ��Ϊ,��index�����ѱ��б�,���б���һ������ */
            ulBeginIdx++;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);


            MN_MSG_UpdateListInfo(clientId,opId,ulLeftReportNum,pstList);
        }
        break;
    }

}
/*lint +e438 +e830*/

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
VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID )
{
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvPathEvt;

    f_stMsgCfgParm.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enCbmMemStore    = MN_MSG_MEM_STORE_NONE;

    stRcvPathEvt.enRcvSmAct         = f_stMsgCfgParm.enRcvSmAct;
    stRcvPathEvt.enSmMemStore       = f_stMsgCfgParm.enSmMemStore;
    stRcvPathEvt.enRcvStaRptAct     = f_stMsgCfgParm.enRcvStaRptAct;
    stRcvPathEvt.enStaRptMemStore   = f_stMsgCfgParm.enStaRptMemStore;
    stRcvPathEvt.enCbmMemStore      = f_stMsgCfgParm.enCbmMemStore;

    bcOpId = MN_MSG_GetBCopId();
    MN_MSG_ReportRcvPathEvent(MN_CLIENT_ALL, bcOpId, VOS_TRUE, &stRcvPathEvt, MN_MSG_EVT_RCVMSG_PATH_CHANGED);

}

/*****************************************************************************
 �� �� ��  : MN_MSG_OutputSmsMoFailureInfo
 ��������  : ���ŷ��������Ϣ�������쳣�¼���¼
 �������  : TAF_MSG_ERROR_ENUM_UINT32 enErrorCode RP-ERROR�Ĵ���ԭ��
 �������  : NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
                                 ���ŷ���ʧ�ܵ�ֱ�������Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��9��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_VOID MN_MSG_OutputSmsMoFailureInfo(
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode,
    NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
)
{
    /* ��ȡ���ŷ�����صķ������� */
    pstSmsMo->stUstInfo.bEfSmssFlag     = f_stEfUstInfo.bEfSmssFlag;
    pstSmsMo->stUstInfo.bEfSmsFlag      = f_stEfUstInfo.bEfSmsFlag;
    pstSmsMo->stUstInfo.bEfSmsrFlag     = f_stEfUstInfo.bEfSmsrFlag;
    pstSmsMo->stUstInfo.bEfSmspFlag     = f_stEfUstInfo.bEfSmspFlag;
    pstSmsMo->stUstInfo.bMoSmsCtrlFlag  = f_stEfUstInfo.bMoSmsCtrlFlag;

    /* ��ȡ����ģ���ʼ��״̬���� */
    PS_MEM_CPY(&pstSmsMo->stMsgStatus,
               &f_stMsgUsimStatusInfo,
               sizeof(pstSmsMo->stMsgStatus));

    /* ��ȡĿ�ĺ���Ͷ������ĺ��� */
    MN_MSG_GetAddressFromSubmit(f_stMsgMoEntity.aucRpDataInfo,
                                f_stMsgMoEntity.ucRpDataLen,
                                &pstSmsMo->stScAddr,
                                &pstSmsMo->stDestAddr);

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstSmsMo->ulMoFailCause = enErrorCode;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_ReadMsgInFlashByIndex
 ��������  : ��������ȡFlash��һ������Ϣ
 �������  : VOS_UINT32   ulIndex ����ֵ
 �������  : VOS_UINT8    *pucSmContent ��ȡ��Buffer

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��01��24��
    ��    ��   : ��ë/W00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                	*fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*�ж϶����ļ��Ƿ��*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_ReadFlashByIndex: SmsFile Not Exit.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_NOTEXIST_FILE;
    }

    fp = gfpSmsFlash;

    /*��ȡ�ļ���С*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if (((ulIndex + 1) * MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*��λ������λ��*/
    lRst = mdrv_file_seek(fp, (VOS_INT32)(ulIndex * MN_MSG_EFSMS_LEN), SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*���ļ�*/
    /* ����ӿ��޸ģ������˲��� */
    lRst = mdrv_file_read(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if ((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:read error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_READ_FILE;
    }

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 �� �� ��  : MN_MSG_WriteMsgInFlashByIndex
 ��������  : ��������Flashдһ������Ϣ
 �������  : VOS_UINT32   ulIndex ����ֵ
 �������  : VOS_UINT8    *pucSmContent Ҫд����ŵ�Buffer

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��01��24��
    ��    ��   : ��ë/W00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��03��04��
    ��    ��   : f62575
    �޸�����   : DTS2013091009786 ֧��ͨ����Ʒ��̬�Ͱ汾����FLASH�ļ���Ŀ¼
*****************************************************************************/
VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                *fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*��������ļ������ڣ���Ҫ�������ļ�*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        /*�����ļ�*/
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"wb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Create SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_CREATE_FILE;
        }

        /*��д��ʽ���ļ�*/
        (VOS_VOID)mdrv_file_close(gfpSmsFlash);
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
        }
    }

    fp = gfpSmsFlash;

    /*��ȡ�ļ���С*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if ((ulIndex*MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*��λ������λ��*/
    lRst = mdrv_file_seek(fp,(VOS_INT32)(ulIndex*MN_MSG_EFSMS_LEN),SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*д�ļ�*/
    /* ����ӿ��޸ģ������˲��� */
    lRst = mdrv_file_write(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:write error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_WRITE_FILE;
    }

    (VOS_VOID)mdrv_file_close(gfpSmsFlash);

    gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetSmsServicePara
 ��������  : ��ȡ����ҵ�����
 �������  : ��
 �������  : MN_MSG_CONFIG_PARM_STRU  *pstMsgCfgParm  ����ҵ�����
             MN_MSG_ME_STORAGE_STATUS_UINT8     *penMeStorageEnable MEʹ��״̬
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��11��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��3��21��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011031800199��֧��ME��������������
  3.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ��DTS2011062201273 MO SMS CONTROL
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  5.��    ��   : 2013��05��20��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_VOID MN_MSG_GetSmsServicePara(
    MN_MSG_CONFIG_PARM_STRU             *pstMsgCfgParm,
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 *penMeStorageEnable
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;
    /* ���Ž��մ洢���ʱ�����NV�����ļ���ʹ�ܱ�־
       VOS_TRUE        ���Ž��մ洢���ʱ�����NV�����ļ�
       VOS_FALSE       ���Ž��մ洢���ʲ�������NV�����ļ���ÿ���ϵ��ָ�ΪSM�洢 */
    VOS_BOOL                            bSmMemEnable;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;

    MN_MSG_NVIM_MO_SMS_CTRL_STRU        stMnMsgSrvPara;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));
    PS_MEM_SET(&stMnMsgSrvPara, 0x00, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_BUTT;
    stMeStorageParm.usMeStorageNum    = 0;


    MN_MSG_InitSmsServiceData(pstMsgCfgParm);
    *penMeStorageEnable = MN_MSG_ME_STORAGE_DISABLE;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read Service Parm From Nvim Failed");
        return;
    }

    pstMsgCfgParm->enAppMemStatus = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET];
    bSmMemEnable                  = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET];
    ulRet = NV_Read(en_NV_Item_Sms_Me_Storage_Info, &stMeStorageParm, sizeof(stMeStorageParm));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara: Read en_NV_Item_Sms_MeStorageEnable Failed");
        stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
        f_usMsgNvimSmsCurReNum = 0;
        return;
    }

    if (MN_MSG_ME_STORAGE_ENABLE == stMeStorageParm.enMeStorageStatus)
    {
        if (VOS_TRUE == bSmMemEnable)
        {
            pstMsgCfgParm->enSmMemStore = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET];
        }

        if (stMeStorageParm.usMeStorageNum > MN_MSG_MAX_NVIM_SMS_REC_NUM)
        {
            f_usMsgNvimSmsCurReNum = MN_MSG_MAX_NVIM_SMS_REC_NUM;
        }
        else
        {
            f_usMsgNvimSmsCurReNum = stMeStorageParm.usMeStorageNum;
        }
    }
    else
    {
        f_usMsgNvimSmsCurReNum = 0;
    }

    *penMeStorageEnable = stMeStorageParm.enMeStorageStatus;

    (VOS_VOID)NV_GetLength(en_NV_Item_MO_SMS_CONTROL_FEATURE, &ulLength);
    ulRet = NV_Read(en_NV_Item_MO_SMS_CONTROL_FEATURE, &stMnMsgSrvPara, ulLength);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read MO_SMS_CONTROL_FEATURE From Nvim Failed");
        f_stMsgMoSmsCtrlInfo.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    PS_MEM_CPY(&f_stMsgMoSmsCtrlInfo, &stMnMsgSrvPara, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetMoSmsCtrlFlag
 ��������  : ��ȡMO SMS CONTROL���Եļ����־
 �������  : ��
 �������  : VOS_UINT8 *pucMoSmsCtrlFlag  MO SMS CONTROL���Եļ����־
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��22��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_GetMoSmsCtrlFlag(
    VOS_UINT8                           *pucMoSmsCtrlFlag
)
{
    *pucMoSmsCtrlFlag = f_stMsgMoSmsCtrlInfo.ucActFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMoSmsCtrlFlag
 ��������  : ����MO SMS CONTROL���Եļ����־
 �������  : ��
 �������  : VOS_UINT8 ucMoSmsCtrlFlag  MO SMS CONTROL���Եļ����־
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��22��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
*****************************************************************************/
VOS_VOID MN_MSG_UpdateMoSmsCtrlFlag(
    VOS_UINT8                           ucMoSmsCtrlFlag
)
{
    f_stMsgMoSmsCtrlInfo.ucActFlg = ucMoSmsCtrlFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : MN_MGS_UpdateSmsCapability
 ��������  : ����SMS�洢���ʵ�����
 �������  : MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore �洢��������
             VOS_UINT32                          ulNum        ָ���洢���ʵ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MGS_UpdateSmsCapability(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_UINT32                          ulNum
)
{
    if (MN_MSG_MEM_STORE_SIM == enSmMemStore)
    {
        f_stMsgEfSmsInfo.ucSmsRealRecNum = (VOS_UINT8)ulNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enSmMemStore)
    {
        f_usMsgNvimSmsCurReNum = (VOS_UINT8)ulNum;
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetSpecificStatusMoEntity
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
)
{
    VOS_UINT32                          ulTotal;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    *pbBufferEntity = VOS_FALSE;
    *pulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_GetMoEntity(pstMoEntity);
    if (enMoStatus == pstMoEntity->enSmaMoState)
    {
        return MN_ERR_NO_ERROR;
    }

    ulTotal = MN_MSG_GetMoBufferCap();
    for(ulLoop = 0; ulLoop < ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        if (enMoStatus == pstMoBuffer->stMoInfo.enSmaMoState)
        {
            *pbBufferEntity = VOS_TRUE;
            *pulIndex       = ulLoop;
            PS_MEM_CPY(pstMoEntity, &pstMoBuffer->stMoInfo, sizeof(pstMoBuffer->stMoInfo));
            return MN_ERR_NO_ERROR;
        }
    }

    return MN_ERR_UNSPECIFIED;
}

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
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_CreateMoInfo(pstMoEntity);
        return;
    }

    MN_MSG_SaveStoreMsg(ulIndex, pstMoEntity, aucEfSmContent);
    return;
}

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
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_UpdateSmaMoState(enMoStatus);
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->stMoInfo.enSmaMoState = enMoStatus;
}

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
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_DestroyMoInfo();
        return;
    }

    MN_MSG_FreeStoreMsg(ulIndex);

    return;
}

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
  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  3.��    ��   : 2013��8��8��
    ��    ��   : y00245242
    �޸�����   : ��ʼ��stTotalMsg����
*****************************************************************************/
VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    NAS_MN_NVIM_TOTAL_MSG_STRU          stTotalMsg;

    if (VOS_NULL_PTR != f_stMsgMoBuffer.pstMoBuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, f_stMsgMoBuffer.pstMoBuffer);
        f_stMsgMoBuffer.ulTotal = 0;
    }

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-8, begin */
    stTotalMsg.ulTotalMsg = 0;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-8-8, end */

    ulRet = NV_Read(en_NV_Item_NVIM_SMS_BUFFER_CAPABILITY,
                    &stTotalMsg,
                    sizeof(stTotalMsg));

    f_stMsgMoBuffer.ulTotal = stTotalMsg.ulTotalMsg;

    if (NV_OK != ulRet)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    if (0 == f_stMsgMoBuffer.ulTotal)
    {
        return;
    }

    f_stMsgMoBuffer.pstMoBuffer = (MN_MSG_STORE_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                            sizeof(MN_MSG_STORE_MSG_STRU) * f_stMsgMoBuffer.ulTotal);
    if (VOS_NULL_PTR == f_stMsgMoBuffer.pstMoBuffer)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        PS_MEM_SET(pstMoBuffer, 0, sizeof(MN_MSG_STORE_MSG_STRU));
    }

    return;
}

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
VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID)
{
    return f_stMsgMoBuffer.ulTotal;
}

/*****************************************************************************
 �� �� ��  : TAF_MSG_SetUsimStatus
 ��������  : ����SIM��״̬
 �������  : SIM��״̬
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
)
{
    f_stMsgUsimStatusInfo.ucUsimStatus = ucUsimStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_MSG_GetUsimStatus
 ��������  : ��ȡSIM��״̬
 �������  : ��
 �������  : ��
 ����ֵ    : SIM��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID)
{
    return f_stMsgUsimStatusInfo.ucUsimStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_MSG_UpdateMtRcvDomain
 ��������  : ���ն���ʱ������MTʵ��Ľ�����
 �������  : ������ 0:PS��1:CS��
 �������  : ��
 ����ֵ    : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
)
{
    if ( (MN_MSG_RCV_DOMAIN_CS != ucRcvDomain)
      && (MN_MSG_RCV_DOMAIN_PS != ucRcvDomain) )
    {
        f_stMsgMtEntity.enRcvDomain = MN_MSG_RCV_DOMAIN_BUTT;
    }
    else
    {
        f_stMsgMtEntity.enRcvDomain = ucRcvDomain;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MSG_GetMtRcvDomain
 ��������  : ��ȡMTʵ��Ľ�����
 �������  : ��
 �������  : ��
 ����ֵ    : ������ MN_MSG_RCV_DOMAIN_PS:PS��MN_MSG_RCV_DOMAIN_CS:CS��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID)
{
    return f_stMsgMtEntity.enRcvDomain;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

