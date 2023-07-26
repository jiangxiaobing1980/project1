// SetSize.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "SetSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSize dialog


CSetSize::CSetSize(CWnd* pParent /*=NULL*/)
	: CDialog(CSetSize::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CSetSize)
	m_cx = 0;
	m_cy = 0;
	//}}AFX_DATA_INIT
}


void CSetSize::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CSetSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSize)
	DDX_Text(pDX, IDC_EDIT1, m_cx);
	DDX_Text(pDX, IDC_EDIT2, m_cy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSize, CDialog)
	//{{AFX_MSG_MAP(CSetSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSetSize, CDialog)
	//{{AFX_DISPATCH_MAP(CSetSize)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISetSize to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {776A285A-C9DC-4E5B-B4A7-28C68F174C85}
static const IID IID_ISetSize =
{ 0x776a285a, 0xc9dc, 0x4e5b, { 0xb4, 0xa7, 0x28, 0xc6, 0x8f, 0x17, 0x4c, 0x85 } };

BEGIN_INTERFACE_MAP(CSetSize, CDialog)
	INTERFACE_PART(CSetSize, IID_ISetSize, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSize message handlers

BOOL CSetSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	UpdateData();
	m_cx = 2800;
	m_cy = 2000;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
