/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MM_Def.h
  Description : MMȫ�ֿ������ݽṹ�궨���ļ�
  History     :
      1.  ��־��      2003.11.25   �¹�����
      2.  s46746   2006-03-17   �������ⵥA32D02502�޸�
      3.��    ��   : 2006��11��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D06442
      4.��    ��   : 2007��3��5��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D09094
      5.��    ��   : 2007��3��20��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D09497
      6.��    ��   : 2007��6��26��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D11968,GSM��������������Ϊ8,ÿ��Լ0.5��,��˱���ʱ������Ϊ4��
      7.��    ��   : 2009��02��28��
        ��    ��   : s46746
        �޸�����   : �������ⵥAT2D09546,WCDMA��ģ�£�A5/1��������Ϊ��֧��
      8.��    ��   : 2009��07��24��
        ��    ��   : z40661
        �޸�����   : ��ϵͳ��ѡ�󣬽������в��ܽ�ͨ
      9.��    ��   : 2009��11��09��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�AT2D15401,CS�ػ�Detach����ʱ��̫�̣�û�еȵ������ͷ����Ӿͳ�ʱ�����ͷ���
*******************************************************************************/
#ifndef _MM_DEF_H_
#define _MM_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

/*****************************************************************************/
/***********************************  �궨��  ********************************/
/*****************************************************************************/
#define     MM_TRUE                                     0                       /* True                                     */
#define     MM_FALSE                                    1                       /* False                                    */

#define ERROR_ID                          0                                     /* Error����                                */
/*****************************************************************************/
/************ ���ݱ��������̺�ԭ��ֵ�жϵó���MM���Ӵ��������ļ��� ***********/
/*****************************************************************************/

#define     MM_CONN_HANDLE_ALL_CALL_PROCESS                 0                   /* hadle all call process                   */
#define     MM_CONN_HANDLE_EMERGENCY_CALL_ONLY              1                   /* hadle emergency call only                */
#define     MM_CONN_HANDLE_NO_CALL_PROCESS                  2                   /* hadle no call process                    */

/*****************************************************************************/
/**************************** ���ڳ����ĺ궨�� *******************************/
/*****************************************************************************/
/* ����-1,0��20,32�ĺ궨�� */
#define     MM_CONST_NUM_MINUS_ONE                     -1
#define     MM_CONST_NUM_0                             0
#define     MM_CONST_NUM_1                             1
#define     MM_CONST_NUM_2                             2
#define     MM_CONST_NUM_3                             3
#define     MM_CONST_NUM_4                             4
#define     MM_CONST_NUM_5                             5
#define     MM_CONST_NUM_6                             6
#define     MM_CONST_NUM_7                             7
#define     MM_CONST_NUM_8                             8
#define     MM_CONST_NUM_9                             9
#define     MM_CONST_NUM_10                            10
#define     MM_CONST_NUM_11                            11
#define     MM_CONST_NUM_12                            12
#define     MM_CONST_NUM_13                            13
#define     MM_CONST_NUM_14                            14
#define     MM_CONST_NUM_15                            15
#define     MM_CONST_NUM_16                            16
#define     MM_CONST_NUM_17                            17
#define     MM_CONST_NUM_18                            18
#define     MM_CONST_NUM_19                            19
#define     MM_CONST_NUM_20                            20
#define     MM_CONST_NUM_32                            32
#define     MM_CONST_NUM_40                            40
#define     MM_CONST_NUM_48                            48
#define     MM_CONST_NUM_64                            64
#define     MM_CONST_NUM_80                            80
#define     MM_CONST_NUM_128                           128
#define     MM_CONST_NUM_256                           256
#define     MM_CONST_NUM_272                           272
#define     MM_CONST_NUM_312                           312
#define     MM_CONST_NUM_1024                          1024

/* ��G�£���GAS�ظ�����ʧ��(ԭ��ֵΪCONN_FAIL)ʱ��MM�����·���������ߵ绰��ͨ�ʣ�
   ��Ϊ�˷�ֹMM/GASֱ��Ƶ���Ľ���ƹ�Ҳ���������Ϣ����������޶���ೢ��5�� */
#define     MM_CALL_RETRY_MAX_TIMES                    5

/*****************************************************************************/
/*****************************  TIMER�ĺ궨��  *******************************/
/*****************************************************************************/
/* MM Timer�����������¶�ʱ������ͬ�����¡� */


/* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

/* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */




