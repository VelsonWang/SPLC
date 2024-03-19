
// PLCSimulationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PLCSimulation.h"
#include "PLCSimulationDlg.h"
#include "afxdialogex.h"

#include "TickHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ProgramData CPLCSimulationDlg::m_prgData;
CDevUart CPLCSimulationDlg::m_uart;
CDevPip CPLCSimulationDlg::m_pip;
CDevSocket CPLCSimulationDlg::m_socket;
CCommunication CPLCSimulationDlg::m_communication;

void ScreenRectToClient( HWND hwnd, RECT* pRect )
{
	POINT *pt1=(POINT *)pRect;
	POINT *pt2=pt1+1;
	ScreenToClient(hwnd,pt1);
	ScreenToClient(hwnd,pt2);
}

void CALLBACK timeEvenCallback (UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	if( lib_API_ReadBit( api_coilM, 8000 ) )
		lib_API_TimerUp();
}


void PLCScanEnd()
{
	CPLCSimulationDlg* pDlg = static_cast<CPLCSimulationDlg*>( AfxGetApp()->GetMainWnd() );
	Sleep( CPLCSimulationDlg::GetPrgData().uScanInterval );//�����£���Ȼ����~~
	pDlg->PostMessage( UMSG_PLCSCANEND, 0, 0 );
}

void PLCSetOutPut( uint16 addr, mbyte b )
{
	CPLCSimulationDlg* pDlg = static_cast<CPLCSimulationDlg*>( AfxGetApp()->GetMainWnd() );
	Sleep(10);
	pDlg->PostMessage( UMSG_PLCSTOP, 0, 0 );
}

void PLCStop()
{
	CPLCSimulationDlg* pDlg = static_cast<CPLCSimulationDlg*>( AfxGetApp()->GetMainWnd() );
	Sleep(500);
	pDlg->PostMessage( UMSG_PLCSTOP, 0, 0 );
}


int MachineAction( int aix, int speed, int location, int bAbsolute )
{
	CPLCSimulationDlg* pDlg = static_cast<CPLCSimulationDlg*>( AfxGetApp()->GetMainWnd() );
	return pDlg->m_cMachine.Action( aix, speed, location, bAbsolute );
}

DWORD WINAPI PLCScanThread(LPVOID pParam)
{
	lib_API_PLCRun();
	printf("PLCScanThread return\n");
	return 0;
}

void RevCallBack( const unsigned char * buf, int sz, void* userData )
{
	if( lib_API_Protocol( DEV_FOR_GUI, (unsigned char*)buf,sz ) != RES_OK )
	{
		//protocolû�д���

	}
}

uint16 ComWrite( unsigned char* data, uint16 sz )
{
	if( CPLCSimulationDlg::m_communication.GetDev() )
	{
		CPLCSimulationDlg::m_communication.GetDev()->Send( data,sz );
	}
	return 0;
}

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


// CPLCSimulationDlg �Ի���

const static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_STATEPLCERR,
	IDS_STATELN,
	IDS_STATELN_NUM,
	IDS_STATECOL,
	IDS_STATECOL_NUM,
	IDS_STATESTEP,
	IDS_STATESTEP_NUM,
};

CPLCSimulationDlg::CPLCSimulationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPLCSimulationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_prgData.pFlash = ( unsigned char*)malloc( SZ_PROGRAM_MEM );
	m_prgData.szFlash = SZ_PROGRAM_MEM / 2;
	//m_prgData.pRam = ( unsigned char*)malloc( SZ_PROGRAM_MEM );
	m_prgData.szRam = SZ_PROGRAM_MEM;
}

void CPLCSimulationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPLCSimulationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNLOADPROGRAM, &CPLCSimulationDlg::OnBnClickedBtnloadprogram)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BTNRELOADPROGRAM, &CPLCSimulationDlg::OnBnClickedBtnreloadprogram)
	ON_MESSAGE(UMSG_PLCSTOP, &CPLCSimulationDlg::OnPlcStop)
	ON_MESSAGE(UMSG_PLCSCANEND, &CPLCSimulationDlg::OnPlcScanend)
	ON_BN_CLICKED(IDC_BTNSTEP, &CPLCSimulationDlg::OnBnClickedBtnstep)
	ON_BN_CLICKED(IDC_BTNRUN, &CPLCSimulationDlg::OnBnClickedBtnrun)
	ON_BN_CLICKED(IDC_BTNRESETPLC, &CPLCSimulationDlg::OnBnClickedBtnresetplc)
	ON_BN_CLICKED(IDC_BTNWATCH, &CPLCSimulationDlg::OnBnClickedBtnwatch)
	ON_BN_CLICKED(IDC_BTNLOADMEM, &CPLCSimulationDlg::OnBnClickedBtnloadmem)
	ON_BN_CLICKED(IDC_BTNSAVEMEM, &CPLCSimulationDlg::OnBnClickedBtnsavemem)
	ON_BN_CLICKED(IDC_BTNFIND, &CPLCSimulationDlg::OnBnClickedBtnfind)
	ON_BN_CLICKED(IDC_BTNDOWNLOAD, &CPLCSimulationDlg::OnBnClickedBtndownload)
	ON_BN_CLICKED(IDC_BTNFINDCLEAR, &CPLCSimulationDlg::OnBnClickedBtnfindclear)
	ON_BN_CLICKED(IDC_BTNOPENCOM, &CPLCSimulationDlg::OnBnClickedBtnopencom)
END_MESSAGE_MAP()


// CPLCSimulationDlg ��Ϣ�������

BOOL CPLCSimulationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	RECT rc;
	TCHAR strFileName[ MAX_PATH ];
	m_nLadViewTop = 110;
	m_nLadViewBottom = 30;
	m_dlgWatch.Create( IDD_WATCH, this );
	m_ladView.Create( IDD_LADVIEW, this );
	this->GetClientRect( &rc );
	rc.top = m_nLadViewTop;
	rc.bottom -= m_nLadViewBottom;
	m_ladView.MoveWindow(&rc); 
	m_ladView.ShowWindow( TRUE );
	m_ladView.ShowScrollBar( SB_VERT, FALSE );
	m_ladView.ShowWindow( FALSE );
	//color 
	::GetWindowRect( ::GetDlgItem( this->GetSafeHwnd(), IDC_COLORRUN ), &m_rcColorRun );
	ScreenRectToClient( this->GetSafeHwnd(), &m_rcColorRun );
	::GetWindowRect( ::GetDlgItem( this->GetSafeHwnd(), IDC_COLORERROR ), &m_rcColorErr );
	ScreenRectToClient( this->GetSafeHwnd(), &m_rcColorErr );

	if(!m_wndStatusBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM )|| !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))  
	{  
		AfxMessageBox(L"Can't create status bar/n");  
		return false;  
	}
	//m_wndStatusBar.MoveWindow(0,rect.bottom-20,rect.right,20,TRUE);// ����״̬����λ�úʹ�С  
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_wndStatusBar.SetPaneText(0,L"����");

	GetModuleFileName( NULL, strFileName, MAX_PATH );
	m_strWorkPath = strFileName;
	int nPos;
	if( ( nPos = m_strWorkPath.ReverseFind( _T('\\') ) ) != -1 
		||  ( nPos = m_strWorkPath.ReverseFind( _T('/') ) ) != -1   )
	{
		m_strWorkPath = m_strWorkPath.Left( nPos + 1 );
	}
	LPCTSTR p = m_strWorkPath.GetBuffer();

	static_cast<CEdit*>( GetDlgItem(IDC_EDIT_PORT))->SetLimitText(20);
	static_cast<CEdit*>( GetDlgItem(IDC_EDITFIND))->SetLimitText(10);
	static_cast<CEdit*>( GetDlgItem(IDC_EDIT_MEM))->SetLimitText(MAX_PATH);

