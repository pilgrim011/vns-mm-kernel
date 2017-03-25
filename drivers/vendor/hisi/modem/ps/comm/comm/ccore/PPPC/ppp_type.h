/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ppp_type.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ�����Ͷ���
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef      _PPP_TYPE_H_
#define      _PPP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif/* end of __cplusplus */

#ifndef PPP_MAXUSERNAMELEN
#define PPP_MAXUSERNAMELEN 128
#endif

#define IMSI_ASCII_LEN 16
#define MSISDN_ASCII_LEN 16
#define PPP_SHARE_MEM_LEN 32

#define PPP_AUTH_FLAG   1
#define PPC_AUTH_FLAG   2

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
typedef struct
{
    struct {
        VOS_INT32 badfcs;
        VOS_INT32 badaddr;
        VOS_INT32 badcommand;
        VOS_INT32 unknownproto;
    } laststats, stats;
    VOS_UINT32 SaveInErrors;
} PPPC_HDLC_STRU;
#endif


/* ������Ϣ */
typedef struct tagPppConfigInfo
{
    VOS_UINT32 bCallbackReq            : 1,
          bCallbackAcc            : 1,
          bCallInAuth             : 1,
          bAuthRmtChap            : 1,
          bAuthRmtPap             : 1,
          bAuthRmtEap             : 1,
          bEnableVJComp           : 1,
          bEnableComp             : 1,
          bSetAsMp                : 1,
          bPapPwdEncrypt          : 1,
          bChapPwdEncrypt         : 1,
          bAuthRmtList            : 1,
          bStacCompress           : 1,
          bMppcCompress           : 1,        /* WGGSN_B03_L2TP_PPPC_COMP*/
          bAuthMethod             : 2,        /* ��֤��ʽ 0: �� 1: ǿ����֤ 2: Э�̼�Ȩ  */
          bUsedFlag               : 1,        /* ���ƿ�ռ�ñ�ǣ�1Ϊռ�� */
          bRadiusPri              : 1,        /* radius���ȷ���IP�Ƿ��0 �ر� 1 ��*/
          bVsncpAPNAmbrFlag       : 1,
          bVsncpDefApnIndFlag     : 1;

    VOS_UINT32  ulNegTimeOut;

    VOS_UINT16 usMru;
    UCHAR  ucDomainName[PDSN_DOMAINNAME_LEN + 1];
    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];
    UCHAR ucPppcnfRev;                                 /* luofang--���ֽڶ��� */
} PPPCONFIGINFO_S;


 typedef struct tagPppDebugInfo
{
    VOS_UINT32 bDebug_Lcp_Packet     : 1,
        bDebug_Lcp_Event        : 1,
        bDebug_Lcp_Error        : 1,
        bDebug_Lcp_StateChange  : 1,
        bDebug_Ipcp_Packet      : 1,
        bDebug_Ipcp_Event       : 1,
        bDebug_Ipcp_Error       : 1,
        bDebug_Ipcp_StateChange : 1,
        bDebug_Ipv6cp_Packet    : 1,
        bDebug_Ipv6cp_Event     : 1,
        bDebug_Ipv6cp_Error     : 1,
        bDebug_Ipv6cp_StateChange: 1,

        bDebug_Pap_Packet       : 1,
        bDebug_Pap_Event        : 1,
        bDebug_Pap_Error        : 1,
        bDebug_Pap_StateChange  : 1,

        bDebug_Chap_Packet      : 1,
        bDebug_Chap_Event       : 1,
        bDebug_Chap_Error       : 1,
        bDebug_Chap_StateChange : 1,

        bDebug_Ccp_Packet       : 1,
        bDebug_Ccp_Event        : 1,
        bDebug_Ccp_Error        : 1,
        bDebug_Ccp_StateChange  : 1,

        bDebug_Ip_Packet        : 1,
        bDebug_Scp_Packet       : 1,
        bDebug_Core_Event       : 1,
        bDebug_Imsi             : 1, /* ���û����Կ��� */ /*Added by hyj for B02*/

        bDebug_EAP_Packet: 1,
        bDebug_EAP_Event: 1,
        bDebug_EAP_Error: 1,
        bDebug_EAP_StateChange: 1;

}  VOS_PACKED PPPDEBUGINFO_S;

typedef struct tagPppCallbacks
{
    VOS_UINT32 (*pfPhyTransmit)(VOS_UINT32, PMBUF_S *);    /* �ײ�����·����ע��Ĺ���·��ʹ�õķ��ͱ��ĺ���
                                            PDSN: A11_PPPC_A10_Encap */
    VOS_UINT32 (*pfUpIoCtl)(VOS_UINT32, VOID *, VOS_UINT32);   /* �ϲ��ṩ����·������ϴ��ݿ�����Ϣ�ĺ���
                                                PDSN: A11_PPPC_SendUsrInfor */
    VOS_UINT32 (*pfPhyIoCtl)(VOS_UINT32, UCHAR);    /* �ײ�����·����ע��Ĺ���·��ʹ�õ����̿��ƺ���
                                            PDSN: A11_PPPC_ReleaseA10Inform */
} PPPCALLBACK_S;


 /* ��Ȩ���� */
