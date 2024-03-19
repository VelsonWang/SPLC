#ifndef __SRAM_H
#define __SRAM_H															    
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿSRAM ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define CSn PGout(10)	// DS0
#define RDn PDout(4)
#define WRn PDout(5)

#define O1_CS PFout(0)
#define O2_CS PFout(1)
#define I1_CS PFout(2)
#define I2_CS PFout(3)
#define I3_CS PFout(4)

#define D0 PDout(14)
#define D1 PDout(15)
#define D2 PDout(0)
#define D3 PDout(1)
#define D4 PEout(7)
#define D5 PEout(8)
#define D6 PEout(9)
#define D7 PEout(10)
#define D8 PEout(11)
#define D9 PEout(12)
#define D10 PEout(13)
#define D11 PEout(14)
#define D12 PEout(15)
#define D13 PDout(8)
#define D14 PDout(9)
#define D15 PDout(10)

void EXTIO_Init(void);
void ExtIO_Out1(uint16_t data);
	
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17 
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18
#define Bank1_SRAM4_ADDR    ((u32)(0x6C000000))//SRAM
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))//��չIO
#define Bank1_SRAM2_ADDR    ((u32)(0x64000000))//TC6014B
#define Bank1_SRAM1_ADDR    ((u32)(0x60000000))//TC6014A

void FSMC_SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);


void fsmc_sram_test_write(u32 addr,u8 data);
u8 fsmc_sram_test_read(u32 addr);

extern u32 testsram[250000];
extern u16 testio_o1;
extern u16 testio_o2;
void fsmc_sram_test(void);

#endif

