/*************************************************************************
*   ��Ȩ����(C) 2008-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  adp_nvim.c
*
*   ��    �� :  y00228784
*
*   ��    �� :  v7r2Ϊ������v7r1�ӿڵ�һ�µ������ļ�
*
*   �޸ļ�¼ :  2013��2��26��  v1.00    y00228784 ����
*************************************************************************/

/*lint -save -e537*/
#include <securec.h>
#include "bsp_nvim.h"
#include "mdrv_nvim.h"
#include "drv_comm.h"
#include "nv_comm.h"
/*lint -restore*/
#ifdef __cplusplus
extern "C"
{
#endif

#define  NV_RESULT_CODE            0xffff
/*lint -save -e958 -e438*/
#ifdef CONFIG_NVIM
/*lint -save -e18*/

/*****************************************************************************
* �� �� ��  : mdrv_nv_readex
*
* ��������  : ����ͬModem NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcread(card_id, itemid,(BSP_U8*)pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_writeex
*
* ��������  : д��ͬModem NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcwrite(card_id, itemid,(BSP_U8*)pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_read_partex
*
* ��������  : ��NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcreadpart(card_id,itemid,ulOffset,(BSP_U8*)pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_write_partex
*
* ��������  : д����NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcwritepart(card_id,itemid,ulOffset,(BSP_U8*)pdata,ulLength);
}


/*****************************************************************************
* �� �� ��  : mdrv_nv_flush
*
* ��������  : ���ڴ��е�nv����ˢ��flash �ļ�ϵͳ��
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_flush()
{
   return bsp_nvm_flush() & NV_RESULT_CODE;
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_get_length
*
* ��������  : ��ȡNV����
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;

    ret = bsp_nvm_get_len(itemid,&len);
    if(ret)
    {
        return ret;
    }
    *pulLength = len;
    return 0;
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_read
*
* ��������  : ��NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_read(itemid,pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_write
*
* ��������  : дNV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_write(itemid,pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_readpart
*
* ��������  : ������NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_readpart(itemid,ulOffset,pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_writepart
*
* ��������  : д����NV������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_writepart(itemid,ulOffset,pdata,ulLength);
}

/*****************************************************************************
* �� �� ��  : mdrv_nv_restore_result
*
* ��������  :  �ָ�������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore_result()
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}

#else

#include <osl_common.h>

unsigned int mdrv_nv_get_nvid_num()
{
    return 0;
}


unsigned int mdrv_nv_get_nvid_list(NV_LIST_INFO_STRU *pstNvIdList)
{
    if(pstNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return 0;
}

unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_flush()
{
    return 0;
}

unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength)
{
    return 0;
}


unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}


unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}


unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_restore_result()
{
    return 0;
}

#endif

/*lint -restore*/

#ifdef __cplusplus
}
#endif

