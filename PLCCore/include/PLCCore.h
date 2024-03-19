/*
 *	�������汾����������
 *	���豸��ط��뿪��
 */
/*
 *	�ڶ����汾����������
 *	�ṩ���û��Ľӿ�
 */

/*
 *	API_FUN �ṩ��
 *
 *
 */
#ifndef __PLCCORE_H__
#define __PLCCORE_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "apis.h"
#include "dataMisc.h"
#include "RunTimeError.h"
#include "insClass.h"

#define ENTIMER_INVALUED	0xffff
#define REGP_INVALUED		0xffffffff

#define ALIGNED_TYPE		uint16
#define MACHINE_ALIGNED_SIZE	16

//����ĺ���������ϵͳ��Դ
//�����ʱ������� MACHINE_ALIGNED_SIZE �����

//�ŷ��������
#define MACHINE_Y_OFFSET	64

//λԪ��
#define REGSZ_X		256
#define REGSZ_Y		256
#define REGSZ_M		4096
#define REGSZ_S		1024
#define REGSZ_L		1024		//�� REGSZ_T + REGSZ_C ΪT��C�Ĺ�����־λ

//��Ԫ��
#define REGSZ_T		256
#define REGSZ_C		256
#define REGSZ_D		4096
#define REGSZ_V		256

//˫�֣���ַ��Ԫ��
#define REGSZ_P		64		//ע�⣺P��32λ�����������Ա���ƫ����

#define REG_COUNT	10
#define REG_UPDATE	5		//��Ҫ����reg�����index ����0��ʼ��

#define REG_X		0
#define REG_Y		1
#define REG_M		2
#define REG_S		3
#define REG_T		4
#define REG_C		5
#define REG_D		6
#define REG_P		7
#define REG_V		8
#define REG_L		9

//������û�ж�ӦReg��
#define REG_K		0xa0
#define REG_H		0xa1
#define REG_PV		0xa2
#define REG_DK		0xb0
#define REG_DH		0xb1



#define DCOUNTER_ADDR	200 //˫�����������ʼ��ַλ��
#define TWORK_ADDR		REGSZ_L - REGSZ_T - REGSZ_C //T������־λ
#define CWORK_ADDR		REGSZ_L - REGSZ_C			//C������־λ

//#define MBYTE2REG( n )	( ( n & 0x0fff ) - dcoilX )
#define MBYTE2REG( n )	( n )

//SZ_TIMER_* �Ĵ�Сע���REGSZ_T��С�Ĺ�ϵ
#define SZ_TIMER_10MS	46
#define SZ_TIMER_100MS	206
#define SZ_TIMER_1S		4

#define SZ_BSTACK		64
#define SZ_MSTACK		64
//#define SZ_LSTATA		512	//�Ƶ���REGSZ_L
#define SZ_FSTACK		64	//(ע�⣺�����REG_Pһ����32λ��)����Ƕ��ʹ�õĶ�ջ
//#define SZ_TIMERLIST	128	//��ʱ����̬�б��С����ͬʱ�򿪵����ʱ����Ŀ,�����ɶ�ʱ������

//��ϵͳ��ַ���
#define SZ_SYSREG_M		256
#define SZ_SYSREG_D		256

//ϵͳ��ַ
//M��ַ
#define SYSADDR_OFFSETM		( REGSZ_M - SZ_SYSREG_M )	
#define SYSADDRM_RUN		( SYSADDR_OFFSETM )						
#define SYSADDRM_INITP		( SYSADDR_OFFSETM + 2 )					
#define SYSADDRM_ERROR		( SYSADDR_OFFSETM +4 )					

#define SYSADDRM_SYSINIT	( SYSADDR_OFFSETM + 10 )	

#define SYSADDRM_FORCEMODE	( SYSADDR_OFFSETM + 35 )	
#define SYSADDRM_FORCERUN	( SYSADDR_OFFSETM + 36 )
#define SYSADDRM_FORCESTOP	( SYSADDR_OFFSETM + 37 )
#define SYSADDRM_RELOAD		( SYSADDR_OFFSETM + 38 )

#define SYSADDRM_MONITORSTART	( SYSADDR_OFFSETM + 40 )