typedef struct tagPppAaaAuthReqMsg
{
    MSG_HDR_S stMsgHdr;             /* NE80ͷ */
    VOS_UINT32     ulMsgType;            /* ��Ϣ���� */
    VOS_UINT32     ulSDBIndex;            /* SDB���� */

    VOS_UINT16 usCDBIndex;                /* GGSN:APNIndex PDSN:DomainIndex */
    UCHAR  ucPktID;                 /* �û���֤�����ID */
    UCHAR  ucUsernameLen;           /* �û������� */

    UCHAR ucUsername[A11_MAX_NAI_LENGTH + 1]; /* �û��� */
    UCHAR ucPwd[18];                /* ���� */
    UCHAR ucPwdLen;                    /* ���볤�� */
    UCHAR ucChapResponseLen;        /* Chap-Response���� */

    UCHAR ucChapResponse[256];        /* Chap-Response */
    UCHAR ucChapChallenge[256];        /* Chap-Challenge */

    UCHAR  ucChapChallengeLen;       /* Response���� */
    UCHAR  ucRes;
    VOS_UINT16 usVPNID;                 /* VPN ID */

    VOS_UINT32  ulIp;                       /* IP��ַ */
    A11_IMSI_S stIMSI;                  /* IMSI */
    VOS_UINT32  ulIpMask;                   /* IP��ַ�������� */
    VOS_UINT32  ulG4EvtTime;               /* Event Time */
    UCHAR  aucC2CorLID[8];           /* Correlation ID */
    VOS_UINT32  ulCurVolume;         /* ����ֵ */
    VOS_UINT32  ulCurDuration;       /* ʱ��ֵ */
    VOS_UINT32  ulVUATS;                /* �����л���֮����û����� */
    VOS_UINT16 usGroupIndex;                    /* test ��Ϣר�� */
    UCHAR  ucPreparedFlag;   /* ʹ��A11_PPC_TYPE_E���� */
    UCHAR  ucUpdateReason;  /* ����ԭ�� */
    UCHAR  ucRenegoFlag;    /* ��Э�̱�� */
    UCHAR  ucPPPFlag;       /*Я����־λ��ֵΪ 1��AUTH�ж���PPP��PPC��Ϣ*/
    UCHAR  ucReserved[6];
 } AAA_AUTHREQ_S;


 /* IP��ַ������Ϣ */
typedef struct tagPppcApplyIpReqMsg
{
    MSG_HDR_S stMsghead;      /*��Ϣͷ�ṹ*/
    VOS_UINT32     ulIndex;              /*����������*/
    VOS_UINT32     ulCDBIndex;        /*����*/
    VOS_UINT32     ulReqIPFlag;          /*����IP��־��1Ϊ����IP��0Ϊ������IP*/
    VOS_UINT32 ulIpadd;
    VOS_UINT32 ulreserverd;
    UCHAR ucAddrType;
    UCHAR ucScid;
    UCHAR ucReserved[2];
} PPPC_APPLYIP_REQ_MSG_S;

/* IP��ַ������Ӧ��Ϣ */
typedef struct tagPppcApplyIpAckMsg
{
    MSG_HDR_S stMsghead;       /*��Ϣͷ�ṹ*/
    VOS_UINT32     ulRetCode;             /*�����룬�ɹ���ʧ��*/
    VOS_UINT32     ulIndex;               /*����������*/
    VOS_UINT32     ulIpAddr;              /*�����IP��ַ*/
    VOS_UINT32     ulReserved;           /* luofang--���ֽڶ��� */
} PPPC_APPLYIP_ACK_MSG_S;



typedef struct tagPppA11Msg                                                  /* A11��Ϣ�ṹ */
{
    VOS_UINT32                      ulRPIndex;
    VOS_UINT32                      ulMsgCode;                                  /* luofang--���ֽڶ��� */
    union
    {
        VOS_UINT32                  ulSwitchRPIndex;                            /* ISPCFSWITCH */
        PPP_LUPPARA_S               stLupPara;                                  /* ISLUP */
    } para;
    VOS_UINT32                      ulL2tpType;
    VOS_UINT32                      ulLcpSendFlag;
} PPP_A11MSG_S;

