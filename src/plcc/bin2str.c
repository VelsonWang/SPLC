//������plc����ת����dsp��ֱ�����еĳ���
#include "base.h"
#include "plcc.h"
//#include "insClass.h"
#include "Memchecker.h"


static int ErrorToCoil( LPPLCCData pData,byte* pos )
{
	printf( "Bin2Str\n��֧�ֵ�Ԫ�����ͣ�������δ֪����!\nλ�ã�0x%x\n", pos - pData->pSource );
	return -1;
}

static int ToCoil( uint16** ppstr, FILE* fout )
{
#define OSZ	5
	PLCCoil coil;
	int16* pu16;
	int32* pu32;
	int32 addr;
	uint16* pstr = *ppstr;
	char strCoil[32];
	char stro[OSZ];
	char* pstro;
	LPCoilItem pCoil; 

	coil.all = *pstr;
	pCoil = GetCoilItemByBin( coil );
	if( pCoil == NULL )
		return -1;
	strcpy( strCoil, pCoil->str );
	++pstr;
	if( pCoil->bin.cargc == 2 )
	{
		pu16 = (int16*)pstr;
		addr = *pu16;
	}else if( pCoil->bin.cargc == 3 )
	{
		pu32 = (int32*)pstr;
		addr = *pu32;
	}else
		return -1;
	*ppstr += pCoil->bin.cargc;
	//if( dcoilPV != pCoil->bin.all )
	//	fwrite( " ",1, 1,fout );
	if( dcoilX == pCoil->bin.all || dcoilY == pCoil->bin.all )
	{
		pstro = stro + OSZ - 1;
		*pstro = 0;
		while( addr )
		{
			--pstro;
			*pstro = ( addr % 8 ) + '0';
			addr /= 8;
		}
		sprintf( strCoil + 1,"%03s",pstro );
	}else if( dcoilPV == pCoil->bin.all )
	{
		ToCoil( ppstr,fout );
		sprintf( strCoil + 1,"%d",addr );
	}else
		sprintf( strCoil + 1,"%d",addr );
	fwrite( strCoil,1, strlen(strCoil),fout );
	return 0;
}

static int ErrorIns( LPPLCCData pData, byte* pos )
{
	printf( "Bin2Str\n��֧�ֵ�ָ�������δָ֪��!\nλ�ã�0x%x\n", pos - pData->pSource );//��֧�ֵ�ָ�δָ֪��
	return -1;
}

int Bin2Str( LPPLCCData pData )
{
	int nArg;
	PLCIns bin;
	LPInsItem pInsItem;
	uint16* pstrEnd;
	uint16* pstr;

	if( pData->szSource % 2 )
		return -1;
	pstr = (uint16*)pData->pSource;
	pstrEnd = pstr + pData->szSource / 2;
	if( !initInsHash() )
		return -1;
	while( pstr < pstrEnd )
	{
		bin.all = *pstr;
		++pstr;
		pInsItem = GetInsItemByBin( bin );
		if( pInsItem == NULL )
			return ErrorIns( pData, (byte*)pstr );
		if( pInsItem->bin.all != dinsP )
			fwrite( pInsItem->str,1,strlen(pInsItem->str),pData->fout );
		nArg = pInsItem->argc;
		while( nArg-- )
		{
			if( pInsItem->bin.all != dinsP )
				fwrite( "\t\t",2, 1,pData->fout );
			if( ToCoil( &pstr, pData->fout ) == -1 )
				return ErrorToCoil( pData, (byte*)pstr );
		}
		fwrite( "\n",1,1,pData->fout );
	}
	return 0;
}
