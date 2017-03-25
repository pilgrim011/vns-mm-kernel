/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafLcsInterface.h
  �� �� ��   : ����
  ��    ��   : l00198894
  ��������   : 2015��9��14��
  ����޸�   :
  ��������   : TafLcsInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFLCSINTERFACE_H__
#define __TAFLCSINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "LcsCommInterface.h"
#include "LocCommonInterface.h"
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_LCS_MSG_ID_BASE             0x0
#define LCS_TAF_MSG_ID_BASE             0x100

/* TAF��LCS֮ǰԭ��ֵ�ֶ� */
#define TAF_LCS_CAUSE_INTER_ERR_BEGIN   0x00010000
#define TAF_LCS_CAUSE_INTER_ERR_END     0x0001FFFF
#define TAF_LCS_CAUSE_NW_SECTION_BEGIN  0x00020000
#define TAF_LCS_CAUSE_NW_SECTION_END    0x0002FFFF
#define TAF_LCS_CAUSE_MM_ERR_BEGIN      0x00030000
#define TAF_LCS_CAUSE_MM_ERR_END        0x0003FFFF
#define TAF_LCS_CAUSE_LMM_ERR_BEGIN     0x00040000
#define TAF_LCS_CAUSE_LMM_ERR_END       0x0004FFFF

/* MMԭ��ֵ�ڲ�ƫ��,��16λ��NAS_MMCM_REL_CAUSE_ENUM_UINT32�зֶ�һ�� */
#define TAF_LCS_CAUSE_MM_CM_SRV_REJ_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x100)
#define TAF_LCS_CAUSE_MM_CM_SRV_REJ_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x1FF)
#define TAF_LCS_CAUSE_MM_CSFB_SRV_REJ_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x200)
#define TAF_LCS_CAUSE_MM_CSFB_SRV_REJ_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x2FF)
#define TAF_LCS_CAUSE_MM_SMS_CP_ERR_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x300)
#define TAF_LCS_CAUSE_MM_SMS_CP_ERR_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x3FF)
#define TAF_LCS_CAUSE_MM_SMS_RP_ERR_BEGIN                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x400)
#define TAF_LCS_CAUSE_MM_SMS_RP_ERR_END                  (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x4FF)
#define TAF_LCS_CAUSE_MM_SS_NW_REJ_BEGIN                 (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x500)
#define TAF_LCS_CAUSE_MM_SS_NW_REJ_END                   (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x5FF)
#define TAF_LCS_CAUSE_MM_RR_CONN_FAIL_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x600)
#define TAF_LCS_CAUSE_MM_RR_CONN_FAIL_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x6FF)
#define TAF_LCS_CAUSE_MM_RR_REL_BEGIN                    (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x700)
#define TAF_LCS_CAUSE_MM_RR_REL_END                      (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x7FF)
#define TAF_LCS_CAUSE_MM_CSFB_LMM_FAIL_BEGIN             (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x800)
#define TAF_LCS_CAUSE_MM_CSFB_LMM_FAIL_END               (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x8FF)
#define TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN              (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x900)
#define TAF_LCS_CAUSE_MM_MM_INTER_ERR_END                (TAF_LCS_CAUSE_MM_ERR_BEGIN + 0x9FF)

