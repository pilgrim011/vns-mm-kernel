/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaCtx.h
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��07��9��
  ����޸�   :
  ��������   : TafMmaCtx.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��07��9��
    ��    ��   : W00176964
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _TAF_MMA_CTX_H_
#define _TAF_MMA_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "TafAppMma.h"
#include  "TafFsm.h"
#include  "TafMmaTimerMgmt.h"
#include  "TafSdcCtx.h"
#include  "MmaUphyInterface.h"

//#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_MAX_MSG_BUFFER_LEN                      (500)                  /* �������󳤶� */
#define TAF_MMA_MAX_MSG_QUEUE_NUM                       (4)                     /* ��󻺴�ĸ��� */
#define TAF_MMA_MAX_STACK_DEPTH                         (4)                     /* ״̬��ջ����� */
#define TAF_MMA_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* ��EventType�л�ȡMsgName     */
#define TAF_MMA_MAX_MSG_QUEUE_SIZE                      (11)                    /* �ڲ���Ϣ�������ĳ��� */

/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
#define TAF_MMA_MAX_OPER_NUM                            (5)
/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

#define TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM           (4)                     /* ��ǰ��Ҫ���Ϳ��ػ�����ģ��������� */

#define TAF_MMA_WILDCARD_CDMAPN_VALUE                   (0xFFFF)
#define TAF_MMA_WILDCARD_EVDOPN_VALUE                   (0xFFFF)


typedef VOS_UINT16   TAF_MMA_SYS_CFG_OPER_TYPE;
#define  TAF_MMA_SYS_CFG_NONE_SET                           (0x0000) /*����Ϊ��*/
#define  TAF_MMA_SYS_CFG_ROAM_SET                           (0x0001) /*����������*/
#define  TAF_MMA_SYS_CFG_MODE_SET                           (0x0002) /*�����˽���ģʽ��������*/
#define  TAF_MMA_SYS_CFG_BAND_SET                           (0x0004) /*������Ƶ��*/
#define  TAF_MMA_SYS_CFG_CS_DETACH_SET                      (0x0010) /*���������˷�������Ҫ����CS Detach*/
#define  TAF_MMA_SYS_CFG_PS_DETACH_SET                      (0x0020) /*���������˷�������Ҫ����PS Detach*/
#define  TAF_MMA_SYS_CFG_CS_ATTACH_SET                      (0x0040) /*���������˷�������Ҫ����CS Attach*/
#define  TAF_MMA_SYS_CFG_PS_ATTACH_SET                      (0x0080) /*���������˷�������Ҫ����PS Attach*/


#define  TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_ATTACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_ATTACH_SET)

#define  TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_DETACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_DETACH_SET)

/* ��Ҫ����syscfg���� */
#define  TAF_MMA_SYS_CFG_SET_REQ_REQUIRED                   (TAF_MMA_SYS_CFG_ROAM_SET  \
                                                            |TAF_MMA_SYS_CFG_MODE_SET  \
                                                            |TAF_MMA_SYS_CFG_BAND_SET)

#define TAF_MMA_SYS_CFG_RAT_NONE_SET                        (0x00)
#define TAF_MMA_SYS_CFG_RAT_G_SET                           (0x01)
#define TAF_MMA_SYS_CFG_RAT_W_SET                           (0x02)
#define TAF_MMA_SYS_CFG_RAT_1X_SET                          (0x04)
#define TAF_MMA_SYS_CFG_RAT_DO_SET                          (0x08)

#define TAF_MMA_SYS_CFG_RAT_C_SET                           (TAF_MMA_SYS_CFG_RAT_1X_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_DO_SET)

#define TAF_MMA_SYS_CFG_RAT_GU_SET                          (TAF_MMA_SYS_CFG_RAT_G_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_W_SET)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_MMA_MSG_CACHE_PRIO_ENUM
 �ṹ˵��  : MMA������Ϣ�����ȼ�ö��
 1.��    ��   : 2013��7��20��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
enum TAF_MMA_MSG_CACHE_PRIO_ENUM
{
    TAF_MMA_MSG_CACHE_PRIO_HIGH              ,                           /* �����ȼ����� */
    TAF_MMA_MSG_CACHE_PRIO_MIDDLE            ,                           /* �����ȼ����� */
    TAF_MMA_MSG_CACHE_PRIO_LOW               ,                           /* �����ȼ����� */

    TAF_MMA_MSG_CACHE_PRIO_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_MMA_FSM_ID_ENUM
 ö��˵��  : ״̬��IDö�ٶ���
  1.��    ��   : 2013��7��9��
    ��    ��   : w00176964
    �޸�����   : �½�
  1.��    ��   : 2015��02��03��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ������IMS SWITCH״̬��
*****************************************************************************/
enum TAF_MMA_FSM_ID_ENUM
{
    TAF_MMA_FSM_MAIN                                            = 0X00,

