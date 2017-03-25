/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_ctf_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-07-15 15:55:00
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��15��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_CTF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CTF_INTERFACE_H__
#define __SOC_CTF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* �Ĵ���˵������ѹɨ��Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_VSCAN_UNION */
#define SOC_CTF_VSCAN_ADDR(base)                      ((base) + (0x000))

/* �Ĵ���˵������ʶ�Ĵ���0��
   λ����UNION�ṹ:  SOC_CTF_PTN0_UNION */
#define SOC_CTF_PTN0_ADDR(base)                       ((base) + (0x010))

/* �Ĵ���˵������ʶ�Ĵ���1��
   λ����UNION�ṹ:  SOC_CTF_PTN1_UNION */
#define SOC_CTF_PTN1_ADDR(base)                       ((base) + (0x014))

/* �Ĵ���˵������ʶ�Ĵ���2��
   λ����UNION�ṹ:  SOC_CTF_PTN2_UNION */
#define SOC_CTF_PTN2_ADDR(base)                       ((base) + (0x018))

/* �Ĵ���˵������ʶ�Ĵ���3��
   λ����UNION�ṹ:  SOC_CTF_PTN3_UNION */
#define SOC_CTF_PTN3_ADDR(base)                       ((base) + (0x01C))

/* �Ĵ���˵������ʶ�Ĵ���4��
   λ����UNION�ṹ:  SOC_CTF_PTN4_UNION */
#define SOC_CTF_PTN4_ADDR(base)                       ((base) + (0x020))

/* �Ĵ���˵������ʶ�Ĵ���5��
   λ����UNION�ṹ:  SOC_CTF_PTN5_UNION */
#define SOC_CTF_PTN5_ADDR(base)                       ((base) + (0x024))

/* �Ĵ���˵������ʶ�Ĵ���6��
   λ����UNION�ṹ:  SOC_CTF_PTN6_UNION */
#define SOC_CTF_PTN6_ADDR(base)                       ((base) + (0x028))

/* �Ĵ���˵������ʶ�Ĵ���7��
   λ����UNION�ṹ:  SOC_CTF_PTN7_UNION */
#define SOC_CTF_PTN7_ADDR(base)                       ((base) + (0x02C))

/* �Ĵ���˵����SGI�ж����μĴ�����
   λ����UNION�ṹ:  SOC_CTF_SGIMASK_UNION */
#define SOC_CTF_SGIMASK_ADDR(base)                    ((base) + (0x040))

/* �Ĵ���˵����PPI�ж����μĴ�����
   λ����UNION�ṹ:  SOC_CTF_PPIMASK_UNION */
#define SOC_CTF_PPIMASK_ADDR(base)                    ((base) + (0x044))

/* �Ĵ���˵�����˼乲���ж����μĴ�����
   λ����UNION�ṹ:  SOC_CTF_SPIMASK_UNION */
#define SOC_CTF_SPIMASK_ADDR(base)                    ((base) + (0x048))

/* �Ĵ���˵����SGI�жϷ���Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SGIGROUP_UNION */
#define SOC_CTF_SGIGROUP_ADDR(base)                   ((base) + (0x04C))

/* �Ĵ���˵����PPI�жϷ���Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_PPIGROUP_UNION */
#define SOC_CTF_PPIGROUP_ADDR(base)                   ((base) + (0x050))

/* �Ĵ���˵�����˼乲���жϷ���Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SPIGROUP_UNION */
#define SOC_CTF_SPIGROUP_ADDR(base)                   ((base) + (0x054))

/* �Ĵ���˵����APBд���ͻָʾ�Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_APB_WR_ERR_UNION */
#define SOC_CTF_APB_WR_ERR_ADDR(base)                 ((base) + (0x058))

/* �Ĵ���˵�����˼乲���ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CTF_SPI_INT_EN_UNION */
#define SOC_CTF_SPI_INT_EN_ADDR(base)                 ((base) + (0x060))

/* �Ĵ���˵�����˼乲���ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SPI_INT_CLR_UNION */
#define SOC_CTF_SPI_INT_CLR_ADDR(base)                ((base) + (0x064))

/* �Ĵ���˵�����˼乲���ж�ԭʼ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SPI_RAWSTAT_UNION */
#define SOC_CTF_SPI_RAWSTAT_ADDR(base)                ((base) + (0x068))

/* �Ĵ���˵�����˼乲���ж�Ŀ��Ĵ���0��
   λ����UNION�ṹ:  SOC_CTF_SPITARG0_UNION */
