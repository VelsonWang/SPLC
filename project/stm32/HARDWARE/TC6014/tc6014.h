#ifndef __TC6014_H
#define __TC6014_H

#include "sys.h"
#include "sram.h"
#include "usart.h"

#define TC6014A_BASE_ADDR Bank1_SRAM1_ADDR
#define TC6014B_BASE_ADDR Bank1_SRAM2_ADDR

#define	TC6014A 0
#define	TC6014B 1

#define outpw(port, data) (*(volatile unsigned short *)(port)) = data
#define inpw(port) (*(volatile unsigned short *)(port))

//-----tc6014 �Ĵ�����ַ����
#define  wr0  0x0  //����Ĵ���
#define  wr1  0x2  //ģʽ�Ĵ���1
#define  wr2  0x4  //ģʽ�Ĵ���2
#define  wr3  0x6  //ģʽ�Ĵ���3 
#define  wr4  0x8  //����Ĵ���
#define  wr5  0xa  //�岹ģʽ�Ĵ���
#define  wr6  0xc  //��λд�����ݼĴ��� 
#define  wr7  0xe  //��λд�����ݼĴ���

#define  rr0  0x0 //��״̬�Ĵ���
#define  rr1  0x2 //״̬�Ĵ���1  
#define  rr2  0x4 //״̬�Ĵ���2 
#define  rr3  0x6 //״̬�Ĵ���3  
#define  rr4  0x8 //����Ĵ���1  
#define  rr5  0xa //����Ĵ���2  
#define  rr6  0xc //��λ�������ݼĴ��� 
#define  rr7  0xe //��λ�������ݼĴ��� 

#define  bp1p  0x4  //BP��1 ��+�������ݼĴ��� 
#define  bp1m  0x6 //BP��1 ��-�������ݼĴ���  
#define  bp2p  0x8  //BP��2 ��+�������ݼĴ���
#define  bp2m  0xa //BP��2 ��-�������ݼĴ���  
#define  bp3p  0xc  //BP��3 ��+�������ݼĴ���
#define  bp3m  0xe //BP��3 ��-�������ݼĴ���

//typedef enum
//{
//	TC6014A = 0,
//	TC6014B
//}ChipEnum;


/*-----------------------wr0------------------------------------------------*/
struct WR0_BITS
{
	uint16_t CMD:7;	//bit0~6 		������
	uint16_t rsvd0:1;	//bit7 			����  	������Ϊ0
	uint16_t X_AXIS_SEL:1;	//bit8		��X��ѡ��λ
	uint16_t Y_AXIS_SEL:1;	//bit9		��Y��ѡ��λ
	uint16_t Z_AXIS_SEL:1;	//bit10		��Z��ѡ��λ
	uint16_t U_AXIS_SEL:1;	//bit11		��U��ѡ��λ
	uint16_t rsvd1:3;	//bit12~14 	����  	������Ϊ0
	uint16_t RESET:1;	//bit15 		��λλ  д0x80ʵ��оƬ��λ��ע�����������Ҫ��Ϊ0
};

union WR0
{
	struct WR0_BITS bit;
	uint16_t all;
};

/*-----------------------wr1------------------------------------------------*/
struct WR1_BITS
{
	uint16_t IN0_L:1;	//bit0 		IN0������Ч��ƽλ 0���͵�ƽ��Ч    1���ߵ�ƽ��Ч
	uint16_t IN0_E:1;	//bit1 		IN0����ʹ��λ     0����ʹ��        1��ʹ��  
	uint16_t IN1_L:1;	//bit2 		IN1������Ч��ƽλ 0���͵�ƽ��Ч    1���ߵ�ƽ��Ч
	uint16_t IN1_E:1;	//bit3 		IN1����ʹ��λ     0����ʹ��        1��ʹ�� 
	uint16_t IN2_L:1;	//bit4 		IN2������Ч��ƽλ 0���͵�ƽ��Ч    1���ߵ�ƽ��Ч
	uint16_t IN2_E:1;	//bit5 		IN2����ʹ��λ     0����ʹ��        1��ʹ�� 
	uint16_t IN3_L:1;	//bit6 		IN3������Ч��ƽλ 0���͵�ƽ��Ч    1���ߵ�ƽ��Ч
	uint16_t IN3_E:1;	//bit7 		IN3����ʹ��λ     0����ʹ��        1��ʹ�� 
	
