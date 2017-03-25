/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_IPC.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: Ifnet���ͨ��ͷ�ļ�
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2008/01/10      z62474          Modify for A82D22522
 ************************************************************************/

#ifndef _TCPIP_IF_IPC_H_
#define _TCPIP_IF_IPC_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* IF_MSG_ACK��IF_MSG_NAK������ͬʱ��λ */
#define IF_MSG_ACK                              0x8000  /* ��Ϣ���Ϊȷ����Ϣ */
#define IF_MSG_NAK                              0x4000  /* ��Ϣ���Ϊ��ȷ����Ϣ */

#define IF_MSG_BROADCAST                0x2000  /* ��Ϣ���Ϊ�㲥��Ϣ */

#define IF_MSG_REQACK                   0x0080  /* ��Ϣ��Ҫȷ�� */
#define IF_IPC_QUE_MAX_NUM              50
#define IF_IPC_SELF_MESSAGE             0xACD   /* ��IPC֪ͨ��Ϣ��ʶ���ã�������IPC��Ϣ */

#define NO_SLOT_ISINSERTING     0xffff

#define IF_DATA_MAX_SIZE    20        /* IF_CHANGE_IF_STATE_MSG��Ϣ��pData���ݵ���󳤶� */


typedef ULONG   (* SENDFAIL_PF)(VOID*);

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                                                      STRUCT                */                                                                 
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */



/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                                                      ENUM                  */                                                                  
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

#define IF_IPC_RESERVED  0

enum    enumMsgID
{
    IF_CREATE_IF_MSG = 1,
    IF_DELETE_IF_MSG,
    /*���Ӽ���ʽ�Ȳ�κͿ��Ȳ����Ŀ  */
    IF_REMOVE_ADAPTOR_MSG, /*���γ���Ϣ*/ 
    /*end*/
    IF_CHANGE_IF_STATE_MSG,
    IF_SET_IF_INFO_MSG,
    IF_CHECK_MSG,
    IF_DOWNLOAD_INDEX_MSG,
    IF_DEVLINK_MSG,
    IF_VLINK_MSG,
    IF_VLINK6_MSG,
    IF_CLONE_IF_MSG,
    IF_GET_SHOW_INFO,
    IF_QUERY_VT_MSG,
    IF_QUERY_VE_MSG,
    IF_GET_MIBINFO,
    IF_CREATE_PRICHAN_MSG,
    IF_VLINK_SMOOTH_MSG,
    IF_IFNET_SMOOTH_MSG,
    IF_GET_SHOW_CONTROLLER,
    IF_ENCAP_SUB,
    IF_NOTIFY_CFMRECOVEROVER,
    IF_IFNET_VT_MSG,
    IF_IFNET_LOGIC_CHECKFLOW,            /*����ͳһ��ӿڰ巢�Ͷ�ʱ����ͳ����Ϣ*/
    IF_IFNET_LOGIC_CHECKFLOW_RESPONSE, /*���ڽӿڰ�ȫ�ֽӿ������ذ��ϱ�����*/
    IF_IFNET_LOGIC_GETPHYDATA,          /*����ȫ�ֽӿ���ӿڰ�����ȡ������Ϣ*/
    IF_GETIOINTF_LINKSTATE,
    IF_MAX_MSG_TYPE,
    IF_HOT_IF_MSG,
    IF_GET_VA_SHOW_INFO,
};

/* sub msg type */
enum    enumPriChanIFInfoMsg
{
    IF_CHANNEL_TYPE,
    IF_PRI_TYPE
};

/* for IF_CREATE_IF_MSG */
enum    enumSubIFCreateMsg
{
    IF_IOBOARD_CREATE_REQ = 100,
    /*���Ӽ���ʽ�Ȳ�κͿ��Ȳ����Ŀ   pengjimei for DEV_HOTCTL 2002/12/16*/
    IF_IOADAPTOR_CREATEREQ,
    /*end*/
    IF_CREATE_SUCCESS
};
/* end of IF_CREATE_IF_MSG */

/* for IF_DELETE_IF_MSG */
enum    enumSubIFDeleteMsg
{
    IF_DELETE_MAINIF_MSG = 1,
    IF_DELETE_SUBIF_MSG
};
/* end of IF_DELETE_IF_MSG */

/* for IF_CHANGE_IF_STATE_MSG */
enum    enumSubChangeIFStateMsg
{
    IF_CHANGE_MTU = 100,
    IF_CHANGE_BAUD,
    IF_CHANGE_UP,
    IF_CHANGE_DOWN,
    IF_CHANGE_RCVMAC,
    IF_CHANGE_IO_TO_MAIN, /*���������������ڽ�û������Ҫ�����Ϣ֪ͨ�����ذ塣pengjimei for D17048  2002/10/21*/
/* #if ( VRP_MODULE_IPV6 == VRP_YES ) */   
    IF_CHANGE_INTERFACEID,
    IF_CHANGE_DAD,
/* #endif */       
    IF_CHANGE_ISL
};
/* end of IF_CHANGE_IF_STATE_MSG */

/* for IF_SET_IF_INFO_MSG */
enum    enumSubSetIFInfoMsg
{
    IF_ENCAPSULATION_MSG = 1,
    IF_SETMTU_MSG,
    IF_SETBAUD_MSG,
    IF_SHOWIF_MSG,
    IF_SHUT_MSG,
    IF_NOSHUT_MSG,
    IF_SETDESCRIPT_MSG,
    IF_CLEAR_PORT,
    IF_SETKEEPALIVE_MSG,
    IF_SETBANDWIDTH_MSG,
    IF_SETSNMPTRAP_MSG,
    IF_GET_VA_SHOWINFO,
    IF_SETVEMAC_MSG,
    IF_SETPROMODE,
    IF_PROTOCOLLIMIT_MSG,
    IF_SETRCVADDRSTATUS,
    IF_SETISISFLAG_MSG,
    IF_SETVRFINDEX_MSG
};
/* end of IF_SET_IF_INFO_MSG */


/* for IF_CHECK_MSG */
enum    enumSubCheckMsg
{
    IF_SYN_ALL_BY_CHECKSUM = 1,
    IF_SYN_MTU,
    IF_SYN_BAUD,
    IF_SYN_ENCAP,
    IF_SYN_PORTTYPE,
    IF_SYN_INDEX,
    IF_SYN_IFNET_REQ,
    IF_SYN_IFNET
    
};
/* end of IF_CHECK_MSG */

/* for IF_DEVLINK_MSG */

enum    enumDevLinkMsg
{
    IF_SEND_DEVLINK_REQ_MSG = 1,
    IF_SEND_DEVLINK_ACK_MSG,
    IF_SEND_DEVLIK_MSG
};


/* end of IF_DEVLINK_MSG */

/* for IF_DOWNLOAD_INDEX_MSG */

enum    enumDownLoadIndexMsg
{
    IF_DOWNLOAD_INDEX_BEGIN_MSG = 1,
    IF_DOWNLOAD_INDEX_SUCCESS_MSG
    
};

/* end of IF_DOWNINDEX_INDEX_MSG */

/* end of sub msg type */

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                                                      FUNCTIONS             */                                         
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
ULONG IF_BoardUp(ULONG);

ULONG IF_BoardIsUp( ULONG );

ULONG IF_GetNextUpBoardID(ULONG ulSlot);
ULONG IF_GetPreUpBoardID(ULONG ulSlot);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif


