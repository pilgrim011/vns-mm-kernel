
/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  mdrv_version.h
*
*   ��    �� :  huawei
*
*   ��    �� :  modem��versionģ��Ϊ�ϲ��ṩ�Ķ���ӿڼ�����
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
                              2015��10��26�� v2.00  zhaodandan����
*************************************************************************/

#ifndef __MDRV_CCORE_VERSION_H__
#define __MDRV_CCORE_VERSION_H__
#ifdef __cplusplus
extern "C"
{
#endif

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

/*memVersionCtrl�ӿڲ�������*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                1

typedef enum{
	 BOARD_TYPE_BBIT    = 0,
	 BOARD_TYPE_SFT,
	 BOARD_TYPE_ASIC,
	 BOARD_TYPE_MAX
}BOARD_ACTUAL_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     V7R2_CHIP              =5,
     V8R1_PILOT_CHIP        = 0x8,

}BSP_CHIP_TYPE_E;

typedef struct  tagMPRODUCT_INFO_S
{
	unsigned char *  productname;  /*оƬ���� */ /* BSP*/
	unsigned int   productnamelen;
	BSP_CHIP_TYPE_E echiptype;  /* PV500_CHIP V7R1_CHIP? */
	unsigned int  platforminfo ;     /* FPGA ASIC?*/
	BOARD_ACTUAL_TYPE_E eboardatype;   /*BBIT SFT ASIC FOR */
} MPRODUCT_INFO_S;

typedef  struct  tagMSW_VER_INFO_S
{
	unsigned short  ulVVerNO;
	unsigned short  ulRVerNO;
	unsigned short  ulCVerNO;
	unsigned short  ulBVerNO;
	unsigned short  ulSpcNO;
	unsigned short  ulCustomNOv;
	unsigned int  ulProductNo;
	unsigned char  acBuildDate[BUILD_DATE_LEN];
	unsigned char  acBuildTime[BUILD_TIME_LEN];
} MSW_VER_INFO_S;

typedef  struct  tagMHW_VER_INFO_S
{
	int  hwindex;  /* HKADC��⵽��Ӳ��ID��(�弶��*/
	unsigned int  hwidsub;  /* HKADC��⵽���Ӱ汾��*/
	unsigned char *  hwfullver;  /* Ӳ���汾��Ϣ MBBʹ�� */
	unsigned int  hwfullverlen;
	unsigned char *  hwname;  /* �ⲿ��Ʒ����  MBBʹ�� CPE? */
	unsigned int  hwnamelen;
	unsigned char *  hwinname;  /* �ڲ���Ʒ����  MBBʹ��*/
	unsigned int  hwinnamelen;  
} MHW_VER_INFO_S;

typedef struct  tagMODEM_VER_INFO_S
{
	MPRODUCT_INFO_S  stproductinfo;
	MSW_VER_INFO_S  stswverinfo;
	MHW_VER_INFO_S  sthwverinfo;
} MODEM_VER_INFO_S;

typedef enum
{
	VER_BOOTLOAD = 0,
	VER_BOOTROM = 1,
	VER_NV = 2,
	VER_VXWORKS = 3,
	VER_DSP = 4,
	VER_PRODUCT_ID = 5,
	VER_WBBP = 6,
	VER_PS = 7,
	VER_OAM = 8,
	VER_GBBP = 9,
	VER_SOC = 10,
	VER_HARDWARE = 11,
	VER_SOFTWARE = 12,
	VER_MEDIA = 13,
	VER_APP = 14,
	VER_ASIC = 15,
	VER_RF = 16,
	VER_PMU = 17,
	VER_PDM = 18,
	VER_PRODUCT_INNER_ID = 19,
	VER_INFO_NUM = 20
} COMP_TYPE_E;



/*******************************************************************************************************
 �� �� ��: bsp_version_memversion_ctrl
 ��������: ����汾��д�ӿ�
*********************************************************************************************************/
int mdrv_ver_memberctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode);

/*****************************************************************************
 �� �� ��  : mdrv_ver_get_info
 ��������  : ����modem�汾��Ϣ
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void);



#ifdef __cplusplus
}
#endif

#endif
