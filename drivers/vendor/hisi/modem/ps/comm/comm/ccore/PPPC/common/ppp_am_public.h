#ifndef __PPP_AM_PUBLIC_H__
#define __PPP_AM_PUBLIC_H__

/************************* �������� **********************************/
#define PPP_MP 0x003d
#define PPP_IP 0x0021
#define PPP_IP6 0x0057
#define PPP_VSNP 0x005b
#define PPP_OSI 0x0023
#define PPP_IPX 0x002b

/*��ַ����*/
#define PPP_LOCAL_ALLOTADDR 1
#define PPP_RADIUS_ALLOTADDR 2
#define PPP_RADIUSPRI_ALLOTADDR 5

#define PPP_EAP_USER_NAME_256BYTE  256
#define VSNCP_RESERVED_LEN 500

/* EAP PACKET CODE */
#define EAP_PACKET_CODE_REQUEST        1
#define EAP_PACKET_CODE_RESPONSE       2
#define EAP_PACKET_CODE_SUCCESS        3
#define EAP_PACKET_CODE_FAILURE        4

/* PPP */
#define A11_SUBNET_LENGTH 37 /* SUBNET */
#define IMSI_S A11_IMSI_S

#define PPP_A11_ALARM_IMSI_LENGTH   15
#define PPP_A11_ALARM_BSID_LENGTH   12
#define PPP_A11_ALARM_BSID_BCD_LEN  6
#define PPP_A11_ALARM_SUBNET_LENGTH 74
#define PPP_A11_ALARM_MAX_NUM        500
#define IPV6_ADDR_LEN 8         /*IPV6��ַ����(ushort����)*/

#define Authentication_Fail 0x83
#define PPP_Negotiation_Fail 0xD2
#define RM_MAX_RADIUSGROUP_NUM 1000
#define AAA_DEFAULT_DOMAIN_INDEX 0xFFFF

#define M_DIAMAUTH_DYNAAA_AAA     1
#define M_DIAMAUTH_STATIC_AAA     0
/* ��һ�η��� DIAMETER ��Ϣ��־ */
#define DIAM_AUTH_FIRST_SEND      1
#define DIAM_AUTH_NO_FIRST_SEND   0


/*  ��PPP�����Ϣ����  */
#define PPP_DIAM_AAA_CREAT_REQ       1    /* ��Ȩ���� */
#define DIAM_AAA_PPP_CREAT_RSP       2    /* ��Ȩ��Ӧ */
#define PPP_DIAM_AAA_RELEASE_REQ     3    /* release���� */

/*��������ppp�û�����*/
#define PPP_USERTYPE_SIP 0
#define PPP_USERTYPE_MIP 1
#define PPP_USERTYPE_MIPAGENT 2
#define PPP_USERTYPE_NULL 3
#define VSNCP_OPTION_ATTACHTYPE_INIT     1
#define VSNCP_OPTION_ATTACHTYPE_HANDOFF  3
#define VSNCP_OPTION_ATTACHTYPE_LEN 3

typedef enum
{
    A11_SEND_ECHO,
    A11_STOP_ECHO
}A11_ECHO_E;

/* BEGIN: Added for PN:���pppЭ�̶�ʱ����Դ�������� by wangyong 00138171, 2013/12/21 */
typedef enum
{
    PPP_NEGO_LIST_NODE_LCP_START = 1,
    PPP_NEGO_LIST_NODE_VSNCP_RENEGO_START = 2,
    PPP_NEGO_LIST_NODE_MS_RELEASE_START = 3,
    PPP_NEGO_LIST_NODE_RP_RELEASE_START = 4,
    PPP_NEGO_LIST_NODE_TYPE_BUTT
} PPP_NEGO_LIST_NODE_TYPE_E;

/* END:   Added for PN:���pppЭ�̶�ʱ����Դ�������� by wangyong 00138171, 2013/12/21 */


