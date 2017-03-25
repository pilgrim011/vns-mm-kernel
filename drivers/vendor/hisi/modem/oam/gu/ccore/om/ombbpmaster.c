/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ombbpmaster.c
  �� �� ��   : ����
  ��    ��   : lixiao 00246515
  ��������   : 2014��1��13��
  ����޸�   :
  ��������   : BbpMaster IP �������ģ�飬�ṩ��дͨ����ʹ�ܡ�ȥʹ�ܽӿڣ��Լ���ͻ���
  �����б�   :
              OM_BbpMasterChanCheckDeCfgPara
              OM_BbpMasterChanSendErrorMsg
              OM_BbpMasterInit
              OM_BbpMasterInitLogFile
              OM_BbpMasterIpcIsr
              OM_BbpMasterRdChanCheckCfgPara
              OM_BbpMasterRdChanGive
              OM_BbpMasterRdChanInfoRefresh
              OM_BbpMasterRdChanIpcLock
              OM_BbpMasterRdChanIpcUnLock
              OM_BbpMasterRdChannelConfig
              OM_BbpMasterRdChannelDeConfig
              OM_BbpMasterRdChanTake
              OM_BbpMasterRdErrorInfoSave
              OM_BbpMasterSaveLogFile
              OM_BbpMasterWrChanCheckCfgPara
              OM_BbpMasterWrChanGive
              OM_BbpMasterWrChanInfoRefresh
              OM_BbpMasterWrChanIpcLock
              OM_BbpMasterWrChanIpcUnLock
              OM_BbpMasterWrChannelConfig
              OM_BbpMasterWrChannelDeConfig
              OM_BbpMasterWrChanTake
              OM_BbpMasterWrErrorInfoSave
  �޸���ʷ   :
  1.��    ��   : 2014��1��13��
    ��    ��   : lixiao 00246515
    �޸�����   : �����ļ�

******************************************************************************/
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "apmprocess.h"
#include "ombbpmaster.h"
#include "hpaoperatertt.h"
#include "bbp_gsm_interface.h"
#include "bbp_comm_interface.h"
#include "soc_bbpmaster_interface.h"
#include "mdrv.h"

#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
#include "bbp_guc_bbpmst_interface.h"
#endif

/*lint -e767 �޸���:����;������:���� 51137;ԭ��:Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_OM_BBP_MASTER_C
/*lint +e767 �޸���:����;������:���� 51137; */


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OM_BBPMASTER_UINT32   g_ulOmBbpMasterChipType = OM_BBPMASTER_NO_IP;

