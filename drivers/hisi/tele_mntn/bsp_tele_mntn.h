/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bsp_tele_mntn.h
  �� �� ��   : ����
  ��    ��   : ���� 00186593
  ��������   : 2014��5��17��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��17��
    ��    ��   : ���� 00186593
    �޸�����   : �����ļ�
  2.ע    ��   : ���¼����ļ��� .c .h ���ݱ�����ȫ��ͬ
                 vendor\hisi\confidential\lpmcu\driver\tele_mntn\
                 kernel\drivers\hisi\tele_mntn\

******************************************************************************/

#ifndef __BSP_TELE_MNTN_H__
#define __BSP_TELE_MNTN_H__

#include <linux/hisi/hisi_tele_mntn.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
typedef struct tele_mntn_queue
{
    unsigned char* base;            /* ���л���ַ       */
    unsigned int length;            /* �����ܳ��ȣ���λbyte */
    unsigned char* front;           /* ����дָ��, ���Ե�ַ��in   */
    unsigned char* rear;            /* ���ж�ָ��, ���Ե�ַ��out  */
}TELE_MNTN_QUEUE_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : tele_mntn_write_log
 ��������  : ����log�ӿ�
 �������  : TELE_MNTN_TYPE_ID type_id
             u32_t len
             void_t * data
 �������  : ��
 �� �� ֵ  : s32_t
 ���ú���  :
 ��������  :
 ˵    ��  : �ú���һ�δ���len���ֵΪ64�ֽڣ�����lenΪ8�ֽڶ��롣
             δ�����ε���Ӱ�����ܣ�����һ��type_idһ�����̵����ݷ�װ�ɽṹ�壬һ���Դ���telemntn
 ��    ��  : hifi�ϵ磬���������̵�log��¼

             hifi���µ��typeidΪ TELE_MNTN_PUPD_HIFI ��ʾ�ϵ���µ磬���Էֽ�Ϊ�������̣��ϵ���µ硣
             �����ϵ����̣����齫PWC_TELE_MNTN_PU_STRU��������ٵ���ִ��tele_mntn_write_log�ӿڣ�
             ������һ�����̵���ִ�ж��tele_mntn_write_log�ӿڡ�


             typedef struct PWC_TELE_MNTN_PU_STRU_S
             {
                 u32_t  wakeCount;
                 u32_t  wakeSrc0;
                 u32_t  wakeSrc1;
                 u32_t  wakeSrcIPC;
                 u8_t   wakeSrcGPIO[8];
             }PWC_TELE_MNTN_PU_STRU;

     	     typedef struct PWC_TELE_MNTN_PD_STRU_S
     	     {
     	         u32_t  sleepCount;
     	     }PWC_TELE_MNTN_PD_STRU;

             typedef struct PWC_TELE_MNTN_PUPD_STRU_S
             {
                 PWC_TELE_MNTN_PD_STRU pdStat;
                 PWC_TELE_MNTN_PU_STRU puStat; //�ýṹ������log���¼��telemntn��
                 u32_t pdSliceTime;
                 u32_t puSliceTime;  //��ʱ��Ϊ���ؼ�¼ʱ��
             }PWC_TELE_MNTN_PUPD_STRU;

             g_hifi_log = (PWC_TELE_MNTN_PUPD_STRU *)0x25000; //ȫ�ֱ�����ָ��̶��ڴ�ռ�
             s32_t  pwc_power_up_hifi( void_t )
             {
                 //��ά�ɲⲿ�֣��Ƚ�һ���������̵�log��¼������
                 g_hifi_log->puStat.wakeCount++;

                 �ϵ紦����

                 //��ά�ɲⲿ�֣��Ƚ�һ���������̵�log��¼������
                 g_hifi_log->puStat.wakeSrc0 = xxx;
                 g_hifi_log->puStat.wakeSrcIPC = xxx;
                 g_hifi_log->puStat.wakeSrcGPIO = xxx;
                 g_hifi_log->puSliceTime = get_slice_time();

                 //���ô��������̼�¼��telemntn�У�����ʱ����Ϣ
                 (void)tele_mntn_write_log(TELE_MNTN_PUPD_HIFI,sizeof(g_hifi_log->puStat),&(g_hifi_log->puStat));

                 return RET_OK;
             }

 �޸���ʷ      :
  1.��    ��   : 2014��5��19��
    ��    ��   : ���� 00186593
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, unsigned int len, const void *data);
extern int tele_mntn_init(void);
extern int tele_mntn_wake_up_acore(void);
extern int tele_mntn_get_head(struct tele_mntn_queue *queue);
extern int tele_mntn_set_head(const struct tele_mntn_queue *queue);
extern int tele_mntn_is_func_on (TELE_MNTN_TYPE_ID type_id);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_tele_mntn.h */
