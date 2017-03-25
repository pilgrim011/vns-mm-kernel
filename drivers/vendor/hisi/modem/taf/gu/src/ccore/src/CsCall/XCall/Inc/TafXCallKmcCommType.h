
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallKmcCommType.h
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��10��20��
  ��������   : TAF X CALL ����KMC ��Ϣ��USER DATA�Ľṹ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00359089
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __TAF_X_CALL_KMC_COMM_TYPE_H__
#define __TAF_X_CALL_KMC_COMM_TYPE_H__

#include "vos.h"
#include "PsLogdef.h"
#include "TafStdlib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_MAX_PLAIN_DATA_LEN                        (160)               /*����������ݳ���*/

#define TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN                 (48)                /*���ǩ����Ϣ����*/

#define TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN                 (160)               /*���ǩ�����ݳ���*/

#define TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN                    (160)               /*������ĳ���*/

#define TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN             (6)                 /*�����볤��*/

#define TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN               (48)                /*KMC��Կ����*/

#define TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN              (24)                /*KMC˽Կ����*/

#define TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN                   (16)                /*���������  128 bits */

#define TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX            (160)               /* Maximum number of bytes for CDMA user data */

#define TAF_XCALL_KMC_MSG_HEADER_LEN                        (4)                 /*ͷ������*/

#define TAF_XCALL_KMC_MSG_SPECIAL_SMS_ID                    (0x00)              /*������ű�ʶ*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD1                   (0x00)              /*������չ�ֶ�1*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD2                   (0x00)              /*������չ�ֶ�2*/

/* header 4 bytes + KeyVersion 1 byte + TIME STAMP 7 bytes + RomoteCtrlCmdType 1 byte + SignInfoLen 1 byte = 14 bytes*/
#define TAF_XCALL_KMC_MSG_REMOTE_CTRL_HEADER_LEN            (14)                /*Զ�̿���ָ����Ϣͷ����*/

/* header 4 bytes + KeyVersion 1 byte + KeyLen 1 byte =6 byte*/
#define TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN     (6)                 /*��Կ������Ϣͷ����*/

#define TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES                    (2)                 /*������չ�ֶγ���*/

#define TAF_XCALL_KMC_MSG_KEY_VESRION_MAX                   (255)               /*��Կ�汾�ŵ����ֵ*/

#define TAF_XCALL_KMC_MSG_KEY_VESRION_MIN                   (1)                 /*��Կ�汾�ŵ���Сֵ*/

#define TAF_XCALL_KMC_MSG_TIME_STAMP_LEN                    (7)                 /*ʱ�������*/

#define TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN               (6)                 /*������Ϣ����*/

#define TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN_BYTES         (1)                 /*������Ϣ���ȱ�־λ��ռ�ֽ���*/

#define TAF_XCALL_KMC_MSG_RSVD1_BYTES                       (1)                 /*�����ֶ�1��ռ�ֽ���*/

#define TAF_XCALL_KMC_MSG_RSVD2_BYTES                       (1)                 /*�����ֶ�2��ռ�ֽ���*/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*************************************
 ö������  TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM
 ö��˵���������ܻ�ģʽ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM
{
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL                   = 0x00,             /*�ֶ������ܻ�*/
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO                     = 0x01,             /*�Զ������ܻ� */
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_BUTT                                         /*����*/
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM_UINT8;

/*************************************
 ö������  TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM
 ö��˵��������֪ͨ ��Ϣ ԭ��ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM
{
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_NO_PERMISSION     = 0x00,             /*�����û��޼���Ȩ��*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_NO_PERMISSION    = 0x01,             /*�Զ��û��޼���Ȩ�� */
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_ILLEGAL           = 0x02,             /*�����ն˷Ƿ�*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_ILLEGAL          = 0x03,             /*�Զ��ն˷Ƿ�*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ESTABLISH_TIME_OUT      = 0x04,             /*�ܻ�������ʱ*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_OTHERS                  = 0x05,             /*����ԭ��*/
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM_UINT8;

/*************************************
 ö������  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM
 ö��˵����Զ�̿���ָ������ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE                    =0x00,              /*��ȫ��Ϣ����*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET                            =0x01,              /*��������*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8;

/*************************************
 ö������  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_EXECUTE_RSLT_ENUM
 ö��˵����Զ�̿���ָ��ִ�н��
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SUCCESS                              = 0x00,  /* �ɹ� */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_KEY_VERSION_MISMATCH_FAILURE         = 0x01,  /* KMC��Կ�汾��һ�µ��µ�ʧ�� */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE                  = 0x02,  /* ǩ����֤ʧ�ܵ��µ�ʧ�� */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE                        = 0x03,  /* �������⵼�°�ȫ��Ϣ����ʧ�� */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8;

/*************************************
 ö������  TAF_XCALL_KMC_MSG_TYPE_ENUM
 ö��˵������Ϣ���ͱ�־
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_TYPE_ENUM
{
    TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ                       =0x00,              /*������Կ����*/
    TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP                       =0x01,              /*������Կ��Ӧ*/
    TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND                   =0x02,              /*���м���֪ͨ��Ϣ*/
    TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ                       =0x03,              /*������Կ����*/
    TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP                       =0x04,              /*������Կ��Ӧ */
    TAF_XCALL_KMC_MSG_TYPE_ERR_IND                          =0x05,              /*����֪ͨ*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND               =0x06,              /*KMC��Կ����*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP               =0x07,              /*KMC��Կ������Ӧ*/
    TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK               =0x08,              /*KMC��Կ����ȷ��*/
    TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND              =0x09,              /*Զ�̿���ָ��   */
    TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP              =0x0a,              /*Զ�̿�����Ӧ   */
    TAF_XCALL_KMC_MSG_TYPE_UNKNOWN                          =0x0b,              /* ����   */
    TAF_XCALL_KMC_MSG_TYPE_BUTT
};
typedef VOS_UINT8   TAF_XCALL_KMC_MSG_TYPE_ENUM_UINT8;

