/*************************************************************************************
*
*                       fa_pub.h
*
*  ��Ŀ���룺           WCDMA PDSN9660 V900R008
*  �������ڣ�           2011/10/24
*  ���ߣ�               wangxiaoyu 167726
*  �޸���ʷ�б�
*  �ο��ĵ���       
*  ���ܣ�               FA���⹫���궨�塢ȫ�ֱ������ӿں���                
*  ������                  
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/
#ifndef __FA_AM_PUBLIC_H__
#define __FA_AM_PUBLIC_H__

#ifdef      __cplusplus
}
#endif 

/*******************************************************************************************************/
/********************                          �궨��                           ************************/
/*******************************************************************************************************/
/*FA�¼�λ*/
#define FA_SD_EVENT             0x01
#define FA_DPE_EVENT            0x02
#define FA_TIMER_EVENT          0x04
#define FA_PDN_EVENT            0x08
#define FA_AUTH_EVENT           0x20


/*���ȶ���*/
#define FA_AAA_CHALLENGE_LEN    253
#define FA_SHARED_KEY_MAX_LEN   128
#define FA_AAA_CHAP_PWD_LEN     255

#define FA_SKEY_MAX_LEN         18
#define FA_MIP_IMSI_LEN         15  /* IMSI��󳤶� */
#define FA_CFG_KEY_LEN          16
#define PRE_SHARED_KEY_MAX_LEN 128
#define FA_CHALLENGE_LEN 16

/*MIP ��Ϣ��*/
#define MIP_REGISTRATION_REQUEST  0x01    /* MIP-Registration Request ��Ϣ */
#define MIP_REGISTRATION_REPLY    0x03    /* MIP-Registration Reply   ��Ϣ */
#define MIP_REVOCATION_REQUEST    0x07    /* MIP-Revocation ��Ϣ */
#define MIP_AGENT_SOLICITATION    0x0a    /* MIP-Agent Solicitation ��Ϣ */
#define MIP_REVOCATION_ACK        0x0F    /* MIP-Revocation Ack��Ϣ */
#define MIP_ADVERTISEMENT         0x10    /* MIP ����㲥��Ϣ */



#define FA_MIPAGENT_GRP_MAXNUM 1000    /*MipAgent ��ʹ�õ��������*/
#define   FA_PDN_PMIP_RESPONSE   0

#define FA_AAA_CHALLENGE_LEN    253
#define FA_AAA_CHAP_PWD_LEN     255
#define PRE_SHARED_KEY_MAX_LEN 128

/*����ͳ�ƼӲ���*/
#define M_FA_MIPPER_ADD(x)  if ( VOS_NULL != (x) ) {(VOS_VOID)PerfSetFamPerfCounterByAddress((x), A11_PERF_OPERATOR_PLUS, 1); }

/*����ͳ�Ƽ�����*/
#define M_FA_MIPPER_DEC(x)  if ( VOS_NULL != (x) ) {(VOS_VOID)PerfSetFamPerfCounterByAddress((x), A11_PERF_OPERATOR_SUB, 1);  }

typedef enum
{
    FA_ENCAP_TYPE_IPINIP = 1,
    FA_ENCAP_TYPE_MINI,
    FA_ENCAP_TYPE_GRE,
} FA_ENCAP_TYPE_E;

typedef enum tagFA_MIP_MODE_E
{
    E_PMIP_HUAWEI = 0,   /* ���ջ�Ϊ˽�����ԣ�Ĭ��ֵ */
    E_PMIP_CNTEL,        /* �����й����Ź淶*/
    E_PMIP_BUTT
}VOS_PACKED FA_MIP_MODE_E;

/*PDN֪ͨFA ����Ϣ��*/
typedef enum
{
    FA_MSG_CODE_PMIP_CREATE,       /* PDN֪ͨFA����PMIP�û�������Ϣ */
    FA_MSG_CODE_PMIP_UPDATE,       /* PDN֪ͨFA����PMIP�û�������Ϣ */
    FA_MSG_CODE_PMIP_DEACTIVE,       /* PDN֪ͨFA����PMIP�û�������Ϣ */

    FA_MSG_CODE_CMIP_CREATE,       /* PDN֪ͨFA����CMIP�û�������Ϣ */
    FA_MSG_CODE_CMIP_DEACTIVE,       /* PDN֪ͨFA����CMIP�û�������Ϣ */

}FA_MSG_CODE_E;

/*FA����PDN����Ϣ��*/
typedef enum
{
    FA_PDN_MIP_SUCCESS = 0,    /*����ɹ�*/
    FA_PDN_MIP_FAIL,           /*����ʧ�ܻ���ȥ��*/ 
} FA_PDN_MIP_MSG_CODE_E;


