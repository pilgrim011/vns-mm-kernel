
/************************************************************************
 *                                                                      *
 *                             ppp_var.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/27                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPPģ��˽��ȫ�ֱ���������˵��                   *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������PPPģ�������˽��ȫ�ֱ�����Ӧ��˵��                  *
 *   �����κεط������ٳ��ֶ�˽��ȫ�ֱ�����extern����                   *
 *                                                                      *
 ************************************************************************/

#ifndef      _PPP_VAR_H_
#define      _PPP_VAR_H_


#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

extern PTM_COMPONENT_INFO_S g_stPppCompInfo;
extern VOS_UINT64 g_ullPppLocalL2tpCsi;        /* ����LAC���CSI */
extern VOS_UINT64 g_ullPppAuthCsi;              /* AUTH��CSI */
extern VOS_UINT64 g_ullPppFACsi;               /* FA��CSI */
extern VOS_UINT64 g_ullPppDiamAuthCsi;              /* AUTH��CSI */
extern PPP_NEGO_NODE_S  *g_pstPppPDNNegoList;
extern PPP_NEGO_NODE_S  *g_pstPppRPNegoList;

extern VOS_UINT64 g_ullPPPLAP2Csi;               /* LAP2��CSI */

extern VOS_UINT64 g_ullPppA11Csi ;           /* A11��CSI */




extern VOS_UINT32 g_ulPppDBGStatisc[];

extern VOS_UINT32 g_ulPppVsncpGetPCO;  /* �Ƿ��ȡPCO */

extern VOS_UINT32 g_ulStubDpeNo;
extern UCHAR g_ucStubDmpuId;

extern HTIMER g_ahNegoListTimeoutID[];
/*extern ULONG *g_ulPppFsmStat[5] ;*/ /* ��״̬����Ϣ���¼�ͳ�� */
extern VOS_UINT32 g_ulPppFsmStat[5][(VOS_UINT32)PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT]; /* ��״̬����Ϣ���¼�ͳ�� */

extern PPP_DEBUG_INFO_S g_pstPppInnerDebugInfo[] ;
extern PPP_DEBUG_INFO_S g_pstPppErrorDebugInfo[] ;

extern VOS_UINT32 g_ulPppA11NotifyQueID ;/* A11֪ͨPPP��Ϣ����*/
extern VOS_VOID* g_pstPppLAPNotifyQueID  ;/* LAP֪ͨPPP��Ϣ���� */
extern VOS_VOID* g_pstPppL2TPNotifyQueID ;/* PPP֪ͨL2TP��Ϣ���� */
extern VOS_VOID* g_pstL2TPPppNotifyQueID ;/* L2TP֪ͨPPP��Ϣ���� */

/* ��ַ�ͷŶ��� �����ڴ���Ϣ����*/
extern VOS_VOID* g_pstPppNegoQueID ;        /* Э�̱�����Ϣ���� */

extern VOS_UINT32 g_ulAuthPapOnoff;/*����PAP��Ȩ*/
extern VOS_UINT32 g_ulAuthChapOnoff;/*����CHAP��Ȩ*/

extern VOS_UINT32 g_ulPCompressOnoff;/*����Э����ѹ��Э��*/
extern VOS_UINT32 g_ulACompressOnoff ;/*���Ƶ�ַ��ѹ��Э��*/
extern VOS_UINT32 g_ulPppEchoRetransmit;
extern VOS_UINT32 g_ulPppEchoTimeout; /* ����ʱ*1000���ʾ10�� */

extern CHAR AuthMsgError[]  ;
extern CHAR AuthMsgSuccess[] ;

extern VOS_UINT32  *g_GTPC_pulPdpRejDueRes;
extern VOS_VOID* g_ulUSMSendLAP2ReqQueID;
extern VOID PPP_Shell_ReceiveDHCPPacket(USM_LAP2_MSG_S* pstMsg);



extern CHAR aucDataGram[];
extern VOS_UINT16 g_usPppVjUserNUm[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];    /*VJѹ���û���,���ڵ���ͳ��*/
extern VOS_UINT16 g_usPppMppcUserNum[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];  /*Mppcѹ�����û���,���ڵ���ͳ��*/
extern VOS_UINT32 g_ulMaxDmpuDpeCpuRate ;                 /* �������DPE��CPUռ���� */
extern VOS_UINT32 g_ulMinDmpuDpeCpuRate ;                 /* �������DPE��CPUռ���� */
extern VOS_UINT32 g_ulDmpuDpeCpuRate[MAX_DMPU_NUM * MAX_DPE_NUM_PDSN];
extern VOS_UINT32 g_ulDmpuDpeNumber[MAX_DMPU_NUM];