/* ����ԭ��ֵƫ��, ��16λ������ԭ��ֵ�ڲ��ֶ�һ�� */
#define TAF_LCS_CAUSE_NW_ERROR_BEGIN                     (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x200)
#define TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN               (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8000)
#define TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN                (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8100)
#define TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN             (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8200)
#define TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN              (TAF_LCS_CAUSE_NW_SECTION_BEGIN + 0x8300)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*******************************************************************************
 ö����    : TAF_LCS_CAUSE_ENUM
 �ṹ˵��  : LCSԭ��ֵ����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum TAF_LCS_CAUSE_ENUM
{
    TAF_LCS_CAUSE_SUCCESS                           = 0,

    /* �ڲ����� */
    TAF_LCS_CAUSE_LCS_NOT_SUPPORT                                      = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 0),     /* MO-LR��һЩ����LCS��֧�� */
    TAF_LCS_CAUSE_LCS_USER_TIMER_OUT                                   = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 1),     /* LCS�ȴ��Ñ��ظ�������ʱ����ʱ */
    TAF_LCS_CAUSE_LCS_NW_TIMER_OUT                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 2),     /* LCS�ȴ�����ظ�������ʱ����ʱ */
    TAF_LCS_CASUE_MSG_PARA_INVAILD                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 3),     /* TAF����LCS��Ϣ������Ч */
    TAF_LCS_CAUSE_MO_LR_ALREADY_EXISTED                                = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 4),     /* ����MO-LR���� */
    TAF_LCS_CAUSE_TAF_MOLR_DISABLE                                     = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 5),     /* �û�DIABLE MO-LR */
    TAF_LCS_CAUSE_EXIST_VOLTE_SER                                      = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 6),     /* ����VOLTEҵ�� */
    TAF_LCS_CAUSE_NORAML_REL                                           = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 7),     /* LCS������������ */
    TAF_LCS_CAUSE_NOT_CAMP_ON                                          = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 8),     /* δפ�� */
    TAF_LCS_CAUSE_CONN_REL                                             = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 9),     /* ��·�ͷ� */
    TAF_LCS_CAUSE_OTHERS                                               = (TAF_LCS_CAUSE_INTER_ERR_BEGIN + 10),    /* ����ԭ�� */

    /* ������ش��� */
    /* Error Codeԭ��ֵ */
    TAF_LCS_CAUSE_NW_ERR_SS_SUBVIOLATION                               = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 19),   /* �����û�Ȩ�� */
    TAF_LCS_CAUSE_NW_ERR_FACILITY_NOT_SUPPORT                          = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 21),   /* Facility��֧�� */
    TAF_LCS_CAUSE_NW_ERR_SYSTEM_FAIL                                   = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 34),   /* �����쳣 */
    TAF_LCS_CAUSE_NW_ERR_DATA_MISSING                                  = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 35),   /* ȱʧ���� */
    TAF_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE                           = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 36),   /* �Ƿ����� */
    TAF_LCS_CAUSE_NW_ERR_POSITION_METHOD_FAIL                          = (TAF_LCS_CAUSE_NW_ERROR_BEGIN + 54),   /* ��λ��ʽ���� */

    /* Rej Compnent Problemԭ��ֵ */
    /*********************** General Problem Codes ********************/
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_COMPONENT                            = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_MISTYPED_COMPONENT                                = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_BADLY_STRUCTURED_COMPONENT                        = TAF_LCS_NW_CAUSE_GENERAL_REJ_BEGIN + 2,

    /************************Invoke Problem Codes***********************/
    TAF_LCS_NW_CAUSE_DUPLICATE_INVOKE_ID                               = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_OPERATION                            = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_INVOKE_MISTYPED_PARAMETER                         = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 2,
    TAF_LCS_NW_CAUSE_RESOURCE_LIMITATION                               = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 3,
    TAF_LCS_NW_CAUSE_INITIATING_RELEASE                                = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 4,
    TAF_LCS_NW_CAUSE_UNRECOGNIZED_LINKED_ID                            = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 5,
    TAF_LCS_NW_CAUSE_LINKED_RESPONSE_UNEXPECTED                        = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 6,
    TAF_LCS_NW_CAUSE_UNEXPECTED_LINKED_OPERATION                       = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 7,
    TAF_LCS_NW_CAUSE_INVALID_MANDATORY_IE                              = TAF_LCS_NW_CAUSE_INVOKE_REJ_BEGIN + 8,

    /**********************Return Result Problem Codes******************/
    TAF_LCS_NW_CAUSE_RETURN_RSLT_UNRECOGNIZED_INVOKE_ID                = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_RETURN_RSLT_UNEXPECTED                            = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_RETURN_RSLT_MISTYPED_PARAMETER                    = TAF_LCS_NW_CAUSE_RTRN_RSLT_REJ_BEGIN + 3,

    /**********************Return Error Problem Codes********************/
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_INVOKE_ID               = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 0,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED                           = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 1,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNRECOGNIZED_ERROR                   = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 2,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_UNEXPECTED_ERROR                     = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 3,
    TAF_LCS_NW_CAUSE_RETURN_ERROR_MISTYPED_PARAMETER                   = TAF_LCS_NW_CAUSE_RTRN_ERR_REJ_BEGIN + 4,

    /* MM���صĴ��� */
    /* MM Inter Error */
    TAF_LCS_CAUSE_MM_INTER_ERR_FORB_LA                                 = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 0,
    TAF_LCS_CAUSE_MM_INTER_ERR_FORB_OTHER                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 1,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR                           = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 2,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_DETACH                               = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 3,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_SIM_INVALID                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 4,
    TAF_LCS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION                   = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 5,
    TAF_LCS_CAUSE_MM_INTER_ERR_T3230_TIMER_OUT                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 6,
    TAF_LCS_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 7,
    TAF_LCS_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE                 = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 8,
    TAF_LCS_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY        = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 9,
    TAF_LCS_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 10,
    TAF_LCS_CAUSE_MM_INTER_ERR_ATTEMPTING_TO_UPDATE                    = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 11,
    TAF_LCS_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS                     = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 12,
    TAF_LCS_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 13,
    TAF_LCS_CAUSE_MM_INTER_ERR_TI_INVALID                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 14,
    TAF_LCS_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT                   = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 15,   /* redial */
    TAF_LCS_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST                       = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 16,
    TAF_LCS_CAUSE_MM_INTER_ERR_UE_INVALID_STATE                        = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 17,
    TAF_LCS_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT                  = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 18,
    TAF_LCS_CAUSE_MM_INTER_ERR_BACK_TO_LTE                             = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 19,
    TAF_LCS_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD                         = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 20,
    TAF_LCS_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 21,   /* ����ҵ��SAPI3����ʧ��,��GAS�ظ�ʧ��,���ز� */
    TAF_LCS_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 22,   /* ����ҵ��SAPI3����ʱGAS�ظ�ʧ��,�ز� */
    TAF_LCS_CAUSE_MM_INTER_ERR_ECALL_INACTIVE                          = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 23,   /* eCall Inactive״̬,���ز� */
    TAF_LCS_CAUSE_MM_INTER_ERR_REEST_FAIL                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 24,   /* MM reest״̬�յ�est_cnf(ʧ��)��rel ind,���ز� */
    TAF_LCS_CAUSE_MM_INTER_ERR_CC_REL_REQ                              = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 25,
    TAF_LCS_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE                     = TAF_LCS_CAUSE_MM_MM_INTER_ERR_BEGIN + 26,

    /* LMM���صĴ��� */
    TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 0),     /* PS��δע�� */
    TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED                            = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 1),     /* PS������ע�� */
    TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 2),     /* USIM����Ч */
    TAF_LCS_CAUSE_LMM_ACCESS_BARRED                                    = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 3),     /* ��BAR */
    TAF_LCS_CAUSE_LMM_STATE_CANNOT_SERVICE                             = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 4),     /* ��ǰ״̬��������Service���� */
    TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT                              = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 5),     /* EPC-LCS��֧�� */
    TAF_LCS_CAUSE_LMM_3411_RUNNING                                     = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 6),     /* 3411��ʱ���������� */
    TAF_LCS_CAUSE_LMM_SERVICE_FAIL                                     = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 7),     /* Serviceʧ�� */
    TAF_LCS_CAUSE_LMM_RRC_CONN_NOT_EXIST                               = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 8),     /* ��·������ */
    TAF_LCS_CAUSE_LMM_LOW_LAYER                                        = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 9),     /* �ײ�ʧ�� */
    TAF_LCS_CAUSE_LMM_USER_INACTIVITY                                  = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 10),    /* ���಻���ʱ����ʱ���µ��ͷ� */
    TAF_LCS_CAUSE_LMM_OTHERS                                           = (TAF_LCS_CAUSE_LMM_ERR_BEGIN + 11),    /* ����ԭ��ֵ */

    TAF_LCS_CAUSE_BUTT

};
typedef VOS_UINT32 TAF_LCS_CAUSE_ENUM_UINT32;