typedef struct tagPppIpcpOption
{
    /* �Ƿ�Э�� */
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    VOS_UINT32 neg_addr :         1,   /* Negotiate IP Address? */
            old_addrs:         1,             /* Use old (IP-Addresses) option? */
            req_addr:         1,              /* Ask peer to send IP address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_reserved: 16;
#else
    VOS_UINT32 accept_reserved: 16,
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            req_addr:         1,              /* Ask peer to send IP address? */
            old_addrs:         1,             /* Use old (IP-Addresses) option? */
            neg_addr :         1;   /* Negotiate IP Address? */
#endif
    VOS_UINT32  ouraddr;
    VOS_UINT32  hisaddr;      /* Addresses in NETWORK BYTE ORDER */
    VOS_UINT32  dnsaddr0;
    VOS_UINT32  nbnsaddr0;   /* Primary DNS address and Primary NDNS address */
    VOS_UINT32  dnsaddr1;
    VOS_UINT32 nbnsaddr1;   /* Secondary DNS and NBNS address */
    VOS_UINT16 vj_protocol;           /* protocol value to use in VJ option */
    UCHAR  maxslotindex;
    UCHAR  cflag;   /* values for RFC1332 VJ compression neg. */
} VOS_PACKED PPP_IPCP_OPTION_S;

typedef struct tagPppIpv6cpOption
{
    /* �Ƿ�Э�� */
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    VOS_UINT32   neg_addr :        1,   /* Negotiate IP Address? */
            old_addrs:        1,             /* Use old (IP-Addresses) option? */
            req_addr:         1,              /* Ask peer to send IP address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_reserved: 16;            /* luofang--���ֽڶ��� */
#else
      VOS_UINT32 accept_reserved: 16,            /* luofang--���ֽڶ��� */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            req_addr:         1,              /* Ask peer to send IP address? */
            old_addrs:        1,             /* Use old (IP-Addresses) option? */
            neg_addr :        1;   /* Negotiate IP Address? */
#endif

    VOS_UINT16 vj_protocol;                      /* protocol value to use in VJ option */
    UCHAR  maxslotindex;
    UCHAR  cflag;              /* values for RFC1332 VJ compression neg. */
    VOS_UINT16 OurV6InId[IPV6_ADDR_LEN/2];
    VOS_UINT16 HisV6InId[IPV6_ADDR_LEN/2];    /*����aaa�·��Ľӿ�id*/
    VOS_UINT16 ConfigV6InId[IPV6_ADDR_LEN/2]; /*���汾�����õĽӿ�id*/
} VOS_PACKED PPP_IPV6CP_OPTION_S;
typedef struct ccp_options
{
    VOS_UINT32  ulMppc_supportedbits;  /* # Supported Bits for MPPC Compress */
    VOS_UINT16 usStac_historys;        /* # history number for stacker Compress */

#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)

    UCHAR   bStac_compress : 1,       /* do stacker Compress? */
            bLZS0_comp: 1,
            bLZS1_comp: 1,
            bMppc_compress: 1,                 /* do Mppc Compress? */
            breserved: 4;        /* luofang--���ֽڶ��� */
#else
    UCHAR   breserved: 4,        /* luofang--���ֽڶ��� */
            bMppc_compress: 1,                 /* do Mppc Compress? */
            bLZS1_comp: 1,
            bLZS0_comp: 1,
            bStac_compress : 1;       /* do stacker Compress? */
#endif

    UCHAR ucStac_checkmode;      /* # stacker compress check mode ( sequence number ) */
} PPP_CCP_options_S;

typedef struct tagPppRenegoInfo
{
    UCHAR               ucIpcpFlag;
    UCHAR               ucIpV6cpFlag;
    UCHAR               ucCcpFlag;
    UCHAR               ucPrenegoRev[5];
    PPP_IPCP_OPTION_S   stIpcpOptions;
    PPP_IPV6CP_OPTION_S stIpcpV6Options;
    PPP_CCP_options_S   stCcpOptions;
} PPPRENOGOINFO;

