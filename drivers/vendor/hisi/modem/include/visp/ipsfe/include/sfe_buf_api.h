/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_buf_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: ������MBUF��ض���API�ṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_BUF_API_H_
#define _SFE_BUF_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "sfe_buf_pub_api.h"

/* ������MBUFģ������붨�� */
typedef enum enumSfeMbufErrCode
{
    SFE_MBUF_OK = SFE_OK,                         /* �����ɹ� */
    SFE_MBUF_ERR_BEGIN = SFE_MBUF_BEGIN_RET_CODE, /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_MBUF_NULL_POINTER_FORWARD,                /* 1  ǰ��ָ��ʱ,DBD����DBΪ��ָ�� */
    SFE_MBUF_NULL_POINTER_BACKWARD,               /* 2  ����ָ��ʱ,DBD����DBΪ��ָ�� */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_FORWARD,         /* 3  ǰ��ָ��ʱ,DB���Ȳ��� */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_BACKWARD,        /* 4  ����ָ��ʱ,DB���Ȳ��� */
    SFE_MBUF_NULL_POINTER_CREATEBYSYSDB,          /* 5  ����ϵͳDB����MBUFʱ�����ָ�� */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATEBYSYSDB,  /* 6  ����ϵͳDB����MBUFʱ����MBUFͷʧ�� */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATEBYSYSDB,       /* 7  ����ϵͳDB����MBUFʱ����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_DB_LEN_INVALID_CREATEBYSYSDB,        /* 8  ����ϵͳDB����MBUFʱDB������DB���ݳ��Ȳ��Ϸ� */
    SFE_MBUF_DB_BEGIN_ADDR_INVALID_CREATEBYSYSDB, /* 9  ����ϵͳDB����MBUFʱDB��ʼ��ַ��DB������ʼ��ַ���Ϸ� */
    SFE_MBUF_DB_END_ADDR_INVALID_CREATEBYSYSDB,   /* 10 ����ϵͳDB����MBUFʱDB������ַ��DB���ݽ�����ַ���Ϸ� */
    SFE_MBUF_DB_SOURCE_INVALID_CREATEBYSYSDB,     /* 11 ����ϵͳDB����MBUFʱDB��Դ���Ϸ� */
    SFE_MBUF_NULL_POINTER_DESTROY,                /* 12 �ͷ�MBUFʱ�����ָ�� */
    SFE_MBUF_NULL_POINTER_CAT,                    /* 13 ��������MBUF�������Ϊ��ָ�� */
    SFE_MBUF_NULL_BUFPOINTER_CREATEBYBUF,         /* 14 ��buffer�������ݴ���MBUFʱ�����bufferָ��ΪNULL */
    SFE_MBUF_NULL_MBUFPOINTER_CREATE,             /* 15 ��������MBUFʱ,����Ĵ��MBUF��ַ���������ΪNULL */
    SFE_MBUF_LEN_INVALID_CREATE,                  /* 16 ��������MBUFʱ,�����Ԥ���ռ������ݳ���֮�ͳ�����һ��DB�ĳ��� */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATE,         /* 17 ��������MBUFʱ,����MBUFͷ�ṹʧ�� */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATE,              /* 18 ��������MBUFʱ,����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DB_FAIL_CREATE,               /* 19 ��������MBUFʱ,����MBUF���ݿ�DBʧ�� */
    SFE_MBUF_STRUCT_SIZE_ERR_INIT,                /* 20 �������ʼ��ʱ���MBUF�ṹ���С����ȷ */
    SFE_MBUF_NULL_GETPRIORITY,                    /* 21 ��ȡMBUF�б������ȼ�ʱ,����MBUFָ��ΪNULL */
    SFE_MBUF_INPUT_NULL_GETPRIORITY,              /* 22 ��ȡMBUF�б������ȼ�ʱ,����洢�������ȼ���ָ��ΪNULL */
    SFE_MBUF_GET_PRECFG_EXPEND_SIZE_ERR,          /* 23 ��ȡ��չMBUF֧��64λϵͳMBUF��չ��Ϣ����Ԥ����ʧ�� */
    SFE_MBUF_NULL_POINTER_CUTHEAD,                /* 24 ��Mbuf��DB�����ײ���ʼɾ��ָ�����ȵ�����ʱ�����ָ�� */
    SFE_MBUF_DATA_LEN_NOTENOUGH_CUTHEAD,          /* 25 ��Mbuf��DB�����ײ���ʼɾ��ָ�����ȵ�����ʱ�����ݳ��Ȳ��� */
    SFE_MBUF_NULL_POINTER_CUTTAIL,                /* 26 ��Mbuf��DB����β����ʼɾ��ָ�����ȵ�����ʱ�����ָ�� */
    SFE_MBUF_DATA_LEN_NOTENOUGH_CUTTAIL,          /* 27 ��Mbuf��DB����β����ʼɾ��ָ�����ȵ�����ʱ�����ݳ��Ȳ��� */
    SFE_MBUF_NULL_POINTER_DELDATA,                /* 28 ��MBUFָ��λ��ɾ��ָ����������ʱ�����ָ�� */
    SFE_MBUF_DATA_LEN_NOTENOUGH_DELDATA,          /* 29 ��MBUFָ��λ��ɾ��ָ����������ʱ�����ݳ��Ȳ��� */
    SFE_MBUF_NULL_POINTER_CREATEBYCPYMBUF,        /* 30 ����MBUF����MBUFʱ�����ָ�� */
    SFE_MBUF_LEN_INVALID_CREATEBYCPYMBUF,         /* 31 ����MBUF����MBUFʱ���Ȳ��Ϸ� */
    SFE_MBUF_DBD_NULL_POINTER_BY_LOCATE_CREATEBYCPYMBUF,  /* 32 ����MBUF����MBUFʱ,��ȡ����λ������ӦDB����ƫ��ʱDBDΪ�� */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_CREATEBYCPYMBUF,/* 33 ����MBUF����MBUFʱ����MBUFͷʧ�� */
    SFE_MBUF_MALLOC_DBD_FAIL_CREATEBYCPYMBUF,     /* 34 ����MBUF����MBUFʱ����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DB_FAIL_CREATEBYCPYMBUF,      /* 35 ����MBUF����MBUFʱ����MBUF���ݿ�DBʧ�� */
    SFE_MBUF_MALLOC_MBUF_POOL_FAIL,               /* 36 ��ʼ��MBUF�ڴ����ʧ�� */
    SFE_MBUF_LEN_INVALID_CREATECTRLPKT,           /* 37 ����������MBUFʱ,�����Ԥ���ռ������ݳ���֮�ͳ�����һ��DB�ĳ��� */
    SFE_MBUF_MBUF_NULL_POINTER_PULLUP,            /* 38 ��MBUF��ʼλ�ú��ָ���������ݷ���һ�������ڴ�ռ�ʱ�����ָ�� */
    SFE_MBUF_LEN_FOR_MBUF_INVALID_PULLUP,         /* 39 ��MBUF��ʼλ�ú��ָ���������ݷ���һ�������ڴ�ռ�ʱ���볤�ȴ��������ܳ��� */
    SFE_MBUF_LEN_FOR_DBD_INVALID_PULLUP,          /* 40 ��MBUF��ʼλ�ú��ָ���������ݷ���һ�������ڴ�ռ�ʱ���볤�ȴ�����DBD���ݿ��ÿռ��С */
    SFE_MBUF_DBD_OR_DB_NULL_POINTER_PULLUP,       /* 41 ��MBUF��ʼλ�ú��ָ���������ݷ���һ�������ڴ�ռ�ʱDBD��DBָ��Ϊ�� */
    SFE_MBUF_MBUF_NULL_POINTER_SETUSERPRVT,       /* 42 ���ò�Ʒ������Ϣ��MBUFʱMBUFָ��Ϊ�� */
    SFE_MBUF_PTRANDLEN_NOTMATCH_SETUSERPRVT,      /* 43 ���ò�Ʒ������Ϣ��MBUFʱ��������ָ���볤�Ȳ�ƥ��,�����ȷ���,��ָ��Ϊ�� */
    SFE_MBUF_DATALEN_INVAILD_SETUSERPRVT,         /* 44 ���ò�Ʒ������Ϣ��MBUFʱ�������ݳ��ȴ������ֵ */
    SFE_MBUF_INPUT_NULL_POINTER_GETUSERPRVT,      /* 45 ��ȡ��Ʒ������Ϣ��MBUFʱ����ָ��Ϊ�� */
    SFE_MBUF_MBUF_NULL_POINTER_INSERTDATA,        /* 46 ��MBUFָ��λ�ò���ָ����������ʱ����MBUF��ָ�� */
    SFE_MBUF_DTAT_LENORPTR_INVALID_INSERTDATA,    /* 47 ��MBUFָ��λ�ò���ָ����������ʱ��������ݳ���Ϊ����ָ��Ϊ�� */
    SFE_MBUF_STARTPOS_INVALID_INSERTDATA,         /* 48 ��MBUFָ��λ�ò���ָ����������ʱָ��λ�÷Ƿ�(���������ܳ���) */
    SFE_MBUF_MALLOC_DBD_INVALID_INSERTDATA,       /* 49 ��MBUFָ��λ�ò���ָ����������ʱDBD�쳣 */
    SFE_MBUF_MALLOC_DBD_1_FAIL_INSERTDATA,        /* 50 ��MBUFָ��λ�ò���ָ����������ʱλ��һ����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DBD_2_FAIL_INSERTDATA,        /* 51 ��MBUFָ��λ�ò���ָ����������ʱλ�ö�����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DBD_3_FAIL_INSERTDATA,        /* 52 ��MBUFָ��λ�ò���ָ����������ʱλ��������MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DB_1_FAIL_INSERTDATA,         /* 53 ��MBUFָ��λ�ò���ָ����������ʱλ��һ����MBUF���ݿ�DBʧ�� */
    SFE_MBUF_MALLOC_DB_2_FAIL_INSERTDATA,         /* 54 ��MBUFָ��λ�ò���ָ����������ʱλ�ö�����MBUF���ݿ�DBʧ�� */
    SFE_MBUF_MALLOC_DB_3_FAIL_INSERTDATA,         /* 55 ��MBUFָ��λ�ò���ָ����������ʱλ��������MBUF���ݿ�DBʧ�� */
    SFE_MBUF_NULL_POINTER_GETTAIL,                /* 56 ��Mbuf��DB����β����ʼ��ȡָ�����ȵ�����ʱ�����ָ�� */
    SFE_MBUF_DATA_LEN_INVAILD_GETTAIL,            /* 57 ��Mbuf��DB����β����ʼ��ȡָ�����ȵ�����ʱ�����ݳ��Ȳ�����ָ������Ϊ0 */
    SFE_MBUF_MBUF_NULL_POINTER_REPLACEDATA,       /* 58 ��MBUFָ��λ���滻ָ����������ʱ����MBUF��ָ�� */
    SFE_MBUF_DTAT_LENORPTR_INVALID_REPLACEDATA,   /* 59 ��MBUFָ��λ���滻ָ����������ʱ��������ݳ���Ϊ����ָ��Ϊ�� */
    SFE_MBUF_STARTPOS_INVALID_REPLACEDATA,        /* 60 ��MBUFָ��λ���滻ָ����������ʱָ��λ�÷Ƿ�(���������ܳ���) */
    SFE_MBUF_MALLOC_DBD_INVALID_REPLACEDATA,      /* 61 ��MBUFָ��λ���滻ָ����������ʱDBD�쳣 */
    SFE_MBUF_INPUT_NULL_POINTER_FRAGMENT,         /* 62 �ڲ��Mbufʱ�����ָ�� */
    SFE_MBUF_INPUT_LEN_INVALID_FRAGMENT,          /* 63 �ڲ��Mbufʱ����ķ�Ƭ����Ϊ0��Ԥ�����ȷǷ� */
    SFE_MBUF_MALLOC_MBUFHEAD_FAIL_FRAGMENT,       /* 64 �ڲ��Mbufʱ����MBUFͷʧ�� */
    SFE_MBUF_MALLOC_DBD_FAIL_FRAGMENT,            /* 65 �ڲ��Mbufʱ����MBUF���ݿ�������DBDʧ�� */
    SFE_MBUF_MALLOC_DB_FAIL_FRAGMENT,             /* 66 �ڲ��Mbufʱ����MBUF���ݿ�DBʧ�� */
    SFE_MBUF_DBD_INVAILD_FRAGMENT,                /* 67 �ڲ��MbufʱDBD�Ƿ� */
    SFE_MBUF_FAIL_MAKE_MEMORY_CONTINUOUS,         /* 68 ʹMBUFͷ�������ĺ�,����ʧ�� */
    SFE_MBUF_GET_PRECFG_POOL_INIT_NUM_ERR,        /* 69 ��ȡ��չMBUF֧��64λϵͳMBUF��ʼ��Դ�ش�СԤ����ʧ�� */
    SFE_MBUF_DBD_NULL_POINTER_BY_COPY_CREATEBYCPYMBUF,  /* 70 ����MBUF����MBUFʱ,��������ʱDBDΪ�� */

    SFE_MBUF_MBUF_NULL_POINTER_MODIFY_PKTLEN,     /* 71 �޸�MBUF���ĳ���ʱ,����MBUF��ָ�� */
    SFE_MBUF_LEN_INVALID_MODIFY_PKTLEN,           /* 72 �޸�MBUF���ĳ���ʱ,��������ݳ�����Ԥ���ռ�֮�ͳ�����һ��DB�ĳ��� */
    SFE_MBUF_MBUF_NULL_POINTER_SETUSERPRVTLEN,    /* 73 ���ò�Ʒ������Ϣ���ȵ�MBUFʱMBUFָ��Ϊ�� */
    SFE_MBUF_DATALEN_INVAILD_SETUSERPRVTLEN,      /* 74 ���ò�Ʒ������Ϣ���ȵ�MBUFʱ�������ݳ��ȴ������ֵ */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_TAIL_FORWARD,    /* 75 TCP����ʱ��Ҫ���ظ����ݳ���ƫ�Ƶ�,��ԭʱ,���ֵ�ǰDB�ռ䲻�� */
    SFE_MBUF_NULL_POINTER_TAIL_FORWARD,           /* 76 TCP����ʱ��Ҫ���ظ����ݳ���ƫ�Ƶ�,��ԭʱ,DBD����DBΪ��ָ�� */
    SFE_MBUF_DB_LENGTH_NOTENOUGH_TAIL_BACKWARD,   /* 77 TCP����ʱ��Ҫ���ظ����ݳ���ƫ�Ƶ�ʱ,���ֵ�ǰDB�ռ䲻�� */
    SFE_MBUF_NULL_POINTER_TAIL_BACKWARD,          /* 78 TCP����ʱ��Ҫ���ظ����ݳ���ƫ�Ƶ�ʱ,DBD����DBΪ��ָ�� */

    SFE_MBUF_FREE_NULL_ONESEG_MBUF,               /* 79 �ͷ�һ��ʽMBUF��ͷʱ�������ָ��Ϊ��*/
    SFE_MBUF_REPET_FREE_ONESEG_MBUF,              /* 80 �ظ��ͷ�һ��ʽMBUF��ͷ*/
    SFE_MBUF_REPET_FREE_ONESEG_DBD,               /* 81 �ظ��ͷ�һ��ʽMBUF��DBD*/
    SFE_MBUF_REPET_FREE_ONESEG_DB,                /* 82 �ظ��ͷ�һ��ʽMBUF��DB*/
    SFE_MBUF_REPET_FREE_ONESEG_SYSDB,             /* 83 �ظ��ͷ�һ��ʽMBUF��SYSDB*/
    SFE_MBUF_MULTI_DBD_MODIFY_PKTLEN,             /* 84 �޸�MBUF���ĳ���ʱ,�����MBUF��DBD������Ψһ */
    SFE_MBUF_GET_POOLUNITNUM_BEFORE_INIT,         /* 85 ��ϵͳ��ʼ��ǰ,���ܻ�ȡ��MBUF��Դ��ͳ�� */
    SFE_MBUF_GET_POOLUNITNUM_INPUT_PARA_INVALID,  /* 86 ��ȡMBUF��Դ��ͳ��ʱ,����Ĳ����ж�ʧ�� */
    SFE_MBUF_GET_POOLUNITNUM_INPUT_FAILED,        /* 87 ��ȡMBUF��Դ��ͳ��ʱ,��ȡ���Ŀ��е�Ԫ���Ƿ�*/
}SFE_MBUF_ERR_CODE_E;


