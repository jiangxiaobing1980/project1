#if !defined(AFX_SERIES_H__01EFA566_50DE_4ED0_9570_225D6D516B95__INCLUDED_)
#define AFX_SERIES_H__01EFA566_50DE_4ED0_9570_225D6D516B95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Series.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSeries command target

class CSeries : public CCmdTarget
{
	DECLARE_SERIAL(CSeries)

	CSeries();           // protected constructor used by dynamic creation
	virtual ~CSeries();

	CSeries(CString na, double dvl, double dWeightMeter, double dUnitPrice)
		: Name( na)
		, Val(dvl) 
		, WeightMeter(dWeightMeter)
		, UnitPrice(dUnitPrice)
	{}

// Attributes
public:

// Operations
public:

	CString Name;
	double	Val;
	double	WeightMeter;
	double	UnitPrice;




public:
	//int GetData(CString sName){}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeries)
	public:
	virtual void OnFinalRelease();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CSeries)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSeries)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIES_H__01EFA566_50DE_4ED0_9570_225D6D516B95__INCLUDED_)
