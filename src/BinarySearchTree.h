#if !defined(AFX_BINARYSEARCHTREE_H__76835A36_2704_4FCF_954A_18C604C19FF1__INCLUDED_)
#define AFX_BINARYSEARCHTREE_H__76835A36_2704_4FCF_954A_18C604C19FF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinarySearchTree.h : header file

#include "Box.h"
#include "operationList.h"
//#include<iostream>

#include <afxtempl.h>
#pragma warning(disable:4786)
#include<set>
using namespace std;

typedef CTypedPtrList<CObList , CBox*> CBoxList;
typedef CTypedPtrMap <CMapStringToPtr, CString, int*> CRecords;

#include "Series.h"
typedef CTypedPtrList<CObList , CSeries*> CSeriesList;

struct BinarySearchTreeNode{

	CBox * data ;	
	BinarySearchTreeNode *leftChild;	//左子节点, 左框
	BinarySearchTreeNode *rightChild;	//右子节点，右框
	BinarySearchTreeNode *InChild;		//三叉节点，也是中梃节点
	BinarySearchTreeNode *ParentChild;		//前驱节点
	BinarySearchTreeNode(CBox* tempdata)
	{	data			= tempdata;
		leftChild		= NULL;
		rightChild		= NULL;
		InChild			= NULL;		//三叉节点，也是中梃节点
		ParentChild		= NULL;		//前驱节点
	}
};


///////////////////////////////////////////////////////////////////
// BinarySearchTree command target

class BinarySearchTree : public CCmdTarget
{
	DECLARE_SERIAL(BinarySearchTree)

	BinarySearchTree();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BinarySearchTree)
	public:
	//}}AFX_VIRTUAL

// Implementation


protected:
	
	BinarySearchTreeNode * Root;

public:
	
	CBoxList* ml;

	CSeriesList* pSeriesList ;

	int nfx ;
	int ntx ;

	CSeriesList* pSeriesList1 ;


private:

public:

	virtual ~BinarySearchTree();

public:

	double GetVal(CString name)
	{
		
		double temp = -999999;
		// Dump the list elements to the debug window.
		POSITION pos = pSeriesList->GetHeadPosition();
		for (int i = 0; i < pSeriesList->GetCount(); i++)
		{			
			//取得数据
			POSITION pos1 = pSeriesList->FindIndex(i);					
			CSeries* d1 = (CSeries* )ml->GetAt(pos1);			
			
			if(name == d1->Name)
			{		
				temp = d1->Val ;
				break;
			}
		}
		return temp ;
		
	}

	BinarySearchTreeNode *GetRoot()	{return this->Root;}

	void SetRoot(BinarySearchTreeNode * p)	{this->Root = p;}
	
	//绘图图形
	void OnDraw (BinarySearchTreeNode * tempRoot , CDC * pDC )
	{
		//这里是绘制一个节点内的框
		GetBoxToNode (tempRoot) ->OnDraw(pDC);
	}

/**********************************************************
	*参数1：当前子树根节点
	*参数2：函数指针
	*参数3：备用指针

	*返回值：空
	*功能：前序遍历二叉查找树
************************************************************/
 void PreOrderBSTPrint(BinarySearchTreeNode * tempRoot , CDC * pDC)
 	{		
		if(NULL==tempRoot)	return ;
		
		OnDraw(tempRoot,pDC);
		//如果有中梃, 就绘制它
 		if(tempRoot->InChild)
 		{
 			OnDraw(tempRoot->InChild,pDC);
 		}

		PreOrderBSTPrint(tempRoot->leftChild , pDC);
		PreOrderBSTPrint(tempRoot->rightChild , pDC);	
 	}


BOOL InsertBST(BinarySearchTreeNode * tempRoot , CPoint  tempPt , UINT iType)
	{
			BinarySearchTreeNode* p  =  NULL;
			SeletedToNode(tempRoot ,tempPt , &p);


			if (p)
			{
				CreateToNode(p , tempPt ,iType);
				return TRUE ;
			}
			else	return FALSE;
	}


void SetIsSeleted(BinarySearchTreeNode *tempRoot  , CPoint  pt)
{

//在这里要清除所有选中状态
	UnsetSeleted(tempRoot);

	BinarySearchTreeNode* p  = NULL;
	SeletedToNode(tempRoot , pt , &p);

	if(p)
	{	
		CBox* m = GetBoxToNode(p);								
		m->SetSeleced();		
	}

}