/*******************************************************************************
 ö����    : TAF_LCS_LR_TYPE_EUNM
 �ṹ˵��  : LCS����Location Request����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum TAF_LCS_LR_TYPE_EUNM
{
    TAF_LCS_LR_TYPE_MO                  = 0,                                    /* MO-LR */
    TAF_LCS_LR_TYPE_MT                  = 1,                                    /* MT-LR */

    TAF_LCS_LR_TYPE_BUTT
};
typedef VOS_UINT8 TAF_LCS_LR_TYPE_EUNM_UINT8;

/*******************************************************************************
 ö����    : TAF_LCS_POWER_STATUS_EUNM
 �ṹ˵��  : ���ػ�״̬ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum TAF_LCS_POWER_STATUS_EUNM
{
    TAF_LCS_POWER_STATUS_OFF            = 0,                                    /* Power Off */
    TAF_LCS_POWER_STATUS_ON             = 1,                                    /* Power On */

    TAF_LCS_POWER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_LCS_POWER_STATUS_EUNM_UINT8;

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
 ö������: TAF_LCS_MSG_ID_ENUM
 ö��˵��: TAF����LCSģ���Ľӿ���ϢID

 �޸���ʷ      :
  1.��    ��   : 2015��09��09��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_LCS_MSG_ID_ENUM
{
    /* TAF���͸�LCS����Ϣԭ�� */
    ID_TAF_LCS_BEGIN_REQ                = TAF_LCS_MSG_ID_BASE + 0x1,            /* _H2ASN_MsgChoice TAF_LCS_BEGIN_REQ_STRU */
    ID_TAF_LCS_END_REQ                  = TAF_LCS_MSG_ID_BASE + 0x2,            /* _H2ASN_MsgChoice TAF_LCS_END_REQ_STRU */
    ID_TAF_LCS_POWER_STATUS_NTF         = TAF_LCS_MSG_ID_BASE + 0x3,            /* _H2ASN_MsgChoice TAF_LCS_POWER_STATUS_NTF_STRU */

    /* LCS���͸�TAF����Ϣԭ�� */
    ID_LCS_TAF_BEGIN_IND                = LCS_TAF_MSG_ID_BASE + 0x1,            /* _H2ASN_MsgChoice LCS_TAF_BEGIN_IND_STRU */
    ID_LCS_TAF_FACILITY_IND             = LCS_TAF_MSG_ID_BASE + 0x2,            /* _H2ASN_MsgChoice LCS_TAF_FACILITY_IND_STRU */
    ID_LCS_TAF_END_IND                  = LCS_TAF_MSG_ID_BASE + 0x3,            /* _H2ASN_MsgChoice LCS_TAF_END_IND_STRU */

    ID_TAF_LCS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 TAF_LCS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ����: LCS_TAF_LOCATION_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: MO-LR����,����ظ���Location��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLocationEstimate   :1;
    VOS_UINT32                          bitOpVelocityEstimate   :1;
    VOS_UINT32                          bitOpSpare              :30;
    LOC_COM_COORDINATE_STRU             stLocationEstimate;             /* λ����Ϣ */
    LOC_COM_VELOCITY_STRU               stVelocityEstimate;             /* �ٶ���Ϣ */
}LCS_TAF_LOCATION_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_LCS_BEGIN_REQ_STRU
 �ṹ˵��  : TAF SSAģ�鷢��LCSģ����ϢID_TAF_LCS_BEGIN_REQ��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_MOLR_PARA_STRU                  stMolrPara;
}TAF_LCS_BEGIN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_LCS_BEGIN_REQ_STRU
 �ṹ˵��  : TAF SSAģ�鷢��LCSģ����ϢID_TAF_LCS_BEGIN_REQ��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_LR_TYPE_EUNM_UINT8          enLcsType;                              /* LR���� */
    LCS_MTLRA_OP_ENUM_UINT8             enAllow;                                /* MT-LRʱ��Ч */
    VOS_UINT8                           ucHandleId;                             /* MT-LRʱ��Ч */
    VOS_UINT8                           aucReserved[1];
}TAF_LCS_END_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_LCS_POWER_STATUS_NTF_STRU
 �ṹ˵��  : TAF SSAģ�鷢��LCSģ����ϢID_TAF_LCS_POWER_STATUS_NTF��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_POWER_STATUS_EUNM_UINT8     enStatus;                               /* ���ػ�״̬ */
    VOS_UINT8                           aucReserved[3];
}TAF_LCS_POWER_STATUS_NTF_STRU;

