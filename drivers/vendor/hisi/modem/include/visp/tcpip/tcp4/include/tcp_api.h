/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_api.h
*
*  Project Code: VISPV1R7
*   Module Name: TCP_API  
*  Date Created: 2008-03-07
*        Author: zhengsenhuo(00104483)
*   Description:  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*   2008-03-07  Zheng SenHuo           Creat the first version.
*   
*******************************************************************************/


#ifndef        _TCP_API_H
#define        _TCP_API_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*[Debug Flag]*/
#define TCP_DEBUG_PACKET    0x01
#define TCP_DEBUG_TRANSA    0x10 
/* Extend debug function for MD5 option, 2002,09,25, zhangfeng */
#define TCP_DEBUG_MD5       0x0100

#define TCP_DEBUG_OFF   0
#define TCP_DEBUG_ON    1

/*TCPģ�������*/
enum tagTCP_ErrCode
{
    TCP_FILTOK = VOS_OK,
    TCP_FAILURE,

    TCP_FILTNOTFOUND,      /* 2 û�ҵ�Ҫɾ���Ĺ���       */
    TCP_FILTNONE,          /* 3 ������Ѿ��������       */
    TCP_FILTTOOMUCH,       /* 4 �������                 */
    TCP_FILTINUSE,         /* 5 ָ���Ĺ����Ѿ������ù��� */
    TCP_FILTADD,           /* 6 �����һ������           */
    TCP_COMP_NULL,         /* 7 TCP���δע��            */
    TCP_PARA_ERR,          /* 8 ���������Χ�Ƿ�         */
    TCP_PARATYPE_ERR,      /* 9 ��������ͷǷ�           */
    TCP_INPUT_NULL_POINT,  /* 10 �����ָ�� */
    TCP_ERR_NULL_INPCB,    /* 11 INPCBָ��Ϊ�� */
    TCP_ERR_NULL_SOCKET,   /* 12 ��ȡSOCKET���ƿ�ָ��Ϊ�� */
    TCP_ERR_NULL_TCPCB,    /* 13 ��ȡTCPCP�ṹָ��Ϊ�� */
    TCP_ERR_GETSTAT_INPCB,     /* 14 ������Ԫ���ȡINPCBʧ�� */
    TCP_ERR_GETSTAT_SOCKETCB,  /* 15 ������Ԫ���ȡSOCKETCBʧ�� */
    TCP_ERR_GETSTAT_TCPCB,     /* 16 ������Ԫ���ȡTCPCBʧ�� */

    TCP_NETINFO_FINISH,        /* 17 TCPNetInfo ��ѯ���� */
    TCP_GETINPCB_WRONG,        /* 18 ��ȡ�õ���INPCBΪ�� */

    /*Added by wangtong207740, ����socket id ��ȡ��Ӧ��tcp����ͳ��, 2012/9/5 */
    TCP_NOT_GLOBAL_SOCKET,      /* 19 ��֧�ַ�ȫ��SOCKET���� */

    TCP_ERR_MAX,
};

/* Added by y00171195/p00193127 for TCPNetInfo TCP״̬�� */
enum tagTCP_StateCode
{
    TCPSTATE_CLOSED        = 0,   /* closed */
    TCPSTATE_LISTEN        = 1,   /* listening for connection */
    TCPSTATE_SYN_SENT      = 2,   /* active, have sent syn */
    TCPSTATE_SYN_RECEIVED  = 3,   /* have send and received syn */
    TCPSTATE_ESTABLISHED   = 4,   /* established */
    TCPSTATE_CLOSE_WAIT    = 5,   /* rcvd fin, waiting for close */
    TCPSTATE_FIN_WAIT_1    = 6,   /* have closed, sent fin */
    TCPSTATE_CLOSING       = 7,   /* closed xchd FIN; await FIN ACK */
    TCPSTATE_LAST_ACK      = 8,   /* had fin and close; await FIN ACK */
    TCPSTATE_FIN_WAIT_2    = 9,   /* have closed, fin is acked */
    TCPSTATE_TIME_WAIT     = 10,  /* in 2*msl quiet wait after close */
};

