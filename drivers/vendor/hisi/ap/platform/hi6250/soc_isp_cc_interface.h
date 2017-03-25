/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_cc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-07-15 16:00:17
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��15��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_ISP_CC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_CC_INTERFACE_H__
#define __SOC_ISP_CC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) CC
 ****************************************************************************/
/* �Ĵ���˵����filter mode configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCCFG_UNION */
#define SOC_ISP_CC_CCCFG_ADDR(base)                   ((base) + (0x000))

/* �Ĵ���˵����reciprocal for bright weight coefficient
   λ����UNION�ṹ:  SOC_ISP_CC_BRIGHTCOEFF_UNION */
#define SOC_ISP_CC_BRIGHTCOEFF_ADDR(base)             ((base) + (0x004))

/* �Ĵ���˵����recriprocals for dark weight coefficients
   λ����UNION�ṹ:  SOC_ISP_CC_DARKCOEFF_UNION */
#define SOC_ISP_CC_DARKCOEFF_ADDR(base)               ((base) + (0x008))

/* �Ĵ���˵����threshold configuration
   λ����UNION�ṹ:  SOC_ISP_CC_THRESA_UNION */
#define SOC_ISP_CC_THRESA_ADDR(base)                  ((base) + (0x018))

/* �Ĵ���˵����threshold configuration
   λ����UNION�ṹ:  SOC_ISP_CC_THRESB_UNION */
#define SOC_ISP_CC_THRESB_ADDR(base)                  ((base) + (0x01C))

/* �Ĵ���˵����threshold configuration
   λ����UNION�ṹ:  SOC_ISP_CC_THRESC_UNION */
#define SOC_ISP_CC_THRESC_ADDR(base)                  ((base) + (0x020))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA0_UNION */
#define SOC_ISP_CC_CCMATRIXA0_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA1_UNION */
#define SOC_ISP_CC_CCMATRIXA1_ADDR(base)              ((base) + (0x028))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA2_UNION */
#define SOC_ISP_CC_CCMATRIXA2_ADDR(base)              ((base) + (0x02C))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA3_UNION */
#define SOC_ISP_CC_CCMATRIXA3_ADDR(base)              ((base) + (0x030))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA4_UNION */
#define SOC_ISP_CC_CCMATRIXA4_ADDR(base)              ((base) + (0x034))

/* �Ĵ���˵����SW Matrix configuration
   λ����UNION�ṹ:  SOC_ISP_CC_CCMATRIXA5_UNION */
#define SOC_ISP_CC_CCMATRIXA5_ADDR(base)              ((base) + (0x038))

/* �Ĵ���˵����Coefficient value of pixel's correct Y
   λ����UNION�ṹ:  SOC_ISP_CC_PIX_YCOEF_UNION */
#define SOC_ISP_CC_PIX_YCOEF_ADDR(base)               ((base) + (0x0044))





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
                     (1/1) CC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCCFG_UNION
 �ṹ˵��  : CCCFG �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter mode configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bimplementcc : 1;  /* bit[0-0] : Color Correct enable- The bit is taken into account when the CC is not processing a frame (similar to shadowed) 
                                                       0: Color correct is disabled
                                                       1: Color correct is enabled */
        unsigned int  bpixyconst   : 1;  /* bit[1-1] : Pixel Y Constant enable- The bit is taken into account when the CC is not processing a frame (similar to shadowed) 
                                                       0: is disabled
                                                       1: is enabled */
        unsigned int  reserved     : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_CC_CCCFG_UNION;