#ifdef _DEBUG
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText( TEXT( "127.0.0.1" ) );
#endif
	//init plc core
	PLCSysInitInfo iniInfo;
	iniInfo.pSend[0] = ComWrite;
	iniInfo.pSend[1] = ComWrite;
	iniInfo.pScanEnd = PLCScanEnd;
	iniInfo.pSetOutPut = PLCSetOutPut;
	iniInfo.pPLCStop = PLCStop;
	iniInfo.pMachine = MachineAction;
	iniInfo.pFlash = m_prgData.pFlash;
	iniInfo.szFlash = m_prgData.szFlash;
	iniInfo.pRam = m_prgData.pRam;
	iniInfo.szRam = m_prgData.szRam;
	*( (unsigned short*)m_prgData.pFlash ) = dinsEND;
	m_prgData.uScanInterval = 100;
	//g_proData.strprgFile[0] = '\0';
	if( lib_API_InitSystem( &iniInfo ) == RES_ERR )
	{
		MessageBox( _T("��ʼ��PLCʧ��"),_T("����"),MB_OK );
		PostQuitMessage( -1 );
	}else
	{
		lib_API_SetWDG(0);
		lib_API_WriteBit( api_coilM, 8000, 0 );
		m_prgData.hThreadScan = ::CreateThread(NULL,0,&PLCScanThread,0,0,NULL);
		if( m_prgData.hThreadScan )
		{
			m_prgData.t=timeSetEvent(1,1,timeEvenCallback,0,TIME_PERIODIC);
		}
		UpdatePLCState( );
	}
	m_cMachine.SetSopCallBack( lib_API_StopMachine );
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPLCSimulationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPLCSimulationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		COLORREF color;
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		if( !lib_API_ReadBit( api_coilM, 8000 ) )
		{
			if( lib_API_ReadBit( api_coilM, 8035 ) )//����ģʽ
			{
				if( lib_API_ReadBit( api_coilM, 8036 ) )	//��������
				{
					color = COLOR_PLCSTEPRUN;
				}else
				{
					color = COLOR_PLCSTOP;
				}
			}else
				color = COLOR_PLCSTOP;
		}else
		{
			color = COLOR_PLCRUN;
		}
		dc.FillSolidRect( &m_rcColorRun, color );
		dc.FillSolidRect( &m_rcColorErr, lib_API_ReadBit( api_coilM, 8004 ) ? COLOR_PLCERR : COLOR_PLCNOERR );
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPLCSimulationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPLCSimulationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	RECT rc;
	this->GetClientRect( &rc );
	rc.top = m_nLadViewTop;
	rc.bottom -= m_nLadViewBottom;
	if( m_ladView.GetSafeHwnd() != NULL )
	{
		m_ladView.MoveWindow(&rc);
	}
	InvalidateRect( &rc,FALSE );
	// TODO: Add your message handler code here
}


