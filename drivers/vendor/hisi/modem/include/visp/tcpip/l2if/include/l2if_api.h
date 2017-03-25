/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              l2if_api.h
*
*  Project Code: VISPV1R7
*   Module Name: L2IF  
*  Date Created: 2008-10-18
*        Author: LY(57500)
*   Description: l2ifģ������ṩapi�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-10-18  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _L2IF_API_H_
#define _L2IF_API_H_
    
#ifdef __cplusplus
extern "C"{
#endif

/* L2IFģ������붨�� */
typedef enum enumL2IfErrCode
{
    L2IF_OK = VOS_OK,                 /* 0 OK                                       */
    L2IF_ERR,                         /* 1 δ֪����                                 */
    L2IF_ERR_NO_REGISTER = MID_COMP_L2IF + 1, /* 2 L2���δע��                     */
    L2IF_ERR_MEM_ALLOCFAIL,           /* 3 �����ڴ�ʧ��                             */
    L2IF_ERR_NULL_POINTER,            /* 4 null pointer                             */
    L2IF_ERR_STR_TOOLONG,             /* 5 ������ַ������ȹ���                     */
    L2IF_ERR_PORTFLAG_INVALID,        /* 6 ����port�ӿ�flag��������                 */
    L2IF_ERR_PHYFUNC_NOREG,           /* 7 û��ע��PORT�ײ�ָ��                     */
    L2IF_ERR_PHYTRANS_FAILED,         /* 8 PORT�ײ㱨�ķ���ʧ��                     */
    L2IF_ERR_PHYIOCTL_FAILED,         /* 9 PORT�ײ�����·�ʧ��                     */
    
    L2IF_ERR_NULL_OUTPOINTER,         /* 10 ���ָ�����Ϊ��                        */
    L2IF_ERR_GETPHYLINKERR,           /* 11 ��ȡPhylinkʧ��                         */
    L2IF_ERR_PORT_NOTL2IFPORT,        /* 12 �˿ڷǶ���ӿ�                          */
    L2IF_ERR_PORT_NOTEXIST,           /* 13 port�޶�Ӧ�˿���Ϣ                      */
    L2IF_ERR_VLAN_SUPER,              /* 14 VLANΪS***R VLAN                        */
    L2IF_ERR_VLAN_INVALID,            /* 15 VLAN ID��Ч                             */
    L2IF_ERR_VLAN_PPICMD,             /* 16 Vlan �·�NP�����ִ���                   */
    L2IF_ERR_VLAN_PPINOREGISTER,      /* 17 VLAN �·�NP PPI�ӿ�δע��               */
    L2IF_ERR_PORT_PPINOREGISTER,      /* 18 PORT �·�NP PPI�ӿ�δע��               */
    L2IF_ERR_MAC_PPINOREGISTER,       /* 19 MAC �·�NP PPI�ӿ�δע��                */
    
    L2IF_ERR_QINQ_PPINOREGISTER,      /* 20 QINQ �·�NP PPI�ӿ�δע��               */    
    L2IF_ERR_PARA_WRONG,              /* 21 ��������                                */
    L2IF_ERR_VLAN_NOEXIST,            /* 22 VLAN������                              */
    L2IF_ERR_VLAN_TYPE,               /* 23 VLAN���ʹ���                            */
    L2IF_ERR_VLAN_MAXSUPER,           /* 24 S***r Vlan�����Ѵﵽ1024                */
    L2IF_ERR_VLAN_MAXSUB,             /* 25 ����S***r VLAN��Sub VLAN�����Ѵﵽ1024  */
    L2IF_ERR_SUBVLAN_INOTHERSUPER,    /* 26 Sub Vlan�Ѽ�������S***r Vlan            */
    L2IF_ERR_VLAN_SUB,                /* 27 VLAN����ΪSub VLAN                      */
    L2IF_ERR_SUBVLAN_NOTINSUPER,      /* 28 Sub VLANû�м���S***r VLAN              */
    L2IF_ERR_VLAN_SUPERNOUP,          /* 29 UP sub vlanʱ��,sup** vlan��û��up      */
    
    L2IF_ERR_VP_NULLPOINT,            /* 30 VP�������ָ��Ϊ��                      */    
    L2IF_ERR_PORT_NULLPOINT,          /* 31 PORT�������ָ��Ϊ��                    */
    L2IF_ERR_PORT_GETIFFAIL,          /* 32 ��ȡifnetָ��ʧ��                       */
    L2IF_ERR_VLAN_NOT_SUPER,          /* 33 VLAN ����su**r vlan                     */
    L2IF_ERR_VLAN_HAVEL3IF,           /* 34 ���ڸ�VLAN��Ӧ������VLAN IF             */
    L2IF_ERR_VP_VLANHASPORT,          /* 35 �ж˿ڼ�����VLAN                        */
    L2IF_ERR_PORT_PPICMD,             /* 36 PORT�·������ִ���                      */
    L2IF_ERR_PORT_MAXNUM,             /* 37 �������˿���                          */
    L2IF_ERR_PORT_NOUSED,             /* 38 �˿ڲ�����                              */
    L2IF_ERR_PORT_LIMITTYPE,          /* 39 �˿��������ʹ���                        */
    
    L2IF_ERR_PORT_INVALIDLINKTYPE,    /* 40 �˿ڵ���·���ʹ���                      */
    L2IF_ERR_VLAN_PVIDNOTEXIST,       /* 41 �˿�δ����PVID                          */
    L2IF_ERR_VP_ISPVID,               /* 42 VLAN ID��PVID������ʧ��                 */
    L2IF_ERR_VP_ISSUPER,              /* 43 sup** vlan������˿��Ƴ�����            */
    L2IF_ERR_VP_ISNOTINMAP,           /* 44 �˿�δ����ͨ��ʽ����ָ��VLAN            */
    L2IF_ERR_VP_ADD_WITH_TAGGED,      /* 45 �˿��Ѿ���tagged��ʽ�����VLAN�������޶����ĸ�VLAN */
    L2IF_ERR_VP_ADD_WITH_UNTAGGED,    /* 46 �˿��Ѿ���untagged��ʽ�����VLAN�������޶����ĸ�VLAN */
    L2IF_ERR_VP_TRUNK_UNTAGGED,       /* 47 Trunk�˿ڲ�����untagged��ʽ����VLAN     */
    L2IF_ERR_VP_VLAN_TAGGED,          /* 48 �˿��Ѿ���tagged��ʽ�������VLAN�����������ö˿ڸ�VLAN������������ϵ */
    L2IF_ERR_VP_VLAN_UNTAGGED,        /* 49 �˿��Ѿ���untagged��ʽ�������VLAN�����������ö˿ڸ�VLAN������������ϵ */
    
    L2IF_ERR_VLANTRANS_HAS_CFG,       /* 50 �˿��Ѿ���VLAN������VLAN Trans����      */
    L2IF_ERR_TRANS_PORTISADDCEVLAN,   /* 51 ���ж˿ڼ��뵽CEVLAN                    */
    L2IF_ERR_TRANS_PORTTYPENOTTRUNK,  /* 52 ����TRANS���ܵĶ˿ڲ���TRUNK            */
    L2IF_ERR_TRANSNODE_NOTEXSIT,      /* 53 û��TRANS���ý��                       */
    L2IF_ERR_VLAN_HAVMAP,             /* 54 ����CeVlan������Mapping����             */
    L2IF_ERR_VLAN_HAVSTACK,           /* 55 ����CeVlan������Stacking����            */
    L2IF_ERR_TRANS_HAVOTHERPE,        /* 56 �����CeVlan��Χ������������PeVlan��    */
    L2IF_ERR_FDB_PORTNOINVLAN,        /* 57 �˿�δ���κη�ʽ����ָ��VLAN            */
    L2IF_ERR_FDB_MACMULTICAST,        /* 58 �㲥��ಥ��ַ                          */
    L2IF_ERR_FDB_NULLPOINT,           /* 59 FDB�������ָ��Ϊ��                     */
    
    L2IF_ERR_FDB_MACLOCAL,            /* 60 ��physical��ַ                               */
    L2IF_ERR_FDB_ANOTHER_PORT,        /* 61 �˿����Ѵ��ڱ��һ��                  */
    L2IF_ERR_MAC_PPICMD,              /* 62 MAC�·������ִ���                       */
    L2IF_ERR_FDB_MACNULL,             /* 63 physical��ַΪ��                             */
    L2IF_ERR_FDB_ANOTHER_TYPE,        /* 64 ��ӱ���������ԭ�������Ͳ�һ��          */
    L2IF_ERR_FDB_NOFREEITEM,          /* 65 ����FDB������Դʧ��                     */
    L2IF_ERR_FDB_NOEXIST,              /* 66 FDB�������                           */
    L2IF_ERR_FDB_ANOTHER_CEVLAN,      /* 67 ��ӱ���CEVlan��ԭ���һ��            */
    L2IF_ERR_VLAN_ADDSELF,            /* 68 Vlan����Ϊ�Լ�����Vlan                  */  
    L2IF_ERR_FDB_AGINGTIME_INVALID,   /* 69 ��̬FDB�ϻ�ʱ�䷶Χ��Ч                 */
    
    L2IF_ERR_TRANS_NO_EXIST,          /* 70 ��ɾ����trans������                     */
    L2IF_ERR_FDB_INVALID_TYPE,        /* 71 �������ͷǷ�                            */
    L2IF_ERR_FDB_OPEN_WAIT_LIST,      /* 72 FDBģ���waitlistʧ��                 */
    L2IF_ERR_FDB_CLOSE_WAIT_LIST,     /* 73 FDBģ��ر�waitlistʧ��                 */
    L2IF_ERR_FDB_WRONGNUM,            /* 74 Ҫ��ȡ�ı�����Ŀ����                    */
    L2IF_ERR_FDB_GET_WAIT_LIST,       /* 75 FDBģ���ȡwaitlistʧ��                 */
    L2IF_ERR_FDB_WAIT_LIST_NOMORE,    /* 76 wait list�Ѿ�û��Ԫ����                 */
    L2IF_ERR_FDB_TRANS_ISNOTEXIST,    /* 77 �˿�δ��Mapping�ķ�ʽ����VLAN           */
    L2IF_ERR_TRANS_VLANADDPORT,       /* 78 VLAN����TRANS֮ǰ�Ѽ��뵽PORT           */
    L2IF_ERR_TRANS_NODEFAULTVLAN,     /* 79 �˿�δ����Stacking��Ĭ��VLAN            */
    
    L2IF_ERR_PORTHASCEDEFVLAN,        /* 80 �˿��Ѿ�������Ce default vlan           */
    L2IF_ERR_PORTHASPVID,             /* 81 �˿��Ѿ�������default vlan              */
    L2IF_ERR_IF_GETIFFAIL,            /* 82 ȡ��VLANIFʧ��                          */
    L2IF_ERR_IF_NOTL3VLANIF,          /* 83 �ӿڲ����ϲ�VLANIF                      */
    L2IF_ERR_MBUFNULL,                /* 84 MBUFΪ��                                */
    L2IF_ERR_PREPENDMBUFFAIL,         /* 85 MBUF Prepend����ʧ��                    */
    L2IF_ERR_CONTINUEMBUFFAIL,        /* 86 MBUF Continue����ʧ��                   */
    L2IF_ERR_RAWCOPYMBUFFAIL,         /* 87 MBUF Raw copy����ʧ��                   */
    L2IF_ERR_VLAN_PHYSTATUS_DOWN,     /* 88 VLAN������״̬DOWN                      */
    L2IF_ERR_TRANS_REGWAITLIST,       /* 89 ע��WaitList���ʧ��                    */
    
    L2IF_ERR_TRANS_SETWAITLIST,       /* 90 ����WaitListͷ�ڵ�ʧ��                  */
    L2IF_ERR_TRANS_GETWAITLIST,       /* 91 ��ȡWaitListͷ�ڵ�ʧ��                  */
    L2IF_ERR_TRANS_UNREGWAITLIST,     /* 92 ��ע��WaitList���ʧ��                  */
    L2IF_ERR_GETLOCALMAC_NOREGISTER,  /* 93 ��ȡ��MAC����Ϊע��                     */

    L2IF_ERR_GETIFINDEX_BYIFNAME,     /* 94 ͨ���ӿ����ֻ�ȡ�ӿ�����ʧ��            */
    L2IF_ERR_IFNET_IS_NULL,           /* 95 IFNET�ӿ�ָ��ΪNULL                     */
    L2IF_ERR_DELETE_IF_FAIL,          /* 96 ɾ���ӿ�ʧ��                            */
    L2IF_ERR_CRT_PORT_FAIL,           /* 97 ����L2 trunk��Ա�˿ڷ���ʧ��            */
    L2IF_ERR_IFTYPE_IS_WRONG,         /* 98 �ӿ����ʹ���                            */
    L2IF_ERR_VP_ACCESS_TAGGED,        /* 99 ACCESS�˿ڲ�����tagged��ʽ����VLAN     */    
    L2IF_ERR_DYNAMIC_FDB_GET,         /* 100 ��ȡ�Ķ�̬FDB�����е�VLANID��MAC���ѯ�Ĳ�һ�� */
    
    L2IF_ERR_MAXCODE                  /* �������� */
}L2IF_ERRCODE_E;

/*******************************************************************************
 * �궨��:                                                                     *
 *******************************************************************************/
/* һ��S***R VLAN�������VLAN��Ŀ */
#define L2IF_MAX_SUB_VLAN       1024

/* ��ʾ����Ϊ���Ʊ��������ֵ */
#define L2IF_LIMIT_RATIO        0  /* ��ʾ����Ա��������������Ʊ�   */
#define L2IF_LIMIT_VALUE        1  /* ��ʾ����������ֵ�����������Ʊ� */

/* ϵͳ��֧�ֵ����VLAN��Ŀ */
#define L2IF_MAX_VLAN_NUM       4096

/* ��λͼ��ʽ��ʾVLAN IDʱ��λͼ����(ULONGΪ��λ) */
#define VLAN_BITMAP_LEN         (L2IF_MAX_VLAN_NUM/(sizeof(ULONG) * 8))

/* Modified by luogaowei, for DTS2013080906587 ,L2IF�ӿ�����Ϊ256, 2013/8/12 */
/* ϵͳ֧�ֵ����˿ڸ��� */
#define L2IF_MAX_PORT_NUM       256

#ifndef MACADDRLEN
#define MACADDRLEN 6   /* physical��ַ���� */
#endif

/*******************************************************************************
 * ö�ٶ���:                                                                   *
 *******************************************************************************/
/* L2IFģ�������ö��� */
typedef enum tagL2IfSetFlag
{
    L2IF_FLAG_SET_NO = 0,           /* 0 �����ñ�� */
    L2IF_FLAG_SET_YES               /* 1 ���ñ�� */
}L2IFSETFLAG_E;

/* �˿���tagged/untagged��ʽ����VLAN */
typedef enum tagL2If_VlanTag
{
    VLAN_UNTAGGED = 0,  /* VLAN��untagged��ʽ����VLAN */
    VLAN_TAGGED   = 1,  /* VLAN��tagged��ʽ����VLAN */
}L2IF_VLANTAG_E;

/* �˿����� */
enum enPortType
{
    PORT_TYPE_INVALID = 0,  
    PORT_TYPE_ACCESS  = 1,          /* ����˿� */
    PORT_TYPE_TRUNK   = 2,          /* �ɵ��˿� */
    PORT_TYPE_HYBRID  = 3,          /* Hybrid �˿� */
    PORT_TYPE_QINQ    = 4,          /* QinQ �˿� */
};

/* ���Ĵ���ʽ */
typedef enum tagL2IF_Unknow_Frame_Mode
{
    L2IF_UNKNOW_FRAME_DROP = 0,                /* ����ģʽ */
    L2IF_UNKNOW_FRAME_2CPU,                    /* ��CPUģʽ */
    L2IF_UNKNOW_FRAME_BC                       /* �㲥ģʽ */
}L2IF_UNKNOW_FRAME_MODE_E;

/* physical��ַѧϰʹ��/��ֹ */
typedef enum tagL2If_MacLearn
{
    L2IF_MAC_LEARNING_DISABLE = 0,   /* physical��ַѧϰ��ֹ */
    L2IF_MAC_LEARNING_ENABLE  = 1    /* physical��ַѧϰʹ�� */
}L2IF_MACLEARN_E;

/* �������ƹ���ʹ��/��ֹ */
typedef enum tagL2If_FlowLimit
{
    L2IF_FLOW_LIMIT_DISABLE = 0,   /* �������ƹ��ܽ�ֹ */
    L2IF_FLOW_LIMIT_ENABLE  = 1    /* �������ƹ���ʹ�� */
}L2IF_MACLIMIT_E;

/* �㲥�������� */
typedef enum tagL2IF_PORT_BROADCAST
{
    L2IF_INBROADCAST_LIMIT,         /* ���й㲥�������� */
    L2IF_INMULCAST_LIMIT,           /* ���жಥ�������� */
    L2IF_INUNMULCAST_LIMIT,         /* ����δ֪������������ */
    L2IF_OUTBROADCAST_LIMIT,        /* ���й㲥�������� */
    L2IF_OUTMULCAST_LIMIT,          /* ���жಥ�������� */
    L2IF_OUTUNMULCAST_LIMIT,        /* ����δ֪������������ */
    L2IF_BROADCAST_MAX,
}L2IF_PORT_BROADCAST_E;

/* TRANSģʽ */
typedef enum tagL2TRANS_MODE
{
    L2TRANS_CEDEFAULT    = 0,       /* Ce Default Vlan stacking*/
    L2TRANS_STACKING     = 1,       /* Stacking*/
    L2TRANS_MAPPING      = 2,       /* Mapping*/
    L2TRANS_STACKINGMAPPING = 3,    /* stack��ʽ���ڴ�vlan�ٴ�mapping,Ŀǰ�������ݲ�֧��*/
    L2TRANS_INVALIDMODE
}L2TRANS_MODE_E;

/*******************************************************************************
 * ���ݽṹ����:                                                               *
 *******************************************************************************/
 /* VLAN��Ϣ���ݽṹ */
typedef struct tagTCPIP_L2IF_VLAN_INFO
{
    UCHAR  ucVlanType;             /* VLAN����,ȱʡֵVLAN_TYPE_INVALID */
    UCHAR  ucShutdown;             /* VLAN�Ĺ���״̬��SHUT OR NOSHUT */
    UCHAR  ucStatus;               /* VLAN������״̬��UP/DOWN��ȱʡֵVLAN_STATUS_DOWN */
    UCHAR  ucMacLearning;          /* physical��ַѧϰ,ȱʡֵMAC_LEARNING_ENABLE */
    UCHAR  ucBroadcast;            /* VLAN�ڹ㲥���ĵĴ���ʽ */
    UCHAR  ucUnkownMulti;          /* VLAN��δ֪�ಥ���ĵĴ���ʽ���������� */
    UCHAR  ucUnkownUniFrame;       /* VLAN��δ֪�������ĵĴ���ʽ */
    UCHAR  ucReserved[1];
    USHORT usSuperVlan;            /* ��Ӧ��s***r-VLAN��VLAN ID,��ʼֵVLANID_INVALID*/
    USHORT usSubCount;             /* ����S***r VLAN���ԣ�������Sub VLAN�ĸ��� */    
    USHORT usSubVlanID[L2IF_MAX_SUB_VLAN]; /* S***r Vlan ������Sub Vlan ID�б� */
    ULONG  ulIfnetIndex;           /* VLAN�ӿڶ�Ӧ��ifindex,ȱʡֵINVALID_IFINDEX(Len: 108) */
}TCPIP_L2IF_VLAN_INFO_S;

/* PORT��Ϣ���ݽṹ */
typedef struct tagTCPIP_L2IF_PORT_INFO
{
    UCHAR  ucIfType;                 /* �˿���·���� */
    UCHAR  ucMacLearning;            /* �˿ڵ�physical��ַѧϰʹ�ܱ�־ */
    UCHAR  ucPriority;               /* �˿����ȼ� 0-7 */
    UCHAR  ucReserved[1];
    USHORT usPVID;                   /* �˿�ȱʡVID */
    USHORT usCEDefaultVlan;          /* ���ڶ˿ڵ�QinQ */
    ULONG  ulIfIndex;                /* �˿�IFNET���� */
    
    UCHAR  ucInBroadSuppressRatio;     /* �˿ڹ㲥���Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucInMultiSuppressRatio;     /* �˿�δ֪�ಥ���Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucInUnicastSuppressRatio;   /* �˿�δ֪�������Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucOutBroadSuppressRatio;  /* �˿����й㲥���Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucOutMultiSuppressRatio;  /* �˿�����δ֪�ಥ���Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucOutUnicastSuppressRatio;/* �˿�����δ֪�������Ƶı���,ȱʡֵ100,�������� */
    UCHAR  ucResv[2];
    ULONG  ulInBroadSuppress;        /* �˿����� �㲥���Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
    ULONG  ulInMultiSuppress;        /* �˿�����δ֪�ಥ���Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
    ULONG  ulInUnicastSuppress;      /* �˿�����δ֪�������Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
    ULONG  ulOutBroadSuppress;       /* �˿����й㲥���Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
    ULONG  ulOutMultiSuppress;       /* �˿�����δ֪�ಥ���Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
    ULONG  ulOutUnicastSuppress;     /* �˿�����δ֪�������Ƶ�ֵ,ȱʡֵ�˿ڴ���,�������� */
}TCPIP_L2IF_PORT_INFO_S;

/* FDB������Ϣ���ݽṹ */
typedef struct tagTCPIP_FDB_ENTRY_S
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical��ַ */        
    USHORT usVlanId;                     /* physical��ַ����VLAN ID */
    ULONG  ulIfIndex;                    /* �ӿ����� */
    UCHAR  ucType;                       /* physical��ַ�������� */
    UCHAR  ucFdbFlag;                    /* VLAN/QINQ ��־,���ھ�̬�ͺڶ���������Ч,��̬FDB����ʱ��Ч */
    USHORT usOutCeVlanId;                /* �û���VLAN ID,���ھ�̬�ͺڶ���������Ч,��̬FDB����ʱ��Ч */
    /* Add by zhaoyue00171897, at 2011-08-17. �޸�ԭ��: ֧�ֻ�ȡ��̬FDB����,���������ϻ�ʱ�� */
    ULONG  ulAgingTime;                  /* �ϻ�ʱ��,���ڶ�̬FDB����ʱ��Ч,��̬�ͺڶ������²��ع�ע */
}TCPIP_FDB_ENTRY_S;