#endif
#define SOC_ISP_CC_CCCFG_bimplementcc_START  (0)
#define SOC_ISP_CC_CCCFG_bimplementcc_END    (0)
#define SOC_ISP_CC_CCCFG_bpixyconst_START    (1)
#define SOC_ISP_CC_CCCFG_bpixyconst_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_BRIGHTCOEFF_UNION
 �ṹ˵��  : BRIGHTCOEFF �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: reciprocal for bright weight coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightcoeffab : 15; /* bit[0-14] : Reciprocal for bright weight coefficient between AB u0.15
                                                         brightcoeffab=CC_brightCoefKab
                                                         brightcoeffab=1/(brightthres_1-brightthres_0) */
        unsigned int  reserved_0    : 1;  /* bit[15-15]:  */
        unsigned int  brightcoeffbc : 15; /* bit[16-30]: Reciprocal for bright weight coefficient between BC u0.15
                                                         brightcoeffbc=CC_brightCoefKbc
                                                         brightcoeffbc=1/(brightthres_2-brightthres_1) */
        unsigned int  reserved_1    : 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_CC_BRIGHTCOEFF_UNION;
#endif
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffab_START  (0)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffab_END    (14)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffbc_START  (16)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffbc_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_DARKCOEFF_UNION
 �ṹ˵��  : DARKCOEFF �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: recriprocals for dark weight coefficients
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  darkcoeffab : 15; /* bit[0-14] : Reciprocal for dark coefficient between AB u0.15
                                                       darkcoeffab= CC_darkCoefKab
                                                       darkcoeffab=1/(darkthres_0-darkthres_1) */
        unsigned int  reserved_0  : 1;  /* bit[15-15]:  */
        unsigned int  darkcoeffbc : 15; /* bit[16-30]: Reciprocal for dark coefficient between BC u0.15
                                                       darkcoeffbc= CC_darkCoefKbc
                                                       darkcoeffbc=1/(darkthres_1-darkthres_2) */
        unsigned int  reserved_1  : 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_CC_DARKCOEFF_UNION;
#endif
#define SOC_ISP_CC_DARKCOEFF_darkcoeffab_START  (0)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffab_END    (14)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffbc_START  (16)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffbc_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_THRESA_UNION
 �ṹ˵��  : THRESA �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightthres_0 : 12; /* bit[0-11] : Bright pixel desaturation threshold u12.0
                                                         brightthres_0=brightThres[0]
                                                         darthres_0<brightthres_0=<brightthres_1 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  brightthres_1 : 12; /* bit[16-27]: Bright pixel desaturation threshold u12.0
                                                         brightthres_1=brightThres[1]
                                                         brightthres_0=<brightthres_1<=brightthres_2 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESA_UNION;
#endif
#define SOC_ISP_CC_THRESA_brightthres_0_START  (0)
#define SOC_ISP_CC_THRESA_brightthres_0_END    (11)
#define SOC_ISP_CC_THRESA_brightthres_1_START  (16)
#define SOC_ISP_CC_THRESA_brightthres_1_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_THRESB_UNION
 �ṹ˵��  : THRESB �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  darthres_0  : 12; /* bit[0-11] : dark pixel desaturation threshold u12.0
                                                       darkthres_0=darkThres[0]
                                                       darkthres_1<=darthres_0<brightthres_0 */
        unsigned int  reserved_0  : 4;  /* bit[12-15]:  */
        unsigned int  darkthres_1 : 12; /* bit[16-27]: dark pixel desaturation threshold u12.0
                                                       darkthres_1=darkThres[1]
                                                       darkthres_2=<darkthres_1<=darthres_0 */
        unsigned int  reserved_1  : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESB_UNION;