/* PDN ģ�鷢��FA��PMIP �û���������ʱ����Ϣ�ṹ*/
typedef struct tagFA_PDN_MIPAGENT_REQ_S
{
    VOS_UINT32   ulPdnIndex;         /* PDN����������*/
    VOS_UINT32   ulHaAddr;           /*HA Ipaddress*/

    VOS_UINT32   ulHomeAddr;         /*Home address*/
    VOS_UINT32   ulSpi;              /*MN-HA SPI*/
    VOS_UINT32   ulPiSubIndex;
    VOS_UINT32   ulCofAddr;       /*COF address*/

    VOS_UINT32   ulUpdateMask;
    VOS_UINT16  usDomainIndex;     /*������*/
    VOS_UINT16  usLifetime;         /* MIP ��·��lifetime */
    
    VOS_UINT16  usVpnID;
    UCHAR   aucSKey[FA_SKEY_MAX_LEN];  /*MN-HA Key*/

    UCHAR   aucNai[A11_MAX_NAI_LENGTH + 1];

    VOS_UINT16  usReservr43667;
    UCHAR   ucStcValue;         /* AAA���ص�stc */
    UCHAR   ucKeyLen;           /*MN-HA Key����*/
} FA_PDN_MIPAGENT_REQ_S;
 
/*FAģ����PDNģ�鷵��CMIP +PMIP ����������Ϣ�ӿ�*/
typedef struct tagFA_PDN_MIPAGENT_RSP_S
{
    VOS_UINT32     ulPdnIndex;      /* PDN����������*/
    UCHAR     ucMsgCode;       /* ������, FA_PDN_MIP_MSG_CODE_E */
    UCHAR     ucReason;        /* :0 ��ʾfa�ظ�����Ӧ��Ϣ����0 ��ʾ����ԭ��ֵ*/    
    UCHAR     ucEncapType;     /* �û����ݷ�װ����: 1 - IPinIp, 2 - Mini, 3 - GRE*/ 
    UCHAR     ucGRESwitchFlag:1;      /*GRESwitchFlag*/
    UCHAR     ucRevTunnelFlag: 1;    /*support reverse tunnel*/
    UCHAR     ucMsSendMethodFlag: 1;    /*MS send method on reverse tunnel*/
    UCHAR     ucReserd:5;
    VOS_UINT32     ulHomeAddr;      /* Home address*/
    VOS_UINT32     ulPriDnsIp;      /* ��DNS��ַ */
    VOS_UINT32     ulSecDnsIp;      /* ��DNS��ַ */
    VOS_UINT32     ulHaIp;          /* ha ip */    
    VOS_UINT32     ulFaIp;          /* fa ip */    
    VOS_UINT32     ulMipKey;
    VOS_UINT16    usDomainIndex;
    UCHAR     ucResv[2];     
} FA_PDN_MIPAGENT_RSP_S;

/* pdn ��Ϣ�ṹ֪ͨFA CMIP �û�����/ ������Ϣ�ṹ�� */
typedef struct tagFA_PDN_CMIP_MSG_S
{
    VOS_UINT32     ulPdnIndex;        /* PDN����������*/
    UCHAR     ucReserv[2];
    VOS_UINT16    usTdormant;        /* PPPЭ�̵�Lifetime */
} FA_PDN_CMIP_MSG_S;

/*FA���͸�AUTH ��֤����Ϣ�ṹ*/
typedef struct tagFA_AAA_AUTHREQ_S
{
    VOS_UINT32     ulMsgType;        /* ��Ϣ���� */
    VOS_UINT32     ulVistLstIndex;   /* Vistor List table Index*/
    VOS_UINT32     ulSdbIndex;    
    VOS_UINT32     ulPDNIndex;
    VOS_UINT32     ulCorrelationID;  /* correlation id*/
    VOS_UINT32     ulHaAddr;         /* HA address*/
    VOS_UINT32     ulFrameIPAddr;    /* Home address*/
    VOS_UINT16    usCDBIndex;       /* domain index*/
    UCHAR     ucPktID;          /* �û���֤�����ID */
    UCHAR     ucReserv;         /* ���ֽڶ���*/
    
    UCHAR     ucUsernameLen;                        /* �û������� */
    UCHAR     ucUsername[A11_MAX_NAI_LENGTH];       /* �û��� */

    UCHAR     ucChapPwdLen;                         /* ���볤�� */
    UCHAR     ucChapPwd[FA_AAA_CHAP_PWD_LEN];       /* ���� */

    UCHAR     ucChapChallengeLen;                   /* Response���� */
    UCHAR     ucChapChallenge[FA_AAA_CHALLENGE_LEN];/* Chap-Challenge */
    UCHAR     ucResv[2];

    UCHAR     ucIMSI[8];                 /* IMSI */
} FA_AAA_AUTHREQ_S;


