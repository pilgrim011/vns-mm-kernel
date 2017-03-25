/**
 * @file sre_symbol_api.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������ű�ģ��Ķ���ͷ�ļ� \n
 */

/**
 * @defgroup SRE_symbol ���ű�
 * @ingroup SRE_inspect
*/

#ifndef _SRE_SYMBOL_API_H
#define _SRE_SYMBOL_API_H

#include "sre_typedef.h"
#include "sre_symbol.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_symbol
 * @brief ���ű�
 *
 * @par ����:
 * ��������ķ�����pcName����ȡ��Ӧ�ķ��ŵ�ַ��
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܡ�</li>
 * </ul>
 *
 * @param  pcName   [IN] ����#CHAR *������ķ�������
 * @param  puwAddr  [OUT] ����#UINT32 *��������ŵ�ַ��
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_NAME_ERROR           0x02002904���ڷ��ű���û�в��ҵ���������ƥ��ķ��Žڵ㡣
 * @retval #OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL         0x0200290b�������ָ�����ΪNULL��
 * @retval #SRE_OK                                    0x00000000����ȡ���ŵ�ַ�ɹ���
 * @par ����:
 * <ul><li>sre_symbol.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_SymFindAddrByName(CHAR *pcName, UINT32 *puwAddr);

/**
 * @ingroup  SRE_symbol
 * @brief ���ű�
 *
 * @par ����:
 * ��������ķ��ŵ�ַ����ȡ��Ӧ�ķ�������
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܡ�</li>
 * </ul>
 *
 * @param  pSymAddr  [IN]  ����#VOID *������ķ��ŵ�ַ��
 * @param  pcName    [OUT] ����#CHAR **������������������
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_ADDR_ERROR           0x02002903���ڷ��ű���û�в��ҵ���ַƥ��ķ��Žڵ㡣
 * @retval #OS_ERRNO_SYMBOL_PARA_POINT_NULL           0x02002900�������ָ�����ΪNULL��
 * @retval #SRE_OK                                    0x00000000����ȡ���ŵ�ַ�ɹ���
 * @par ����:
 * <ul><li>sre_symbol.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_SymFindNameByAddr(VOID *pSymAddr, CHAR **ppcName);


/**
 * @ingroup  SRE_SymbolTableAdd
 * @brief ��ӷ��ű���Ϣ��OS��
 *
 * @par ����:
 * ��ӷ��ű���Ϣ��OS��
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * <li>ֻ֧������һ��overlay����ʼ�ͽ�����ַ����֧���ö����</li>
 * <li>�ýӿڶ�ε��������һ��Ϊ׼��</li>
 * </ul>
 *
 * @param  pstSymbolNode    [IN]  ����# OS_SYMBOL_NODE_S*�����ű�ṹ���������ʼ��ַ
 * @param  uwSymbolNum      [IN]  ����# UINT32�����ű�ṹ�����
 * @param  uwOverlayStart   [IN]  ����# UINT32��overlay�ε���ʼ��ַ
 * @param  uwOverlayEnd     [IN]  ����# UINT32��overlay�εĽ�����ַ(��ʼ��ַ+��С)
 *
 * @retval #OS_ERRNO_SYMBOL_PARA_POINT_NULL     0x02002900�����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_SYMBOL_PARA_INVALID        0x0200290c����ηǷ�
 * @retval #SRE_OK                              0x00000000����ȡ����ջ��Ϣ�ɹ���
 * @par ����:
 * <ul><li>sre_callstack.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_SymbolTableAdd(OS_SYMBOL_NODE_S* pstSymbolNode, UINT32 uwSymbolNum, UINT32 uwOverlayStart, UINT32 uwOverlayEnd);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYMBOL_API_H */

/**
 * History:
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

