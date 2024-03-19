#pragma once

class CViewMemDc
{
private:
	HDC m_hdc;
	HBITMAP m_membmp;
	SIZE m_szMax;
public:
	CViewMemDc(void);
	~CViewMemDc(void);
	HDC GetDC(){return m_hdc;}
	void SetSize( int nx, int ny );
	SIZE GetSize();
	BOOL BitBlt( HDC hdcDest, int x, int y, int cx, int cy, int x1, int y1, DWORD rop);
	BOOL StretchBlt( HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,int nXOriginSrc,int nYOriginSrc,int nWidthSrc,int nHeightSrc,DWORD dwRop);
};

class TrackDc{
public:
	typedef void(*PDrawFact)( HDC hdc, RECT rt );
protected:
	RECT m_rcOld;

	PDrawFact m_pDraw;
public:
	TrackDc();
	~TrackDc();
	PDrawFact SetDrawFact( PDrawFact pDrawFact );
	void Draw( HDC hdc );
	void TrackDraw( HDC hdc, RECT& rc );
	void Remove();
};