#include "exti.h"
#include "delay.h" 
#include "led.h" 

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//�ⲿ�ж�13~15�������
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)//��ͣ���ذ���
	{
		
		EXTI_ClearITPendingBit(EXTI_Line13);  //���LINE13�ϵ��жϱ�־λ
	}
	
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)//TC6014A�ж�
	{
		
		EXTI_ClearITPendingBit(EXTI_Line14);  //���LINE14�ϵ��жϱ�־λ
	}
	
	if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//TC6014B�ж�
	{
		
		EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15�ϵ��жϱ�־λ
	}
	
/*
	delay_ms(10);	//����
//	if(KEY1==0)	 
//	{
//		LED1=!LED1;
//	}		 
	EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15�ϵ��жϱ�־λ  
*/
}

	   
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
	
	//GPIOB13��14��15��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource13);//PB13 ���ӵ��ж���13
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource14);//PB14 ���ӵ��ж���14
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource15);//PB15 ���ӵ��ж���15
	
	/* ����EXTI_Line13,14,15 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�13,��ͣ����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�14,TC6014A
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15,TC6014B
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����   
}