/*set/get SYN/FIN/WIN*/
#define TCP_FUNSPEC_CHGKEEPVAL          0
#define TCP_FUNSPEC_CHGKEEPFINTIME      1
#define TCP_FUNSPEC_WINSIZE             2
#define TCP_FUNSPEC_ESTABLISHED         3
/*Added by y00216869 for DTS2016080205624 :ͬ��c70��������balong��Ʒ����֧��2msl������ , 2016/8/03 */
#define TCP_FUNSPEC_DEFMSL              4
/*End added by y00216869 for DTS2016080205624 :ͬ��c70��������balong��Ʒ����֧��2msl������ , 2016/8/03 */

/* TCPͳ�ƽṹ */
typedef struct tagTCPSTAT
{
    ULONG    ulAccepts;
    ULONG    ulClosed;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;
    ULONG    ulPCBCacheMiss;

    /* Added by LQZ, Mar-26 97. */
    ULONG    ulPersistDrops;

    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvBadOff;
    ULONG    ulRcvBadSum;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvShort;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;

    ULONG    ulSndRST;   /* Added for MIB-II */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    /* added by mayun to distinguish con_estab timer and keepalive timer */
    ULONG    ulKeepAliveTimeOut;  /*·�������ʱ����ʱ����*/
    ULONG    ulKeepAliveDrops;    /*����̽��ʧ�ܶ������Ӵ���*/

    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;
    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

    /* Added for tcp ha */
    ULONG ulSeqRcvNxtRevised; /* Times that seqRcvNxt has been revised */

    /* Added for notification failure */
    ULONG    ulNotifyReadFailed;
    ULONG    ulNotifyWriteFailed;
    ULONG    ulNotifyPeerCloseFailed;
    ULONG    ulNotifyKeepLiveDownFailed;
    ULONG    ulNotifyConnectFailed;

    /* Added by fengjing209023 cookieά�� */
    ULONG    ulCookieRcvdSyn;       /* cookie��ʱ�յ���SYN������ */
    ULONG    ulCookieRspdSynAck;    /* cookie��ʱ�ص�SYNACK������ */
    ULONG    ulCookieRcvdAck;       /* cookie��ʱ�յ���ACK������ */
    ULONG    ulCookiePassedAck;     /* cookie��ʱУ��ɹ���ACK������ */
    ULONG    ulCookieTimoAck;       /* cookie��ʱУ��ʧ�ܵ�ACK������(��ʱ) */
    ULONG    ulCookieBadMssAck;     /* cookie��ʱУ��ʧ�ܵ�ACK������(MSS��������) */
    ULONG    ulCookieOtherPkt;      /* cookie��ʱ����socket�յ����������� */
    ULONG    ulUsrCookieOnWhenTIMO; /* cookie��ʱ�յ���ACK���ĳ�ʱ�����ǲ�ƷCOOKIE���� */
    
    ULONG    ulRecvMemDrop;        /* �ڴ治�㶪���ı����� */
} TCPSTAT_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ����������ݽṹ */
typedef struct tagTCP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF����*/
    ULONG    ulLAddr;       /* ���˵�ַ(������) */
    ULONG    ulFAddr;       /* �Զ˵�ַ(������) */
    ULONG    ulLPort;       /* ���˶˿ں� */
    ULONG    ulFPort;       /* �Զ˶˿ں� */
    ULONG    ulSocketID ; /*��socket idָ��ʱ����socket����ͳ����Ϣ��*/
    /* ��������Ԫ�飬����ΪTCPDORP��INPCB����ɾ��������ڸ������ȻҪ��socketid��ȡ */
    ULONG    ulTaskID;      /* ����ID */
}TCP4CONN_S;

/* ����socket id task id ����Ԫ���TCPͳ�ƽṹ */
typedef struct tagTCP4PERSTAT
{
    TCP4CONN_S stTcp4Conn; /* ʵ�ʻ�ȡ��socket id task id ����Ԫ��*/    
    
    ULONG    ulAccepts;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;

    ULONG    ulPersistDrops;
    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;

    ULONG    ulSndRST;   /* Added for MIB-II */
    ULONG    ulSndSYN;   /* Added for Qos Info */
    ULONG    ulSndFIN;   /* Added for Qos Info */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    ULONG    ulKeepAliveTimeOut;  /*·�������ʱ����ʱ����*/
    ULONG    ulKeepAliveDrops;    /*����̽��ʧ�ܶ������Ӵ���*/

    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;

    /*socket ��������Ϣ*/
    ULONG    ulSndHiWat ; /*���ͻ�������ˮλ*/
    ULONG    ulRcvHiWat ; /*���ջ�������ˮλ*/
    ULONG    ulSndCC ; /*���ͻ�������ʵ������ */
    ULONG    ulRcbCC ; /*���ջ�������ʵ������ */

    ULONG    ulSubSOTimeODrops;      /* number of subsocket droped because of timeout */
    ULONG    ulSubSoBacklogDrops;    /* number of subsocket droped because of exceeding backlog */  
} TCP4PERSTAT_S;

