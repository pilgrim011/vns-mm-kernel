
/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  product_version_info.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  ����ά��Ӳ���汾�������Ϣ
*
*   �޸ļ�¼ :  2013��2��23��  v1.00  zuofenghua  ����
*
*************************************************************************/

/*lint --e{537}*/
/*lint -save -e958*/

#include <string.h>
#include "securec.h"
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_version.h>

PRODUCT_INFO_NV_STRU huawei_product_info = {0};
NV_SW_VER_STRU nv_sw_ver={0};

/*****************************************************************************
* �� �� ��  	: bsp_version_productinfo_init
*
* ��������  : ��NV(0xD115)��ֵ��huawei_product_info
*
* ����˵��  : ��
*
*����ֵ : VER_ERROR��ʾ��ȡ�쳣
*                   VER_OK��ʾ��ȡ����
*****************************************************************************/
static __inline__ int bsp_version_productinfo_init(void)
{
    u32 ret = 0;
    u32 hw_ver = bsp_get_version_info()->board_id;

    /*lint -save -e26 -e119*/
    ret = bsp_nvm_read(NV_ID_DRV_NV_VERSION_INIT,(u8*)&huawei_product_info,sizeof(PRODUCT_INFO_NV_STRU));
    if(NV_OK != ret)
    {
        ver_print_error(" bsp_nvm_read failed!\n");
        return VER_ERROR;
    }

    if(hw_ver!=huawei_product_info.index){
        ver_print_error(" product id(0x%x) is not defined in xml!\n",hw_ver);
        huawei_product_info.index = hw_ver;
        return VER_ERROR;
    }
    /*lint -restore*/

    return VER_OK;
}

/*****************************************************************************
* �� �� ��  	: bsp_version_ccore_init
*
* ��������  : ccore�汾�ų�ʼ��
*
* ����˵��  : ��
*
*����ֵ : ��
*****************************************************************************/
int bsp_version_ccore_init(void)
{
    int ret = VER_ERROR;
    (void)memset_s((void *)(&huawei_product_info), sizeof(PRODUCT_INFO_NV_STRU), 0, sizeof(PRODUCT_INFO_NV_STRU));

    ret = bsp_version_productinfo_init();
    if(VER_ERROR==ret)
        ver_print_error("bsp_version_productinfo_init fail! ");
    else
        ver_print_error("bsp version ccore init OK!\n");

    mdrv_ver_init();
    return ret;
}



/*****************************************************************************
*                                                                                                                               *
*            ���½ӿ��ṩ��mdrv�ӿڵ���                                                  *
*                                                                                                                               *
******************************************************************************/



/*****************************************************************************
* �� ��	: bsp_version_get_hardware
* �� ��	: ��ȡӲ���汾��(Ӳ���汾����+ Ver.+Ӳ���Ӱ汾��+A)
*****************************************************************************/
char * bsp_version_get_hardware(void)
{
    u32 len;
    static bool b_geted=false;
    static char hardware_version[VERSION_MAX_LEN];
    char hardware_sub_ver = 0;

    if((HW_VER_INVALID == huawei_product_info.index))
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    if(!b_geted){
        /*lint -save -e18 -e718 -e746 -e732*/
        len = (unsigned int)(strlen(huawei_product_info.hwVer) + strlen(" Ver.X"));
        hardware_sub_ver = (char)huawei_product_info.hwIdSub+'A';
        (void)memset_s((void *)hardware_version, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(hardware_version, VERSION_MAX_LEN, huawei_product_info.hwVer, 
        strlen(huawei_product_info.hwVer)), VERSION_MAX_LEN, " Ver.", strlen(" Ver."));
        *((hardware_version + len) - 1) = hardware_sub_ver;
        *(hardware_version + len) = 0;
        b_geted=true;
    }

    return (char *)hardware_version;
}

/*****************************************************************************
* �� ��	: bsp_get_product_inner_name
* �� ��	: ��ȡ�ڲ���Ʒ����(�ڲ���Ʒ��+ �ڲ���Ʒ��plus)
*****************************************************************************/
char * bsp_version_get_product_inner_name(void)
{
    unsigned int len;
    static bool b_geted=false;
    static char product_inner_name[VERSION_MAX_LEN];

    if( HW_VER_INVALID == huawei_product_info.index)
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    if(!b_geted){
        len = (unsigned int)(strlen(huawei_product_info.name)+ strlen(huawei_product_info.namePlus));
        /*lint -save -e732*/
        (void)memset_s((void*)product_inner_name, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(product_inner_name, VERSION_MAX_LEN, huawei_product_info.name, strlen(huawei_product_info.name)), VERSION_MAX_LEN, huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));
        *(product_inner_name+len) = 0;
        b_geted=true;
    }

    return  (char*)product_inner_name;
}

/*****************************************************************************
* �� ��	: bsp_get_product_out_name
* �� ��	: ��ȡ�ⲿ��Ʒ����
*****************************************************************************/
char * bsp_version_get_product_out_name(void)
{
    if(HW_VER_INVALID == huawei_product_info.index)
    {
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return NULL;
    }

    return (char *)huawei_product_info.productId;
}



/*****************************************************************************
*                                                                                                                               *
*            ���½ӿ��ṩ��dumpģ�����                                                 *
*                                                                                                                               *
******************************************************************************/