#define SOC_CTF_SPITARG0_ADDR(base)                   ((base) + (0x070))

/* �Ĵ���˵�����˼乲���ж�Ŀ��Ĵ���1��
   λ����UNION�ṹ:  SOC_CTF_SPITARG1_UNION */
#define SOC_CTF_SPITARG1_ADDR(base)                   ((base) + (0x0074))

/* �Ĵ���˵�����˼乲���ж�Ŀ��Ĵ���2��
   λ����UNION�ṹ:  SOC_CTF_SPITARG2_UNION */
#define SOC_CTF_SPITARG2_ADDR(base)                   ((base) + (0x078))

/* �Ĵ���˵�����˼乲���ж�Ŀ��Ĵ���3��
   λ����UNION�ṹ:  SOC_CTF_SPITARG3_UNION */
#define SOC_CTF_SPITARG3_ADDR(base)                   ((base) + (0x07C))

/* �Ĵ���˵����SGI�жϲ����Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SGIG_UNION */
#define SOC_CTF_SGIG_ADDR(base, N)                    ((base) + (0x000 + 0x400 + 0x80*(N)))

/* �Ĵ���˵����SGIPending״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_CTF_SGIPSTAT0_UNION */
#define SOC_CTF_SGIPSTAT0_ADDR(base, N)               ((base) + (0x004 + 0x400 + 0x80*(N)))

/* �Ĵ���˵����SGIPending״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CTF_SGIPSTAT1_UNION */
#define SOC_CTF_SGIPSTAT1_ADDR(base, N)               ((base) + (0x008 + 0x400 + 0x80*(N)))

/* �Ĵ���˵����PPIPending״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_PPIPSTAT_UNION */
#define SOC_CTF_PPIPSTAT_ADDR(base, N)                ((base) + (0x00C + 0x400 + 0x80*(N)))

/* �Ĵ���˵�����˼乲���ж�Pending״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_SPIPSTAT_UNION */
#define SOC_CTF_SPIPSTAT_ADDR(base, N)                ((base) + (0x010 + 0x400 + 0x80*(N)))

/* �Ĵ���˵�����ж�ȷ�ϼĴ�����
   λ����UNION�ṹ:  SOC_CTF_IAR_UNION */
#define SOC_CTF_IAR_ADDR(base, N)                     ((base) + (0x040 + 0x400 + 0x80*(N)))

/* �Ĵ���˵�����жϽ����Ĵ�����
   λ����UNION�ṹ:  SOC_CTF_EOIR_UNION */
#define SOC_CTF_EOIR_ADDR(base, N)                    ((base) + (0x044 + 0x400 + 0x80*(N)))

/* �Ĵ���˵�����ж��źżĴ�����
   λ����UNION�ṹ:  SOC_CTF_OUTSTAT_UNION */
#define SOC_CTF_OUTSTAT_ADDR(base, N)                 ((base) + (0x048 + 0x400 + 0x80*(N)))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CTF_VSCAN_UNION
 �ṹ˵��  : VSCAN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ѹɨ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctf_vscan_en : 1;  /* bit[0]   : ������APB_MCU�ӿڷ��ʣ�������APB_CPU�ӿڷ��ʡ�ָʾ��ǰACPU�Ƿ��ڵ�ѹɨ��ģʽ����λֵΪ0�� 0���ǵ�ѹɨ��ģʽ�� 1����ѹɨ��ģʽ�� */
        unsigned int  reserved     : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_CTF_VSCAN_UNION;
#endif
#define SOC_CTF_VSCAN_ctf_vscan_en_START  (0)
#define SOC_CTF_VSCAN_ctf_vscan_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN0_UNION
 �ṹ˵��  : PTN0 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten0 : 32; /* bit[0-31]: ��Ӧ��Core����ɲ��Դ����ָ��patternд�뵽��Ӧ�ı�ʶ�Ĵ������Թ�LPM3��LP_PERI_APB����APB�ӿڶ�ȡCTF�ڲ��ļĴ���ֵ���ж�ACPU�Ƿ��ڵ�ǰ��ѹ����ȷִ�в��Դ��롣 */
    } reg;
} SOC_CTF_PTN0_UNION;
#endif
#define SOC_CTF_PTN0_patten0_START  (0)
#define SOC_CTF_PTN0_patten0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN1_UNION
 �ṹ˵��  : PTN1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN1_UNION;
