#include "tc6014.h"

TC6014_TypeDef tc6014s_wregs[2];
TC6014_TypeDef* ptc6014_wregs;

uint32_t adr = TC6014A_BASE_ADDR;

//�ı������оƬ
void select_chip(int chip)
{
	if(chip == TC6014A)
	{
		adr = TC6014A_BASE_ADDR;
		ptc6014_wregs = &tc6014s_wregs[0];
	}
	else
	{
		adr = TC6014B_BASE_ADDR;
		ptc6014_wregs = &tc6014s_wregs[1];
	}
}

//���ڲ����ĸ�оƬ
int which_chip(void)
{
	if(adr == TC6014A_BASE_ADDR)
		return TC6014A;
	else
		return TC6014B;
}

// wreg1(��ָ��,����)------------д��Ĵ���1 �趨
void wreg1(int axis,int wdata)
{
	//D8~D11λΪXYZU��ѡ��λ������
	// 1      �����1��
	// 2      �����2��
	// 4      �����3��
	// 8      �����4��
	//0x0f�����л�����
	outpw(adr+wr0, (axis << 8) + 0xf);//��ָ��
	outpw(adr+wr1, wdata);
}

// wreg2(��ָ��,����)-------------д��Ĵ���2 �趨
void wreg2(int axis,int wdata)
{
	outpw(adr+wr0, (axis << 8) + 0xf);//��ָ��
	outpw(adr+wr2, wdata);
}

// wreg3(��ָ��,����)-------------д��Ĵ���3 �趨
void wreg3(int axis,int wdata)
{
	outpw(adr+wr0, (axis << 8) + 0xf);//��ָ��
	outpw(adr+wr3, wdata);
}

// command(��ָ��,�������)-----����д��
void command(int axis,int cmd)
{
	outpw(adr+wr0, (axis << 8) + cmd);
}

// range(��ָ��,����)----------------��Χ(R) �趨
void range(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x00);
}

// acac(��ָ��,����)----------------�仯��(K)�趨
void acac(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x01);
}

// dcac(��ָ��,����)----------------�仯��(L)�趨
void dcac(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x0e);
}


// acc(��ָ��,����)------------------��/���ٶ�(A)�趨
void acc(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x02);
}

// dec(��ָ��,����) -------------------���ٶ�(D) �趨
void dec(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x03);
}

// startv(��ָ��,����) -----------------��ʼ�ٶ�(SV) �趨
void startv(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x04);
}

// speed(��ָ��,����) -----------------�����ٶ�(V) �趨
void speed(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x05);
}

// pulse(��ָ��,����) -----------------���������/�յ�(P) �趨
void pulse(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x06);
}

// decp(��ָ��,����) -----------------�ֶ����ٵ�(DP) �趨
void decp(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x07);
}

// center(��ָ��,����) ----------------Բ�����ĵ�(C) �趨
void center(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x08);
}

// lp(��ָ��,����) --------------------�߼�λ�ü�����(LP)�趨
void lp(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x09);
}

// ep(��ָ��,����) ------------------ʵ��λ�ü�����(EP)�趨
void ep(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x0a);
}

// compp(��ָ��,����) ------------COMP + (CP) �趨
void compp(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x0b);
}

// compm(��ָ��,����) -----------COMP - (CM) �趨
void compm(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x0c);
}

// accofst(��ָ��,����) -----------���ټ�����ƫ��(AO)�趨
void accofst(int axis,long wdata)
{
	outpw(adr+wr7, (wdata >> 16) & 0xffff);
	outpw(adr+wr6, wdata & 0xffff);
	outpw(adr+wr0, (axis << 8) + 0x0d);
}

//---------------------------------ԭ�����ٶ�(HV)�趨
void hsspeed(int axis,int wdata)
{
	outpw(adr+wr6, wdata);
	outpw(adr+wr0, (axis << 8) + 0x61);
}