/*****************************************************************************
* �� ��	: bsp_get_build_date_time
* �� ��	: ��ȡ�������ں�ʱ��
*****************************************************************************/
char * bsp_version_get_build_date_time(void)
{
	static char * build_date   = __DATE__ ", " __TIME__;
	return build_date;
}

/*****************************************************************************
* �� ��	: bsp_get_chip_version
* �� ��	: ��ȡоƬ�汾��
*****************************************************************************/
char * bsp_version_get_chip(void)
{
	return (char *)PRODUCT_CFG_CHIP_SOLUTION_NAME;
}

/*****************************************************************************
* �� ��	: bsp_get_firmware_version
* �� ��	: ��ȡ����汾��
*****************************************************************************/
char * bsp_version_get_firmware(void)
{
    u32 ret = VER_OK;

    /*lint -save -e26 -e119*/
    ret=bsp_nvm_read(NV_ID_DRV_NV_DRV_VERSION_REPLACE_I, (u8 *)&nv_sw_ver, sizeof(NV_SW_VER_STRU));
    if(NV_OK != ret){
        ver_print_error("get NV_SW_VERSION_REPLACE failed!\n");
        return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
    }
    else if(0 == nv_sw_ver.nvStatus){
        return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
    }
    /*lint -restore*/

    return (char *)nv_sw_ver.nv_version_info;
}

/*****************************************************************************
* �� ��	: bsp_version_get_release
* �� ��	: ��ȡȫ�汾��
*****************************************************************************/
char * bsp_version_get_release(void)
{
    return PRODUCT_FULL_VERSION_STR;
}



/*****************************************************************************
* �� �� ��  	: bsp_get_version_info
*
* ��������  : Ϊ����ģ���ṩ���ְ汾����Ϣ
*
* ����˵��  : ��
*
*����ֵ : version�Ĺ����ڴ����ݽṹ��ĵ�ַ
*****************************************************************************/
const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
    /*lint -save -e124*/
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
    /*lint -restore*/
}

/*****************************************************************************
* �� ��	: bsp_version_debug
* �� ��	: ���ڵ��Բ鿴�汾�������Ϣ
*****************************************************************************/
int bsp_version_debug(void)
{
    if(huawei_product_info.index == HW_VER_INVALID){
        ver_print_error("huawei_product_info.index = HW_VER_INVALID\n");
        return VER_ERROR;
    }

    ver_print_error("\n\n1 . the element value of nv(0xd115):\n");
    ver_print_error("Hardware index :0x%x\n",huawei_product_info.index);
    ver_print_error("hw_Sub_ver     :0x%x\n",huawei_product_info.hwIdSub);
    ver_print_error("Inner name     :%s\n",huawei_product_info.name);
    ver_print_error("name plus      :%s\n",huawei_product_info.namePlus);
    ver_print_error("HardWare ver   :%s\n",huawei_product_info.hwVer);
    ver_print_error("DLOAD_ID       :%s\n",huawei_product_info.dloadId);
    ver_print_error("Out name       :%s\n",huawei_product_info.productId);

    ver_print_error("\n\n2 . the element value of nv(0xc362):\n");
    ver_print_error("nvStatus       :0x%x\n",nv_sw_ver.nvStatus);
    ver_print_error("nv_version_info:%s\n",nv_sw_ver.nv_version_info);

    ver_print_error("\n\n3 . get from func(bsp_version_get_xxx):\n");
    ver_print_error("HardWare ver   :%s\n",bsp_version_get_hardware());
    ver_print_error("Inner name     :%s\n",bsp_version_get_product_inner_name());
    ver_print_error("Out name       :%s\n",bsp_version_get_product_out_name());
    ver_print_error("Build_time     :%s\n",bsp_version_get_build_date_time());
    ver_print_error("Chip_ver       :%s\n",bsp_version_get_chip());
    ver_print_error("Firmware       :%s\n",bsp_version_get_firmware());
    ver_print_error("Release_ver    :%s\n",bsp_version_get_release());

    ver_print_error("\n\n4 . get from bsp_get_version_info:\n");
    ver_print_error("board_id            :0x%x\n",bsp_get_version_info()->board_id);
    ver_print_error("board_id_udp_masked :0x%x\n",bsp_get_version_info()->board_id_udp_masked);
    ver_print_error("chip_version        :0x%x\n",bsp_get_version_info()->chip_version);
    ver_print_error("chip_type           :0x%x\n",bsp_get_version_info()->chip_type);
    ver_print_error("plat_type           :0x%x  (0:asic a:fpga e:emu)\n",bsp_get_version_info()->plat_type);
    ver_print_error("board_type(for drv) :0x%x  (0:bbit 1:sft 2:asic 3:soc)\n",bsp_get_version_info()->board_type);
    ver_print_error("board_type(for mdrv):0x%x  (0:bbit 1:sft 2:asic)\n",(BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type);
    ver_print_error("bbit_type           :0x%x  (1:dallas 2:722 3:chicago)\n",bsp_get_version_info()->bbit_type);
    ver_print_error("product_type        :0x%x  (0:mbb 1:phone)\n",bsp_get_version_info()->product_type);
    ver_print_error("product_name        :0x%x\n",bsp_get_version_info()->product_name);

    return VER_OK;
}

/*lint -restore*/