typedef struct tagFaAaaAuthRepMsg
{
    VOS_UINT32     ulMsgType;
    VOS_UINT32     ulSdbIndex;
    VOS_UINT32     ulVistLstIndex;
    VOS_UINT32     CorrelationID;
    VOS_UINT32     ulHaAddr;
    VOS_UINT32     ulFrameIPAddr;
    VOS_UINT32     SecurityLevel;
    VOS_UINT32     ReverseTunnel;
    VOS_UINT32     KeyID[5]; 

    VOS_UINT32 IpQoS; 
    VOS_UINT32 DiffServicesMarking1;        
    VOS_UINT32 DiffServicesMarking2;    
    VOS_UINT32 DiffServicesMarking3;    
    VOS_UINT32 ulPIMARY_DNS_SERVER;      
    VOS_UINT32 ulSECOND_DNS_SERVER;      
    VOS_UINT32 AlwaysOn;    
    VOS_UINT32 ServicesOptionProfile1;    
    VOS_UINT32 ServicesOptionProfile2;    
    VOS_UINT32 RemoteIPv4Addr;   
    VOS_UINT32 RemoteIPv4AddrMask;    
    VOS_UINT32 RemoteIPv6Addr1;   
    VOS_UINT32 RemoteIPv6Addr2;    
    VOS_UINT32 RemoteIPv6Addr3;    
    VOS_UINT32 RemoteIPv6Addr4;    
    VOS_UINT32 RemoteAddrTblIndex;    
    VOS_UINT32 MnAaaRemove;   
    VOS_UINT32 Deactivetime;    
    VOS_UINT32 ulSessionTime;

    UCHAR PreSharedSecret[PRE_SHARED_KEY_MAX_LEN];    
    
    UCHAR ucSecLen;
    UCHAR ucStcValue;
  
    UCHAR ucResult;    
    UCHAR ucPktID;    

    VOS_UINT32 ulInputPeakRate;  
    VOS_UINT32 ulOutputPeakRate; 
    VOS_UINT32 ulGuarantBitRateUp; 
    VOS_UINT32 ulGuarantBitRateDown; 

    UCHAR ucRateFlag;
    UCHAR uzReserv3[2];    
    UCHAR aucMdn[MDN_MAX_LEN+1];
    UCHAR aucVpnName[RD_HW_VPN_NAME_LEN_MAX + 1];
    
    VOS_UINT32   ulAcctInterimInterval;
    A11_QOS_INFO_S stA11QoS;
    VOS_UINT16  bulIpQosFlag : 1,                  /* IP Qos */ 
            bulInputPeakRateFlag : 1,  /*���з�ֵ���ʣ� ��λΪbps*/
            bulOutputPeakRateFlag : 1, /*���з�ֵ���ʣ� ��λΪbps*/
            bulGuarantBitRateUpFlag : 1, /*PDSN�û����б�֤���� (bps)*/
            bulGuarantBitRateDownFlag : 1, /* PDSN�û����б�֤����(bps) */
            bulAllowed_AB_BETFlag : 1, /*bps*/
            bulMaxConnectionFlag : 1,
            bucRateFlagFlag : 1,
            bucAllowed_PTFTsFlag : 1,  /* Allowed Persistent TFTs */
            bucMaxPerFlowPriorityforUserFlag : 1,        /* Maximum Per Flow Priority for the User  */
            bucInterUserPriorityFlag : 1,                /* Inter-User Priority */
            bstA11SOProfileFlag : 1,
            bstAuthFlowProfileIDFlag : 1,     /* Authorized Flow Profile IDs for the User */    
            bstAllowedDSCPMarkingFlag : 1, /* Allowed Differentiated Services Marking */
            bszUserProfileNameFlag :1;
    
    UCHAR  ucUserClassAAAFlag : 1;
    UCHAR  ucActiveStopIndication:1;     /*Accounting-Stop-triggered-by-Active-Stop-Indication */  
        
    UCHAR  szUserProfileName[PDN_USER_PROFILE_NAME_LENGTH + 1];    /*User Profile���Ƶ��ַ���*/

} FA_AAA_AUTHREP_S;

typedef struct tagFA_SD_TABLE_MSG_S
{
    UCHAR ucScID;           /*Sc���߼�VCPU ID*/
    UCHAR aucRes[3];        /**/
    VOS_UINT32 ulIdLow;          /*ID low*/
    UCHAR aucNai[A11_MAX_NAI_LENGTH + 1];       /*NAI*/
} VOS_PACKED FA_SD_TABLE_MSG_S;

/*FA����NP�����н����������*/
typedef struct tagFA_DOWN_TUNNEL_LEAF_S
{
    VOS_UINT32  ulMNaddrHigh;    /* MN's home address*/
    VOS_UINT32  ulMNaddrLow;     /* ipv4ʱ��ȫF */
    VOS_UINT32  ulHAaddrHigh;    /* HA's address*/
    VOS_UINT32  ulHAaddrLow;     /* ipv4ʱ��ȫF */
    VOS_UINT32  ulFAaddrHigh;    /* FA's address*/
    VOS_UINT32  ulFAaddrLow;     /* ipv4ʱ��ȫF */
    VOS_UINT16 usVpnId;         /* VPN ID*/
    UCHAR  ucDpeId;         /* DPE ID*/
    UCHAR  ucResv; 
    VOS_UINT32  ulUserIndex;     /* PDP����*/
} VOS_PACKED FA_DOWN_TUNNEL_LEAF_S;


/* �·�NP���н������������������� */
typedef enum
{
    FA_ADD_NP_TBL = 0,   /* ���ӱ��� */

    FA_DEL_NP_TBL,       /* ɾ������ */

    FA_UPD_NP_TBL,       /* ���±��� */

    FA_ASY_NP_DEL
} FA_NP_TBL_ACT_TYPE_E;  

/* PDN֪ͨfa�Ĳ������� */
typedef enum
{
    PDN_FA_PMIP_START = 0,      /*start the Pmip service */
    PDN_FA_PMIP_DEACTIVE,       /*deactive the Pmip user*/
    PDN_FA_PMIP_UPDATE,
} PDN_FA_MSG_CODE_E;  

typedef struct tagFA_A11_INFO_S 
{

    VOS_UINT32  ulIndex;         /* ���������� */
    VOS_UINT32  ulCofAddr;       /*COF address*/
    VOS_UINT32  ulHaAddr;        /*Home Agent address*/
    VOS_UINT32  ulPriDnsIp;
    VOS_UINT32  ulSecDnsIp;
    VOS_UINT16 usLifetime;      /* MIP Lifetime*/
    UCHAR  ucUserType;      /* �û���������: 0 - CMIPv4, 1 - PMIPv4, 2 - CMIPv6, 3 - PMIPv6*/
} FA_A11_INFO_S;

/* ����ͳ�ƽṹ */
typedef struct tagFA_PERFSTATISTIC_S
{
    VOS_SIZE_T pulRcvRrqNum; /* FA�յ�ע���������� */
    VOS_SIZE_T pulRelayRrq;  /* FAת����HA��ע����������*/
    VOS_SIZE_T pulDenyUnknow;/* ��Ϊδ��ԭ����ش�����ܾ�ע����������� */
    VOS_SIZE_T pulDenyAdmin;/* ��Ϊ�����ϵĽ�ֹ�����룺65����ش�����ܾ�ע�����������*/
    VOS_SIZE_T pulDenyResource;/* ����Դ����(Code 66)����ش�����ܾ�ע����������� */
    VOS_SIZE_T pulDenyAaaAuth;/* ���ƶ��ڵ���֤ʧ��(Code 67)����ش�����ܾ�ע�����������*/
    VOS_SIZE_T pulDenyLifeTime;/* ���������������̫��(Code 69).����ش�����ܾ�ע�����������*/
    VOS_SIZE_T pulDenyRrqForm; /*  ��������Ϣ��ʽ����(Code 70)����ش�����ܾ�ע����������� */
    VOS_SIZE_T pulDenyEncap; /* ������ķ�װ��Ч(Code 72)����ش�����ܾ�ע�����������*/
    VOS_SIZE_T pulDenyRegTimeOut;  /* FA��ע�ᳬʱ���ܾ���ע�������������������78�� */
    VOS_SIZE_T pulRcvValidRrpNum;/* FA�յ�HA��ע��Ӧ������*/
    VOS_SIZE_T pulRelayRrpNum;/* FAת����MN��ע��Ӧ������*/
    VOS_SIZE_T pulRcvInvalidRrp;/* FA�յ�����Чע��Ӧ������ */
    VOS_SIZE_T pulDenyHaAuth; /* ��HA����֤ʧ��(Code 68)���µ���ش���ܾ�ע��Ӧ�������*/
    VOS_SIZE_T pulSendRevo;   /* FA������Revocation��Ϣ���� */
    VOS_SIZE_T pulRcvRevo;  /* FA�յ���Revocation��Ϣ���� */
    VOS_SIZE_T pulMipCurUsrNum;/* ��ǰ�����ƶ�IP�û��� */
    
    VOS_SIZE_T pulPmipRrqNum;/* PMIP�û�FA���͸�HA��ע���������� */
    VOS_SIZE_T pulPmipRrpNum;/* PMIP�û�FA�յ�HA��ע��Ӧ������ */
    VOS_SIZE_T pulPmipSuccsRrpNum; /* PMIP�û�FA�յ�HA�ĳɹ�ע��Ӧ������ */
    VOS_SIZE_T pulPmipCurUsrNum;/* ��ǰPMIP�û��� */
    VOS_SIZE_T pulPmipActReqNum;/* PMIP�Ự���������� */
    VOS_SIZE_T pulPmipActSuccsNum;/* PMIP�Ự����ɹ��� */
    VOS_SIZE_T pulDenyRrpForm ;/* ��Ӧ����Ϣ�ĸ�ʽ����(Code 71)�������ľܾ�ע��Ӧ������� */
} FA_PERFSTATISTIC_S;

