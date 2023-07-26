#if !defined(AFX_BOX_H__D6DF5F90_7675_4BD4_A764_EC8DBBD8DC46__INCLUDED_)
#define AFX_BOX_H__D6DF5F90_7675_4BD4_A764_EC8DBBD8DC46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Box.h : header file
//
//#include <afxtempl.h>
//typedef CTypedPtrList<CObList , CObject*> CObjectList;


/////////////////////////////////////////////////////////////////////////////
// CBox command target

class CBox : public CCmdTarget
{
	DECLARE_SERIAL(CBox)

	CBox();           // protected constructor used by dynamic creation
	virtual ~CBox();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBox)
	public:
	virtual void OnFinalRelease();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

public:
	//static CObjectList *PublicTable , *pSeriesTable , *pSamples;
	//static CDC *pDC ;

public:

	//CBox(CRect rt) : m_rtBox( rt), m_bIsSeleced(FALSE) , szType("0") ,m_Pos(-1) , m_Parents(-1){}

private:	

	BOOL	m_bIsSeleced;
	CRect	m_rtBox;

public:
	int    m_Pos;
	int    m_Parents;
/*
	CString	szName ;	
	CString	szType;

	float m_Length ;
	float m_Width ;
	float m_Height ;
	float m_Weight ;
	float m_Price ;
*/
	/*
	//基类 
	class bomitem  
	{  
	public:
	bomitem();
	virtual ~bomitem(); 
	
	  public:  
	  
		int id ;

		string type ; 
		string parenstype ;  

		POINT Insert_pt;
		
		  
};

  */





public:

	virtual CRect GetBox() const{ return  m_rtBox ;}	
	virtual void  SetBox(CRect  rtBox) { m_rtBox = rtBox ;}	
	 //CString GetToType() const{ return  szType ;}	
	 //void  SetToType(int  iType) { szType = iType ;}	
	
	virtual BOOL IsSeleced() {return m_bIsSeleced ;}
	virtual void SetSeleced(){	m_bIsSeleced = TRUE ;}	
	virtual void UnSeleced() {	m_bIsSeleced = FALSE ;}
	
	virtual BOOL SelectTest(const CPoint & ptHit) const
	{
		
		CRect rtBox(m_rtBox);
		//调整坐标
		rtBox.NormalizeRect();
		
		return rtBox.PtInRect(ptHit);		
		
	}
	
// 	virtual BOOL SelectTest(const CRect & rtHit) const
// 	{
// 		
// 		CRect rtBox(m_rtBox);
// 		//调整坐标
// 		rtBox.NormalizeRect();
// 		
// 		CRect rtTest(rtHit);
// 		//调整坐标
// 		rtTest.NormalizeRect();
// 		
// 		
// 		CRect rtRet(0,0,0,0);
// 		
// 		//IntersectRect此函数使CRect等于两个现有矩形的交集。交集是同时包含在两个现有矩形中的最大矩形。
// 		
// 		return rtRet.IntersectRect(&rtBox,&rtTest);		
// 		
// 	}
	


	virtual void OnDraw(CDC*); //
	
public:



protected:
	
// 	//调整坐标
// 	void ReviseRect(int iMapMode) 
// 	{
// 		if(MM_TEXT == iMapMode)
// 		{
// 			m_rtBox.bottom	=  - abs(m_rtBox.bottom)  ;
// 			m_rtBox.top		=  - abs(m_rtBox.top)  ;			
// 		}
// 		else
// 		{			
// 			m_rtBox.bottom	=   abs(m_rtBox.bottom)  ;
// 			m_rtBox.top		=   abs(m_rtBox.top)  ;
// 		}		
// 	}

	//virtual void DrawSelecedBox(CDC* pDC)	{	}



	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};





/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOX_H__D6DF5F90_7675_4BD4_A764_EC8DBBD8DC46__INCLUDED_)
