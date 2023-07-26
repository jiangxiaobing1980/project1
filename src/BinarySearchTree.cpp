// BinarySearchTree.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "BinarySearchTree.h"

#include "Box.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BinarySearchTree

IMPLEMENT_SERIAL(BinarySearchTree, CCmdTarget,1)

BinarySearchTree::BinarySearchTree()
{
	EnableAutomation();
	Root=NULL;

	 nfx = 60 ;
	 ntx = 60 ;

}

BinarySearchTree::~BinarySearchTree()
{
	
}

//DEL void BinarySearchTree::OnFinalRelease()
//DEL {
//DEL 	// When the last reference for an automation object is released
//DEL 	// OnFinalRelease is called.  The base class will automatically
//DEL 	// deletes the object.  Add additional cleanup required for your
//DEL 	// object before calling the base class.
//DEL 
//DEL 	CCmdTarget::OnFinalRelease();
//DEL }




BEGIN_MESSAGE_MAP(BinarySearchTree, CCmdTarget)
	//{{AFX_MSG_MAP(BinarySearchTree)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(BinarySearchTree, CCmdTarget)
	//{{AFX_DISPATCH_MAP(BinarySearchTree)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBinarySearchTree to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D2D1656C-DF40-4D84-9337-370BA8BA14A5}
static const IID IID_IBinarySearchTree =
{ 0xd2d1656c, 0xdf40, 0x4d84, { 0x93, 0x37, 0x37, 0xb, 0xa8, 0xba, 0x14, 0xa5 } };

BEGIN_INTERFACE_MAP(BinarySearchTree, CCmdTarget)
	INTERFACE_PART(BinarySearchTree, IID_IBinarySearchTree, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BinarySearchTree message handlers

//DEL void BinarySearchTree::Serialize(CArchive& ar) 
//DEL {
//DEL 	if (ar.IsStoring())
//DEL 	{	// storing code
//DEL 
//DEL 		//ar.Write (&Root , sizeof(Root)) ;
//DEL 
//DEL 		//BSTSerialize(Root,ar) ;
//DEL 
//DEL 	}
//DEL 	else
//DEL 	{	// loading code
//DEL 
//DEL 		//ar.Read (&Root , sizeof(Root)) ;
//DEL 		
//DEL 		//UnBSTSerialize(Root,ar) ;
//DEL 	}
//DEL }
