#include <boot.h>
#include <sys.h>
#include <system.h>
#include <modemid.h>
#include <hi_version.h>
#include <bsp_version.h>

static u32 g_is_verison_ddr_init = 0;

/*lint -save -e838 -e835 -e716 -e717 -e774*/

/*****************************************************************************
* �� �� ��  	: bsp_version_get_hw_version_from_ap
*
* ��������  : ��ȡӲ���汾��
*
* ����˵��  : ��
*
*����ֵ : Ӳ���汾��
*****************************************************************************/
static u32 bsp_version_get_hw_version_from_ap(void)
{
#ifdef CONFIG_VERSION_STUB
    return HW_VERSION_STUB;
#else
    u32 productid = 0;
    struct modemid_operators *modemid_ops = get_operators(MODEMID_MODULE_NAME_STR);
    if(!modemid_ops){
        cprintf("bsp_version_get_hw_version_from_ap failed, can not get modemid_ops!\n");
        return HW_VER_INVALID;
    }
    productid = modemid_ops->get_productid();
    cprintf("[version]get modemid_ops succ! productid:0x%x!\n",productid);
    return productid;
#endif
}

/*****************************************************************************
* �� �� ��  	: bsp_version_get_board_type
*
* ��������  : ��ȡboard type
*
* ����˵��  : ��
*
*����ֵ : BSP_BOARD_ACTUAL_TYPE_E: SOC/BBIT/SFT/ASIC
*****************************************************************************/
static VERSION_BOARD_TYPE_E bsp_version_get_board_type(void)
{
	switch(bsp_get_version_info()->plat_type){
		case PLAT_ASIC:
			#ifdef PXXX_BOARD_TYPE_ONLY_SOC
				return BSP_BOARD_TYPE_SOC;
			#elif defined(PXXX_BOARD_TYPE_BBIT)
			    return BSP_BOARD_TYPE_BBIT;
			#else
				return BSP_BOARD_TYPE_ASIC;
			#endif
		case PLAT_FPGA:
			return BSP_BOARD_TYPE_SFT;
             case PLAT_EMU:
			return BSP_BOARD_TYPE_ASIC;
		default:
			return BSP_BOARD_TYPE_MAX;
	}
}

/*****************************************************************************
* �� �� ��  	: bsp_version_get_product_type
*
* ��������  : ��ȡproduct type
*
* ����˵��  : ��
*
*����ֵ : VERSION_PRODUCT_TYPE_E: MBB/PHONE
*
*****************************************************************************/
static VERSION_PRODUCT_TYPE_E bsp_version_get_product_type(void)
{
    VERSION_PRODUCT_TYPE_E product_type = PRODUCT_ERROR;
    switch(bsp_get_version_info()->chip_type){
        case CHIP_K3V3:
        case CHIP_K3V5:
        case CHIP_K3V6:
        case CHIP_V8R5:
            product_type = PRODUCT_PHONE;
            break;
        case CHIP_P531:
        case CHIP_P532:
        case CHIP_V711:
        case CHIP_V722:
        case CHIP_V750:
            product_type = PRODUCT_MBB;
            break;
        default:
            product_type = PRODUCT_ERROR;
            break;
    }
    return product_type;
}

