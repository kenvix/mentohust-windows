// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MentoHUST.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_TAB, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTabPages();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::InitTabPages()
{
	m_TabCtrl.InsertItem(0, LoadString(IDS_CFG_ACCOUNT));
	m_TabCtrl.InsertItem(1, LoadString(IDS_CFG_PARAMETER));
	CRect rect;
	m_TabCtrl.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top += 20;
	rect.left += 1;
	rect.right -= 1;
	rect.bottom -= 1;
	AccountPage.Create(IDD_CFG_ACCOUNT, this);
	ParameterPage.Create(IDD_CFG_PARAMETER, this);
	AccountPage.MoveWindow(&rect);
	ParameterPage.MoveWindow(&rect);
	ShowPage(1);
}

void CConfigDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ShowPage(m_TabCtrl.GetCurSel());
	*pResult = 0;
}

void CConfigDlg::ShowPage(UINT nIndex)
{
	switch (nIndex)
	{
	case 0:
		AccountPage.ShowWindow(TRUE);
		ParameterPage.ShowWindow(FALSE);
		AccountPage.SetFocus();
		break;
	case 1:
		AccountPage.ShowWindow(FALSE);
		ParameterPage.ShowWindow(TRUE);
		ParameterPage.SetFocus();
		break;
	default:
		break;
	}
	m_TabCtrl.SetCurSel(nIndex);
}

void CConfigDlg::OnOK() 
{
	if (!AccountPage.WriteConfig())
		ShowPage(0);
	else if (!ParameterPage.WriteConfig())
		ShowPage(1);
	else
	{
		MessageBox(LoadString(IDS_SAVE_SUCCESS), LoadString(IDS_MSG_CAPTION), MB_OK|MB_ICONWARNING);
		CDialog::OnOK();
	}
}

void CConfigDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	AccountPage.DestroyWindow();
	ParameterPage.DestroyWindow();
}
