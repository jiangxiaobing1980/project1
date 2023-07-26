// OperationList.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "OperationList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperationList

IMPLEMENT_SERIAL(COperationList, CCmdTarget,1)

COperationList::COperationList()
{
}

COperationList::~COperationList()
{
	while (!m_List.IsEmpty())
	{
	     delete m_List.GetHead();
	     m_List.RemoveHead();
    }

}


BEGIN_MESSAGE_MAP(COperationList, CCmdTarget)
	//{{AFX_MSG_MAP(COperationList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperationList message handlers

void COperationList::Serialize(CArchive& ar) 
{
	m_List.Serialize( ar); 

	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
