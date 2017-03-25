/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallFacilityDecode.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��9��20��
  ����޸�   : 2007��9��20��
  ��������   : ʵ��CS������ص�API�ӿں���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Taf_Ssa_DecodeDef.h"
#include "MnCallFacilityDecode.h"
#include "MnCallFacilityEncode.h"
#include "MnComm.h"
#include "MnCall.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/


/*****************************************************************************
  4 �궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_FACILITY_ENCODE_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/
/*****************************************************************************
  5 ��������
*****************************************************************************/
MN_CALL_SS_ID_TABLE_STRU    g_stCallInvokeIdTable[MN_CALL_MAX_INVOKE_NUM];

/*lint -save -e958 */

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_SsCdArgEncode
 ��������  : �������ƫת����
 �������  : pArg - Ҫ����ĺ���ƫת����
 �������  : pDest - �����Ŀ�Ļ���
 �� �� ֵ  : ���������ĳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsCdArgEncode(
    const MN_CALL_SS_CD_ARG_STRU        *pstArg,
    VOS_UINT8                           *pucDest
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulArgLen = 0;

    if ((0 == pstArg->ucNumberLen) ||
        (pstArg->ucNumberLen > MN_CALL_SS_CD_NUM_LEN) ||
        (pstArg->ucSubAddrLen > MN_CALL_SS_CD_SUB_ADDR_LEN))
    {
        MN_WARN_LOG("MN_CALL_SsCdArgEncode:Bad parameter for call deflecting");
        return 0;
    }

    /*lint -e961*/
    /* ����callDeflectionArg�ṹ */
    pucDest[ulArgLen++] = 0x30;          /* tag of SEQUENCE */
    pucDest[ulArgLen++] = 0;             /* length, �����д */

    /* ����deflectedToNumber */
    pucDest[ulArgLen++] = 0x80;
    pucDest[ulArgLen++] = pstArg->ucNumberLen;
    for (i=0; i<pstArg->ucNumberLen; i++)
    {
        pucDest[ulArgLen++] = pstArg->aucNumber[i];
    }

    /* ����deflectedToSubaddress */
    if (pstArg->ucSubAddrLen > 0)
    {
        pucDest[ulArgLen++] = 0x81;
        pucDest[ulArgLen++] = pstArg->ucSubAddrLen;
        for (i=0; i<pstArg->ucSubAddrLen; i++)
        {
            pucDest[ulArgLen++] = pstArg->aucSubAddr[i];
        }
    }
    /*lint +e961*/

    pucDest[1] = (VOS_UINT8)(ulArgLen - 2);

    return ulArgLen;
}

#if 0
/*****************************************************************************
 �� �� ��  : MN_CALL_SsRegCcEntryArgEncode
 ��������  : ����accessRegisterCCEntry(ע��CCBS)����
 �������  : ��
 �������  : pDest - �����Ŀ�Ļ���
 �� �� ֵ  : ���������ĳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��1��12��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsRegCcEntryArgEncode(
    VOS_UINT8                           *pucDest
)
{
    VOS_UINT32                          ulArgLen = 0;

    pucDest[ulArgLen++] = 0x30;          /* tag of SEQUENCE */
    pucDest[ulArgLen++] = 0;             /* ������ */

    return ulArgLen;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsCugInfoArgEncode
 Description    : ����Cug-info����
 Input          : pDest - �����Ŀ�Ļ���
                  pArg - Ҫ�����CUG����
 Output         :
 Return Value   : ���������ĳ���
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2006-02-28
    Author      : D49431
    Modification: Created function

  2.Date        : 2006-04-14
    Author      : D49431
    Modification: �������ⵥA32D02961�޸�

  3.Date        : 2006-12-11
    Author      : D49431
    Modification: �������ⵥA32D07850�޸�
  4.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsCugInfoArgEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_CUG_CFG_STRU          *pstArg
)
{
    VOS_UINT32                          ulArgLen = 0;
    VOS_UINT8                           *pucSeqLen;

    /*lint -e961*/
    /*���SEQUENCE��Tag*/
    pucDest[ulArgLen++] = 0x30;                /*cug-info tag*/
    pucSeqLen = &pucDest[ulArgLen++];
    *pucSeqLen = 0;

    /* Ŀǰֻ֧��Index 0~9 */
    if (VOS_TRUE == pstArg->bIndexPresent)
    {
        if (pstArg->ulIndex <= 9)
        {
            /*����cug-index����*/
            pucDest[ulArgLen++] = 0x80;            /*tag*/
            pucDest[ulArgLen++] = 1;               /*length*/
            pucDest[ulArgLen++] = (VOS_UINT8)pstArg->ulIndex;

            *pucSeqLen += 3;
        }
    }

    if (VOS_TRUE == pstArg->bSuppressOA)
    {
        /*����suppressOA����*/
        pucDest[ulArgLen++] = 0x82;            /*tag*/
        pucDest[ulArgLen++] = 0;               /*VOS_NULL_PTR*/

        *pucSeqLen += 2;
    }

    if (VOS_TRUE == pstArg->bSuppressPrefer)
    {
        /*����suppressPrefCUG����*/
        pucDest[ulArgLen++] = 0x81;            /*tag*/
        pucDest[ulArgLen++] = 0;               /*VOS_NULL_PTR*/

        *pucSeqLen += 2;
    }

    /*lint +e961*/
    return ulArgLen;
}


