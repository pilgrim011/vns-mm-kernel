/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_pub.h
*
*  Project Code: V1.1.0
*   Module Name: pub
*  Date Created: 2009-8-18
*        Author: z62531
*   Description: pubģ��������Ϳ����湲�õĽṹ,��ȶ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-18    z62531           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_PUB_H_
#define _IPSFE_PUB_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ��ͨ���д�����ʾ������ARP��Ϣ�Ľṹ�� */
typedef struct tagSFE_ARP_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT8  uiIpAddr[LEN_16];    /* ��ַ, ���ʮ�����ַ��� */
}SFE_ARP_SHOW_S;

/* ��ͨ���д�����ʾ������BFD��Ϣ�Ľṹ�� */
typedef struct tagSFE_BFD_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT32 u32SessionID;        /* BFD�ỰID */
}SFE_BFD_SHOW_S;

/* ��ͨ���д�����ʾ������ROUTE��Ϣ�Ľṹ�� */
typedef struct tagSFE_ROUTE_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT8  uiIpAddr[LEN_16];    /* ��ַ, ���ʮ�����ַ��� */
}SFE_ROUTE_SHOW_S;

#ifdef  __cplusplus
}
#endif

#endif

