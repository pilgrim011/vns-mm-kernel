/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : BST_SRV_AsEvnt.cpp
  �� �� ��   : ����
  ��    ��   : d00173029
  ��������   : 2014��07��01��
  ����޸�   :
  ��������   : ������¼���������ش��������Ա����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��01��
    ��    ��   : d00173029
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_AsEvnt.h"
#include "BST_SRV_Event.h"
#include "BST_DBG_MemLeak.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_ASEVNT_CPP
/*lint +e767*/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/******************************************************************************
  4 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : BST_SRV_CAsRcver
 ��������  : ���캯��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_SRV_CAsRcver::BST_SRV_CAsRcver( BST_OS_MBX_T *pstRcverMbx )
    : m_pstRcvMbox( pstRcverMbx )
{
    BST_SRV_CAsEvt                     *pcAsMng;
    pcAsMng                             = BST_SRV_CAsEvt::GetInstance();
    m_ulEventFlagSet                    = BST_AS_EVT_NONE;
    BST_ASSERT_NULL( pcAsMng );
    pcAsMng->Attach( this );
}

/*****************************************************************************
 �� �� ��  : ~BST_SRV_CAsRcver
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_SRV_CAsRcver::~BST_SRV_CAsRcver( BST_VOID )
{
    BST_SRV_CAsEvt          *pcAsMng;

    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    BST_ASSERT_NULL( pcAsMng );
    pcAsMng->Detach( this );
}

/*****************************************************************************
 �� �� ��  : RegAsNotice
 ��������  : ע�������¼�
 �������  : enEvent:�¼���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_SRV_CAsRcver::RegAsNotice( BST_AS_EVT_ENUM_UINT32 enEvent )
{
    if ( BST_SRV_IsValidAsEvent( enEvent ) )
    {
        BST_SRV_SetAsFlag( m_ulEventFlagSet, enEvent );
    }
}

/*****************************************************************************
 �� �� ��  : DelEvent
 ��������  : ɾ��������¼�
 �������  : enEvent:�¼���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_SRV_CAsRcver::DelEvent( BST_AS_EVT_ENUM_UINT32 enEvent )
{
    if ( BST_SRV_IsValidAsEvent( enEvent ) )
    {
        BST_SRV_ClrAsFlag( m_ulEventFlagSet, enEvent );
    }
}

/*****************************************************************************
 �� �� ��  : GetEventSet
 ��������  : ��ȡ������¼���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������¼���
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_AS_EVT_SET_UINT32 BST_SRV_CAsRcver::GetEventSet( BST_VOID )
{
    return m_ulEventFlagSet;
}

/*****************************************************************************
 �� �� ��  : GetInstance
 ��������  : ��ȡBST_SRV_CAsEvtʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : BST_SRV_CAsEvtʵ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_SRV_CAsEvt *BST_SRV_CAsEvt::GetInstance( BST_VOID )
{
    static BST_SRV_CAsEvt *pcAsEvtPtr   = BST_NULL_PTR;
    if ( BST_NULL_PTR == pcAsEvtPtr )
    {
        pcAsEvtPtr = new BST_SRV_CAsEvt();
    }
    return pcAsEvtPtr;
}

/*****************************************************************************
 �� �� ��  : AsEventRcv
 ��������  : ���������¼�
 �������  : enEvent: �¼�
             ulLength: ��������
             pvData:�¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_SRV_CAsEvt::Receive(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvNextIdx;
    BST_AS_EVT_SET_UINT32       ulEventFlags;

    if ( !BST_SRV_IsValidAsEvent( enEvent ) )
    {
        return;
    }
    Save( enEvent, ulLength, pvData );
    for( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU * )lstFirst( &m_stAsRcverList );
         BST_NULL_PTR != pstRcvIdx;
         pstRcvIdx = pstRcvNextIdx )
    {
        pstRcvNextIdx           = ( BST_SRV_ASRCVER_NODE_STRU * )
                                  lstNext( ( NODE * )pstRcvIdx );
        ulEventFlags            = pstRcvIdx->pRcver->GetEventSet();

        if ( BST_SRV_AsEvntFlagUsed( ulEventFlags, enEvent ) )
        {
            BST_SRV_ApiSendAsEvent( pstRcvIdx->pRcver, enEvent, ulLength, pvData );
        }
    }
}

BST_VOID BST_SRV_CAsEvt::Forward(
    BST_SRV_CAsRcver       *pcAsRcver,
    BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32          ulLength,
        BST_VOID           *pvData )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvNextIdx;
    BST_AS_EVT_SET_UINT32       ulEventFlags;

    if ( !BST_SRV_IsValidAsEvent( enEvent ) )
    {
        return;
    }
    if ( BST_NULL_PTR == pcAsRcver)
    {
        return;
    }
    for( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU * )lstFirst( &m_stAsRcverList );
         BST_NULL_PTR != pstRcvIdx;
         pstRcvIdx = pstRcvNextIdx )
    {
        pstRcvNextIdx           = ( BST_SRV_ASRCVER_NODE_STRU * )
                                  lstNext( ( NODE * )pstRcvIdx );
        if ( pcAsRcver != pstRcvIdx->pRcver )
        {
            continue;
        }
        ulEventFlags            = pstRcvIdx->pRcver->GetEventSet();
        if ( BST_SRV_AsEvntFlagUsed( ulEventFlags, enEvent ) )
        {
            pstRcvIdx->pRcver->AsEventCallback( enEvent, ulLength, pvData );
            break;
        }
        else
        {
            return;
        }
    }
}

/*****************************************************************************
 �� �� ��  : SaveAsMsg
 ��������  : ���������¼�
 �������  : enEvent: �¼�
             ulLength: ��������
             pvData:�¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_SRV_CAsEvt::Save(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulBufLen,
    BST_VOID               *pvData )
{
}
/*****************************************************************************
 �� �� ��  : Inquire
 ��������  : �¼���ѯ
 �������  : enEvent: �¼�
             ulLength: ��������
             pvData:�¼�����
 �������  : ��
 �� �� ֵ  : BST_BOOL
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_BOOL BST_SRV_CAsEvt::Inquire(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulBufLen,
    BST_VOID               *pvData )
{
    return BST_FALSE;
}

/*****************************************************************************
 �� �� ��  : Attach
 ��������  : ���Ž�����¼�������
 �������  : pcRcver: ������¼�������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -e429*/