typedef struct tagTcpSockInfo
{
    ULONG    ulLocalAddr;          /*���˵�ַ ����˳��*/
    ULONG    ulPeerAddr;           /*�Զ˵�ַ ����˳��*/
    USHORT   usLocalPort;          /*���˶˿ں� ����˳��*/
    USHORT   ulPeerPort;           /*�Զ˶˿ں� ����˳��*/

    ULONG    so_sOptions;            /*socketѡ��*/
    ULONG    so_sState;              /*tcp ״̬*/

    SHORT    so_sLinger;             /*Linger ֵ */
    SHORT    so_sQ0Len;         /* δ��������Ӹ���*/
    SHORT    so_sQLen;          /* �Ѿ����Ӹ��� */
    SHORT    so_sQLimit;        /* tcp ������Ӹ��� */

    ULONG    ulDelayedAck;        /*�ӳٷ��͵�ACK��������*/
    ULONG    ulRcvAckByte;        /*���յ��ֽ���*/
    ULONG    ulRcvAckPacket;      /*�յ���ACK��������*/
    ULONG    ulRcvAfterClose;     /*�رպ���յı��ĸ���*/    
    ULONG    ulRcvPacketAfterWnd; /*�������ڽ��մ�������*/
    ULONG    ulRcvPartDupPacket;  /*�����ظ���������*/
    ULONG    ulRcvOutOrderPacket; /*������������*/
    ULONG    ulRcvTotal;          /*�ܼ��յ�������*/
    ULONG    ulRcvPacket;         /*��˳�򵽴ﱨ������*/
    ULONG    ulRexmtTimeOut;      /*�ش���ʱ����ʱ����*/
    ULONG    ulSndByte;           /*���͵ı����ֽ���*/
    ULONG    ulSndPacket;         /*���͵����ݱ���*/
    ULONG    ulSndAcks;           /*����ACK������*/
    ULONG    ulSndRexmtPacket;    /*�����ط�����*/
} TCP_SOCK_INFO_S;



#define TCP_MAXFILTNUM      5

typedef struct tagTCPFILT
{
    ULONG   ulTaskId;        /* ����û����õĹ��������е�����ID   */
    ULONG   ulSockId;        /* ����û����õĹ��������е��׽ӿں� */
}TCPFILT_S;

typedef struct tagTCPDBUGFILTRD
{       
    TCPFILT_S stTCPDbugFilt[TCP_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* ��ǰ���������ĸ��� */
}TCPDBUGFILTRD_S;


typedef ULONG   TCP_SEQ;

/* TCPͷ���ݽṹ */
typedef struct tagTCPHDR
{
    USHORT  usSrcPort;
    USHORT  usDstPort;
    TCP_SEQ                 seqSeqNumber;
    TCP_SEQ                 seqAckNumber;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucX2:4,
                    ucOffset:4;
#else
    UCHAR   ucOffset:4, /* warning:nonstandard extension used : bit field types other than LONG. */
                    ucX2:4;     /* warning:nonstandard extension used : bit field types other than LONG. */
#endif
    UCHAR   ucFlags;
    USHORT      usWnd;
    USHORT      usCheckSum;
    USHORT      usUrgentPoint;
} TCPHDR_S;

typedef struct tagTCPIP_TCPNETINFO_S
{
    ULONG   ulTaskId;       /* ����ID     */
    ULONG   ulSrcIp;        /* �����ֽ��� */
    ULONG   ulDstIp;        /* �����ֽ��� */
    USHORT  usSrcPort;
    USHORT  usDestPort;
    USHORT  usState;
    USHORT  usRes;
    /*Added by limin00188004, ��ȡ����״̬ʱ���socket���󶨵�VRF����, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
    ULONG   ulVrfIndex;
    /* End of Added by limin00188004, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
}TCPIP_TCPNETINFO_S;

/* COOKIE��Կ, 136���ֽڳ��� */  
typedef ULONG ( *gpfTCPIPGetCookieSecret)(ULONG* pulCookieValue, ULONG ulBytesNum); 

/* ��ȡ��ƷCOOKIE���ع��ӣ�����1��ʾ��Ʒ�򿪣�0��ʾ��Ʒ�ر�*/
typedef ULONG ( *gpfTCPIPGetUsrCookieSwitch)(ULONG* pulCookieSwitch);

/* Structure used as input parameter for hook function to notify TCP MD5
   configuration. */
typedef struct tagTCP4MD5CFGNOTIFY 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulOper;           /* Add: 1 or Del: 0 */ 
} TCP4MD5CFGNOTIFY_S;
/* Structure used as input parameter for hook function to notify TCP MD5
   authentication result. */
typedef struct tagTCPMD5AUTHRESULT 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulResult;         /* permit: 1 or deny: 0 */ 
} TCP4MD5AUTHRESULTNOTIFY_S; 
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   configuration. */
typedef ULONG ( *gpfTCPIPMd5CfgNotifyHook)(TCP4MD5CFGNOTIFY_S* pstCfgPara);
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   authentication result. */
typedef ULONG ( *gpfTCPIPMd5AuthNotifyHook)(TCP4MD5AUTHRESULTNOTIFY_S* pstAuthResult);