/* TRANS������Ϣ���ݽṹ */
typedef struct tagTCPIP_L2TRANS_CONFIGINFO
{
    ULONG  ulPortIndex;             /*����˿ڵĽӿ�����*/
    ULONG  ulTransMode;             /*��ʾ��Stacking����Mappingģʽ���μ�L2TRANS_MODE_E*/
    USHORT usPeVlan;                /*PeVlan ID*/
    USHORT usOutVlanBegin;          /*CeVlan ��ʼID*/
    USHORT usOutVlanEnd;            /*CeVlan ��ֹID*/
    UCHAR  ucReserve[2];
}TCPIP_L2TRANS_CONFIGINFO_S;

/*******************************************************************************
 * ע�����亯��ԭ��:                                                           *
 *******************************************************************************/

/* ��ȡ��mac��ע�ắ��ԭ�� */
typedef ULONG  (*GETLOCALMAC_HOOK_FUNC)(UCHAR* pucMacAddr);

/* �˿ڱ��ķ��ͺ���ԭ�� */
typedef ULONG  (*PORT_PHYTRANSMIT_HOOK_FUNC)(ULONG ulPhyCtlBlk, MBUF_S *pstMbuf);

/* �˿�������·����ƺ���ԭ�� */
typedef ULONG  (*PORT_PHYIOCTL_HOOK_FUNC)(ULONG ulPhyCtlBlk, ULONG ulCmd, CHAR *pData);

