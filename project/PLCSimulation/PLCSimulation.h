
// PLCSimulation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPLCSimulationApp:
// �йش����ʵ�֣������ PLCSimulation.cpp
//

class CPLCSimulationApp : public CWinApp
{
public:
	CPLCSimulationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CPLCSimulationApp theApp;