void CPLCSimulationDlg::OnBnClickedBtnloadprogram()
{
	int nPos;
	CStdString str;
#ifdef _DEBUG
	const BOOL VistaStyle = FALSE;
#else
	const BOOL VistaStyle = TRUE;
#endif
	CFileDialog dlg(TRUE, _T("*.wpg"), _T("*.wpg"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, _T("����wpg �ļ�(*.wpg)|*.wpg|lad �ļ�(*.lad)|*.lad|�����ļ�(*.*)|*.*||"),NULL,0,VistaStyle);
	dlg.m_ofn.lpstrTitle=_T("Open Project File");
	if(dlg.DoModal() == IDOK)
	{
		m_prgData.bWPG = FALSE;
		m_prgData.strFile.Empty();
		m_ladView.ShowWindow( FALSE );
		str.Assign( dlg.GetPathName() );
		nPos = str.ReverseFind(L'.');
		if( nPos != -1 )
		{
			str = str.Right( str.GetLength() - nPos - 1 );
			str.MakeUpper();
			m_prgData.bWPG = ( str == _T("WPG") );
		}
		m_prgData.strFile.Assign( dlg.GetPathName() );
		if( LoadProgram() )
		{
			str.Format( _T("PLCSimulation [file: %s]"),m_prgData.strFile.GetBuffer() );
			SetWindowText( str.GetBuffer() );
		}
		UpdatePLCState( );
	}
}


BOOL CPLCSimulationDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	RECT rc;
	this->GetClientRect( &rc );
	if( m_ladView.IsWindowVisible() )
		rc.bottom = m_nLadViewTop;
	pDC->FillSolidRect( &rc, GetSysColor(COLOR_3DFACE) );
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CPLCSimulationDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	WPARAM wParam;
	LPARAM lParam;
	wParam = MAKELONG(nFlags,zDelta);
	lParam = MAKELONG(pt.x,pt.y);
	m_ladView.SendMessage( WM_MOUSEWHEEL, wParam,lParam );
	return TRUE;
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CPLCSimulationDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	lib_API_WriteBit( api_coilM, 8010, 0 );
	Sleep(10);
	lib_API_WriteBit( api_coilM, 8000, 0 );
	WaitForSingleObject(m_prgData.hThreadScan,INFINITE);
	timeKillEvent(m_prgData.t);
	lib_API_UninitSystem();
	if( m_prgData.pDev )
	{
		m_prgData.pDev->Close();
		m_prgData.pDev = NULL;
	}
	return CDialogEx::DestroyWindow();
}


void CPLCSimulationDlg::OnBnClickedBtnreloadprogram()
{
	LoadProgram();
	UpdatePLCState();
}


void CPLCSimulationDlg::OnOK()
{
	//���λس��رմ���
}

inline void CPLCSimulationDlg::SetStatusString( CString str )
{
	m_wndStatusBar.SetPaneText( CPLCSimulationDlg::STATUSE_SEPARATOR, str );
}

BOOL CPLCSimulationDlg::LoadProgram(void)
{
	CStdString strSource;
	CStdString str;
	CStdString strBin;
	char buff[512];
	DWORD bytesRead;
	BOOL bRes = FALSE;

	if( m_prgData.strFile.IsEmpty() )
		goto load_over;
	lib_API_SetWDG(0);
	m_ladView.ShowWindow( FALSE );
	strSource = m_strWorkPath + _T("plc.lad");
	strBin = m_strWorkPath + _T("plc.bin");
	//����
	if( !m_prgData.bWPG )
	{
		CopyFile( m_prgData.strFile, strSource,FALSE );
		str.Format( _T("plcc.exe -o \"%s\"  \"%s\""), 
			strBin.GetBuffer(), 
			m_prgData.strFile.GetBuffer() );
	}else
	{
		str.Format( _T("plcc.exe -o \"%s\" -t \"%s\" \"%s\" -p -e 0x44"), 
			strBin.GetBuffer(), 
			strSource.GetBuffer(), 
			m_prgData.strFile.GetBuffer() );
	}
	HANDLE hOutputRead = INVALID_HANDLE_VALUE;
	HANDLE hOutputWrite = INVALID_HANDLE_VALUE;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE; 
	if ( !CreatePipe(&hOutputRead,&hOutputWrite,&sa,0))
	{
		printf("Error On CreatePipe1");
		goto load_over;
	}

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	//GetStartupInfo(&si);
	si.hStdError = hOutputWrite;
	si.hStdOutput = hOutputWrite;
	//si.hStdInput = hOutputWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (
		!CreateProcessA( NULL,   // No module name (use command line)
		(LPSTR)str.ToAnsi(),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
		)
	{
		goto load_over;
	}
	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );
	
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	if( PeekNamedPipe( hOutputRead, buff, 512, &bytesRead,NULL,NULL ) )
	{
		if( bytesRead )
		{
			buff[ bytesRead ] = 0;
			str.Assign( buff,CP_ACP );
			MessageBox( str,_T("�������"),MB_OK );
			goto load_over;
		}
	}else{
		MessageBox( _T("�������"),_T("�������"),MB_OK );
		goto load_over;
	}

	if( m_ladView.LoadPLC( strSource.GetBuffer() ) )
	{
		//����PLC
		FILE* fp;
		size_t sz;
		fp = _wfopen( strBin.GetBuffer(),_T("rb") );
		if( fp == NULL )
			goto load_over;
		fseek( fp, 0, SEEK_END );
		sz = ftell( fp );
		if( sz % 2 || sz >= sizeof( m_prgData.pFlash ) )
		{
			goto load_over;
		}
		fseek( fp, 0, SEEK_SET );
		fread( m_prgData.pFlash, 1, sz, fp );
		fclose(fp);
		//����ͣPLC
		lib_API_WriteBit( api_coilM, 8000, 0 );
		::SetWindowText( ::GetDlgItem( this->GetSafeHwnd(),IDC_BTNRUN ),_T("����") );
		Sleep(1000);
		if( lib_API_LoadProgram() != RES_OK )
		{
			::MessageBox( this->GetSafeHwnd() ,_T("�������ʧ�ܣ�"),_T("����"), MB_OK );
			goto load_over;
		}
		lib_API_WriteBit( api_coilM, 8038, 1 );
		lib_API_WriteBit( api_coilM, 8000, 1 );
		lib_API_SetWDG(300);
		m_ladView.ShowWindow( TRUE );
		InvalidateRect( NULL,FALSE );
		bRes = TRUE;
	}else
	{
		str = _T("����ͼת��ʧ��,��������ͼ�߼���\n");
		m_ladView.GetErr( strBin );
		str.Append( strBin );
		MessageBox( str,_T("����"), MB_OK );
	}

