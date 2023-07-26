// Box.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "Box.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CBox

IMPLEMENT_SERIAL(CBox, CCmdTarget,1)

//CObjectList* CBox::PublicTable = NULL;
//CObjectList* CBox::pSeriesTable = NULL;
//CObjectList* CBox::pSamples = NULL;


CBox::CBox()
{
	//EnableAutomation();
	
}

CBox::~CBox()
{

}


void CBox::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CBox, CCmdTarget)
	//{{AFX_MSG_MAP(CBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBox, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBox to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D433A03A-780F-44BC-87C5-9848F9B759B4}
static const IID IID_IBox =
{ 0xd433a03a, 0x780f, 0x44bc, { 0x87, 0xc5, 0x98, 0x48, 0xf9, 0xb7, 0x59, 0xb4 } };

BEGIN_INTERFACE_MAP(CBox, CCmdTarget)
	INTERFACE_PART(CBox, IID_IBox, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBox message handlers

void CBox::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		//ar << m_rtBox << m_bIsSeleced << m_Type << szName << m_Parents << m_Pos;		
	}
	else
	{	// loading code
		//ar >> m_rtBox >>m_bIsSeleced >> m_Type >>  szName >>m_Parents >> m_Pos;
	}
}


void CBox::OnDraw(CDC* pDC)
{
	//UnSeleced();
	if(IsSeleced())
	{	
		//Моід			  					 
		CBrush brush;
		brush.CreateSolidBrush(RGB(87,250,255));	
		CBrush  *OldBrush = (CBrush*)pDC->SelectObject(&brush);
		pDC->Rectangle(GetBox());
		pDC->SelectStockObject(BLACK_BRUSH );
		brush.DeleteObject();

	}
	else
	{	
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(m_rtBox);
	}
/*
	if(5 == GetToType())
	{
		pDC->SelectStockObject(NULL_BRUSH);
		
		CRect rt = GetBox();

		CPoint pt = rt.CenterPoint();
		
		pDC->MoveTo(pt.x-10,pt.y);	pDC->LineTo(pt.x+10,pt.y);
		pDC->MoveTo(pt.x,pt.y-10);	pDC->LineTo(pt.x,pt.y+10);
		
	
		
	}

	if(6 == GetToType())
	{
		pDC->SelectStockObject(NULL_BRUSH);
		
		CRect rt = GetBox();
		
		pDC->MoveTo(rt.right,rt.top);	pDC->LineTo(rt.left,rt.top+	(rt.bottom-rt.top)/2 );
		
		pDC->LineTo(rt.right,rt.bottom);
		
	}

	if(7 == GetToType())
	{
		pDC->SelectStockObject(NULL_BRUSH);
		
		CRect rt = GetBox();
		
		pDC->MoveTo(rt.left,rt.top);	pDC->LineTo(rt.right,rt.top+	(rt.bottom-rt.top)/2 );
		
		pDC->LineTo(rt.left,rt.bottom);
		
	}

*/
	
}