#define SYSADDRM_LIMITPOINT10	( SYSADDR_OFFSETM + 50 ) //��1�����޵�
#define SYSADDRM_LIMITPOINT11	( SYSADDR_OFFSETM + 51 ) //��1���Ҽ��޵�
#define SYSADDRM_LIMITPOINT20	( SYSADDR_OFFSETM + 52 )
#define SYSADDRM_LIMITPOINT21	( SYSADDR_OFFSETM + 53 )
#define SYSADDRM_LIMITPOINT30	( SYSADDR_OFFSETM + 54 )
#define SYSADDRM_LIMITPOINT31	( SYSADDR_OFFSETM + 55 )
#define SYSADDRM_LIMITPOINT40	( SYSADDR_OFFSETM + 56 )
#define SYSADDRM_LIMITPOINT41	( SYSADDR_OFFSETM + 57 )
#define SYSADDRM_LIMITPOINT50	( SYSADDR_OFFSETM + 58 )
#define SYSADDRM_LIMITPOINT51	( SYSADDR_OFFSETM + 59 )
#define SYSADDRM_LIMITPOINT60	( SYSADDR_OFFSETM + 60 ) //��6�����޵�
#define SYSADDRM_LIMITPOINT61	( SYSADDR_OFFSETM + 61 ) //��6���Ҽ��޵�
#define SYSADDRM_LIMITPOINT70	( SYSADDR_OFFSETM + 62 )
#define SYSADDRM_LIMITPOINT71	( SYSADDR_OFFSETM + 63 )
#define SYSADDRM_LIMITPOINT80	( SYSADDR_OFFSETM + 64 )
#define SYSADDRM_LIMITPOINT81	( SYSADDR_OFFSETM + 65 )
#define SYSADDRM_LIMITPOINT90	( SYSADDR_OFFSETM + 66 )
#define SYSADDRM_LIMITPOINT91	( SYSADDR_OFFSETM + 67 )
#define SYSADDRM_LIMITPOINTa0	( SYSADDR_OFFSETM + 68 )
#define SYSADDRM_LIMITPOINTa1	( SYSADDR_OFFSETM + 69 )

#define SYSADDRM_MACHINESTOP1	( SYSADDR_OFFSETM + 70 )
#define SYSADDRM_MACHINESTOP2	( SYSADDR_OFFSETM + 71 )
#define SYSADDRM_MACHINESTOP3	( SYSADDR_OFFSETM + 72 )
#define SYSADDRM_MACHINESTOP4	( SYSADDR_OFFSETM + 73 )
#define SYSADDRM_MACHINESTOP5	( SYSADDR_OFFSETM + 74 )
#define SYSADDRM_MACHINESTOP6	( SYSADDR_OFFSETM + 75 )
#define SYSADDRM_MACHINESTOP7	( SYSADDR_OFFSETM + 76 )
#define SYSADDRM_MACHINESTOP8	( SYSADDR_OFFSETM + 77 )
#define SYSADDRM_MACHINESTOP9	( SYSADDR_OFFSETM + 78 )
#define SYSADDRM_MACHINESTOPa	( SYSADDR_OFFSETM + 79 )

#define SYSADDRM_DCOUNTER	( SYSADDR_OFFSETM + DCOUNTER_ADDR )	

//D��ַ
#define SYSADDR_OFFSETD		( REGSZ_D - SZ_SYSREG_D )
#define SYSADDRD_WATCHDOG	( SYSADDR_OFFSETD )
#define SYSADDRD_VERTION	( SYSADDR_OFFSETD + 1 )
#define SYSADDRD_RAMSIZE	( SYSADDR_OFFSETD + 2 )
#define SYSADDRD_ERROR		( SYSADDR_OFFSETD + 4 )
#define SYSADDRD_ERRORARG	( SYSADDR_OFFSETD + 5 ) //32λ

#define SYSADDRD_SCANTIME	( SYSADDR_OFFSETD + 10 )
#define SYSADDRD_SCANSTEP	( SYSADDR_OFFSETD + 11 )
#define SYSADDRD_SECOND		( SYSADDR_OFFSETD + 13 )
#define SYSADDRD_MINITER	( SYSADDR_OFFSETD + 14 )
#define SYSADDRD_HOURE		( SYSADDR_OFFSETD + 15 )
#define SYSADDRD_DAY		( SYSADDR_OFFSETD + 16 )
#define SYSADDRD_MOUTH		( SYSADDR_OFFSETD + 17 )
#define SYSADDRD_YEAR		( SYSADDR_OFFSETD + 18 )
#define SYSADDRD_WEEK		( SYSADDR_OFFSETD + 19 )

#define SYSADDRD_STEMPSET		( SYSADDR_OFFSETD + 36 )

#define SYSADDRD_SCANTIME		( SYSADDR_OFFSETD + 10 )
#define SYSADDRD_MONITORSTART	( SYSADDR_OFFSETD + 40 )
#define SYSADDRD_MONITORLEN		( SYSADDR_OFFSETD + 100 )