#ifndef LAP_POOL_NAME_MAX_LENGTH
#define LAP_POOL_NAME_MAX_LENGTH 32
#endif
/* PPP���ƿ� */
typedef struct tagPppInfo
{
    /*********************************/
    /*       ָ�붨��              */
    /*********************************/
    PPPCONFIGINFO_S* pstConfigInfo;         /* ������Ϣ */
    PPPCONFIGINFO_S* pstUsedConfigInfo;     /* ��ǰ�ӿ����û������������Ϣ,ֻ�����ÿɼ��ӿ���Ч */
    PPPRENOGOINFO*   pstPppRenegoInfo;      /* ��Э����Ϣ */

    VOID* pstLcpInfo;           /* LCP  ���ƿ�ָ�� */
    VOID* pstPapInfo;           /* PAP  ���ƿ�ָ�� */
    VOID* pstChapInfo;          /* CHAP ���ƿ�ָ�� */
    VOID* pstEapInfo;           /* EAP  ���ƿ� */
    VOID* pstIpcpInfo;          /* IPCP ���ƿ�ָ�� */
    VOID* pstIpV6cpInfo;        /* IPV6CP ���ƿ�ָ�� */
    VOID* pstVsncpInfo;         /* VSNCP ���ƿ�ָ�� */
    VOID* pstCcpInfo;           /* CCP  ���ƿ�ָ�� */
    VOID* pL2tpPara;            /* L2TP��Ҫ�Ĳ��� */
    VOID* pulCurrFsm;           /* ��ǰ״̬�� */
    VOID* pstHdlcInfo;

    VOS_UINT32 bIsAsync          : 1,        /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
          bSynAsyConvert    : 1,        /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
          bLoopBacked       : 1,        /* �ӿ��Ƿ������Ի� */
          bLowerIsUp        : 1,
          bIPReleaseFlg     : 1,        /* 0: ��Ҫ�ͷ�IP�� 1: ����Ҫ�ͷ�IP(MIP&L2tp�û�)*/
          bIPTech           : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent ;3 NIL*/
          bAuthServer       : 1,        /* PDSN��Ʒ��̬��֧��serverģʽ��0��ʾ��֤��ϻ�������֤��1���ڽ�����֤ */
          bAuthClient       : 1,        /* PDSN��Ʒ��̬��֧��clientģʽ����ֵʼ��Ϊ�� */
          bReNego           : 1,        /* ��Э�̱�־ */
          bReNegoV6         : 1,        /* IPV6��Э�̱�־ */
          bPppStateFlg      : 2,        /* ��̬���ӱ�� */
          bPppMode          : 1,        /* �ս�ģʽΪ0������ģʽΪ1 */
          bPppClient        : 1,        /* �ͻ���ģʽΪ1������Ϊ0 */
          bPhaseFlag        : 2,        /* 0:LCP�׶Σ�1:��Ȩ�׶Σ�2:IPCP�׶� 3:�ɹ��׶� */
          bFailFlag         : 4,        /* 0:�Լ�Э��ʧ��. 1:A11/GTPC֪ͨɾ��. 2:�û�Ҫ������. 3:L2TP֪ͨɾ�� */
          bMppcFlag         : 1,        /* MPPC�û���ͳ�Ʊ�־ */
          bVjFlag           : 1,        /* VJ�û���ͳ�Ʊ�־ */
          bLzs0Flag         : 1,        /* Stac_Lzs0�û���ͳ�� */
          bLzs1Flag         : 1,        /* Stac_Lzs1�û���ͳ�� */
          bPpcAAAFlag       : 1,        /* ���ֶ��Ѿ�û�����壬�ο����ⵥDTS2013010508014  */
          bPppSuccess       : 1,        /* PPP�����ɹ����,����PPPָ���Ż� */
          bAuthFlag         : 1,        /* �����ж��Ƿ��Ѿ���ɹ�chap��pap��Ȩ,����VOS_TRUE,����Э�̲�����AAA */
          bIpcpSucFlag      : 1,        /* PPPЭ��IPCPЭ�̳ɹ����,�ñ������Э�̹���Ҳ����ı� */
          bPppStateFlgV6    : 2,        /* IPV6��̬���ӱ�� */
          bPccFlag          : 1;        /* �Ƿ�ΪPCC�û���ʶ*/

    VOS_UINT32 bRecvLcpMsgFlag   : 1,        /* ��ʾ�Ƿ��յ���LCP����Ϣ*/
          bIpv6cpNoToPDN    : 1,        /* ipv6cp finish ʱ�Ƿ�֪ͨPDN, 0��ʾ֪ͨ�� 1Ϊ��֪ͨ */
          bIpcpNoToPDN      : 1,        /* ipcp finish ʱ�Ƿ�֪ͨPDN, 0��ʾ֪ͨ�� 1Ϊ��֪ͨ */
          bEhrpdUser        : 1,        /* �Ƿ�ΪeHRPD�û� */
          bEAPAuthFlag      : 1,        /* EAP�Ƿ��Ѿ��ɹ��� */
          bIPCPNakHandFlag  : 1,        /* IPCP NAK HANDLING */
          bReservNew        : 26;       /* ע���޸�Ϊ���� */


    /*********************************/
    /*       �ṹ�嶨��              */
    /*********************************/
    IMSI_S            stIMSI;

    PPPDEBUGINFO_S stPppDebugInfo;    /* ������Ϣ */
    VOS_UINT32 ulNowUTCInSec;
    VOS_UINT32 ulRemoteAccm;         /* �Զ�ACCM������ */
    VOS_UINT32 ulLocalAccm;          /* ����ACCM������ */
    VOS_UINT32 ulRPIndex;
    VOS_UINT32 ulPcfIP;
    VOS_UINT32 ulIPAddr;             /* ����IP��ַ����ʼ��Ϊ2.2.2.2 */
    VOS_UINT32 ulPeerIPAddr;         /* ����RADIUS SERVER��DHCP���͵��û�IP��ַ */
    VOS_UINT32 ulDNSAddr1;
    VOS_UINT32 ulDNSAddr2;
    ULONG64 ulNegoStartTime;      /* PPPЭ�̿�ʼʱ�� */
    ULONG64 ulNegoEndTime;        /* ˫ջipv6��Э�̳ɹ���¼��ֵ,���ⵥ��:DTS2012051200799 */
    VOS_UINT16 usPeerId;                /* �����һ�η��ͷ�����id */
    VOS_UINT16 usTokenId;

    VOS_UINT16 usState;
    VOS_UINT16 usPhase;              /* PPP��ǰ����Э�̽׶�,����Ϊ����ֵ:
                                                 PPP_PHASE_DEAD
                                                 PPP_PHASE_ESTABLISH
                                                 PPP_PHASE_AUTHENTICATE
                                                 PPP_PHASE_CBCP
                                                 PPP_PHASE_NETWORK
                                                 PPP_PHASE_TERMINATE
                                               */
    VOS_UINT16 usCDBIndex;     /* GGSN:APNIndex PDSN:DomainIndex */
    VOS_UINT16 usVirtualDomainIdx;

    VOS_UINT16 usMtu;
    VOS_UINT16 usPcfIndex;

    VOS_UINT16 usIpv6Addr[IPV6_ADDR_LEN];     /*����ipv6��ַ����ʼ��Ϊ:FE80::FFFF:FFFF:FFFF:FFFF*/
    VOS_UINT16 usPeerIPv6Addr[IPV6_ADDR_LEN]; /* ����RADIUS SERVER��lap������û�IPv6��ַ����ǰ׺�ͽӿ�id*/

    HTIMER                  hPppInactiveTimer;  /* MAX PPP Inactive Timer */
    VOS_UINT32              ulPppInactTimerLen; /* MAX PPP Inactive Timer ʱ��,��λs */
    VOS_UINT32              ulPppInactTimeOutCnt; /* MAX PPP Inactive Timer��ʱ���������ڸö�ʱ��ʱ���ϴ�(����VOS��ʱ��������18Сʱ)�����賬ʱ��β���ִ�г�ʱ������ */

    UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];

    UCHAR  ucServiceOpt;
    UCHAR  ucFSMFailType;           /* FSM_CODE_E */
    UCHAR  ucDmpuId;                /* ѹ���ӿ�CPU��, 0ΪCPU2, 1ΪCPU3 */
    UCHAR  ucDpeId;                 /* �ӿ�DPE�� */

    UCHAR  ucIpCapability;     /*ip�������μ�ö�� PDSN_PPP_IPTYE ���� */

    UCHAR ucPppRleaseCode;    /* PPPģ�鷢������֪ͨUSMԭ��ֵ */
    UCHAR ucV4NcpReleaseCode;   /* ����׶�Э��ʧ��֪ͨPDN��ԭ��ֵ */
    UCHAR ucV6NcpReleaseCode;   /* ����׶�Э��ʧ��֪ͨPDN��ԭ��ֵ */
    UCHAR ucAAAType;            /* ehrpd aaa ���������� */

    PS_BOOL_ENUM_UINT8      enServerTermReq;  /* ��¼�Ƿ���������Ͽ�����PDN���ӵ���PPP�ͷ���· */
    PS_BOOL_ENUM_UINT8      enIsDoingAccessAuth; /* ��¼��ǰPPP ID�Ƿ������������Ȩ */
    PS_BOOL_ENUM_UINT8      enInactiveTimerEnable;      /* MAX PPP Inactive Timer���� */

    VOS_UINT8 aucReserved[8];
} PPPINFO_S;