/*************************************
 ö������  TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM
 ö��˵����KMC MSG ����봦����
 1.����:      20151023
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
enum TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM
{
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS                  =0,
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_TYPE_UNKNOWN,                            /*��Ϣ���ʹ���*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH,                              /*��Ϣ���ݲ���*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR,                           /*ǩ����Ϣ����Ϊ0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_CIPHER_LEN_ERR,                              /*������Ϣ����Ϊ0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_REMOTE_NUMBER_LEN_ERR,                       /*���е绰���볤��Ϊ0*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_PUB_KEY_LEN_ERR,                             /*��Կ���Ȳ��� */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR,                        /*���볤�ȳ������ֵ*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_TIME_STAMP_ERR,                              /*ʱ����д�*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ROMOTE_CTRL_CMD_TYPE_ERR,                    /*Զ�̿���ָ�����ʹ���*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ERR_IND_CAUSE_ERR,                           /*����֪ͨԭ��ֵ����*/
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_BUTT
};
typedef VOS_UINT32   TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32;

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
/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU
 �ṹ˵����������Ϣ�ֶ�
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBsid;
    VOS_UINT8                           aucReserved[2];
}TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_SIGN_INFO_STRU
 �ṹ˵����ǩ����Ϣ�ֶ�
 1.����:      20151023
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*KMCǩ����Ϣ����*/
    VOS_UINT8                           ucSignInfoLen;
    VOS_UINT8                           aucReserved[3];

    /*KMCǩ����Ϣ*/
    VOS_UINT8                           aucSignInfo[TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN];
}TAF_XCALL_KMC_MSG_SIGN_INFO_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_PUB_KEY_STRU
 �ṹ˵������Կ�ֶ�
 1.����:      20151023
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*KMC��Կ����*/
    VOS_UINT8                           ucKeyLen;
    VOS_UINT8                           aucReserved[3];

    /*KMC��Կ*/
    VOS_UINT8                           aucKey[TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
}TAF_XCALL_KMC_PUB_KEY_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_PRIV_KEY_STRU
 �ṹ˵����˽Կ�ֶ�
 1.����:      20151026
   ����:      y00245242
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*KMC˽Կ����*/
    VOS_UINT8                           ucKeyLen;
    VOS_UINT8                           aucReserved[3];

    /*KMC˽Կ*/
    VOS_UINT8                           aucKey[TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN];
}TAF_XCALL_KMC_PRIV_KEY_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_PRIV_KEY_STRU
 �ṹ˵���������ֶ�
 1.����:      20151102
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    VOS_UINT16                          usCipherLen;        /*���ĳ��ȣ�2bytes*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucCipher[TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN]; /*����*/
}TAF_XCALL_KMC_MSG_CIPHER_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_KEY_REQ_STRU
 �ṹ˵������Կ������Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_TRIGGER_MODE_ENUM_UINT8               enTriggerMode;      /*�����ܻ�ģʽ*/
    VOS_UINT8                                               ucKeyVersion;       /*KMC��Կ�汾*/
    VOS_UINT8                                               aucReserved[2];
    TAF_XCALL_KMC_PUB_KEY_STRU                              stTmpPubKey;        /*��ʱ��Կ*/
    TAF_XCALL_KMC_MSG_CIPHER_STRU                           stCipher;           /*�����ֶ�*/
    TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_STRU                  stAdditionalInfo;   /*������Ϣ�ֶ�*/
}TAF_XCALL_KMC_MSG_KEY_REQ_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_KEY_RSP_STRU
 �ṹ˵������Կ��Ӧ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_CIPHER_STRU                           stCipher;           /*�����ֶ�*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;         /*ǩ����Ϣ*/
}TAF_XCALL_KMC_MSG_KEY_RSP_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU
 �ṹ˵�������м���֪ͨ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*���к��볤��*/
    VOS_UINT8                           ucRemoteNumberLen;

    VOS_UINT8                           aucReserved[1];

    /*���к���*/
    VOS_UINT8                           aucRemoteNumber[TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN];
}TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_ERR_IND_STRU
 �ṹ˵��������֪ͨ ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/

