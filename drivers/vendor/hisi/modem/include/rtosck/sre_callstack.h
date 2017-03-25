/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_callstack.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ�����ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_hw Ӳ��֧��
   *@ingroup SRE_kernel
 */

#ifndef _SRE_CALLSTACK_H
#define _SRE_CALLSTACK_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_callstack
 *  ����ջ�����Ϣ�����룺��ȡ��������ջ����Ĳ���ΪNULL
 *
 * ֵ: 0x02003501
 *
 * �������: ��ȷ������Ĳ�����ΪNULL
 */
#define OS_ERRNO_CALLSTACK_PTR_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_CALLSTACK, 0x01)

/**
 * @ingroup SRE_callstack
 *  Ӳ�������Ϣ�����룺��ȡ��������ջ����������ò����Ƿ�
 *
 * ֵ: 0x02003502
 *
 * �������: ��ȷ������������ò�������0��С��10
 */
#define OS_ERRNO_CALLSTACK_MAX_NUM_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_CALLSTACK, 0x02)

/**
 * @ingroup SRE_callstack
 *  ����ջ�����Ϣ�����룺���overlay�ε�unwind��Ϣʱ���ε���ʼ�������ַ�Ƿ�
 *
 * ֵ: 0x02003503
 *
 * �������: ��ȷ������Ķν�����ַ������ʼ��ַ
 */
#define OS_ERRNO_CALLSTACK_PARA_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_CALLSTACK, 0x03)



#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_callstack
 * @brief ��ȡ���ߵ���ջ��Ϣ
 *
 * @par ����:
 * ��ȡ��ǰ���������쳣ʱ�����ĵ���ջ��Ϣ��
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * <li>֧����ͨ����(ϵͳ��������)���쳣���ӵ���(ϵͳ�����쳣)��ǰ�߻�ȡ��Ϊ��ǰ�����ĵ���ջ��Ϣ�����߻�ȡ��Ϊ�쳣ʱ�����ĵ���ջ��Ϣ��</li>
 * <li>�������洢��������PC��˳��Ϊ����ײ㺯�������ϲ㺯����</li>
 * </ul>
 *
 * @param  puwMaxNum [IN/OUT] ����#UINT32 *�������ò���������/������������룺������puwPCList�����ɵ�Ԫ�ظ����������ʵ�ʽ������ĺ������ò�����
 * @param  puwPCList [OUT] ����#UINT32 *���洢����PC��Ϣ�Ļ������׵�ַ��������д�������ú�����PC��
 *
 * @retval #OS_ERRNO_CALLSTACK_PTR_NULL         0x02003501����ȡ����ջ��Ϣʱ������Ĳ���ָ��ΪNULL��
 * @retval #OS_ERRNO_CALLSTACK_MAX_NUM_VALID    0x02003502����ȡ����ջ��Ϣʱ������������ò�������0���ߴ���10��
 * @retval #SRE_OK                              0x00000000����ȡ����ջ��Ϣ�ɹ���
 * @par ����:
 * <ul><li>sre_callstack.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_GetCallStack(UINT32 *puwMaxNum, UINT32 *puwPCList);

/**
 * @ingroup  SRE_UnwindTableAdd
 * @brief ���overlay�ε�unwind��Ϣ��OS��
 *
 * @par ����:
 * ���overlay�ε�unwind��Ϣ��OS��
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * <li>ֻ֧�����һ��overlay�������ʼ�ͽ�����ַ����֧����Ӷ������ε��������һ��Ϊ׼��</li>
 * <li>ʹ���߱�֤overlay�ε�����ε�ַΪִ�о���Ĵ��ַ��</li>
 * </ul>
 *
 * @param  uwUnwindStart [IN]  ����# UINT32��unwind�ε���ʼ��ַ����.ARM.exidx�ε���ʼ��ַ
 * @param  uwUnwindEnd   [IN]  ����# UINT32��unwind�εĽ�����ַ(��ʼ��ַ+��С)����.ARM.exidx�εĽ�����ַ
 * @param  uwTextStart   [IN]  ����# UINT32������ε���ʼ��ַ
 * @param  uwTextEnd     [IN]  ����# UINT32������εĽ�����ַ(��ʼ��ַ+��С)
 *
 * @retval #OS_ERRNO_CALLSTACK_PARA_INVALID     0x02003503�����overlay�ε�unwind��Ϣʱ���ε���ʼ�������ַ�Ƿ���
 * @retval #SRE_OK                              0x00000000����Ϣ��ӳɹ���
 * @par ����:
 * <ul><li>sre_callstack.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_UnwindTableAdd(UINT32 uwUnwindStart, UINT32 uwUnwindEnd, UINT32 uwTextStart, UINT32 uwTextEnd);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */



