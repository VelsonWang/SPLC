#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"
#include "pwm.h"
#include "adc.h"
#include "spi.h"
#include "w25qxx.h"
#include "sram.h" 
#include "can.h"
#include "ext_io.h"
#include "tc6014.h"
#include "iwdg.h"
#include "stmflash.h"
//ALIENTEK ̽����STM32F407������ ʵ��36
//�ⲿSRAM ʵ�� 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

//FLASHģ��IIC----------------------------------------------------------------------------------
//Ҫд�뵽STM32 FLASH���ַ�������
const u8 IN_TEXT_Buffer[]={"STM32 FLASH TEST"};
#define TEXT_LENTH sizeof(IN_TEXT_Buffer)	 		  	//���鳤��	
#define IN_SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0) 

//FLASH-----------------------------------------------------------------------------------------
//Ҫд�뵽W25Q16���ַ�������
const u8 TEXT_Buffer[]={"Explorer STM32F4 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	

//----------------------------------------------------------------------------------------------

int main(void)
{        	 
 	u8 i=0;
	u8 key = 0;
	
	u8 led_cnt=0;
	
	u16 led0pwmval=0;    
	u8 dir=1;
//	u16 adcx;
//	float temp;
	
	u32 ts=0;
	
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	
	u8 can_cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=1;//CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	
//	union WR2 wr2_t;
//	uint8_t s = sizeof(uint8_t); //1
//	s = sizeof(uint16_t);					//2
//	s = sizeof(uint32_t);					//4
//	s = sizeof(int);							//4
//	s = sizeof(short);						//2
//	s = sizeof(long);							//4
//	s = sizeof(float);						//4
//	res = s;											//��ֹ���������Ż���s

//	wr2_t.all |= 0x0001;
//	res = wr2_t.all&0x0001;
//	
//	wr2_t.bit.ALM_E = 1;
//	res = wr2_t.bit.ALM_E;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	uart2_init(9600);
	
	LED_Init();					//��ʼ��LED,ͬʱ��ʼ��STM32�����TC6014�ļ��޵�����
//	EXTIO_Init();
//	EXTIX_Init();       //��ʼ���ⲿ�ж����루������ͣ���غ�TC6014���жϣ� 
//	TIM3_PWM_Init(500-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.
//	Adc_Init();         //��ʼ��ADC
//	W25QXX_Init();			//W25QXX��ʼ��
 	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM,TC6014����չIO��FSMC�ӿ�  
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps
//	
//	while(W25QXX_ReadID()!=W25Q128)								//��ⲻ��W25Q128
//	{
//		printf("W25Q128 Check Failed!\n");
//		delay_ms(500);
//		printf("Please Check!      \n");
//		delay_ms(500);
//		LED0=!LED0;		//DS0��˸
//	}
//	printf("W25Q128 Ready!\n"); 
//	FLASH_SIZE=16*1024*1024;	//FLASH ��СΪ16�ֽ�
	
	//while(1)
		printf("the testsram is:\n");
//	
//	for(ts=0;ts<250000;ts++)
//	{
//		testsram[ts]=ts;//Ԥ���������	
//		//printf("%d\t", testsram[ts]);
////		PDout(14) = 0;
////		PDout(14) = 1;
//	}
	printf("\n");
	
//	fsmc_sram_test();//����SRAM����	
//	testsram[0] = 0xa5;	
	
	//testio[1] = 0x005a;
//	IWDG_Init(4,500); //���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	
	//key = 1;
  while(1)
	{	
//		IWDG_Feed();//ι��
		//SRAM����----------------------------------------------------------------------------------
//		if(key==1)
//		{
//			key = 0;
//			fsmc_sram_test();//����SRAM����
//		}
//		else if(key==2)
//		{
//			for(ts=0;ts<250000;ts++)
//				printf("%d",testsram[ts]);//��ʾ��������	
//			printf("\n");
//		}
		
		//FLASH����---------------------------------------------------------------------------------
//		else if(key==3)
//		{
//			printf("Start Write W25Q128....\n");
//			W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
//			printf("W25Q128 Write Finished!\n");	//��ʾ�������
//		}
//		else if(key==4)
//		{
//			printf("Start Read W25Q128.... \n");
//			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
//			printf("The Data Readed Is:   \n");	//��ʾ�������
//			printf("%s\n",datatemp);					//��ʾ�������ַ���
//		}
		
		//adc����-----------------------------------------------------------------------------------
//		else if(key==5)
//		{
///*
//			adcx=Get_Adc_Average(ADC_Channel_10,20);//��ȡͨ��10��ת��ֵ��20��ȡƽ��
//			printf("the origin adc value is %d\n",adcx);    //��ʾADCC�������ԭʼֵ
//			temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//			adcx=temp;                            //��ֵ�������ָ�adcx��������ΪadcxΪu16����
//			printf("the integer value is %d\n",adcx);    //��ʾ��ѹֵ���������֣�3.1111�Ļ������������ʾ3
//			temp-=adcx;                           //���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111
//			temp*=1000;                           //С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
//			printf("the decimal value is %f\n",temp); //��ʾС�����֣�ǰ��ת��Ϊ��������ʾ����������ʾ�ľ���111.
//*/
//		}
		
		//can����-----------------------------------------------------------------------------------
//		else if(key==6)//����һ������
//		{
//			printf("the send data is: ");
//			for(i=0;i<8;i++)
//			{
//				canbuf[i]=can_cnt+i;//��䷢�ͻ�����
//				printf("%d\t",canbuf[i]);	  //��ʾ����
// 			}
//			printf("\n");
//			res=CAN1_Send_Msg(canbuf,8);//����8���ֽ� 
//			if(res)printf("Failed\n");		//��ʾ����ʧ��
//			else printf("OK    \n");	 		//��ʾ���ͳɹ�								   
//		}
//		else if(key==7)//�ı�CAN�Ĺ���ģʽ
//		{	   
//			mode=!mode;
//			CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,mode);	//CAN��ͨģʽ��ʼ��,��ͨģʽ,������500Kbps 
//			if(mode==0)//��ͨģʽ����Ҫ2��������
//			{
//				printf("Nnormal Mode \n");	    
//			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
//			{
// 				printf("LoopBack Mode\n");
//			}
//		}
//		
//		//flashģ��IIC
//		else if(key==8)
//		{
//			printf("Start Write FLASH....\n");
//			STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)IN_TEXT_Buffer,IN_SIZE);
//			printf("FLASH Write Finished!\n");//��ʾ�������
//		}
//		else if(key==9)
//		{
//			printf("Start Read FLASH.... \n");
//			STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)datatemp,IN_SIZE);
//			printf("The Data Readed Is:  \n");//��ʾ�������
//			printf("%s\n",datatemp);//��ʾ�������ַ���
//		}
		
//		else 
			delay_ms(10);
		
//		if(dir)led0pwmval++;//dir==1 led0pwmval����
//		else led0pwmval--;	//dir==0 led0pwmval�ݼ� 
// 		if(led0pwmval>300)dir=0;//led0pwmval����300�󣬷���Ϊ�ݼ�
//		if(led0pwmval==0)dir=1;	//led0pwmval�ݼ���0�󣬷����Ϊ����
//		TIM_SetCompare1(TIM3,led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
//		TIM_SetCompare2(TIM3,led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
//		
//		can_cnt=CAN1_Receive_Msg(canbuf);
//		if(can_cnt)//���յ�������
//		{	
//			printf("the receive data is: ");		
// 			for(i=0;i<can_cnt;i++)			
//				printf("%d\t",canbuf[i]);	  //��ʾ����
//			printf("\n");
//		}
		
		led_cnt++;
		if(led_cnt==20)//DS0��˸.
		{
			led_cnt=0;
			//printf("the testsram is:\n");
			//if(testsram[0]==0xa5)
				LED0=!LED0;
			can_cnt++;
 		}
	}
}