/* �û�����MBUFʱ��СԤ������ */
#define SFE_MBUF_DB_MIN_RESERVE_SPACE 128


/*******************************************************************************
*    Func Name: SFE_MBUF_CreateBySysDB
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: ����ϵͳDB����MBUF
*  Description: ����ϵͳDB����MBUF
*        Input: SFE_MBUF_DATABLOCKDESCRIPTOR_S **ppstDBDAddr: ������ݿ�������DBD��ʼ��ַ<�ǿ�ָ��>
*               UINT8 *pu8DBAddr: DB��ʼ��ַ<�ǿ�ָ��>
*               UINT32 u32DBLen: DB����<�޷���32λֵ>
*               UINT8 *pu8DataAddr: DB��������ʼ��ַ<�ǿ�ָ��>
*               UINT32 u32DataLen: DB�����ݳ���<�޷���32λֵ>
*               VOID  *pstSysDBCtrl: ϵͳDB��Ӧ�Ŀ��ƿ�, ��ѡ<�ǿ�ָ��>
*               UINT32 u32DataSource: DB��Դ<�޷���32λֵ>
*               UINT32 u32ModuleID: ģ��ID, ��16bit������Ʒʹ��<�޷���32λֵ>
*       Output: SFE_MBUF_S **ppstMbuf: ��Ź���õ�MBUF��ַ<�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: Important points if any
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28   wangmingxia/luowentong          Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateBySysDB(SFE_MBUF_S **ppstMbuf, SFE_MBUF_DATABLOCKDESCRIPTOR_S **ppstDBDAddr,
                                     UINT8 *pu8DBAddr, UINT32 u32DBLen,
                                     UINT8 *pu8DataAddr, UINT32 u32DataLen,
                                     VOID  *pstSysDBCtrl,
                                     UINT32 u32DataSource,
                                     UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_CreateByCopyBuffer
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: �������ݴ���MBUF
*  Description: �������ݴ���MBUF
*        Input: UINT32 u32ReserveHeadSpace: MBUF���ݿ�ͷ��Ԥ���Ŀռ䳤��,<�޷���32λֵ>
*               ��Ʒ�ڴ���MBUFʱ����Ԥ���㹻��������VISPЭ��ջ����ʱ���ͷ����Ϣ.��128�ֽ�.
*               UINT32 u32DataLength: �������ݳ���<�޷���32λֵ>
*               UINT8 *pu8DataBuffer: �����ַ<�ǿ�ָ��>
*               UINT32 u32ModuleID: ���ô˺�����ģ���<�޷���32λֵ>
*       Output: SFE_MBUF_S **ppstMbuf: �ɹ�ʱ�����´�����MBUF��ַ<�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.��Ʒ����MBUFʱ����ָ��Ԥ������.
*                 Ԥ���ĳ��ȱ������Э��ջ������Ҫ��ӵ�ͷ������,����Ԥ��128�ֽڡ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateByCopyBuffer(SFE_MBUF_S **ppstMbuf, UINT32 u32ReserveHeadSpace,
                                          UINT32 u32DataLength, UINT8 *pu8DataBuffer, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_CreateForControlPacket
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: ����ָ�����ȵ�������MBUF
*  Description: ����ָ�����ȵ�������MBUF
*        Input: UINT32 u32ReserveHeadSpace: MBUF���ݿ�ͷ��Ԥ���Ŀռ䳤��<�޷���32λֵ>
*               UINT32 u32DataLength: ����MBUF֮��Ҫ�������ݳ���<�޷���32λֵ>
*               UINT32 u32ModuleID: ���ô˺�����ģ���<�޷���32λֵ>
*       Output: SFE_MBUF_S **ppstMbuf: �ɹ�ʱ�����´�����MBUF��ַ<�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.��Ʒ����MBUFʱ����ָ��Ԥ������.
*                 Ԥ���ĳ��ȱ������Э��ջ������Ҫ��ӵ�ͷ������,����Ԥ��128�ֽڡ�
*               2.�ýӿ�ֻ֧�ִ���һ��DB��������MBUF��
*               3.��Ʒ��ʹ�øýӿڴ��������ݵ�MBUF��,��Ʒ���MBUF����д�����ݳ���һ��Ҫ�봴��MBUF
*                 ʱָ���ĳ������.����������������SFE_MBUF_ModifyControlPacketLen�ӿ��޸�
*                 MBUF�м�¼�����ݳ��ȡ�
*    Reference: SFE_MBUF_CreateBySysDB
*               SFE_MBUF_CreateByCopyBuffer
*               SFE_MBUF_Destroy
*               SFE_MBUF_ModifyControlPacketLen
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_CreateForControlPacket(SFE_MBUF_S **ppstMbuf, UINT32 u32ReserveHeadSpace,
                                              UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_ModifyControlPacketLen
* Date Created: 2009-9-12
*       Author: w60786/h00121208
*      Purpose: �޸�ʹ��SFE_MBUF_CreateForControlPacket�ӿڴ�����MBUF�м�¼�����ݳ���.
*  Description: �޸�ʹ��SFE_MBUF_CreateForControlPacket�ӿڴ�����MBUF�м�¼�����ݳ���.
*        Input: SFE_MBUF_S *pstMbuf: MBUFָ��<�ǿ�ָ��>
*               UINT32 u32DataLength: MBUF�е�ǰ�洢�����ݳ���<32λ�޷�������>
*               UINT32 u32ModuleID: ���ô˺�����ģ���<32λ�޷�������>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.��Ʒ���뱣֤�����MBUFֻ����ͨ��SFE_MBUF_CreateForControlPacket�ӿڴ�����MBUF��
*               2.��Ʒ���뱣֤�����MBUF������ֻ��һ��DB��
*    Reference: SFE_MBUF_CreateForControlPacket
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_ModifyControlPacketLen(SFE_MBUF_S *pstMbuf, UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Destroy
* Date Created: 2009-8-11
*       Author: w60786
*      Purpose: MBUF�ͷź���
*  Description: MBUF�ͷź���
*        Input: SFE_MBUF_S *pstMBuf: ���ͷŵ�MBUF<�ǿ�ָ��>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: Important points if any
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-11    wangmingxia/luowentong          Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_Destroy(SFE_MBUF_S *pstMBuf);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetPktPriority
* Date Created: 2009-11-7
*       Author: w60786
*      Purpose: ��ȡMBUF�б������ȼ�
*  Description: ��ȡMBUF�б������ȼ�
*        Input: SFE_MBUF_S *pstMBuf: ����MBUFָ��<�ǿ�ָ��>
*       Output: UINT32 *pu32PktPriority: �������ȼ� <�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution:
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-7    w60786           Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_MBUF_GetPktPriority(SFE_MBUF_S *pstMBuf, UINT32 *pu32PktPriority);

/*******************************************************************************
*    Func Name: SFE_MBUF_InsertData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��MBUFָ��λ�ò���ָ����������
*  Description: ��MBUFָ��λ�ò���ָ����������
*        Input: SFE_MBUF_S *pstMbuf:  ���������ݵ�MBUF<�ǿ�ָ��>
*               UINT32 u32StartPo:    �������������MBUF�е���ʼ�洢λ��<[0,Mbuf���ݳ���]>
*               UINT8 *pu8DataBuffer: ���������ݻ�����<�ǿ�ָ��>
*               UINT32 u32DataLength: ����������ݳ���<32λ�޷�������>
*               UINT32 u32ModuleID:   ģ��ID<32λ�޷�������>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.���øýӿں�������ʼָ����ܻᷢ���仯,��������ڸýӿڵ���֮���û�
*                 ϣ������MBUF�е�����,��������»�ȡ���ݵ���ʼ��ַ.
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_InsertData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos, UINT8 *pu8DataBuffer,
                           UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_DeleteData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��MBUFָ��λ��ɾ��ָ����������
*  Description: ��MBUFָ��λ��ɾ��ָ����������
*        Input: SFE_MBUF_S *pstMbuf:  ��ɾ�����ݵ�MBUF<�ǿ�>
*               UINT32 u32StartPo:    ��ɾ�����ݵ���ʼλ��<[0,Mbuf���ݳ���]>
*               UINT32 u32DataLength: ��ɾ�������ݳ���<32λ�޷�������>
*               UINT32 u32ModuleID:   ģ��ID<32λ�޷�������>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.���øýӿں�������ʼָ����ܻᷢ���仯,��������ڸýӿڵ���֮���û�
*                 ϣ������MBUF�е�����,��������»�ȡ���ݵ���ʼ��ַ.
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_DeleteData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos,
                           UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_ReplaceData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��MBUFָ��λ���滻ָ����������
*  Description: ��MBUFָ��λ���滻ָ����������
*        Input: SFE_MBUF_S *pstMbuf:  ���滻���ݵ�MBUF<�ǿ�ָ��>
*               UINT32 u32StartPo:    ���滻��������MBUF�е���ʼ�洢λ��<[0,Mbuf���ݳ���]>
*               UINT8 *pu8DataBuffer: ���滻���ݻ�����<32�ǿ�ָ��
*               UINT32 u32DataLength: ���滻�����ݳ���<32λ�޷�������>
*               UINT32 u32ModuleID:   ģ��ID<32λ�޷�������>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution:
*    Reference: SFE_MBUF_DeleteData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_GetTailData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_ReplaceData(SFE_MBUF_S *pstMbuf, UINT32 u32StartPos,
                            UINT8 *pu8DataBuffer, UINT32 u32DataLength, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Fragment
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��һ��MBUF��ֳɶ��MBUF
*  Description: ��һ��MBUF��ֳɶ��MBUF
*        Input: SFE_MBUF_S *pstOriginMbuf:      Ҫ��ֵ�ԭʼMBUF����<�ǿ�ָ��>
*               UINT32 u32ReserveLen:           ��ÿ��MBuf ��һ��DBͷ��Ԥ���ĳ���<32λ�޷�������>
*               UINT32 u32FragLen:              Ҫ��ֵ����ݳ���<��0,32λ�޷�������>
*               UINT32 u32ModuleID:             ģ��ID<32λ�޷�������>
*       Output: SFE_MBUF_S **ppstFragMbufChain: ��ֺ��MBuf����ͷ<�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.����ָ���ĳ��Ȳ��MBUF���ڲ�ֺ��µ�MBUF ��һ��DBͷ��Ԥ��ָ���ĳ��ȡ�
*               2.��ֺ�����һ��MBUF��С����С��ָ���Ĳ�ֳ��ȡ�
*               3.�ú������۷��سɹ�����ʧ��,�ú����������ͷ�ԭʼ�ı���MBUF,�����ɵ����߸����ͷ�.
*               4.���ԭʼ���ĵĳ���С�ڵ�����Ҫ��Ƭ�ĳ����򷵻�ʧ��.��Ʒ���øú���ʱҪ��֤ԭʼ����
*                 ����Ҫ�ȷ�Ƭ���ȴ�.
*    Reference: SFE_MBUF_Concatenate
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_Fragment(SFE_MBUF_S *pstOriginMbuf, SFE_MBUF_S **ppstFragMbufChain,
                         UINT32 u32ReserveLen, UINT32 u32FragLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_Concatenate
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: �ϲ�����MBUF����һ��MBUF�е��������ӵ���һ��MBUF�ĺ���
*  Description: �ϲ�����MBUF����һ��MBUF�е��������ӵ���һ��MBUF�ĺ���
*        Input: SFE_MBUF_S *pstDstMbuf: Ŀ��MBUF<�ǿ�>
*               SFE_MBUF_S *pstSrcMbuf: Ҫ�ϲ���MBUF
*               UINT32 u32ModuleID:     ģ��ID
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution:
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_Concatenate(SFE_MBUF_S *pstDstMbuf, SFE_MBUF_S *pstSrcMbuf, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_SetUserPrivateData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ���ò�Ʒ������Ϣ��MBUF��
*  Description: ���ò�Ʒ������Ϣ��MBUF��
*        Input: SFE_MBUF_S *pstMbuf: MBUF����<�ǿ�>
*               UINT8 *pu8DataBuf:   ��Ʒ����������ʼ��ַ
*               UINT32 u32DataLen:   ���ݳ���<[0,64]>
*               UINT32 u32ModuleID:  ģ��ID<32λ�޷�������>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 
*    Reference: SFE_MBUF_SetUserPrivateDataLen
*               SFE_MBUF_GetUserPrivateBufInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_SetUserPrivateData(SFE_MBUF_S *pstMbuf, UINT8 *pu8DataBuf,
                                   UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetUserPrivateBufInfo
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��ȡ�����еĲ�Ʒ������Ϣ
*  Description: ��ȡ�����еĲ�Ʒ������Ϣ
*        Input: pstMbuf: MBUF����<�ǿ�>
*       Output: ppu8UserBufAddr MBUF�д�Ų�Ʒ�������ݻ������ʼ��ַ
*               pu32UserBufLen: MBUF�д�Ų�Ʒ�������ݻ���ĳ���<[0,64]>
*               pu32UserDataLen: MBUF�д�ŵ�ʵ���������ݳ���
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.�û����뱣֤�ڲ���˽�л���ʱ����Խ��,���ܳ�����󳤶�*pu32UserBufLen
*               2.�û�ʹ��SFE_MBUF_GetUserPrivateBufInfo��ȡ�û�˽�л��沢������д���ݺ�,
*                 �������SFE_MBUF_SetUserPrivateDataLen�ӿڽ��������ݳ������õ�MBUF��.
*    Reference: SFE_MBUF_SetUserPrivateDataLen
*               SFE_MBUF_GetUserPrivateBufInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_GetUserPrivateBufInfo(SFE_MBUF_S *pstMbuf, UINT8 **ppu8UserBufAddr,
                                      UINT32 *pu32UserBufLen, UINT32 *pu32UserDataLen);

/*******************************************************************************
*    Func Name: SFE_MBUF_SetUserPrivateDataLen
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ���ñ����еĲ�Ʒʵ���������ݳ���
*  Description: ���ñ����еĲ�Ʒʵ���������ݳ���
*        Input: SFE_MBUF_S *pstMbuf: MBUF����<�ǿ�>
*               UINT32 u32UserDataLen: MBUF�д�ŵ�ʵ���������ݳ���
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: �û����뱣֤���õĳ��Ȳ����Ϸ�,���ܳ���MBUF�еĲ�Ʒ˽�л�����󳤶�
*    Reference: SFE_MBUF_GetUserPrivateBufInfo
*               SFE_MBUF_SetUserPrivateData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_SetUserPrivateDataLen(SFE_MBUF_S *pstMbuf, UINT32 u32UserDataLen);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetTailData
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: ��ȡMBUFβ��ָ�����ȵ�����
*  Description: ��ȡMBUFβ��ָ�����ȵ�����
*        Input: SFE_MBUF_S *pstMbuf: MBUF����<�ǿ�>
*               UINT32 u32DataLen: Ҫ��ȡ��β�����ݳ��� <32λ�޷�������>
*               UINT32 u32ModuleID:  ģ��ID<32λ�޷�������>
*       Output: UINT8 *pu8DataBuf: ��Ż�ȡ���ݵĻ�����,��Ʒ���뱣֤������������u32DataLen��<�ǿ�ָ��>
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution:
*    Reference: SFE_MBUF_InsertData
*               SFE_MBUF_ReplaceData
*               SFE_MBUF_DeleteData
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_MBUF_GetTailData(SFE_MBUF_S *pstMbuf, UINT8 *pu8DataBuf, UINT32 u32DataLen, UINT32 u32ModuleID);

/*******************************************************************************
*    Func Name: SFE_MBUF_GetPoolTotalAndFreeUnitNum
* Date Created: 2011-07-26
*       Author: zhukun 00166124 
*      Purpose: ��ȡMBUF��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*  Description: ��ȡMBUF��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum: MBUF��Դ���ܵĵ�Ԫ��
*               UINT32 *pu32FreeUnitNum: MBUF��Դ��ʣ��ĵ�Ԫ��
*       Return: �ɹ�:SFE_MBUF_OK
*               ʧ��:������
*      Caution: 1.MBUF��Դ���ܵ�Ԫ��Ϊ��ʼ������ֵ����Ϊ����Ԥ���ĵ�Ԫ��SFE_MBUF_RESERVE_MBUF_NUM
*               2.�ýӿ�Ҫ��ϵͳ������ɺ���ò�����Ч
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-26   zhukun 00166124         Create
*
*******************************************************************************/
UINT32 SFE_MBUF_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

#ifdef  __cplusplus
}
#endif

#endif


