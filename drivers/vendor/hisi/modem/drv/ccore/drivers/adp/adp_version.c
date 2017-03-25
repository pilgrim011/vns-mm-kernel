
/*lint --e{537}*/

#include <string.h>
#include "securec.h"
#include <mdrv_misc_comm.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include "bsp_version.h"
#include "mdrv_version.h"

VERSIONINFO                 verCheckInfo[ VER_INFO_NUM ];
MODEM_VER_INFO_S     ver_info;
extern PRODUCT_INFO_NV_STRU huawei_product_info;

/**********************************************************************************************************************************
 �� �� ��: bsp_version_memversion_ctrl
 ��������: ����汾��д�ӿڡ�
 �������: (1)pcData����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��ַ��
                                           ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ�ĵ�ַ��
                        (2)ucLength����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��С��
                                              ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ���ַ�����������'\0'��
                        (3)ucType���汾��ϢID
                        (4)ucMode��0����ȡָ��ID������汾��Ϣ��1��д��ָ��ID������汾��Ϣ��
 �� �� ֵ  : 0:  �����ɹ��� -1������ʧ�ܡ�
***********************************************************************************************************************************/
/*lint -save -e958*/
static int bsp_version_memversion_ctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode)
/*lint -save restore*/
{
    /*lint -save -e958*/
    u8 *lpv_VerTmp;
    u8 liv_Index;
    u8 ucLen;
    /*lint -save restore*/

    if(ucType >= VER_INFO_NUM)
    {
        ver_print_error("Version Info Type Error\n");
        return VER_ERROR;
    }

    if (ucMode > VERIONWRITEMODE)
    {
        ver_print_error("Control Mode Error\n");
        return VER_ERROR;
    }

    ucLen = ucLength;
    if((VERIONWRITEMODE == ucMode)&&(ucLen > VER_MAX_LENGTH))
    {
        ver_print_error("Version Info Length Error\n");
        ucLen = VER_MAX_LENGTH;
    }

    if((VERIONWRITEMODE == ucMode)&&(0 == ucLen))
    {
        /*lint -save -e18 -e718 -e746*/
        ucLen = (u8)(strlen((const char *)pcData)+1);
        /*lint -restore*/
        if(ucLen >= VER_MAX_LENGTH)
            ucLen = VER_MAX_LENGTH;
    }

    if(NULL == pcData)
    {
        ver_print_error("Data Buffer Pointer Null\n");
        return VER_ERROR;
    }

    lpv_VerTmp = (u8 *)verCheckInfo[ucType].CompVer;
    for(liv_Index = 0; liv_Index < ucLen; liv_Index++)
    {
        if(ucMode)
            *(lpv_VerTmp + liv_Index) = *((u8 *)pcData + liv_Index);
        else
            *((u8 *)pcData + liv_Index) = *(lpv_VerTmp + liv_Index);
    }

    return  VER_OK;
}

/********************************************************************************************************************
 �� �� ��  : bsp_version_init
 ��������  :�汾��ģ���ʼ��
********************************************************************************************************************/
void bsp_version_init(void)
{
    u32 i;
    int ret = 0;

    (void)memset_s((void *)verCheckInfo, sizeof (verCheckInfo), 0, sizeof (verCheckInfo));
    for( i = 0; i < VER_INFO_NUM; i++)
        verCheckInfo[i].CompId = (u8)i;

    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_FULL_VERSION_STR, 0 , VER_VXWORKS,(unsigned char)VERIONWRITEMODE);
    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_FULL_VERSION_STR ,0 , VER_PRODUCT_ID,(unsigned char)VERIONWRITEMODE);
    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_DLOAD_SOFTWARE_VER, 0, VER_SOFTWARE,(unsigned char)VERIONWRITEMODE);
    if(NULL != bsp_version_get_hardware())
        ret |= bsp_version_memversion_ctrl((signed char *)bsp_version_get_hardware(), 0, VER_HARDWARE,(unsigned char)VERIONWRITEMODE);

    if (VER_ERROR == ret)
        ver_print_error("bsp_version_memversion_ctrl return Error\n");

}



/*****************************************************************************
*                                                                                                                               *
*            ���½ӿ�Ϊmdrv�ӿ�                                                                       *
*                                                                                                                               *
******************************************************************************/



/*****************************************************************************
 �� �� ��  : mdrv_ver_memberctrl
 ��������  :  ����汾��д�ӿڣ����ϲ��ṩ
****************************************************************************/
int mdrv_ver_memberctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode)
{
	return bsp_version_memversion_ctrl(pcData,ucLength,ucType,ucMode);
}

/*****************************************************************************
 �� �� ��  : mdrv_ver_get_info
 ��������  : ����modem�汾��Ϣ�����ϲ��ṩ
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void)
{
	return &ver_info;
}

/*****************************************************************************
 �� �� ��  : mdrv_ver_init
 ��������  :  ver_info��ʼ��
****************************************************************************/
void mdrv_ver_init(void)
{
    (void)memset_s(&ver_info, sizeof(MODEM_VER_INFO_S), 0x0, sizeof(MODEM_VER_INFO_S));

    ver_info.stproductinfo.eboardatype = (BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type;
    ver_info.stproductinfo.echiptype = V7R2_CHIP;
    ver_info.stproductinfo.productname = (unsigned char*)bsp_version_get_product_out_name();
    ver_info.stproductinfo.productnamelen = VER_MAX_LENGTH;

    ver_info.sthwverinfo.hwfullver = (unsigned char*)bsp_version_get_hardware();
    ver_info.sthwverinfo.hwfullverlen = VER_MAX_LENGTH;
    ver_info.sthwverinfo.hwidsub = huawei_product_info.hwIdSub;
    ver_info.sthwverinfo.hwindex = (int)(bsp_get_version_info()->board_id);
    ver_info.sthwverinfo.hwinname = (unsigned char*)bsp_version_get_product_inner_name();
    ver_info.sthwverinfo.hwinnamelen = VER_MAX_LENGTH;
    ver_info.sthwverinfo.hwname = (unsigned char*)bsp_version_get_product_out_name();
    ver_info.sthwverinfo.hwnamelen = VER_MAX_LENGTH;

    (void)memcpy_s(ver_info.stswverinfo.acBuildDate, BUILD_DATE_LEN, __DATE__, sizeof(__DATE__));
    (void)memcpy_s(ver_info.stswverinfo.acBuildTime, BUILD_TIME_LEN, __TIME__, sizeof(__TIME__));/*[false alarm]*/

    return ;
}

/*lint -save -e64 -e437 -e233 -e713*/
/*****************************************************************************
 �� �� ��  : mdrv_misc_support_check
 ��������  : ��ѯģ���Ƿ�֧�֣����ϲ��ṩ
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E mdrv_misc_support_check (BSP_MODULE_TYPE_E module_type)
{
    s32 ret;
    bool bSupport = BSP_MODULE_SUPPORT;
    DRV_MODULE_SUPPORT_STRU   stSupportNv;

    if(module_type >= BSP_MODULE_TYPE_BOTTOM)
    {
        return BSP_MODULE_UNSUPPORT;
    }

    ret = bsp_nvm_read(NV_ID_DRV_MODULE_SUPPORT, (u8*)&stSupportNv, sizeof(DRV_MODULE_SUPPORT_STRU));
    if(NV_OK != ret)
	{
		/*lint --e{18,718,746}*/
		(void)memset_s((void *)&stSupportNv, (u32)sizeof(DRV_MODULE_SUPPORT_STRU), 0xFF,(u32)sizeof(DRV_MODULE_SUPPORT_STRU));

		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HWADP,
			"bsp_nvm_read error, ret %#x, item %#x\n, set to default %#x",
			ret, NV_ID_DRV_MODULE_SUPPORT, stSupportNv);
	}

    switch(module_type)
    {
        case BSP_MODULE_TYPE_SD:
            bSupport = stSupportNv.sdcard;
            break;

        case BSP_MODULE_TYPE_CHARGE:
            bSupport = stSupportNv.charge;
            break;

        case BSP_MODULE_TYPE_WIFI:
            bSupport = stSupportNv.wifi;
            break;

        case BSP_MODULE_TYPE_OLED:
            bSupport = stSupportNv.oled;
            break;

        case BSP_MODULE_TYPE_HIFI:
			bSupport = stSupportNv.hifi;
            break;

        case BSP_MODULE_TYPE_POWER_ON_OFF:
			bSupport = stSupportNv.onoff;
            break;

        case BSP_MODULE_TYPE_HSIC:
			bSupport = stSupportNv.hsic;
            break;

        case BSP_MODULE_TYPE_LOCALFLASH:
			bSupport = stSupportNv.localflash;
            break;

		default:
			bSupport = 0;
    }

    if(bSupport)
        return BSP_MODULE_SUPPORT;
    else
        return BSP_MODULE_UNSUPPORT;
}/* [false alarm]:�� */
/*lint -restore +e64 +e437 +e233 +e713*/



