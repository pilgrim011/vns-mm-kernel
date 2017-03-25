#ifndef __MDRV_CCORE_PMU_H__
#define __MDRV_CCORE_PMU_H__
#ifdef __cplusplus
extern "C"
{
#endif


#include <mdrv_pm_common.h>
#include <mdrv_pm.h>

    /*
       int DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id);
       int DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, unsigned int voltage_mv );
       int DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, unsigned int *voltage_mv );
       int DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,unsigned short **list, unsigned int *size);
       int DRV_MODEM_APT_ENABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_APT_DISABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_APT_STATUS_GET(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       int DRV_MODEM_MODE_CONFIG(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);
       */

    typedef enum
    {
        TULPA_VCC,
        TULPA_VBIAS,
        GPA_VCC,
        GPA_VBIAS,
        RFIC_ANALOG0,
        RFIC_ANALOG1,
        FEM,

        CONSUMER_ID_BUTT
    }EX_RFFE_POWER_ID_E;

    typedef enum
    {
        DCXO_CFIX1,
        DCXO_CFIX2,
        DCXO_COMPENSATE_BUTT
    }DCXO_COMPENSATE_ID_E;

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_check_pastar
     *  ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
     *  �������  : modem_id       ����
     *  �������  : ��
     *  �� �� ֵ  : 0          û���쳣
     *             -1       �����쳣
     ******************************************************************************/
    int mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id);

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_set_voltage
     *  ��������  : ͨ��ģ�����õ�ѹ�ӿ�
     *  �������  : consumer_id     �û�id
     *              voltage_mv      ���õĵ�ѹֵ����
     *  �������  : ��
     *  �� �� ֵ  : 0       ���óɹ�
     *             -1       ����ʧ��
     ******************************************************************************/
    int mdrv_pmu_set_voltage( EX_RFFE_POWER_ID_E consumer_id, unsigned int voltage_mv , PWC_COMM_CHANNEL_E chn);


    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_get_voltage
     *  ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
     *  �������  : consumer_id     �û�id
     *              voltage_mv      ��õĵ�ѹֵ����
     *  �������  : ��
     *  �� �� ֵ  : 0       ��ȡ�ɹ�
     *             -1       ��ȡʧ��
     ******************************************************************************/
    int mdrv_pmu_get_voltage( EX_RFFE_POWER_ID_E consumer_id, unsigned int *voltage_mv, PWC_COMM_CHANNEL_E chn );

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_list_voltage
     *  ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
     *  �������  : consumer_id     �û�id
     *              list            ��ѹ��Χ����
     *              size            �����С
     *  �������  : ��
     *  �� �� ֵ  : 0       ��ȡ�ɹ�
     *             -1       ��ȡʧ��
     * *****************************************************************************/
    int mdrv_pmu_list_voltage(EX_RFFE_POWER_ID_E consumer_id, unsigned short **list, unsigned int *size);

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_enable_apt
     *  ��������  : ͨ��ģ��ʹ��APT�ӿ�
     *  �������  : modem_id       ����
     *              mode_id        ͨ��ģʽ
     *  �������  : ��
     *  �� �� ֵ  : 0      ���óɹ�
     *             -1      ����ʧ��
     ******************************************************************************/
    int mdrv_pmu_enable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_disable_apt
     *  ��������  : ͨ��ģ��ȥʹ��APT�ӿ�
     *  �������  : modem_id       ����
     *              mode_id        ͨ��ģʽ
     *  �������  : ��
     *  �� �� ֵ  : 0         ���óɹ�
     *             -1      ����ʧ��
     ******************************************************************************/
    int mdrv_pmu_disable_apt(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_get_aptstatus
     *  ��������  : ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
     *  �������  : modem_id       ����
     *              mode_id        ͨ��ģʽ
     *  �������  : ��
     *  �� �� ֵ  : PWRCTRL_COMM_ON     APTʹ��
     *              PWRCTRL_COMM_OFF    APTδʹ��
     *                     -1           ��ȡʧ��
     ******************************************************************************/
    int mdrv_pmu_get_aptstatus(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id);

     /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_dcxo_fre_compensate
     *  ��������  : Ϊdcxo��ȡƵ�ʲ���
     *  �������  : value:��Ҫ���ڵ�ֵ
     *              
     *  �������  : ��
     *  �� �� ֵ  : null
     *             
     ******************************************************************************/   
     void mdrv_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
    
    /*****************************************************************************
     *  �� �� ��  : mdrv_pmu_set_lod27_ao
     *  ��������  : ����ldo27�Ƿ�Ϊ����״̬
     					ֻ��austin��v7r5��ʹ�ã�������Ʒ��̬���ṩҲ����׮
     *  �������  : ao:trueʱ������ldo27��falseʱ��ldo27�������µ�
     *              
     *  �������  : ��
     *  �� �� ֵ  : 0      ���óɹ�
     *             -1      ����ʧ��
     ******************************************************************************/ 
    int mdrv_pmu_set_ldo27_ao(int ao);

#ifdef __cplusplus
}
#endif
#endif
