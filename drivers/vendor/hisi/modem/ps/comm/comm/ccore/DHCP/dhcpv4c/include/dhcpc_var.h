/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Dhcpc_var.h
  �� �� ��   : ����
  ��    ��   : caopu
  ��������   : 2008��7��16��
  ����޸�   :
  ��������   : Dhcpc_var.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��16��
    ��    ��   : caopu
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __DHCPC_VAR_H__
#define __DHCPC_VAR_H__


extern ULONG   g_ulCtrlblkXaxis;
extern ULONG   g_ulCtrlblkYaxis;

extern VOID    *g_pulSDDhcpMCQueID        ;
extern VOID    *g_pulSDDhcpv6cMcQueId;
extern VOID    *g_pulDHCP_LAP2_RSPQueID   ;
extern VOID    *g_pulDHCP_LAP2_REQQueID   ;

extern ULONG   g_ulDhcpcTaskId            ;
extern RELTMR_T   g_ulDhcpcRenewTimerID      ;
extern RELTMR_T   g_ulDhcpcRetransTimerID    ;
extern RELTMR_T   g_ulDhcpcCtrlBlockAgingTimerID;
extern RELTMR_T g_ulDhcpcSeqnumAgingTimerID;
extern ULONG   g_ulDhcpcTimerQid          ;
extern ULONG   g_ulDhcpcServerQid         ;
extern ULONG   g_ulCurrDHCPCCtlIndex      ;    /*���ö�ʱ��Ŀǰ������û�DHCP���ƿ�����*/
extern ULONG   g_ulTimerRenewType         ;    /*���ö�ʱ������*/
extern ULONG   g_ulCurrProcIndex          ;    /*�ط���ʱ����ǰ����������index*/
extern ULONG   g_ulTimerRetransType       ;    /*�ط���ʱ������*/
extern ULONG   g_ulDHCPCTransId           ;    /*Xid����ʼֵ*/
extern ULONG   g_ulDhcpcGlbLeaseTime      ;    /*ȫ�����õ�IP��Чʱ��ȫ�ֱ���*/
extern ULONG   g_ulDHCPCDbgPkt            ;
extern ULONG   g_ulDhcpcInnerQid;
/*dft���Ϳ��ƿ鶨ʱ��ID*/
extern ULONG   g_uldftDhcpcSendCBTimerID;

extern ULONG *g_DFT_pulDHCPSendCBNum;      /* DFT�ϱ�DHCP���Ϳ��ƿ���Ŀ */

/*APN���õ�DHCP������UDPS���������*/
//extern AM_SLL_S                       g_stDhcpcUdpsSrvNumList;  

/*  �ط���ʱ������ṹ*/
extern DLL_S                       g_astTimerLink[DHCPC_TMR_CIRCLE_TIME]; 

/*ȫ��UDPS����ű���*/
extern DHCPC_GLOBAL_UDPS_SRVNO_S   g_stDhcpcGlobalUdpsSrvNo;

/*��ʱ���ƿ�����*/
extern DHCPC_CTRLBLK_NODE          *g_pstDhcpCtrlBlkNodeArr;

/*DHCP ���ƿ���������*/
extern DHCPC_CTRLBLK               **g_pstDhcpcCtrlBlkRec;

/*m00551573 ȫ�ļ�pclint 2012-10-11 start*/
//extern DHCPC_HASH_S    g_DHCPC_stHashTable;         /*IP HASH ��*/
/*m00551573 ȫ�ļ�pclint 2012-10-11 end*/

extern UCHAR           *g_pucDpeRightValAddr;       /*dpe ���ɷֵ���Ȩ��ֵ�׵�ַ*/
extern UCHAR           *g_pucDpeRightCountAddr;     /*SD ���ڸ��ɷֵ�ѡ��dpe�ļ���ֵ�׵�ַ*/

extern RELTMR_T g_aulDhcpcSrvTimerId[DHCPGRP_MAX_NUM];
extern ULONG g_ulDhcpDebug;
extern ULONG g_aulDHCPDbgCnt[DHCP_MAX_FAILURE_COUNTER];
/* Added start by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for ����ͳ�� */
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DiscoveryNumAddr ; /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Discovery��Ϣ����*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4RequestNumAddr ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Request��Ϣ����*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DeclineNumAddr ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Decline��Ϣ����*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4ReleaseNumAddr ;   /*����ͳ��PGW���͸�DHCP Server��DHCPV4 Releases��Ϣ����*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4OfferNumAddr ;     /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Offer��Ϣ����*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4AckNumAddr ;       /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Ack��Ϣ����*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4akNumAddr ;        /*����ͳ��PGW���յ�DHCP Serverʼ����DHCPV4 Nak��Ϣ����*/

/* Added end by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for ����ͳ�� */
extern UCHAR g_ucSoftParaDHCPKPN;

extern ULONG g_ulDhcpCtrlBlockAgingFlag;

extern ULONG g_ulDhcpcCurrentScanPdpIndex;

extern ULONG g_ulDhcpcCurrentScanHashKey;

extern ULONG g_ulDhcpcLogRecordRegId;

/* �澯���� */

 /*�澯ɨ�趨ʱ��ID */
extern ULONG g_ulDhcpcAlarmTimerID;

extern UCHAR *g_pucDhcpPktBuf;

/* BEGIN: Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/9 */
extern DHCPC_CTRLBLK **g_pstDhcpcIpv6CtrlBlkRec;
/* END:   Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/9 */

extern ULONG g_ulDhcpcSpuType;

/* Added start by y00170683 at 2012-07-10 UGW10.0 for DHCPV6���� */
extern ULONG g_ulDhcpcBoardType;
extern ULONG g_ulResendTimeout;
/* Added end by y00170683 at 2012-07-10 UGW10.0 for DHCPV6���� */

#endif /* __DHCPC_VAR_H__ */
