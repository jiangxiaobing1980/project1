#if !defined(AFX_CREATEBOMITEM_H__84155C5E_E046_43B8_BB08_D9446E0DDAF4__INCLUDED_)
#define AFX_CREATEBOMITEM_H__84155C5E_E046_43B8_BB08_D9446E0DDAF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateBomItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateBomItem dialog

class CCreateBomItem : public CDialog
{
// Construction
public:
	CCreateBomItem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateBomItem)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateBomItem)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateBomItem)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCreateBomItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEBOMITEM_H__84155C5E_E046_43B8_BB08_D9446E0DDAF4__INCLUDED_)