/* Multilink User����ڵ� */
typedef struct tagPppMultilinkUser
{
    struct tagPppMultilinkUser *pNext;        /* ����ָ�� */
    CHAR cUserName[PPP_MAXUSERNAMELEN + 2];   /* �û��� */
    CHAR c_IntfName[200 + 2];                 /* virtual template�ӿ��� */
    CHAR ucReserved[4];                       /* luofang--���ֽڶ��� */
} PPPMULTILINKUSER_S;

/* ״̬��ģ�����ݽṹ���� */
typedef struct tagPppFsm
{
    CHAR *    pProtocolInfo;         /* ��Э����ƿ�ָ�� */
    CHAR *    pPppInfo;             /* PPP���ƿ�ָ�� */
    struct tagPppFsmCallbacks *pstCallBacks;  /* �ص������� */
    VOS_UINT32     ulTimeOutTime;         /* config request���ĵĳ�ʱʱ�� */
    VOS_UINT32     ulEchoTimeOutTime;     /* LCP Echo request���ĵĳ�ʱʱ�� */
    HTIMER     ulTimeOutID;           /* config request���ĵĶ�ʱ�� */
    HTIMER  ulEchoTimeoutID;       /* LCP Echo request���ĵĶ�ʱ�� */
/* EAP-dev */
    HTIMER     hVendorSpecificTimeID;      /* �汾����Э����Ӧ��ʱ�� */
    VOS_UINT16 usProtocol;             /* ��Э���PPPЭ��� */
    SHORT  sRetransmits;            /* config request�����ش����� */
    VOS_UINT16 usNakloops;             /* Nak�Է�ͬһ��ѡ��Ĵ��� */
    UCHAR  ucState;                  /* Э��״̬ */
    UCHAR  ucPktId;                  /* ��Э�鵱ǰ���ĵ�ID */
    UCHAR  ucEchoId;                 /* LCP Echo request���ĵ�ID */
    UCHAR  ucEchoState;            /*r002 add record echo state*/
/* EAP-dev */
#if 0
    SHORT  sVSRetransmits;        /* �汾����Э��ָʾ�����ش����� */
#else
    SHORT  sVSTransmits;            /* �汾����Э��ָʾ���Ĵ��ʹ���(�����������ش�) */
#endif
    UCHAR  ucVSId;                 /*�汾����Э��ָʾ���ĵ�Identifier */
    UCHAR  ucTimerType;
    UCHAR  ucRev[6];
} PPPFSM_S;