load_over:
	CloseHandle(hOutputRead);
	CloseHandle(hOutputWrite);
	return bRes;
}

afx_msg LRESULT CPLCSimulationDlg::OnPlcStop(WPARAM wParam, LPARAM lParam)
{
	if( lib_API_ReadBit( api_coilM, 8035 ) )//�������
	{
		CStdString str;
		UINT32 step = 0;
		lib_API_ReadData( api_coilD, 8011,&step );
		str.Format(_T("%d"), step );
		m_wndStatusBar.SetPaneText( CPLCSimulationDlg::STATUSE_STEP_NUM, str );
	}
	m_ladView.OnPLCScanEnd();
	return 0;
}

//�����ö���
CStdString g_strStata[][2] = {
	{ TEXT("ͨ"),TEXT("��") },
	{ TEXT("��ʼ"),TEXT("����") },
};
typedef struct tagMAction{
	CString name;
	int action;
	int locate;
	int speed;
	int delay;
	int bLast;
}MAction,*LPMAction;

typedef struct tagTAction{
	CString name;
	unsigned char coil;
	int addr;
	int statestr;
	int bLast;
}TAction,*LPTAction;

MAction g_maction[] = {
	{ TEXT("MY�ᶯ��"),1500,1000,1002,1004 },
	{ TEXT("MZ�ᶯ��"),1501,1030,1032,1034 },
	{ TEXT("X�ᶯ��"),1502,1060,1062,1064 },
	{ TEXT("SY�ᶯ��"),1503,1090,1092,1094 },
	{ TEXT("SZ�ᶯ��"),1504,1120,1122,1124 },
	{ TEXT("C�ᶯ��"),1505,1150,1151,1051 },
};
TAction g_taction[]={
	{ TEXT("�о�1"),api_coilY,13,0 },
	{ TEXT("�о�2"),api_coilY,14,0 },
	{ TEXT("�о�3"),api_coilY,29,0 },
	{ TEXT("�о�4"),api_coilY,19,0 },
	{ TEXT("��1"),api_coilY,15,0 },
	{ TEXT("��1"),api_coilY,16,0 },

	{ TEXT("����"),api_coilY,24,0 },
	{ TEXT("���ʹ�"),api_coilY,31,0 },

	{ TEXT("��1���"),api_coilM,122,1 },
	{ TEXT("��2���"),api_coilM,123,1 },
	{ TEXT("��3���"),api_coilM,124,1 },
	{ TEXT("��4���"),api_coilM,125,1 },
	{ TEXT("��1���"),api_coilM,126,1 },
	{ TEXT("��2���"),api_coilM,127,1 },

	{ TEXT("��Ʒ����"),api_coilM,1331,-1 },
	{ TEXT("�ѵ�����"),api_coilM,1522,-1 },

	{ TEXT("��ģ����"),api_coilY,10,0 },
	{ TEXT("��������"),api_coilY,7,0 },
	{ TEXT("��о1����"),api_coilY,3,0 },
	{ TEXT("��о2����"),api_coilY,4,0 },

	{ TEXT("�ȴ���ģ��"),api_coilM,1450,-1 },
	{ TEXT("�ȴ���ȫ�Ź�"),api_coilM,1451,-1 },
	{ TEXT("�ȴ���о��λ"),api_coilM,1455,-1 },
	{ TEXT("�ȴ��������λ"),api_coilM,1456,-1 },
	{ TEXT("�ȴ���о��λ"),api_coilM,1457,-1 },
	{ TEXT("�ȴ���1ȷ��"),api_coilM,1458,-1 },
	{ TEXT("�ȴ���2ȷ��"),api_coilM,1459,-1 },
	{ TEXT("�ȴ���3ȷ��"),api_coilM,1460,-1 },
	{ TEXT("�ȴ���4ȷ��"),api_coilM,1461,-1 },
	{ TEXT("����1ȷ��"),api_coilM,1462,-1 },
	{ TEXT("����2ȷ��"),api_coilM,1463,-1 },
	{ TEXT("�ȴ������˵�λ"),api_coilM,1464,-1 },
};