    TAF_MMA_FSM_PHONE_MODE                                      = 0X01,

    TAF_MMA_FSM_IMS_SWITCH                                      = 0X02,
    TAF_MMA_FSM_SYS_CFG                                         =0x03,

    TAF_MMA_FSM_BUTT

};
typedef VOS_UINT32 TAF_MMA_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_MMA_INIT_CTX_TYPE_ENUM
 �ṹ˵��  : ��ʼ��MMA CTX����
 1.��    ��   : 2013��7��9��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
enum TAF_MMA_INIT_CTX_TYPE_ENUM
{
    TAF_MMA_INIT_CTX_STARTUP                    = 0,
    TAF_MMA_INIT_CTX_POWEROFF                   = 1,
    TAF_MMA_INIT_CTX_BUTT
};
typedef VOS_UINT8 TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8;

/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
/*****************************************************************************
 ö����    : TAF_MMA_OPER_TYPE_ENUM_UINT32
 �ṹ˵��  : ��ʼ��MMA CTX����
 1.��    ��   : 2013��7��9��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
enum TAF_MMA_OPER_TYPE_ENUM
{
    /* Modified by b00269685 for L-C��������Ŀ, 2014-2-14, begin */

    TAF_MMA_OPER_SYS_CFG_REQ                    = 0,
    TAF_MMA_OPER_ACQ_REQ                        = 1,
    TAF_MMA_OPER_REG_REQ                        = 2,
    TAF_MMA_OPER_POWER_SAVE_REQ                 = 3,
    TAF_MMA_OPER_DETACH_REQ                     = 4,
    TAF_MMA_OPER_CFPLMN_SET_REQ                 = 5,
    TAF_MMA_OPER_CFPLMN_QRY_REQ                 = 6,

    TAF_MMA_OPER_PREF_PLMN_SET_REQ              = 7,
    TAF_MMA_OPER_PREF_PLMN_QUERY_REQ            = 8,
    TAF_MMA_OPER_PREF_PLMN_TEST_REQ             = 9,
    TAF_MMA_OPER_CDMACSQ_SET_REQ                = 10,
    TAF_MMA_OPER_PLMN_LIST_REQ                  = 11,
    TAF_MMA_OPER_EONS_UCS2_REQ                  = 12,
    TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ            = 13,
    TAF_MMA_OPER_PLMN_SPEC_SEL_REQ              = 14,
    TAF_MMA_OPER_PLMN_LIST_ABORT_REQ            = 15,

    TAF_MMA_OPER_GETSTA_QUERY_REQ               = 16,
    TAF_MMA_OPER_CHVER_QUERY_REQ                = 17,

    TAF_MMA_OPER_SET_CSIDLIST_REQ               = 18,

    TAF_MMA_OPER_HDR_CSQ_SET_REQ                = 19,
    TAF_MMA_OPER_CSG_LIST_SEARCH_REQ            = 20,
    TAF_MMA_OPER_CSG_LIST_ABORT_REQ             = 21,

    TAF_MMA_OPER_BUTT

    /* Modified by b00269685 for L-C��������Ŀ, 2014-2-14, end */
};
typedef VOS_UINT32 TAF_MMA_OPER_TYPE_ENUM_UINT32;

/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

/*****************************************************************************
 ö����    : TAF_MMA_READ_SIM_FILES_CNF_ENUM
 �ṹ˵��  : ���ڱ�Ƕ�ȡUSIM�ļ��Ļظ���Ϣ
1.��    ��   : 2015��3��13��
  ��    ��   : z00161729
  �޸�����   : AT&T ֧��EONS�����޸�

*****************************************************************************/
enum  TAF_MMA_READ_SIM_FILES_CNF_ENUM
{
    TAF_MMA_READ_USIM_FILE_FLG_NULL                         = 0x0,
    TAF_MMA_READ_USIM_PNN_FILE_ID_FLG                       = 0x1,
    TAF_MMA_READ_SIM_PNN_FILE_ID_FLG                        = 0x2,
    TAF_MMA_READ_USIM_OPL_FILE_ID_FLG                       = 0x4,
    TAF_MMA_READ_SIM_OPL_FILE_ID_FLG                        = 0x8,
    TAF_MMA_READ_USIM_SPN_FILE_ID_FLG                       = 0x10,
    TAF_MMA_READ_SIM_SPN_FILE_ID_FLG                        = 0x20,
    TAF_MMA_READ_CPHS_FILE_ID_FLG                           = 0x40,
    TAF_MMA_READ_SIM_SPDI_FILE_ID_FLG                       = 0x80,
    TAF_MMA_READ_USIM_SPDI_FILE_ID_FLG                      = 0x100,
    TAF_MMA_READ_CUSTOM_SRV_PROFILE_FILE_ID_FLG             = 0x200,
    TAF_MMA_READ_USIM_EFAD_FILE_ID_FLG                      = 0x400,
    TAF_MMA_READ_SIM_EFAD_FILE_ID_FLG                       = 0x800,
    TAF_MMA_READ_USIM_EFEHPLMN_FILE_ID_FLG                  = 0x1000,
    TAF_MMA_READ_ATTGSM_EFACTINGHPLMN_FILE_ID_FLG           = 0x2000,
    TAF_MMA_READ_CDMA_IMSIM_FILE_ID_FLG                     = 0x4000,
    TAF_MMA_READ_CSIM_IMSIM_FILE_ID_FLG                     = 0x8000,
    TAF_MMA_READ_CDMA_RUIMID_FILE_ID_FLG                    = 0x10000,
    TAF_MMA_READ_CSIM_RUIMID_FILE_ID_FLG                    = 0x20000,


