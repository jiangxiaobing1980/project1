#if !defined(AFX_OPERATIONEXCEL_H__C7BF6EBD_8D4E_474E_B375_0F951CCC2DCC__INCLUDED_)
#define AFX_OPERATIONEXCEL_H__C7BF6EBD_8D4E_474E_B375_0F951CCC2DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once


#include <afxdb.h>
#include <odbcinst.h>

//#include <afxtempl.h>
#include "OperationList.h"

#endif // _MSC_VER > 1000
// OperationExcel.h : header file
//

//typedef CTypedPtrList<CPtrList , CObject*> CObjectList;

/////////////////////////////////////////////////////////////////////////////
// COperationExcel command target

class COperationExcel : public CCmdTarget
{
	DECLARE_DYNCREATE(COperationExcel)

	COperationExcel();           // protected constructor used by dynamic creation
	virtual ~COperationExcel();
// Attributes
public:

// Operations
public:
	void WriteExcel();

	//参数1:链表指针,参数2:列表框指针,参数3:状态字符串/"自动加载"/"选择加载"
	void ReadExcel(CObjectList * , CListCtrl * , CString );	
	CString GetFilePathName();
	CString GetExcelDriver();
	//CString FilePathName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperationExcel)
	public:
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(COperationExcel)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COperationExcel)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATIONEXCEL_H__C7BF6EBD_8D4E_474E_B375_0F951CCC2DCC__INCLUDED_)
