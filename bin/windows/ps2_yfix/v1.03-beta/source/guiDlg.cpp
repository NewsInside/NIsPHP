/*  ps2_pal2ntsc_yfix - PS2 PAL TO NTSC VIDEO MODE CHANGER WITH Y-FIX
 *  Copyright (C) 2003-2004  Jayteemaster <jayteemaster2003@yahoo.com.br>
 *  URL: www.geocities.com/jayteemaster2003
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// guiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gui.h"
#include "guiDlg.h"
// CD support
#include ".\cd\CDVDbin.h"
#include ".\cd\Misc.h"
#include ".\cd\CDVDisodrv.h"
#include ".\cd\CDVDedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiDlg dialog

CGuiDlg::CGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuiDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuiDlg)
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_EDIT2, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGuiDlg, CDialog)
	//{{AFX_MSG_MAP(CGuiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiDlg message handlers

BOOL CGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
	//(CGuiDlg::GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);
	CGuiDlg::getOutputControl();
	CGuiDlg::m_edit.FmtLines(FALSE);
	UDACCEL ac;
	CGuiDlg::m_spin.SetRange(0,64);
	CGuiDlg::m_spin.GetAccel(1,&ac);
	ac.nInc=1;
	CGuiDlg::m_spin.SetAccel(1,&ac);
	CGuiDlg::m_spin.SetPos(48);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

char lpstrFile[MAX_PATH]="";
char elfname[MAX_PATH]="";
int CDROM=0;

void CGuiDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	// Display the open dialog box to retrieve the user-selected movie file
	char szInitialDirectory[MAX_PATH]=".\\";
	char szFileTitle[MAX_PATH];
	//char lpstrFilter[MAX_PATH]="ELF files";
	char lpstrFilter[MAX_PATH]=
	"CD/DVD images (*.iso;*.bin)\0*.iso;*.bin\0"
	"ELF files (SLES;SCES;ELF)\0SLES_???.??;SCES_???.??;*.ELF\0";
	//"CD/DVD images (*.bin;*.iso;*.img;*.bwi)\0*.bin;*.iso;*.img;;*.bwi\0"
	//"RAW(2352) CD/DVD images (*.bin;*.img;*.bwi)\0*.bin;*.img;*.bwi\0"
	//"ISO(2048) CD/DVD images (*.iso)\0*.iso\0";


	OPENFILENAME ofn;
	BOOL bOpen;

	extern CGuiApp theApp;
	strcpy(szInitialDirectory, LPCTSTR(theApp.GetProfileString("", "LastDir", ".\\")));
	strcpy(lpstrFile, "");
	
	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = AfxGetMainWnd()->m_hWnd;
	ofn.hInstance         = 0;
	ofn.lpstrFilter       = lpstrFilter;

	ofn.lpstrCustomFilter = 0;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = lpstrFile;
	ofn.nMaxFile          = MAX_PATH;
	ofn.lpstrFileTitle    = szFileTitle;
	ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrInitialDir   = szInitialDirectory;
	ofn.lpstrTitle        = 0;
	ofn.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = 0;
    ofn.lCustData = 0;
    ofn.lpfnHook = 0;
    ofn.lpTemplateName = 0;

	bOpen = GetOpenFileName((LPOPENFILENAME)&ofn);

	CDROM=0;
	//(CGuiDlg::GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);
	if (bOpen) 
	{

		theApp.WriteProfileString("", "LastDir", lpstrFile);

		// Check that input elf is a valid MIPS elf
		unsigned char elf_ident[0x10] = { 0x7f, 0x45, 0x4c, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		unsigned char temp_buff[16];
		FILE *file;

		file = fopen(lpstrFile, "rb");
		if (!file)
		{
			return;
		}
		memset(temp_buff, 0, 16);
		fread(temp_buff, 1, 16, file);
		fclose(file);

		if (memcmp(temp_buff, elf_ident, 16)==0)
		{
			//
			extern int check_compressed(char *filename);
			if (check_compressed(lpstrFile)==1)
			{
				CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
				(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
				CGuiDlg::MessageBox("ELF FILE IS COMPRESSED", "PS2 YFIX", MB_OK|MB_ICONERROR);
				return;
			}
			//
			CGuiDlg::SetDlgItemText(IDC_EDIT1,lpstrFile);
			(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			CGuiDlg::m_edit.SetSel(0, -1, TRUE);
			CGuiDlg::m_edit.ReplaceSel("", FALSE);
		}
		else if (CDautodetect(lpstrFile)==1)
		{
			// Check CD/DVD image
			int ret;
			char fname[MAX_PATH];


			CDROM=1;
			memset(elfname, 0, MAX_PATH);

			ret=CDVDopen(lpstrFile);
			if (ret<0)
			{
				CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
				(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
				if (ret==-1)
					CGuiDlg::MessageBox("CD/DVD IMAGE IS READ ONLY or IS OPENED BY ANOTHER PROGRAM", "PS2 YFIX", MB_OK|MB_ICONERROR);
				else
					CGuiDlg::MessageBox("INVALID CD/DVD IMAGE", "PS2 YFIX", MB_OK|MB_ICONERROR);
				return;
			}

			ret=GetPS2ElfName(fname);
			if (ret==FALSE)
			{
				CDVDclose();
				CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
				(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
				CGuiDlg::MessageBox("NOT A CD/DVD PS2 IMAGE", "PS2 YFIX", MB_OK|MB_ICONERROR);
				return;
			}
			CGuiDlg::SetDlgItemText(IDC_EDIT1,fname);

			char *pos=strstr(fname,"cdrom0:\\");
			if (pos!=NULL)
			{
				pos+=strlen("cdrom0:\\");
				memcpy(elfname, pos, strlen(fname)-strlen("cdrom0:\\"));
			}
			else
			{
				pos=strstr(fname,"cdrom:\\");
				pos+=strlen("cdrom:\\");
				memcpy(elfname, pos, strlen(fname)-strlen("cdrom:\\"));
			}

			CDVDFS_init();
			int fd=CDVDFS_open(elfname, 1);
			if (fd<0)
			{
				CDVDclose();
				CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
				(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
				CGuiDlg::MessageBox("INVALID CD/DVD PS2 IMAGE", "PS2 YFIX", MB_OK|MB_ICONERROR);
				return;
			}
			CDVDFS_close(fd);

			CDVDclose();
			//CGuiDlg::SetDlgItemText(IDC_EDIT1, fname);
			(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			//(CGuiDlg::GetDlgItem(IDC_BUTTON3))->EnableWindow(TRUE);
			CGuiDlg::m_edit.SetSel(0, -1, TRUE);
			CGuiDlg::m_edit.ReplaceSel("", FALSE);
		}
		else
		{
			CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
			(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
			CGuiDlg::MessageBox("ILLEGAL FILE TYPE", "PS2 YFIX", MB_OK|MB_ICONERROR);
			return;
		}

	}

}

int pn_selector;
extern int make_pn_selector1(char *filename);
int yfix_offset=32;

void CGuiDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	char *argv[2];
	char tempname[MAX_PATH];
	extern void main_(int argc, char *argv[]);
	extern int please_inform;
	extern int wasmodified;
	extern char Editmsg[1024];
	extern BOOL show_Editmsg;
	int ret_pn=1;
	
	yfix_offset=CGuiDlg::m_spin.GetPos();
	(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
	pn_selector=0;
	{
		pn_selector=0;
	}
	//
	if (CDROM)
	{
		extract(lpstrFile, elfname, tempname);
		//
		// Check that inside elf is a valid MIPS elf
		unsigned char elf_ident[0x10] = { 0x7f, 0x45, 0x4c, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		unsigned char temp_buff[16];
		FILE *file;

		file = fopen(tempname, "rb");
		if (!file)
		{
			return;
		}
		memset(temp_buff, 0, 16);
		fread(temp_buff, 1, 16, file);
		fclose(file);
		if (memcmp(temp_buff, elf_ident, 16)!=0)
		{
			CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
			//(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
			CGuiDlg::MessageBox("CD/DVD IMAGE ELF FILE IS INVALID", "PS2 YFIX", MB_OK|MB_ICONERROR);
			return;
		}
		//
		//
		extern int check_compressed(char *filename);
		if (check_compressed(tempname)==1)
		{
			CGuiDlg::SetDlgItemText(IDC_EDIT1,"");
			//(CGuiDlg::GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
			CGuiDlg::MessageBox("CD/DVD IMAGE ELF FILE IS COMPRESSED", "PS2 YFIX", MB_OK|MB_ICONERROR);
			return;
		}
		//
		if (show_Editmsg)
			CGuiDlg::MessageBox(Editmsg, "PS2 YFIX", MB_OK|MB_ICONINFORMATION);
		argv[1]=tempname;
	}
	else
		argv[1]=lpstrFile;
	//
#if 1
	main_(2, argv);
#endif
	if (pn_selector)
	{
		ret_pn=make_pn_selector1(argv[1]);
	}
	//
	if (CDROM)
	{
		if (pn_selector)
		{
			if (ret_pn==0)
				insert(lpstrFile, elfname, tempname);
		}
		else
		{
			if (wasmodified)
				insert(lpstrFile, elfname, tempname);
		}
	}
	if ((please_inform)&&(!CDROM)&&(!pn_selector))
		CGuiDlg::MessageBox("THE SIZE OF THE ELF FILE WAS CHANGED!\nIf you are building a new PS2 CD/DVD image you must update the *.iml, *.ims files (or whatever) to reflect the new elf size.\nIf the patched elf is to be inserted into an already built *.BIN PS2 image please do not forget to regenerate the corrupted sectors after inserting the elf.", "PS2 YFIX", MB_OK|MB_ICONINFORMATION);
	please_inform = 0;
	/*
	if ((wasmodified)||(ret_pn==0))
		CGuiDlg::MessageBox("AFTER BURN PLEASE REPORT THE RESULT TO KTD WEBSITE:\n                       http://www.nofuzz.com/ktd\n\nThis will help others and also to improve this program. Thank you.", "PS2 PAL 2 NTSC W/ YFIX", MB_OK|MB_ICONINFORMATION);
	*/
	wasmodified=0;
}

CEdit *p_m_edit;

void CGuiDlg::getOutputControl()
{
	p_m_edit = &(CGuiDlg::m_edit);
}

void CGuiDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg Dlg;

	Dlg.DoModal();

}
