#pragma once
#include "common\StdString.h"
#include <Windows.h>
#include <tchar.h>

//#define NOTECOIL_SYMBOL //����ע����Ȧռ��һ��
#define NAME_MAX_LEN	20

#define COIL_ERROR			-1
#define COIL_NULL			0
#define COIL_VLINE			1
#define COIL_HLINE			2
#define COIL_VHLINE			3
#define MARK_COIL_SYMBOL	0x07
#define COIL_MATHERLINE		(1<<3)
#define COIL_OUTPUTLINE		(2<<3)
#define COIL_OCCUPATION		(3<<3)
#define COIL_BASE			(4<<3)
#define COIL_NOTE			(5<<3)
#define COIL_INPUT			(6<<3)
#define COIL_OUTPUT			(7<<3)
#define COIL_SYMBOL			(8<<3)
#define COIL_LINKER			(9<<3)


class LIBX_API CBaseCoil
{
public:
	enum eFrameType{
		eInputCoil,
		eOutputCoil,
		eFnc,
	};
	/*
	 * ��һ����Ԫ�ֳ�4���֣�1���ϱ����֣�2��Ԫ��ͼ�ꣻ3���±����֣�4���ײ�����
	 * ��Сģʽֻ��1��2
	 * ����ģʽ1��2��3
	 * ���ģʽ1��2��3��4
	 */
	enum eDrawUnitType{	
		eDrawUnitMin,
		eDrawUnitNormal,
		eDrawUnitMax,
	};
	typedef struct tagDrawInfo{		//���ڻ��Ƶ���Ϣ��ʹ�������Ϣ����˱����˹̶���С��������
		int				nRowLen;
		int				nColLen;
		eDrawUnitType	eDUType;		
		int				nLineOffset;	//���ߵ�offset
		int				nSpase;			//-||- �м���
		SIZE			offsetMid;		//�м䶥���ƫ���������ڻ��Ƽ�ͷ��||��
		SIZE			szArrow;		//��ͷ��С
		int				nOutPutLine;	//�����Ȧ���߶γ���
		int				nRadius;		//�����Ȧ�뾶
		int				nHeightVline;	//���ߵĳ��ȣ���Ϊ��ע����Ȧ��ʱ�򣬳���Ҫ����ע����Ȧ�ĸ߶�
		HDC				hdc;
		HFONT			hFont;
		HFONT			hOldFont;
		int				nUnitLen;		//��λ���ȣ�colΪ4����λ���ȣ�rowΪ8����λ����
		COLORREF		colorFont;
		COLORREF		colorNote;
		COLORREF		colorOutNote;
		COLORREF		colorOldFont;
		COLORREF		colorStateColse;	//û��ʹ��
	}DrawInfo,*LPDrawInfo;
	static BOOL PrepareDrawInfo(LPDrawInfo pInfo, int nRowLen, int nColLen, eDrawUnitType eType );
	static void DeleteDrawInfo( LPDrawInfo pInfo );
	static BOOL BeginPaint( HDC hdc,LPDrawInfo pInfo );
	static void EndPaint( LPDrawInfo pInfo );
	static void DrawFrame( LPDrawInfo pInfo, SIZE &posOffset,eFrameType eType,int nColOccupation = 1 );

protected:
	UINT m_uCoilType;

	//��schematic���б����λ����Ϣ�����ڲ�����
	//int m_nPosRow;
	//int m_nPosCol;
	int m_nColOccupation;		//ռ���˼��У�ֻ��ռ�ö��У�����ռ�ö���
	CStdString m_strName;
	CStdString m_strNote;
	
public:
	CStdString m_strIns;

	BOOL m_bLinkIn;//��coil���ӵ���coil�ı�־�����ù������Ǹ�coil����
	CBaseCoil* m_pRightUp;
	CBaseCoil* m_pRight;
	CBaseCoil* m_pLeftDown;

	void* m_userData;

public:
	CBaseCoil( const CBaseCoil& coil );
	CBaseCoil( UINT uType = COIL_BASE,CStdString strName=_T("") );
	virtual ~CBaseCoil(void){}
	static void DrawLine( LPDrawInfo pInfo, UINT uType,SIZE &posOffset );
	void EmptyLink();
	BOOL IsOrphan();
	void SetName( const CStdString& str ){ m_strName = str;}
	CStdString GetName(){ return m_strName; }
	void SetNote( const CStdString& str ){ m_strNote = str; }
	CStdString GetNote(){ return m_strNote; }
	UINT GetType(){ return m_uCoilType; }
	int GetColOccupation(){ return m_nColOccupation; }
	virtual void Draw(LPDrawInfo pInfo, SIZE &posOffset );
};