    TAF_MMA_READ_USIM_FILE_CNF_BUTT
};

typedef VOS_UINT32 TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32;
/*****************************************************************************
 ö����    : TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM
 �ṹ˵��  : �ӳ��ϱ�CL�޷���״̬������
 1.��    ��   : 2015��01��07��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
enum TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM
{
    TAF_MMA_DELAY_CL_REPORT_TYPE_DO,
    TAF_MMA_DELAY_CL_REPORT_TYPE_DO_LTE,

    TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM_UINT8;


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
 �ṹ��    : TAF_MMA_ENTRY_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ҫ����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_MMA_MAX_MSG_BUFFER_LEN];
} TAF_MMA_ENTRY_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_PHONE_MODE_SET_ORDER_STRU
 �ṹ˵��  : ��¼���ײ��·�����������Ⱥ�˳��
              ����˵��:
              ������˳��ΪIMSA->CDMA->MSCC,��ôaulSwitchOnModuleID�д�ŵ�
              �Ⱥ�˳��ΪIMSA->CDMA->MSCC,������ܸ���Ϊ3,����IMSAģ�鷢�Ϳ��������ʱ��
              usSwitchOnIndex��ŵ�ֵΪ0��

              ������˳��ΪIMSA->MSCC;��ôaulSwitchOnModuleID�д�ŵײ��
              �Ⱥ�˳��ΪIMSA->MSCC,������ܸ���Ϊ2,����MSCCģ���Ϳ��������ʱ��
              usSwitchOnIndex��ŵ�ֵΪ1;

              ʹ�����½ṹ��MMA�����׵�����ײ����Ҫ��Ŀ���˳������

*****************************************************************************/
typedef struct
{
    VOS_UINT16      usNum;                                                      /* ���²㷢�Ϳ���������ܸ��� */
    VOS_UINT16      usIndex;                                                    /* ָ����Ҫ������Ӧģ��Ľ��뼼�����±� */
    VOS_UINT32      aulModuleID[TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM];         /* ������ÿ�����Ҫ�����ײ�ģ����Ⱥ�˳�� */
}TAF_MMA_PHONE_MODE_SET_ORDER_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_PHONE_MODE_CTX_STRU
 �ṹ˵��  : ģʽ����״̬��������
 1.��    ��   : 2013��7��9��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;       /* ���ػ��Ĵ���ԭ��ֵ */
    TAF_MMA_PHONE_MODE_SET_ORDER_STRU   stPhoneModeOrder;                    /* TAF MMA����˳����� */
}TAF_MMA_FSM_PHONE_MODE_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_SYSCFG_CTX_STRU
 �ṹ˵��  : ϵͳ����״̬��������
 1.��    ��   : 2015��4��9��
   ��    ��   : h00313353
   �޸�����   : ����
 2.��    ��   : 2015��12��3��
   ��    ��   : w00176964
   �޸�����   : DTS2015061601845:����ԭʼsyscfg�����Ĳ�������,�û�SYSCFGʧ��ʱ�����û�����
*****************************************************************************/
typedef struct
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;                             /* ��¼SYSCFG�Ĳ�������-ʵʱˢ�� */
    TAF_MMA_SYS_CFG_OPER_TYPE           usOrigOperType;                         /* ��¼SYSCFG������ԭʼ��������-���ı� */

    VOS_UINT8                           ucAttachOpId;                           /* ��¼attach����ʱ��OpId*/
    VOS_UINT8                           aucRsv[3];

    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
}TAF_MMA_FSM_SYS_CFG_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_EXTRA_CTX_UNION
 �ṹ˵��  : ״̬��״̬�����ṹ,״̬����������Ϣ
 1.��    ��   : 2013��7��13��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef union
{
    TAF_MMA_FSM_PHONE_MODE_CTX_STRU                         stPhoneModeCtx;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                            stSysCfgCtx;

}TAF_MMA_FSM_EXTRA_CTX_UNION;

