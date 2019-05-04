// gui.h : main header file for the GUI application
//

#if !defined(AFX_GUI_H__A1E18F6D_BA35_4855_B1B5_48DEF0E1D30A__INCLUDED_)
#define AFX_GUI_H__A1E18F6D_BA35_4855_B1B5_48DEF0E1D30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGuiApp:
// See gui.cpp for the implementation of this class
//

class CGuiApp : public CWinApp
{
public:
	CGuiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGuiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_H__A1E18F6D_BA35_4855_B1B5_48DEF0E1D30A__INCLUDED_)