afx_msg LRESULT CPLCSimulationDlg::OnPlcScanend(WPARAM wParam, LPARAM lParam)
{
	USES_CONVERSION;
	int i;
	UINT32 uLocate = 0;
	UINT32 uSpeed = 0;
	UINT32 uDelay = 0;

	char bStata;
	char bNow;
	if( m_ladView.IsWindowVisible() )
		m_ladView.OnPLCScanEnd();
	if( m_dlgWatch.IsWindowVisible() )
		m_dlgWatch.OnPLCScanEnd();
	return 0;
	for ( i = 0; i < sizeof( g_maction ) / sizeof(MAction); ++i )
	{
		uLocate = 0;
		uSpeed = 0;
		uDelay = 0;
		bNow = lib_API_ReadBit( api_coilM, g_maction[i].action );
		if( bNow && !g_maction[i].bLast )
		{
			
			if( lib_API_ReadData( api_coilDD, g_maction[i].locate,&uLocate ) 
				&& lib_API_ReadData( api_coilDD, g_maction[i].speed,&uSpeed ) 
				&& lib_API_ReadData( api_coilD, g_maction[i].delay,&uDelay ) )
			{
				if( i == sizeof( g_maction ) / sizeof(MAction) - 1 )
				{
					if( lib_API_ReadData( api_coilD, g_maction[i].locate,&uLocate ) 
						&& lib_API_ReadData( api_coilD, g_maction[i].speed,&uSpeed )  )
					{
						printf( "%s:���ƣ�%d����ʱ��%d\n",T2A( g_maction[i].name ),uLocate,uSpeed );
					}
				}else{
					printf( "%s:λ�ã�%d�����ȣ�%d,��ʱ��%d\n",T2A( g_maction[i].name ),uLocate,uSpeed,uDelay );
				}
				
			}
		}
		g_maction[i].bLast = bNow;
	}
	for ( i = 0; i < sizeof( g_taction ) / sizeof(TAction); ++i )
	{
		bNow = lib_API_ReadBit( g_taction[i].coil, g_taction[i].addr );
		if( g_taction[i].statestr == -1 )
		{
			if( bNow && !g_taction[i].bLast ){
				printf( "%s\n", T2A( g_taction[i].name ) );
			}
		}else{
			if( bNow && !g_taction[i].bLast ){
				printf( "%s:%s\n",T2A( g_taction[i].name ),T2A( g_strStata[g_taction[i].statestr][0] ) );
			}else if( !bNow && g_taction[i].bLast )
			{
				printf("%s:%s\n",T2A( g_taction[i].name ),T2A( g_strStata[g_taction[i].statestr][1] ) );
			}
		}
		g_taction[i].bLast = bNow;
	}
	return 0;
}


