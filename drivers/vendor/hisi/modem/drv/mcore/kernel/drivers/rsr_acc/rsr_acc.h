#ifndef __RSR_ACC__
#define __RSR_ACC__
struct rsr_acc_bd_s
{
    struct
    {
    	unsigned int bd_flow     :2;/*[0]:save_en:1��ʾ��save������ִ�и�bd��
    													0��ʾsave������������bd
    										[1]:restore_en:1��ʾ��restore������ִ�и�bd��
    													0��ʾrestore������������bd*/
    	unsigned int reserved_1	 :2;/*[2-3]*/
    	unsigned int bd_oper     :3;/*[4-6]:   0:save ����reg_baddr-->ddr_baddr
    										1:restore ����ddr_baddr--->reg_baddr
    										2:save&restore:save flow ��reg_baddr-->ddr_baddr;restore flow ��ddr_baddr--->reg_baddr
    										3:~restore
    										4:wait*/
    	unsigned int reserved_2  :9;/*[7-15]*/
    	unsigned int bd_type     :2;/*[16-17]: 
									1:��������Ĵ�������
									2:�����Ĵ�������
									other:reserved
									*/
		unsigned int reserved_3  :14;/*[18-31]*/
																	
    }cfg;
	u32* ddr_baddr;/*Ҫ����Ĵ������ݵ�Ŀ�ĵ�ַ�Ļ���ַ*/
	u32* reg_baddr;/*Ҫ����ļĴ�������ַ*/
	unsigned int bd_flow_operation;/*bd_type=1,��ʾ���������ļĴ�������
									bd_type=2,��ʾ��ȡ��restoreʱ�����ã���ʾbit_mask*/
	
}__attribute__((aligned(8)));

#define CTRL_OFFSET(i)          ((i)*0x80+0x80) /*ͨ�����ƼĴ���                       */
#define BD_BASE_OFFSET(i)       ((i)*0x80+0x84) /*bd����ַ���üĴ���              */ 
#define BD_LEN_OFFSET(i)        ((i)*0x80+0x88) /*bd�����üĴ���                          */ 
#define SR_STATUS_OFFSET(i)     ((i)*0x80+0x8C) /*bd����ָ�״̬�Ĵ���         */ 
#define DMA_CTRL_OFFSET          0x0             /*DMA ״̬���ƼĴ���               */
#define INT_STATUS_OFFSET        0x8             /*ͨ��״̬����                            */
#define INT_MASK_OFFSET          0xC             /*ͨ��״̬ȡ���Ĵ���           */
#define INT_MSTATUS_OFFSET       0x10            /*ȡ�����ͨ��״̬�Ĵ���*/
#define DEBUG_STATE_OFFSET       0x14            /*bd�����ݴ���״̬�Ĵ���  */
enum{
	RSR_ACC_CHANNEL_0,
	RSR_ACC_CHANNEL_1,
	RSR_ACC_CHANNEL_2,
	RSR_ACC_CHANNEL_3,
	RSR_ACC_CHANNEL_MAX,
};

enum rsracc_flow_e{
	suspend_flow=0x1,
	resume_flow =0x2,
};
/*RSRACCģ��ά�������bd����*/
#define MAX_RSR_ACC_BD_CNT 250


#endif