typedef struct tagPppFsmCallbacks
{
    /* ������Э�̱��Ĵ��� */
    VOID (*resetci)(PPPFSM_S *);   /* ����������Ϣ����Э�̳�ʼֵ */
    VOS_UINT16 (*cilen)(PPPFSM_S *);    /* ��Ҫ���͵�request���ĳ��� */
    VOID (*addci)(PPPFSM_S *, UCHAR *);

    /* ��֯Э�̱��� */
    VOS_UINT16 (*ackci)(PPPFSM_S *, UCHAR *, VOS_UINT32);

    /* ����Է���ack���� */
    VOS_UINT16 (*nakci)(PPPFSM_S *, UCHAR *, VOS_UINT32);

    /* ����Է���nak���� */
    VOS_UINT16 (*rejci)(PPPFSM_S *, UCHAR *, VOS_UINT32);

    /* ����Է���reject���� */
    UCHAR (*reqci)(PPPFSM_S *, UCHAR *, VOS_UINT32 *);

    /* ����Է���request���� */
    VOS_UINT16 (*extcode)(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, VOS_UINT32, VOS_UINT32);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
    /* ����Э�����еı��ģ���protocol reject�� */

    /* �¼���Э��ת������ֹ״̬ */
    VOID (*up)(PPPFSM_S *);         /* Э��up */
    VOID (*down)(PPPFSM_S *);       /* Э����ʱdown,����Ҫ����Э��.
                                       ��finished��������:����PPPOE��DDR�ȵ������
                                       ����֪ͨ�²�����· */
    VOID (*finished)(PPPFSM_S *);   /* Э�������֪ͨ�ײ�:�����·.����LCP,ֻҪ����
                                       PPPOE��DDR�ȵ����,�������reset��ʱ��,
                                       ��ʱ����������Э�� */
    VOID (*starting)(PPPFSM_S *);   /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                                       ����������Э��,�����,�뷢һ��up�¼�.
                                       Э����������û�о���涨,���Բ�ʵ��*/

    /* ��Э����Ϣ */
    CHAR proto_name[8];             /* ��Э���� */
} PPPFSMCALLBACK_S;