	//�������ж�����/��ֹλ  1������   0����ֹ�
	uint16_t PLUSE:1;	//bit8 		ÿһ���������������أ��жϽ��������������������߼���
	uint16_t P_MTE_CN:1;	//bit9  �߼�/ʵλ����������ֵ >= COMP-�Ĵ�������ֵʱ���жϷ���
	uint16_t P_LT_CN:1;	//bit10 �߼�/ʵλ����������ֵ < COMP-�Ĵ�������ֵʱ���жϷ���
	uint16_t P_LT_CP:1;	//bit11 �߼�/ʵλ����������ֵ >= COMP+�Ĵ�������ֵʱ���жϷ���
	uint16_t P_MTE_CP:1;	//bit12 �߼�/ʵλ����������ֵ < COMP+�Ĵ�������ֵʱ���жϷ���
	uint16_t C_END:1;	//bit13   �Ӽ�������ʱ���ڶ������������������жϷ���
	uint16_t C_STA:1;	//bit14   �Ӽ�������ʱ���ڶ�����ʼ����������жϷ���
	uint16_t E_END:1;	//bit15   ��������ʱ���жϷ���
};

union WR1
{
	struct WR1_BITS bit;
	uint16_t all;
};

/*-----------------------wr2------------------------------------------------*/
struct WR2_BITS
{
	uint16_t SLMTP:1;	//bit0 	  �Ƿ��COMP+�Ĵ�����Ϊ������� 0����   1����
	uint16_t SLMTN:1;	//bit1 		�Ƿ��COMP-�Ĵ�����Ϊ������� 0����   1����
	uint16_t LMTMD:1;	//bit2 		Ӳ��������Чʱ������ֹͣ��ʽ  0������ֹͣ  1������ֹͣ
	uint16_t HLMTP:1;	//bit3 		���������������ź�(nLMTP)���߼���ƽ  0������Ч   1������Ч
	uint16_t HLMTN:1;	//bit4 		���������������ź�(nLMTN)���߼���ƽ  0������Ч   1������Ч
	uint16_t CMPSL:1;	//bit5 		��COMP+/-�Ĵ����ıȽ϶����趨Ϊ�߼�λ�ü���������ʵ��λ�ü�����
	uint16_t PLSMD:1;	//bit6 		��������������ʽ  0������2���巽ʽ   1������+����ʽ
	uint16_t PLS_L:1;	//bit7 		����������߼���ƽ  0�����߼�    1�����߼�
	uint16_t DIR_L:1; //bit8 		���������߼���ƽ  0��������(L) ������(H)  1��������(H) ������(L) 
	uint16_t PINMD:1;	//bit9    �����������ź�ģʽ 0��2����������   1����/����������
	uint16_t PIND:2;	//bit10~11 	2������������ܱ�  00��1/1  01��1/2  10��1/4  11����Ч
	uint16_t ALM_L:1;	//bit12   �����ź�(nALARM)���߼���ƽ 0������Ч   1������Ч
	uint16_t ALM_E:1;	//bit13   �Ƿ�ʹ�ܽ����ŷ���������nALARM�ź�  0����   1����
	uint16_t INP_L:1;	//bit14   �����ź�(nINPOS)���߼���ƽ 0������Ч   1������Ч
	uint16_t INP_E:1;	//bit15   �Ƿ�ʹ�ܽ����ŷ���������nINPOS�ź�  0����   1����
};

union WR2
{
	struct WR2_BITS bit;
	uint16_t all;
};

