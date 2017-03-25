



#ifndef __CNAS_XSD_FSM_REDIR_TBL_H__
#define __CNAS_XSD_FSM_REDIR_TBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern NAS_STA_STRU                                         g_astCnasXsdRedirStaTbl[];

/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define CNAS_XSD_GetRedirStaTbl()                          (g_astCnasXsdRedirStaTbl)


/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


enum CNAS_XSD_REDIR_STA_ENUM
{
    /* System redirection indication init*/
    CNAS_XSD_REDIR_STA_INIT                   = 0x00,

    /* Waiting for CAS system sync confirmation*/
    CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF                   = 0x01,

    /* Waiting for CAS system sync stop confirmation */
    CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF                   = 0x02,

     /* Waiting for CAS system sync confirmation with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS                   = 0x03,

    /* Waiting for CAS system sync stop confirmation with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS                   = 0x04,

    /* Waiting for CAS OHM indication */
    CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND                   = 0x05,

    /* Waiting for CAS OHM indication after camp on with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND                   =  0x06
};
typedef VOS_UINT32 CNAS_XSD_REDIR_STA_ENUM_UINT32;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern NAS_FSM_DESC_STRU * CNAS_XSD_GetRedirFsmDescAddr(VOS_VOID);
extern VOS_UINT32 CNAS_XSD_GetRedirStaTblSize(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasXsdFsmRedirTbl.h */
