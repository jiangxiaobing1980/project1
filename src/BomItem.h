#if !defined(AFX_BOMITEM_H__794669F0_FC8C_470F_B135_0F29A73D1C0F__INCLUDED_)
#define AFX_BOMITEM_H__794669F0_FC8C_470F_B135_0F29A73D1C0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BomItem.h : header file
//


#include <afxtempl.h>

#include "Series.h"

typedef CTypedPtrList<CObList , CSeries*> CTypePtrList;

/////////////////////////////////////////////////////////////////////////////
// CBomItem command target

class CBomItem : public CCmdTarget
{
	DECLARE_SERIAL(CBomItem)

	CBomItem();           // protected constructor used by dynamic creation
	virtual ~CBomItem();
// Attributes
public:

	CString m_Name;
	CString ID;
	CString m_Type;
	
	
	double m_Length;
	double m_Width;
	double m_Heigth;
	double m_UnitPrice;
	double m_UnitWeight;
	int    m_Position;
	int    m_ParentsPosition;
	CRect  m_rtBox;
	BOOL   m_bIsSeleced;

	CTypePtrList *m_pOutDataList;

// Operations
public:

	//

	virtual BOOL IsSeleced() {return m_bIsSeleced ;}
	virtual void SetSeleced(){	m_bIsSeleced = TRUE ;}	
	virtual void UnSeleced() {	m_bIsSeleced = FALSE ;}
	void OnDraw(CDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBomItem)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CBomItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBomItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOMITEM_H__794669F0_FC8C_470F_B135_0F29A73D1C0F__INCLUDED_)
