/**
 * @file SRE_libc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������C�⺯��ͷ�ļ��� \n
 */

/**@defgroup SRE_libc libc
 *@ingroup SRE_inspect
*/

#ifndef __SRE_LIBC_H__
#define __SRE_LIBC_H__

#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "sre_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_LIBC == YES)
#ifndef _TOOL_WIN32
/**
 * @ingroup SRE_libc
 * LIBC�����룺����C�⺯��ʱ������Ĳ������Ϸ���
 *
 * ֵ: 0x02003701
 *
 * �������: ����C�⺯��ʱ���豣֤����Ĳ����Ϸ���
 */
#define OS_ERRNO_LIBC_PARA_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x01)

/**
 * @ingroup SRE_libc
 * LIBC�����룺����vsnprintf����snprintf����ʱ����ʽ������ַ������Ȳ�С�����볤��size��
 *
 * ֵ: 0x02003702
 *
 * �������: ����vsnprintf����snprintf����ʱ���豣֤��ʽ������ַ�������С�����볤��size��
 */
#define OS_ERRNO_LIBC_LEN_TOO_LONG                         SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x02)

/**
 * @ingroup SRE_libc
 * LIBC�����룺ע���ӡǰ׺����ʱ������Ĺ��Ӻ���ΪNULL��
 *
 * ֵ: 0x02003703
 *
 * �������: ��֤ע���ӡǰ׺����ʱ����Ĺ��Ӻ�����ΪNULL��
 *
 */
#define OS_ERRNO_LIBC_PRINT_PRIFIX_HOOK_NULL                                   SRE_ERRNO_OS_ERROR(OS_MID_LIBC, 0x03)

/**
* @ingroup  SRE_libc
* @brief ���ɱ������ʽ�������һ���ַ����顣
*
* @par ����:
* ��ap����ʽformat�����һ��ָ����������С���ַ�����str�й��ܡ�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>����ʽ������ַ������ȴ���(size-1)ʱ������OS_INVALID�����ǻ��(size-1)���ַ������str�С�</li>
* <li>str�ռ��С���û���֤����������ڴ�Խ�硣</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* @param  size  [IN] ����#size_t��str�ɽ��ܵ�����ֽ���,��ֹ��������Խ�硣
* @param  format[IN] ����#const char *�������ʽ���ַ���ָ�롣
* @param  ap    [IN] ����#va_list��va_list������
*
* @retval  #OS_INVALID                             ��β��Ϸ������߸�ʽ������ַ������ȴ���(size-1)��
* @retval  #[0, size)                              �ɹ�����str�е��ַ��������ڵ���0������С��size��
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsprintf
*/
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief ���ɱ������ʽ�������һ���ַ����顣
*
* @par ����:
* ��ap����ʽformat������ַ�����str�й��ܡ�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��%�������͸�ʽ��ת����</li>
* <li>str�ռ��С���û���֤����������ڴ�Խ�硣</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* @param  ap    [IN] ����#va_list��va_list������
*
* @retval  #OS_INVALID                             ��β��Ϸ���
* @retval  #��ʽ������ַ���                       �ɹ�����str�е��ַ�����
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int vsprintf(char *str, const char *format, va_list ap);

/**
* @ingroup  SRE_libc
* @brief ���ɱ����������format��ʽ�����ַ�����Ȼ���临�Ƶ�str�С�
*
* @par ����:
* ���ɱ����������format��ʽ�����ַ�����Ȼ���临�Ƶ�ָ����������Сstr�С�
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>����ʽ������ַ������ȴ���(size-1)ʱ������OS_INVALID�����ǻ��(size-1)���ַ������str�С�</li>
* <li>str�ռ��С�Ϳ�ѡ�����ĺϷ������û���֤����������ڴ�Խ��������쳣��</li>
* </ul>
*
* @param  str   [OUT] ����#char *�������ɵĸ�ʽ�����ַ�����������
* @param  size  [IN] ����#size_t��str�ɽ��ܵ�����ֽ���,��ֹ��������Խ�硣
* @param  format[IN] ����#const char *�������ʽ���ַ���ָ�롣
* @param  ...   [IN] ��ѡ������
*
* @retval  #OS_INVALID                             ��β��Ϸ������߸�ʽ������ַ������ȴ���(size-1)��
* @retval  #[0, size)                              �ɹ�����str�е��ַ��������ڵ���0������С��size��
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see vsnprintf
*/
extern int snprintf(char *str, size_t size, const char *format, ...);