#endif
#define SOC_ISP_CC_THRESB_darthres_0_START   (0)
#define SOC_ISP_CC_THRESB_darthres_0_END     (11)
#define SOC_ISP_CC_THRESB_darkthres_1_START  (16)
#define SOC_ISP_CC_THRESB_darkthres_1_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_THRESC_UNION
 �ṹ˵��  : THRESC �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightthres_2 : 12; /* bit[0-11] : Bright pixel desaturation threshold u12.0
                                                         brightthres_2=brightThres[2]
                                                         brightthres_1<=brightthres_2 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  darkthres_2   : 12; /* bit[16-27]: dark pixel desaturation threshold u12.0
                                                         darkthres_1=darkThres[1]
                                                         darkthres_2=<darkthres_1 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESC_UNION;
#endif
#define SOC_ISP_CC_THRESC_brightthres_2_START  (0)
#define SOC_ISP_CC_THRESC_brightthres_2_END    (11)
#define SOC_ISP_CC_THRESC_darkthres_2_START    (16)
#define SOC_ISP_CC_THRESC_darkthres_2_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA0_UNION
 �ṹ˵��  : CCMATRIXA0 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff0   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff0=colorCorrectMatA[0] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff1   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff1=colorCorrectMatA[1] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA0_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA0_coeff0_START    (0)
#define SOC_ISP_CC_CCMATRIXA0_coeff0_END      (13)
#define SOC_ISP_CC_CCMATRIXA0_coeff1_START    (16)
#define SOC_ISP_CC_CCMATRIXA0_coeff1_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA1_UNION
 �ṹ˵��  : CCMATRIXA1 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff2   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff2=colorCorrectMatA[2] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff3   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff3=colorCorrectMatA[3] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA1_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA1_coeff2_START    (0)
#define SOC_ISP_CC_CCMATRIXA1_coeff2_END      (13)
#define SOC_ISP_CC_CCMATRIXA1_coeff3_START    (16)
#define SOC_ISP_CC_CCMATRIXA1_coeff3_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA2_UNION
 �ṹ˵��  : CCMATRIXA2 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff4   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff4=colorCorrectMatA[4] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff5   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff5=colorCorrectMatA[5] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA2_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA2_coeff4_START    (0)
#define SOC_ISP_CC_CCMATRIXA2_coeff4_END      (13)
#define SOC_ISP_CC_CCMATRIXA2_coeff5_START    (16)
#define SOC_ISP_CC_CCMATRIXA2_coeff5_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA3_UNION
 �ṹ˵��  : CCMATRIXA3 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff6   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff6=colorCorrectMatA[6] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff7   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff7=colorCorrectMatA[7] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA3_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA3_coeff6_START    (0)
#define SOC_ISP_CC_CCMATRIXA3_coeff6_END      (13)
#define SOC_ISP_CC_CCMATRIXA3_coeff7_START    (16)
#define SOC_ISP_CC_CCMATRIXA3_coeff7_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA4_UNION
 �ṹ˵��  : CCMATRIXA4 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff8   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff8=colorCorrectMatA[8] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff9   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff9=colorCorrectMatA[9] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA4_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA4_coeff8_START    (0)
#define SOC_ISP_CC_CCMATRIXA4_coeff8_END      (13)
#define SOC_ISP_CC_CCMATRIXA4_coeff9_START    (16)
#define SOC_ISP_CC_CCMATRIXA4_coeff9_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_CCMATRIXA5_UNION
 �ṹ˵��  : CCMATRIXA5 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff10  : 14; /* bit[0-13] : Matrix coefficient Qs14.0
                                                    coeff10=colorCorrectMatA[10] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff11  : 14; /* bit[16-29]: Matrix coefficient Qs14.0
                                                    coeff11=colorCorrectMatA[11] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA5_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA5_coeff10_START   (0)
#define SOC_ISP_CC_CCMATRIXA5_coeff10_END     (13)
#define SOC_ISP_CC_CCMATRIXA5_coeff11_START   (16)
#define SOC_ISP_CC_CCMATRIXA5_coeff11_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CC_PIX_YCOEF_UNION
 �ṹ˵��  : PIX_YCOEF �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: Coefficient value of pixel's correct Y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pix_ycoef_val : 6;  /* bit[0-5] : Coefficient value of pixel's correct Y u6.0  */
        unsigned int  reserved      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_CC_PIX_YCOEF_UNION;
#endif
#define SOC_ISP_CC_PIX_YCOEF_pix_ycoef_val_START  (0)
#define SOC_ISP_CC_PIX_YCOEF_pix_ycoef_val_END    (5)






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

#endif /* end of soc_isp_cc_interface.h */