/*****************************************************************************
 �ṹ��    : LCS_TAF_BEGIN_IND_STRU
 �ṹ˵��  : LCSģ�鷢��TAF SSAģ����ϢID_LCS_TAF_BEGIN_IND��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_MTLR_PARA_STRU                  stMtlrPara;
}LCS_TAF_BEGIN_IND_STRU;

/*****************************************************************************
 �ṹ��    : LCS_TAF_FACILITY_IND_STRU
 �ṹ˵��  : LCSģ�鷢��TAF SSAģ����ϢID_LCS_TAF_FACILITY_IND��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    LCS_TAF_LOCATION_INFO_STRU          stLocationParam;
    TAF_LCS_CAUSE_ENUM_UINT32           enCause;                                /* ԭ��ֵ */
}LCS_TAF_FACILITY_IND_STRU;

/*****************************************************************************
 �ṹ��    : LCS_TAF_END_IND_STRU
 �ṹ˵��  : LCSģ�鷢��TAF SSAģ����ϢID_LCS_TAF_END_IND��Ӧ�ṹ��
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    TAF_LCS_LR_TYPE_EUNM_UINT8          enLcsType;                              /* LR���� */
    VOS_UINT8                           ucHandleId;                             /* MT-LRʱ��Ч */
    VOS_UINT8                           aucReserved[2];                         /* ����λ */
    TAF_LCS_CAUSE_ENUM_UINT32           enCause;                                /* ԭ��ֵ */
}LCS_TAF_END_IND_STRU;




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/








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

#endif /* end of TafLcsInterface.h */