void CPLCSimulationDlg::OnBnClickedBtnstep()
{
	//����ͣPLC
	lib_API_WriteBit( api_coilM, 8000, 0 );
	lib_API_WriteBit( api_coilM, 8035, 1 );//�������
	lib_API_WriteBit( api_coilM, 8036, 1 );
	lib_API_WriteBit( api_coilM, 8037, 1 );
}


void CPLCSimulationDlg::OnBnClickedBtnrun()
{
	// TODO: Add your control notification handler code here
	lib_API_WriteBit( api_coilM, 8035, 0 );//�������
	lib_API_WriteBit( api_coilM, 8036, 0 );
	lib_API_WriteBit( api_coilM, 8037, 0 );
	lib_API_WriteBit( api_coilM, 8000, !lib_API_ReadBit( api_coilM, 8000 ) );
	UpdatePLCState();
}

void CPLCSimulationDlg::OnBnClickedBtnresetplc()
{
	if( lib_API_ReadBit( api_coilM, 8000 ) )
		SetStatusString( _T("��λPLC������ֹͣ����") );
	else
		lib_API_ResetPLC();
}


void CPLCSimulationDlg::UpdatePLCState(void)
{
	if( m_ladView.IsWindowVisible() )
	{
		GetDlgItem( IDC_BTNRUN )->EnableWindow(TRUE);
		if( lib_API_ReadBit( api_coilM, 8000 ) )
		{
			lib_API_SetWDG(300);
			GetDlgItem( IDC_BTNRUN )->SetWindowText(_T("ֹͣ"));
			GetDlgItem( IDC_BTNSTEP )->EnableWindow(FALSE);
		}else
		{
			lib_API_SetWDG(0);
			GetDlgItem( IDC_BTNRUN )->SetWindowText(_T("����"));
			GetDlgItem( IDC_BTNSTEP )->EnableWindow(TRUE);
		}
	}else
	{
		GetDlgItem( IDC_BTNRUN )->EnableWindow(FALSE);
		GetDlgItem( IDC_BTNSTEP )->EnableWindow(FALSE);
	}
	InvalidateRect( NULL,FALSE );
}


void CPLCSimulationDlg::OnBnClickedBtnwatch()
{
	if( m_dlgWatch.IsWindowVisible() )
		m_dlgWatch.ShowWindow( FALSE );
	else
		m_dlgWatch.ShowWindow( TRUE );
}


void CPLCSimulationDlg::OnBnClickedBtnloadmem()
{
	FILE *fp;
	if( OpenMemFile( &fp, TRUE ) )
	{
		lib_API_LoadMem( fp, DUMP_MEM_M | DUMP_MEM_D );
		fclose( fp );
	}
}


void CPLCSimulationDlg::OnBnClickedBtnsavemem()
{
	FILE *fp;
	if( OpenMemFile( &fp,FALSE ) )
	{
		lib_API_DumpMem( fp, DUMP_MEM_M | DUMP_MEM_D );
		fclose( fp );
	}
}


