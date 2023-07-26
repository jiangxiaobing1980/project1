// Series.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "Series.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeries

IMPLEMENT_SERIAL(CSeries, CCmdTarget,1)

CSeries::CSeries()
{
	EnableAutomation();
}

CSeries::~CSeries()
{
}


void CSeries::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSeries, CCmdTarget)
	//{{AFX_MSG_MAP(CSeries)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSeries, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSeries)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISeries to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {DA8CED6A-67DE-4120-A5E0-55F440DD99D8}
static const IID IID_ISeries =
{ 0xda8ced6a, 0x67de, 0x4120, { 0xa5, 0xe0, 0x55, 0xf4, 0x40, 0xdd, 0x99, 0xd8 } };

BEGIN_INTERFACE_MAP(CSeries, CCmdTarget)
	INTERFACE_PART(CSeries, IID_ISeries, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeries message handlers

void CSeries::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		ar << Name << Val << WeightMeter << UnitPrice;
	}
	else
	{	// loading code
		ar >> Name >> Val >> WeightMeter >> UnitPrice;
	}
}

//DEL double CSeries::GetVal(CString name)
//DEL {
//DEL 	if (name == Name) 	return Val;
//DEL 	else return -999999 ;
//DEL }
