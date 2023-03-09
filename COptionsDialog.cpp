// COptionsDialog.cpp : implementation file
//

#include "pch.h"
#include "Game1.h"
#include "afxdialogex.h"
#include "COptionsDialog.h"


// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)

COptionsDialog::COptionsDialog(bool bRowColumn,CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumn(bRowColumn)
{

}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT1, m_ctrlStaticText1);
	DDX_Text(pDX, IDC_EDIT_VALUE1, m_nValue1);
	DDX_Control(pDX, IDC_STATIC_TEXT2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT_VALUE2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionsDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()


// COptionsDialog message handlers


void COptionsDialog::OnBnClickedButtonDefaults()
{
	// TODO: Add your control notification handler code here
	//Se deben realizar cosas diferentes por los diferentes lenguajes
	if (m_bRowColumn) {
		m_nValue1 = m_nValue2 = 15; //Tablero de 15 * 15
	}
	else {
		m_nValue1 =
	}

}