extern VOS_UINT32 g_ulLastSelDmpuDpe ;                    /* �ϴ�ѡ���DPE */
extern VOS_UINT32 g_ulPppReNegIndex ;                     /* ���ڼ�¼��ǰ��Э�̵��û����� */
extern VOS_UINT32 g_ulDmpuCpuThreshold;                 /* �ӿ�CPUռ�������� */
extern VOS_UINT32 g_ulPppDiamAaaQueID;      /* AUTH��Ϣ���� */
extern VOS_UINT8  g_ucUdpCheckSumFlag ; /*udp checksum ���*/
extern VOS_UINT32 *g_aulDoStatiscTime;
extern VOS_UINT32 *g_aulNoStatiscTime;

extern LINKTCB_S        g_pstLocalLinkTcb[];

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
extern PPPC_HDLC_STRU   g_astHdlcPool[];
#endif

/* PPP�ڲ���ά�ɲ⹴����Ϣ�洢 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppInterMntnInfo;

/* PPP��CDS������ά�ɲ⹴����Ϣ�洢 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppCdsMntnInfo;

/* PPP��RLP������ά�ɲ⹴����Ϣ�洢 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppRlpMntnInfo;

/* extern PPPINFO_S        *g_astPppPool; */
extern PPPINFO_S        g_astPppPool[];

/* extern PPPLCPINFO_S     *g_astPppLcpPool ; */
extern PPPLCPINFO_S     g_astPppLcpPool[];

/* extern PPPIPCPINFO_S    *g_astPppIpcpPool; */
extern PPPIPCPINFO_S    g_astPppIpcpPool[];

/* extern PPPPAPINFO_S     *g_astPppPapPool ; */
extern PPPPAPINFO_S     g_astPppPapPool[] ;

/* extern PPPCHAPINFO_S    *g_astPppChapPool; */
extern PPPCHAPINFO_S    g_astPppChapPool[];

/* extern PPP_CCP_INFO_S   *g_astPppCcpPool ; */
extern PPP_CCP_INFO_S   g_astPppCcpPool[] ;

/* extern PPPCONFIGINFO_S  *g_astPppConfifPool; */
extern PPPCONFIGINFO_S  g_astPppConfifPool[];

extern PPP_NEGO_NODE_S  *g_pstPppNegoList;
/* extern PPPIPV6CPINFO_S  *g_astPppIpv6cpPool; */
extern PPPIPV6CPINFO_S  g_astPppIpv6cpPool[];

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
/* extern PPPC_EAP_INFO_STRU     *g_astPppEapPool; */
extern PPPC_EAP_INFO_STRU     g_astPppEapPool[];

#endif
extern PPPA11_AlarmLink_HEAD_S g_stPppA11AlarmLink;
extern PPP_FAIL_COUNTER g_stPPPFailCounter;
extern VOS_UINT32 ulOneSecondTimer;
extern PPPFSMCALLBACK_S g_stVsncpCallbacks;
extern VOS_UINT32 g_ulPPPTaskId;
#ifdef __PRODUCT_TYPE_PDSN80
extern VOS_UINT32 g_ulPppLicenseQueID;/* License��Ϣ���� */
#endif
/* extern VSNCP_OPTION_DECODE *g_pVsncpOptionDecode; */
extern VSNCP_OPTION_DECODE g_pVsncpOptionDecode[];

extern VSNP_CONIFG_OPTION_FLAG_S g_stVsncpOptionFlag;
/* extern VSNCP_OPTION_ENCODE *g_pVsncpOptionEncode; */
extern VSNCP_OPTION_ENCODE g_pVsncpOptionEncode[];


extern VOS_UINT32 g_ulPppNegoQueID ;     /* Э�̱�����Ϣ���� */
extern VOS_UINT32 g_ulPppCompressQueID ;

 /* PPP��־���� */
extern VOS_UINT32 g_ulPppLogLevelErr;
extern VOS_UINT32 g_ulPppAaaQueID;/* AUTH��Ϣ���� */
extern VOS_UINT32 g_ulPppDhcpQueID;/* DHCP��Ϣ���� */
extern VOS_UINT32 g_ulPppPcrfcQueID;
extern VOS_UINT32 g_ulPppTimeQueID;/* ��ʱ����Ϣ���� */
extern VOS_UINT32 g_ulPppCcpQueID;       /* ѹ��������Ϣ���� */ /*WGGSN_B03_L2TP_PPPC_COMP*/
extern VOS_UINT32 g_ulPppGspcQueID;     /* ����GSPC IPC��Ϣ���� *//* Added by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
extern LONG g_ulPppL2tpMaxUserNum; /* L2TP����û��� */
extern LONG g_ulPppCcpMaxUserNum;
extern LONG g_ulPppVjMaxUserNum;
extern VOS_UINT32 g_ulPPPLapFlowctrl;
extern VOS_UINT32 g_ulPPPA11Flowctrl;
extern VOS_UINT32 g_ulPPPTimerFlowctrl;
extern VOS_UINT32 g_ulPPPAAAFlowctrl;
extern VOS_UINT32 g_ulPPPNegoFlowctrl;
extern VOS_UINT32 g_ulPPPPcrfcFlowCtrl;