/*�����û�����������֤(CHAP/PAP)*/
typedef struct
{
    VOS_UINT16 usType;
    UCHAR  ucPktID;
    CHAR   szUsrName[PPP_MAXUSERNAMELEN + 2];
    UCHAR  ucUsrNameLen;
    CHAR   szPwd[PPPC_MAX_PASSWORD_LEN];
    UCHAR  ucPwdLen;
    CHAR   szResponse[PPPC_MAX_RESPONSE_LEN];
    UCHAR  ucResponseLen;
} PPPC_AUTH_MSG_STRU;

 typedef struct tagPppNegoNode
{
    struct tagPppNegoNode* pNext;
    VOS_UINT32 ulRpIndex;
    VOS_UINT32 ulPDNIndex;
    UCHAR ucCounter;   /* Э�̳�ʱ������ */
    UCHAR ucNodeType;
    UCHAR aucRsv[2];
} PPP_NEGO_NODE_S;

 typedef struct tagPppLcpOption
{
    /* �Ƿ�Э�� */
    VOS_UINT32 neg_mru           : 1,
          neg_asyncmap      : 1,
          neg_upap          : 1,
          neg_chap          : 1,
          neg_eap           : 1,
          neg_magicnumber   : 1,
          neg_pcompression  : 1,
          neg_accompression : 1,
          neg_lqr           : 1,
          neg_mrru          : 1,
          neg_ssnhf         : 1,
          neg_discr         : 1,
          neg_callback      : 1,
          neg_reserved      :19;    /* luofang--���ֽڶ��� */

    /* Э�̲���ֵ */
    VOS_UINT16 mru;
    VOS_UINT16 mrru;
    VOS_UINT32  asyncmap;
    VOS_UINT32  magicnumber;
    VOS_UINT32  numloops;
    VOS_UINT32  lqr_period;      /* Reporting period for LQR 1/100ths second */
    UCHAR  chap_mdtype;
    UCHAR  discr_len;
    UCHAR  discr_class;
    UCHAR  callbackopr;
    UCHAR  discr_addr[20];
    UCHAR  callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR  callbacklen;
    UCHAR  ucReserved[3];   /* luofang--���ֽڶ��� */
} PPP_LCP_OPTION_S;

typedef struct tagPPP_PPPINFO_BKP_V
{
    IMSI_S stIMSI;
    PPPDEBUGINFO_S stPppDebugInfo; /* �ӿڵ�debug������Ϣ */
    PPP_LCP_OPTION_S  stLcpGotOptions;
    PPP_IPCP_OPTION_S stIpcpGotOptions;
    PPP_IPV6CP_OPTION_S stIpv6cpGotOptions;

    VOS_UINT32 bIsAsync      : 1,        /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
          bSynAsyConvert: 1,        /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
          bLoopBacked   : 1,        /* �ӿ��Ƿ������Ի� */
          bLowerIsUp    : 1,
          bIPTech       : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent */
          bAuthServer   : 1,
          bAuthClient   : 1,
          bReNego       : 1,        /* ��Э�̱�־ */
          bStac         : 1,        /* stacѹ����� */
          bMppc         : 1,        /* mppcѹ����� */
          bPppMode      : 1,        /* �ս�ģʽΪ0������ģʽΪ1 */
          bPppClient    : 1,        /* �ͻ���ģʽΪ1������Ϊ0 */
          bIsNullFlag   : 1,        /* �յĿ��ƿ��� */
          bIPReleaseFlg : 1,        /* 0: ��Ҫ�ͷ�IP�� 1: ����Ҫ�ͷ�IP(MIP&L2tp�û�)*/
          bReNegoV6     : 1,        /* IPV6��Э�̱�־ */
          bPppStateFlg  : 2,        /* ipv4��̬���ӱ�� */
          bPppStateFlgV6: 2,        /* ipv6��̬���ӱ�� */
          bPhaseFlag    : 2,        /* �ñ��Ŀǰ������SNMP�澯ͳ�ƣ��������Կ����Ż���
                                                          0:LCP�׶Σ�1:��Ȩ�׶Σ�2:IPCP�׶� 3:�ɹ��׶� */
          bRev: 10;

    VOS_UINT32  ulDhcpTimeOutTime;    /* ��ʱʱ�� */
    VOS_UINT32  ulDNSAddr1;
    VOS_UINT32  ulDNSAddr2;
    VOS_UINT32  ulRemoteAccm;        /* �Զ�ACCM������ */
    VOS_UINT32  ulLocalAccm;         /* ����ACCM������ */
    VOS_UINT32  ulRPIndex;
    VOS_UINT32  ulPeerIPAddr;        /* ����RADIUS SERVER��DHCP���͵��û�IP��ַ */
    VOS_UINT32  ulPcfIP;             /* PCFIP */

    VOS_UINT16 usMtu;
    VOS_UINT16 usCDBIndex;

    VOS_UINT16 usVirtualDomainIdx;
    VOS_UINT16 usPeerIPv6Addr[IPV6_ADDR_LEN]; /* ����RADIUS SERVER��lap������û�IPv6��ַ ����ǰ׺�ͽӿ�id*/

    UCHAR ucDmpuId;
    UCHAR ucDpeId;
    UCHAR ucDhcpUsed;           /*dhcp���ƿ�ռ�ñ�� 1 ��ռ�� 0 δռ��*/
    UCHAR ucIpCapability;     /*ip�������μ�ö�� PDSN_PPP_IPTYE ���� */
    UCHAR ucIpv6cpPktId;
    UCHAR ucPpcAAAFlag;
    UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];
}PPP_PPPINFO_BKP_S;

