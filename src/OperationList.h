#if !defined(AFX_OPERATIONLIST_H__F78C807D_713F_433A_941D_A45FF60603D3__INCLUDED_)
#define AFX_OPERATIONLIST_H__F78C807D_713F_433A_941D_A45FF60603D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxtempl.h>
typedef CTypedPtrList<CObList , CObject*> CObjectList;

//#include "Box.h"
#include "Dimension.h"


/////////////////////////////////////////////////////////////////////////////
// COperationList command target

//ͨ�ö����������
class COperationList : public CCmdTarget
{
	DECLARE_SERIAL(COperationList)

	COperationList();           // protected constructor used by dynamic creation
	virtual ~COperationList();
// Attributes
public:

// Operations
public:

	CObjectList m_List;



// 	int GetCount()
// 	{
// 		return pSeriesList->GetCount() ;
// 	}
// 
// 	void AddTail(CSeries* NewElem)	
// 	{
// 
// 		pSeriesList->AddTail(NewElem);
// 	}

void OnDraw(CObject* Obj , CDC* pDC, CPoint pt)
{
	CDimension* p = (CDimension*)Obj;
	p->OnDraw(pDC);
		
}

void SelectedTest(CObject* Obj , CDC* pDC, CPoint pt)
{
	CDimension* p = (CDimension*)Obj;
	p->IsSelected(pt);;
	
}

//���������ڵ�Ԫ��
void Traver( CDC* pDC, CPoint pt , int n)
{
	if(!m_List.IsEmpty())
	{
		POSITION pos = COperationList::m_List.GetHeadPosition() ;
		while(pos != NULL)
		{
			CObject *p = (CObject*)COperationList::m_List.GetNext(pos);						
			
			switch(n)
			{
				case 0: OnDraw		(p, pDC, pt);	break;
				case 1: SelectedTest(p, pDC, pt);	break;

			default: break;
			}				
		}		
	}
}

 
	/*
	//���������ڵ��ַ��������еĵ�n��Ԫ�ص�ֵ	
	double  GetValToArr(CObjectList* l ,CString s , int col)
	{	
		double  a = -99;
	
			POSITION pos = l->GetHeadPosition() ;
			while(pos != NULL)
			{
				CStringArray *p = (CStringArray *)l->GetNext(pos);

				if(p->GetSize() <= col)
				{
					AfxMessageBox("�ַ������鳤�Ȳ���...");
					return a;
				}
				else
				{
					if(s == p->GetAt(0) )
					{
						a = atof(p->GetAt(col));
						break;
					}
				}
			}
	

		return a;
	
} 
*/
/*
	//�����ڵ�����Ԫ��ѡ������Ϊ��	
	BOOL SetUnSeleced(CObjectList* l)
	{	
		if(!l || l->IsEmpty())
			return FALSE;
		
		POSITION pos = l->GetHeadPosition() ;
		while(pos != NULL)
		{
			CBox *p = (CBox *)l->GetNext(pos);
			p->UnSeleced();			
		}	
		
		return TRUE;
		
} 

*/
/*
	//��β��ͷ����ȡ��һ��ѡ�е�Ԫ��
	CBox* GetSeletedBox(CObjectList* l , CPoint pt)
	{
		CBox *p = NULL ;

		if(!l || l->IsEmpty())
			return FALSE;
		
		
		POSITION pos = l->GetTailPosition() ;
		while(pos != NULL)
		{
			p = (CBox *)l->GetPrev(pos);
			if(p->GetBox().PtInRect(pt))
				return p ;
			else
				p =NULL;		
		}	

			return p ;
		
	}



	//�����ӽڵ㷵�ظ��׽ڵ�
	CBox* GetParentsBox(CObjectList* pBoxList , CBox* ChildBox)
	{
		
		// Dump the list elements to the debug window.
		POSITION pos = pBoxList->GetHeadPosition();
		for (int i = 0; i <pBoxList->GetCount(); i++)
		{
			CBox* pa = (CBox*)pBoxList->GetNext(pos);

			if(ChildBox->m_Parents == pa->m_Pos)
				return pa ;
		}

		return NULL;
	}

	//���ؽڵ�����ӽڵ�
	CBox* GetLeftChildBox(CObjectList* pBoxList , CBox* ParentsBox)
	{
		
		CRect rtParentsBox = ParentsBox->GetBox();
		int ParentsBoxleft = rtParentsBox.left;

		// Dump the list elements to the debug window.
		POSITION pos = pBoxList->GetHeadPosition();
		for (int i = 0; i <pBoxList->GetCount(); i++)
		{
			CBox* pa = (CBox*)pBoxList->GetNext(pos);
			CRect rtpa = pa->GetBox();
			int paleft = rtpa.left;

			if(ParentsBox->m_Pos == pa->m_Parents 
				&& paleft == ParentsBoxleft)
				return pa ;
		}
		
		return NULL;
	}

	//���ؽڵ�����ӽڵ�
	CBox* GetRightChildBox(CObjectList* pBoxList ,CBox* ParentsBox)
	{
		
		CRect rtParentsBox = ParentsBox->GetBox();
		int ParentsBoxright = rtParentsBox.right;
		
		// Dump the list elements to the debug window.
		POSITION pos = pBoxList->GetHeadPosition();
		for (int i = 0; i <pBoxList->GetCount(); i++)
		{
			CBox* pa = (CBox*)pBoxList->GetNext(pos);
			CRect rtpa = pa->GetBox();
			int paright = rtpa.right;
			
			if(ParentsBox->m_Pos == pa->m_Parents 
				&& paright == ParentsBoxright)
				return pa ;
		}
		
		return NULL;
	}

	//���ؽڵ�������ӽڵ�
	CBox* GetPostChildBox(CObjectList* pBoxList ,CBox* ParentsBox)
	{
		
		CRect rtParentsBox = ParentsBox->GetBox();
		CPoint ParentsBoxCenterPoint = rtParentsBox.CenterPoint();
		
		
		// Dump the list elements to the debug window.
		POSITION pos = pBoxList->GetHeadPosition();
		for (int i = 0; i <pBoxList->GetCount(); i++)
		{
			CBox* pa = (CBox*)pBoxList->GetNext(pos);
			CRect rtpa = pa->GetBox();			
			CPoint paBoxCenterPoint = rtpa.CenterPoint();
			
			if(ParentsBox->m_Pos == pa->m_Parents 
				&& paBoxCenterPoint == ParentsBoxCenterPoint)
				return pa ;
		}
		
		return NULL;
	}

	//�������нڵ�
	BOOL UpdataList(CObjectList* pBoxList )
	{
		
		
		if (pBoxList->IsEmpty()) return FALSE ;
		
		
		POSITION pos = pBoxList->GetHeadPosition();
		for (int i = 0; i <pBoxList->GetCount(); i++)
		{
			CBox* pa = (CBox*)pBoxList->GetNext(pos);
			CRect rtpa = pa->GetBox();
	
			
			if(pa->m_Pos != 0	&& pa->m_Pos != -1)
			{
				//��ͷ�ڵ� && ��ǰ�ڵ����ӽڵ�
				//�ҵ���ǰ�ڵ�������������ӽڵ�������ұ߿�����±߿�
				

				//CRect rtChildBox = ChildBox->GetBox();

				CBox* LeftBox	= GetLeftChildBox(pBoxList,pa);
				CBox* RightBox	= GetRightChildBox(pBoxList,pa);
				CBox* PostBox	= GetPostChildBox(pBoxList,pa);

				//int ParentsBoxleft = rtParentsBox.left;

			}

			
		}
		
		return TRUE;
	}


	
	BOOL RemoveAll(CObList* pList)
	{
		if(!pList || pList->IsEmpty())
		{
			return FALSE;
		}
		else
		{
			
			while (!pList->IsEmpty())
			{
				delete pList->GetHead();
				pList->RemoveHead();
			}
		}

		return TRUE ;
	}


//DEL 	double  NameToValue( CObjectList* pSeriesList, CString name)
//DEL 	{
//DEL 		
//DEL 		double temp = -999999;
//DEL 		// Dump the list elements to the debug window.
//DEL 		POSITION pos = pSeriesList->GetHeadPosition();
//DEL 		for (int i = 0; i < pSeriesList->GetCount(); i++)
//DEL 		{			
//DEL 			//ȡ������
//DEL 			POSITION pos1 = pSeriesList->FindIndex(i);					
//DEL 			CSeries* d1 = (CSeries* )pSeriesList->GetAt(pos1);			
//DEL 			
//DEL 			if(name == d1->Name)
//DEL 			{		
//DEL 				temp = d1->Val ;
//DEL 				break;
//DEL 			}
//DEL 		}
//DEL 		return temp ;
//DEL 		
//DEL 	}

	
//DEL double  NameToUnitPrice( CObjectList* pSeriesList, CString name)
//DEL 	{
//DEL 		
//DEL 		double temp = -999999;
//DEL 		// Dump the list elements to the debug window.
//DEL 		POSITION pos = pSeriesList->GetHeadPosition();
//DEL 		for (int i = 0; i < pSeriesList->GetCount(); i++)
//DEL 		{			
//DEL 			//ȡ������
//DEL 			POSITION pos1 = pSeriesList->FindIndex(i);					
//DEL 			CSeries* d1 = (CSeries* )pSeriesList->GetAt(pos1);			
//DEL 			
//DEL 			if(name == d1->Name)
//DEL 			{		
//DEL 				temp = d1->UnitPrice ;
//DEL 				break;
//DEL 			}
//DEL 		}
//DEL 		return temp ;
//DEL 		
//DEL 	}

	int  GetCount ( CObjectList* pSeriesList)
	{
		
	
		return pSeriesList->GetCount() ;
		
	}

	
//DEL 		double  NameToWeightMeter( CObjectList* pSeriesList, CString name)
//DEL 	{
//DEL 		
//DEL 		double temp = -999999;
//DEL 		// Dump the list elements to the debug window.
//DEL 		POSITION pos = pSeriesList->GetHeadPosition();
//DEL 		for (int i = 0; i < pSeriesList->GetCount(); i++)
//DEL 		{			
//DEL 			//ȡ������
//DEL 			POSITION pos1 = pSeriesList->FindIndex(i);					
//DEL 			CSeries* d1 = (CSeries* )pSeriesList->GetAt(pos1);			
//DEL 			
//DEL 			if(name == d1->Name)
//DEL 			{		
//DEL 				temp = d1->WeightMeter ;
//DEL 				break;
//DEL 			}
//DEL 		}
//DEL 		return temp ;
//DEL 		
//DEL 	}

		CRect GetFrameRect(CObjectList* tempList)
		{
			CRect temp = NULL;
			// Dump the list elements to the debug window.
					
				CBox* pb  = (CBox* )tempList->GetAt(tempList->FindIndex(0));
				temp = pb->GetBox();
			
			return temp ;

		}
*/
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperationList)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(COperationList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATIONLIST_H__F78C807D_713F_433A_941D_A45FF60603D3__INCLUDED_)
