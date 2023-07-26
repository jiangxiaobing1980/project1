#if !defined(AFX_SETSIZE_H__A8FC2D61_46F6_45E8_86C9_3F46EDE13590__INCLUDED_)
#define AFX_SETSIZE_H__A8FC2D61_46F6_45E8_86C9_3F46EDE13590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetSize dialog

class CSetSize : public CDialog
{
// Construction
public:
	CSetSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetSize)
	enum { IDD = IDD_DIALOG2 };
	int		m_cx;
	int		m_cy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSize)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetSize)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSetSize)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSIZE_H__A8FC2D61_46F6_45E8_86C9_3F46EDE13590__INCLUDED_)