/* PPPC���ƿ�ı��ݽṹ */
typedef struct tagPPP_BKP_V
{
    HAMSGHEAD_S       stHaMsg;
    UCHAR             ulRecordCount;
    UCHAR             ucRev[7];
    PPP_PPPINFO_BKP_S stPppInfobkp[PPP_BKP_INFO_MAX];
} VOS_PACKED PPP_BKP_S;

/* ��¼��ʱ����ʱ�����ڷ����ı�Ŀ��ƿ������Ľṹ*/
typedef struct tagPPP_CHANGEDINFO_BKP_S
{
    VOS_UINT32 ulChangeFlag;
    VOS_UINT32 ulNextIndex;
} VOS_PACKED PPP_CHANGEDINFO_BKP_S;


typedef struct
{
    VOS_UINT32 ulLCPInitFail;      /*LCP init ʧ��*/
    VOS_UINT32 ulLCPStartingFail;  /*LCP Starting ʧ��*/
    VOS_UINT32 ulLCPClosedFail;    /*LCP Closed ʧ��*/
    VOS_UINT32 ulLCPStopedFail;    /*LCP Stoped ʧ��*/
    VOS_UINT32 ulLCPClosingFail;   /*LCP Closing ʧ��*/
    VOS_UINT32 ulLCPStoppingFail;  /*LCP Stopping ʧ��*/
    VOS_UINT32 ulLCPReqsentFail;   /*LCP Reqsent ʧ��*/
    VOS_UINT32 ulLCPAckrcvdFail;   /*LCP Ackrcvd ʧ��*/
    VOS_UINT32 ulLCPAcksentFail;   /*LCP Acksent ʧ��*/
    VOS_UINT32 ulLCPOtherFail;     /*LCP ����ԭ��ʧ��*/
    VOS_UINT32 ulIPCPInitFail;     /* IPCP Init ʧ��*/
    VOS_UINT32 ulIPCPStartingFail; /* IPCP Starting ʧ��*/
    VOS_UINT32 ulIPCPClosedFail;   /* IPCP Closed ʧ��*/
    VOS_UINT32 ulIPCPStopedFail;   /* IPCP Stoped ʧ��*/
    VOS_UINT32 ulIPCPClosingFail;  /* IPCP Closing ʧ��*/
    VOS_UINT32 ulIPCPStoppingFail; /* IPCP Stopping ʧ��*/
    VOS_UINT32 ulIPCPReqsentFail;  /* IPCP Reqsent ʧ��*/
    VOS_UINT32 ulIPCPAckrcvdFail;  /* IPCP Ackrcvd ʧ��*/
    VOS_UINT32 ulIPCPAcksentFail;  /* IPCP Acksent ʧ��*/
    VOS_UINT32 ulIPCPOtherFail;    /*IPCP ����ԭ��ʧ��*/
} PPP_FAIL_COUNTER;

/* L2TP�û����澯�ṹ */
typedef struct
{
    VOS_UINT32 ulsn; /*�ۺ�*/
    VOS_UINT32 ulrate; /* �û������� */
} PPP_L2TP_USERALARM_S;

typedef struct tagCCPMsg
{
    MSG_HDR_S stMsgHdr;
    VOS_UINT32     ulUserIndex; /*���û�������*/
    UCHAR     ucCode; /*ccp���ĵ�code*/
    UCHAR     ucIdFlag; /*ccp�����е�ID*/
    VOS_UINT16    usReserved; /* �����ֶΣ�Ϊ�����ֽڶ��� */
} PPPCOMP_CCPMSG_S;

typedef struct tagLinkItem
{
    PF_USHORT offset;
    PF_USHORT lcopy;
    PF_ULONG  seq;
    PF_USHORT litem;
    PF_USHORT usRsvd[3];    /*��֤�����ָ�밴8�ֽڶ���*/
    PF_UCHAR *pdata;        /*���ڴ洢MBUF��������ַ(ƫ��IP+GRE)*/
    PMBUF_S  *pMbuf;        /*���ڴ洢MBUF��ַ*/
    struct tagLinkItem* pnext;
}LINKITEM_S;

typedef struct tagLinkTcb
{
    PF_UCHAR tcounter : 1;
    PF_UCHAR seqflag  : 1;
    PF_UCHAR endflag  : 1;  /*֮ǰ���������һ��������7E��β*/
    PF_UCHAR clearflag: 1;
    PF_UCHAR grpkt    : 4;  /*���еȴ���������ݰ��ĸ���*/

    PF_UCHAR pkt_num;
    PF_UCHAR ucNum_seq;
    PF_UCHAR aucRsv1[1];

    LINKITEM_S* phead;      /*��֤phead��8�ֽڶ���*/
    PF_ULONG seq_late;      /*�ȴ�����һ�����к�*/
}LINKTCB_S;



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_TYPE_H_ */