/*VSNCP Configure Reject������*/
typedef enum
{
    PPP_VSNCP_GENERAL_ERROR = 0,
    PPP_VSNCP_UNAUTHORIZEDN_APN,
    PPP_VSNCP_EXCEED_PDN_LIMIT,
    PPP_VSNCP_NO_PGW,
    PPP_VSNCP_PGW_UNREACHABLE,
    PPP_VSNCP_PGW_REJECT = 5,
    PPP_VSNCP_INSUFFICIENT_PARAS,
    PPP_VSNCP_RES_UNAVAILABLE,
    PPP_VSNCP_ADMIN_PROHIBITED,
    PPP_VSNCP_PDN_INUSE,
    PPP_VSNCP_SUBSCRIPTION_LIMIT = 10,
    PPP_VSNCP_APN_EXIST,
    /* �����codeֵ��˽�е� */
    PPP_VSNCP_DECODE_OK,
}PPP_VSNCP_REJECT_ERRCODE_E;


/* ��Ȩ��Ӧ */
typedef struct tagDIAMAuthRspMsg
{
    VOS_UINT32 ulMsgCode;                                                    /* ��Ϣ�� */
    VOS_UINT32 ulSDBIndex;                                                   /* context���� ��SDB���� */
    VOS_UINT32 ulQosProfileID;                                               /* qos profile id */
    VOS_UINT32 ulSessionTimeout;                                             /* session timeout */
    VOS_UINT32 ulAccountInterval;                                            /* Accounting-Interim-Interval */
    VOS_UINT32 ulDefaultAPNId;                                               /* default APN id */
    VOS_UINT32 ulULMaxBw;                                                    /* �������������� */
    VOS_UINT32 ulDLMaxBw;                                                    /* �������������� */
    VOS_UINT32 ulResultCode;                                                 /* result code */
    VOS_UINT32 ulEAPLen;                                                     /* EAP LEN */
    DIAM_AUTH_APN_INFO_S stApnInfo[DIAM_AUTH_APN_INFO_MAX_NUMBER];      /* APN CONFIGURATION */
    VOS_UINT16 usPeerId;                                                    /* PEER ID */
    VOS_UINT16 us3GPPCC;                               /* �Ʒ����� */
    UCHAR aucUsername[DIAM_AUTH_USERNAME_MAX_LEN + 1];                       /* �û��� */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];                           /* Mobile-Node-Identifier */
    UCHAR ucUsernameLen;                                                /* �û������� */
    UCHAR ucResult;                                                     /* ��Ȩ��� */
    UCHAR ucApnInfoNum;                                                 /* APN INFO���� */
    UCHAR ucStateLen;                                                   /* APN INFO���� */
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucMSK[DIAM_AUTH_MSK_LEN];                                    /* MSK */
    UCHAR aucMdn[MDN_MAX_LEN+1];                                        /* ����MDN���� */
    UCHAR aucEAP[4];                                                    /* EAP */
}DIAM_AUTHRSP_S;

/* diam��Ȩ���� */
typedef struct tagPppDiamAuthMsg
{
    VOS_UINT32 ulMsgType;            /* ��Ϣ���� */
    VOS_UINT32 ulRpIndex;            /* SDB���� */
    VOS_UINT32 ulNowUTCInSec;
    VOS_UINT32 ulReleaseCode;
    VOS_UINT16 usPeerID;            /* diameter aaa server ID */
    VOS_UINT16 usEAPlen;            /* EAP len */
    VOS_UINT16 usTokenId;           /* �����ĵ�TOKEN ID */
    VOS_UINT16 usDynLocalPeerId;    /* ��̬aaa����������local���� */
    UCHAR ucAAAType;
    UCHAR ucRsv;
    UCHAR ucStateLen;
    UCHAR ucFirstSendFlag;
    A11_IMSI_S stIMSI;
    UCHAR aucUserName[DIAM_AUTH_USERNAME_MAX_LEN + 1];
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucAAAHost[DIAM_AUTH_DRA_HOST_MAX_LENGTH + 1];        /* origin host */
    UCHAR aucAAARealm[DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH + 1];       /* origin realm */
    UCHAR aucEAP[4];
}PPP_DIAM_AUTH_MSG_S;