//---------------------------------�ⲿģʽ(EM)�趨
void expmode(int axis,int em6data,int em7data)
{
	outpw(adr+wr6, em6data);
	outpw(adr+wr7, em7data);
	outpw(adr+wr0, (axis << 8) + 0x60);
}

//---------------------------------ͬ������ģʽ(SM)�趨
void syncmode(int axis,int sm6data,int sm7data)
{
	outpw(adr+wr6, sm6data);
	outpw(adr+wr7, sm7data);
	outpw(adr+wr0, (axis << 8) + 0x64);
}

// readlp(��ָ��)---------------------�߼�λ�ü�������ֵ(LP)����
long readlp(int axis)
{
	long a;long d6;long d7;
	outpw(adr+wr0, (axis << 8) + 0x10);
	d6 = inpw(adr+rr6);d7 = inpw(adr+rr7);
	a = d6 + (d7 << 16);
	return(a);
}

// readep(��ָ��)--------------------ʵ��λ�ü�������ֵ(EP)����
long readep(int axis)
{
	long a;long d6;long d7;
	outpw(adr+wr0, (axis << 8) + 0x11);
	d6 = inpw(adr+rr6);d7 = inpw(adr+rr7);
	a = d6 + (d7 << 16);
	return(a);
}

// wait(��ָ��)------------------------����������
void waitaxis(int axis)
{
	while(inpw(adr+rr0) & axis);
}
             
// next_wait( )--------------------------�������岹��һ�������趨
void next_wait(void)       
{
	while((inpw(adr+rr0) & 0x0200) == 0x0);
}

// bp_wait( )----------------------------��BP �岹��һ�������趨
void bp_wait(void)        
{
	while((inpw(adr+rr0) & 0x6000) == 0x6000);
}

// homesrch( )---------------------ȫ��ԭ����
void homesrch(void)
{     
	speed(0x3,2000);// 1��2����ٶ���2000   
	hsspeed(0x3,50);   
	pulse(0x1,3500); //��һ��������� 
	pulse(0x2,700);  //�ڶ���������� 

	     
	speed(0x4,40);  //��3����ٶ���40  
	hsspeed(0x4,40);   
	pulse(0x4,20);  //�������������  
	     
	hsspeed(0x8,30);  
	command(0xf,0x62);//�������Զ�ԭ��ع�   
	waitaxis(0xf);  //�ȴ���������  
	if(inpw(adr+rr0) & 0x0010)  
	{
		printf("X-axis Home Search Error \n");
	}
	if(inpw(adr+rr0) & 0x0020)
	{
		printf("Y-axis Home Search Error \n");
	}
	if(inpw(adr+rr0) & 0x0040)
	{
		printf("Z-axis Home Search Error \n");
	}
	if(inpw(adr+rr0) & 0x0080)
	{
		printf("U-axis Home Search Error \n");
	}
}

void test(char flag)
{
	int  count;
	outpw(adr+wr0, 0x8000);//�����λ
	for(count = 0; count < 50; ++count);

	//------------ȫ��ģʽ�趨------------
	command(0xf,0xf);//��һ�����л�����ѡ����һ����
	outpw(adr+wr1, 0x0000);//ģʽ�Ĵ���1 00000000 00000000  
	outpw(adr+wr2, 0x0000);//ģʽ�Ĵ���2 00000000 00000000  
	outpw(adr+wr3, 0x0000);//ģʽ�Ĵ���3 00000000 00000000  
	//expmode(0x3,0x5d08,0x497f); //��һ�����ⲿģʽ�趨 

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
	
	//wr4��wr5�����ṫ���
	outpw(adr+wr4, 0x0303); //nOUT3~0����͵�ƽ      
	//outpw(adr+wr5, 0x0124); //2�����ٶȺ㶨��XΪ���ᣬYΪ���ᣬZΪ����
	
//	acc(0x3,200);   
//	speed(0x3,4000);  
//	pulse(0x1,80000);  
//	pulse(0x2,40000);   
	//command(0xf,0x20); //������������ 
	if(flag)
		command(0xf,0x20); //������������
	else
		command(0xf,0x21); //������������
	waitaxis(0xf);
}

