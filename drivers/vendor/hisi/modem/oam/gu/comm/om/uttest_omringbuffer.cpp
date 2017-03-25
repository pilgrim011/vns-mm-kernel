#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include <stdio.h>
#include <stdlib.h>

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
extern "C"
{
#endif
    extern unsigned int uttest_OM_RingBufferCreate_case1(void);
    extern unsigned int uttest_OM_RingBufferCreate_case2(void);
    extern unsigned int uttest_OM_RingBufferCreate_case3(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case1(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case2(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case3(void);
    extern unsigned int uttest_OM_RingBufferCreateEx_case4(void);
    extern unsigned int uttest_OM_RingBufferNBytes_case1(void);
    extern unsigned int uttest_OM_RingBufferFreeBytes_case1(void);
    extern unsigned int uttest_OM_RingBufferIsFull_case1(void);
    extern unsigned int uttest_OM_RingBufferIsFull_case2(void);
    extern unsigned int uttest_OM_RingBufferIsEmpty_case1(void);
    extern unsigned int uttest_OM_RingBufferGetReserve_case1(void);
    extern unsigned int uttest_OM_RingBufferGetReserve_case2(void);
    extern unsigned int uttest_OM_RingBufferRemove_case1(void);
    extern unsigned int uttest_OM_RingBufferRemove_case2(void);
    extern unsigned int uttest_OM_RingBufferRemove_case3(void);
    extern unsigned int uttest_OM_RingBufferPut_case1(void);
    extern unsigned int uttest_OM_RingBufferPut_case2(void);
    extern unsigned int uttest_OM_RingBufferPut_case3(void);
    extern unsigned int uttest_OM_RingBufferPut_case4(void);
    extern unsigned int uttest_OM_RingBufferPut_case5(void);

    extern void *__kmalloc(unsigned int ulSize, unsigned int ulFlag);
    extern void OM_RealMemCopy( const char *source, char *destination, int nbytes );
    extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif


/*******************************************************************
�����������      : OM_RingBufferCreate_001
������������      : �ڴ�����ʧ����
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2012-08-27
  ��   ��  : x51137
  �޸����� : v9r1MSP��ֺͿ�ά�ɲ⿪����Ŀ�޸ĺ���
*******************************************************************/
TEST(OM_RingBufferCreate1, UT)
{
	// ���ñ��⺯��
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(once());

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferCreate_002
������������      : �����ɹ�
Ԥ�ڽ��          : �������ؿ��ƽṹ��
�޸���ʷ          :
1.��   ��  : 2012-08-27
  ��   ��  : x51137
  �޸����� : v9r1MSP��ֺͿ�ά�ɲ⿪����Ŀ�޸ĺ���
*******************************************************************/
TEST(OM_RingBufferCreate2, UT)
{
	// ���ñ��⺯��
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferCreate_003
������������      : Buffer������Ϣ�Ѿ�����
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2012-08-27
  ��   ��  : x51137
  �޸����� : v9r1MSP��ֺͿ�ά�ɲ⿪����Ŀ�޸ĺ���
*******************************************************************/
TEST(OM_RingBufferCreate3, UT)
{
	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreate_case3());
}

/*******************************************************************
�����������      : OM_RingBufferCreateEx_001
������������      : ����ָ��ΪNULL
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2013-09-03
  ��   ��  : d00212987
  �޸����� : Error Log�ϱ��͹���ģʽ��Ŀ��������
*******************************************************************/
TEST(OM_RingBufferCreateEx1, UT)
{
	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case1());
}

/*******************************************************************
�����������      : OM_RingBufferCreateEx_002
������������      : ����ռ����8k
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2013-09-03
  ��   ��  : d00212987
  �޸����� : Error Log�ϱ��͹���ģʽ��Ŀ��������
*******************************************************************/
TEST(OM_RingBufferCreateEx2, UT)
{
	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case2());
}

/*******************************************************************
�����������      : OM_RingBufferCreateEx_003
������������      : Buffer������Ϣ�Ѿ�����
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2013-09-03
  ��   ��  : d00212987
  �޸����� : Error Log�ϱ��͹���ģʽ��Ŀ��������
*******************************************************************/
TEST(OM_RingBufferCreateEx3, UT)
{
    // ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case3());
}

/*******************************************************************
�����������      : OM_RingBufferCreateEx_004
������������      : ��������buffer�ɹ�
Ԥ�ڽ��          : ��������NULL
�޸���ʷ          :
1.��   ��  : 2013-09-03
  ��   ��  : d00212987
  �޸����� : Error Log�ϱ��͹���ģʽ��Ŀ��������
*******************************************************************/
TEST(OM_RingBufferCreateEx4, UT)
{
    // ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferCreateEx_case4());
}

/*******************************************************************
�����������      : OM_RingBufferNBytes_001
������������      : ����buffer���ֽ���
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferNBytes1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferNBytes_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferNBytes_001
������������      : ����buffer�п����ֽ���
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferFreeBytes1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferFreeBytes_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferIsFull_001
������������      : ����buffer������
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferIsFull1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferIsFull_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferIsFull2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsFull_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferIsEmpty_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferIsEmpty1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferIsEmpty_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferIsEmpty_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferGetReserve1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

    MOCKER(OM_RealMemCopy)
        .expects(exactly(2));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferGetReserve_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferIsEmpty_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferGetReserve2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(2));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferGetReserve_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferRemove_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferRemove1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferRemove_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferRemove2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferRemove_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferRemove3, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferRemove_case3());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferPut_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferPut1, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
	    .expects(once());

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case1());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferPut_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferPut2, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
	    .expects(exactly(2));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case2());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferPut_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferPut3, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case3());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferGet_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferGet4, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case4());

	GlobalMockObject::reset();
}

/*******************************************************************
�����������      : OM_RingBufferPut_001
������������      : ����buffer��δ��
Ԥ�ڽ��          : ���������ֽ���
�޸���ʷ          :
1.��   ��  : 2013-11-26
	��   ��  : J00168360
	�޸����� :
*******************************************************************/
TEST(OM_RingBufferGet5, UT)
{
	MOCKER(__kmalloc)
	    .stubs()
		.will(returnValue((void*)0x5a5a5a5a));

	MOCKER(OM_RealMemCopy)
		.expects(exactly(1));

	// ִ�м��
	EXPECT_EQ(VOS_OK, uttest_OM_RingBufferPut_case5());

	GlobalMockObject::reset();
}
