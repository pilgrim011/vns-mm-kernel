
#include "bsp_version.h"

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
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}

