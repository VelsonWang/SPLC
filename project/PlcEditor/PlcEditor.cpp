
// PlcEditor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PlcEditor.h"
#include "MainFrm.h"
#include "DlgNewFile.h"

#include "ChildFrm.h"
#include "LADDoc.h"
#include "LADView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlcEditorApp

BEGIN_MESSAGE_MAP(CPlcEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPlcEditorApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CPlcEditorApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CPlcEditorApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CPlcEditorApp ����

CPlcEditorApp::CPlcEditorApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PlcEditor.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CPlcEditorApp ����

CPlcEditorApp theApp;


// CPlcEditorApp ��ʼ��

BOOL CPlcEditorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	m_pDocTemplate = new CMultiDocTemplate(IDR_PlcEditorTYPE,
		RUNTIME_CLASS(CLADDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CLADView));
	if (!m_pDocTemplate)
		return FALSE;
	AddDocTemplate(m_pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	//��ʼ��ins�б�
	initInsHash();
	return TRUE;
}

int CPlcEditorApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CPlcEditorApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CPlcEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPlcEditorApp �Զ������/���淽��

void CPlcEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CPlcEditorApp::LoadCustomState()
{
}

void CPlcEditorApp::SaveCustomState()
{
}

// CPlcEditorApp ��Ϣ�������
void CPlcEditorApp::OnFileOpen()
{
	// TODO: Add your command handler code here
#ifdef _DEBUG
	const BOOL VistaStyle = FALSE;
#else
	const BOOL VistaStyle = TRUE;
#endif
	if( m_project.IsOpen() )
	{
		if( MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),_T("�����Ѿ����ģ��Ƿ񱣴棿"),_T("��ʾ"),MB_OKCANCEL ) == IDOK )
		{
			m_project.Save();
			//( (CMainFrame*)AfxGetMainWnd() )->m_wndFileView.CloseProject();
		}
		m_project.Close();
	}
	CFileDialog dlg(TRUE, _T("*.pproj"), _T("*.pproj"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, _T("Project File(*.pproj)|*.pproj|All Files(*.*)|*.*||"),NULL,0,VistaStyle);
	dlg.m_ofn.lpstrTitle=_T("Open Project File");
	if(dlg.DoModal() == IDOK)
	{
		m_pDocTemplate->OpenDocumentFile( dlg.GetPathName() );
	}
}
void CPlcEditorApp::OnFileNew()
{
	// TODO: Add your command handler code here
	ASSERT(m_pDocTemplate);
	CDlgNewFile Dlg;
	if( m_project.IsOpen() )
	{
		
	}
	if( Dlg.DoModal() == IDOK )
	{
		Dlg.m_strProjectPath += _T("\\") + Dlg.m_strProjectName;
		if( Dlg.m_bMKDir )
		{
			if( !CreateDirectory(Dlg.m_strProjectPath, NULL ) && GetLastError() != ERROR_ALREADY_EXISTS )
			{
				MessageBox(NULL,_T("�����ļ���ʧ�ܣ�"),_T("����"),MB_OK );
				return;
			}
			Dlg.m_strProjectPath += _T("\\") + Dlg.m_strProjectName;
		}
		Dlg.m_strProjectPath += _T(".pproj");
		if( m_project.Create( Dlg.m_strProjectPath ) )
		{
			m_project.m_nMaxLn = Dlg.m_nStep;
			m_project.m_nMaxCol = Dlg.m_nCol;
			m_project.Save();
			AddToRecentFileList( Dlg.m_strProjectPath );
			m_pDocTemplate->OpenDocumentFile( Dlg.m_strProjectPath );
		}
	}
}
