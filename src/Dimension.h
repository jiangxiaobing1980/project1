#if !defined(AFX_DIMENSION_H__06803123_B208_430B_B7C1_902909B28492__INCLUDED_)
#define AFX_DIMENSION_H__06803123_B208_430B_B7C1_902909B28492__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
typedef CArray<CPoint,CPoint> PTARRAY;

class CDimension : public CCmdTarget
{
	DECLARE_SERIAL(CDimension)

	CDimension();           // protected constructor used by dynamic creation
	virtual ~CDimension();

// Attributes
public:

	//限定
	//0-1为输入左右点或上下点//2-3为文字框选择框
	PTARRAY ptArr;	

	CString dimText;

	int SideLineLen ;

private:

// Operations
public:


public:



	BOOL IsSelected(const CPoint & ptHit) const
	{
		
		CRect rt(ptArr[2],ptArr[3]);
		//调整坐标
		rt.NormalizeRect();

		if(rt.PtInRect(ptHit))
		{
			AfxMessageBox("Dimension is : " + dimText);
		}
		
		return rt.PtInRect(ptHit);		
		
	}

	//判断是否是水平标注
	BOOL isHorizontalDim()
	{
		
		if(	ptArr[0].y == ptArr[1].y)
			return TRUE;
		else
			return FALSE;

	}

	void Sideline(CDC* pDC , CPoint pt)
	{
		pDC->MoveTo(pt.x,pt.y+SideLineLen);
		pDC->LineTo(pt.x,pt.y-SideLineLen);
	}

	void Linkline(CDC* pDC)
	{
		pDC->MoveTo(ptArr[0]);
		pDC->LineTo(ptArr[1]);
	}

	void DrawText(CDC* pDC)
	{
		dimText = itos(abs( ptArr[1].x-ptArr[0].x));

		ptArr[2] = CPoint((ptArr[1].x-ptArr[0].x)/2+ptArr[0].x-SideLineLen, ptArr[0].y+SideLineLen);
		ptArr[3] = CPoint(ptArr[2].x+SideLineLen*3,ptArr[2].y-SideLineLen*2);

		pDC->TextOut(ptArr[2].x+2 , ptArr[2].y-SideLineLen*2 , dimText);	
		pDC->Rectangle(ptArr[2].x, ptArr[2].y, ptArr[3].x , ptArr[3].y);
		
	}

	void OnDraw(CDC* pDC)
	{
		/////////////////////////////////////////////////	
		//输出	
		pDC->SelectStockObject(NULL_BRUSH );
		Sideline(pDC ,ptArr[0]);
		Sideline(pDC ,ptArr[1]);
		Linkline(pDC);
		DrawText(pDC);
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDimension)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDimension)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMENSION_H__06803123_B208_430B_B7C1_902909B28492__INCLUDED_)
