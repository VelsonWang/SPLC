
// LADDoc.cpp : CLADDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PlcEditor.h"
#endif
#include "PlcEditor.h"
#include "LADDoc.h"
#include "mainfrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLADDoc

IMPLEMENT_DYNCREATE(CLADDoc, CDocument)

BEGIN_MESSAGE_MAP(CLADDoc, CDocument)
END_MESSAGE_MAP()


// CLADDoc ����/����

CLADDoc::CLADDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CLADDoc::~CLADDoc()
{
}

BOOL CLADDoc::OnNewDocument()
{
	theApp.OnFileNew();
	return FALSE;
}




// CLADDoc ���л�

void CLADDoc::Serialize(CArchive& ar)
{
	char* strAnsi;
	CFile* file = ar.GetFile();
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		CStdString str;
		if( !m_schematic.ToIns( str ) )
		{
			libSch::CoilPos pos = m_schematic.GetErrorPos();
		}
		strAnsi = (char*)str.ToAnsi();
		//Ŀǰֻ����ansi
		file->Write( strAnsi, strlen(strAnsi) );
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		char* buf;
		buf = new char[ file->GetLength() + 1 ];
		file->Read( buf,file->GetLength() );
		buf[ file->GetLength() ] = 0;
		m_schematic.FromInsBuff( buf, file->GetLength() );
		delete[] buf;
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CLADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CLADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CLADDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLADDoc ���

#ifdef _DEBUG
void CLADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLADDoc ����

BOOL CLADDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	CString strFilter = lpszPathName;
	int nPos = strFilter.ReverseFind(_T('.'));
	if( nPos == -1 )
		return FALSE;
	strFilter = strFilter.Right( strFilter.GetLength() - nPos );
	if( strFilter == _T(".pproj") )
	{
		if( theApp.GetProject().IsOpen() )
		{
			if( MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),_T("�����Ѿ����ģ��Ƿ񱣴棿"),_T("��ʾ"),MB_OKCANCEL ) == IDOK )
			{
				theApp.GetProject().Close();
				( (CMainFrame*)AfxGetMainWnd() )->m_wndFileView.CloseProject();
			}else
			{
				theApp.AddToRecentFileList( lpszPathName );
				return FALSE;
			}
		}
		if( theApp.GetProject().Load( CString(lpszPathName) ) )
		{
			( (CMainFrame*)AfxGetMainWnd() )->m_wndFileView.LoadProject();
			theApp.AddToRecentFileList( lpszPathName );
		}
	}else if( strFilter == _T(".lad") )
	{
		libSch::BlockSize szBlock;
		szBlock.nLn = theApp.GetProject().m_nMaxLn;
		szBlock.nCol = theApp.GetProject().m_nMaxCol + 1;
		m_schematic.SetBlockSize( &szBlock );
		if( !theApp.GetProject().IsOpen() || !CDocument::OnOpenDocument(lpszPathName) )
			return FALSE;
		return TRUE;
		//SetModifiedFlag();
	}
	return FALSE;
}
