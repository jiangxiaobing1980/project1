// Dimension.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "Dimension.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDimension

IMPLEMENT_SERIAL(CDimension, CCmdTarget,1)

CDimension::CDimension()
:SideLineLen(10) 
{
	for(int i = 0;i<10;i++)
	{
		CPoint tmp=0;
		ptArr.Add(tmp);
	}
}

CDimension::~CDimension()
{	
	ptArr.RemoveAll();
}

//CBox*	CDimension::pstaOutFrame = NULL ;
//int		CDimension::sc  = 5;



BEGIN_MESSAGE_MAP(CDimension, CCmdTarget)
	//{{AFX_MSG_MAP(CDimension)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDimension message handlers

void CDimension::Serialize(CArchive& ar) 
{
	ptArr.Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar <<   dimText << SideLineLen ;
	}
	else
	{	// loading code

		ar >>   dimText >> SideLineLen ;
	}
}