/*-----------------------wr3------------------------------------------------*/
struct WR3_BITS
{
	uint16_t MANLD:1;	//bit0 	  �Ѽ�/���ٶ��������ļ����趨Ϊ�Զ����ٻ��ֶ����� 0���Զ�����   1���ֶ�����
	uint16_t DSNDE:1;	//bit1 		�Ѽ�/��������ʱ�ļ����ٶ��趨Ϊ���ٶȵ���ֵ���߶����ļ��ٶȵ���ֵ 0��ʹ�ü��ٶȵ���ֵ   1��ʹ�ü��ٶȵ���ֵ
	uint16_t SACC:1;	//bit2 		�趨ֱ�߼�/���ٻ���S���߼�/���� 0��ֱ�߼�/����  1��S���߼�/���٣�ʹ��ǰһ��Ҫ��ü�/���ٶȵı仯�ʣ�  
	uint16_t EXOP0:2;	//bit3~4 		�����ⲿ�����ź�(nEXPP,nEXPM)�趨�������� 00/11����Ч   01��������������  10��������������
	uint16_t rsvd0:2;	//bit5~6 	����  	������Ϊ0	
	uint16_t OUTSL:1;	//bit7 		ѡ������ź�nOUT7~4Ϊͨ����������������״̬  0��ͨ��  1��״̬
													/*
													nOUT4/CMPP   ���߼�/ʵ�ʼ�������ֵ >= COMP+�Ĵ���ʱ������ߵ�ƽ����������͵��
													nOUT5/CMPM   ���߼�/ʵ�ʼ�������ֵ >= COMP-�Ĵ���ʱ������ߵ�ƽ����������͵�ƽ
													nOUT6/ASND   ������������ִ�У������ڼ���״̬ʱ������ߵ�ƽ����������͵�ƽ
													nOUT7/DSND   ������������ִ�У������ڼ���״̬ʱ������ߵ�ƽ����������͵�ƽ�
													*/
	uint16_t OUT4:1;	//bit8 		������ź�nOUT4��Ϊͨ�����ʹ��ʱ����ֵ  0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t OUT5:1;	//bit9 		������ź�nOUT5��Ϊͨ�����ʹ��ʱ����ֵ  0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t OUT6:1;	//bit10 		������ź�nOUT6��Ϊͨ�����ʹ��ʱ����ֵ  0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t OUT7:1;	//bit11 		������ź�nOUT7��Ϊͨ�����ʹ��ʱ����ֵ  0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t rsvd1:4;	//bit12~15 	����  	������Ϊ0	
};

union WR3
{
	struct WR3_BITS bit;
	uint16_t all;
};

/*-----------------------wr4------------------------------------------------*/
struct WR4_BITS
{
	uint16_t XOUT0:1;	//bit0 	  XOUT0ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t XOUT1:1;	//bit1 	  XOUT1ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t XOUT2:1;	//bit2 	  XOUT2ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t XOUT3:1;	//bit3 	  XOUT3ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	
	uint16_t YOUT0:1;	//bit4 	  YOUT0ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t YOUT1:1;	//bit5 	  YOUT1ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t YOUT2:1;	//bit6 	  YOUT2ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t YOUT3:1;	//bit7 	  YOUT3ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	
	uint16_t ZOUT0:1;	//bit8 	  ZOUT0ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t ZOUT1:1;	//bit9 	  ZOUT1ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t ZOUT2:1;	//bit10 	  ZOUT2ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t ZOUT3:1;	//bit11 	  ZOUT3ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���

	uint16_t UOUT0:1;	//bit12 	  UOUT0ͨ����� 0���͵�ƽ���   1���ߵ�ƽ��
	uint16_t UOUT1:1;	//bit13 	  UOUT1ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t UOUT2:1;	//bit14 	  UOUT2ͨ����� 0���͵�ƽ���   1���ߵ�ƽ���
	uint16_t UOUT3:1;	//bit15 	  UOUT3ͨ����� 0���͵�ƽ���   1���ߵ�ƽ����
};

union WR4
{
	struct WR4_BITS bit;
	uint16_t all;
};

/*-----------------------wr5------------------------------------------------*/
struct WR5_BITS
{
	uint16_t AX1:2;	//bit0~1 	  ָ�����в岹�����ĵ�һ�ᣨ���ᣩ
	uint16_t AX2:2;	//bit2~3 	  ָ�����в岹�����ĵڶ���
	uint16_t AX3:2;	//bit4~5 	  ָ�����в岹�����ĵ�����
							/*
							��			����
							X   		00
							Y				01
							Z				10
							U				11
							*/
	uint16_t rsvd0:2;	//bit6~7 	  ����  	������Ϊ0	
	
