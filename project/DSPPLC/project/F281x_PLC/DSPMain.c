
#include "DSP281x_Device.h"
#include "DSP281x_Examples.h"
#include "lib_sci.h"
#include "plc_instruction.h"
#include "PLCCore.h"
#include "MemManager.h"

#include <stdlib.h>

unsigned  int  *LEDReg  = (unsigned int *)0x2800;    //LED ���ƼĴ���
unsigned  int  *KEY_SEL_REG= (unsigned int *)0x2E00;


extern uint16 plcprg[];
extern uint16 szprg;
extern PLCSystem g_sys;

DEVICE_SCI devSci;

unsigned int ProtocolSend( unsigned int* data, unsigned int sz )
{
	int b = Sci_DbufSend( &devSci, data, sz );
	return b;
}

interrupt void ISRTimer0(void)
{
	API_TimerUp();
	CpuTimer0Regs.TCR.bit.TIF=1;   //
 	PieCtrlRegs.PIEACK.bit.ACK1=1;    //
 	EINT; //��ȫ���ж�
}

void main(void)
{   
	int i;
	Uint16  buf[ MAX_PROTOCL_BUF_SZ * 2 ];
	SCI_BUF txBuf;
	SCI_CONFIG confSci;

	unsigned int KeyValue;
	InitSysCtrl();			//��ʼ��ϵͳ

	DINT;				//���ж� 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//��ʼ��PIE���ƼĴ���
	InitPieVectTable();		//��ʼ��PIE������ 
	InitPeripherals();		//��ʼ������Ĵ��� 
	InitGpio();				//��ʼ��IO��
	//InitScia();				//��ʼ��SCIA�Ĵ���
	
	txBuf.buf = buf;
	txBuf.sz = MAX_PROTOCL_BUF_SZ * 2;

	confSci.LCLK_kHz = 37500;
	confSci.baud = SCIBAUD_19200;
	confSci.stop = SCISTOP_1;
	confSci.parity = SCIPARITY_NONE;
	confSci.data = SCIDATA_8;
	confSci.fifo = 1;
	confSci.intterupt = SCIINT_RX | SCIINT_TX;
	confSci.sciId = SCIID_A;
	confSci.szFFRx = 1;
	confSci.szFFTx = 0;
	confSci.pTxBuf = &txBuf;
	confSci.pRxBuf = 0;
	confSci.pCallBack = API_Protocol;
	
	Sci_Init( &devSci, &confSci );

	EALLOW;	
	PieCtrlRegs.PIEIER1.bit.INTx7=1;
	PieVectTable.TINT0 = &ISRTimer0;
	EDIS;  

	ConfigCpuTimer( &CpuTimer0, 150, 1000 );	

	IER |= M_INT1;		//enable time0 int

	EINT;				//Enable INTM
	ERTM;				//Enable DBGM
   
	*LEDReg=0xff;
   	KeyValue=0x0f;

	EvaRegs.T1CON.bit.TENABLE=1;      //ʹ�ܶ�ʱ��T1��������

	API_InitSystem( (mbyte*)plcprg, szprg, 0, 0 );
	API_InitProtocol();
	API_SetComWriteFun( ProtocolSend );
	
	while( GetBit( g_sys.R[ REG_M ].pState,SYSADDRM_SYSINIT ) )
	{
		if( GetBit( g_sys.R[ REG_M ].pState,SYSADDRM_RUN ) )
		{	
			if( API_LoadProgram() == RES_OK )
			{
				StartCpuTimer0();
				while( GetBit( g_sys.R[ REG_M ].pState,SYSADDRM_RUN ) ) 
				{
					if( g_sys.pPlcMain == g_sys.pPlcStep )//һ��ɨ�����ڵ�
					{
						KeyValue = (*KEY_SEL_REG);
						KeyValue = ~KeyValue;
						for( i = 0; i < 4; ++i )
							API_WriteBit( dcoilX, i, ( KeyValue >> i ) & 0x01 );
						KeyValue = 0;
						for( i = 0; i < 8; ++i )
						{
							KeyValue <<= 1;
							KeyValue |= API_ReadBit( dcoilY,i );
						}
						KeyValue = ~KeyValue & 0x0ff;
						*LEDReg= KeyValue;
					}
					if( API_PLCScan() == RES_ERR ) 
					{
						*LEDReg=0;
						//break;
					}
				}
				StopCpuTimer0();
			}
		}
		//plcֹͣ���н�ִ�����´���
		DELAY_US( 100000 );
		KeyValue = !KeyValue;
		if( KeyValue )
		{
			*LEDReg=1;
		}else
		{
			*LEDReg=0xff;
		}
	}
} 	