void SeletedToNode(BinarySearchTreeNode *tempRoot, CPoint  pt , BinarySearchTreeNode **p)
{
	if(NULL==tempRoot)	return ;

	CBox * p0 = GetBoxToNode(tempRoot) ;				
	CRect rtmp0 = p0->GetBox() ;	

	if( rtmp0.PtInRect(pt) && !tempRoot->leftChild && !tempRoot->rightChild)
	{		
			*p = tempRoot;	
			return ;
	}

	
	if(tempRoot->InChild)
	{

		CBox * p2 = GetBoxToNode(tempRoot->InChild) ;				
		CRect rtmp2 = p2->GetBox() ;
		
		if( rtmp2.PtInRect(pt))
		{		
			*p = tempRoot->InChild;	
			return ;
		}
	}

	if(tempRoot->leftChild)
		SeletedToNode(tempRoot->leftChild, pt ,	p);

	if(tempRoot->rightChild)
		SeletedToNode(tempRoot->rightChild , pt, p);

}


void UpDataToSet(BinarySearchTreeNode *tempRoot, set<int>& x , set<int>& y)
{
	if(NULL==tempRoot)	return ;	


	//如果是根节点
	if( tempRoot == Root)
	{
		//先清空set	
		while (!x.empty())
		{
			x.erase(x.begin());        
		}		
		x.clear();	
		
		
		while (!y.empty())
		{
			y.erase(y.begin());        
		}
		y.clear();
		
		//把左和右插入set
		CBox * p0 = GetBoxToNode(tempRoot) ;
		CRect rtmp0 = p0->GetBox() ;		
		
		x.insert((int)rtmp0.left);
		x.insert((int)rtmp0.right);

		y.insert((int)rtmp0.top);
		y.insert((int)rtmp0.bottom);


	}
	else
	{
		if(tempRoot->InChild )
		{
					
				CBox * p2 = GetBoxToNode(tempRoot->InChild) ;
				int i = 0	//p2->GetToType();

				if(i == 2)
				{					
					CRect rtmp2 = p2->GetBox() ;
					CPoint pt2 = rtmp2.CenterPoint();
					
					x.insert((int)pt2.x);		
					
				}

				if(i == 12)
				{					
					CRect rtmp12 = p2->GetBox() ;
					CPoint pt12 = rtmp12.CenterPoint();
					
					y.insert((int)pt12.y);		
					
				}

		}
	}
	

	
	if(tempRoot->leftChild)
		UpDataToSet(tempRoot->leftChild, x , y);
	
	if(tempRoot->rightChild)
		UpDataToSet(tempRoot->rightChild , x , y);
	
}


