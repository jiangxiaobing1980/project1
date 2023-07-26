// CreateBomItem.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "CreateBomItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateBomItem dialog


CCreateBomItem::CCreateBomItem(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateBomItem::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CCreateBomItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCreateBomItem::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CCreateBomItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateBomItem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateBomItem, CDialog)
	//{{AFX_MSG_MAP(CCreateBomItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCreateBomItem, CDialog)
	//{{AFX_DISPATCH_MAP(CCreateBomItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICreateBomItem to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0C740663-D3EC-4D2B-8321-5ECDA0568515}
static const IID IID_ICreateBomItem =
{ 0xc740663, 0xd3ec, 0x4d2b, { 0x83, 0x21, 0x5e, 0xcd, 0xa0, 0x56, 0x85, 0x15 } };

BEGIN_INTERFACE_MAP(CCreateBomItem, CDialog)
	INTERFACE_PART(CCreateBomItem, IID_ICreateBomItem, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateBomItem message handlers

BOOL CCreateBomItem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CListCtrl  *m_ListCtrl = (CListCtrl  *)GetDlgItem(IDC_LIST1);

	//可以先用下面的语句来删除以前的东西：
	//for(int k=2;k>=0;k--) //注意要从后往前删，否则出错
	//m_ListCtrl->DeleteColumn(k);
	//m_ListCtrl->DeleteAllItems();

	m_ListCtrl->InsertColumn(0,_T("类别"),LVCFMT_IMAGE|LVCFMT_LEFT);
	m_ListCtrl->InsertColumn(1,_T("名称"));
	m_ListCtrl->InsertColumn(2,_T("长度"));
	m_ListCtrl->InsertColumn(3,_T("宽度"));
	m_ListCtrl->InsertColumn(4,_T("单重"));
	m_ListCtrl->InsertColumn(5,_T("单价"));
	//然后设置列宽：
	for(int i=0;i<6;i++)
	m_ListCtrl->SetColumnWidth(i ,100);


	//插入行
	m_ListCtrl->InsertItem	(0,		"铝型材");
	m_ListCtrl->SetItemText	(0,1,	"窗框");
	m_ListCtrl->SetItemText	(0,2,	"1000");
	m_ListCtrl->SetItemText	(0,3,	"0");
	m_ListCtrl->SetItemText	(0,4,	"1.925");
	m_ListCtrl->SetItemText	(0,5,	"240.56");



	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
