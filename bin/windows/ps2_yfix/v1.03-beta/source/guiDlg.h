// guiDlg.h : header file
//

#if !defined(AFX_GUIDLG_H__3035C123_A2D7_4E2D_AE78_205B7068639B__INCLUDED_)
#define AFX_GUIDLG_H__3035C123_A2D7_4E2D_AE78_205B7068639B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiDlg dialog

class CGuiDlg : public CDialog
{
// Construction
public:
	CGuiDlg(CWnd* pParent = NULL);	// standard constructor
	void getOutputControl();

// Dialog Data
	//{{AFX_DATA(CGuiDlg)
	enum { IDD = IDD_GUI_DIALOG };
	CSpinButtonCtrl	m_spin;
	CButton	m_pn_selector;
	CEdit	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDLG_H__3035C123_A2D7_4E2D_AE78_205B7068639B__INCLUDED_)
