#if !defined(AFX_SERIESDATA_H__4018965D_B9BB_4A7C_85CC_D55954F6B037__INCLUDED_)
#define AFX_SERIESDATA_H__4018965D_B9BB_4A7C_85CC_D55954F6B037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesData.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSeriesData command target

class CSeriesData : public CCmdTarget
{
	DECLARE_DYNCREATE(CSeriesData)

	CSeriesData();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesData)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSeriesData();

	// Generated message map functions
	//{{AFX_MSG(CSeriesData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSeriesData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESDATA_H__4018965D_B9BB_4A7C_85CC_D55954F6B037__INCLUDED_)