/*******************************************************************************
*    Func Name: TCPIP_ShowTcpStatistic
*  Description: ��ʾTCP4ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ShowTcpStatistic(VOID);
/****************************************************************************
*    Func Name: TCPIP_ShowTCPCB()
*  Description: ��ʾTCP4���ƿ���Ϣ
*        Input: VOID *pAddress: TCP���ƿ����ڵĵ�ַ
*       Output: ��
*       Return: ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ShowTCPCB(VOID *pAddress);
/*******************************************************************************
*    Func Name: TCPIP_ShowTCP
*  Description: ��ʾTCP4��������Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ShowTCP(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetTCPStat
*  Description: ���TCP4�����ͳ����Ϣ
*        Input: 
*       Output: TCPSTAT_S *pstTCPStat:ָ��ṹ��TCPSTAT_S��ָ�롣����ָ����ڴ����û�����������ͷ�
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetTCPStat(TCPSTAT_S *pstTCPStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrTCPStat
*  Description: ���TCP4�����ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ClrTCPStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugTCPAll
*  Description: ���TCP4 DEBUG��ǲ�������ֵ����
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_NoDebugTCPAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DebugTCPAll
*  Description: ������TCP4 DEBUG����
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_DebugTCPAll(VOID);
/****************************************************************************
*    Func Name: TCPIP_SetTCPDbgFilter()
*  Description: ��/�ر�ָ��socket id��task id��TCP4 debug����
*        Input: ULONG ulFlag        ������
*               ULONG ulDbgFilterId ��������
*               ULONG ulTaskId      socket���ڵ�����ID
*               ULONG ulSockId      �׽���ID
*       Output: ��
*       Return: TCP_FILTOK          �����ɹ�
*               TCP_FILTNOTFOUND    û�ҵ�Ҫɾ���Ĺ���
*               TCP_FILTNONE        ������Ѿ��������
*               TCP_FILTTOOMUCH     �������
*               TCP_FILTINUSE       ָ���Ĺ����Ѿ������ù���
*               TCP_FILTADD         �����һ������
*               VOS_ERR             ����ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
LONG TCPIP_SetTCPDbgFilter(ULONG ulFlag, ULONG ulDbgFilterId, ULONG ulTaskId, ULONG ulSockId);
/*******************************************************************************
*    Func Name: TCPIP_SetTCPRespondQuench
*  Description: �����Ƿ���ӦTCPԴ���Ʊ���
*        Input: ULONG ulSetYes:0  ����Ӧ   ��0  ��Ӧ
*       Output: ��
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetTCPRespondQuench(ULONG ulSetYes);
/****************************************************************************
*    Func Name: TCPIP_GetTCPParam()
*  Description: ��ȡTCP4���ȫ�ֱ���ֵ
*        Input: ULONG ulType     ȫ�ֱ�������
*               
*       Output: ULONG * pulValue ���ص�ǰȫ�ֱ�����ֵ
*       Return: ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_GetTCPParam(ULONG ulType, ULONG * pulValue);
/****************************************************************************
*    Func Name: TCPIP_SetTCPParam()
*  Description: ����TCP4���ȫ�ֱ���ֵ
*        Input: ULONG ulType     ȫ�ֱ�������
*               ULONG * pulValue Ҫ���õ�ֵ
*       Output: ��
*       Return: VOS_OK          �����ɹ�
*               VOS_ERR         ���ڵ�����ƽ��
*               TCP_PARAMERROR  ��������
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetTCPParam(ULONG ulType, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTCPDbgFilter
*  Description: ��ȡTCP4 DEBUG��ʶ�͹������ֵ,������MD5������Ϣ
*        Input: ULONG *pulDebugFlag:����TCP Debug��ʶ
*               TCPDBUGFILTRD_S *pstPacketFilter:���ص�TCP���Ĺ���ֵ
*               TCPDBUGFILTRD_S *pstEventFilter:���ص�TCP״̬����ֵ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_GetTCPDbgFilter(ULONG *pulDebugFlag, TCPDBUGFILTRD_S *pstPacketFilter, TCPDBUGFILTRD_S *pstEventFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetTCPDbgFilterWithMd5
* Date Created: 2009-12-2
*       Author: zhangchunyu(62474)
*  Description: ��ȡTCP4 DEBUG��ʶ�͹������ֵ,����MD5������Ϣ
*        Input: ULONG *pulDebugFlag:����TCP Debug��ʶ
*               TCPDBUGFILTRD_S *pstPacketFilter:���ص�TCP���Ĺ���ֵ
*               TCPDBUGFILTRD_S *pstEventFilter:���ص�TCP״̬����ֵ
*               TCPDBUGFILTRD_S *pstMD5Filter:���������˵�MD5
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-2    zhangchunyu(62474)     Create the first version.
*
*******************************************************************************/
VOID TCPIP_GetTCPDbgFilterWithMd5(ULONG *pulDebugFlag, 
                                  TCPDBUGFILTRD_S *pstPacketFilter,
                                  TCPDBUGFILTRD_S *pstEventFilter,
                                  TCPDBUGFILTRD_S *pstMD5Filter);

