
// PlcEditorView.h : CPlcEditorView ��Ľӿ�
//

#pragma once
#include "MemDc.h"
#include "PlcEditorDoc.h"
#include "Schematic.h"

class CPlcEditorView : public CView
{
protected: // �������л�����
	CPlcEditorView();
	DECLARE_DYNCREATE(CPlcEditorView)

// ����
public:
	CPlcEditorDoc* GetDocument() const;
// ����
public:
	void UpdataScroll();
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlcEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	TrackDc m_trackDc;
	CMemDc m_memDc;
	CSchematic m_schematic;
	RECT m_rcFocuse;
	int m_nFocuseRow,m_nFocuseCol;
	static void DrawFact( HDC hdc, RECT rt );
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // PlcEditorView.cpp �еĵ��԰汾
inline CPlcEditorDoc* CPlcEditorView::GetDocument() const
   { return reinterpret_cast<CPlcEditorDoc*>(m_pDocument); }
#endif

