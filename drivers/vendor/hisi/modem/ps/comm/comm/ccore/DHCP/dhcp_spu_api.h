/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : dhcp_spu_api.h
  Version       : Initial Draft
  Author        : l00103336
  Created       : 2012/4/24
  Last Modified :
  Description   : DHCPģ��SPU�ṩ�Ĺ������ݶ���
  Function List :
  History       :
  1.Date        : 2012/4/24
    Author      : l00103336
    Modification: Created file

******************************************************************************/
#ifndef __DHCP_SPU_API_H__
#define __DHCP_SPU_API_H__

/*******************************************************************************************************/
/********************                          �궨��                           ************************/
/*******************************************************************************************************/
/*dhcp���ݰ��е�chaddr ��,sname���file��ĳ���*/
#define DHCPS_CHADDR_LEN               16
#define DHCPS_SNAME_LEN                64
#define DHCPS_FILE_LEN                128

#define DHCPV6C_MAX_DUID_LEN 14 /* DUID ����󳤶� 14�ֽ� */

/* 24bit��С�ֽ���ת��---��Ҫ��transctionId��24bit 0x15001605----0x15051600*/
#ifndef VOS_NTOHBIT24
#if VOS_BYTE_ORDER == VOS_BIG_ENDIAN
#define VOS_NTOHBIT24(x)    (x)
#define VOS_HTONBIT24(x)    (x)
#else
#define VOS_NTOHBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )

#define VOS_HTONBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )
#endif
#endif

/*******************************************************************************************************/
/********************                        �ṹ����                           ************************/
/*******************************************************************************************************/

/*DHCPS��USM֮�����Ϣ����*//*��Ҫ�ŵ�pub.h��*/
typedef enum tagDHCPS_USM_MSG_E
{
    DHCPS_USM_APPLYIP_MSG           =  1,   /*DHCPS���͸�USM����IP��ַ*/
    DHCPS_USM_RELEASEIP_MSG        =  2,  /*DHCPS���͸�USM�ͷ�IP��ַ*/
    DHCPS_USM_APPLYIPOK_MSG       = 3,  /*USM��Ӧ�������ַ�ɹ�*/
    DHCPS_USM_APPLYIPFAILED_MSG = 4,  /*USM��Ӧ�������ַʧ��*/
    DHCPS_USM_DEACTIVE_MSG         = 5,  /*USM���͵�ȡ���û�*/
    DHCPS_USM_MSG_END
}DHCPS_USM_MSG_E;

