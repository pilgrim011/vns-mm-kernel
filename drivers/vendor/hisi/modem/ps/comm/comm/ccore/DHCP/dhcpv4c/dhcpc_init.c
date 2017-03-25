/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpc_init.c
  �� �� ��   : ����
  ��    ��   : yuqingping(25027)
  ��������   : 2002��11��21��
  ����޸�   :
  ��������   : dhcpcģ��������ʼ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2002��11��21��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ļ�

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

RELTMR_T g_ulDhcpcDftTimerID = 0;
RELTMR_T g_ulFreeDhcpcCtrlBlkMemTimerId = 0;


/*****************************************************************************
 �� �� ��  : DHCPC_CtrlBlockAgingTimerOut
 ��������  : dhcp���ƿ��ϻ���ʱ����ʱ����
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��02��08��
    ��    ��   : jiahuidong
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_CtrlBlockAgingTimerOut( VOID* pvArg )
{
    DHCPC_SendSelfPdpCheckMsg(1);
    return;
}



/*****************************************************************************
 �� �� ��  : DHCPC_DftSendCtrlBlockTimerOut
 ��������  : dhcp dft�ϱ����Ϳ��ƿ鶨ʱ��
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��02��08��
    ��    ��   : jiahuidong
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_DftSendCtrlBlockTimerOut()
{
    ULONG    i = 0;
    ULONG ulNum = 0;

    for ( i = 0; i < DHCPC_MAX_CTRLBLKNUM; i++ )
    {
        if ( DHCPC_CTRLBLK_IDLE == g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg )
        {
            ulNum++;
        }
    }

    *g_DFT_pulDHCPSendCBNum = ulNum;
    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_Tmr_Init
 ��������  :DHCPCģ�鴴����ʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1.��      ��   : 2009��07��04��
    ��      ��   : jiahuidong00142544
    �޸�����   : �����ɺ���
*****************************************************************************/
ULONG DHCPC_Tmr_Init( VOID )
{
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_RENEW_TIMER_LENGTH,/*10s*/
                           ( VOID ( * )( VOID * ) )DHCPC_TimerOut,
                           &g_ulTimerRenewType,
                           &g_ulDhcpcRenewTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_RETRANS_TIMER_LENGTH,/*0.1s*/
                           ( VOID ( * )( VOID * ) )DHCPC_TimerOut,
                           &g_ulTimerRetransType,
                           &g_ulDhcpcRetransTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*����dhcp���ƿ��ϻ���ʱ��*/
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_CTRL_BLOCK_AGING_TIMER_INTERVAL,
                           ( VOID ( * )( VOID * ) )DHCPC_CtrlBlockAgingTimerOut,
                           NULL,
                           &g_ulDhcpcCtrlBlockAgingTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*����dft �ϱ� dhcp���Ϳ��ƿ鶨ʱ��*/
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_DFTCB_TIMER_INTERVAL,
                           ( VOID ( * )( VOID * ) )DHCPC_DftSendCtrlBlockTimerOut,
                           NULL,
                           &g_ulDhcpcDftTimerID,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /* BEGIN: Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/23 */
    if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_FREE_SCAN_TIMER_LENGTH,
                           ( VOID ( * )( VOID * ) )DHCPC_FreeDhcpcCtrlBlkMem,
                           NULL,
                           &g_ulFreeDhcpcCtrlBlkMemTimerId,
                           VOS_TIMER_LOOP ) )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    /* END:   Added for PN:DHCPv6���� by tianyang 00144555, 2012/7/23 */

    /* zhangjinquan 00175135 DHCPv6���� 2012-07-23 start */
    /* ����Сʱ����ɨ�账��ʱ�� */
    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                            DHCPC_MSG_TYPE_TIMER,
                            DHCPC_MILLSECONDS_PER_SECOND, /* 1�� */
                            (VOID (*)(VOID *))DHCPC_HourListTimerOut,
                            NULL,
                            &g_ulDHCPCHourTimerId,
                            VOS_TIMER_LOOP))
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /* �����뼶����ɨ�账��ʱ�� */
    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                            DHCPC_MSG_TYPE_TIMER,
                            DHCPC_SECOND_TIMER_INTERVAL, /* 200���� */
                            (VOID (*)(VOID *))DHCPC_SecondListTimerOut,
                            NULL,
                            &g_ulDHCPCSecondTimerId,
                            VOS_TIMER_LOOP))
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    /* zhangjinquan 00175135 DHCPv6���� 2012-07-23 end   */

    /* Added start by y00170683 at 2012-09-10 UGW10.0---SEQNUM�ϻ�����---DS.UGWV9R10C0.DHCPv6.DHCP.0024֧��TIDʹ�������ά�� */
    if (PGP_Timer_Create(DHCPC_SELF_CSI,
                           DHCPC_MSG_TYPE_TIMER,
                           DHCPC_AGEING_SEQNUM_TIMER_LENGTH,
                           (VOID (*)(VOID *))DHCPV6C_AgeingSeqNum,
                           NULL,
                           &g_ulDhcpcSeqnumAgingTimerID,
                           VOS_TIMER_LOOP))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    /* Added end by y00170683 at 2012-09-10 UGW10.0---SEQNUM�ϻ�����---DS.UGWV9R10C0.DHCPv6.DHCP.0024֧��TIDʹ�������ά�� */

    return VOS_OK;
}

