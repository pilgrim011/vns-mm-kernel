/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _DEFLATE_H
#define _DEFLATE_H
#endif

#include <product_config.h>

#include "osl_types.h"
#include "osl_sem.h"

#include "osl_spinlock.h"
#include "osl_thread.h"
#include "drv_nv_id.h"

#include "bsp_socp.h"

#include "socp_balong.h"
#include "hi_deflate.h"
#include "bsp_shared_ddr.h"


/* DEFLATE_REG Base address of Module's Register */
 enum DEFLATE_STATE_ENUM
    {
    DEFLATE_IDLE               = 0,    /* DEFLATE���ڿ���̬ */
    DEFLATE_BUSY,                      /* DEFLATE��æ */
    DEFLATE_UNKNOWN_BUTT              /*  δ֪״̬ */
};
#define  SOCP_REG_DEFLATE_INFORMATION                  Hi_SOCP_REG_DEFLATE_INFORMATION            /* deflateѹ��ģ��汾��Ϣ */
#define  SOCP_REG_DEFLATE_GLOBALCTRL                   Hi_SOCP_REG_DEFLATE_GLOBALCTRL             /* SOCP deflateȫ�ֿ��ƼĴ��� */
#define  SOCP_REG_DEFLATE_IBUFTIMEOUTCFG               Hi_SOCP_REG_DEFLATE_IBUFTIMEOUTCFG         /* ѹ��ģ��ibuf��ʱ���������� */
#define  SOCP_REG_DEFLATE_RAWINT                       Hi_SOCP_REG_DEFLATE_RAWINT                 /* ԭʼ�жϼĴ��� */
#define  SOCP_REG_DEFLATE_INT                          Hi_SOCP_REG_DEFLATE_INT                    /* �ж�״̬�Ĵ��� */
#define  SOCP_REG_DEFLATE_INTMASK                      Hi_SOCP_REG_DEFLATE_INTMASK                /* �ж����μĴ��� */
#define  SOCP_REG_DEFLATE_TFRTIMEOUTCFG                Hi_SOCP_REG_DEFLATE_TFRTIMEOUTCFG          /* ѹ�����ݿ鴫�䳬ʱ������������ֵ */
#define  SOCP_REG_DEFLATE_STATE                        Hi_SOCP_REG_DEFLATE_STATE                  /* ѹ��ģ��������� */
#define  SOCP_REG_DEFLATE_ABORTSTATERECORD             Hi_SOCP_REG_DEFLATE_ABORTSTATERECORD       /* ѹ���쳣״̬��¼ */
#define  SOCP_REG_DEFLATEDEBUG_CH                      Hi_SOCP_REG_DEFLATEDEBUG_CH                /* ѹ��ģ��bugͨ�� */
#define  SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG           Hi_SOCP_REG_DEFLATEDEST_BUFREMAINTHCFG     /* ѹ��ͨ·Ŀ��buffer����ж���ֵ�Ĵ��� */
#define  SOCP_REG_DEFLATEDEST_BUFRPTR            	   Hi_SOCP_REG_DEFLATEDEST_BUFRPTR            /* ѹ��ͨ·Ŀ��buffer��ָ��Ĵ��� */
#define  SOCP_REG_DEFLATEDEST_BUFWPTR                  Hi_SOCP_REG_DEFLATEDEST_BUFWPTR            /* ѹ��ͨ·Ŀ��bufferдָ��Ĵ��� */
#define  SOCP_REG_DEFLATEDEST_BUFADDR                  Hi_SOCP_REG_DEFLATEDEST_BUFADDR            /* ѹ��ͨ·Ŀ��buffer��ʼ��ַ�Ĵ��� */
#define  SOCP_REG_DEFLATEDEST_BUFDEPTH                 Hi_SOCP_REG_DEFLATEDEST_BUFDEPTH           /* ѹ��ͨ·Ŀ��buffer��ȼĴ��� */
#define  SOCP_REG_DEFLATEDEST_BUFTHRH                  Hi_SOCP_REG_DEFLATEDEST_BUFTHRH            /* ������ֵ�ж����üĴ��� */
#define  SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT            Hi_SOCP_REG_DEFLATEDEST_BUFOVFTIMEOUT      /* ѹ��Ŀ��BUFFER�����ʱ���üĴ��� */
#define  SOCP_REG_SOCP_MAX_PKG_BYTE_CFG                Hi_SOCP_REG_SOCP_MAX_PKG_BYTE_CFG          /* socp�������ֽ���ֵ���� */
#define  SOCP_REG_DEFLATE_OBUF_DEBUG                   Hi_SOCP_REG_DEFLATE_OBUF_DEBUG             /* ѹ��Ŀ��buffer DEBUG */

#define DEFLATE_DRX_BACKUP_DDR_ADDR                    (SHM_BASE_ADDR + SHM_OFFSET_DEFLATE)
#define DEFLATE_REG_ADDR_DRX(addr)                     (addr + g_strDeflateStat.baseAddr)
#define DEFLATE_DRX_REG_GBLRST_NUM   (18)
#define DEFLATE_WORK_STATE ((s32)(1)<<19)

#define DEFLATE_OK                  (0)
#define DEFLATE_ERROR               (1)

typedef struct tagSOCP_DRX_DEFLATEDST_S
{
	u32 u32DeflateGlobal;
	u32 u32IbufTimeoutConfig;
	u32 u32RawInt;
	u32 u32IntState;
	u32 u32IntMask;
	u32 u32ThfTimeoutConfig;
	u32 u32DeflateState;
	u32 u32AbortStateRecord;
    u32 u32DebugChan;
	u32 u32ObufThrh;
    u32 u32ReadAddr;
    u32 u32WriteAddr;
    u32 u32StartAddr;
    u32 u32BufSize;
    u32 u32IntThrh;
    u32 u32OvfTimeoutEn;
    u32 u32PkgConfig;
    u32 u32ObufDebug;
}SOCP_DRX_DEFLATEDST_S;

typedef struct tagDEFLATE_GBL_STATE
{    
    u32                 baseAddr;	
} DEFLATE_GBL_STATE;


#define DEFLATE_REG_READ(reg, result)           (result = readl(g_strDeflateStat.baseAddr + reg))
#define DEFLATE_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strDeflateStat.baseAddr, reg, pos, bits, val)
#define DEFLATE_REG_WRITE(reg, data)            (writel(data, (g_strDeflateStat.baseAddr + reg)))

 