/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2013��7��9��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                                /* L1״̬ */

    /* �����ϢMSGID������  */
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    /* ״̬������ */
    TAF_MMA_FSM_EXTRA_CTX_UNION         unFsmCtx;
}TAF_MMA_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_STACK_STRU
 �ṹ˵��  : ״̬��ջ�����ṹ
 1.��    ��   : 2013��7��13��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */
    VOS_UINT16                          usStackPopFlg;                          /* ��ǰջpop��־ */
    TAF_MMA_FSM_CTX_STRU                astFsmStack[TAF_MMA_MAX_STACK_DEPTH];   /* ״̬��ջ����� */
}TAF_MMA_FSM_STACK_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_CACH_MSG_INFO_STRU
 �ṹ˵��  : �������Ϣ����
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_MMA_ENTRY_MSG_STRU              stMsgEntry;     /* ����ľ�������   */
}TAF_MMA_CACH_MSG_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_MSG_QUEUE_STRU
 �ṹ˵��  : �������Ϣ����
 1.��    ��   : 2013��7��13��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_MMA_CACH_MSG_INFO_STRU          astMsgQueue[TAF_MMA_MAX_MSG_QUEUE_NUM]; /* MMA����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_MMA_MSG_QUEUE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_INTERNAL_MSG_BUF_STRU
 �ṹ˵��  : �ڲ���Ϣ���еĽṹ
 1.��    ��   : 2013��7��19��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* ��ϢID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[TAF_MMA_MAX_MSG_BUFFER_LEN];     /* ��Ϣ���� */
}TAF_MMA_INTERNAL_MSG_BUF_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_INTERNAL_MSG_QUEUE_STRU
 �ṹ˵��  : ����MMA�ڲ���Ϣ������
 1.��    ��   : 2013��7��19��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* TAF MMA�ڲ���Ϣ���� */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       astMmaMsgQueue[TAF_MMA_MAX_MSG_QUEUE_SIZE];

    /* ������Ϣ��ʱ����buff,����ֲ�����ʱֱ��ʹ�øÿռ�,Ϊ�˱��ⷢ���ڲ���Ϣʱ
    ռ�ýϴ��ջ�ռ� */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /* �ڲ���Ϣ������е�����βָ�� */
    VOS_UINT8                           ucTail;

    /* �ڲ���Ϣ������е�����ͷָ�� */
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} TAF_MMA_INTERNAL_MSG_QUEUE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_PHONE_MODE_CTRL_CTX_STRU
 �ṹ˵��  : �ֻ�ģʽ������Ϣ
 1.��    ��   : 2013��7��11��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulAutoInitPsFlg;                        /* �ϵ��Ƿ��ʼ��Э��ջ */
    VOS_UINT32                          ulAutoSwitchOnFlg;                      /* �ϵ��Ƿ��Զ�����(�����ڲ����������MSCC) */
}TAF_MMA_PHONE_MODE_CTRL_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_MAINTAIN_CTX_STRU
 �ṹ˵��  : MMA�����Ϣ�ṹ��
 1.��    ��   : 2013��9��4��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmaLogInfoFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_MAINTAIN_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU
 �ṹ˵��  : MMA����������ģ���ʼ����Ϣ
 1.��    ��   : 2014��3��12��
   ��    ��   : y00176023
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU;
/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
/*****************************************************************************
 �ṹ��    : TAF_MMA_OPER_CTX_STRU
 �ṹ˵��  : MMA���ñ������������
 1.��    ��   : 2014��2��17��
   ��    ��   : s00261364
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucUsedFlag;
    VOS_UINT8                           aucReserved[3];
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType;
    VOS_VOID                           *pPara;
} TAF_MMA_OPER_CTX_STRU;
/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

/*****************************************************************************
 �ṹ��    : TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG NV��ṹ
 1. ��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 2. ��    ��   : 2015��09��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /* ��ʱ�ϱ���ʱ��ʱ��,��λ:���� */
}TAF_MMA_GUL_DELAY_REPORT_SERVICE_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_CL_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : Cģ�ӳ��ϱ���ʱ�� NV��ṹ
 1. ��    ��   : 2015��09��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClDelayRptEnable;             /* CLģʽ�£���ʱ�ϱ����ܿ��أ�TRUEΪ�򿪣�FALSEΪ�ر� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulClRptSrvStaDelayTimerValue;   /* ��ʱ�ϱ�ʱ������λ:���� */
}TAF_MMA_CL_DELAY_REPORT_SERVICE_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_DELAY_SND_SERVICE_STATUS_STRU
 �ṹ˵��  : Cģ�ӳ��ϱ���ʱ�� NV��ṹ
 1. ��    ��   : 2016��01��06��
    ��    ��   : h00313353
    �޸�����   : DTS2016010508602
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucCLNoServiceDelayRptLen;                   /* CLģʽ�£���ʱ�ϱ��޷����ܿ��أ�0Ϊ�رգ�����ʱ��Ϊ�򿪣���λΪ�� */
    VOS_UINT8                               ucDoNoServiceDelayRptLen;                   /* CLģʽ�£�DO�޷����ӳ��ϱ��޷���Ķ�ʱ��ʱ����0Ϊ�رգ�����ʱ��Ϊ�򿪣���λΪ�� */
    TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM_UINT8 enDelayType;
    VOS_UINT8                               ucReserved;
}TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : �ӳ��ϱ���ʱ�� NV��ṹ����ΪGUL��CL
 1. ��    ��   : 2015��09��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18����
