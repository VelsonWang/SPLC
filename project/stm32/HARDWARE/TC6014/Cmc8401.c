#include "Cmc8401.h"
#include "tc6014.h"

int __stdcall c8401_board_initial(void)
{
	int  count;
	outpw(adr+wr0, 0x8000);//�����λ
	for(count = 0; count < 2; ++count);
	
	//------------ȫ��ģʽ�趨------------
	command(0xf,0xf);//���л���������
	outpw(adr+wr1, 0x0000);//ģʽ�Ĵ���1 00000000 00000000  
	outpw(adr+wr2, 0xe000);//ģʽ�Ĵ���2 11100000 00000000  
	outpw(adr+wr3, 0x0000);//ģʽ�Ĵ���3 00000000 00000000  
	expmode(0xf,0x5d08,0x497f); //�������ⲿģʽ�趨 

	//--------ȫ��������������趨----
	accofst(0xf,0);//A0 = 0 ����ƫ��Ϊ0��Ĭ��Ϊ8��   
	range(0xf,800000); //R = 800,000(���� = 10) 
	acac(0xf,1010); //K = 1,010(�仯�� = 619KPPS/SEC2)   
	dcac(0xf,1010); //L = 1,010(�仯�� = 619KPPS/SEC2)    
	acc(0xf,100);  //A = 100(��/���ٶ�=125KPPS/SEC)  
	dec(0xf,100); //D = 100(���ٶ� = 125KPPS/SEC)  
	startv(0xf,100);  //SV = 100(��ʼ�ٶ� = 1,000PPS) 
	speed(0xf,4000);  //V = 4,000(�����ٶ� = 40,000PPS) 
	pulse(0xf,100000); //P = 100,000(��������� = 100,000)  
	lp(0xf,0);  //LP = 0(�߼�λ�ü����� = 0)
	ep(0xf,0);  //EP = 0(ʵ��λ�ü����� = 0)  
	
	return 2;
}

void __stdcall c8401_board_close(void){}
	
BOOL __stdcall c8401_set_pulse_mode(WORD cardno, WORD axis, WORD pulsemode)
{
	int axis_t = 0;
	//оƬѡ��
	select_chip((int)cardno);
	
	//��¼��
	axis_t = (0x01<<axis);
	ptc6014_wregs->_wr0.all = (uint16_t)(axis_t << 8);//��¼wr0
	
	//��¼Ҫд�ļĴ���λ
	switch(pulsemode)
	{
		case 0:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 0;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 0;
			break;
		case 1:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 0;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 1;
			break;
		case 2:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 0;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 1;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 0;
			break;
		case 3:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 0;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 1;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 1;
			break;
		case 4:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 1;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 0;
			break;
		case 5:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 1;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 1;
			break;
		case 6:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 1;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 1;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 0;
			break;
		case 7:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 1;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 1;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 1;
			break;
		default:
			ptc6014_wregs->_wr2[axis].bit.PLSMD = 1;
			ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;
			ptc6014_wregs->_wr2[axis].bit.DIR_L = 0;//����ֵʱ������ΪĬ��ֵ4
			break;
	}
	wreg2(axis_t, ptc6014_wregs->_wr2[axis].all);//д�Ĵ���
	return 1;
}

BOOL __stdcall c8401_set_encoder_mode(WORD cardno, WORD axis, WORD pulsemode, WORD dir, WORD countmode)
{
	int axis_t = 0;
	select_chip((int)cardno);
	
	axis_t = (0x01<<axis);
	ptc6014_wregs->_wr0.all = (axis_t << 8);//��¼wr0
	
	if(pulsemode)//�������巽ʽ
		ptc6014_wregs->_wr2[axis].bit.PINMD = 1;//D9 = 1Ϊ�������巽ʽ
	else
		ptc6014_wregs->_wr2[axis].bit.PINMD = 0;
	
	if(dir)//��ʵ���Ҳ�������߼�λD7
		ptc6014_wregs->_wr2[axis].bit.PLS_L = 1;//���߼�
	else
		ptc6014_wregs->_wr2[axis].bit.PLS_L = 0;//���߼�
	
	switch(countmode)//����D10~D11
	{
		case 0:
			ptc6014_wregs->_wr2[axis].bit.PIND = 2;//4��
			break;
		case 1:
			ptc6014_wregs->_wr2[axis].bit.PIND = 1;//2��
			break;
		case 2:
			ptc6014_wregs->_wr2[axis].bit.PIND = 0;//1��
			break;
		default:
			ptc6014_wregs->_wr2[axis].bit.PIND = 2;//����ֵĬ��4��
			break;
	}
	wreg2(axis_t, ptc6014_wregs->_wr2[axis].all);//д�Ĵ���
	return 1;
}

BOOL __stdcall c8401_set_t_profile(WORD cardno, WORD axis, long sspd, long rspd, double tacc, double tdec)
{
	int axis_t = 0;
	select_chip((int)cardno);
	
	axis_t = (0x01<<axis);
	ptc6014_wregs->_wr0.all = (axis_t << 8);//��¼wr0
	
	
	return 1;
}