/* zhangjinquan 00175135 DHCPv6���� 2012-06-30 start */
/*DHCP���ƿ�*/
typedef struct tagDHCPC_CTRLBLK
{
    struct tagDHCPC_CTRLBLK *pstPreNode;    /* add by tianyang 00144555 for dhcpv6 ���� 2012-07-18 */
    struct tagDHCPC_CTRLBLK *pstNextNode;
    VOID *pTmpDhcpCtrlBlkPtr;       /* ���ڱ�����ʱ���ƿ�ָ�� */
    VOS_UINT32       ulDHCPCtxIdx;       /*DHCP���ƿ�����*/
    VOS_UINT32       ulPDPIndex;         /*�û�������������*/
    VOS_UINT32       aulMSISDN[2];       /*MSISDN*/
    VOS_UINT32       aulIMSI[2];         /*IMSI*/
    VOS_UINT32       aulIMEI[2];         /* IMEI */
    VOS_UINT32       ulLease;            /*��õ�lease*/
    VOS_UINT32       ulTimeStamp;        /*����REQ��Ϣ��ϵͳʱ��*/
    VOS_UINT32       aulSrvIp[4];        /*������server IP*/
    VOS_UINT32       aulUserIpAddr[4];   /*�û������ĵ�IP��ַ*/
    VOS_UINT32       aulMainDnsAddr[4];  /*��DNS-IP��ַ*/
    VOS_UINT32       aulSecdDnsAddr[4];  /*��DNS-IP��ַ*/
    VOS_UINT32       aulAgentIpAddr[4];  /*����IP��ַ*/
    VOS_UINT32       ulTmpVar;           /*��ʱ���������ڱ�����ʱ���ƿ�ָ�뼰��Լʱ����REQ��ulTimeStamp*/
    VOS_UINT32       ulTEIDC;            /* TEIDC. ע��!!!! ���������޸ġ���Dhcpv6��ʹ����,�����ڿ��ƿ���������޸ġ� */
    VOS_UINT32       ulT1;               /* DHCPv6��ַ��T1ʱ�� */
    VOS_UINT32       ulT2;               /* DHCPv6��ַ��T2ʱ�� */

    VOS_UINT16      usVPNIndex;         /* ����LAP��Ϣ�е�VPN���� */
    VOS_UINT16      usPoolIndex;
    VOS_UINT16      usServerGrpIndex;   /*ServerGrp index*/
    VOS_UINT16      usApnIndex;         /*APN����*/

    VOS_UINT16      usSeqNum;
    UCHAR       ucUserType:4;       /*UserType ppp,gtp*/
    UCHAR       usDhcpStatus:4;
    UCHAR       ucRole:4;
    UCHAR       ucUser:4;            /*�û�����:V0:0;V1:1;V2:2*/
    UCHAR       ucCurSvrSendCount:4; /* ��ǰServer������Ϣ�Ĵ��� */
    UCHAR       ucTotalSendCount:4;  /* ��Server������Ϣ���ܴ��� */
    UCHAR       ucResendTimeout;     /* �ڷ�����Ϣ�ĵ�һ�λ�ȡ,�ط���Ϣ�����в���ȡ. */
    UCHAR       ucCurrentServer:1;
    UCHAR       ucWaitRspTimeOutNum:4;
    UCHAR       ucAgingFlag:3;       /* ���ƿ��� */
    UCHAR       ucLAPNo;

    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN]; /* �����ַ��DHCP������ID */
    UCHAR       ucIpType:4;
    UCHAR       ucResource:3;       /* ��Դλ��־ */
    UCHAR       ucUsedFlag:1;       /* ���ƿ��Ƿ�ռ�ñ�־. ע��!!!! �����ڿ��ƿ���������޸ġ�  */
    UCHAR       ucLeaseStatus:4;    /* ��Լ״̬ */
    UCHAR       ucCause:4;

    UCHAR       ucRandomNo;        /* ������� DTS2012091903437 y00170683 */

#if 0
    UCHAR       aucResved[3];       /*�����ֶ�*/
#endif
    VOS_UINT8   ucRabId;                      /*RabId*/
    MODEM_ID_ENUM_UINT16  enModemId;          /*enModemId*/
}DHCPC_CTRLBLK;
/* zhangjinquan 00175135 DHCPv6���� 2012-06-30 end   */

/* BEGIN: Added by jixiaoming for ��ʡ�ڴ� at 2012-10-26 */

typedef struct tagDHCPV4C_BAK_INFO_S
{
    VOS_UINT32       ulUserIpAddr;
    VOS_UINT32       ulAgentIpAddr;
    VOS_UINT32       ulServerIp;
    UCHAR       aucReserve[44];
}DHCPV4C_BAK_INFO_S;

typedef struct tagDHCPV6C_BAK_INFO_S
{
    VOS_UINT32       aulUserIpAddr[4];
    VOS_UINT32       aulAgentIpAddr[4];
    VOS_UINT32       ulT1;               /* DHCPv6��ַ��T1ʱ�� */
    VOS_UINT32       ulT2;               /* DHCPv6��ַ��T2ʱ�� */
    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN];    /* �����ַ��DHCPV6������ID */
    UCHAR       ucLeaseStatus:4;    /* ��Լ״̬.V6��ʹ�� */
    UCHAR       ucResource:3;       /* ��Դλ,V6ʹ�� */
    UCHAR       ucCurrentServer:1;  /* ��ǰʹ�õ�Server,V6ʹ�� */
    UCHAR       ucReserve;
}DHCPV6C_BAK_INFO_S;