#endif
#define SOC_CTF_PTN1_patten1_START  (0)
#define SOC_CTF_PTN1_patten1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN2_UNION
 �ṹ˵��  : PTN2 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN2_UNION;
#endif
#define SOC_CTF_PTN2_patten2_START  (0)
#define SOC_CTF_PTN2_patten2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN3_UNION
 �ṹ˵��  : PTN3 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN3_UNION;
#endif
#define SOC_CTF_PTN3_patten3_START  (0)
#define SOC_CTF_PTN3_patten3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN4_UNION
 �ṹ˵��  : PTN4 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten4 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN4_UNION;
#endif
#define SOC_CTF_PTN4_patten4_START  (0)
#define SOC_CTF_PTN4_patten4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN5_UNION
 �ṹ˵��  : PTN5 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten5 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN5_UNION;
#endif
#define SOC_CTF_PTN5_patten5_START  (0)
#define SOC_CTF_PTN5_patten5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN6_UNION
 �ṹ˵��  : PTN6 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten6 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN6_UNION;
#endif
#define SOC_CTF_PTN6_patten6_START  (0)
#define SOC_CTF_PTN6_patten6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PTN7_UNION
 �ṹ˵��  : PTN7 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʶ�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patten7 : 32; /* bit[0-31]:  */
    } reg;
} SOC_CTF_PTN7_UNION;
#endif
#define SOC_CTF_PTN7_patten7_START  (0)
#define SOC_CTF_PTN7_patten7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SGIMASK_UNION
 �ṹ˵��  : SGIMASK �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgimask  : 8;  /* bit[0-7] : Each bit corresponds to SGI INTID 7~0.Active low. 0: mask��mask��Ч��; 1: not mask��mask��Ч��. */
        unsigned int  reserved : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_CTF_SGIMASK_UNION;
#endif
#define SOC_CTF_SGIMASK_sgimask_START   (0)
#define SOC_CTF_SGIMASK_sgimask_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PPIMASK_UNION
 �ṹ˵��  : PPIMASK �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPI�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppimask  : 2;  /* bit[29-30]: Each bit corresponds to PPI INTID 30~29 0: mask��mask��Ч��; 
                                                    1: not mask��mask��Ч��. */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIMASK_UNION;
#endif
#define SOC_CTF_PPIMASK_ppimask_START   (29)
#define SOC_CTF_PPIMASK_ppimask_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPIMASK_UNION
 �ṹ˵��  : SPIMASK �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spimask  : 16; /* bit[0-15] : Each bit corresponds to SPI INTID 47~32 */
        unsigned int  reserved : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIMASK_UNION;
#endif
#define SOC_CTF_SPIMASK_spimask_START   (0)
#define SOC_CTF_SPIMASK_spimask_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SGIGROUP_UNION
 �ṹ˵��  : SGIGROUP �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI�жϷ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgigroup : 8;  /* bit[0-7] : Each bit corresponds to SGI INTID 7~0; 
                                                   0���԰�ȫ�ж�FIQ����ʽ 1���Էǰ�ȫ�ж�IRQ����ʽ�͸���Ӧ��core interface�� */
        unsigned int  reserved : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_CTF_SGIGROUP_UNION;
#endif
#define SOC_CTF_SGIGROUP_sgigroup_START  (0)
#define SOC_CTF_SGIGROUP_sgigroup_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PPIGROUP_UNION
 �ṹ˵��  : PPIGROUP �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPI�жϷ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppigroup : 2;  /* bit[29-30]: Each bit corresponds to PPI INTID 30~29; 0���԰�ȫ�ж�FIQ����ʽ 1���Էǰ�ȫ�ж�IRQ����ʽ�͸���Ӧ��core interface�� */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIGROUP_UNION;
#endif
#define SOC_CTF_PPIGROUP_ppigroup_START  (29)
#define SOC_CTF_PPIGROUP_ppigroup_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPIGROUP_UNION
 �ṹ˵��  : SPIGROUP �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���жϷ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spigroup : 16; /* bit[0-15] : Each bit corresponds to SPI INTID 47~32; 0���԰�ȫ�ж�FIQ����ʽ 1���Էǰ�ȫ�ж�IRQ����ʽ�͸���Ӧ��core interface�� */
        unsigned int  reserved : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIGROUP_UNION;
