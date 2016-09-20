
// MHCDGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MHCDGUI.h"
#include "MHCDGUIDlg.h"
#include "afxdialogex.h"
#include <Winbase.h>
#include <TLHELP32.H>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMHCDGUIDlg dialog



CMHCDGUIDlg::CMHCDGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MHCDGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMHCDGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, CListMsg);
}
#define MYWM_NOTIFYICON WM_USER+100
#define   WM_MYMESSAGE   WM_USER+101 
BEGIN_MESSAGE_MAP(CMHCDGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMHCDGUIDlg::OnBnClickedStart)
	ON_MESSAGE(MYWM_NOTIFYICON, &CMHCDGUIDlg::OnMyIconNotify)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(ID_HELP, &CMHCDGUIDlg::OnBnClickedHelp)
END_MESSAGE_MAP()


// CMHCDGUIDlg message handlers


BOOL CMHCDGUIDlg::MyTaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip)
{
	BOOL res;
	NOTIFYICONDATA tnid;
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hwnd;
	tnid.uID = uID;
	tnid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	tnid.uCallbackMessage = MYWM_NOTIFYICON;
	tnid.hIcon = hicon;
	if (lpszTip)
		lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip));
	else
		tnid.szTip[0] = '\0';
	res = Shell_NotifyIcon(NIM_ADD, &tnid);
	if (hicon)
		DestroyIcon(hicon);
	return res;
}

BOOL CMHCDGUIDlg::MyTaskBarDeleteIcon(HWND hwnd, UINT uID)
{
	BOOL res;
	NOTIFYICONDATA tnid;
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hwnd;
	tnid.uID = uID;
	res = Shell_NotifyIcon(NIM_DELETE, &tnid);
	return res;
}

afx_msg LRESULT CMHCDGUIDlg::OnMyIconNotify(WPARAM wParam, LPARAM lParam)
{
	UINT nID;
	UINT uMouseMsg;
	nID = (UINT)wParam;
	uMouseMsg = (UINT)lParam;
	if (uMouseMsg == WM_LBUTTONDOWN)
	{
		ShowWindow(SW_SHOWNORMAL);
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	return 0;
}

BOOL CMHCDGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CreateMutex(NULL, false, "MHCD by suwuhao");
	EnableDebugPriv(SE_DEBUG_NAME);
	MyTaskBarAddIcon(this->GetSafeHwnd(), IDR_MAINFRAME, m_hIcon, "MapHackClickDetector by suwuhao");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMHCDGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMHCDGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMHCDGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMHCDGUIDlg::EnableDebugPriv(const char * name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken))
	{
		MessageBox((LPCSTR)"OpenProcessToken Error!", (LPCSTR)"Error!", MB_OK);
		return 1;
	}

	if (!LookupPrivilegeValue(NULL, name, &luid))
	{
		MessageBox((LPCSTR)"LookupPrivivlegeValue Error!", (LPCSTR)"Error", MB_OK);
	}
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;

	if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		MessageBox((LPCSTR)"AdjustTokenPrivileges Error!", (LPCSTR)"Error", MB_OK);
		return 1;
	}
	return 0;
}

DWORD CMHCDGUIDlg::FindTarget(LPCTSTR lpszProcess)
{
	DWORD dwRet = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe32);
	do
	{
		if (lstrcmpi(pe32.szExeFile, lpszProcess) == 0)
		{
			dwRet = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
	CloseHandle(hSnapshot);
	return dwRet;
}

BOOL CMHCDGUIDlg::RemoteLoadLibrary(DWORD dwProcessID, LPCSTR lpszDll)
{
	// Open war3 process
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessID);

	if (!hProcess)
	{
		AfxMessageBox((LPCTSTR)"OpenProcess Failed");
		return FALSE;
	}
	// Write name of DLL into war3 memory
	DWORD dwSize, dwWritten;
	dwSize = lstrlenA(lpszDll) + 1;
	LPVOID lpBuf = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == lpBuf)
	{
		AfxMessageBox((LPCTSTR)"VirtualAllocEx Failed at 1.");
		CloseHandle(hProcess);
		return FALSE;
	}
	if (WriteProcessMemory(hProcess, lpBuf, (LPVOID)lpszDll, dwSize, &dwWritten))
	{
		// Number of bytes inconsistant -> failed.
		if (dwWritten != dwSize)
		{
			AfxMessageBox((LPCTSTR)"VirtualAllocEx Failed 2.");
			VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
			CloseHandle(hProcess);
			return FALSE;
		}
	}
	else
	{
		AfxMessageBox((LPCTSTR)"WriteProcessMemory Failed");
		CloseHandle(hProcess);
		return FALSE;
	}
	// Let war3 load our DLL.
	DWORD dwID;
	LPVOID pFunc = LoadLibraryA;
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, lpBuf, 0, &dwID);

	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}

BOOL CMHCDGUIDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (pCopyDataStruct->dwData == 0x33)
	{
		CListMsg.AddString((char *)(pCopyDataStruct->lpData));
		CListMsg.SetTopIndex(CListMsg.GetCount() - 1);
	}

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

DWORD CMHCDGUIDlg::dwProcessID = 0;
void CMHCDGUIDlg::OnBnClickedStart()
{
	char szTarget[MAX_PATH] = "war3.exe";

	dwProcessID = FindTarget((LPCTSTR)szTarget);
	if (0 == dwProcessID)
	{
		AfxMessageBox((LPCTSTR)"Cannot find war3.exe");
		//return;
	}
	else if (!RemoteLoadLibrary(dwProcessID, (LPCSTR)"MHCDDLL.dll"))
	{
		AfxMessageBox((LPCTSTR)"Loading DLL failed.");
		//return;
	}
	else
	{
		CListMsg.ResetContent();
	}
}


void CMHCDGUIDlg::OnBnClickedHelp()
{
	CListMsg.AddString("This is the rebuilt English version.");
	CListMsg.AddString("Support Windows 7 32-bit and Warcraft III 1.24b.");
	CListMsg.AddString("Copy MHCDDLL.dll into the same folder with war3.exe.");
	CListMsg.AddString("Then click \"Initialize\" after war3 is started.");
	CListMsg.AddString("This project is made only for my personal interest on Warcraft III.");
	CListMsg.AddString("My used name is suwuhao. Contact: suwuhao@yahoo.com");
	CListMsg.AddString("Current contact: zhujfmail@gmail.com");
	CListMsg.AddString("Current repository: https://github.com/zhujf553");
	CListMsg.SetTopIndex(CListMsg.GetCount() - 1);
}