enum enumPPPFailedFlag
{
    PPPNEGOFAIL = 0,
    PPPLOWEDOWN,
    PPPUSERDOWN,
    PPPL2TPDOWN,
    LAPRECYCLE,
    /* Added start by c00127007 at 2010-03-30 PDSNV9R7C05 for �����Ż� */
    PPPA11DOWN,
    PPPFADOWN,
    PPPPCRFCFAIL, /*pcrfc����ʧ��*/
    PPPLICESEERROR,
    PPPA11DOWNNOLCPTER, /*����Ҫ����lcp termination*/
    /* Added end by c00127007 at 2010-03-30 PDSNV9R7C05 for �����Ż� */
};


/* PPP_A11_Alarm���ýṹ */
typedef struct tagAlarmLink
{
    VOS_UINT32 ulPDSNIP;     /* PDSN IP */
    VOS_UINT32 ulPcfIP;      /* PCF IP */
    UCHAR ucIMSI[PPP_A11_ALARM_IMSI_LENGTH + 1];   /* IMSI */
    VOS_UINT32 ulTimestamp;  /* Timestamp */
    UCHAR ucErrorCode;  /* Error Code */
    UCHAR ucBSID[PPP_A11_ALARM_BSID_LENGTH + 1];   /* BSID */
    UCHAR aucSubnet[PPP_A11_ALARM_SUBNET_LENGTH + 1]; /* SUBNET */
    #ifdef __LINUX_PLATFORM__
    UCHAR ucReserve456567[3];
    #endif
}VOS_PACKED PPPA11_AlarmLink_S;


/* upʱ�Ĳ��� */
typedef struct tagPppLUpPara    /* �ײ�UP���Ĳ��� */
{
    IMSI_S stIMSI;              /* IMSI */
    VOS_UINT32  ulPcfIP;
    VOS_UINT16 usPcfIndex;
    VOS_UINT16 usTokenId;
    UCHAR  ucServiceOpt;
    UCHAR  beHRPDMode:1,
           bReserv:7;
    UCHAR  ucBSID[6];
    UCHAR  aucSubnet[A11_SUBNET_LENGTH + 1];      /*Subnet For HRPD d7*/
} PPP_LUPPARA_S;



/* downʱ�Ĳ��� */
typedef struct tagPppLDownPara    /* �ײ�UP���Ĳ��� */
{
    VOS_UINT32 ulLcpSendFlag;
} PppLDownPara;

/* AAA��PPPC����Ϣ */
typedef struct tagPppcAaaAuthReq
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
    UCHAR ucIMSI[8];                /* IMSI */
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

}PPPC_AAA_AUTH_REQ_S ;

typedef enum
{
    LCP_INFOR = 1,   /* LCP ��Ϣ */

    IPCP_INFOR,      /* IPCP ��Ϣ */

    SCP_INFOR,

    IPCPV6_INFOR,     /* IPV6 IPCP ��Ϣ */

    VSNCP_INFOR,      /* VSNCP ��Ϣ */

    MAGICNUM_INVALID, /* magic number ��Ч��־ */
} PPPC_USR_INFOR_FLAG_E;    /* PPPC�����û���Ϣʱʹ�õı�־ */

#define PPP_CPU_2_ON_SPU 2
#define PPP_SET_IPTECH(pppinfo, iptech) \
        if (PPP_USERTYPE_NULL == pppinfo->bIPTech ) \
        {\
            pppinfo->bIPTech = (iptech);\
        }



#define PPP_SELF_SGID      g_stPppCompInfo.ullSelfSgId

#define PPP_CPU_OFFLINE  0  /* CPU����λ */
#define PPP_CPU_ONLINE   1  /* CPU��λ */


