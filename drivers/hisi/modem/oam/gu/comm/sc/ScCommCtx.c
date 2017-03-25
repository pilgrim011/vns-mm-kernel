

/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ScCommCtx.c
  �� �� ��   : ����
  ��    ��   : d00212987
  ��������   : 2015��08��10��
  ����޸�   :
  ��������   : SC CONTEXT�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��10��
    ��    ��   : d00212987
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ScCommCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_SC_CONTEXT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
 ȫ�ֱ�����    : g_stScCtx
 ȫ�ֱ���˵��  : SC����������
 1.��    ��   : 2012��04��19��
   ��    ��   : w00184875
   �޸�����   : �½�
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            ".\\yaffs0\\SC\\Pers\\CKFile.bin",
            ".\\yaffs0\\SC\\Pers\\DKFile.bin",
            ".\\yaffs0\\SC\\Pers\\AKFile.bin",
            ".\\yaffs0\\SC\\Pers\\PIFile.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.bin",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.bin"
        },
        {
            ".\\yaffs0\\SC\\Pers\\CKSign.hash",
            ".\\yaffs0\\SC\\Pers\\DKSign.hash",
            ".\\yaffs0\\SC\\Pers\\AKSign.hash",
            ".\\yaffs0\\SC\\Pers\\PISign.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I0.hash",
            ".\\yaffs0\\SC\\Pers\\ImeiFile_I1.hash"
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        ".\\SecureDataA.bin",
        ".\\SecureDataC.bin"
    }
};
#else
static SC_CONTEXT_STRU                  g_stScCtx = {
    /* SC_COMM_GLOBAL_VAR */
    {
        {
            "/mnvm2:0/SC/Pers/CKFile.bin",
            "/mnvm2:0/SC/Pers/DKFile.bin",
            "/mnvm2:0/SC/Pers/AKFile.bin",
            "/mnvm2:0/SC/Pers/PIFile.bin",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.bin",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.bin",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.bin",
#endif
        },
        {
            "/mnvm2:0/SC/Pers/CKSign.hash",
            "/mnvm2:0/SC/Pers/DKSign.hash",
            "/mnvm2:0/SC/Pers/AKSign.hash",
            "/mnvm2:0/SC/Pers/PISign.hash",
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I2.hash",
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
            "/mnvm2:0/SC/Pers/ImeiFile_I1.hash",
#endif
#else
            "/mnvm2:0/SC/Pers/ImeiFile_I0.hash",
#endif
        }
    },
    /* SC_FAC_GLOBAL_VAR */
    {
        SC_AUTH_STATUS_UNDO,
        "",
        VOS_FALSE,
        ""
    },
    /* SC_APSEC_GLOBAL_VAR */
    {
        0,
        {0, 0},
        0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        SC_SECURITY_FILE_STATE_IDEL,
        {
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},
            {0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR},{0,VOS_NULL_PTR}
        },
        "/mnvm2:0/SC/Apsec/SecureDataA.bin",
        "/mnvm2:0/SC/Apsec/SecureDataC.bin"
    }
};

#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : SC_CTX_GetScCtxAddr
 ��������  : ��ȡ��ǰSC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰSC��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��04��20��
   ��    ��   : w00184875
   �޸�����   : �����ɺ���

*****************************************************************************/
SC_CONTEXT_STRU* SC_CTX_GetScCtxAddr(VOS_VOID)
{
    return &(g_stScCtx);
}

/*****************************************************************************
 �� �� ��  : SC_CTX_GetCommGlobalVarAddr
 ��������  : ��ȡSC����������ȫ�ֱ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SC����������ȫ�ֱ���������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��19��
    ��    ��   : w00184875
    �޸�����   : �����ɺ���
*****************************************************************************/
SC_COMM_GLOBAL_STRU*  SC_CTX_GetCommGlobalVarAddr( VOS_VOID )
{
    return &g_stScCtx.stScCommGlobalVar;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