/*******************************************************************************************************/
/********************                        ȫ�ֱ���                           ************************/
/*******************************************************************************************************/
extern VOS_UINT32 g_ulFaTaskId;                  /* FA����ID */

extern VOS_UINT32 g_ulTimerToFaQueId;            /* FA��ʱ����Ϣ���� */
extern VOS_UINT32 g_ulPdnToFaQueId;              /* FA��PDN��Ϣ���� */
extern VOS_UINT32 g_ulAuthToFaQueId;             /* FA��AUTH��Ϣ���� */

extern MC_QUE_ID g_pDpeToFaQueID ;     /* ����DPE���͵�FA��RRQ�������*/
extern MC_QUE_ID g_pSdToFaQueID;            /* ����SD��FA�Ĺ�����Ϣ���� */
extern MC_QUE_ID g_pDpeToFaRvcQueID;

extern UCHAR g_ucPmipFaMode;                /* FA����ģʽ, ���48 */


extern VOS_UINT32 g_ulFaMipUserCounter; /*mip license*/
extern VOS_UINT32 g_ulFaMaxMipUserNum; /*��ǰmip�û���*/
extern FA_PERFSTATISTIC_S g_stFaPerfStatistic;    /*����ͳ������*/

/*******************************************************************************************************/
/********************                        �ⲿ�ӿ�                           ************************/
/*******************************************************************************************************/
//extern VOS_UINT32   FA_SetA10Tbl(VOS_UINT32 ulRpIndex, DPS_CP_A10_CMDBLOCK_S* pstA10Tbl);
extern VOS_UINT32 FA_PrintMipData(VOS_UINT32 ulPdnIndex, UCHAR* pucBuff);    /*������MIP�ֶ����*/
extern VOS_UINT32 FA_GetContexSize(VOS_VOID);
extern VOS_UINT32 FA_GetContextInfoByPdnIndex(VOS_UINT32 ulPdnIndex , FA_A11_INFO_S* pstFaA11Info);
extern VOID FA_MipVpnInit(VOS_VOID);
extern VOID FA_MipPccInit(VOS_VOID);
extern VOS_UINT32 FA_GetSduIdByNaiHash (VOS_UINT32 ulHashTblNum, VOID* pData);
extern VOS_UINT32 FA_WhtherSendNaiTokenToSDU(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR **ppucNai);
extern VOID FA_FreeResBeforeFreePdnRes(VOS_UINT32 ulPdnIndex);
extern VOS_UINT32 FA_BackupMasterCreUpdFaProc(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 FA_BackupSlaveCreUpdFaProc(UCHAR *pucCurrent);
extern VOS_UINT32 FA_BackupMasterUpdFaAdvSeqProc(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 FA_BackupSlaveUpdFaAdvSeqProc(UCHAR *pucCurrent);

extern VOS_UINT32 FA_BackupSmoothFaContext(PDN_CONTEXT_S *pstPdnContext);
extern VOS_UINT32 FA_GetRpIndexByFaIndex(VOS_UINT32 ulFaIndex, VOS_UINT32 *pulRpIndex);
extern VOS_UINT32 FA_A11UpdateNpTable( VOS_UINT32 ulFaIndex );
extern VOS_UINT32 FA_PdnCheckPccSwitch(UCHAR ucPdnType);
extern VOS_UINT32 FA_ResCheckByFaContextIndex(VOS_UINT32 ulFaContextIndex);
extern VOS_UINT32 FA_OmInitial(VOID);
#ifdef      __cplusplus
}
#endif 

#endif
