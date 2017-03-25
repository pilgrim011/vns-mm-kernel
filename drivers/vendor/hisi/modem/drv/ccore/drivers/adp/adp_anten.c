#include <product_config.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <drv_nv_def.h>
#include <hi_anten.h>
#include <gpio_balong.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <bsp_version.h>
#include <bsp_rf_balong.h>


/*****************************************************************************
 �� �� ��  : drv_anten_lock_status_get
 ��������  : ��ȡ���������ߵ�����״̬
 �������  : none
 �������  : 0 - ��������
             1 - ��������
 �� �� ֵ  : 0 - �ɹ�
             ����Ϊʧ��

*****************************************************************************/
int mdrv_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    return bsp_anten_get_lockstate(modem_id,status);
}


/*****************************************************************************
 �� �� ��  : drv_anten_int_install
 ��������  : �ж�ע�ắ����������õ�ǰ������״̬
 �������  : routine   - �жϴ�����
             para      - �����ֶ�
 �������  : none
 �� �� ֵ  : void

*****************************************************************************/
void mdrv_anten_register_intr_cb(PWC_COMM_MODEM_E modem_id, void* routine, int para)
{
    bsp_anten_int_install(modem_id, routine, para);
}
/*****************************************************************************
* �� ��    : mdrv_anten_set_outer_rfswitch
* �� ��    : NASר�ýӿ�
                    ���Modem������ѡ����ƽӿ�
                    ��ǰ���岻֧�ִ˹��ܣ���ӦNV��Ϊȫ0�������������쳣 ����-1
* �� ��    : @status 1:���Modem���߹��ܣ�0�������Modem���߹���

* �� ��    : ��

* �� ��    : 0Ϊ�ɹ���-1Ϊʧ��
* �� ��    : z00228752
*****************************************************************************/
int mdrv_anten_set_outer_rfswitch(unsigned int status)
{   
    return bsp_anten_set_outer_rfswitch(status);
}
/*****************************************************************************
* �� ��    : mdrv_anten_set_outer_rfswitch
* �� ��    : NASר�ýӿ�
                    ���Modem������ѡ���ѯ�ӿ�
                    ��ǰ���岻֧�ִ˹��ܣ���ӦNV��Ϊȫ0�������������쳣 ����-1
* �� ��    : ��

* �� ��    : @status 1:���Modem���߹��ܣ�0�������Modem���߹���

* �� ��    : 0Ϊ�ɹ���-1Ϊʧ��
* �� ��    : z00228752
*****************************************************************************/
int mdrv_anten_get_outer_rfswitch(unsigned int *status)
{
    return bsp_anten_get_outer_rfswitch(status);
}
/*****************************************************************************
* �� ��    : mdrv_anten_set_mode
* �� ��    : DSPר�ýӿ�,GPIO����������
* �� ��    : @mode:����ģʽ
*                   ANT_LTE     =  0, lte�ּ�����
*                   ANT_GSM     =  1, GSM��������

* �� ��    : @status 1:���Modem���߹��ܣ�0�������Modem���߹���

* �� ��    : 0:��ȷ��-1:����
* �� ��    : z00228752
*****************************************************************************/
int mdrv_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    return bsp_anten_set_mode(mode);
}

/*****************************************************************************
* �� ��    : mdrv_fem_ioctrl
* �� ��    : ��Ƶ�ܽ�����
* �� ��    : @ctrl_type  �ӿ����ͣ�
              1Ϊgpio��mipi����NV���ã�
              2Ϊֱ�Ӵ�������
              3��2�Ļ����ϻὫ�����ڵ͹��Ļ���ʱ�ָ�
              4��ʾVIA MODEM�Ƿ���λ

               ctrl_type = CFG_RFFE_GROUP_GPIO_MIPI
              @para1 is nvindex      nv  ��������ȡֵΪ0-15���˲����μ�nv�ֲ�18002
              @para2 is mux          �ܽŸ������ã�0Ϊgpio���ܣ�1Ϊ�߿ع���
              @para3 is reserved     ����

               ctrl_type = CFG_RFFFE_SET_PIN_NO_NV
              @para1 is gpio num     gpio���
              @para2 is mux          �ܽŸ������ã�0Ϊgpio���ܣ�1Ϊ�߿ع���
              @para3 is value        ��para2Ϊgpio���ܣ���valueΪ�����ƽ

               ctrl_type = CFG_RFFE_SET_PIN_WITH_RESUEM(��1�Ļ����ϣ����ӵ͹��Ĺ���)
              @para1 is gpio num     gpio���
              @para2 is mux          �ܽŸ������ã�0Ϊgpio���ܣ�1Ϊ�߿ع���
              @para3 is value        ��para2Ϊgpio���ܣ���valueΪ�����ƽ

               ctrl_type = CFG_VIA_MODEM_IS_ACTIVE(����modem�Ƿ���λ)
              @para1 is active       0��ʾ����λ��1��ʾ��λ
              @para2 is mux          ����
              @para3 is value        ����

* �� ��    : ��
* �� ��    : 0Ϊ�ɹ���-1Ϊʧ��
* �� ��    : z00228752
* ˵ ��    : �˽ӿ����ֻ�ƽ̨ʹ�ã�MBB���輰����׮����
*****************************************************************************/
int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return bsp_fem_ioctrl(ctrl_type,para1,para2,para3);
}

