/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CasMntnOmInterface.h
  �� �� ��   : ����
  ��    ��   : along
  ��������   : 2015��6��27��
  ����޸�   :
  ��������   : CasMntnOmInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��27��
    ��    ��   : w00248682
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CASMNTNOMINTERFACE_H__
#define __CASMNTNOMINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "CUeSpec.h"
#include "PsTypeDef.h"
#include "TTFComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : CAS_MNTN_RPT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : EVDO ����С����Ϣ������
*****************************************************************************/
enum CAS_MNTN_RPT_TYPE_ENUM
{
    CAS_MNTN_RPT_ONLYONE              = 0,
    CAS_MNTN_RPT_PERIOD                  ,
    CAS_MNTN_RPT_CHNGE_RPT               ,
    CAS_MNTN_RPT_TYPE_BUTT
};
typedef VOS_UINT8 CAS_MNTN_RPT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CAS_MNTN_RPT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : 1X ����С����Ϣ������
*****************************************************************************/
enum CAS_1X_MNTN_RPT_TYPE_ENUM
{
    CAS_1X_MNTN_RPT_ONLYONE              = 0,
    CAS_1X_MNTN_RPT_PERIOD                  ,
    CAS_1X_MNTN_RPT_TYPE_BUTT
};
typedef VOS_UINT8 CAS_1X_MNTN_RPT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CAS_MNTN_RPT_CMD_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :��ʼ��ѯ����ֹͣ��ѯ����
*****************************************************************************/
enum CAS_MNTN_RPT_CMD_ENUM
{
    CAS_MNTN_RPT_STOP                 = 0,
    CAS_MNTN_RPT_START                = 1,
    CAS_MNTN_RPT_BUTT
};
typedef VOS_UINT8 CAS_MNTN_RPT_CMD_ENUM_UINT8;


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
 �ṹ��    : CAS_1X_OM_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Cnf��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucReserved[3];

    CAS_1X_MNTN_RPT_TYPE_ENUM_UINT8         enReportType;                       /*һ���ϱ��������ϱ� */

    PS_RSLT_CODE_ENUM_UINT32                enRslt;                             /* ���ز�ѯ�ṹ�ɹ���ʧ�� */

}CAS_1X_OM_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_CAS_1X_CELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CELL_INFO CONFIG   OM�ں�������Ϣ�ṹ
*****************************************************************************/

typedef struct
{
    CAS_MNTN_RPT_CMD_ENUM_UINT8             enCommand;                          /* start or stop */

    CAS_1X_MNTN_RPT_TYPE_ENUM_UINT8         enReportType;                       /* һ���ϱ��������ϱ� */

    VOS_UINT16                              usReportPeriod;                      /* report time period */
} OM_CAS_1X_CELL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;

    OM_CAS_1X_CELL_INFO_STRU        stCellInfoStru;

}OM_CAS_1X_CELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  CAS_1X_OM_CELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Cnf��Ϣ --- OM�ں�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;

    CAS_1X_OM_CELL_INFO_STRU        stCellInfoStru;

}CAS_1X_OM_CELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_CAS_1X_SERVICE_CFG_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SERVICE CFG INFO   OM�ں�������Ϣ�ṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               aucReserved[3];

    CAS_MNTN_RPT_CMD_ENUM_UINT8             enCommand;                /* start or stop */

} OM_CAS_1X_SERVICE_CFG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                             ulMsgId;

    VOS_UINT16                             usOriginalId;
    VOS_UINT16                             usTerminalId;
    VOS_UINT32                             ulTimeStamp;
    VOS_UINT32                             ulSN;

    OM_CAS_1X_SERVICE_CFG_INFO_STRU        stServiceCfgInfoStru;

}OM_CAS_1X_SERVICE_CFG_INFO_REQ_STRU;
/*****************************************************************************
 �ṹ��    :  CAS_1X_OM_SERVICE_CFG_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Service Cfg Info Cnf��Ϣ --- OM�ں�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                             ulMsgId;

    VOS_UINT16                             usOriginalId;
    VOS_UINT16                             usTerminalId;
    VOS_UINT32                             ulTimeStamp;
    VOS_UINT32                             ulSN;

    PS_RSLT_CODE_ENUM_UINT32               enRslt;                 /* ���ز�ѯ�ṹ�ɹ���ʧ�� */

}CAS_1X_OM_SERVICE_CFG_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : OM_CAS_HRPD_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CELL_INFO CONFIG
*****************************************************************************/
typedef struct
{
    CAS_MNTN_RPT_CMD_ENUM_UINT8             enCommand;                          /* start or stop */

    CAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;                       /* һ���ϱ��������ϱ����߱仯�ϱ�*/

    VOS_UINT16                              usReportPeriod;                     /* report time period */
} OM_CAS_HRPD_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_OM_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Cnf��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucReserved[3];

    CAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;                       /*һ���ϱ��������ϱ����߱仯�ϱ�*/

    PS_RSLT_CODE_ENUM_UINT32                enRslt;                             /* ���ز�ѯ�ṹ�ɹ���ʧ�� */
}CAS_HRPD_OM_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_CAS_HRPD_CELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CELL_INFO CONFIG   OM�ں�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;

    OM_CAS_HRPD_CELL_INFO_STRU      stCellInfoStru;

}OM_CAS_HRPD_CELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  CAS_HRPD_OM_CELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Cnf��Ϣ --- OM�ں�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;

    CAS_HRPD_OM_CELL_INFO_STRU      stCellInfoStru;

}CAS_HRPD_OM_CELL_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : OM_CAS_HRPD_CONN_INFO_RESET_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CONN_INFO_RESET   OM�ں�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
}OM_CAS_HRPD_CONN_INFO_RESET_NTF_STRU;


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

#endif /* end of CasMntnOmInterface.h */

