#if !defined(AFX_SERIESDATADLG_H__DD76B212_06F7_469E_8837_3BF2AF0B3831__INCLUDED_)
#define AFX_SERIESDATADLG_H__DD76B212_06F7_469E_8837_3BF2AF0B3831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OperationExcel.h"

/////////////////////////////////////////////////////////////////////////////
// CSeriesDataDlg dialog

class CSeriesDataDlg : public CDialog
{
// Construction
public:
	CSeriesDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSeriesDataDlg)
	enum { IDD = IDD_DIALOG3 };
	//}}AFX_DATA
public:
	CObjectList *pubTable , *pseriesTable;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesDataDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeriesDataDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSeriesDataDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESDATADLG_H__DD76B212_06F7_469E_8837_3BF2AF0B3831__INCLUDED_)