/*
   DHCP Client���ݿ��ƿ�.���д�ŵ�Ϊ���뱸�ݵ�����,�Ǳ��뱸�����ݲ��ɷ��롣
   �޸ĸýṹ��,��Ӱ�쵽CKP������ڴ��С�������޸ĸýṹ�����ͨ��MDE����
*/
typedef struct tagDHCPC_BACKBLK_S
{
    VOS_UINT32       aulMSISDN[2];       /* MSISDN */
    VOS_UINT32       aulIMSI[2];         /* IMSI */
    VOS_UINT32       aulIMEI[2];         /* IMEI */
    VOS_UINT32       ulLease;            /* leaseʱ��,V4��V6���� */
    VOS_UINT32       ulTimeStamp;        /* ��ַ�����renew�ɹ���ʱ��� */
    VOS_UINT32       ulTEIDC;
    VOS_UINT32       ulPDPIndex;         /* ���������� */
    VOS_UINT16      usVPNIndex;         /* �����LAP��Ϣ�л�ȡ��VPN���� */
    VOS_UINT16      usPoolIndex;        /* ��ַ������ */
    VOS_UINT16      usServerGrpIndex;   /* ServerGrp index*/
    VOS_UINT16      usApnIndex;         /* APN���� */

    union
    {
        DHCPV4C_BAK_INFO_S stDhcpv4;
        DHCPV6C_BAK_INFO_S stDhcpv6;
    }unBakInfo;

    UCHAR       ucLAPNo;            /* �����ַ��LAP���е�ı�� */
    UCHAR       ucRandomNo;         /* ������ٺ� */
    UCHAR       ucRole:4;           /* Ŀǰ���������ĵĽ�ɫ */
    UCHAR       usDhcpStatus:4;     /* DHCP״̬ */
    UCHAR       ucReserve;
}DHCPC_BACK_BLK_S;
/* END: Added by jixiaoming for ��ʡ�ڴ� at 2012-10-26 */

/*dhcp���������ṹDHCPS_ANALYZEDPACKET_S*/
typedef struct tagDHCPS_ANALYZEDPACKET
{
    VOS_UINT32        ulRequestedAddr;      /*�����ip��ַ*/
    VOS_UINT16      usPacketLength;       /*���ݰ�����*/
    UCHAR        ucPacketType;          /*���ݰ�����*/
    UCHAR        ucHtype;                 /* �û�Ӳ������*/

    VOS_UINT32        ulXid;                       /* Transaction ID */
    VOS_UINT16      usFlags;                  /* Flag bits */
    VOS_UINT16      usMaxDhcpSize;     /*���İ��ĳ��� */

    VOS_UINT32        ulCiaddr;                 /* Client IP address (if already in use) */
    VOS_UINT32        ulGiaddr;                 /* DHCP relay agent IP address */
    UCHAR        pucChaddr [DHCPS_CHADDR_LEN];       /* Client hardware address */
    VOS_UINT32        ulYiaddr;                 /* Client IP address */
    VOS_UINT32        ulServerId;             /* ��������IP��ַ */
    UCHAR        aucParaReqList[256];   /*1~254, ��ౣ��254��*/
    UCHAR        ucParaReqLen;
    UCHAR        ucOptionOverload;  /*�ֶ� overload��־*/
    /* Modified start by ZhangYang  z00142225 at 2008-12-17 UGWV900R001C001 for ��ַ���书�� */
    UCHAR       ucRapidCommitFlag;
    UCHAR       aucRev[1];
    /* Modified end by ZhangYang  z00142225 at 2008-12-17 UGWV900R001C001 for ��ַ���书�� */
}DHCPS_ANALYZEDPACKET_S;

/*��Լ������Ϣ�ṹDHCPS_LEASE_S*/
typedef struct tagDHCPS_LEASE
{
    DHCPS_ANALYZEDPACKET_S  *pstAnalyzedPacket;       /*��Ӧ��ԭʼ���ĵĽ�����Ϣ*/
    VOS_UINT32                   ulAddr;                   /*lease��ipv4��ַ*/
    VOS_UINT32                   ulIndex;                  /*��Լ������Ҳ���û�������������*/

    UCHAR                   ucPmipFlag;               /*S5S8�ӿڵ�Э���־  0 gtp  1 pmip*/
    UCHAR                   ucRole;                   /*���ӽ�ɫ*/
    UCHAR                   ucLeaseState:4;           /*����LEASE��״̬ */
    UCHAR                   ucLeaseTimerOP:3;         /*֪ͨ������Լ��ʱ��������־:0��ʾ��Ч;1��ʾ����;2��ʾɾ��;3��ʾ��ɾ��������*/
    UCHAR                   ucUsed:1;                 /*ʹ�ñ��*/
    UCHAR                   ucUserNumFlag:1;          /*Ԥ���ֶ�*/
    UCHAR                   ucFirstRequestMsgFlag:1;  /*ֱ�ӷ���Request��Ϣ�ı�־λ*/
    UCHAR                   ucReserveBit:6;
#ifdef __LINUX_PLATFORM__
    UCHAR                   aucReserve[4];
#endif
}DHCPS_LEASE_S;

typedef struct tagDHCP
{
    UCHAR       ucOp; /*1=����2=Ӧ��*/
    UCHAR       ucHtype; /*client��Ӳ����ַ����:1=Ethernet*/
    UCHAR       ucHlen; /*client��Ӳ����ַ����:Ethernet=6*/
    UCHAR       ucHops;
    VOS_UINT32       ulXid;
    VOS_UINT16      usSecs;
    VOS_UINT16      usFlag;
    VOS_UINT32       ulCiaddr;
    VOS_UINT32       ulYiaddr; /*Server�����client��IP��ַ*/
    VOS_UINT32       ulSiaddr;
    VOS_UINT32       ulGiaddr; /*���ص�ַ*/
    UCHAR       szChaddr[DHCPS_CHADDR_LEN];/*client��Ӳ����ַ*/
    CHAR        szSname[DHCPS_SNAME_LEN];
    CHAR        szFile[DHCPS_FILE_LEN];
}VOS_PACKED DHCP_S;

/*DHCPS��USM�ӿڵ����ݽṹ����*/
typedef struct tagDHCPS_USM_MSG_S
{
    VOS_UINT32 ulMsgType;                    /*��Ϣ����*/
    VOS_UINT32 ulPDPContextIndex;     /*PDP�����ĵ�����������Լ������*/
    VOS_UINT32 ulAddress;                    /*IP��ַ*/
} DHCPS_USM_MSG_S;

/***************************************************************/
/**************         DHCPV6 ��Ϣ�ṹ��         ***************/
/***************************************************************/

/*�����ȫ����չ���� 1�ֽڶ���*/
#pragma pack(1)
/* DHCPV6��Ϣ�嶨�� */
typedef struct tagDHCPV6C_MSG_S
{
    VOS_UINT32  ulMsgTypeBit8:8;  /* ��Ϣ���� */
    VOS_UINT32  ulTransIdBit24:24; /* transaction ID */
}DHCPV6C_MSG_S;
#pragma pack()

/*******************************************************************************************************/
/********************                        ȫ�ֱ���                           ************************/
/*******************************************************************************************************/

extern VOS_UINT32 g_ulDhcpDebug;
extern VOS_UINT32 g_ulDHCPSUSMQueId;
extern VOS_UINT32 g_ulDhcpServerTaskId ;

/*******************************************************************************************************/
/********************                        ��������                           ************************/
/*******************************************************************************************************/
extern VOS_UINT32 DHCPC_BackupProc( char **ppbuff, UCHAR ucIpType, VOS_UINT32 ulTEIDC);
extern VOS_UINT32 DHCPC_BKRestoreProc( char **ppbuff, UCHAR ucIpType, VOS_UINT32 ulTEIDC );
//extern VOS_UINT32 DHCPC_BKDeleteProc( UCHAR ucIpType, VOS_UINT32 ulTEIDC, UCHAR ucUser, VOS_UINT32 ulPDPIndex );

#endif /* end of __DHCP_SPU_API_H__ */