//创建窗框节点
BOOL CreateToFrameNode(BinarySearchTreeNode *tempRoot  , CRect rt)
{
	if(NULL==tempRoot && tempRoot == Root )


	{
		//1. 把框大小传进来
		//2. 创建2个节点 分别为外框、内框2个子节点
		//3. 把指针都连接起来
		
		//窗框宽度
// 		int k = 10;
// 		if(pRecords)
// 		{		
// 			int *kx= NULL ;	
// 			pRecords->Lookup("窗框小面", kx);
// 			k= *kx ;
// 		}

		int k = nfx ;
		
		if(pSeriesList1 && !pSeriesList1->IsEmpty()  )
		{
			//AfxMessageBox("000");
			CoperationList pOperationList ;
			k = (int) pOperationList.NameToValue(pSeriesList1, "窗框小面") ;
		}

// 		CString str ;
// 		str.Format("窗框小面: %d",k);					
// 		AfxMessageBox(str);

		//////////////////////////////////////////////////
		
		CRect* r1 = new CRect(rt);
		CBox* c1 = new CBox(r1);
		c1->SetToType(0);
		BinarySearchTreeNode* n1 = new BinarySearchTreeNode (c1);		
		SetRoot(n1);
	
			
		CRect* r2 = new CRect(rt.left+k,rt.top+k,rt.right-k,rt.bottom-k);
		CBox* c2 = new CBox(r2);
		c2->SetToType(0);
		BinarySearchTreeNode* n2 = new BinarySearchTreeNode (c2);
		n1->leftChild = n2 ;
		n2->ParentChild = n1;

		////////////////////////////////////////////////////

		return TRUE ;	
	}
	else 	return FALSE;
	

	
}

	
//创建一个节点
BOOL CreateToNode(BinarySearchTreeNode *temp  , CPoint  pt , UINT iType)
{
	if(NULL==temp)
		return FALSE;
	else
	{


		int v = ntx ;
		
		if(pSeriesList1 && !pSeriesList1->IsEmpty()  )
		{
			//AfxMessageBox("000");
			CoperationList pOperationList ;
			v = pOperationList.NameToValue(pSeriesList1, "中梃小面") ;
		}


		

			CBox* m0 = GetBoxToNode(temp);
			CRect p0 = m0->GetBox();//为父框

			
		if(2 == iType)
		{		
		

		
			CRect* p1 = new CRect(p0.left,p0.top,pt.x-v/2,p0.bottom);
			CBox*  m1 = new CBox(p1);
			BinarySearchTreeNode* n1 = new BinarySearchTreeNode (m1);	
			temp->leftChild = n1;
			n1->ParentChild = temp ;
			
			CRect* p2 = new CRect(pt.x-v/2,p0.top,pt.x+v/2,p0.bottom);
			CBox*  m2 = new CBox(p2);
			m2->SetToType(iType);
			BinarySearchTreeNode* n2 = new BinarySearchTreeNode (m2);	
			temp->InChild = n2;
			n2->ParentChild = temp ;

			CRect* p3 = new CRect(pt.x+v/2,p0.top,p0.right,p0.bottom);
			CBox*  m3 = new CBox(p3);
			BinarySearchTreeNode* n3 = new BinarySearchTreeNode (m3);	
			temp->rightChild = n3;
			n3->ParentChild = temp ;
		}

		if(12 == iType)
		{			
			//CBox* m0 = GetBoxToNode(temp);
			//CRect p0 = m0->GetBox();//为父框
					
			
			CRect* p1 = new CRect(p0.left,p0.top,p0.right , pt.y-v/2);
			CBox*  m1 = new CBox(p1);			
			BinarySearchTreeNode* n1 = new BinarySearchTreeNode (m1);	
			temp->leftChild = n1;
			n1->ParentChild = temp ;
			
			CRect* p2 = new CRect(p0.left,pt.y-v/2,p0.right,pt.y+v/2);
			CBox*  m2 = new CBox(p2);
			m2->SetToType(iType);
			BinarySearchTreeNode* n2 = new BinarySearchTreeNode (m2);	
			temp->InChild = n2;
			n2->ParentChild = temp ;
			
			CRect* p3 = new CRect(p0.left,pt.y+v/2,p0.right,p0.bottom);
			CBox*  m3 = new CBox(p3);
			BinarySearchTreeNode* n3 = new BinarySearchTreeNode (m3);	
			temp->rightChild = n3;
			n3->ParentChild = temp ;
		}
	
		m0->SetToType(0);

	}

	

	return TRUE ;

}

/**********************************************************
*功能：取得一个RECT
*参数：节点
*返回值：RECT
************************************************************/
CRect* GetRectToNode(BinarySearchTreeNode *p )
{
	if(p)
	{		
		CBox * pb = (CBox *)p->data ;		
		return & pb->GetBox() ;	
	}
	else return NULL;	
}


void ModfiyInBox()
{
	BinarySearchTreeNode * tempRoot = GetRoot();


	if(tempRoot && tempRoot->leftChild)
	{	
		int xm = 55 ;

		if(pSeriesList1 && !pSeriesList1->IsEmpty()  )
		{
			//AfxMessageBox("000");
			CoperationList pOperationList ;
			xm = (int)pOperationList.NameToValue(pSeriesList1, "窗框小面") ;
		}

		CBox* b0 = GetBoxToNode(tempRoot);
		CRect rt0 = b0->GetBox();
		//开始操作中梃节点
		CBox* b1 = GetBoxToNode(tempRoot->leftChild);
		CRect rt1(rt0.left + xm , rt0.top +xm , rt0.right - xm , rt0.bottom - xm );
		b1->SetBox(rt1);	
	
	
		//4. 更新所有节点的左节点的数据和右节点的数据
		PreOrderBST(Root, 4);	
	}	
 }



 void MoveToNode(BinarySearchTreeNode *tempRoot , int value)
 {
 	if(tempRoot)
 	{			
 			//开始操作中梃节点
 			CBox* b0 = GetBoxToNode(tempRoot);
 			CRect r0 = b0->GetBox();
 			
				UINT s = b0->GetToType() ;

				if (2 == s)
				{
					r0.left		+= value;
					r0.right	+= value;
					b0->SetBox(r0);//为父框				
				}
				
				
				if (12 == s)
				{
					r0.top		+= value;
					r0.bottom	+= value;
					b0->SetBox(r0);//为父框
						
				}
						//4. 更新所有节点的左节点的数据和右节点的数据
					PreOrderBST(Root, 4);	
 		}	
 }