/* Timerʱ���궨�� */
#define     MM_TIMER_T3210_VALUE                        (20 * 1000)
#define     MM_TIMER_T3211_VALUE                        (15 * 1000)
#define     MM_TIMER_T3213_VALUE                        ( 4 * 1000)
#define     MM_TIMER_T3214_VALUE                        (20 * 1000)
#define     MM_TIMER_T3216_VALUE                        (15 * 1000)
#define     MM_TIMER_T3218_VALUE                        (20 * 1000)
#define     MM_TIMER_T3220_VALUE                        ( 5 * 1000)
#define     MM_TIMER_T3230_VALUE                        (15 * 1000)
#define     MM_TIMER_T3240_VALUE                        (10 * 1000)
#define     MM_TIMER_PROTECT_AGENT_VALUE                (10 * 1000)
/*A32D11968==>GSM��������������Ϊ8,ÿ��Լ0.5��,��˱���ʱ������Ϊ4��*/
#define     MM_TIMER_PROTECT_DETACH_VALUE               (8 * 1000)
/*<==A32D11968*/

#define     MM_TIMER_PROTECT_W_SIGNALLING_VALUE         (115 * 1000)
#define     MM_TIMER_PROTECT_G_SIGNALLING_VALUE         (60 * 1000)


#define     MM_TIMER_PROTECT_CC_VALUE                   (30 * 1000)

/* #define     MM_TIMER_PERIOD_VALUE                        5 * 1000 */

#define     MM_TIMER_PROTECT_CCBS_VALUE                 (15 * 1000)

#define     MM_TIMER_PROTECT_SUSPEND_VALUE              (15 * 1000)/* MMC is 10s */

#define     MM_TIMER_T3212_MAX_VALUE                    (18*60*60*1000) /*OSA��ʱ����󳤶�*/

#define     MM_TIMER_DELAY_LU_GSM_VALUE                 (1000)     /* 1 �� */
#define     MM_TIMER_DELAY_CS_SERVICE_GSM_VALUE         (4000)     /* 4 �� */

#define     MM_TIMER_WAIT_CONNECT_REL_VALUE             (10000)    /* 10 �� */



/* ��ΪGMM�Ĺػ�������ʱ��ʱ��Ϊ8S��MM�ı�����ʱ��ʱ���Գ���GMM�� */
#define NAS_MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT_LEN_VALUE     (8500)     /* MM�ػ�������ʱ��ʱ�� */



/* MM ����SYSCFG������Detach���̵Ķ�ʱ��ʱ��,��GMM�ı���PSʱ��Ϊ25s��һ�� */
#define     NAS_MM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE           (26000)

/* MM ������SYSCFG������PS���Detach���̵Ķ�ʱ��ʱ��,��CGCATT */
#define     NAS_MM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE       (90000)


/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-11, begin */
#define     MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_LEN_VALUE           (5000)     /* MM�ȴ���ȡLMM��CS��ȫ�����ĵĶ�ʱ��ʱ�� */
/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-11, end */


#define     MM_TIMER_MAX_VALUE                             (18*60*60*1000)      /*OSA��ʱ����󳤶�*/

/* ���º궨�������: MM_TimerStop ��Ч */
#define     MM_TIMER_STOP_ALL                          100                      /* ֹͣ��ǰ�Ѿ����������ж�ʱ��             */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#define     MM_TIMER_T3242_VALUE                                    (12*3600*1000)  /* ʱ��12Сʱ */
#define     MM_TIMER_T3243_VALUE                                    (12*3600*1000)  /* ʱ��12Сʱ */
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */


/*****************************************************************************/
/************************** TIMER���б�־�ĺ궨�� ****************************/
/*****************************************************************************/

#define     MM_TIMER_T3210_FLG                 (0x00000001<<MM_TIMER_T3210)     /* T3210��ʱ����־                          */
#define     MM_TIMER_T3211_FLG                 (0x00000001<<MM_TIMER_T3211)     /* T3211��ʱ����־                          */
#define     MM_TIMER_T3212_FLG                 (0x00000001<<MM_TIMER_T3212)     /* T3212��ʱ����־                          */
#define     MM_TIMER_T3213_FLG                 (0x00000001<<MM_TIMER_T3213)     /* T3213��ʱ����־                          */
#define     MM_TIMER_T3214_FLG                 (0x00000001<<MM_TIMER_T3214)     /* T3214��ʱ����־                          */
#define     MM_TIMER_T3216_FLG                 (0x00000001<<MM_TIMER_T3216)     /* T3216��ʱ����־                          */
#define     MM_TIMER_T3218_FLG                 (0x00000001<<MM_TIMER_T3218)     /* T3218��ʱ����־                          */
#define     MM_TIMER_T3220_FLG                 (0x00000001<<MM_TIMER_T3220)     /* T3220��ʱ����־                          */
#define     MM_TIMER_T3230_FLG                 (0x00000001<<MM_TIMER_T3230)     /* T3230��ʱ����־                          */
#define     MM_TIMER_T3240_FLG                 (0x00000001<<MM_TIMER_T3240)     /* T3240��ʱ����־                          */
#define     MM_TIMER_PROTECT_AGENT_FLG         (0x00000001<<MM_TIMER_PROTECT_AGENT)
#define     MM_TIMER_PROTECT_DETACH_FLG        (0x00000001<<MM_TIMER_PROTECT_DETACH)
#define     MM_TIMER_PROTECT_SIGNALLING_FLG  \
            (0x00000001<<MM_TIMER_PROTECT_SIGNALLING)