/*****************************************************************************
* �� �� ��  	: bsp_version_get_product_name
*
* ��������  : ��ȡproduct name
*
* ����˵��  : ��
*
*����ֵ : VERSION_PRODUCT_NAME_E: 0x3650/0x3660/0x6250/0x6932/0x6950
*
*****************************************************************************/
static VERSION_PRODUCT_NAME_E bsp_version_get_product_name(void)
{
    VERSION_PRODUCT_NAME_E product_name = PRODUCT_NOT_SUPPORT;
    switch(bsp_get_version_info()->chip_type){
        case CHIP_K3V5:
            product_name = PRODUCT_AUSTIN;
            break;
        case CHIP_K3V6:
            product_name = PRODUCT_CHICAGO;
            break;
        case CHIP_V8R5:
            product_name = PRODUCT_DALLAS;
            break;
        case CHIP_V722:
            product_name = PRODUCT_722;
            break;
        case CHIP_V750:
            product_name = PRODUCT_750;
            break;
        case CHIP_P532:
            switch(bsp_get_version_info()->bbit_type){
                case DALLAS_BBIT:
                    product_name = PRODUCT_DALLAS;
                    break;
                case V722_BBIT:
                    product_name = PRODUCT_722;
                    break;
                case CHICAGO_BBIT:
                    product_name = PRODUCT_CHICAGO;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return product_name;
}

/*****************************************************************************
* �� �� ��  	: bsp_version_ddr_init
*
* ��������  : version�Ĺ����ڴ����ݳ�ʼ��
*
* ����˵��  : ��
*
*����ֵ : ��
*****************************************************************************/
void bsp_version_ddr_init(void)
{
    u32 chip_version = 0;
    u32 hw_version = HW_VER_INVALID;
    BSP_VERSION_INFO_S *p_version_info = (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);

    if(sizeof(BSP_VERSION_INFO_S) > SHM_SIZE_VERSION)
    {
        cprintf("bsp_version_ddr_init fail: sizeof(BSP_VERSION_INFO_S) > SHM_SIZE_VERSION!\n");
        return;
    }
    memset(p_version_info, 0, (u32)sizeof(BSP_VERSION_INFO_S));
    g_is_verison_ddr_init = 1;

    //оƬ�汾��
    chip_version = (u32)readl((unsigned)CHIP_VER_ADDR);
    p_version_info->chip_version = chip_version;
    p_version_info->chip_type = (VERSION_CHIP_TYPE_E)((chip_version & CHIP_TYPE_MASK) >> 16);
    p_version_info->plat_type = (VERSION_PLAT_TYPE_E)((chip_version & PLAT_TYPE_MASK) >> 12);
    //K3 plat type definition differ from balong, delte this after chicago
    //(1) for asic, plat type == 0, do nothing
    //(2) for fpga, plat type == 1, change to  a
    //(2) for emu, plat type == 2, change to  e
    if(0x1 == p_version_info->plat_type)
        p_version_info->plat_type = 0xa;
    else if(0x2 == p_version_info->plat_type)
        p_version_info->plat_type = 0xe;

    //Ӳ���汾��
    hw_version = bsp_version_get_hw_version_from_ap();
    if(HW_VER_INVALID==hw_version)
        cprintf("bsp_version_get_hw_version failed!hw_version:0x%x.\n",hw_version);
    p_version_info->board_id = hw_version;
    p_version_info->board_id_udp_masked = hw_version;

    //�����汾��
    p_version_info->board_type = bsp_version_get_board_type();
    p_version_info->product_type = bsp_version_get_product_type();
    p_version_info->product_name = bsp_version_get_product_name();

    return;
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
    if(!g_is_verison_ddr_init)
    {
        //avoid accessing the ddr addr before init
        /* coverity[loop_bottom] */
        while(1){}
    }
    return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}

/*****************************************************************************
* �� �� ��  	: bsp_version_get_chip_type
*
* ��������  : ��ȡchip type
*
* ����˵��  : ��
*
*����ֵ : VERSION_CHIP_TYPE_E: CHIP_V750/CHIP_V722��
*
*ע��:�ýӿڽ��ṩ��bsp_disable_non_on_clk  ����!!!
*****************************************************************************/
VERSION_CHIP_TYPE_E bsp_version_get_chip_type(void)
{
    u32 chip_version = (u32)readl((unsigned)CHIP_VER_ADDR);
    VERSION_CHIP_TYPE_E chip_type = (VERSION_CHIP_TYPE_E)((chip_version & CHIP_TYPE_MASK) >> 16);
    return chip_type;
}

/*lint -restore*/