#endif
#define SOC_CTF_SPIGROUP_spigroup_START  (0)
#define SOC_CTF_SPIGROUP_spigroup_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_APB_WR_ERR_UNION
 �ṹ˵��  : APB_WR_ERR �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: APBд���ͻָʾ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_wr_err : 1;  /* bit[0]   : APB_MCU��APB_CPUͬʱд��ͬһ��ַ��д������ͻָʾ�����塣 0: �޳�ͻ��
                                                     1���г�ͻ */
        unsigned int  reserved   : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_CTF_APB_WR_ERR_UNION;
#endif
#define SOC_CTF_APB_WR_ERR_apb_wr_err_START  (0)
#define SOC_CTF_APB_WR_ERR_apb_wr_err_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPI_INT_EN_UNION
 �ṹ˵��  : SPI_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_int_en : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_en[15:0] corresponds to SPI INTID 47~32. 0����Ӧ��SPI INTID�ж�pending״̬���䣻1����Ӧ��SPI INTID�ж�pending״̬ʹ�ܡ�  */
        unsigned int  reserved            : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_INT_EN_UNION;
#endif
#define SOC_CTF_SPI_INT_EN_mcu2acpu_raw_int_en_START  (0)
#define SOC_CTF_SPI_INT_EN_mcu2acpu_raw_int_en_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPI_INT_CLR_UNION
 �ṹ˵��  : SPI_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_int_clr : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_clr[15:0] corresponds to SPI INTID 47~32. 0���������Ӧ��SPI INTID�жϣ� 1�������Ӧ��SPI INTID�жϡ� */
        unsigned int  reserved             : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_INT_CLR_UNION;
#endif
#define SOC_CTF_SPI_INT_CLR_mcu2acpu_raw_int_clr_START  (0)
#define SOC_CTF_SPI_INT_CLR_mcu2acpu_raw_int_clr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPI_RAWSTAT_UNION
 �ṹ˵��  : SPI_RAWSTAT �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�ԭʼ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu2acpu_raw_status : 16; /* bit[0-15] : Each bif of mcu2acpu_raw_int_status[15:0] corresponds to SPI INTID 47~32. LPM3ͨ������mcu2acpu_raw_int_en��mcu2acpu_raw_status��ӦBit�øߣ�ACPUͨ������mcu2acpu_raw_int_clr��mcu2acpu_raw_status��ӦBit���͡� */
        unsigned int  reserved            : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPI_RAWSTAT_UNION;
#endif
#define SOC_CTF_SPI_RAWSTAT_mcu2acpu_raw_status_START  (0)
#define SOC_CTF_SPI_RAWSTAT_mcu2acpu_raw_status_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPITARG0_UNION
 �ṹ˵��  : SPITARG0 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�Ŀ��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 32, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 33, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 34, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: ����ָʾ���˼乲���жϷ��͵��ļ���Core. InterfaceFor SPI INTID 35, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID35 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG0_UNION;
#endif
#define SOC_CTF_SPITARG0_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG0_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG0_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG0_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG0_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG0_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG0_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG0_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPITARG1_UNION
 �ṹ˵��  : SPITARG1 �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�Ŀ��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 36, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 37, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 38, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 39, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID39 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG1_UNION;
#endif
#define SOC_CTF_SPITARG1_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG1_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG1_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG1_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG1_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG1_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG1_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG1_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPITARG2_UNION
 �ṹ˵��  : SPITARG2 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�Ŀ��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 40, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 41, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 42, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 43, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID43 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG2_UNION;
