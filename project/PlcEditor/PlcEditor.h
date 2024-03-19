
// PlcEditor.h : PlcEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Project.h"

// CPlcEditorApp:
// �йش����ʵ�֣������ PlcEditor.cpp
//

class CPlcEditorApp : public CWinAppEx
{
public:
	CPlcEditorApp();


protected:
	CProject m_project;
	CMultiDocTemplate* m_pDocTemplate;

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnAppAbout();
	CProject& GetProject(){ return m_project; }
	DECLARE_MESSAGE_MAP()
	
};

extern CPlcEditorApp theApp;
