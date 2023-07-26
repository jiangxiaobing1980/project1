// BomItem.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "BomItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBomItem

IMPLEMENT_SERIAL(CBomItem, CCmdTarget,1)

CBomItem::CBomItem()
{
	EnableAutomation();
	ID = "";
	m_Name = "";	 
	
	m_Length = 0 ;
	m_Width = 0 ;
	m_Heigth = 0 ;

	m_UnitPrice = 0 ;
	m_UnitWeight = 0 ;

	m_Position = 0 ;
	m_ParentsPosition = 0 ;

	m_Type = "";
	m_rtBox.SetRect(0,0,0,0);
	m_bIsSeleced = FALSE;
	
	m_pOutDataList = NULL;


}

CBomItem::~CBomItem()
{
}


void CBomItem::OnDraw(CDC* pDC)
{
	
	if(IsSeleced())
	{	
		//Ìî³ä			  					 
		CBrush brush;
		brush.CreateSolidBrush(RGB(87,250,255));	
		CBrush  *OldBrush = (CBrush*)pDC->SelectObject(&brush);
		pDC->Rectangle(m_rtBox);
		pDC->SelectStockObject(BLACK_BRUSH );
		brush.DeleteObject();
		
	}
	else
	{	
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(m_rtBox);
	}


	pDC->SelectStockObject(NULL_BRUSH);	
	CRect rt = m_rtBox;
	CPoint pt = rt.CenterPoint();

	if("¹Ì¶¨²£Á§´°" == m_Type)
	{		
		pDC->MoveTo(pt.x-10,pt.y);	pDC->LineTo(pt.x+10,pt.y);
		pDC->MoveTo(pt.x,pt.y-10);	pDC->LineTo(pt.x,pt.y+10);		
		
	}
	
	if("×óÆ½¿ª" == m_Type)
	{		
		pDC->MoveTo(rt.right,rt.top);	pDC->LineTo(rt.left,rt.top+	(rt.bottom-rt.top)/2 );		
		pDC->LineTo(rt.right,rt.bottom);
		
	}
	
	if("ÓÒÆ½¿ª" == m_Type)
	{		
		pDC->MoveTo(rt.left,rt.top);	pDC->LineTo(rt.right,rt.top+	(rt.bottom-rt.top)/2 );		
		pDC->LineTo(rt.left,rt.bottom);
		
	}
	
	
	
}



void CBomItem::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CBomItem, CCmdTarget)
	//{{AFX_MSG_MAP(CBomItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBomItem, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CBomItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBomItem to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {CE5F6B20-1906-4B2F-B180-360AA594FCDB}
static const IID IID_IBomItem =
{ 0xce5f6b20, 0x1906, 0x4b2f, { 0xb1, 0x80, 0x36, 0xa, 0xa5, 0x94, 0xfc, 0xdb } };

BEGIN_INTERFACE_MAP(CBomItem, CCmdTarget)
	INTERFACE_PART(CBomItem, IID_IBomItem, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBomItem message handlers