typedef struct
{
    TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ENUM_UINT8              enErrCause;         /*ԭ��ֵ*/
    VOS_UINT8                                               aucReserved[3];     /*�����ֶ�*/
}TAF_XCALL_KMC_MSG_ERR_IND_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU
 �ṹ˵����KMC��Կ���� ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{

    VOS_UINT8                                               ucKeyVersion;       /*KMC��Կ�汾*/
    VOS_UINT8                                               aucReserved[3];     /*�����ֶ�*/
    TAF_XCALL_KMC_PUB_KEY_STRU                              stPubKey;           /*KMC��Կ*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;         /*KMCǩ����Ϣ*/
}TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU
 �ṹ˵����KMC��Կ������Ӧ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*�����*/
    VOS_UINT8                           aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
}TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU
 �ṹ˵����KMC��Կ����ȷ�� ��Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*�����*/
    VOS_UINT8                           aucRandomData[TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN];
} TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU
 �ṹ˵����Զ�̿���ָ��
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    /*KMC��Կ�汾*/
    VOS_UINT8                                               ucKeyVersion;
    VOS_UINT8                                               aucReserved1[3];     /*�����ֶ�*/
    /*ʱ���*/
    TAF_STD_TIME_ZONE_TYPE_STRU                             stTimeStamp;

    /*Զ�̿���ָ������*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRomoteCtrlCmdType;
    VOS_UINT8                                               aucReserved2[3];     /*�����ֶ�*/

    /*KMCǩ����Ϣ*/
    TAF_XCALL_KMC_MSG_SIGN_INFO_STRU                        stSignInfo;

}TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU
 �ṹ˵����Զ�̿���ָ����Ӧ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRomoteCtrlCmdType;                            /*Զ�̿���ָ������*/
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enExecuteRslt;                                  /*ָ��ִ�н��*/
    VOS_UINT8                                               ucKeyVersion;                                   /*�ն˴洢��KMC��Կ�汾��*/
    VOS_UINT8                                               ucReserved;                                    /*�����ֶ�*/
}TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU;

/*************************************
 �ṹ����  TAF_XCALL_KMC_MSG_INFO_STRU
 �ṹ˵�����ն���KMC������Ϣ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*************************************/
typedef struct
{
    VOS_UINT8                                               ucSpecSmsID;        /*������ű�ʶ*/
    VOS_UINT8                                               aucExtCtrlField[TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES];  /*������չ�ֶ�*/
    TAF_XCALL_KMC_MSG_TYPE_ENUM_UINT8                       enSmsType;          /*��Ϣ����*/
    union
    {
        TAF_XCALL_KMC_MSG_KEY_REQ_STRU                      stKeyReq;           /*��Կ����*/
        TAF_XCALL_KMC_MSG_KEY_RSP_STRU                      stKeyRsp;           /*��Կ��Ӧ*/
        TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU               stMtEncryptInd;     /*���м���֪ͨ��Ϣ*/
        TAF_XCALL_KMC_MSG_ERR_IND_STRU                      stErrInd;           /*����֪ͨ*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU           stPubKeyUpdateInd;  /*KMC��Կ����*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU           stPubKeyUpdateRsp;  /*KMC��Կ������Ӧ*/
        TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU           stPubKeyUpdateAck;  /*KMC��Կ����ȷ��*/
        TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU          stRemoteCtrlInd;    /*Զ�̿���ָ��   */
        TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU          stRemoteCtrlRsp;    /*Զ�̿���ָ����Ӧ*/
                                                                                /*����*/

    }u;
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt;             /*�������*/
}TAF_XCALL_KMC_MSG_STRU;

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

#endif /* end of TafXCallKmcCommType.h */