BST_VOID BST_SRV_CAsEvt::Attach( BST_SRV_CAsRcver *pcRcver )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_ASSERT_NULL( pcRcver );
    pstRcvIdx                   = ( BST_SRV_ASRCVER_NODE_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_SRV_ASRCVER_NODE_STRU ) );
    BST_ASSERT_NULL( pstRcvIdx );
    pstRcvIdx->pRcver           = pcRcver;
    lstAdd( &m_stAsRcverList, (NODE *)pstRcvIdx );
}
/*lint +e429*/
/*****************************************************************************
 �� �� ��  : Detach
 ��������  : ȥ���Ž�����¼�������
 �������  : pcRcver: ������¼�������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -e438*/
BST_VOID BST_SRV_CAsEvt::Detach( BST_SRV_CAsRcver *pcRcver )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_ASSERT_NULL( pcRcver );

    for ( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU *)lstFirst( &m_stAsRcverList );
          BST_NULL_PTR != pstRcvIdx;
          pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU *)lstNext( (NODE *) pstRcvIdx ) )
    {
        if ( pstRcvIdx->pRcver == pcRcver )
        {
            lstDelete( &m_stAsRcverList, (NODE *)pstRcvIdx );
            BST_OS_FREE( pstRcvIdx );
            break;
        }
    }
}
/*lint +e438*/
/*****************************************************************************
 �� �� ��  : BST_SRV_CAsEvt
 ��������  : ���캯��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_SRV_CAsEvt::BST_SRV_CAsEvt( BST_VOID )
{
    lstInit( &m_stAsRcverList );
}

/*****************************************************************************
 �� �� ��  : ~BST_SRV_CAsEvt
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_SRV_CAsEvt::~BST_SRV_CAsEvt( BST_VOID )
{
    BST_RLS_LOG("BST_SRV_CAsEvt destructor exception!");
}

/*****************************************************************************
 �� �� ��  : BST_SRV_RcvAsEvent
 ��������  : ����AS�¼�
 �������  : enAsEvent:�¼�ID
             ulLength:��������
             pvData:��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_UINT32 BST_SRV_RcvAsEvent(
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    if ( BST_NULL_PTR == pcAsMng )
    {
        return 0;
    }
    pcAsMng->Receive( enAsEvent, ulLength, pvData );
    return ulLength;
}

