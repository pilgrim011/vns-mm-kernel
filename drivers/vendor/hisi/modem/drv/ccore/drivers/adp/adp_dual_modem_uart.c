/*************************************************************************
*   ��Ȩ����(C) 2008-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  adp_uart.c
*
*   ��    �� :  z00265007
*
*   ��    �� :  v7r2Ϊ������v7r1�ӿڵ�һ�µ������ļ�
*
*   �޸ļ�¼ :  2013��2��1��  v1.00  y00184236  ����
*************************************************************************/

#include "mdrv_dual_modem.h"
#include "osl_types.h"

#ifndef CONFIG_BALONG_MDM_UART   /* ��׮ */

int uart_core_recv_handler_register(UART_CONSUMER_ID uPortNo, pUARTRecv pCallback)
{
	return 0;

}
int uart_core_send(UART_CONSUMER_ID uPortNo, unsigned char * pDataBuffer, unsigned int uslength)
{
	return 0;

}
int bsp_dual_modem_init(void)
{
	return 0;
}
int bsp_dual_modem_drv_init(void)
{
	return 0;
}

#endif

