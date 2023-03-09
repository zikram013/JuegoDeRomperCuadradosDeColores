#pragma once
#include "afxdialogex.h"


// COptionsDialog dialog

class COptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(bool bRowColumn,CWnd* pParent = nullptr);   // standard constructor
	virtual ~COptionsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStaticText1;
	int m_nValue1;
	CStatic m_ctrlStaticText2;
	int m_nValue2;
	afx_msg void OnBnClickedButtonDefaults();
	virtual BOOL OnInitDialog();
	bool m_bRowColumn;
};