*****************************************************************************/
typedef struct
{
    TAF_MMA_GUL_DELAY_REPORT_SERVICE_STATUS_STRU            stGulDelayRptCtrlInfo;  /* GULģ�£���ʱ�ϱ����ܿ����� */
    TAF_MMA_CL_DELAY_REPORT_SERVICE_STATUS_STRU             stClDelayRptCtrlInfo;   /* CLģ�£���ʱ�ϱ����ܿ����� */
    TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU                    stCLNoServiceDelayRptInfo;  /* CLģʽ�£��ӳ��ϱ�DO��LTE�޷���Ķ�ʱ��ʱ����Ϣ */

} TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_GET_GEO_NV_CFG_STRU
 �ṹ˵��  : ��ȡ��������ص�NV����
 1.��    ��   : 2015��05��22��
   ��    ��   : n00269697
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCfgGetGeoFlag;                        /* ��ȡ������Ŀ��� */
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:����C�˵�����λ�������ϵ� ;
                                                                                   1:��C�˵�����λ*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulGetGeoTimerLen;                       /* ��ȡ�����붨ʱ��ʱ������λΪ�� */
    VOS_UINT32                          ulGeoEffectiveTimeLen;                  /* ��������Чʱ������λΪ���� */
} TAF_MMA_GET_GEO_NV_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SDC_CDMA_LOC_INFO_STRU
 �ṹ˵��  : ��ʼ��õ�Xģ��λ����Ϣ������sid��nid��Get_Geo_cnf��Ϣ��������mcc��sidͨ����g_astTafCountryList����
 1.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulMcc;
    VOS_INT32    lSid;
    VOS_INT32    lNid;
}TAF_SDC_CDMA_LOC_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_GET_GEO_CTX_STRU
 �ṹ˵��  : ��ȡ������������
 1.��    ��   : 2015��05��22��
   ��    ��   : f00179208
   �޸�����   : �½�
 2.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : CL_MUTIMODE_OPTIMIZE �޸ģ�����stCdmaLocInfo
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGetGeoTickTime;                       /* LTEλ����Ϣ��ʱ�������λΪ�� */
    TAF_SDC_PLMN_ID_STRU                stGeoPlmnId;                            /* ����λ����Ϣ��PLMN��Ϣ */
    TAF_MMA_GET_GEO_NV_CFG_STRU         stGetGeoNvCfg;
    TAF_SDC_CDMA_LOC_INFO_STRU          stGeoCdmaLocInfo;                          /*���ڱ���Xģ���ѻ�ȡ��λ����Ϣ*/
    VOS_UINT32                          ulGetGeoCdmaTickTime;                      /* CDMAλ����Ϣ��ʱ�������λΪ�� */
} TAF_MMA_GET_GEO_CTX_STRU;

/*****************************************************************************
 ö����    : TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM
 �ṹ˵��  : AP����Dplmn�ĳ���
 1.��    �� : 2015��11��02��
   ��    �� : l00289540
   �޸����� : �����ṹ
*****************************************************************************/
enum TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM
{
    TAF_MMA_AP_PRESET_DPLMN_SCENE_SWITCH_ON,                                     /* �ϵ翪��Ԥ��DPLMN���� */
    TAF_MMA_AP_PRESET_DPLMN_SCENE_DPLMN_UPDATE,                                  /* Ap Dplmn���ݿ��и��´�������������DPLMN�ĳ��� */
    TAF_MMA_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE,                                   /* ���������ĸ���DPLMN�ĳ��� */
    TAF_MMA_AP_PRESET_DPLMN_SCENE_BUTT
};
typedef VOS_UINT8 TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TAF_MMA_GET_HPLMN_STRU
 �ṹ˵��  : �����ѯHPLMN�ı�־
 1.��    ��   : 2012��4��19��
   ��    ��   : w00166186
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene;
    VOS_UINT8                                               aucReserved[3];
}TAF_MMA_SET_DPLMN_CTX_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_GET_HPLMN_STRU
 �ṹ˵��  : �����ѯHPLMN�ı�־
 1.��    ��   : 2012��4��19��
   ��    ��   : w00166186
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_CTRL_STRU                                       stCtrl;
    VOS_UINT8                                               ucHplmnMncLen;
    VOS_UINT8                                               aucReserved[3];
    TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32                  enWaitSimFileCnfFlg;
    VOS_UINT32                                              ulEHplmnNum;
    TAF_SDC_PLMN_ID_STRU                                    astEHplmnList[TAF_SDC_MAX_EHPLMN_NUM];
}TAF_MMA_GET_HPLMN_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_CSG_LIST_CTX_STRU
 �ṹ˵��  : ��¼CSG List�������������
 1.��    ��   : 2015��9��28��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8                 enCsgListAbortProc;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT8                                               ulPlmnWithCsgIdNum;
    TAF_MMA_CSG_ID_LIST_INFO_STRU                           astCsgIdListInfo[TAF_SDC_MAX_CSG_ID_LIST_NUM];
} TAF_MMA_CSG_LIST_CTX_STRU;


