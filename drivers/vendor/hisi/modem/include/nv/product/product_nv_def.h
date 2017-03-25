/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_def.h
  Description     :   ����NV �ṹ�嶨��
  History         :
******************************************************************************/

#ifndef __PRODUCT_NV_DEF_H__
#define __PRODUCT_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_CHECK_NUM       1000

/*��ο��ṹ������*/
typedef struct
{
    int reserved;  /*note */
}PRODUCT_MODULE_STRU;

typedef struct
{
    u32 uwGuCrcResult;                      /* GU����NV��У���� */
    u32 uwTlCrcResult;                      /* TL����NV��У���� */
    u32 uwGuM2CrcResult;                    /* GU����NV��У���� */
}NV_CRC_CHECK_RESULT_STRU;

typedef struct
{
    u16 uhwValidCount;                       /* ָʾ��Ч���ݵĸ��� */
    u16 uhwRsv;                              /* ����λ */
    u16 auhwNeedCheckID[MAX_CHECK_NUM];      /* ������Ҫ����NV_IDֵ */
}NV_CHECK_ITEM_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