#endif
#define SOC_CTF_SPITARG2_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG2_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG2_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG2_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG2_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG2_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG2_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG2_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPITARG3_UNION
 �ṹ˵��  : SPITARG3 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�Ŀ��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cputargets_byte_offset0 : 8;  /* bit[0-7]  : For SPI INTID 44, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset1 : 8;  /* bit[8-15] : For SPI INTID 45, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset2 : 8;  /* bit[16-23]: For SPI INTID 46, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor.  */
        unsigned int  cputargets_byte_offset3 : 8;  /* bit[24-31]: For SPI INTID 47, processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means the pending SPI INTID47 is sent to processros 0 and 1. */
    } reg;
} SOC_CTF_SPITARG3_UNION;
#endif
#define SOC_CTF_SPITARG3_cputargets_byte_offset0_START  (0)
#define SOC_CTF_SPITARG3_cputargets_byte_offset0_END    (7)
#define SOC_CTF_SPITARG3_cputargets_byte_offset1_START  (8)
#define SOC_CTF_SPITARG3_cputargets_byte_offset1_END    (15)
#define SOC_CTF_SPITARG3_cputargets_byte_offset2_START  (16)
#define SOC_CTF_SPITARG3_cputargets_byte_offset2_END    (23)
#define SOC_CTF_SPITARG3_cputargets_byte_offset3_START  (24)
#define SOC_CTF_SPITARG3_cputargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SGIG_UNION
 �ṹ˵��  : SGIG �Ĵ����ṹ���塣��ַƫ����:0x000 + 0x400 + 0x80*(N)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI�жϲ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgig_id           : 3;  /* bit[0-2]  : The Interrupt ID of the SGI to forward to the specified CPU interfaces. The value of this field is the Interrupt ID, in the range 0-7, for example a value of 3'b011 specifiies interrupt ID 3. */
        unsigned int  reserved_0        : 13; /* bit[3-15] : reserved */
        unsigned int  sgi_cputargetlist : 8;  /* bit[16-23]: CPU Core N (N: 0~7)��SGI�жϲ�����Each bit of CPUTargetList[7:0] refers to the corresponding CPU interface, for example CPUTargetList[0] corresponds to CPU interface 0. Setting a bit to 1 indicates that the interrupt must be forwarded to the corresponding interface. */
        unsigned int  reserved_1        : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_CTF_SGIG_UNION;
#endif
#define SOC_CTF_SGIG_sgig_id_START            (0)
#define SOC_CTF_SGIG_sgig_id_END              (2)
#define SOC_CTF_SGIG_sgi_cputargetlist_START  (16)
#define SOC_CTF_SGIG_sgi_cputargetlist_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SGIPSTAT0_UNION
 �ṹ˵��  : SGIPSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x004 + 0x400 + 0x80*(N)����ֵ:0x00000102�����:32
 �Ĵ���˵��: SGIPending״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgid0_status : 8;  /* bit[0-7]  : Each bit of sgiid0[7:0] refers to the corresponding source CPU ID for SGI INTID 0. */
        unsigned int  sgid1_status : 8;  /* bit[8-15] : Each bit of sgiid0[15:8] refers to the corresponding source CPU ID for SGI INTID 1. */
        unsigned int  sgid2_status : 8;  /* bit[16-23]: Each bit of sgiid1[23:16] refers to the corresponding source CPU ID for SGI INTID 2. */
        unsigned int  sgid3_status : 8;  /* bit[24-31]: Each bit of sgiid0[31:24] refers to the corresponding source CPU ID for SGI INTID 3. */
    } reg;
} SOC_CTF_SGIPSTAT0_UNION;
#endif
#define SOC_CTF_SGIPSTAT0_sgid0_status_START  (0)
#define SOC_CTF_SGIPSTAT0_sgid0_status_END    (7)
#define SOC_CTF_SGIPSTAT0_sgid1_status_START  (8)
#define SOC_CTF_SGIPSTAT0_sgid1_status_END    (15)
#define SOC_CTF_SGIPSTAT0_sgid2_status_START  (16)
#define SOC_CTF_SGIPSTAT0_sgid2_status_END    (23)
#define SOC_CTF_SGIPSTAT0_sgid3_status_START  (24)
#define SOC_CTF_SGIPSTAT0_sgid3_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SGIPSTAT1_UNION
 �ṹ˵��  : SGIPSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x008 + 0x400 + 0x80*(N)����ֵ:0x00000102�����:32
 �Ĵ���˵��: SGIPending״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sgid4_status : 8;  /* bit[0-7]  : Each bit of sgiid0[7:0] refers to the corresponding source CPU ID for SGI INTID 4. */
        unsigned int  sgid5_status : 8;  /* bit[8-15] : Each bit of sgiid0[15:8] refers to the corresponding source CPU ID for SGI INTID 5. */
        unsigned int  sgid6_status : 8;  /* bit[16-23]: Each bit of sgiid1[23:16] refers to the corresponding source CPU ID for SGI INTID 6. */
        unsigned int  sgid7_status : 8;  /* bit[24-31]: Each bit of sgiid0[31:24] refers to the corresponding source CPU ID for SGI INTID 7. */
    } reg;
} SOC_CTF_SGIPSTAT1_UNION;
#endif
#define SOC_CTF_SGIPSTAT1_sgid4_status_START  (0)
#define SOC_CTF_SGIPSTAT1_sgid4_status_END    (7)
#define SOC_CTF_SGIPSTAT1_sgid5_status_START  (8)
#define SOC_CTF_SGIPSTAT1_sgid5_status_END    (15)
#define SOC_CTF_SGIPSTAT1_sgid6_status_START  (16)
#define SOC_CTF_SGIPSTAT1_sgid6_status_END    (23)
#define SOC_CTF_SGIPSTAT1_sgid7_status_START  (24)
#define SOC_CTF_SGIPSTAT1_sgid7_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CTF_PPIPSTAT_UNION
 �ṹ˵��  : PPIPSTAT �Ĵ����ṹ���塣��ַƫ����:0x00C + 0x400 + 0x80*(N)����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPIPending״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 29; /* bit[0-28] : reserved */
        unsigned int  ppistatus : 2;  /* bit[29-30]: ָʾPPI�жϵĵ�ǰ״̬
                                                     bit 30: PPI ID30 - Non-secure physical timer event
                                                     bit 29: PPI ID29- Secure physical timer event  */
        unsigned int  reserved_1: 1;  /* bit[31]   : reserved */
    } reg;
} SOC_CTF_PPIPSTAT_UNION;
#endif
#define SOC_CTF_PPIPSTAT_ppistatus_START  (29)
#define SOC_CTF_PPIPSTAT_ppistatus_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_CTF_SPIPSTAT_UNION
 �ṹ˵��  : SPIPSTAT �Ĵ����ṹ���塣��ַƫ����:0x010 + 0x400 + 0x80*(N)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˼乲���ж�Pending״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spistatus : 16; /* bit[0-15] : ָʾSPI�жϵĵ�ǰ״̬ */
        unsigned int  reserved  : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_CTF_SPIPSTAT_UNION;