/*#define   MM_TIMER_PROTECT_FLG               (0x00000001<<MM_TIMER_PROTECT) */ /* ������ʱ����־                           */

#define     MM_TIMER_PROTECT_CC_FLG            (0x00000001<<MM_TIMER_PROTECT_CC)

#define     MM_TIMER_PROTECT_CCBS_FLG          (0x00000001<<MM_TIMER_PROTECT_CCBS)


/****************************************************************************/
/****************************** MM��RRC�ӿڵĺ궨�� *************************/
/****************************************************************************/

/* ԭ��    �ĺ궨�� */


/****************************************************************************/
/************************* MM��MMC�ӿڵĺ궨�� ******************************/
/****************************************************************************/

/* ԭ��    �ĺ궨�� */




/****************************************************************************/
/************************ ���紥��detach���̵ĺ궨��  ***********************/
/****************************************************************************/
#define     MM_NET_DETACH_REATTACH                          1                   /* re-attach required                       */
#define     MM_NET_DETACH_REATTACH_NOT_REQUIRED             2                   /* re-attach not required                   */
#define     MM_NET_DETACH_WITH_IMSI                         3                   /* IMSI detach                              */




/*****************************************************************************/
/*************************** ԭ��ֵ�ĺ궨�� **********************************/
/*****************************************************************************/

/*****************************************************************************/
/*************************** �����¼��ĺ궨�� ********************************/
/*****************************************************************************/
#define     MM_EVENT_ID_ATTACH_REQ             (2)
#define     MM_EVENT_ID_DETACH_REQ             (22)
#define     MM_EVENT_ID_CC_EST_REQ             (24)
#define     MM_EVENT_ID_CC_DATA_REQ            (27)
#define     MM_EVENT_ID_PAGING_IND             (31)
#define     MM_EVENT_ID_AUTH_REQ               36
#define     MM_EVENT_ID_AUTH_REJ               37
#define     MM_EVENT_ID_IDENTITY_REQ           38
#define     MM_EVENT_ID_TMSI_REALLOC_CMD       39
#define     MM_EVENT_ID_CM_SVC_ACCEPT          40
#define     MM_EVENT_ID_CM_SVC_REJ             41
#define     MM_EVENT_ID_ABORT                  42
#define     MM_EVENT_ID_MM_INFO                43
#define     MM_EVENT_ID_MM_STATUS              44
#define     MM_EVENT_ID_LU_ACCEPT              45
#define     MM_EVENT_ID_LU_REJECT              46
#define     MM_EVENT_ID_CM_SVC_PROMPT          47
#define     MM_EVENT_ID_CC_MESSAGE             50
#define     MM_EVENT_ID_SMS_EST_REQ            (62)
#define     MM_EVENT_ID_SMS_DATA_REQ           (64)
#define     MM_EVENT_ID_SS_EST_REQ             (65)
#define     MM_EVENT_ID_SS_DATA_REQ            (67)
#define     MM_EVENT_ID_SS_MESSAGE             69
#define     MM_EVENT_ID_SMS_MESSAGE            70

#define     MM_EVENT_ID_TC_MESSAGE             73

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */
#define     MM_EVENT_ID_T3242_EXPIRED          (90)
#define     MM_EVENT_ID_T3243_EXPIRED          (91)
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

#define     MM_EVENT_ID_STATUS_95              195
#define     MM_EVENT_ID_STATUS_96              196

#define     MM_EVENT_ID_INVALID                255

/* NAS INFO TYPE DEFINE */

#define     MM_NAS_INFO_NULL_FLG            0x00
#define     MM_NAS_INFO_ATTACH_FLG          0x01
#define     MM_NAS_INFO_SIM_STATUS_FLG      0x02
#define     MM_NAS_INFO_SK_FLG              0x04
#define     MM_NAS_INFO_LOCA_INFO_FLG       0x08
#define     MM_NAS_INFO_DEL_KEY_FLG         0x40
#define     MM_NAS_INFO_ALL_FLG             0x0F