void DeletedToNode(BinarySearchTreeNode *tempRoot)
{
	if(tempRoot)
	{	
			CBox* i = NULL ;
			CBox* l = NULL ;
			CBox* r = NULL;
			

			//这是左右节点都无子节情况删除
			if(!tempRoot->ParentChild->leftChild->InChild && !tempRoot->ParentChild->rightChild->InChild)
			{
				i = GetBoxToNode(tempRoot->ParentChild->InChild);
				l = GetBoxToNode(tempRoot->ParentChild->leftChild);
				r = GetBoxToNode(tempRoot->ParentChild->rightChild);
				
				tempRoot->ParentChild->InChild = NULL;
				tempRoot->ParentChild->leftChild = NULL;
				tempRoot->ParentChild->rightChild = NULL;
				
				delete i ;
				delete l ;
				delete r ;				
				
			}

	}
	
	
	
}

void OperateToNode(BinarySearchTreeNode *tempRoot , CPoint tempPt , int ModifyNum , int operNum)
{
	if(tempRoot)
	{

		if(77 == operNum)
		{
			//AfxMessageBox("0000");
			ModfiyInBox();
		}
			
		

		//1. 先取得选中的节点		
		BinarySearchTreeNode* p  = NULL ;
		SeletedToNode(tempRoot ,tempPt , &p);
		

		
		
		//是否是中梃节点
		if(p && p != Root && p != Root->leftChild  )
		{
			//如果选中的是左节点或右节点直接返回
			if (p == p->ParentChild->leftChild || p == p->ParentChild->rightChild )
			{
				//设置框状态
				if(5 == operNum)
				{
					CBox* pA =GetBoxToNode (p);
					pA->SetToType(5);
				}

				//设置框状态
				if(6 == operNum)
				{
					CBox* pB =GetBoxToNode (p);
					pB->SetToType(6);
				}

				//设置框状态
				if(7 == operNum)
				{
					CBox* pC =GetBoxToNode (p);
					pC->SetToType(7);
				}
					//修改窗框小面


				return;	
			}	
			
			//修改
			if(75 == operNum)
			MoveToNode (p->ParentChild->InChild , ModifyNum);

			//删除
			if(76 == operNum)
			DeletedToNode (p->ParentChild->InChild );

		
		
	
		}
		
	}
	
}


void UpdateLR(BinarySearchTreeNode* tempRoot)
{
	if (tempRoot != Root)
	{
		if(tempRoot && tempRoot->InChild && tempRoot->leftChild && tempRoot->rightChild)
		{
				//取得父节点框
				CBox* b0 = GetBoxToNode(tempRoot);
				CRect r0 = b0->GetBox();
				
				//取得中梃节点框
				CBox* b2 = GetBoxToNode(tempRoot->InChild);
				CRect r2 = b2->GetBox();
				UINT s = b2 ->GetToType();

				if(2 ==s)
				{				//取得左框
					CBox* b1 = GetBoxToNode(tempRoot->leftChild);
					CRect r1 = b1->GetBox();						
					r1.top = r0.top;
					r1.bottom = r0.bottom;

					r1.left = r0.left;
					r1.right = r2.left;
					//把修改好的RECT再写回去
					b1->SetBox(r1);//为父框
				
					
					CBox* b2 = GetBoxToNode(tempRoot->InChild);
					CRect r2 = b2->GetBox();
					
					r2.top =	r0.top;
					r2.bottom = r0.bottom;
					//把修改好的RECT再写回去
					b2->SetBox(r2);//为父框

					
					//取得右框//////////////////////////////////
					CBox* b3 = GetBoxToNode(tempRoot->rightChild);
					CRect r3 = b3->GetBox();				
					r3.top = r0.top;
					r3.bottom = r0.bottom;

					r3.left = r2.right;
					r3.right =r0.right;
					//把修改好的RECT再写回去
					b3->SetBox(r3);//为父框	

				}

				if(12 ==s)
				{				//取得左框
					CBox* b1 = GetBoxToNode(tempRoot->leftChild);
					CRect r1 = b1->GetBox();
					//r1.NormalizeRect();	
					r1.left = r0.left;
					r1.right = r0.right;

					r1.top = r0.top;
					r1.bottom = r2.top;
					//把修改好的RECT再写回去
					b1->SetBox(r1);//为父框


					//取得右框//////////////////////////////////
					CBox* b2 = GetBoxToNode(tempRoot->InChild);
					CRect r2 = b2->GetBox();
					
					r2.left = r0.left;
					r2.right = r0.right;
					
					//r2.top = r0.bottom;
					//r2.bottom =r0.bottom;
					//把修改好的RECT再写回去
					b2->SetBox(r2);//为父框	
				
					
					//取得右框//////////////////////////////////
					CBox* b3 = GetBoxToNode(tempRoot->rightChild);
					CRect r3 = b3->GetBox();
					
					r3.left = r0.left;
					r3.right = r0.right;

					r3.top = r2.bottom;
					r3.bottom =r0.bottom;
					//把修改好的RECT再写回去
					b3->SetBox(r3);//为父框	
					
				}
			
			}
	}

}