typedef ULONG (*TCPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncTCPInputHook( TCPINPUT_HOOK_FUNC pfFuncHook );
extern TCPINPUT_HOOK_FUNC g_TCP_Input_HookFunc;

#define TCP_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define TCP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define TCP_PROCESSED_BY_INTERMEDIATE                  2

/*******************************************************************************
*    Func Name: TCPIP_GetPerTcp4ConnStats
* Date Created: 2009-12-25
*       Author: Gexianjun/h00121208
*  Description: ָ��socket id, task id��ָ����Ԫ�飬VRF��ȡָ����TCPͳ����Ϣ
*        Input: TCP4CONN_S *pstConnInfo:    ��ȡָ��TCP Socket�������
*       Output: TCP4PERSTAT_S *pstRetStats: ��ȡָ����TCPͳ����Ϣ
*       Return: �ɹ�:VOS_OK;ʧ��:������
*      Caution: ���socket��ģʽ��ȫ��socket,����socket id��ȡtcpͳ����Ϣ,����Ҫָ��task id;
*               ������Ҫͬʱָ��socket id��task id�����ӿڻ�ȡTCPͳ����Ϣ�������������Բ�����ȷ
*               ��ȡ:�����������Ϊsocket id + task idȥ��ȡ;���������Ϊ��Ԫ��+vrfȥ��ȡ��
*               Ҳ����ͬʱָ����������ϡ���ȡ�������ȸ���socket id +task idȥ��ȡ,
*               �����ȡʧ��,�ٸ�����Ԫ��+vrfȥ��ȡ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-25   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo, TCP4PERSTAT_S *pstRetStats);

/*******************************************************************************
*    Func Name: TCPIP_ResetPerTcp4ConnStats
* Date Created: 2009-12-25
*       Author: Gexianjun/h00121208
*  Description: ָ��socket id, task id��ָ����Ԫ�飬VRF���ָ����TCPͳ����Ϣ
*        Input: TCP4CONN_S *pstConnInfo: ���ָ��TCP Socket�������
*       Output: 
*       Return: �ɹ�:VOS_OK;ʧ��:������
*      Caution: ���socket��ģʽ��ȫ��socket,����socket id���tcpͳ����Ϣ,����Ҫָ��task id;
*               ������Ҫͬʱָ��socket id��task id�����ӿ����TCPͳ����Ϣ�������������Բ�����ȷ
*               ���:�����������Ϊsocket id + task idȥ���;���������Ϊ��Ԫ��+vrfȥ�����
*               Ҳ����ͬʱָ����������ϡ�����������ȸ���socket id +task idȥ����tcp socket, ���
*               ���ҳɹ�,�����ָ���ĸ�tcp socket��ͳ����Ϣ,�������ʧ��,�ٸ�����Ԫ��+vrfȥ����tcp socket,
*               ������ҳɹ�,�����ָ���ĸ�tcp socket��ͳ����Ϣ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-25   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo);

/*******************************************************************************
*    Func Name: TCPIP_OpenTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: �򿪲�ѯ���
*        Input: 
*       Output: pulWaitlist:Waitlist���
*       Return: �ɹ�:VOS_OK;ʧ��:������
*      Caution: ֻ�в�ѯ����򿪳ɹ����ܽ�����һ��TCP����������Ϣ��ѯ������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenTcpNetInfo(UINTPTR *pulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: ��ȡTCP����������Ϣ
*        Input: pulWaitlist:Waitlist���
*       Output: TCPIP_TCPNETINFO_S*pstNetInfo����������Ϣ
*       Return: �ɹ�:VOS_OK;ʧ��:������
*      Caution: ֻ�в�ѯ����򿪳ɹ����ܽ�����һ��TCP����������Ϣ��ѯ����,ÿ�β�ѯ��ȡһ��������Ϣ,�ú���
*               �ڴ򿪲�ѯ�������Խ��ж�β�ѯ�Է������е�TCP����������Ϣ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetTcpNetInfo(UINTPTR ulWaitlist, TCPIP_TCPNETINFO_S *pstNetInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: �رղ�ѯ���
*        Input: ulWaitlist:Waitlist���
*       Output: 
*       Return: �ɹ�:VOS_OK;ʧ��:������
*      Caution: �ڲ�ѯ��������߻�ȡTCP����������Ϣʧ��ʱ��Ҫ�رղ�ѯ�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseTcpNetInfo(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpInfo
* Date Created: 2012-09-05
*       Author: wangtong207740
*  Description: 
*        Input: ULONG ulSocketId:
*               TCP_SOCK_INFO_S *pstTcpInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-05   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_GetTcpInfo(ULONG ulSocketId, TCP_SOCK_INFO_S *pstTcpInfo);

/*******************************************************************************
*    Func Name: TCPIP_RegTcpCookieSecret
* Date Created: 2014-5-13
*       Author: f00209023
*  Description: ע���ȡTCP COOKIE����Կ����
*        Input: gpfTCPIPGetCookieSecret  pfGetCookieHook
*       Return: VOS_OK:
*      Caution: ���Ϊ����ע��ʧ�ܣ�����ɹ�����VISP��ʼ��֮ǰע��
*         Լ��: ��Ʒ��Ҫʹ��cookie���ԣ������ע��ù��ӡ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-5-13   f00209023                Create
*
*******************************************************************************/
ULONG TCPIP_RegTcpCookieSecret(gpfTCPIPGetCookieSecret  pfGetCookieHook);
/*******************************************************************************
*    Func Name: TCPIP_RegGetUsrCookieSwitch
* Date Created: 2014-5-13
*       Author: f00209023
*  Description: ע���ȡ��ƷCOOKIE���صĹ���
*        Input: gpfTCPIPGetUsrCookieSwitch pfGetUserCookieSwitch
*       Return: VOS_OK:
*      Caution: ���Ϊ����ע��ʧ�ܣ�����ɹ�����VISP��ʼ��֮ǰע��
*         Լ��: ��Ʒ��Ҫʹ��cookie���ԣ������ע��ù��ӡ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-5-13   f00209023                Create
*
*******************************************************************************/
ULONG  TCPIP_RegGetUsrCookieSwitch(gpfTCPIPGetUsrCookieSwitch pfGetUserCookieSwitch);

ULONG TCPIP_RegTcp4Md5CfgNotifyHook(gpfTCPIPMd5CfgNotifyHook pfCfgNotify);

ULONG  TCPIP_RegTcp4Md5AuthNotifyHook(gpfTCPIPMd5AuthNotifyHook pfAuthNotify);
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