BBPMASTER_ENTITY_STRU g_astOmBbpMasterWrEntity[OM_BBPMASTER_MAX_WR_CHAN_CNT];
BBPMASTER_ENTITY_STRU g_astOmBbpMasterRdEntity[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChanWM[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChanWM[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_ulOmBbpMasterTest;

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChCallCnt[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChCallCnt[OM_BBPMASTER_MAX_RD_CHAN_CNT];

OM_BBPMASTER_UINT32   g_astOmBbpMasterWrChIpcCnt[OM_BBPMASTER_MAX_WR_CHAN_CNT];
OM_BBPMASTER_UINT32   g_astOmBbpMasterRdChIpcCnt[OM_BBPMASTER_MAX_RD_CHAN_CNT];

/*****************************************************************************
 �� �� ��  : OM_BbpMasterGetV8R1BbitBaseAddr
 ��������  : ����PID��ȡV8R1��FPGAƽ̨BBP Master�Ļ���ַ;
             V8R1FPGAƽ̨��,W��G1��G2��BBP Master����ַ��ͬ����SFT��ASIC�ϲŹ�һ
 �������  : ulPID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetV8R1BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    if (I0_DSP_PID_GPHY == ulPID)
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
    else if (I1_DSP_PID_GPHY == ulPID)
    {
        return SOC_BBP_GSM1_BASE_ADDR;
    }
    else
    {
        return SOC_BBP_CDMA_BASE_ADDR;
    }
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterGetV7R5BbitBaseAddr
 ��������  : ����PID��ȡV8R1��FPGAƽ̨BBP Master�Ļ���ַ;
             V7R5FPGAƽ̨��,G1��G2��BBP Master����ַ��ͬ����SFT��ASIC�ϲŹ�һ
 �������  : ulPID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetV7R5BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    /* BBIT: 2G ����ַ���� */
    if (I0_DSP_PID_GPHY == ulPID)
    {
        return (SOC_BBP_COMM_BASE_ADDR + 0x800); /* G0ƫ�Ƶ�ַ�� 0x800 */
    }
    else if (I1_DSP_PID_GPHY == ulPID)
    {
        return (SOC_BBP_COMM_BASE_ADDR + 0x800); /* G1ƫ�Ƶ�ַ�� 0x800 */
    }
    else
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterGetK3V6BaseAddr
 ��������  : ����PID��ȡK3V6��FPGAƽ̨BBP Master�Ļ���ַ;
             K3V6FPGAƽ̨��,U2��BBP Master����ַ��ͬ����SFT��ASIC�ϲŹ�һ
 �������  : ulPID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetK3V6BbitBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
    /* U2ƫ�Ƶ�ַ�� -0xC90000��������PIDͬ���Ͽ� */

    return SOC_BBP_COMM_BASE_ADDR;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterGetBaseAddr
 ��������  : ����PID��ȡBBP Master�Ļ���ַ;
             V8R1FPGAƽ̨��,W��G1��G2��BBP Master����ַ��ͬ����SFT��ASIC�ϲŹ�һ
 �������  : ulPID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetBaseAddr(OM_BBPMASTER_UINT32 ulPID)
{
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_INT    lBoardType;

    lBoardType = VOS_GetBoardType();

    /* SFT & ASIC����ַ��һ */
    if ((BOARD_TYPE_ASIC == lBoardType) || (BOARD_TYPE_SFT == lBoardType))
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }

    if (OM_BBPMASTER_IP_V8R1 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetV8R1BbitBaseAddr(ulPID);
    }
    else if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetV7R5BbitBaseAddr(ulPID);
    }
    else if (OM_BBPMASTER_IP_K3V6 == g_ulOmBbpMasterChipType)
    {
        return OM_BbpMasterGetK3V6BbitBaseAddr(ulPID);
    }
    else
    {
        return SOC_BBP_COMM_BASE_ADDR;
    }
#else
    /* Cģ ������̬����ַ��ͬ */
    return SOC_BBP_COMM_BASE_ADDR;
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterV7R5RWInt0ChanIsr
 ��������  : OM BbpMaster����ģ���дͨ���ж���Ӧ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterV7R5RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntSta;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [5:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��[11:8]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־�� */
    ulWrIntSta  = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY));
    ulWrIntSta |= OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY));
    ulWrIntSta |= OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY));

    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY), ulWrIntSta);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY), ulWrIntSta);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY), ulWrIntSta);

    ulRdIntSta = ulWrIntSta;

    /* ��������дͨ������ѯ��Ӧ��Status Reg��������ж��ϱ�������ö�Ӧ���жϴ�������ִ����ɺ����ζ�Ӧ���жϴ����� */
    for (i = 0 ; i < OM_BBPMASTER_V7R5_WR_CHAN_CNT; i++)
    {
        if(0 == (ulWrIntSta & 0x1))
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntSta = ulWrIntSta >> 1;
    }

    ulRdIntSta = ulRdIntSta >> 8;

    for (i = 0 ; i < OM_BBPMASTER_V7R5_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterV8R5RWInt0ChanIsr
 ��������  : OM BbpMaster����ģ���дͨ���ж���Ӧ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterV8R5RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntSta;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��[31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־�� */
    ulWrIntSta  = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR, ulWrIntSta);

    ulRdIntSta  = ulWrIntSta;

    /* ��������дͨ������ѯ��Ӧ��Status Reg��������ж��ϱ�������ö�Ӧ���жϴ�������ִ����ɺ����ζ�Ӧ���жϴ����� */
    for (i = 0 ; i < OM_BBPMASTER_V8R5_WR_CHAN_CNT; i++)
    {
        if(0 == (ulWrIntSta & 0x1))
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntSta = ulWrIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntSta = ulWrIntSta >> 1;
    }

    ulRdIntSta = ulRdIntSta >> OM_BBP_MASTER_CHAN_REG_WIDTH;

    for (i = 0 ; i < OM_BBPMASTER_V8R5_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/
#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterV8R5RWInt0ChanIsr
 ��������  : OM BbpMaster����ģ���дͨ���ж���Ӧ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterK3V6RWInt0ChanIsr(OM_BBPMASTER_VOID)
{
#if ( VOS_WIN32 != VOS_OS_VER )
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32          i;
    OM_BBPMASTER_UINT32          ulWrIntStaLow;
    OM_BBPMASTER_UINT32          ulWrIntStHigh;
    OM_BBPMASTER_UINT32          ulRdIntSta;

    ulWrIntStHigh = 0;

    /*lint -e662 -e661*/
    mdrv_int_disable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/

    /* [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��[31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־�� */
    ulWrIntStaLow = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR_ADDR, ulWrIntStaLow);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("StaLow 0x%x\n", (int)ulWrIntStaLow);
    }

#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    ulWrIntStHigh = OM_BBPMASTER_READ_REG(BBPCOMM_BBPMST_INT0_STATE2_ADDR);
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_CLR2_ADDR, ulWrIntStHigh);
#endif

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("StaHigh 0x%x\n", (int)ulWrIntStHigh);
    }

    ulRdIntSta    = ulWrIntStaLow;

    /* ���� 0:15 дͨ������ѯ��Ӧ��Status Reg��������ж��ϱ�������ö�Ӧ���жϴ�������ִ����ɺ����ζ�Ӧ���жϴ����� */
    for (i = 0 ; i < OM_BBP_MASTER_CHAN_REG_WIDTH; i++)
    {
        if(0 == (ulWrIntStaLow & 0x1))
        {
            ulWrIntStaLow = ulWrIntStaLow >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i].pfnIntFunc)
        {
            ulWrIntStaLow = ulWrIntStaLow >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i].pfnIntFunc();
        ulWrIntStaLow = ulWrIntStaLow >> 1;
    }

    ulRdIntSta = ulRdIntSta >> OM_BBP_MASTER_CHAN_REG_WIDTH;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint1("RdIntSta 0x%x\n", (int)ulRdIntSta);
    }

    for (i = 0 ; i < OM_BBPMASTER_K3V6_RD_CHAN_CNT; i++)
    {
        if(0 == (ulRdIntSta & 0x1))
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterRdEntity[i].pfnIntFunc)
        {
            ulRdIntSta = ulRdIntSta >> 1;
            continue;
        }

        g_astOmBbpMasterRdEntity[i].pfnIntFunc();
        ulRdIntSta = ulRdIntSta >> 1;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint("RdInt Finish\n");
    }

    /* BBPMST_INT0_MASK2���ж�0��дͨ��23~дͨ��16���ж�mask���üĴ��� */
    for (i = 0 ; i < (OM_BBPMASTER_K3V6_WR_CHAN_CNT - OM_BBP_MASTER_CHAN_REG_WIDTH); i++)
    {
        if(0 == (ulWrIntStHigh & 0x1))
        {
            ulWrIntStHigh = ulWrIntStHigh >> 1;
            continue;
        }

        if (OM_BBPMASTER_NULL_PTR == g_astOmBbpMasterWrEntity[i+OM_BBP_MASTER_CHAN_REG_WIDTH].pfnIntFunc)
        {
            ulWrIntStHigh = ulWrIntStHigh >> 1;
            continue;
        }

        g_astOmBbpMasterWrEntity[i+OM_BBP_MASTER_CHAN_REG_WIDTH].pfnIntFunc();
        ulWrIntStHigh = ulWrIntStHigh >> 1;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        LogPrint("IntStHigh Finish\n");
    }

    /*lint -e662 -e661*/
    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
    /*lint +e662 +e661*/
#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitChipType
 ��������  : ��ʼ��BBP MASTER������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitChipType( OM_BBPMASTER_VOID )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V8R1;
#endif

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V7R5;
#endif

#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_K3V6;
#else
    g_ulOmBbpMasterChipType = OM_BBPMASTER_IP_V8R5;
#endif
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitBaseAddr
 ��������  : ��ʼ��BBP���ʵĻ���ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitBaseAddr( OM_BBPMASTER_VOID )
{
    if (OM_BBPMASTER_NO_IP == g_ulOmBbpMasterChipType )
    {
        return;
    }

    /* дͨ����ַ��ʼ�� */
    g_astOmBbpMasterWrChanWM[0]  = (BBPCOMM_BBPMST_WR_CH0_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[1]  = (BBPCOMM_BBPMST_WR_CH1_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[2]  = (BBPCOMM_BBPMST_WR_CH2_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[3]  = (BBPCOMM_BBPMST_WR_CH3_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[4]  = (BBPCOMM_BBPMST_WR_CH4_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);

    /* V7R5������һ��дͨ����ַ */
#if (BBP_MASTER_INT_MODE == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[5]  = (BBPCOMM_BBPMST_WR_CH5_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* V8R5������8��дͨ����ַ */
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[6]  = (BBPCOMM_BBPMST_WR_CH6_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[7]  = (BBPCOMM_BBPMST_WR_CH7_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[8]  = (BBPCOMM_BBPMST_WR_CH8_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[9]  = (BBPCOMM_BBPMST_WR_CH9_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[10] = (BBPCOMM_BBPMST_WR_CH10_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[11] = (BBPCOMM_BBPMST_WR_CH11_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[12] = (BBPCOMM_BBPMST_WR_CH12_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[13] = (BBPCOMM_BBPMST_WR_CH13_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* K3V5������10��дͨ����ַ */
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_astOmBbpMasterWrChanWM[14] = (BBPCOMM_BBPMST_WR_CH14_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[15] = (BBPCOMM_BBPMST_WR_CH15_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[16] = (BBPCOMM_BBPMST_WR_CH16_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[17] = (BBPCOMM_BBPMST_WR_CH17_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[18] = (BBPCOMM_BBPMST_WR_CH18_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[19] = (BBPCOMM_BBPMST_WR_CH19_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[20] = (BBPCOMM_BBPMST_WR_CH20_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[21] = (BBPCOMM_BBPMST_WR_CH21_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[22] = (BBPCOMM_BBPMST_WR_CH22_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterWrChanWM[23] = (BBPCOMM_BBPMST_WR_CH23_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* ��ȡͨ����ַ��ʼ�� */
    g_astOmBbpMasterRdChanWM[0]  = (BBPCOMM_BBPMST_RD_CH0_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[1]  = (BBPCOMM_BBPMST_RD_CH1_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[2]  = (BBPCOMM_BBPMST_RD_CH2_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[3]  = (BBPCOMM_BBPMST_RD_CH3_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);

    /* V8R5������7��дͨ����ַ */
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
    g_astOmBbpMasterRdChanWM[4]  = (BBPCOMM_BBPMST_RD_CH4_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[5]  = (BBPCOMM_BBPMST_RD_CH5_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[6]  = (BBPCOMM_BBPMST_RD_CH6_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[7]  = (BBPCOMM_BBPMST_RD_CH7_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[8]  = (BBPCOMM_BBPMST_RD_CH8_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[9]  = (BBPCOMM_BBPMST_RD_CH9_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[10] = (BBPCOMM_BBPMST_RD_CH10_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    /* K3V5������5����ͨ����ַ */
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
    g_astOmBbpMasterRdChanWM[11] = (BBPCOMM_BBPMST_RD_CH11_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[12] = (BBPCOMM_BBPMST_RD_CH12_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[13] = (BBPCOMM_BBPMST_RD_CH13_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[14] = (BBPCOMM_BBPMST_RD_CH14_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
    g_astOmBbpMasterRdChanWM[15] = (BBPCOMM_BBPMST_RD_CH15_MODE_ADDR - SOC_BBP_COMM_BASE_ADDR);
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterGetIpInfo
 ��������  : ��ȡBBP Master��IP����
 �������  : ��
 �������  : ��
 �� �� ֵ  : OM_BBPMASTER_NO_IP/OM_BBPMASTER_OLD_IP/OM_BBPMASTER_NEW_IP
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterGetIpInfo( OM_BBPMASTER_VOID )
{
    return g_ulOmBbpMasterChipType;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitV8R1Entity
 ��������  : ��ʼ��V8R1 BBP Master�Ķ�дʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV8R1Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V8R1_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    /*  ���V8R1,2G���дͨ��ȥ�����Ᵽ�� */
    g_astOmBbpMasterWrEntity[3].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[4].ulShared        = OM_BBPMASTER_NO;

    for ( i = 0 ; i < OM_BBPMASTER_V8R1_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

   /*  ���V8R1,2G��ض�ͨ��ȥ�����Ᵽ�� */
    g_astOmBbpMasterRdEntity[2].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterRdEntity[3].ulShared        = OM_BBPMASTER_NO;

}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitV7R5Entity
 ��������  : ��ʼ��V7R5 BBP Master�Ķ�дʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV7R5Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V7R5_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    /*  ���V7R5,2G���дͨ��ȥ�����Ᵽ�� */
    g_astOmBbpMasterWrEntity[0].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[1].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[4].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterWrEntity[5].ulShared        = OM_BBPMASTER_NO;

    for ( i = 0 ; i < OM_BBPMASTER_V7R5_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_YES;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

    /*  ���V7R5,2G��ض�ͨ��ȥ�����Ᵽ�� */
    g_astOmBbpMasterRdEntity[0].ulShared        = OM_BBPMASTER_NO;
    g_astOmBbpMasterRdEntity[3].ulShared        = OM_BBPMASTER_NO;

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* ʹ��ARM��BBP Mater��дͨ������жϣ�������MaskλΪĬ��ֵ(����),������ͨ��ʱʹ��Maskλ */
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
    OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterV7R5RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;

}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitV8R5Entity
 ��������  : ��ʼ��V8R5 BBP Master�Ķ�дʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitV8R5Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_V8R5_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    for ( i = 0 ; i < OM_BBPMASTER_V8R5_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* ʹ��ARM��BBP Mater����дͨ������жϣ�������MaskλΪĬ��ֵ(����),������ͨ��ʱʹ��Maskλ */
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterV8R5RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitV8R5Entity
 ��������  : ��ʼ��V8R5 BBP Master�Ķ�дʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitK3V6Entity( OM_BBPMASTER_VOID )
{
    OM_BBPMASTER_UINT32 i;

    for ( i = 0 ; i < OM_BBPMASTER_K3V6_WR_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterWrEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterWrEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterWrChCallCnt[i]          = 0;
        g_astOmBbpMasterWrChIpcCnt[i]           = 0;
    }

    for ( i = 0 ; i < OM_BBPMASTER_K3V6_RD_CHAN_CNT; i++ )
    {
        g_astOmBbpMasterRdEntity[i].ulShared    = OM_BBPMASTER_NO;
        g_astOmBbpMasterRdEntity[i].pfnIntFunc  = OM_BBPMASTER_NULL_PTR;

        g_astOmBbpMasterRdChCallCnt[i]          = 0;
        g_astOmBbpMasterRdChIpcCnt[i]           = 0;
    }

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    /* ʹ��ARM��BBP Mater����дͨ������жϣ�������MaskλΪĬ��ֵ(����),������ͨ��ʱʹ��Maskλ */
    OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

    mdrv_int_connect(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0),
                       (VOIDFUNCPTR)OM_BbpMasterK3V6RWInt0ChanIsr,
                        0);

    mdrv_int_enable(mdrv_int_get_num(BSP_INT_TYPE_GUCBBP_AXIMST_ERR0));
#endif
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInitEntity
 ��������  : ��ʼ��BBP Master�Ķ�дʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterInitEntity( OM_BBPMASTER_VOID )
{
    g_ulOmBbpMasterTest = 0;

    switch (g_ulOmBbpMasterChipType)
    {
        case OM_BBPMASTER_IP_V8R1:
            OM_BbpMasterInitV8R1Entity();
            break;

        case OM_BBPMASTER_IP_V7R5:
            OM_BbpMasterInitV7R5Entity();
            break;

        case OM_BBPMASTER_IP_V8R5:
            OM_BbpMasterInitV8R5Entity();
            break;

        case OM_BBPMASTER_IP_K3V6:
            OM_BbpMasterInitK3V6Entity();
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterInit
 ��������  : OM BbpMaster����ģ���ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterInit( OM_BBPMASTER_VOID )
{
    OM_BbpMasterInitChipType();

    OM_BbpMasterInitBaseAddr();

    OM_BbpMasterInitEntity();

    return OM_BBPMASTER_OK;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanIpcLock
 ��������  : OM BbpMaster����ģ��дͨ����IPC��Դ�����뺯��
 �������  : ulChanId
 �������  : ��
 �� �� ֵ  : VOS_YES��VOS_NO
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterWrChanIpcLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32             u32SignalNum;

    /* ͨ�����Բ���Ҫͨ����Դ������ */
    if (OM_BBPMASTER_NO == g_astOmBbpMasterWrEntity[ulChanId].ulShared)
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }

    g_astOmBbpMasterWrChIpcCnt[ulChanId]++;

    /* �����дͨ��IPC��Դ���Ŷ�Ӧдͨ��ID + IPC_SEM_BBPMASTER_0 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_0;

#ifdef CSDR_FEATURE_ON
#else
    if (VOS_OK == mdrv_ipc_spin_trylock(u32SignalNum))
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcLock mdrv_ipc_spin_trylock u32SignalNum: %d\n", (int)u32SignalNum);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }
#endif
#endif

    return OM_BBPMASTER_NO;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanIpcUnLock
 ��������  : OM BbpMaster����ģ��дͨ����IPC��Դ���ͷź���
 �������  : ulChanId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanIpcUnLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                          u32SignalNum;

    /* ͨ�����Բ���Ҫͨ����Դ������ */
    if (OM_BBPMASTER_NO == g_astOmBbpMasterWrEntity[ulChanId].ulShared)
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterWrChanIpcUnLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return;
    }

    /* �����Unlock��ͳ�� */
    if (0 < g_astOmBbpMasterWrChIpcCnt[ulChanId])
    {
        g_astOmBbpMasterWrChIpcCnt[ulChanId]--;
    }

    /* �����дͨ��IPC��Դ���Ŷ�Ӧдͨ��ID + IPC_SEM_BBPMASTER_0 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_0;

#ifdef CSDR_FEATURE_ON
#else
    mdrv_ipc_spin_unlock(u32SignalNum);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint1("OM_BbpMasterWrChanIpcUnLock mdrv_ipc_spin_unlock u32SignalNum: %d\n", (int)u32SignalNum);
        /*lint +e534*/
    }
#endif
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterRdChanIpcLock
 ��������  : OM BbpMaster����ģ���ͨ����IPC��Դ�����뺯��
 �������  : ulChanId
 �������  : ��
 �� �� ֵ  : VOS_YES��VOS_NO
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_UINT32 OM_BbpMasterRdChanIpcLock(OM_BBPMASTER_UINT32 ulChanId)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                          u32SignalNum;

    /* ͨ�����Բ���Ҫͨ����Դ������ */
    if ( OM_BBPMASTER_NO == g_astOmBbpMasterRdEntity[ulChanId].ulShared )
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return OM_BBPMASTER_YES;
    }

    g_astOmBbpMasterRdChIpcCnt[ulChanId]++;

    /* ����Ķ�ͨ��IPC��Դ���Ŷ�Ӧ��ͨ��ID + IPC_SEM_BBPMASTER_5 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_5;

#ifdef CSDR_FEATURE_ON
#else
    if (VOS_OK == mdrv_ipc_spin_trylock(u32SignalNum))
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcLock mdrv_ipc_spin_trylock u32SignalNum: %d\n", (int)u32SignalNum);
            /*lint +e534*/
        }

        return VOS_YES;
    }
#endif
#endif

    return VOS_NO;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterRdChanIpcUnLock
 ��������  : OM BbpMaster����ģ���ͨ����IPC��Դ���ͷź���
 �������  : ulChanId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanIpcUnLock( OM_BBPMASTER_UINT32 ulChanId )
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    OM_BBPMASTER_UINT32                              u32SignalNum;

    /* ͨ�����Բ���Ҫͨ����Դ������ */
    if ( OM_BBPMASTER_NO == g_astOmBbpMasterRdEntity[ulChanId].ulShared )
    {
        if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
        {
            /*lint -e534*/
            LogPrint1("OM_BbpMasterRdChanIpcUnLock Chan Id: %d Need not IPC\n", (int)ulChanId);
            /*lint +e534*/
        }

        return;
    }

    /* �����Unlock��ͳ�� */
    if (0 < g_astOmBbpMasterRdChIpcCnt[ulChanId])
    {
        g_astOmBbpMasterRdChIpcCnt[ulChanId]--;
    }

    /* ����Ķ�ͨ��IPC��Դ���Ŷ�Ӧ��ͨ��ID + IPC_SEM_BBPMASTER_5 */
    u32SignalNum = ulChanId + IPC_SEM_BBPMASTER_5;

#ifdef CSDR_FEATURE_ON
#else
    mdrv_ipc_spin_unlock(u32SignalNum);

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint1("OM_BbpMasterRdChanIpcUnLock mdrv_ipc_spin_unlock u32SignalNum: %d\n", (int)u32SignalNum);
        /*lint +e534*/
    }

#endif
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanTake
 ��������  : OM BbpMasterдͨ��ʹ�����ã�����ʹ���ϲ�͸����ʽ��
 �������  : ulChanId
             pstWrChanCfg
       V7R5: [5:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
              [11:8]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
              [21:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
              [27:24]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�

       V8R5: [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
              [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�

       K3V6: INT_MASK [15:0]���ֱ�Ϊ��������дͨ��(0~15)��Ӧ�жϵ�����λ��1��ʾ���Ρ�
                       [31:16]���ֱ�Ϊ��������дͨ��(0~15)����λ��дʹ�ܡ�

             INT_MASK2 [15:0]���ֱ�Ϊ��������дͨ��(16~24)��Ӧ�жϵ�����λ��1��ʾ���Ρ�
                        [31:16]���ֱ�Ϊ��������дͨ��(16~24)����λ��дʹ�ܡ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanTake(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_WR_CHANNEL_CONFIG_STRU *pstWrChanCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstWrChanCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_MODE_OFFSET),
                                                pstWrChanCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_CLK_SEL_OFFSET),
                                                pstWrChanCfg->ulClockSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_BASE_ADDR_OFFSET),
                                                pstWrChanCfg->ulStartAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_END_ADDR_OFFSET),
                                                pstWrChanCfg->ulEndAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_BURST_BEAT_OFFSET),
                                                pstWrChanCfg->ulBurstLen);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_AXI_SEL_OFFSET),
                                                pstWrChanCfg->ulAxiSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_INTR_MODE_OFFSET),
                                                pstWrChanCfg->ulIntMode);

    /* ʹ��ARM��BBP Mater��дͨ������ж� */
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
            (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << ulChanId));
    }
    else /* Mask(0~15) & Mask2(16~23) */
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);

        if (OM_BBP_MASTER_CHAN_REG_WIDTH > ulChanId)
        {
            OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << ulChanId));
        }
        else
        {
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
            OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK2_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_16 << (ulChanId - OM_BBP_MASTER_CHAN_REG_WIDTH)));
#endif
        }
    }

    g_astOmBbpMasterWrEntity[ulChanId].pfnIntFunc = pstWrChanCfg->pfnIntFunc;
#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanGive
 ��������  : OM BbpMasterдͨ��ȥʹ�����ã�����ʹ���ϲ�͸����ʽ��
 �������  : ulChanId
             pstWrChanDeCfg
 �������  : ��

     V7R5: [5:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                  [11:8]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                  [21:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
                  [27:24]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�

    V8R5: [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
              [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�

    K3V6: [15:0]���ֱ�Ϊ��������дͨ��(0~15)��Ӧ�жϵ�����λ��1��ʾ���Ρ�
             [31:16]���ֱ�Ϊ��������дͨ��(0~15)����λ��дʹ�ܡ�
           [15:0]���ֱ�Ϊ��������дͨ��(16~24)��Ӧ�жϵ�����λ��1��ʾ���Ρ�
                  [31:16]���ֱ�Ϊ��������дͨ��(16~24)����λ��дʹ�ܡ�

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterWrChanGive(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_CHANNEL_DECONFIG_STRU *pstWrChanDeCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstWrChanDeCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_MODE_OFFSET),
                                                pstWrChanDeCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterWrChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_WR_CLK_SEL_OFFSET),
                                                pstWrChanDeCfg->ulClockSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON

    /* Mask(0~15) & Mask2(16~23) */
    if (OM_BBP_MASTER_CHAN_REG_WIDTH > ulChanId)
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                            (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_0 | OM_BBPMASTER_MASK_BIT_16) << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_U2 == FEATURE_ON)
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK2_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                            (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_0 | OM_BBPMASTER_MASK_BIT_16) << (ulChanId - OM_BBP_MASTER_CHAN_REG_WIDTH)));
#endif
    }

    g_astOmBbpMasterWrEntity[ulChanId].pfnIntFunc = OM_BBPMASTER_NULL_PTR;
#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanGive
 ��������  : OM BbpMasterдͨ��ȥʹ�����ã�����ʹ���ϲ�͸����ʽ��
 �������  : ulChanId
             pstWrChanDeCfg
 �������  : ��

    V7R5: [5:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                  [11:8]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                  [21:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
                  [27:24]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�

    V8R5: [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
              [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�

    K3V6: INT_MASK [15:0]���ֱ�Ϊ0~15����дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                       [31:16]���ֱ�Ϊ0~15����дͨ������λ��дʹ�ܡ�
             INT_MASK2 [15:0]���ֱ�Ϊ0~15����дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
                       [31:16]���ֱ�Ϊ0~15����дͨ������λ��дʹ�ܡ�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanTake(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_RD_CHANNEL_CONFIG_STRU *pstRdChanCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstRdChanCfg)
    {
        return;
    }


#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_MODE_OFFSET),
                                                pstRdChanCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_CLK_SEL_OFFSET),
                                                pstRdChanCfg->ulClockSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_INIT_ADDR_OFFSET),
                                                pstRdChanCfg->ulStartAddr);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_BURST_BEAT_OFFSET),
                                                pstRdChanCfg->ulBurstLen);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_AXI_SEL_OFFSET),
                                                pstRdChanCfg->ulAxiSel);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_INTR_MODE_OFFSET),
                                                pstRdChanCfg->ulIntMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_BIT_WIDTH_IND_OFFSET),
                                                pstRdChanCfg->ulValidLen);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I0_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(I1_DSP_PID_GPHY)), 1);
        OM_BBPMASTER_WRITE_REG((BBPCOMM_BBPMST_INT0_EN_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(DSP_PID_WPHY)), 1);

        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (VOS_UINT32)((VOS_UINT32)OM_BBPMASTER_MASK_BIT_24 << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_EN_ADDR, 1);
        /*lint -e701*/
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_R_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (OM_BBPMASTER_MASK_BIT_16 << ulChanId));
        /*lint +e701*/
#endif
    }

    g_astOmBbpMasterRdEntity[ulChanId].pfnIntFunc = pstRdChanCfg->pfnIntFunc;
#endif
#endif
#endif
    return;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChanGive
 ��������  : OM BbpMasterдͨ��ȥʹ�����ã�����ʹ���ϲ�͸����ʽ��
 �������  : ulChanId
             pstWrChanDeCfg
 �������  : ��
     V7R5: [5:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
           [11:8]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
           [21:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
           [27:24]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�

    V8R5: [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
          [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_VOID OM_BbpMasterRdChanGive(OM_BBPMASTER_UINT32 ulPID,
                                             OM_BBPMASTER_UINT32 ulChanId,
                                             BBPMASTER_CHANNEL_DECONFIG_STRU *pstRdChanDeCfg)
{
    if (OM_BBPMASTER_NULL_PTR == pstRdChanDeCfg)
    {
        return;
    }

#if ( VOS_WIN32 != VOS_OS_VER )
    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_MODE_OFFSET),
                                                pstRdChanDeCfg->ulWorkMode);

    OM_BBPMASTER_WRITE_REG((OM_BBPMASTER_UINT32)(g_astOmBbpMasterRdChanWM[ulChanId]
                                                + OM_BbpMasterGetBaseAddr(ulPID)
                                                + OM_BBPMASTER_RD_CLK_SEL_OFFSET),
                                                pstRdChanDeCfg->ulClockSel);

#if (BBP_MASTER_INT_MODE == FEATURE_ON)
#ifndef CSDR_FEATURE_ON
    if (OM_BBPMASTER_IP_V7R5 == g_ulOmBbpMasterChipType)
    {
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    (VOS_UINT32)((VOS_UINT32)(OM_BBPMASTER_MASK_BIT_24 | OM_BBPMASTER_MASK_BIT_8) << ulChanId));
    }
    else
    {
#if (FEATURE_BBP_MASTER_CHAN_EXTEND == FEATURE_ON)
        /*lint -e701*/
        OM_BBPMASTER_WRITE_REG(BBPCOMM_BBPMST_INT0_MASK_R_ADDR - SOC_BBP_COMM_BASE_ADDR + OM_BbpMasterGetBaseAddr(ulPID),
                    ((OM_BBPMASTER_MASK_BIT_16 | OM_BBPMASTER_MASK_BIT_0) << ulChanId));
        /*lint +e701*/
#endif
    }

    g_astOmBbpMasterRdEntity[ulChanId].pfnIntFunc = OM_BBPMASTER_NULL_PTR;
#endif
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChannelConfig
 ��������  : OM BbpMasterдͨ��ʹ�����ýӿ�
 �������  : ulPID,
             ulChanId
             pstWrChanCfg
 �������  : ��
 �� �� ֵ  : ���ý��������
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_WR_CHANNEL_CONFIG_STRU *pstWrChanCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstWrChanCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_WR_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    g_astOmBbpMasterWrChCallCnt[ulChanId]++;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    if (OM_BBPMASTER_YES != OM_BbpMasterWrChanIpcLock(ulChanId))
    {
#ifdef CSDR_FEATURE_ON
        CSDR_MNTN_LogError2(ulPID, ulChanId);
#else
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelConfig OM_BBPMASTER_LOCK_IPC_FAIL: PID: %d, Chan Id: %d\n",
                (int)ulPID, (int)ulChanId);
        /*lint +e534*/
#endif
        return OM_BBPMASTER_LOCK_IPC_FAIL;
    }

    /* ����ͨ���ɹ������¿�ν�ɲ�ͨ����Ϣ */
    OM_BbpMasterWrChanTake(ulPID, ulChanId, pstWrChanCfg);

#else
    /*lint -e534*/
    LogPrint("\r\n OM_BbpMasterWrChannelConfig: no support BbpMaster!!!");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterWrChannelDeConfig
 ��������  : OM BbpMasterдͨ��ȥʹ�����ýӿ�
 �������  : ulPID,
             ulChanId
             pstChanDeCfg
 �������  : ��
 �� �� ֵ  : ���ý��������
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstChanDeCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_WR_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterWrChannelDeConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    /* �����Unlock��ͳ�� */
    if (0 < g_astOmBbpMasterWrChCallCnt[ulChanId])
    {
        g_astOmBbpMasterWrChCallCnt[ulChanId]--;
    }

    OM_BbpMasterWrChanGive(ulPID, ulChanId, pstChanDeCfg);

    OM_BbpMasterWrChanIpcUnLock(ulChanId);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterWrChannelDeConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterRdChannelConfig
 ��������  : OM BbpMaster��ͨ��ʹ�����ýӿ�
 �������  : ulPID,
             ulChanId
             pstRdChanCfg
 �������  : ��
 �� �� ֵ  : ���ý��������
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_RD_CHANNEL_CONFIG_STRU *pstRdChanCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstRdChanCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_RD_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    g_astOmBbpMasterRdChCallCnt[ulChanId]++;

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    if (OM_BBPMASTER_YES != OM_BbpMasterRdChanIpcLock(ulChanId))
    {
#ifdef CSDR_FEATURE_ON
        CSDR_MNTN_LogError2(ulPID, ulChanId);
#else
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelConfig OM_BBPMASTER_LOCK_IPC_FAIL: PID: %d, Chan Id: %d\n",
                (int)ulPID, (int)ulChanId);
        /*lint +e534*/
#endif
        return OM_BBPMASTER_LOCK_IPC_FAIL;
    }

    /* ����ͨ���ɹ������¿�ά�ɲ�ͨ����Ϣ */
    OM_BbpMasterRdChanTake(ulPID, ulChanId, pstRdChanCfg);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterRdChannelConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

/*****************************************************************************
 �� �� ��  : OM_BbpMasterRdChannelDeConfig
 ��������  : OM BbpMaster��ͨ��ȥʹ�����ýӿ�
 �������  : ulPID,
             ulChanId
             pstChanDeCfg
 �������  : ��
 �� �� ֵ  : ���ý��������
 ���ú���  :
 ��������  :

  �޸���ʷ      :
  1.��    ��   :
    ��    ��   : l00246515
    �޸�����   : �����ɺ���
*****************************************************************************/
OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg)
{
#if (FEATURE_BBP_MASTER == FEATURE_ON)
    if (OM_BBPMASTER_NULL_PTR == pstChanDeCfg)
    {
        return OM_BBPMASTER_PARA_CFG_NULL;
    }

    if (OM_BBPMASTER_MAX_RD_CHAN_CNT <= ulChanId)
    {
        return OM_BBPMASTER_PARA_CHANID_INVALID;
    }

    if (OM_BBPMASTER_DBG_ON == g_ulOmBbpMasterTest)
    {
        /*lint -e534*/
        LogPrint2("OM_BbpMasterRdChannelDeConfig PID: %d, Chan Id: %d\n", (int)ulPID, (int)ulChanId);
        /*lint +e534*/
    }

    /* �����Unlock��ͳ�� */
    if (0 < g_astOmBbpMasterRdChCallCnt[ulChanId])
    {
        g_astOmBbpMasterRdChCallCnt[ulChanId]--;
    }

    OM_BbpMasterRdChanGive(ulPID, ulChanId, pstChanDeCfg);

    OM_BbpMasterRdChanIpcUnLock(ulChanId);
#else
    /*lint -e534*/
    LogPrint("OM_BbpMasterRdChannelDeConfig: no use now!!!\r\n");
    /*lint +e534*/
#endif

    return OM_BBPMASTER_CONFIG_SUCC;
}

OM_BBPMASTER_VOID OM_BbpMasterChannelInfoShow(OM_BBPMASTER_VOID)
{
#ifndef CSDR_FEATURE_ON
    OM_BBPMASTER_UINT32 i;

    /*lint -e534*/
    for (i = 0; i < OM_BBPMASTER_MAX_WR_CHAN_CNT; i++)
    {
        LogPrint3("OM_BbpMaster Wr Channel %d Call Count: %d, IPC Count: %d\n", (int)i, (int)g_astOmBbpMasterWrChCallCnt[i], (int)g_astOmBbpMasterWrChIpcCnt[i]);
    }

    for (i = 0; i < OM_BBPMASTER_MAX_RD_CHAN_CNT; i++)
    {
        LogPrint3("OM_BbpMaster Rd Channel %d Call Count: %d, IPC Count: %d\n", (int)i, (int)g_astOmBbpMasterRdChCallCnt[i], (int)g_astOmBbpMasterRdChIpcCnt[i]);
    }
    /*lint +e534*/
#endif
    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
