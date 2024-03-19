#pragma once

#include "..\PLCCore\plc_instruction.h"

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

class CBaseCoil
{
public:
	typedef struct tagDrawInfo{		//���ڻ��Ƶ���Ϣ��ʹ�������Ϣ����˱����˹̶���С��������
		int nRowLen;
		int nColLen;
		int nLineOffset;	//���ߵ�offset
		int nSpase;			//-||- �м���
		SIZE offsetMid;		//�м䶥���ƫ���������ڻ��Ƽ�ͷ��||��
		SIZE szArrow;		//��ͷ��С
		int nOutPutLine;	//�����Ȧ���߶γ���
		int nRadius;		//�����Ȧ�뾶
		int nHeightVline;	//���ߵĳ��ȣ���Ϊ��ע����Ȧ��ʱ�򣬳���Ҫ����ע����Ȧ�ĸ߶�
		HDC hdc;
		HFONT hFont;
		HFONT hOldFont;
		int nUnitLen;		//��λ���ȣ�colΪ4����λ���ȣ�rowΪ8����λ����
		COLORREF colorFont;
		COLORREF colorNote;
		COLORREF colorOutNote;
		COLORREF colorOldFont;
	}DrawInfo,*LPDrawInfo;
	static BOOL PrepareDrawInfo(LPDrawInfo pInfo, int nRowLen, int nColLen );
	static void DeleteDrawInfo( LPDrawInfo pInfo );
	static BOOL BeginPaint( HDC hdc,LPDrawInfo pInfo );
	static void EndPaint( LPDrawInfo pInfo );

protected:
	UINT m_uCoilType;

	//��schematic���б����λ����Ϣ�����ڲ�����
	//int m_nPosRow;
	//int m_nPosCol;
	int m_nColOccupation;		//ռ���˼��У�ֻ��ռ�ö��У�����ռ�ö���
	LPTSTR m_strName;
	LPTSTR m_strNote;
	UINT32 m_uMark;
	void*	m_pUserData;
public:
	CString m_strIns;

	BOOL m_bLinkIn;//��coil���ӵ���coil�ı�־�����ù������Ǹ�coil����
	CBaseCoil* m_pRightUp;
	CBaseCoil* m_pRight;
	CBaseCoil* m_pLeftDown;

public:
	CBaseCoil( const CBaseCoil& coil );
	CBaseCoil( UINT uType = COIL_BASE,LPTSTR strName = NULL );
	virtual ~CBaseCoil(void){ if(m_strName) delete[] m_strName; if(m_strNote) delete[] m_strNote; }
	static void DrawLine( LPDrawInfo pInfo, UINT uType,SIZE &posOffset );
	LPTSTR GetName(){ return m_strName; }
	void EmptyLink();
	BOOL IsOrphan();
	BOOL SetName( LPTSTR str );
	BOOL SetNote( LPTSTR str );
	UINT GetType(){ return m_uCoilType; }
	int GetColOccupation(){ return m_nColOccupation; }
	void* GetUserData(){ return m_pUserData; }
	void SetUserData( void* pUserData ) { m_pUserData = pUserData; }
	virtual void Draw(LPDrawInfo pInfo, SIZE &posOffset );
};
