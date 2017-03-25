

#ifndef __MDDRC_SEC_H__
#define __MDDRC_SEC_H__

#include <osl_types.h>
/* 722 ��ʼ���Ӱ�ȫ���� 
  ����Ժ�ƽ̨���첻�����ø�ͷ�ļ� 
  ����Ժ�ƽ̨�нϴ���죬���ƽ̨��������ͷ�ļ� */


/*"��ǰ����Ĵ�С��
6'd15�� 64KB��
6'd16��128KB����ʱ.bits.rgn_base_addr[   0]��������Ϊ�㣻
6'd17��256KB����ʱ.bits.rgn_base_addr[ 1:0]��������Ϊ�㣻
6'd18��512KB����ʱ.bits.rgn_base_addr[ 2:0]��������Ϊ�㣻
6'd19��  1MB����ʱ.bits.rgn_base_addr[ 3:0]��������Ϊ�㣻
6'd20��  2MB����ʱ.bits.rgn_base_addr[ 4:0]��������Ϊ�㣻
6'd21��  4MB����ʱ.bits.rgn_base_addr[ 5:0]��������Ϊ�㣻
6'd22��  8MB����ʱ.bits.rgn_base_addr[ 6:0]��������Ϊ�㣻
6'd23�� 16MB����ʱ.bits.rgn_base_addr[ 7:0]��������Ϊ�㣻
6'd24�� 32MB����ʱ.bits.rgn_base_addr[ 8:0]��������Ϊ�㣻
6'd25�� 64MB����ʱ.bits.rgn_base_addr[ 9:0]��������Ϊ�㣻
6'd26��128MB����ʱ.bits.rgn_base_addr[10:0]��������Ϊ�㣻
6'd27��256MB����ʱ.bits.rgn_base_addr[11:0]��������Ϊ�㣻
6'd28��512MB����ʱ.bits.rgn_base_addr[12:0]��������Ϊ�㣻
6'd29��  1GB����ʱ.bits.rgn_base_addr[13:0]��������Ϊ�㣻
6'd30��  2GB����ʱ.bits.rgn_base_addr[14:0]��������Ϊ�㣻
6'd31��  4GB����ʱ.bits.rgn_base_addr[15:0]��������Ϊ�㣻
6'd32��  8GB����ʱ.bits.rgn_base_addr[16:0]��������Ϊ�㣻
6'd33�� 16GB����ʱ.bits.rgn_base_addr[17:0]��������Ϊ�㣻
6'd34�� 32GB����ʱ.bits.rgn_base_addr[18:0]��������Ϊ�㣻
6'd35�� 64GB����ʱ.bits.rgn_base_addr[19:0]��������Ϊ�㣻
6'd36��128GB����ʱ.bits.rgn_base_addr[20:0]��������Ϊ�㣻
6'd37��256GB����ʱ.bits.rgn_base_addr[21:0]��������Ϊ�㣻
6'd38��512GB����ʱ.bits.rgn_base_addr[22:0]��������Ϊ�㣻
6'd39��1TB��  ��ʱ.bits.rgn_base_addr[23:0]��������Ϊ�㡣
ע�⣺
1.rgn0�������ã�Ĭ�ϸ���������ַ�ռ䣻
2.Ϊÿ���������õ������С��
�ۼ�����������ʼ��ַ��
���������ܵĵ�ַ�ռ��С��" */
#define DDR_RGN_SIZE_64KB     (15)
#define DDR_RGN_SIZE_128KB    (16)
#define DDR_RGN_SIZE_256KB    (17)
#define DDR_RGN_SIZE_512KB    (18)
#define DDR_RGN_SIZE_1MB      (19)
#define DDR_RGN_SIZE_2MB      (20)
#define DDR_RGN_SIZE_4MB      (21)
#define DDR_RGN_SIZE_8MB      (22)
#define DDR_RGN_SIZE_16MB     (23)
#define DDR_RGN_SIZE_32MB     (24)
#define DDR_RGN_SIZE_64MB     (25)
#define DDR_RGN_SIZE_128MB    (26)
#define DDR_RGN_SIZE_256MB    (27)
#define DDR_RGN_SIZE_512MB    (28)
#define DDR_RGN_SIZE_1GB      (29)

