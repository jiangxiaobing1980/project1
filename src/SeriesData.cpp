// SeriesData.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "SeriesData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesData

IMPLEMENT_DYNCREATE(CSeriesData, CCmdTarget)

CSeriesData::CSeriesData()
{
	EnableAutomation();
}

CSeriesData::~CSeriesData()
{
}


void CSeriesData::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSeriesData, CCmdTarget)
	//{{AFX_MSG_MAP(CSeriesData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSeriesData, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSeriesData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISeriesData to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {8C24E458-1E46-4ECA-8293-BDCF901C270A}
static const IID IID_ISeriesData =
{ 0x8c24e458, 0x1e46, 0x4eca, { 0x82, 0x93, 0xbd, 0xcf, 0x90, 0x1c, 0x27, 0xa } };

BEGIN_INTERFACE_MAP(CSeriesData, CCmdTarget)
	INTERFACE_PART(CSeriesData, IID_ISeriesData, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesData message handlers