/* MM��Ҫ������ͬ���ı�ʶ,����G/W��ѡ��,����LAU�ĳ���*/
#define     MM_NAS_INFO_SYNC_AS_FLG        ((MM_NAS_INFO_ATTACH_FLG) | (MM_NAS_INFO_LOCA_INFO_FLG) )




#define     MM_MAX_OPID                                    255

/* Read Sim File ID */
#define     MM_READ_IMSI_FILE_ID                            0x6F07
#define     MM_READ_CKIK_FILE_ID                            0x6F08
#define     MM_READ_LOCA_INFO_FILE_ID                       0x6F7E
#define     MM_READ_KC_FILE_ID                              0x6F20

/* Sim File Len */
#define     MM_SIM_FILE_LEN_IMSI                            9
#define     MM_SIM_FILE_LEN_CKIK                            33
#define     MM_SIM_FILE_LEN_LOCA_INFO                       11
#define     MM_SIM_FILE_LEN_KC                              9

/* CK IK Invalid define */
#define     MM_CK_IK_INVALID                                0
#define     MM_CKSN_INVALID                                 0x07
#define     MM_TMSI_INVALID                                 0

/* ��������ATTACH��RAU���� */
#define     MM_ATTACH                           1
#define     MM_RAU                              2
#define     MM_NET_DETACH                       3
#define     MM_SERVICE_REQ                      4

#define     MM_SUBLAYER_INFO_LOCK_SUCCESS       0
#define     MM_SUBLAYER_INFO_LOCK_FAILURE       1

#define     MM_SUBLAYER_INFO_UNLOCK_SUCCESS       0
#define     MM_SUBLAYER_INFO_UNLOCK_FAILURE       1


/* ��֧��GPRSҵ���С����־ */

#define     MM_UNSUPPORT_GPRS           0xFFFF


/* LAI��Ч�ı�ʶ */
/*#define     MM_INVALID_LAI              0xFEFF*/
#define     MM_INVALID_LAI              0xFFFE

#define     NAS_MM_INVALID_EMERGENCY_NUMBER                 (0xFF)

#define     MM_AUTH_PRO                             0x0
#define     MM_LAU_SUCCESS                          0x1
#define     MM_LAU_FAILURE                          0x2
#define     MM_SERVICE_SUCCESS                      0x5
#define     MM_SERVICE_FAILURE                      0x6
#define     MM_TMSI_RELOC                           0x7
#define     MM_DETACH_COMPLETE                      0x8

#define     MM_EVENT_ID_STATUS_95              195
#define     MM_EVENT_ID_STATUS_96              196

#define     NAS_MM_CIPHER_ALGO_UEA0              0
#define     NAS_MM_CIPHER_ALGO_UEA1              1
#define     NAS_MM_CIPHER_ALGO_NOPRESENT         2

#define MM_RAND_MAX 0x7fff

#define     MM_CLASSMARK_RF_POWER_CAP_MASK     0x7
#define     MM_CLASSMARK_RF_POWER_CAP_CLASS1   0x0
#define     MM_CLASSMARK_RF_POWER_CAP_CLASS2   0x1
#define     MM_CLASSMARK_RF_POWER_CAP_CLASS3   0x2
#define     MM_CLASSMARK_RF_POWER_CAP_CLASS4   0x3

#define     MM_CLASSMARK_A5_1_NOT_SUPPORT_MASK 0x8

#define     MM_CLASSMARK_REVISION_LEVEL_GSM_PH1           0x00
#define     MM_CLASSMARK_REVISION_LEVEL_GSM_PH2           0x01
#define     MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER      0x02

#define     MM_CS_SERV_NONE_EXIST                           0x00
#define     MM_CS_SERV_EMERGENCY_CALL_EXIST                 0x01
#define     MM_CS_SERV_NORMAL_CALL_EXIST                    0x02
#define     MM_CS_SERV_SMS_EXIST                            0x03
#define     MM_CS_SERV_SS_EXIST                             0x04
#define     MM_CS_SERV_MT_EXIST                             0x05


enum{
    MM_DECODE_SUCCESS,
    MM_DECODE_END,
    MM_DECODE_FAILURE
};
typedef VOS_UINT32      MM_DECODE_RESULT_ENUM_U32;
#define MMC_MM_SIGNALING_STATUS_ABSENT          0
#define MMC_MM_SIGNALING_STATUS_PRESENT         1


#define     MM_CC_MSG_TYPE_POS                  1
#define     MM_CC_MSG_SETUP                     0x05

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
