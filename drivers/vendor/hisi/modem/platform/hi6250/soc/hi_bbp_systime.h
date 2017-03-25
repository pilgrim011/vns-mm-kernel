/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name		: hi_bbp_systime.h */
/* Version		: 2.0 */
/* Autho			: xxx*/
/* Created		: 2013-02-26*/
/* Last Modified	: */
/* Description		:  The C union definition file for the module bbp_systime*/
/* Function List	: */
/* History		: */
/* 1 Date		: */
/* Modification 	: Create file */
/******************************************************************************/

#ifndef __HI_BBP_SYSTIME_H__
#define __HI_BBP_SYSTIME_H__
#include "product_config.h"
/*
 * Project: hi
 * Module : bbp_systime
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    bbp_systime �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#ifdef BSP_CONFIG_K3V3_SFT
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x1008 /* DRX���Զ�ʱ�ĵ�32λ */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x100c /* DRX���Զ�ʱ�ĸ�32λ */
#else
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x534 /* DRX���Զ�ʱ�ĵ�32λ */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x538 /* DRX���Զ�ʱ�ĸ�32λ */
#endif

#ifndef __ASSEMBLY__

/********************************************************************************/
/*    bbp_systime �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    fpga_version               : 32; /* [31..0] F1�汾�� */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_FPGA_VERSION_T;    /* F1�汾�� */

typedef union
{
    struct
    {
        unsigned int    abs_timer_l                : 32; /* [31..0] DRX���Զ�ʱ�ĵ�32λ */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_L_T;    /* DRX���Զ�ʱ�ĵ�32λ */

typedef union
{
    struct
    {
        unsigned int    abs_timer_h                : 32; /* [31..0] DRX���Զ�ʱ�ĸ�32λ */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_H_T;    /* DRX���Զ�ʱ�ĸ�32λ */

typedef union
{
    struct
    {
        unsigned int    drp_data                   : 32; /* [31..0] DRP���� */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_DRP_DATA_T;    /* DRP���� */

typedef union
{
    struct
    {
        unsigned int    abb_rst                    : 32; /* [31..0] ABB��λ���� */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABB_RST_T;    /* ABB��λ���� */


/********************************************************************************/
/*    bbp_systime ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
#if 0
HI_SET_GET(hi_bbp_systime_abs_timer_l_abs_timer_l,abs_timer_l,HI_BBP_SYSTIME_ABS_TIMER_L_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
HI_SET_GET(hi_bbp_systime_abs_timer_h_abs_timer_h,abs_timer_h,HI_BBP_SYSTIME_ABS_TIMER_H_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET)
#endif
#endif

#endif // __HI_BBP_SYSTIME_H__