#endif
#define SOC_CTF_SPIPSTAT_spistatus_START  (0)
#define SOC_CTF_SPIPSTAT_spistatus_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CTF_IAR_UNION
 �ṹ˵��  : IAR �Ĵ����ṹ���塣��ַƫ����:0x040 + 0x400 + 0x80*(N)����ֵ:0x000003FF�����:32
 �Ĵ���˵��: �ж�ȷ�ϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iar_intid : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  iar_cpuid : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻ط����ж������CPU�ӿڱ�ţ��������������жϣ����򷵻�0 */
        unsigned int  reserved  : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_CTF_IAR_UNION;
#endif
#define SOC_CTF_IAR_iar_intid_START  (0)
#define SOC_CTF_IAR_iar_intid_END    (9)
#define SOC_CTF_IAR_iar_cpuid_START  (10)
#define SOC_CTF_IAR_iar_cpuid_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_CTF_EOIR_UNION
 �ṹ˵��  : EOIR �Ĵ����ṹ���塣��ַƫ����:0x044 + 0x400 + 0x80*(N)����ֵ:0x000003FF�����:32
 �Ĵ���˵��: �жϽ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  eoir_intid : 10; /* bit[0-9]  : �жϺţ���GICC_IARһ�� */
        unsigned int  eoir_cpuid : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ�������GICC_IARһ�£��������������жϣ�������Ч */
        unsigned int  reserved   : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_CTF_EOIR_UNION;
#endif
#define SOC_CTF_EOIR_eoir_intid_START  (0)
#define SOC_CTF_EOIR_eoir_intid_END    (9)
#define SOC_CTF_EOIR_eoir_cpuid_START  (10)
#define SOC_CTF_EOIR_eoir_cpuid_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_CTF_OUTSTAT_UNION
 �ṹ˵��  : OUTSTAT �Ĵ����ṹ���塣��ַƫ����:0x048 + 0x400 + 0x80*(N)����ֵ:0x00000003�����:32
 �Ĵ���˵��: �ж��źżĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nfiq_stat : 1;  /* bit[0]   : �����CPU CoreN��FIQ�źš�active low�� */
        unsigned int  nirq_stat : 1;  /* bit[1]   : �����CPU CoreN��IRQ�źš�Active low�� */
        unsigned int  reserved  : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_CTF_OUTSTAT_UNION;
#endif
#define SOC_CTF_OUTSTAT_nfiq_stat_START  (0)
#define SOC_CTF_OUTSTAT_nfiq_stat_END    (0)
#define SOC_CTF_OUTSTAT_nirq_stat_START  (1)
#define SOC_CTF_OUTSTAT_nirq_stat_END    (1)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_ctf_interface.h */