	uint16_t LSPD:2;	//bit8~9 	  �趨�岹�����Ĺ̶����ٶ�ģʽ
							/*
					bit9:bit8		����ģʽ
							00		���ٶȺ㶨��Ч
							01		2�����ٶȺ㶨
							10		�������趨��
							11		3�����ٶȺ㶨
							*/

	uint16_t rsvd1:1;	//bit10 	  ����  	������Ϊ0	
	
	uint16_t EXPLS:1;	//bit11 	  �Ƿ�����ⲿ�ź�(EXPLSN)���в����岹���� 0����   1�����
	uint16_t CMPLS:1;	//bit12 	  �Ƿ����������в����岹���� 0����   1�����
	uint16_t rsvd2:1;	//bit13 	  ����  	������Ϊ0
	uint16_t CIINT:1;	//bit14 	  �Ƿ�ʹ�������岹�ж� 0����   1�����
	uint16_t BPINT:1;	//bit15 	  �Ƿ�ʹ��λģʽ�岹�ж� 0����   1�����
};

union WR5
{
	struct WR5_BITS bit;
	uint16_t all;
};

/*-----------------------tc6014�Ĵ���------------------------------------------------*/
typedef struct TC6014_Wregs
{
	//TC6014�ļĴ���
	union WR0 _wr0;
	union WR1 _wr1[4];
	union WR2 _wr2[5];
	union WR3 _wr3[5];
	union WR4 _wr4[2];
	union WR5 _wr5[2];
	uint16_t _wr6[2];
	uint16_t _wr7[2];
	
	//TC6014�Ĳ���
	uint32_t R; //range  ��Χ
	uint32_t SV; //start velocity ��ʼ�ٶ�
	uint32_t V;  //drive velocity �����ٶ�
	uint32_t A;  //acceleration ���ٶ�
	uint32_t D;  //deceleration ���ٶ�
	uint32_t K;  //jerk  ���ٶȱ仯��
	uint32_t L;  //deceleration increase rate ���ٶȱ仯��
	
	uint8_t clock; //ʱ��=fclk/16000000��fclk(�ⲿ����Ƶ��)һ��Ϊ16MHz����clock = 1
	uint16_t multiple; //����=8000000/R�����Ϊ500����R=16000ʱ
	uint32_t initial_speed; //��ʼ�ٶ�(pps)=SV*multiple*clock
	uint32_t drive_speed; //�����ٶ�(pps)=V*multiple*clock
	uint32_t acceleration; //���ٶ�(pps/sec)=A*125*multiple*clock*clock
	uint32_t deceleration; //���ٶ�(pps/sec)=D*125*multiple*clock*clock
	uint32_t jerk; //���ٶȱ仯��(pps/sec/sec/sec)=62.5*1000000*multiple*clock*clock*clock/K
	uint32_t dec_inc_tate; //���ٶȱ仯��(pps/sec/sec/sec)=62.5*1000000*multiple*clock*clock*clock/L
}TC6014_TypeDef;

extern TC6014_TypeDef* ptc6014_wregs;
extern uint32_t adr;

void select_chip(int chip);
int which_chip(void);
void wreg1(int axis,int wdata);
void wreg2(int axis,int wdata);
void wreg3(int axis,int wdata);
void command(int axis,int cmd);
void range(int axis,long wdata);
void acac(int axis,int wdata);
void dcac(int axis,int wdata);
void acc(int axis,int wdata);
void dec(int axis,int wdata);
void startv(int axis,int wdata);
void speed(int axis,int wdata);
void pulse(int axis,long wdata);
void decp(int axis,long wdata);
void center(int axis,long wdata);
void lp(int axis,long wdata);
void ep(int axis,long wdata);
void compp(int axis,long wdata);
void compm(int axis,long wdata);
void accofst(int axis,long wdata);
void hsspeed(int axis,int wdata);
void expmode(int axis,int em6data,int em7data);
void syncmode(int axis,int sm6data,int sm7data);
long readlp(int axis);
long readep(int axis);
void waitaxis(int axis);
void next_wait(void);
void bp_wait(void);
void homesrch(void);


void test(char flag);
	
#endif