void CPLCSimulationDlg::OnBnClickedBtnfind()
{
	CString strFind;
	GetDlgItem( IDC_EDITFIND )->GetWindowText( strFind );
	m_ladView.FindCoil( strFind );
	InvalidateRect(NULL,FALSE);
}


void CPLCSimulationDlg::OnBnClickedBtnfindclear()
{
	m_ladView.m_strFind.Empty();
}

void CPLCSimulationDlg::OnBnClickedBtndownload()
{
	//���أ��Ȳ�֧��

}

void CPLCSimulationDlg::OnBnClickedBtnopencom()
{
	// TODO: Add your control notification handler code here
	CBaseDev *pDev = NULL;
	CString str;
	GetDlgItem( IDC_EDIT_PORT )->GetWindowText( str );
	str.MakeUpper();
	pDev = m_communication.GetDev();
	if( pDev == NULL )
	{
		if( str.Find(_T("COM")) != -1 )
		{
			COMCONFIG conf;
			memset( &conf, 0, sizeof( conf ) );
			_tcscpy_s( conf.comName, str.GetBuffer() );
			conf.dwBaudRate = 19200;
			conf.bitByteSize = 8;
			conf.bitParity = NOPARITY;
			conf.bitStopBits = ONESTOPBIT;
			conf.szBuff = 512;
			m_uart.Config( &conf );
			if( m_uart.Open() )
			{
				m_communication.SetRevCallBack( RevCallBack );
				m_communication.SetSelDev( &m_uart );
				if( pDev ) pDev->Close();
			}else
				MessageBox(_T("���豸ʧ�ܣ�"),_T("��ʾ"));
		}else if( str.Find(_T("PIP")) != -1 ){
			m_pip.Config(str.GetBuffer(),1024);
			if( m_pip.Open() )
			{
				m_communication.SetRevCallBack( RevCallBack );
				m_communication.SetSelDev( &m_pip );
				if( pDev ) pDev->Close();
			}else
				MessageBox(_T("���豸ʧ�ܣ�"),_T("��ʾ"));
		}else if( str == _T("127.0.0.1") )
		{
			m_socket.Config( str.GetBuffer(), 1024,TRUE );
			if( m_socket.Open() )
			{
				m_communication.SetRevCallBack( RevCallBack );
				m_communication.SetSelDev( &m_socket );
				if( pDev ) pDev->Close();
			}else
				MessageBox(_T("���豸ʧ�ܣ�"),_T("��ʾ"));
		}else
			MessageBox(_T("δ֪�豸���߲�֧�ֵ��豸��"),_T("��ʾ"));
	}else
	{
		m_communication.SetSelDev( NULL );
		pDev->Close();
	}
	CPLCSimulationDlg::GetPrgData().pDev = pDev;
	GetDlgItem(IDC_BTNOPENCOM)->SetWindowText( m_communication.GetDev() ? _T("�ر�ͨ��") : _T("��ͨ��") );
}

BOOL CPLCSimulationDlg::OpenMemFile( FILE** fp, BOOL bOpen )
{
	CString str;
	GetDlgItem(IDC_EDIT_MEM)->GetWindowText( str );
	if( !PathFileExists( str ) )
	{
#ifdef _DEBUG
		const BOOL VistaStyle = FALSE;
#else
		const BOOL VistaStyle = TRUE;
#endif
		CFileDialog dlg( bOpen, _T("*.bin"), _T("*.bin"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			, _T("bin �ļ�(*.bin)|*.bin|�����ļ�(*.*)|*.*||"),NULL,0,VistaStyle);
		dlg.m_ofn.lpstrTitle=_T("Open mem File");
		if(dlg.DoModal() == IDOK)
			str = dlg.GetPathName();
		else
			return FALSE;
	}
	if( _wfopen_s( fp, str, bOpen ? _T("rb") : _T("wb") ) == 0 )
	{
		GetDlgItem(IDC_EDIT_MEM)->SetWindowText( str );
		return TRUE;
	}else
		return FALSE;
}

