/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_addr_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2010-6-9
*        Author: w60786
*   Description: �������ַ����ģ���û�APIͷ�ļ��������û���Ҫʹ�õ����ݽṹ�����APIԭ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-6-9     w60786           Creat the first version.
*
*******************************************************************************/
#ifndef _SFE_ADDR_API_H_
#define _SFE_ADDR_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������ADDRģ������� */
typedef enum enumSfeAddrErrCode
{
    SFE_ADDR_OK = SFE_OK,                               /* �����ɹ� */
    SFE_ADDR_ERR_BEGIN = SFE_ADDR_BEGIN_RET_CODE,       /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ADDR_IFID_INVALID_ADD,                          /* 1  Ҫ��ӵ�ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_IP_INVALID_ADD,                            /* 2  Ҫ��ӵ�ַ�Ĳ��Ϸ� */
    SFE_ADDR_GETBASEINFOFAIL_ADD,                       /* 3  ��ӵ�ַ,��ȡ�ӿ�base�ڵ�ʧ�� */
    SFE_ADDR_IP_NUM_MAX_ADD,                            /* 4  ��ӵ�ַ,�ӿڵĵ�ַ��Ŀ�Ѿ��ﵽ���ֵ */
    SFE_ADDR_MALLOC_FAIL_ADDIPADDR_ADD,                 /* 5  ��ӵ�ַ,��ȡ��ַ�������ݽṹ����ʧ�� */
    SFE_ADDR_GETBASEINFOFAILFORUPDATE_ADD,              /* 6  ��ӵ�ַ,��ȡ��ַ�������ݽṹ�ڵ�ʧ�� */
    SFE_ADDR_IP_HAS_SETTED_ADD,                         /* 7  ��ӵ�ַ,IP����ͳһ�ӿ����ù� */
    SFE_ADDR_IFID_INVALID_DEL,                          /* 8  Ҫɾ����ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_IP_INVALID_DEL,                            /* 9  Ҫɾ����ַ�Ľӿ�ָ��Ϊ�� */
    SFE_ADDR_GETBASEINFOFAIL_DEL,                       /* 10 ɾ����ַ,��ȡ�ӿ�base�ڵ�ʧ�� */
    SFE_ADDR_IP_NOT_EXIST_DEL,                          /* 11 ɾ����ַ,Ҫɾ���ĵ�ַ������ */
    SFE_ADDR_FREE_IPADDR_FAIL_DEL,                      /* 12 ɾ����ַ,��Դ���ͷŵ�ַ�ڵ�ʧ�� */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PRECFG_FAIL,        /* 13 ��ַ�����ʼ��,��ȡ��ַ��Դ��ʼ������ʧ�� */
    SFE_ADDR_GET_SFE_IPADDR_MAX_NUM_PER_IF_PRECFG_FAIL, /* 14 ��ַ�����ʼ��,��ȡÿ���ӿ���������IP ADDR��Ŀʧ�� */
    SFE_ADDR_ALLOC_IP_ADDR_POOL_FAIL,                   /* 15 ��ַ�����ʼ��,��ʼ��IP ADDR��Դ��ʧ�� */

}SFE_ADDR_ERR_CODE_E;

/*******************************************************************************
*    Func Name: SFE_ADDR_AddIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: ��ӵ�ַ
*  Description: ��ӵ�ַ
*        Input: UINT32 u32IpAddr: Ҫ��ӵĵ�ַ(������)
*               UINT32 u32SubnetMask: Ҫ��ӵĵ�ַ��������
*               SFE_MBUF_IFID_S *pstIfId: Ҫ��ӵ�ַ�Ľӿ�
*       Output: 
*       Return: �ɹ����� SFE_ADDR_OK
*               ʧ�ܷ��� ������
*      Caution: 1.�ɵ����߱�֤һ����ַֻ��������һ���ӿ���.�ڲ���������ж�.
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 SFE_ADDR_AddIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);

/*******************************************************************************
*    Func Name: SFE_ADDR_DelIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: ɾ����ַ
*  Description: ɾ����ַ
*        Input: UINT32 u32IpAddr: Ҫɾ���ĵ�ַ(������)
*               UINT32 u32SubnetMask: Ҫɾ���ĵ�ַ����������
*               SFE_MBUF_IFID_S *pstIfId: Ҫɾ����ַ�Ľӿ�
*       Output: 
*       Return: �ɹ����� SFE_ADDR_OK
*               ʧ�ܷ��� ������
*      Caution: 
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
UINT32 SFE_ADDR_DelIpAddr(UINT32 u32IpAddr, UINT32 u32SubnetMask, SFE_MBUF_IFID_S *pstIfId);

/*******************************************************************************
*    Func Name: SFE_ADDR_ShowIpAddr
* Date Created: 2010-06-04
*       Author: w60786
*      Purpose: ��ʾ���������е�ַ��Ϣ
*  Description: ��ʾ���������е�ַ��Ϣ
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-04   w60786                  Create
*
*******************************************************************************/
VOID SFE_ADDR_ShowIpAddr(VOID);


#ifdef  __cplusplus
}
#endif

#endif