/*******************************************************************************
 �ṹ��    : TAF_MMA_USER_PREF_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM/WCDMAƵ��
             bitλ��1��ʾ��Ƶ����Ч

 1.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*******************************************************************************/
typedef struct
{
    VOS_UINT32  BandSpare7                   : 7;
    VOS_UINT32  BandGsmDcs1800               : 1;
    VOS_UINT32  BandGsmEgsm900               : 1;
    VOS_UINT32  BandGsmPgsm900               : 1;
    VOS_UINT32  Spare6                       : 6;
    VOS_UINT32  BandWcdma_VII_2600           : 1;
    VOS_UINT32  BandWcdma_VIII_900           : 1;
    VOS_UINT32  BandWcdma_IX_1700            : 1;
    VOS_UINT32  BandGsm850                   : 1;
    VOS_UINT32  BandGsmRgsm900               : 1;
    VOS_UINT32  BandGsmPcs1900               : 1;
    VOS_UINT32  BandWcdma_I_Imt2k1           : 1;
    VOS_UINT32  BandWcdma_II_PCS_1900        : 1;
    VOS_UINT32  BandWcdma_III_1800           : 1;
    VOS_UINT32  BandWcdma_IV_1700            : 1;
    VOS_UINT32  BandWcdma_V_850              : 1;
    VOS_UINT32  BandWcdma_VI_800             : 1;
    VOS_UINT32  BandWCDMA_XIX_850            : 1;
    VOS_UINT32  BandWcdma_XI_1500            : 1;
    VOS_UINT32  Spare2                       : 2;
}TAF_MMA_USER_PREF_BAND_STRU;

/*******************************************************************************
 �ṹ��    :TAF_MMA_GSM_PREF_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : union GSM_BAND_SET_UN��ԱBitBand����
             bitλ��1��ʾ��Ƶ����Ч
1.��    �� : 2012��3��5��
  ��    �� : w00176964
  �޸����� : DTS201212345678:����BAND6��BAND19��֧��

2.��    ��   : 2015��4��11��
  ��    ��   : y00245242
  �޸�����   : iteration 13����
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;
}TAF_MMA_GSM_PREF_BAND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MMA_WCDMA_PREF_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : union WCDMA_BAND_SET_UN��ԱBitBand����
             bitλ��1��ʾ��Ƶ����Ч

 1.��    ��   : 2012��2��18��
   ��    ��   : w00181244
   �޸�����   : DTS2012020802332�����W BAND XI�Ķ���
 2.��    ��: 2012��3��5��
   ��    ��: w00176964
   �޸�����: DTS201212345678:����BAND6��BAND19��֧��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare10           :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}TAF_MMA_WCDMA_PREF_BAND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MMA_USER_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �û����õ�GU band
 1.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulPrefBand;
    TAF_MMA_USER_PREF_BAND_STRU         BitBand;
}TAF_MMA_USER_BAND_SET_UN;

/*******************************************************************************
 �ṹ��    : TAF_MMA_WCDMA_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMAƵ��union����
 1.��    ��: 2012��3��5��
   ��    ��: w00176964
   �޸�����: ����BAND6��BAND19��֧��
 2.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_WCDMA_PREF_BAND_STRU        BitBand;
}TAF_MMA_WCDMA_BAND_SET_UN;

/*******************************************************************************
 �ṹ��    : TAF_MMA_GSM_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSMƵ��union����
1.��    �� : 2012��3��5��
  ��    �� : w00176964
  �޸����� : DTS201212345678:����BAND6��BAND19��֧��
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_GSM_PREF_BAND_STRU          BitBand;
}TAF_MMA_GSM_BAND_SET_UN;

/*******************************************************************************
 �ṹ��    : TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�ζ���
 1.��    �� : 2014��8��1��
   ��    �� : b00269685
   �޸����� : ���NV8229
 2.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*******************************************************************************/
typedef struct
{
    TAF_MMA_WCDMA_BAND_SET_UN               unWcdmaBand;
    TAF_MMA_GSM_BAND_SET_UN                 unGsmBand;
    VOS_UINT8                               aucReserved1[12];
    VOS_UINT8                               aucReserved2[12];
}TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_SYSCFG_USER_SET_BAND_STRU
 �ṹ˵��  : ���浱ǰ�û�ͨ��syscfg���õ�Ƶ����Ϣ
 1.��    ��   : 2011��7��18��
   ��    ��   : z00161729
   �޸�����   : ����

  2.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
typedef struct
{
    TAF_MMA_USER_BAND_SET_UN            uUserSetGuBand;                         /* �ϴ��û����óɹ���ǰ��Ч��GUƵ�� */
    TAF_USER_SET_PREF_BAND64            stOrigUserSetGuBand;                    /* �ϴ��û����óɹ���GU 64λԭʼƵ��,������ѯʹ�� */
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   uUserSetUeFormatGuBand;                 /* ת��ΪUE֧�ָ�ʽ���ϴ��û����óɹ���ǰ��Ч��GUƵ�� */
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUserSetLteBand;                       /* �ϴ��û����óɹ���ǰ��Ч��LTEƵ�� */
#endif
}TAF_MMA_SYSCFG_USER_SET_BAND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU
 �ṹ˵��  : ���浱ǰ�û�ͨ��syscfg���õĲ���ֵ
 1.��    ��   : 2011��7��18��
   ��    ��   : z00161729
   �޸�����   : ����

  2.��    ��   : 2012��4��20��
    ��    ��   : z40661
    �޸�����   : DTS2012033105463

  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
typedef struct
{
    TAF_MMA_RAT_ORDER_STRU              stRatPrioList;                          /* �ϴ��û����óɹ���ǰ��Ч�Ľ���ģʽ���ȼ�*/
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enRoam;                                 /* �ϴ��û����óɹ���ǰ��Ч���������� */
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8   enPrioRat;                              /* �ϴ��û����óɹ���ǰ��Ч�Ľ������ȼ� */
    VOS_UINT8                           ucReserve;
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;                            /* �ϴ��û����óɹ���ǰ��Ч�ķ����� */
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU   stUserSetBand;                          /* �ϴ��û����óɹ���ǰ��Ч��Ƶ����Ϣ */
}TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_UE_BAND_CAPA_ST
 �ṹ˵��  : UE֧�ֵ�Ƶ����Ϣ
 1.��    ��   : 2011��7��11��
   ��    ��   : z00161729
   �޸�����   : ����UE֧�ֵ�LTEƵ����Ϣ

 2.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    TAF_MMA_WCDMA_BAND_SET_UN           unWRFSptBand;
    TAF_MMA_GSM_BAND_SET_UN             unGRFSptBand;

#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUeSupportLteBand;
#endif
}TAF_MMA_UE_BAND_CAPA_ST;


/*****************************************************************************
 �ṹ��    : TAF_MMA_DSDS_INFO_STRU
 �ṹ˵��  : DSDS��ص���Ϣ
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;
}TAF_MMA_DSDS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_ATTACH_INFO_STRU
 �ṹ˵��  : ATTACH��ص���Ϣ
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAttachOpId;
    VOS_UINT8                           aucRsved[3];
}TAF_MMA_ATTACH_INFO_STRU;



/*****************************************************************************

 �ṹ��    : TAF_MMA_CONTEXT_STRU
 �ṹ˵��  : TAF MMA ģ������������
 1.��    ��   : 2013��7��11��
   ��    ��   : W00176964
   �޸�����   : �½�
 2.��    ��   : 2015��9��30��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        MMA״̬��״̬����״̬ջ
    **************************************************************************/
    TAF_MMA_FSM_CTX_STRU                                    stCurFsm;                               /* ״̬����ǰ��״̬������ */
    TAF_MMA_FSM_STACK_STRU                                  stFsmStack;                             /* ״̬����״̬��ջ����   */

    TAF_MMA_PHONE_MODE_CTRL_CTX_STRU                        stPhoneModeCtrl;                        /* �ֻ�ģʽ���������� */

    TAF_MMA_TIMER_CTX_STRU                                  astMmaTimerCtx[TAF_MMA_MAX_TIMER_NUM];  /* MMA��ǰ�������еĶ�ʱ����Դ */
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU                stMmaExternalModuleInitStatusCtx;       /* MMA��ʼ��״̬��Ϣ */
    /* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];  /* MMA L-C������������ */

    /* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

    /**************************************************************************
                        TAF MMA������Ϣ����
    **************************************************************************/
    TAF_MMA_MSG_QUEUE_STRU                                  stBufferEntryMsgQueue;

    TAF_MMA_INTERNAL_MSG_QUEUE_STRU                         stInternalMsgQueue;                     /* MMA�Ӳ���ڲ���Ϣ���� */

    TAF_MMA_MAINTAIN_CTX_STRU                               stMaintainInfo;

    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU                        stCFreqLockValue;                       /* 1x&evdo��Ƶ��Ϣ */

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     stLastSyscfgSet;                        /* �ϴ��û����óɹ���syscfg���� */

    TAF_MMA_UE_BAND_CAPA_ST                                 stUeBandCap;                            /* UE֧�ֵ�Ƶ������ */

    TAF_MMA_ATTACH_INFO_STRU                                stAttachInfo;

    TAF_MMA_DSDS_INFO_STRU                                  stDsdsInfo;

    TAF_MMA_GET_GEO_CTX_STRU                                stGetGeoInfo;
	
    TAF_MMA_CSG_LIST_CTX_STRU                               stCsgListInfo;

    TAF_MMA_GET_HPLMN_STRU                                  stGetHplmnInfo;
    TAF_MMA_SET_DPLMN_CTX_STRU                              stSetDplmnCtx;

    TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU                stDelayRptCtrlNVInfo;


}TAF_MMA_CONTEXT_STRU;