VOS_UINT32 PPP_Shell_OutPut(VOS_UINT32 ulRpindex, PMBUF_S *pstPMBuffNew, VOS_UINT16 usProtocol);
VOS_UINT32 PPP_StartIPV4CP(VOS_UINT32 ulRpIdx, VOS_UINT32 ulIpAddr, VOS_UINT32 ulPriDns, VOS_UINT32 ulSecDns);
VOS_UINT32 PPP_StartIPV6CP(VOS_UINT32 ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns);
VOS_UINT32 PPP_StopIPV4CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_StopIPV6CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_ReleaseIPV4CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_ReleaseIPV6CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_SendFakeIPV4CPReqMsg(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_SendFakeIPV6CPReqMsg(VOS_UINT32 ulRpIndex);

VOS_UINT32 PPP_ipv6_addr_check(VOS_UINT16 *pstIpv6addr);
VOS_UINT32 PPP_GetNowUTCInSec(VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPStop(VOS_UINT32 ulRpIdx, UCHAR ucPDNId, VOS_UINT32 ulReleaseCode);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPStart(VOS_UINT32 ulRpIdx, UCHAR ucPDNId, UCHAR *pucPacket);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPRenegoStart(VOS_UINT32 ulRpIdx, UCHAR ucPDNId);
extern VOS_UINT32 PPP_GetRetryInterval(VOID);
extern VOS_UINT32 PPP_Shell_L2tpProc(VOS_UINT32 ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara);
extern VOS_UINT32 PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode);
extern VOID PPP_PDNSendVSNCPReject(VOS_UINT32 ulRPIndex, UCHAR *pucMsg, UCHAR ucErrCode);
extern VOS_UINT32 PPP_GetIpV6Capbility(VOID);
extern VOID PPP_PDNClearVSNCP(PDN_CONTEXT_S *pstPDNContext);
extern VOS_UINT32 A11_PPPC_EchoSet(A11_ECHO_E ucFlag, VOS_UINT32 ulRPIndex);
extern VOS_UINT32 AM_PPP_SendMsgToLap2(USM_LAP2_MSG_S* pstMsg);
extern VOS_UINT32 InsertAlarmLink(PPPA11_AlarmLink_S *pstAlarmLink);
extern VOS_UINT32 PPP_SendRtMsg(VOS_UINT64 ullSrtCsi,VOS_UINT64 ullDstCsi, VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgCode, UCHAR *pucMsg, VOS_UINT32 ulMsgLen );
extern VOS_UINT32 PPP_GetPeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusPeerId);
extern VOS_UINT32 PPP_GetAAAType(VOS_UINT32 ulRpIndex, UCHAR *pucAAAType);
extern VOID PPP_SetSendSTRFlag(VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState);
extern VOS_UINT32 PPP_GetIpAddrByBufReq( VOS_UINT32 ulRpIndex, VOS_UINT32 *pulReqIpAddr );
extern VOS_UINT32 PPP_BackupMasterCreUpdPppProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType,
                                                  UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 PPP_BackupSlaveCreUpdPppProc(UCHAR *pucCurrent);

extern VOS_UINT64 PPP_GetLocalL2tpCsi(VOID);
extern VOID PPP_BackupRestoreVsncp(PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId);
extern VOID PPP_BackupSlaveDelResource(VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_BackupSmoothPppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext);

VOID PPP_BackupSmoothSubBoardDown(VOID);


extern VOID PPP_IpcpTimeOutProcForPdn(VOS_UINT32 ulRpIndex);
extern VOID PPP_UpdatePcfInfo(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPcfIp, VOS_UINT16 usPcfIndex);




extern VOS_UINT32 PPP_USMStartVsncp(UCHAR *pucVsncpMsg, VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_RPNodeDelete(VOS_UINT32 ulRPIndex);
extern VOID PPP_RPNegoListProc(VOID* pPara);
extern VOS_UINT32 PPP_RPNodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR ucNodeType);
extern VOS_UINT32 PPP_A11_GetSubBoardStat( UCHAR ucDmpuId);

#endif