/*
int main(void)
{
	int  count;
	outpw(adr+wr0, 0x8000);//�����λ
	for(count = 0; count < 2; ++count);

	//------------ȫ��ģʽ�趨------------
	command(0x3,0xf);//��һ�����л�����ѡ����һ����
	outpw(adr+wr1, 0x0000);//ģʽ�Ĵ���1 00000000 00000000  
	outpw(adr+wr2, 0xe000);//ģʽ�Ĵ���2 11100000 00000000  
	outpw(adr+wr3, 0x0000);//ģʽ�Ĵ���3 00000000 00000000  
	expmode(0x3,0x5d08,0x497f); //��һ�����ⲿģʽ�趨 

	//--------ȫ��������������趨----
	accofst(0x3,0);//A0 = 0 ����ƫ��Ϊ0��Ĭ��Ϊ8��   
	range(0x3,800000); //R = 800,000(���� = 10) 
	acac(0x3,1010); //K = 1,010(�仯�� = 619KPPS/SEC2)   
	dcac(0x3,1010); //L = 1,010(�仯�� = 619KPPS/SEC2)    
	acc(0x3,100);  //A = 100(��/���ٶ�=125KPPS/SEC)  
	dec(0x3,100); //D = 100(���ٶ� = 125KPPS/SEC)  
	startv(0x3,100);  //SV = 100(��ʼ�ٶ� = 1,000PPS) 
	speed(0x3,4000);  //V = 4,000(�����ٶ� = 40,000PPS) 
	pulse(0x3,100000); //P = 100,000(��������� = 100,000)  
	lp(0x3,0);  //LP = 0(�߼�λ�ü����� = 0)
	ep(0x3,0);  //EP = 0(ʵ��λ�ü����� = 0)  
	
	command(0xc,0xf);  //���������л�����ѡ����������
	outpw(adr+wr1, 0x0000);                                            
	outpw(adr+wr2, 0x0000);  
	outpw(adr+wr3, 0x0000);   
	expmode(0x4,0x5d08,0x01c4); //�������ⲿģʽ�趨  
	expmode(0x8,0x5d08,0x010c); //�������ⲿģʽ�趨  
	 
	accofst(0xc,0);  
	range(0xc,800000);  
	acac(0xc,1010);    
	dcac(0xc,1010);   
	acc(0xc,100);    
	dec(0xc,100);   
	startv(0xc,50); //SV = 50(��ʼ�ٶ� = 500PPS)   
	speed(0xc,40);  //V = 40(�����ٶ� = 400PPS)  
	pulse(0xc,10); //P = 10(��������� = 10)   
	lp(0xc,0);    
	
	//wr4��wr5�����ṫ���
	outpw(adr+wr4, 0x0000); //nOUT3~0����͵�ƽ      
	outpw(adr+wr5, 0x0124); //2�����ٶȺ㶨��XΪ���ᣬYΪ���ᣬZΪ���� 

	     
	acc(0x3,200);   
	speed(0x3,4000);  
	pulse(0x1,80000);  
	pulse(0x2,40000);   
	command(0x3,0x20); //������������ 
	waitaxis(0x3);                           
	    
	wreg3(0x1, 0x0002); //��һ��ʹ�ü��ٶȵ���ֵ 
	acc(0x1,200);  
	dec(0x1,50);   
	speed(0x1,4000);   
	pulse(0x1,80000);   
	command(0x1,0x20);  
	waitaxis(0x1);                         
	wreg3(0x1, 0x0000);                  
	    
	wreg3(0x3, 0x0004); //��һ����ʹ��s���߼�/����  
	acac(0x3,1010);    
	acc(0x3,200);    
	speed(0x3,4000);   
	pulse(0x1,50000);   
	pulse(0x2,25000);   
	command(0x3,0x21);  //������������  
	waitaxis(0x3);
	wreg3(0x3, 0x0000);                 
	     
	startv(0x4,40);   
	speed(0x4,40);    
	pulse(0x4,700);    
	command(0x4,0x20);   
	waitaxis(0x4);   
	pulse(0x4,350);  
	command(0x4,0x21);  
	waitaxis(0x4);    
	                                          
	outpw(adr+wr5, 0x0124);  
	range(0x1,800000);   
	range(0x2,1131371);   
	speed(0x1,100);   
	pulse(0x1,5000);   
	pulse(0x2,-2000);  
	command(0x0,0x30);        
	waitaxis(0x3);
	                                           
	outpw(adr+wr5, 0x0124);  
	range(0x1,800000);  
	range(0x2,1131371);   
	speed(0x1,100);   
	center(0x1,-5000);  
	center(0x2,0);                     
	pulse(0x1,0);                         
	pulse(0x2,0);                        
	command(0x0,0x33);                   
	waitaxis(0x3);
	                                            
	speed(0x1,1);    
	command(0,0x36); //λģʽ�岹 
	outpw(adr+bp1p, 0x0000);  
	outpw(adr+bp1m, 0x2bff);
	outpw(adr+bp2p, 0xffd4);
	outpw(adr+bp2m, 0x0000);
	command(0,0x38);
	outpw(adr+bp1p, 0xf6fe); 
	outpw(adr+bp1m, 0x0000);
	outpw(adr+bp2p, 0x000f);
	outpw(adr+bp2m, 0x3fc0);
	command(0,0x38);
	outpw(adr+bp1p, 0x1fdb);  
	outpw(adr+bp1m, 0x0000);
	outpw(adr+bp2p, 0x00ff);
	outpw(adr+bp2m, 0xfc00);
	command(0,0x38);
	command(0,0x34);
	bp_wait();    
	outpw(adr+bp1p, 0x4000);  
	outpw(adr+bp1m, 0x7ff5);
	outpw(adr+bp2p, 0x0000);
	outpw(adr+bp2m, 0x0aff);
	command(0,0x38);
	command(0,0x37);  
	waitaxis(0x3);  
	                                   
	speed(0x1,100);  
	pulse(0x1,4500);  
	pulse(0x2,0);
	command(0,0x30);
	next_wait();    
	center(0x1,0);    
	center(0x2,1500);
	pulse(0x1,1500);
	pulse(0x2,1500);
	command(0,0x33);
	next_wait();
	pulse(0x1,0);   
	pulse(0x2,1500);
	command(0,0x30);
	next_wait();
	center(0x1,-1500);   
	center(0x2,0);
	pulse(0x1,-1500);
	pulse(0x2,1500);
	command(0,0x33);
	next_wait();
	pulse(0x1,-4500);  
	pulse(0x2,0);
	command(0,0x30);
	next_wait();
	center(0x1,0);   
	center(0x2,-1500);
	pulse(0x1,-1500);
	pulse(0x2,-1500);
	command(0,0x33);
	next_wait();
	pulse(0x1,0);    
	pulse(0x2,-1500);
	command(0,0x30);
	next_wait();
	center(0x1,1500);   
	center(0x2,0);
	pulse(0x1,1500);
	pulse(0x2,-1500);
	command(0,0x33);
	waitaxis(0x3);
	range(0x6,800000);   
	acc(0x6,400);    
	startv(0x6,50);    
	speed(0x6,3000);   
	pulse(0x2,50000);  
	pulse(0x4,10000);  
	compp(0x2,15000);  
	lp(0x6,0);   
	syncmode(0x2,0x2001,0x0000);  
	    
	    
	syncmode(0x4,0x0000,0x0001);  
	     
	command(0x2,0x20);   
	waitaxis(0x6);  
	return 0;
}
*/