/*****************************************************************************
 Prototype      : MN_CALL_SsInvokeArgEncode
 Description    : ����Invoke����
 Input          : ucOpCode - ������
                  punArg   - Ҫ�����CUG����
 Output         : pucDest  - ��������Ŀ�Ļ���
 Return Value   : ������
 Calls          : ---
 Called By      : ---

 History        :
  1.Date        : 2008-02-26
    Author      : D49431
    Modification: Created function
  2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsInvokeArgEncode(
    VOS_UINT8                            ucOpCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if (punArg == VOS_NULL_PTR)
    {
        return 0;
    }

    switch(ucOpCode)
    {
    case MN_CALL_SS_CUG_OPERATION:
        return MN_CALL_SsCugInfoArgEncode(pucDest, &punArg->cugInfoArg);

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    case MN_CALL_SS_CD_OPERATION:
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg )
        {
            return MN_CALL_SsCdArgEncode(&punArg->stCdArg, pucDest);
        }
        else
        {
            return 0;
        }

    case MN_CALL_SS_REG_CC_ENTRY_OPERATION:
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg )
        {
            return 0;
        }
        else
        {
            return 0;
        }

   /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    default:
        return 0;
    }

}


/*****************************************************************************
 Prototype      : MN_CALL_SsComponentEncode()
 Description    : Component��Ϣ����
 Input          : punComponent - ��Ҫ�����component������
 Output         : pucDest      - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsComponentEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    VOS_UINT32                          ulComponentLen = 0;
    /*lint -e961*/
    switch(punComponent->ucCompType)
    {
    case MN_CALL_SS_INVOKE_TYPE_TAG:
        pucDest[ulComponentLen++] = MN_CALL_SS_INVOKE_TYPE_TAG;
        pucDest[ulComponentLen++] = 0;
        pucDest[ulComponentLen++] = MN_CALL_SS_INVOKE_ID_TAG;
        pucDest[ulComponentLen++] = 1;
        pucDest[ulComponentLen++] = punComponent->invokeComp.ucInvokeId;
        if (punComponent->invokeComp.bitOpLinkId)
        {
            pucDest[ulComponentLen++] = MN_CALL_SS_LINKED_ID_TAG;
            pucDest[ulComponentLen++] = 1;
            pucDest[ulComponentLen++] = punComponent->invokeComp.ucLinkId;
        }
        pucDest[ulComponentLen++] = MN_CALL_SS_OPERATION_CODE_TAG;
        pucDest[ulComponentLen++] = 1;
        pucDest[ulComponentLen++] = punComponent->invokeComp.ucOperateCode;
        ulComponentLen +=
            MN_CALL_SsInvokeArgEncode(punComponent->invokeComp.ucOperateCode,
                                   &punComponent->invokeComp.unArg,
                                   &pucDest[ulComponentLen]);

        pucDest[1] = (VOS_UINT8)(ulComponentLen - 2);
        break;

    case MN_CALL_SS_RETURN_RESULT_TYPE_TAG:
        break;

    case MN_CALL_SS_RETURN_ERROR_TYPE_TAG:
        break;

    case MN_CALL_SS_REJECT_TYPE_TAG:
        break;

    default:
        break;
    }
    /*lint +e961*/
    return ulComponentLen;
}



/*****************************************************************************
 Prototype      : MN_CALL_FacilityEncode()
 Description    : Facility��Ϣ����
 Input          : punComponent - ��Ҫ�����component������
                : ucTi         - Tiֵ
 Output         : pucDest      - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
VOS_UINT32 MN_CALL_FacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    return MN_CALL_SsComponentEncode(&pucDest[0], punComponent);
}

/*****************************************************************************
 Prototype      : MN_CALL_SimpleFacilityEncode()
 Description    : Facility��Ϣ����
 Input          : punComponent - ��Ҫ�����component������

 Output         : pucDest      - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
VOS_VOID MN_CALL_SimpleFacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
)
{
    pucDest[0] = (VOS_UINT8)MN_CALL_SsComponentEncode(&pucDest[1], punComponent);
}

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Free()
 Description    : ����InvokeId
 Input          : ucInvokeId: Ҫ�ͷŵ�ucInvokeId
 Output         :
 Return Value   : SPEECH_SUCCESS  �ͷųɹ�
                : SPEECH_ERROR    �ͷ�ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_VOID MN_CALL_InvokeId_Free( VOS_UINT8 ucInvokeId )
{
    g_stCallInvokeIdTable[ucInvokeId].bUsed      = VOS_FALSE;
    g_stCallInvokeIdTable[ucInvokeId].ucCallId   = MN_CALL_INVALID_TI;
    g_stCallInvokeIdTable[ucInvokeId].ucInvokeId = MN_CALL_MAX_INVOKE_NUM;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

