
// MHCDGUIDlg.h : header file
//

#pragma once


// CMHCDGUIDlg dialog
class CMHCDGUIDlg : public CDialogEx
{
private:
	static DWORD dwProcessID;
	HANDLE f_;
	char * pInfo;
	char lastInfo = 100;

	int EnableDebugPriv(const char * name);
	DWORD FindTarget(LPCTSTR lpszProcess);
	BOOL RemoteLoadLibrary(DWORD dwProcessID, LPCSTR lpszDll);
	BOOL MyTaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL MyTaskBarDeleteIcon(HWND hwnd, UINT uID);

// Construction
public:
	CMHCDGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MHCDGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CListBox CListMsg;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnMyIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedHelp();
};
