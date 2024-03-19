#include "PLCCore.h"
#include "MemManager.h"
#include "insClass.h"

# pragma warning (disable:4996)

void M_DumpMem( PLPLCSystem psys )
{
	FILE* fb;
	fb = fopen( "mem.dump","wb" );
	if( fb == NULL )
		return;
	fwrite( psys->pBitMap, sizeof(uint16), psys->nBitMapsz, fb );
	fwrite( psys->pDataMap, sizeof(uint16), psys->nDataMapsz, fb );
	fwrite( psys->R[REG_D].pData, sizeof( uint16 ),psys->R[REG_D].sz, fb );
	fclose( fb );
}

void M_dDump( mbyte* pdata, uint16 sz )
{
	FILE* fb;
	fb = fopen( "c:\\program.dump","wb" );
	if( fb == NULL )
		return;
	fwrite( pdata, sizeof(mbyte), sz, fb );
	fclose( fb );
}

//����32λ�˷�
uint16 g_mun1[2],g_mun2[2],g_result[4];
uint16 g_tmp1[3];
uint16 g_tmp2[3];

void M_MulNum32( uint32 num1, uint32 num2, uint32* resultH, uint32* resultL )
{
	int i,j;
	uint32* p32 = (uint32*)g_mun1;
	*p32 = num1;
	p32 = (uint32*)g_mun2;
	*p32 = num2;
	p32 = (uint32*)g_result;
	*p32++ = 0;
	*p32++ = 0;
	g_tmp1[0] = g_mun1[0];
	g_mun1[0] = g_mun1[1];
	g_mun1[1] = g_tmp1[0];
	g_tmp1[0] = g_mun2[0];
	g_mun2[0] = g_mun2[1];
	g_mun2[1] = g_tmp1[0];
	g_tmp1[0] = 0;
	g_tmp1[1] = 0;
	g_tmp1[2] = 0;
	g_tmp2[0] = 0;
	g_tmp2[1] = 0;
	g_tmp2[2] = 0;
__asm{
;Step1:
	mov ax,g_mun1+2
	mov bx,g_mun2+2
	mul bx
	mov g_tmp1+4,ax
	mov cx,dx
	;-------Number A �ĵ�16λ���� Number B �ĵ�ʮ��λ,�������g_tmp1+4
	;��λ����CX
	mov ax,g_mun1
	mov bx,g_mun2+2
	mul bx
	mov g_tmp1+2,ax
	add g_tmp1+2,cx
	adc g_tmp1,dx
	;-------Number A �ĸ�16λ���� Number B �ĵ�ʮ��λ,�������g_tmp1+4
	;�������g_tmp1+2,��g_tmp1+2����һ����˵Ľ�λ��Ӵ���g_tmp1+2
	;���ڶ�����˵Ľ�λ����������� g_tmp1(ǰһλ����ӿ��ܲ�����λ)
;Step2:
	mov ax,g_mun1+2
	mov bx,g_mun2
	mul bx
	mov g_tmp2+4,ax
	mov cx,dx
	;-------ͬ��
	mov ax,g_mun1
	mov bx,g_mun2
	mul bx
	mov g_tmp2+2,ax
	add g_tmp2+2,cx
	adc g_tmp2,dx
	;-------ͬ��
;SUM:
	mov ax,g_tmp1+4
	mov g_result+6,ax

	mov ax,g_tmp2+4
	add g_tmp1+2,ax
	mov ax,g_tmp1+2
	mov g_result+4,ax

	mov ax,g_tmp2+2
	adc g_tmp1,ax
	mov ax,g_tmp1
	mov g_result+2,ax

	mov ax,g_tmp2
	adc g_result,ax
	;-------��λ���
	}
	for ( i = 0, j = sizeof( g_result ) / sizeof( uint16 ) - 1; i < j; ++i,--j )
	{
		g_tmp1[0] = g_result[i];
		g_result[i] = g_result[j];
		g_result[j] = g_tmp1[0];
	}
	p32 = (uint32*)g_result;
	*resultL = *p32++;
	*resultH = *p32;
}

#pragma warning(default:4996)
