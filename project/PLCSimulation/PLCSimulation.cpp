
// PLCSimulation.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PLCSimulation.h"
#include "PLCSimulationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLCSimulationApp

BEGIN_MESSAGE_MAP(CPLCSimulationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPLCSimulationApp ����

CPLCSimulationApp::CPLCSimulationApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPLCSimulationApp ����

CPLCSimulationApp theApp;

#ifdef _DEBUG
static BOOL bConsole;
#endif // _DEBUG
// CPLCSimulationApp ��ʼ��

BOOL CPLCSimulationApp::InitInstance()
{
#ifdef _DEBUG
	if( bConsole = AllocConsole() )
	{
		freopen("CONOUT$","w",stdout);
		freopen("CONIN$","r+t",stdin);
		TCHAR   szBuf[100]; 
		GetConsoleTitle(szBuf,   100); //�õ�����̨����
		HWND   hwnd   =   ::FindWindow(NULL,   szBuf); //���ҿ���̨ 
		HMENU   hmenu   =   ::GetSystemMenu(hwnd,   FALSE); //��ȡ�˵�
		::RemoveMenu(hmenu,   SC_CLOSE,MF_BYCOMMAND); //�Ƴ��ر�
	}
#endif // _DEBUG
	//������
	//LPTSTR strCmd = GetCommandLine();
	//lib_plccW( strCmd );
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CPLCSimulationDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CPLCSimulationApp::ExitInstance()
{
#ifdef _DEBUG
	if( bConsole )
	{
		fclose(stdout);
		fclose(stdin);
		FreeConsole();
	}
#endif // _DEBUG
	return CWinApp::ExitInstance();
}