/* ��ǰ����İ�ȫȨ�����ԡ�
sp[3]����ȫ�����ԣ�
sp[2]����ȫд���ԣ�
sp[1]���ǰ�ȫ�����ԣ�
sp[0]���ǰ�ȫд���ԣ�
sp[n]=0����ֹ���ʣ�
sp[n]=1��������ʡ�*/ 
#define __DDR_SEC_R__    	(0x1<<3)
#define __DDR_SEC_W__    	(0x1<<2)
#define __DDR_UNSEC_R__    	(0x1<<1)
#define __DDR_UNSEC_W__    	(0x1<<0)
#define DDR_RGN_ATTR_SP_SEC		(__DDR_SEC_R__|__DDR_SEC_W__)
#define DDR_RGN_ATTR_SP_UNSEC	(__DDR_SEC_R__|__DDR_SEC_W__|__DDR_UNSEC_R__|__DDR_UNSEC_W__)


typedef union
{
	struct
	{
		u32 rgn_base_addr	: 24; 	/* 23:0 */
		u32 rgn_size		: 6;	/* 29:24 */
		u32 reserved1 		: 1;	/* 30:30 */
		u32 reg_en 			: 1;	/* 31:31 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_MAP;


typedef union
{
	struct
	{
		u32 spp				: 4;   /* 3:0 */
		u32 security_inv	: 1;   /* 4:4 */
		u32 reserved1 		: 3;   /* 7:5 */
		u32 mid_en 			: 1;   /* 8:8 */
		u32 mid_inv			: 1;   /* 9:9 */
		u32 reserved2 		: 6;   /* 15:10 */
		u32 subrgn_disable	: 16;  /* 31:16 */
	}bits;
	u32 reg_val;
}DDR_REG_SEC_RGN_ATTRIB;

#define DDR_RGN_MAP_BASE_ADDR(addr) ((addr)>>8)

#define DDR_SEC_BASE_ADDR	(0x90040000)
#define DDR_SEC_RGN_MAP_ADDR(ports, regions) 		(0x500+0x200*ports+0x10*regions)
#define DDR_SEC_RGN_ATTRIB_ADDR(ports, regions) 	(0x504+0x200*ports+0x10*regions)
#define DDR_SEC_MID_WR_ADDR(ports, regions) 		(0x508+0x200*ports+0x10*regions)
#define DDR_SEC_MID_RD_ADDR(ports, regions) 		(0x50c+0x200*ports+0x10*regions)


#define DDR_RGN_NUMBER	(16)

#define REGION_CONFIG_COMM(region,base_addr,size,ssp,sub_rgn)	\
do {	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_base_addr 	= (base_addr >> 16);	\
	ddr_reg_sec_rgn_maps[region].bits.rgn_size 			= size;			\
	ddr_reg_sec_rgn_maps[region].bits.reg_en			= 1;			\
	ddr_reg_sec_rgn_attribs[region].bits.spp 			= ssp;			\
	ddr_reg_sec_rgn_attribs[region].bits.subrgn_disable	= sub_rgn;		\
}while (0)
    
#define REGION_CONFIG_REG(region,port)	\
do {    \
    writel(ddr_reg_sec_rgn_maps[region].reg_val   , DDR_SEC_BASE_ADDR + DDR_SEC_RGN_MAP_ADDR(port,region));\
    writel(ddr_reg_sec_rgn_attribs[region].reg_val, DDR_SEC_BASE_ADDR + DDR_SEC_RGN_ATTRIB_ADDR(port,region));\
}while (0)


#ifdef CONFIG_DDR_SECURITY
void mddrc_sec_cfg(void);
#else
static inline void mddrc_sec_cfg(void){}
#endif


#endif /* __MDDRC_SEC_H__ */
