#ifndef __SD_AM_PUBLIC_H__
#define __SD_AM_PUBLIC_H__

#define SPUD_MAX_LOCAL_TOKEN_NUM 64

/*sd ��sc ���ͨ�ö��е���Ϣ��ĺ궨�� */
#define GENERAL_MSG_MASTER_DELETE_CODE 0 /*0��ʾ����ɾ��*/
#define GENERAL_MSG_SLAVE_REBUILD_CODE 1 /*1��ʾ�����ؽ�*/
#define GENERAL_MSG_SLAVE_DELETE_CODE  2 /*2��ʾ����ɾ��*/


#define SD_OTHER_MSG_QUE_LEN 512

/*sd ��sc ���ͨ�ö��еĸ�ʽ */
typedef struct tagSC_GENERAL_MSG_S
{
    VOS_UINT32 ulScLogicalVcpuId;  /*Sc���߼�VCPU ID*/
    VOS_UINT32 ulDpeId;                       /*Dpe���߼�VCPU ID*/
    VOS_UINT32 ulMsgID;                     /*0��ʾ����ɾ��,1��ʾ�����ؽ�,2��ʾ����ɾ��*/
    UCHAR aucImsi[8];                /*IMSI ��BCD��*/
    VOS_UINT16 usGenToken;                  /* ���û���Ӧ��TOKEN��Ϣ */
    UCHAR ucSduId;
    UCHAR ucbit1LuimImsiValid:1;    
    UCHAR ucGenerRev:7;
} SC_GENERAL_MSG_S;
#if 0

/* SC����״̬���ɷֵ���ṹ */
typedef struct  tagSC_ACCESS_STATE_S
{
    VOS_UINT32 ulDpeUserNum[MAX_DPE_NUM_PDSN];   /* SC�ϱ�DPE���û����� */
    VOS_UINT32 ulScUserNum;   /* SC�ϱ��û��� */
    UCHAR ucCpuRate;    /* SC�ڵ�CPU������  ȡ��*/
    UCHAR ucMemRate;    /* SC�ڵ��ڴ������� ȡ�� */
    UCHAR ucReserve[2]; /* 4�ֽڶ��뱣�� */
} SC_ACCESS_STATE_S;
#endif

typedef struct tagFA_NAITOKEN_INFO_S 
{

    UCHAR aucNai[A11_MAX_NAI_LENGTH + 1];
    VOS_UINT16 usToken;
    UCHAR  ucScId;
    UCHAR  ucSduId;
}FA_NAITOKEN_INFO_S;


typedef enum 
{
    SD_OTHER_MSG_TYPE_CHECK_IMSI = 1,  

    SD_OTHER_MSG_TYPE_BULT,
} SD_OTHER_MSG_TYPE_E;

/* IMSI���� */
typedef enum 
{
    SD_IMSI_TYPE_CUIMIMSI,  
    SD_IMSI_TYPE_LUIMIMSI,  
    
    SD_IMSI_TYPE_BUTT,  
} SD_IMSI_TYPE_E;

#define A11_IMSI_CHECK_TO_SD_ITEM_MAX 10
#define A11_IMSI_CHECK_TO_SDU_ITEM_MAX 10
#define A11_NAI_CHECK_TO_SDU_ITEM_MAX 10
#define A11_IMSI_CHECK_MAX_PER_500MS 10

#define A11_IMSI_CHECK_MAX_PER_500MS 30


typedef struct tagA11_SD_IMSI_CHECK_MSG_S
{
    VOS_UINT32 ulItemNum;
    SC_GENERAL_MSG_S astItemArray[0];
} A11_SD_IMSI_CHECK_MSG_S;

typedef struct tagA11_NAI_CHECK_MSG_S
{
    VOS_UINT32 ulItemNum;
    FA_NAITOKEN_INFO_S astItemArray[0];
} A11_NAI_CHECK_MSG_S;

extern VOS_UINT32 SD_QueryScidByImsi(UCHAR  *pucImsi, UCHAR  *pucScid);

#endif /* __SD_AM_PUBLIC_H__ */
