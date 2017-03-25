/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpc_var.c
  �� �� ��   : ����
  ��    ��   : c57548
  ��������   : 2007��11��3��
  ����޸�   :
  ��������   : dhcpcģ���ȫ�ֱ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��11��3��
    ��    ��   : c57548
    �޸�����   : �����ļ�

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpv6c_pkt.h"
#include "dhcpc_var.h"

/*��sd֮��Ĺ������id*/
VOID    *g_pulSDDhcpMCQueID         = 0;

/* ��sd�Ͻ���dhcpv6 server��Ϣ�Ĺ������ */
VOID    *g_pulSDDhcpv6cMcQueId      = 0;

/*dhcpc��lap������Ϣ�Ķ���id*/
VOID    *g_pulDHCP_LAP2_RSPQueID    = 0;

/*dhcpc����lap��Ϣ�Ķ���id*/
VOID    *g_pulDHCP_LAP2_REQQueID    = 0;

/*����dhcpc hash����ʱ��hash�ڵ�ı��*/
ULONG   g_ulCtrlblkXaxis = 0; /*����HASH����X��,����Ϊ65535*/

/*����dhcpc hash����ʱÿ��hash�ڵ��µĿ��ƿ�ڵ���*/
ULONG   g_ulCtrlblkYaxis = 0; /*����HASH����Y��,����HASHKEY��ͬ�Ľڵ�*/

/*dhcpcģ�������id*/
ULONG   g_ulDhcpcTaskId             = 0;

/*����������Ϣ�Ķ�ʱ��id*/
RELTMR_T   g_ulDhcpcRenewTimerID       = 0;

/*�����ط���Ϣ�Ķ�ʱ��id*/
RELTMR_T   g_ulDhcpcRetransTimerID     = 0;

/*���ƿ��ϻ���ʱ��ID*/
RELTMR_T g_ulDhcpcCtrlBlockAgingTimerID = 0;

/*dft���Ϳ��ƿ鶨ʱ��ID*/
ULONG   g_uldftDhcpcSendCBTimerID = 0;

/*SEQNUM�ϻ���ʱ��ID*/
RELTMR_T g_ulDhcpcSeqnumAgingTimerID = 0;

/*��ʱ������id*/
ULONG   g_ulDhcpcTimerQid           = 0;

ULONG   g_ulDhcpcInnerQid           = 0;


/*dhcpc����sd������Ϣ�Ķ���id*/
ULONG   g_ulDhcpcServerQid          = 0;

/*���ö�ʱ��Ŀǰ������û�DHCP���ƿ�����*/
ULONG   g_ulCurrDHCPCCtlIndex       = 1;

/*���ö�ʱ������*/
ULONG   g_ulTimerRenewType          = 0;

/*�ط���ʱ����ǰ����������index*/
ULONG   g_ulCurrProcIndex           = 0;

/*�ط���ʱ������*/
ULONG   g_ulTimerRetransType        = 0;

/*Xid����ʼֵ*/
ULONG   g_ulDHCPCTransId            = 0;

/*ȫ�����õ�IP��Чʱ��ȫ�ֱ���*/
ULONG   g_ulDhcpcGlbLeaseTime       = 0;

/*DHCPCģ����Դ�ӡ����*/
ULONG   g_ulDHCPCDbgPkt             = 0;

/*dhcpcģ��ĵ��Լ�������*/
ULONG   g_aulDHCPDbgCnt[DHCP_MAX_FAILURE_COUNTER];

/*APN���õ�DHCP������UDPS���������*/
//AM_SLL_S                       g_stDhcpcUdpsSrvNumList;

/*  �ط���ʱ������ṹ*/
DLL_S                       g_astTimerLink[DHCPC_TMR_CIRCLE_TIME];

/*ȫ��UDPS����ű���*/
DHCPC_GLOBAL_UDPS_SRVNO_S   g_stDhcpcGlobalUdpsSrvNo;

/*��ʱ���ƿ�����*/
DHCPC_CTRLBLK_NODE          *g_pstDhcpCtrlBlkNodeArr;

/*DHCP ���ƿ���������*/
DHCPC_CTRLBLK               **g_pstDhcpcCtrlBlkRec = 0;
/* BEGIN: Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/9 */
/*DHCP ���ƿ���������for DHCPv6*/
DHCPC_CTRLBLK               **g_pstDhcpcIpv6CtrlBlkRec = NULL;
/* END:   Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/9 */

/*m00551573 ȫ�ļ�pclint 2012-10-11 start*/
//DHCPC_HASH_S    g_DHCPC_stHashTable;            /*IP HASH ��*/
/*m00551573 ȫ�ļ�pclint 2012-10-11 end*/

UCHAR           *g_pucDpeRightValAddr = NULL;   /*dpe ���ɷֵ���Ȩ��ֵ�׵�ַ*/
UCHAR           *g_pucDpeRightCountAddr = NULL;     /*SD ���ڸ��ɷֵ�ѡ��dpe�ļ���ֵ�׵�ַ*/

/*�������������Ƿ�������̽�ⶨʱ��id*/
RELTMR_T g_aulDhcpcSrvTimerId[DHCPGRP_MAX_NUM] = {0};

/* �澯���� */


 /*�澯ɨ�趨ʱ��ID */
ULONG g_ulDhcpcAlarmTimerID = 0;

/*dhcpcģ��ĵ��Դ�ӡ����*/
VOS_UINT32 g_ulDhcpDebug = 0;

/* Added start by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for ����ͳ�� */
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DiscoveryNumAddr =  VOS_NULL_PTR ; /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Discovery��Ϣ����*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4RequestNumAddr =  VOS_NULL_PTR ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Request��Ϣ����*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DeclineNumAddr =  VOS_NULL_PTR ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Decline��Ϣ����*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4ReleaseNumAddr =  VOS_NULL_PTR ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Releases��Ϣ����*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4OfferNumAddr =  VOS_NULL_PTR ;     /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Offer��Ϣ����*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4AckNumAddr =  VOS_NULL_PTR ;       /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Ack��Ϣ����*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4akNumAddr =  VOS_NULL_PTR ;        /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Nak��Ϣ����*/

/* Added end by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for ����ͳ�� */

/*���ƿ��ϻ����*/
ULONG  g_ulDhcpCtrlBlockAgingFlag = 0;

/*����������ʱ��¼��ǰ����������������*/
ULONG  g_ulDhcpcCurrentScanPdpIndex = 0;

/*����dhcp���ƿ�ʱ��¼��ǰ��hashkey*/
ULONG g_ulDhcpcCurrentScanHashKey = 0;

ULONG *g_DFT_pulDHCPSendCBNum = NULL;      /* DFT�ϱ�DHCP���Ϳ��ƿ���Ŀ */

/**********Dhcpc ��־ע��id***********/
ULONG g_ulDhcpcLogRecordRegId = 0;

UCHAR *g_pucDhcpPktBuf = VOS_NULL;

ULONG g_ulDhcpcSpuType = 0;

/* Added start by y00170683 at 2012-07-10 UGW10.0 for DHCPV6���� */
ULONG g_ulDhcpcBoardType = CRM_BOARD_TYPE_SPUD;
ULONG g_ulResendTimeout = 0;
/* Added end by y00170683 at 2012-07-10 UGW10.0 for DHCPV6���� */

