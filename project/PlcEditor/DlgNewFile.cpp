// DlgNewFile.cpp : implementation file
//

#include "stdafx.h"
#include "plcEditor.h"
#include "DlgNewFile.h"
#include "afxdialogex.h"


// CDlgNewFile dialog

IMPLEMENT_DYNAMIC(CDlgNewFile, CDialog)

	CDlgNewFile::CDlgNewFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewFile::IDD, pParent)
	, m_strProjectName(_T(""))
	, m_strProjectPath(_T(""))
	, m_nStep(0)
	, m_nCol(0)
{

}

CDlgNewFile::~CDlgNewFile()
{
}

void CDlgNewFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROJECTNAME, m_strProjectName);
	DDX_Text(pDX, IDC_PROJECTPATH, m_strProjectPath);
	DDX_Text(pDX, IDC_MAX_STEP, m_nStep);
	DDV_MinMaxInt(pDX, m_nStep, 0, 30000);
	DDX_Text(pDX, IDC_MAX_COL, m_nCol);
	DDV_MinMaxInt(pDX, m_nCol, 0, 100);
}


BEGIN_MESSAGE_MAP(CDlgNewFile, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgNewFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_VIEWPATH, &CDlgNewFile::OnBnClickedViewpath)
END_MESSAGE_MAP()


// CDlgNewFile message handlers


BOOL CDlgNewFile::OnInitDialog()
{
	CString wndID;
	CDialog::OnInitDialog();

	( (CButton*)GetDlgItem(IDC_MKDIR) )->SetCheck( TRUE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgNewFile::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if( m_strProjectName.IsEmpty() || m_strProjectPath.IsEmpty() )
	{
		MessageBox( _T("��������ȷ�Ĳ�����"),_T("����"),MB_OK );
		return;
	}
	m_bMKDir = ( (CButton*)GetDlgItem(IDC_MKDIR) )->GetCheck();
	CDialog::OnOK();
}


void CDlgNewFile::OnBnClickedViewpath()
{
	BROWSEINFO bi;
	TCHAR Buffer[MAX_PATH];
	bi.hwndOwner = this->GetSafeHwnd();
	bi.pidlRoot =NULL;//��ʼ���ƶ���rootĿ¼�ܲ����ף�
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = _T("ѡ�񹤳�Ŀ¼");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�

	bi.lpfn = NULL;
	//bi.iImage=IDR_MAINFRAME;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		m_strProjectPath = Buffer;
		UpdateData(FALSE);
	}
}