CBox* GetBoxToNode(BinarySearchTreeNode *p )
{
	if(p)
	{		
		CBox * pb = (CBox *)p->data ;		
		return pb ;	
	}
	else return NULL;	
}

void UnsetSeleted(BinarySearchTreeNode *tempRoot)
{

	if(NULL==tempRoot)
		return ;

	//清除本体选中状态
	BinarySearchTreeNode* p  = tempRoot;	
	CBox* m = GetBoxToNode(p);
	m->UnSeleced();	
	
	//清除中梃选中状态
	if(p->InChild)
	{
		CBox* n = GetBoxToNode(p->InChild);			
		n->UnSeleced();
	}

	UnsetSeleted(tempRoot->leftChild );
 	UnsetSeleted(tempRoot->rightChild);

}


//DEL   void UnBSTSerialize(BinarySearchTreeNode *tempRoot ,CArchive& ar)
//DEL   {
//DEL   	//Serialize(CArchive& ar) 
//DEL  	
//DEL  	if(NULL==tempRoot)
//DEL   		return ;
//DEL   
//DEL //   	if(Root != tempRoot)
//DEL // 	{
//DEL //   		ar.Read (&tempRoot , sizeof(tempRoot)) ;
//DEL //  		
//DEL //   		
//DEL //   		if(tempRoot->InChild)
//DEL // 		{
//DEL //  			ar.Read (&tempRoot->InChild , sizeof(tempRoot->InChild)) ;
//DEL // 		}
//DEL //   		
//DEL // 	}
//DEL   
//DEL   	UnBSTSerialize(tempRoot->leftChild  ,ar );
//DEL   	UnBSTSerialize(tempRoot->rightChild ,ar);
//DEL   	
//DEL   }


  void BSTSerialize(BinarySearchTreeNode *tempRoot)
  {
  	//Serialize(CArchive& ar) 
  	
  	if(NULL==tempRoot)
  		return ;
  
	
	if(tempRoot)
	{
		CBox* p1 = GetBoxToNode(tempRoot);
		
		ml->AddTail(p1);
		
		
		if(tempRoot->InChild)
		{
			CBox* p1 = GetBoxToNode(tempRoot->InChild);			
			ml->AddTail(p1);
		}
	}
  	
  	BSTSerialize(tempRoot->leftChild  );
  	BSTSerialize(tempRoot->rightChild );
  	
  }


//**********************************************************
void PreOrderBST(BinarySearchTreeNode* tempRoot, int i)
{
	if(NULL==tempRoot)
		return ;
	//查询i值，再执行对应的分支函数
	switch (i)
	{
		case 0:break;
		case 1:break;
		case 2:break;
		case 3:break;
		case 4: UpdateLR(tempRoot);break;


		//case 100: BSTSerialize(tempRoot);
		default: break;
	}
	PreOrderBST(tempRoot->leftChild,   i);
	PreOrderBST(tempRoot->rightChild,  i);
}


//DEL void  Test(BinarySearchTreeNode* tempRoot){AfxMessageBox("ok");}


	// Generated message map functions
	//{{AFX_MSG(BinarySearchTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(BinarySearchTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINARYSEARCHTREE_H__76835A36_2704_4FCF_954A_18C604C19FF1__INCLUDED_)