/* ͨ��PORT�ӿ�����ȡ�ײ���Ϣ����ԭ�� */
typedef ULONG  (*PORT_GETPHYLINK_HOOK_FUNC)(CHAR *szName, ULONG *pulPhyLink);

/* ��VISP������ת��VLAN����ʱ��ͨ����ע�ṳ�ӻ�ȡ�����ȼ��ֶ� */
typedef ULONG  (*L2IF_TOS_TO_VLAN_PRIORITY)(MBUF_S *pMbuf, ULONG *pPriority);

/*******************************************************************************
 * APIԭ��:                                                                    *
 *******************************************************************************/

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLocalMacHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: ��Ʒע���ȡ��mac�����亯��
*        Input: GETLOCALMAC_HOOK_FUNC pfFunc: ��ȡ��mac���亯��ԭ��
*       Output: 
*       Return: VOS_OK:     ע��ɹ�
*               VOS_ERR:    ע��ʧ��
*      Caution: Э��ջ����ǰע��,���ɽ�ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetLocalMacHook(GETLOCALMAC_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPortPhyTransmitHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: ��Ʒע�ύ�����˿ڵĵײ㱨�ķ������亯�� 
*        Input: PORT_PHYTRANSMIT_HOOK_FUNC pfFunc: ��ע�ắ��
*       Output: 
*       Return: VOS_OK:     ע��ɹ�
*               VOS_ERR:    ע��ʧ��
*      Caution: Э��ջ����ǰע��,���ɽ�ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPortPhyTransmitHook(PORT_PHYTRANSMIT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPortPhyIoCtlHook
* Date Created: 2008-10-18
*       Author: LY(57500)
*  Description: ��Ʒע�ύ�����˿ڵ������������亯��
*        Input: PORT_PHYIOCTL_HOOK_FUNC pfFunc: ��ע�ắ��
*       Output: 
*       Return: VOS_OK:     ע��ɹ�
*               VOS_ERR:    ע��ʧ��
*      Caution: Э��ջ����ǰע��,���ɽ�ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPortPhyIoCtlHook(PORT_PHYIOCTL_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPortPhyLinkHook
* Date Created: 2008-10-25
*       Author: LY(57500)
*  Description: ���ݽӿ�����ȡ�ײ���Ϣע�ắ��
*        Input: PORT_GETPHYLINK_HOOK_FUNC pfFunc: ��ע��ָ��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPortPhyLinkHook(PORT_GETPHYLINK_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_AddSubVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ���Sub VLAN��S***r VLAN
*        Input: USHORT usSuperVlanId: S***r VLAN��VLAN ID
*               USHORT usSubVlanId: Sub VLAN��VLAN ID
*       Output: 
*       Return: 
*      Caution: ֱ�ӽ�COMMON VLAN��ӵ�S***r VLAN�У�COMMON VLANֱ���Զ�ת��ΪSub VLAN
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_AddSubVlan(USHORT usSuperVlanId, USHORT usSubVlanId);

/*******************************************************************************
*    Func Name: TCPIP_CreateVlan
* Date Created: 2008-10-20
*       Author: z00104207
*  Description: ����VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-20   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_CreateVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_RemoveSubVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��Sub VLAN��S***r VLAN���Ƴ�
*        Input: USHORT usSuperVlanId: S***r VLAN��VLAN ID
*               USHORT usSubVlanId: Sub VLAN��VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RemoveSubVlan(USHORT usSuperVlanId, USHORT usSubVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DeleteVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ɾ��VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_DeleteVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DeleteBatchVlan
* Date Created: 2008-11-11
*       Author: Zheng Sen Huo (00104483)
*  Description: ɾ��ָ����Χ��VLAN��
*        Input: USHORT usBeginVlan:��ʼVLANID
*               USHORT usEndVlan:����VLANID
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-11   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DeleteBatchVlan(USHORT usBeginVlan, USHORT usEndVlan);

/*******************************************************************************
*    Func Name: TCPIP_GetPortInfoByIfIndex
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��������ڽӿ�������ȡ����˿�������Ϣ
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               TCPIP_L2IF_PORT_INFO_S *pulPortInfo: �˿�������Ϣ���������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPortInfoByIfIndex(ULONG ulIfIndex, TCPIP_L2IF_PORT_INFO_S *pstPortInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetUsedPort
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��ȡ��ǰ���õĶ˿���Ŀ�Ͷ�Ӧ�Ľӿ������б�
*        Input: ULONG *pulPortNum: ��ǰ���õĶ˿���Ŀ
*               ULONG  ulIfIndexList[L2IF_MAX_PORT_NUM]: ���õĶ���˿ڶ�Ӧ�Ľӿ������б�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUsedPort(ULONG *pulPortNum, ULONG ulIfIndexList[L2IF_MAX_PORT_NUM]);

/*******************************************************************************
*    Func Name: TCPIP_GetUsedVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��ȡ��ǰ���õ�VLAN��Ŀ��VLAN ID�б�
*        Input: 
*       Output: ULONG *pulVlanNum: ��ǰ���õ�VLAN��
*               ULONG ulVlanIDBitMap[VLAN_BITMAP_LEN]: vlan id λͼ
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUsedVlan(ULONG *pulVlanNum, ULONG ulVlanIDBitMap[VLAN_BITMAP_LEN]);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanInfo
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ����VLAN ID��ȡVLAN����Ϣ
*        Input: USHORT usVlanId: VLAN ID
*       Output: TCPIP_L2IF_VLAN_INFO_S *pstVlanInfo: VLAN��Ϣ���������
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVlanInfo(USHORT usVlanId, TCPIP_L2IF_VLAN_INFO_S *pstVlanInfo);

/*******************************************************************************
*    Func Name: TCPIP_SetPortMacLearn
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ʹ��/ȥʹ�ܶ���˿�physical��ַѧϰ����
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               ULONG ulFlag: ʹ��/ȥʹ�ܱ��, L2IF_FLAG_SET_NO / L2IF_FLAG_SET_YES
*       Output: 
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortMacLearn(ULONG ulIfIndex, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetPortPriority
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ���ö���˿����ȼ�
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               UCHAR ucPriority: ���ȼ���Χ��0~7
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortPriority(ULONG ulIfIndex, UCHAR ucPriority);

/*******************************************************************************
*    Func Name: TCPIP_SetPortSuppressRatio
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ���ö���˿��������Ʊ���,ucSuppressRatio ֵΪ100��ʾ���������ƹ���
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               ULONG ulLimitType: ��Ҫ���Ƶı������ͣ���������/���е������ġ�
*               ����/���жಥ���ġ�����/���й㲥����
*               UCHAR ucSuppressRatio: �������ʵİٷ���
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortSuppressRatio(ULONG ulIfIndex, ULONG ulLimitType, UCHAR ucSuppressRatio);


/*******************************************************************************
*    Func Name: TCPIP_SetPortSuppressValue
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: �������ƶ���˿����ʵľ���ֵ,ֵΪ0��ȫf��ʾ����������
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               ULONG ulLimitType: ��Ҫ���Ƶı������ͣ���������/���е������ġ�
*               ����/���жಥ���ġ�����/���й㲥����
*               ULONG ulSuppressValue: �������ʵľ���ֵ
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortSuppressValue(ULONG ulIfIndex, ULONG ulLimitType, ULONG ulSuppressValue);

/*******************************************************************************
*    Func Name: TCPIP_SetPortType
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ���ö���˿ڵ���·����
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               UCHAR ucPortType: Ҫ���óɵĶ˿����ͣ�����PORT_TYPE_ACCESS,
*               PORT_TYPE_TRUNK, PORT_TYPE_HYBRID��PORT_TYPE_QINQ��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortType(ULONG ulIfIndex, UCHAR ucPortType);

/*******************************************************************************
*    Func Name: TCPIP_SetStackingDefaultVlan
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ���ö˿ڵ�Ĭ��Stacking VLAN
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*               USHORT usVlanID: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetStackingDefaultVlan(ULONG ulIfIndex, USHORT usVlanID);

/*******************************************************************************
*    Func Name: TCPIP_UndoStackingDefaultVlan
* Date Created: 2008-11-20
*       Author: Zheng Sen Huo (00104483)
*  Description: ȡ������˿ڵ�StackingDefaultVlan
*        Input: ULONG ulIfIndex:����˿�����
*       Output: 
*       Return: �ɹ�����L2IF_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_UndoStackingDefaultVlan(ULONG ulIfIndex);


/*******************************************************************************
*    Func Name: TCPIP_SetSuperVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ����VLANΪSu*** VLAN��Su*** VLAN�ָ�ΪCommond VLAN
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: L2IF_FLAG_SET_NO / L2IF_FLAG_SET_YES
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSuperVlan(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanBroadCast
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ����VLAN�ڹ㲥���ĵĴ���ʽ
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucFlag: L2IF_UNKNOW_FRAME_DROP / L2IF_UNKNOW_FRAME_2CPU
*                             / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanBroadCast(USHORT usVlanID, UCHAR ucFlag);


/*******************************************************************************
*    Func Name: TCPIP_SetVlanUnknowMulti
* Date Created: 2008-11-10
*       Author: wuhailan
*  Description: ����VLAN��δ֪�ಥ���ĵĴ���ʽ
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucFlag: L2IF_UNKNOW_FRAME_DROP / L2IF_UNKNOW_FRAME_2CPU
*                             / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: L2IF_OK: �ɹ�
*               ������:  ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   wuhailan                Create
*
*******************************************************************************/
ULONG TCPIP_SetVlanUnknowMulti(USHORT usVlanID, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanMacLearn
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ����ָ��VLAN��physical��ַѧϰ�Ƿ�ʹ��
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: MAC_LEARNING_DISABLE / MAC_LEARNING_ENABLE
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanMacLearn(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanUnknowUnicast
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ����VLAN��δ֪�������ĵĴ���ʽ��Ĭ�ϵĴ���ʽ�ǹ㲥��ʽ��δ֪
*               ����������ָ�����ݱ��ĵ��ϵ�MAC��VLAN TAG�޷��ҵ�ƥ��Ķ���ת��
*               ����ĵ�������
*        Input: USHORT usVlanId: VLAN ID
*               UCHAR ucFlag: δ֪�������ĵĴ���ʽ������: L2IF_UNKNOW_FRAME_DROP
*               / L2IF_UNKNOW_FRAME_2CPU / L2IF_UNKNOW_FRAME_BC
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetVlanUnknowUnicast(USHORT usVlanId, UCHAR ucFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllVlanInfo
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ��ʾ����VLAN����Ϣ
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVlanInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowPortInfoByIfName
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��������ڽӿ���ʾ����˿�������Ϣ
*        Input: ULONG ulIfIndex: �˿ڶ�Ӧ�Ľӿ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPortInfoByIfName(UCHAR *pucIfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlan
* Date Created: 2008-10-24
*       Author: z00104207
*  Description: ����VLAN ID��ʾVLAN����ϸ������Ϣ
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-24   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_ShutdownVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: Shut downָ����VLAN
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_ShutdownVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_UpVlan
* Date Created: 2008-10-23
*       Author: z00104207
*  Description: ��shout down��VLAN��UP
*        Input: USHORT usVlanId: VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_UpVlan(USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_AddPortToVlan
* Date Created: 2008-10-31
*       Author: z00104207
*  Description: ��Hybrid���ͻ�Trunk���͵Ķ���˿���ӵ�VLAN
*        Input: ULONG ulIfIndex: ����˿ڶ�Ӧ�Ľӿ�����
*               USHORT usVlanId: Ŀ��VLAN ID
*               ULONG ulTagFlag: �˿ڼ���VLAN�ķ�ʽ: VLAN_UNTAGGED/VLAN_TAGGED
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-31   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_AddPortToVlan(ULONG ulIfIndex, USHORT usVlanId, ULONG ulTagFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetDefaultVlan
* Date Created: 2008-11-04
*       Author: z00104207
*  Description: ���ö���˿ڵ�Ĭ��VLAN
*        Input: ULONG ulIfIndex: ����˿ڶ�Ӧ�Ľӿ�����
*               USHORT usVlanId: Ŀ��VLAN ID
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDefaultVlan(ULONG ulIfIndex, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_UndoDefaultVlan
* Date Created: 2008-11-06
*       Author: z00104207
*  Description: ȡ���˿ڵ�PVID
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-06   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_UndoDefaultVlan(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_CreatePortIf
* Date Created: 2008-10-25
*       Author: LY(57500)
*  Description: ��̬����PORT�ӿ�
*        Input: CHAR *szPortIfName: �ӿ�����������ʽΪ��ethernetXYZ��
*                                    XYZ��X�ĺ����ǰ�ţ�YZ�ĺ����Ǹð�Ķ˿ںš�
*                                    ����ֵ���û��������ͽ��͡��ⲿ����
*               ULONG ulL2Flag: ��ʶ�Ǵ�����ͨport�ӿ�(L2IF_PORT)����L2-TRUNK��Ա�˿�(L2IF_TRUNKPORT)
*       Output: ULONG *pulIfIndex: ���PORT�ӿ�ָ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CreatePortIf(CHAR *szPortIfName, ULONG ulL2Flag, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_L2PortSwitch
* Date Created: 2010-01-04
*       Author: z62531
*  Description: ʵ��L2��ͨ�˿���L2Trunk��Ա�˿ڵĻ���ת��
*        Input: CHAR *szPortIfName: �ӿ�����������ʽΪ��ethernetXYZ��
*                                    XYZ��X�ĺ����ǰ�ţ�YZ�ĺ����Ǹð�Ķ˿ںš�
*                                    ����ֵ���û��������ͽ��͡��ⲿ����
*       Output: ULONG *pulIfIndex: ���PORT�ӿ�ָ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-01-04   z62531     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_L2PortSwitch(CHAR *szPortIfName, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DelPortFromVlan
* Date Created: 2008-11-04
*       Author: wuhailan
*  Description: ������˿ڴ�ָ��vlan��ɾ��
*        Input: ULONG ulIfIndex:����ӿ�����
*               USHORT usVlanId:vlan id
*       Output: ��
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPortFromVlan(ULONG ulIfIndex, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_DelPortFromAllVlan
* Date Created: 2008-11-04
*       Author: wuhailan 
*  Description: �˳�����VLAN����Ĭ��VLAN��
*        Input: ULONG ulIfIndex:�˿�����
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPortFromAllVlan(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetPortListInVlan
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: ��ȡ����VLAN�Ķ˿���Ŀ�Ͷ˿�IFIndex�б�
*        Input: USHORT usVlanId:       VLAN id
*               ULONG *pulPortNum:     �˿���Ŀ
*               ULONG ulIfList[L2IF_MAX_PORT_NUM]:  �˿����� 
*       Output: ULONG *pulPortNum:     ����VLAN�Ķ˿���Ŀ
*               ULONG ulIfList[L2IF_MAX_PORT_NUM]:  ����VLAN�Ķ˿�IFIndex�б� 
*       Return: �ɹ�����L2IF_OK������������
*      Caution: �����Ifnet List�����С���������û���֤
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPortListInVlan(USHORT usVlanId, ULONG *pulPortNum, ULONG ulIfList[L2IF_MAX_PORT_NUM]);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanListInPort
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: ��ȡ�˿ڼ����VLAN��Ŀ��VLAN�б�
*        Input: ULONG ulIfIndex:         �ӿ�����
*       Output: ULONG *pulVlanNum:       �˿ڼ����VLAN��Ŀ
*               ULONG ulVlanList[VLAN_BITMAP_LEN]:   �˿ڼ����VLANλͼ����
*               ULONG ulTagList[VLAN_BITMAP_LEN]:    �˿ڼ����VLAN��Tag���λͼ����
*       Return: �ɹ�����L2IF_OK������������
*      Caution: �����VLAN List�����С���������û���֤
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*  2011-08-04   s00176784               Modify
*******************************************************************************/
ULONG TCPIP_GetVlanListInPort(ULONG ulIfIndex, ULONG *pulVlanNum, 
                              ULONG ulVlanList[VLAN_BITMAP_LEN], ULONG ulTagList[VLAN_BITMAP_LEN]);


/*******************************************************************************
*    Func Name: TCPIP_ShowPortListInVlan
* Date Created: 2008-11-04
*       Author: h00121208
*  Description: ��ʾ����VLAN�Ľӿ�����
*        Input: USHORT usVlanID: VLAN id
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-04   h00121208               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPortListInVlan(USHORT usVlanID);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanListInPort
* Date Created: 2008-11-05
*       Author: wuhailan
*  Description: ��ʾ�ӿ����ڵ�vlan list��Ϣ
*        Input: CHAR *pIfName:�ӿ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-05   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVlanListInPort(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanMapping
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿���������Vlan Mapping����
*        Input: ULONG ulIfIndex:      �˿�����
*               USHORT usOutVlanBegin:Mappingǰ����ʼVLANID 1~4094
*               USHORT usOutVlanEnd:  Mappingǰ����ֹVLANID 1~4094
*               USHORT usMappingVlan: Mapping���VLANID 1~4094
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanMapping(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usMappingVlan);

/*******************************************************************************
*    Func Name: TCPIP_DelVlanMapping
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿�����ɾ��Vlan Mapping����
*        Input: ULONG ulIfIndex:      �˿�����
*               USHORT usOutVlanBegin:Mappingǰ����ʼVLANID 1~4094
*               USHORT usOutVlanEnd:  Mappingǰ����ֹVLANID 1~4094
*               USHORT usMappingVlan: Mapping���VLANID 1~4094
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelVlanMapping(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usMappingVlan);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanStacking
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿���������Stacking����
*        Input: ULONG ulIfIndex:      �˿�����
*               USHORT usOutVlanBegin:Stacking�ڲ�Vlan����ʼVLANID 1~4094
*               USHORT usOutVlanEnd:  Stacking�ڲ�Vlan����ֹVLANID 1~4094
*               USHORT usStackingVlan:Stacking�����VLANID 1~4094
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanStacking(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usStackingVlan);

/*******************************************************************************
*    Func Name: TCPIP_DelVlanStacking
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿�����ɾ��Stacking����
*        Input: ULONG ulIfIndex:      �˿�����
*               USHORT usOutVlanBegin:Stacking�ڲ�Vlan����ʼVLANID 1~4094
*               USHORT usOutVlanEnd:  Stacking�ڲ�Vlan����ֹVLANID 1~4094
*               USHORT usStackingVlan:Stacking�����VLANID 1~4094
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelVlanStacking(ULONG ulIfIndex, USHORT usOutVlanBegin, USHORT usOutVlanEnd,USHORT usStackingVlan);

/*******************************************************************************
*    Func Name: TCPIP_SetPortQinqProtocol
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿���������QinQ�����Э���
*        Input: ULONG ulIfIndex:      �˿�����
*               USHORT usQinqProtocol:QinQ�����Э���
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPortQinqProtocol(ULONG ulIfIndex, USHORT usQinqProtocol);

/*******************************************************************************
*    Func Name: TCPIP_GetQinqProtocolByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ˿�������ȡQinQ�����Э���
*        Input: ULONG ulIfIndex:        �˿�����
*               USHORT *pusQinqProtocol:QinQ�����Э���
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetQinqProtocolByPort(ULONG ulIfIndex, USHORT *pusQinqProtocol);

/*******************************************************************************
*    Func Name: TCPIP_OpenVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: ��ȡWaitList���
*        Input: ULONG *pulWaitlist:WaitList���
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVlanQinQTable(UINTPTR *pulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: ����WaitList�����ȡQinQ������Ϣ
*        Input: ULONG ulWaitlist:WaitList���
*               ULONG ulTransNum:��Ҫ��ȡ��������Ϣ����
*       Output: TCPIP_L2TRANS_CONFIGINFO_S *pstTransEntry:Trans������Ϣ
*               ULONG *pulTransNumReturn:ʵ�ʻ�ȡ��������Ϣ����
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVlanQinQTable(UINTPTR ulWaitlist,ULONG ulTransNum, 
                                    TCPIP_L2TRANS_CONFIGINFO_S *pstTransEntry,ULONG *pulTransNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_CloseVlanQinQTable
* Date Created: 2008-11-24
*       Author: Zheng Sen Huo (00104483)
*  Description: �ر�WaitList
*        Input: ULONG ulWaitlist:WaitList���
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-24   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseVlanQinQTable(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_DelAllMappingByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ���˿�����ɾ���˿�������Mapping������Ϣ
*        Input: ULONG ulIfIndex:����˿�����
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelAllMappingByPort(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DelAllStackingByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ���˿�����ɾ���˿�������Stacking������Ϣ
*        Input: ULONG ulIfIndex:����˿�����
*       Output: 
*       Return: �ɹ�:L2IF_OK
*               ʧ��:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_DelAllStackingByPort(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQByPort
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ���ݶ���˿�����ʾ����Trans��Ϣ
*        Input: CHAR *pIfName:����˿���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQByPort(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQByPEVlan
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ����PeVlan��ʾ���Vlan��ص�Trans��Ϣ
*        Input: USHORT usPeVlan:Mapping���VlanID��Stacking�����VlanID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQByPEVlan(USHORT usPeVlan);

/*******************************************************************************
*    Func Name: TCPIP_ShowVlanQinQAll
* Date Created: 2008-10-23
*       Author: Zheng Sen Huo (00104483)
*  Description: ��ʾ���ж˿��µ�Trans��Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowVlanQinQAll(VOID);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddStatic
* Date Created: 2008-11-13
*       Author: zhangchi(00142640)
*  Description: ��Ӿ�̬physical��ַ����
*        Input: UCHAR *aucMacAddr:  MAC����
*               USHORT usVlanId:    VLAN ID
*               ULONG ulIfIndex:    �ӿ�����
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddStatic(UCHAR *aucMacAddr, USHORT usVlanId, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddBlackhole
* Date Created: 2008-11-15
*       Author: zhangchi(00142640)
*  Description: ��Ӻڶ�MAC����
*        Input: UCHAR *aucMacAddr:  MAC����
*               USHORT usVlanId:    VLAN ID
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddBlackhole(UCHAR *aucMacAddr, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddMappingStatic
* Date Created: 2008-11-17
*       Author: zhangchi(00142640)
*  Description: ��ӻ���Mapping�ľ�̬Mac����
*        Input: UCHAR *aucMacAddr: physical��ַ
*               USHORT usVlanId:   VLAN id
*               USHORT usCeVlanId: CEVLAN id
*               ULONG ulIfIndex:   �ӿ�����
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddMappingStatic(UCHAR *aucMacAddr, USHORT usVlanId, USHORT usCeVlanId, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_FDB_AddMappingBlackhole
* Date Created: 2008-11-17
*       Author: zhangchi(00142640)
*  Description: ��ӻ���Mapping�ĺڶ�Mac����
*        Input: UCHAR *aucMacAddr: physical��ַ
*               USHORT usVlanId:   VLAN id
*               USHORT usCeVlanId: CEVLAN id
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����

*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_AddMappingBlackhole(UCHAR *aucMacAddr, USHORT usVlanId, USHORT usCeVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByType
* Date Created: 2008-11-18
*       Author: zhangchi(00142640)
*  Description: ���ݱ�������ɾ��FDB����
*        Input: UCHAR ucType: ��������
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-18   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByType(UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByVlanType
* Date Created: 2008-11-19
*       Author: zhangchi(00142640)
*  Description: ���ݱ������ͺ�VLAN IDɾ��FDB����
*        Input: USHORT usVlanID: VLAN ID
*               UCHAR ucType:    ��������
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-19   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByVlanType(USHORT usVlanID, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByPortType
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: ���ݶ˿ںͱ�������ɾ��MAC����
*        Input: ULONG ulIfIndex: �ӿ�����
*               UCHAR ucType:    ��������
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByPortType(ULONG ulIfIndex, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByPortVlanType
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: ���ݶ˿ڣ�VLAN�ͱ�������ɾ��MAC����
*        Input: ULONG ulIfIndex:�ӿ�����
*               USHORT usVlanId:VLAN ID
*               UCHAR ucType:   ��������
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByPortVlanType(ULONG ulIfIndex, USHORT usVlanId, UCHAR ucType);

/*******************************************************************************
*    Func Name: TCPIP_FDB_DelEntryByMacVlan
* Date Created: 2008-11-20
*       Author: zhangchi(00142640)
*  Description: ����physical��ַ��VLAN IDɾ��MAC����
*        Input: UCHAR *aucMacAddr: physical��ַ
*               USHORT usVlanId:   VLAN ID
*       Output: 
*       Return: �ɹ�����L2IF_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-20   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_DelEntryByMacVlan(UCHAR *aucMacAddr, USHORT usVlanId);

/*******************************************************************************
*    Func Name: TCPIP_FDB_SetAgingTime
* Date Created: 2008-11-14
*       Author: lianglong111779
*  Description: ���ö�̬physical��ַ������ϻ�ʱ��
*        Input: ULONG ulAgingTime:  �ϻ�ʱ��
*       Output: 
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   lianglong111779         Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_SetAgingTime(ULONG ulAgingTime);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetAgingTime
* Date Created: 2008-11-14
*       Author: lianglong111779
*  Description: ��ȡ��̬physical��ַ������ϻ�ʱ��
*        Input: ULONG ulAgingTime:  �ϻ�ʱ��
*       Output: 
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   lianglong111779         Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetAgingTime(ULONG* pulAgingTime);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetEntryByMacPlusVlan
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: ����physical��ַ��VLAN ID����ȡ����
*        Input: UCHAR* aucMacAddr:physical��ַ
*               USHORT usVlanid:VLAN ID
*       Output: TCPIP_FDB_ENTRY_S* pstFdbEntry:���صı���
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetEntryByMacPlusVlan(UCHAR* aucMacAddr, USHORT usVlanid, TCPIP_FDB_ENTRY_S* pstFdbEntry);

/*******************************************************************************
*    Func Name: TCPIP_FDB_OpenWtLstObject
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: ��waitlist
*        Input: 
*       Output: ULONG *pulWaitListHandle:wait list handle
*       Return: �ɹ���ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_OpenWtLstObject(UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_FDB_CloseWtLstObject
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: �ر�waitlist
*        Input: ULONG ulWaitListHandle:wait list handle
*       Output: 
*       Return: �ɹ���ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_CloseWtLstObject(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetWLStaticByIfIndexPlusVlan
* Date Created: 2008-11-17
*       Author: luowentong105073
*  Description: ���ݽӿ�������VLAN ID��ȡ����
*        Input: ULONG ulWaitlist:wait list handle
*               ULONG ulIfIndex:�ӿ�����
*               USHORT usVlanId:VLAN ID
*               ULONG *pulFdbNum:������Ŀ
*       Output: TCPIP_FDB_ENTRY_S** ppstFdbEntry:��������
*               ULONG *pulFdbNum:������Ŀ
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-17   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetWLStaticByIfIndexPlusVlan(UINTPTR ulWaitlist, ULONG ulIfIndex, USHORT usVlanId, 
    TCPIP_FDB_ENTRY_S* pstFdbEntry, ULONG *pulFdbNum);
    

/*******************************************************************************
*    Func Name: TCPIP_FDB_GetWLBlackholeByVlan
* Date Created: 2008-11-22
*       Author: luowentong105073
*  Description: ����VLAN ID��ȡ�ڶ�����
*        Input: ULONG ulWaitListHandle:wait list
*               USHORT usVlanId:VLAN ID
*               ULONG *pulFdbNum:������Ŀ
*       Output: TCPIP_FDB_ENTRY_S* pstFdbEntry:��������
*               ULONG *pulFdbNum:������Ŀ
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-22   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_FDB_GetWLBlackholeByVlan(UINTPTR ulWaitlist, USHORT usVlanId, 
    TCPIP_FDB_ENTRY_S* pstFdbEntry, ULONG *pulFdbNum);
    
/*******************************************************************************
*    Func Name: TCPIP_FDB_ShowStatic
* Date Created: 2008-11-22
*       Author: zhangchi(00142640)
*  Description: ��ʾ���о�̬MAC����
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-22   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_FDB_ShowStatic(VOID);    

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTos2VlanPriorityHook
* Date Created: 2008-11-18
*       Author: wuhailan 
*  Description: ��VISP������ת��VLAN����ʱ��ͨ����ע�ṳ�ӻ�ȡ�����ȼ��ֶ�
*        Input: L2IF_TOS_TO_VLAN_PRIORITY pfHookFunc:��������
*       Output: 
*       Return: �ɹ�����L2IF_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-18   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTos2VlanPriorityHook(L2IF_TOS_TO_VLAN_PRIORITY pfHookFunc);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _L2IF_API_H_      */