extern TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
);

VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID );

VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID );

VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID );

TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID);
TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID);

TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID);

VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
);


VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID);

VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID);


TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID);

TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID);

VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
);

VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID );

VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
);

VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
);


VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA���ڲ���Ϣ���� */
);
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
);

VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
);

TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID);

VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID );

VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID );

TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID);

TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
);

VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
);

VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID);

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */


TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID );

VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);

TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID);
VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID );

VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
);

VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
);

MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus(VOS_VOID);

VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted(VOS_VOID);
/* Added by b00269685 for L-C��������Ŀ, 2014-2-14, begin */
TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID );
VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
);

VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
);

VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
);

VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
);

VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
);
/* Added by b00269685 for L-C��������Ŀ, 2014-2-14, end */


VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(VOS_UINT8 ucDelayReportServiceStatusFlg);
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID);
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(VOS_UINT32 ulTimerLen);
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID);
TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU *TAF_MMA_GetCLNoServiceDelayRptInfo(VOS_VOID);



TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID);

VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID);


#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID TAF_MMA_InitCsgListCtx(VOS_VOID);
TAF_MMA_CSG_LIST_CTX_STRU* TAF_MMA_GetCsgListCtxAddr(VOS_VOID);
VOS_VOID TAF_MMA_SetCsgListAbortType(
    TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8                 enCsgListAbortType
);
TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8 TAF_MMA_GetCsgListAbortType(VOS_VOID);
#endif


TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID);
VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID);
VOS_VOID  TAF_MMA_SetGeoNoSimStartFlag(
    VOS_UINT8                           ucNoSimStartFlag
);
VOS_VOID TAF_MMA_InitGetHplmnInfo(VOS_VOID);
TAF_MMA_GET_HPLMN_STRU *TAF_MMA_GetHplmnInfo(VOS_VOID);
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID );
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID );
VOS_UINT8  TAF_MMA_GetGeoNoSimStartFlag(VOS_VOID);
VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID);
VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag);
VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID);
VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID);
VOS_UINT8 TAF_MMA_GetGeoCmpFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetGeoCmpFlag(VOS_UINT8 ucGetGeoCmpFlag);
VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID);

TAF_MMA_SET_DPLMN_CTX_STRU* TAF_MMA_GetSetDplmnCtxAddr(VOS_VOID);

VOS_VOID TAF_MMA_InitSetDplmnCtx(VOS_VOID);

TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8 TAF_MMA_GetDplmnUpdateScene(VOS_VOID);

VOS_VOID TAF_MMA_SetDplmnUpdateScene(
    TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene
);

VOS_VOID  TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen);
VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID);

VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID);

VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
);


VOS_VOID TAF_MMA_SaveSysCfgOrigOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);

TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetSysCfgOrigOperType_SysCfg(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID);

TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID);

#endif

TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID);

TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID);

TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID);

TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID);

TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID);

VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID);


TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID);

VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
);

VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusFlg(
    VOS_UINT8 ucCLDelayReptSrvStatusFlg
);

VOS_UINT8 TAF_MMA_GetCLDelayReptSrvStatusFlg(VOS_VOID);

VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusTimerLen(
    VOS_UINT32 ulTimerLen
);

VOS_UINT32 TAF_MMA_GetCLDelayReptSrvStatusTimerLen(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_MMA_IsGeoCdmaLocValid(VOS_VOID);

VOS_VOID TAF_MMA_UpdateGeoCdmaLocInfo(
    VOS_INT32                   lSid,
    VOS_INT32                   lNid
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

#endif /* end of TafMmaCtx.h */