extern VOS_UINT32 g_ulPPPTmpTaskFlowCtrl;
extern VOS_UINT32 g_ulPppInnerMsgQueID;     /* added by luofang ��ʱ������Ϣ���� */
/* ���ƿ�����ָ�� */
/* debug����ʹ�õı��� */
extern struct tagPppDebugInfo g_stPppDebugInfo ;

/* debugʹ�õı��������� */

extern CHAR *g_cPPP_Debug_Protocol_Name[];
extern CHAR *g_cPPP_Debug_code[];
extern CHAR *g_cPPP_Debug_state[];
extern CHAR *g_cPPP_Debug_event[];
extern CHAR *g_cPPP_Debug_LcpOption[];
extern CHAR *g_cPPP_Debug_IpcpOption[] ;
/*------------- ����ͳ��ʹ�õ�ȫ�ֱ��� -------------*/
extern PPPPERFSTATISTIC_S g_stPppPerfStatistic;
extern IPV6PERFSTATISTIC_S g_stIpv6PerfStatistic;
extern VOS_UINT32 g_aulIpv6Cnt[];

/*------------- �ڲ�����ʹ�õ�ȫ�ֱ��� -----------------*/
extern IMSI_S g_stPppDebugImsi;        /* ���û�����IMSI��Ϣ*/

/*------------- ���ݵ���ģ���ȫ�ֱ��� -----------------*/
extern UCHAR g_ucPppBkpFailFlg;            /* ���ݹ���״̬��־,1ʧ��,0�ɹ� */
extern VOS_UINT32 g_ulPppRoutineBkpCurIndex;           /* ��ǰ���ƿ�����*/
extern VOS_UINT32 g_ulPppRoutineBkpHeadIndex;          /* ͷ���ƿ�����*/
extern PPP_CHANGEDINFO_BKP_S*    g_stPppChangedInfoBkp;
extern VOS_UINT32 g_ulPppBackupTID;
extern VOS_UINT32 ulDealedNum;
extern VOS_UINT32 g_ulBackupControl;
extern VOS_UINT16 g_usPppLzs0UserNum;  /*LZS0ѹ���û���*/
extern VOS_UINT16 g_usPppLzs1UserNum; /* LZS1ѹ���û��� */
extern VOS_UINT8 g_ucPppCcpSwitch;
extern VOS_UINT8 g_ucPppCcpType;
extern VOS_UINT8 g_ucPppVjSwitch;
extern VOS_UINT16 * g_pusPppL2tpCallId;
extern PPP_CFG_INFO_REC_S g_stPppCfgInfo;
extern VOS_UINT32 g_ppp_ulTempLapBatchDelteTaskID2;
extern VOS_UINT32 g_ulLapReportTID;

extern VOS_UINT32 g_ulPppTaskTrace;

extern  struct Command_Group_S PppCommandGroup;
extern VOS_UINT32 g_ulPppDebugSwitch;

/* extern UCHAR *g_ucPppSendPacketHead; */
extern UCHAR g_ucPppSendPacketHead[];

/* extern UCHAR *g_ucPppRcvPacketHead; */
extern UCHAR g_ucPppRcvPacketHead[];




/* ��������PPP����� */
extern VOS_UINT32 g_ulSoftPara534;
extern VOS_UINT32 g_ulSoftPara562;
extern VOS_UINT32 g_ulSoftPara567;
extern VOS_UINT32 g_ulSoftPara571;
extern VOS_UINT32 g_ulSoftPara577;
extern VOS_UINT32 g_ulSoftPara537;
extern VOS_UINT32 g_ulSoftPara585;
extern VOS_UINT32 g_ulSoftPara586;
extern VOS_UINT32 g_ulSoftPara587;




extern VOS_UINT32 g_ulReNegoTaskId;
extern VOS_UINT32 g_ulPppAAAWritelogFlag;
extern VOS_UINT32 g_ulLap1RebuildingFlag;

extern VOS_UINT32 g_ulMaxVJNum;

extern VOS_UINT32 g_ulSpuId;        /* ��SPU���߼���� */
/*��ǰspu������*/
extern CRM_SPU_BOARD_TYPE_ENUM g_enPppBoardType;

extern VOS_UINT32 g_ulPPPL2tpFlowctrl;

extern UCHAR g_ucPppSendPacketHead[PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER];


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