#define SYSADDRD_AIXSPOS1		( SYSADDR_OFFSETD + 150 ) //��1��λ��
#define SYSADDRD_AIXSPOS2		( SYSADDR_OFFSETM + 152 ) 
#define SYSADDRD_AIXSPOS3		( SYSADDR_OFFSETM + 154 )
#define SYSADDRD_AIXSPOS4		( SYSADDR_OFFSETM + 156 )
#define SYSADDRD_AIXSPOS5		( SYSADDR_OFFSETM + 158 )
#define SYSADDRD_AIXSPOS6		( SYSADDR_OFFSETD + 160 ) 
#define SYSADDRD_AIXSPOS7		( SYSADDR_OFFSETM + 162 ) 
#define SYSADDRD_AIXSPOS8		( SYSADDR_OFFSETM + 164 )
#define SYSADDRD_AIXSPOS9		( SYSADDR_OFFSETM + 166 )
#define SYSADDRD_AIXSPOSa		( SYSADDR_OFFSETM + 168 )

//��Ӧ���������ţ�����������ָ����ģ����Բ�Ӧ�ò���D��ַ
//#define SYSADDRD_FUNSTATCK	( REGSZ_D - REGSZ_P - SZ_FSTACK )//������ں���P
//#define SYSADDRD_FUNP		( REGSZ_D - REGSZ_P )

#define SYS_VERTION			26100	

//����ϵͳ��Դ����

#define MAX_ARGC	6

typedef struct tagReg{
	union{
		uint16* pData;
		uint32* pData32;
	};
	uint16* pState;
	uint16* pLastState;
	uint16* pUpdate;
	uint32 uUpdateFlag;		//�������ø���laststate�ı�־λ
	uint32 uBlocksz:16;		//���¿�Ĵ�С
	uint32 sz:16;
}Reg,*LPReg;

typedef struct tagStaticLink{
	uint16 id;
	struct tagStaticLink* pNext;
	uint16* pCounter;
	mbyte* pTimeOut;
}StaticLink,*LPStaticLink;

typedef struct tagSystemConf{
	PLCCallBack fncCallBack;

	uint16*	pFlash;
	uint16	szFlash;
	mbyte* pPlcMain;		//plc���
	mbyte* pPlcStep;		//
	mbyte* pPlcPrgEnd;
	mbyte* pPlcScanPos;
	uint16* pBitMap;	//��Ԫ����ַ��
	uint16 nBitMapsz;
	uint16* pDataMap;	//���ݵ�ַ��
	uint16 nDataMapsz;
	Reg R[REG_COUNT];
	uint16 nSysMAddr;
	uint16 nSysDAddr;

	Stack bStack;	//���״̬stack����anb��orb ���֧��64 sa:SZ_BSTACK
	Stack mStack;	//ĸ�ߵ�״̬stack ����mps��mrd��mpp ���֧��64 sa:SZ_MSTACK
	//Reg regLS;		//(�Ƶ���REG_L)���������״̬ ����ldp ldf�� sa:SZ_LSTATA
	Stack pFStack;		//������ջ sa:SZ_FSTACK
	Stack bFStack;		//���溯����ĸ��״̬
	mbyte bMatherLine;	//ĸ��״̬
	
	StaticLink sLinkTimer[ REGSZ_T ];	//��̬��ʱ������ id ΪENTIMER_INVALUEDʱδ��ռ�� sa��ENTIMER_INVALUED
	LPStaticLink pEnT1ms;				//��̬��ʱ������ʹ�ܶ�ʱ��ʱ����ʱ�������б���ʼ��ʱ
	LPStaticLink pEnT10ms;					
	LPStaticLink pEnT100ms;
	mbyte nTimerCount;

	uint16 wdgSet;
	uint16 wdgCount;
	int	   iStl;
	uint16 uStep;

	uint16 uScanTime;
	InsClassFuns iClassFuns;
}PLCSystem,*PLPLCSystem;


//��ʱ���б�
api_res AddToTimerList( mbyte id,mbyte* pTimeOut );
void ReMoveTimerNod( mbyte id );
void ResetTimerList( void );

void WriteBitCoil( LPReg preg, uint16 addr, mbyte bs );
void UpdateBitCoil( LPReg preg, uint16 addr );
api_res UpdateLastStata( void );

PLPLCSystem GetSystem( void );
api_res GetFormatCoil( mbyte nCoil, uint16 addr, LPReg* ppCoil, uint16* paddr );



#ifdef __cplusplus
}
#endif
#endif