#if (OS_OPTION_IO_INTF == YES)

/**< ���Show���� */
#define SHOW_MAX_LEN 321

/**
* @ingroup  SRE_libc
* @brief ��׼�����ӡ��
*
* @par ����:
* ע��ͨ��������Ӻ󣬵��øú�����ʵ�������ӡ��
*
* @attention
* <ul>
* <li>Ŀǰֻ��CORTEX_AXƽ̨֧�ֱ�׼�����ӡ������</li>
* <li>֧��c��d��i��x��s��f��%�������͸�ʽ��ת����</li>
* <li>֧���Ҷ���(��߲�0���߿ո�)�������(�ұ߲��ո�)��</li>
* <li>��֧�����ж��߳��е��ã����û���֤��</li>
* <li>����Balong��Ʒ��֧�ִ�ӡǰ׺(�߳���)������ISP��Ʒ����֧�ִ�ӡǰ׺��</li>
* <li>���֧�ִ�ӡ�ַ���ΪSHOW_MAX_LEN(321)��������������</li>
* <li>���ô˺���ʱ����Ҫ�������ĵ�ǰ�߳����ڵ�ջ�ռ���Դ(��ԼΪ343���ֽ�)��</li>
* <li>��ѡ�����ĺϷ������û���֤��������ɴ�ӡ�쳣��</li>
* </ul>
*
* @param  pcFormat [IN] ����#CHAR *�������ʽ���ַ���ָ�롣
* @param  ...      [IN] ��ѡ������
*
* @retval  #OS_INVALID                             ��β��Ϸ���
* @retval  #[0,SHOW_MAX_LEN)                       �Ѿ������ӡ���ַ����������ӡ�ɹ���
* @par ����:
* <ul><li>sre_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see SRE_Printf
*/
extern int printf(const CHAR *pcFormat, ...);

#endif
#endif

/**< �û���ӡǰ׺��󳤶� */
#define PRINT_PREFIX_MAX_LEN    64

/**
 *@ingroup sre_shell
 *�û���ӡǰ׺�Ĺ��Ӻ������Ͷ��塣
 */
typedef UINT32 (*PRINT_PREFIX_FUNC)(CHAR *pcBuff);

/**
 *@ingroup sre_shell
 *@brief �û�ע���ӡǰ׺���ӡ�
 *
 *@par ����:
 *ע���û���ӡǰ׺�Ĺ��ӣ�OS��buffer�����û������û�ͨ��ע��Ĺ��ӽ��и�ʽ����
 *@attention
 * <ul>
 * <li>�����ע��ù���ʱ�����һ��ע��Ĺ�����Ч��
 * <li>ע��Ĺ��Ӻ�������Ϊ�գ���һ��ע�ṳ�Ӻ���������ͨ��ע��պ�������ȡ����
 * <li>������Ӻ����ĳ���buffer��Ϊ���ַ�����OS��buffer�ַ���������Ϊ��ӡǰ׺��ӡ��
 * <li>������Ӻ����ĳ���bufferΪ���ַ�����OS�����ӷ���ֵ��16���ƴ�ӡ��
 * <li>�û���֤���Ӻ�������buffer���Ȳ�����64�ֽڡ�
 * </ul>
 *
 *@param pfnHook [IN] ����#PRINT_PREFIX_FUNC�����Ӻ�����
 *
 *@retval #OS_ERRNO_SHELL_PRINT_PRIFIX_HOOK_NULL 0x02002d3b�����Ӻ���Ϊ��
 *@retval #SRE_OK 0x00000000���ɹ����ء�
 *
 *@par ����:
 *sre_libc.h���ýӿ��������ڵ�ͷ�ļ�
 *@since RTOSck V100R005C00
 *@see ��
 */
extern UINT32 SRE_PrintPrefixRegHook(PRINT_PREFIX_FUNC pfnHook);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__SRE_LIBC_H__

