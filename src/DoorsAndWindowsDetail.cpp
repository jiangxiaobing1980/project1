// DoorsAndWindowsDetail.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "DoorsAndWindowsDetail.h"

#include <iostream>
//#include "windoor_type.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DoorsAndWindowsDetail

IMPLEMENT_DYNCREATE(DoorsAndWindowsDetail, CCmdTarget)

DoorsAndWindowsDetail::DoorsAndWindowsDetail()
{
}

DoorsAndWindowsDetail::~DoorsAndWindowsDetail()
{
}




float GetValToName(LISTBom *l ,string s)
{	
	float a = 0;
    LISTBom::iterator i; 
     
    for (i = (*l).begin(); i != (*l).end(); ++i)
      {    
    	if(s == i->name)
    	{
	    	a = i->val ;
	    }		
    }	
	return a; 
} 

bomitem :: bomitem()
{
	id = 0 ;
 	name =	"";
 	type =	""; 
	parenstype=	"";  
    length 	=0;
	width 	=0;
	height 	=0;
	weight 	=0;
	price 	=0;
	memset (&Insert_pt , 0 ,sizeof(POINT));

}

bomitem :: ~bomitem()
{
}


window::window()
{
	Isempty = true ;
		//Ϊ�������ռ� 
		alum_frametype *palum_frametype = new alum_frametype ;	
		frame =  palum_frametype;
		
				
		//Ϊ���������ռ� 
		alum_complex *pvpost = new alum_complex[10] ;			
		
		//����ָ���ռ� 
		for(int i = 0; i< 10 ;i++)
		{
			vpost[i] = pvpost + i;
		}
		
		//Ϊ���������ռ� 
		alum_complex *phpost = new alum_complex[10] ;			
		
		//����ָ���ռ� 
		for( i = 0; i< 10 ;i++)
		{
			hpost[i] = phpost + i;
		}
		///////////
		
		
		//Ϊ�̶�ѹ�߿�����ڴ� 
		alum_frametype *pfixframe = new alum_frametype[10] ;
		
		//����ָ���ռ� 
		for( i = 0; i< 10 ;i++)
		{
			fixframe[i] = pfixframe + i;
			
		}
	
	
}
    
window::~window()
{
	/*
	delete frame ; 
   delete [] vpost ; 
    delete [] hpost ;
    delete [] fixframe ;
   */ 
}

BOOL window::Addframe(float w , float h ,LISTBom *s ,LISTBom *p)
{
			
	this->frame->width = w;
	this->frame->height = h;
	this->frame->type = "�������";

	//ָ�������4֧���������Ͳ�����	 
	this->frame->alumcom[0]->length = this->frame->width;	//1600
	this->frame->alumcom[1]->length = this->frame->width;	//1600
	this->frame->alumcom[2]->length = this->frame->height;	//1900
	this->frame->alumcom[3]->length = this->frame->height;	//1900
	for(int i = 0; i< 4 ;i++)
	{	 
		this->frame->alumcom[i]->type = "���������Ͳ�";
	}
	

	
	cout << "����: "<< "\t" << this->frame->width <<"\t"<< this->frame->height  << endl; 	
	
	//ѭ��ָ��4֧���򸴺��Ͳĵķֽ�����	 
	for( i = 0; i< 4 ;i++)
	{	 
		this->frame->alumcom[i]->plinetype[0]->type = "����";
		this->frame->alumcom[i]->plinetype[0]->weight = GetValToName(s ,"������������");
				
		this->frame->alumcom[i]->plinetype[1]->type = "������";
		this->frame->alumcom[i]->plinetype[1]->weight =  GetValToName(s ,"�������������");
		this->frame->alumcom[i]->plinetype[1]->price  =  GetValToName(s ,"�������������"); 
		
	}
	
	
	cout <<  endl;
	this->frame->GetWeight();
	this->frame->GetPrice(p);
	
	float a ;	
	for( i = 0; i< 4 ;i++)
	{	 
		this->frame->hardware[i]->type = "������������";
		this->frame->hardware[i]->width = 20 ; // GetValToName(s ,"��������");
		this->frame->hardware[i]->height = 15 ; // GetValToName(s ,"��������");	
		this->frame->hardware[i]->price  =  2.0  ; //GetValToName(s ,"���������뵥��"); 
		a += this->frame->hardware[i]->price ;
		
		
	}
	
	cout << "������������ "<< a<<" Ԫ"<< endl;
	
	for( i = 0; i< 50 ;i++)
	{	 
		if (this->frame->hardware[i]->type == "������������")
		a +=  this->frame->hardware[i]->width*2 + this->frame->hardware[i]->height ;	
		
		
	}
	
	cout << "������������ע������ "<< a<<" mm"<< endl;

	cout << "������������ע������ "<< a * 0.016 <<" Ԫ"<< endl;	
	
	cout << "������潺���� "<< 4 * 0.44 <<" Ԫ"<< endl;	

	cout <<endl;
	cout <<endl;
	
	this->Isempty = false ; 
	 
	return true ;
}


///////////////////////////////////////////////


///�߿� 
line_frametype:: line_frametype()
{	
		linetype *pline = new linetype[10] ;			
		
		//����ָ���ռ� 
		for(int i = 0; i< 10 ;i++)
		{
			line[i] = pline + i;			
		}
		
			
	
		boardtype *pboard = new boardtype;
		
		board = pboard;
		
		
		bomitem *phardware = new bomitem[50];
		for( i = 0; i< 50 ;i++)
		{
			hardware[i] = phardware + i ;
		}
}

line_frametype:: ~line_frametype()
{
	/*
	delete [] line ;		
	delete board ;
	delete [] hardware ;
	*/
} 

//��֧�߲����� 
float linetype:: GetWeight()
{
	if(this->weight != 0)
	cout <<"��֧�߲����أ� " << this->length <<"\t"<<this->weight * (this->length / 1000)<<" kg"<< endl ;
	
	return this->weight * (this->length / 1000); 
	
}

/////////////�����Ͳ��߿� ��ʼ�� 
alum_frametype:: alum_frametype()
{
		alum_complex *palumcom = new alum_complex[10] ;			
		
		//����ָ���ռ� 
		for(int i = 0; i< 10 ;i++)
		{
			alumcom[i] = palumcom + i;			
		}
	
}

alum_frametype:: ~alum_frametype()
{
		//delete [] alumcom ;	
} 


//�߲�������� 
float line_frametype:: GetWeight()
{		
		float a = 0 ;
	
		//ѭ���ۼӸ��߲ĵ����� 
		for(int i = 0; i< 10 ;i++)
		{		
			a += line[i]->GetWeight() ;
		}

	cout << endl ;	
	cout <<"�߲���������� "<< a<<  " kg" <<endl ;
	
	return a ;	
}



//���������Ͳ�������� 
float alum_frametype:: GetWeight()
{			
		float a = 0 ;
	
		//ѭ���ۼӸ��߲ĵ����� 
		for(int i = 0; i< 10 ;i++)
		{		
			a += alumcom[i]->GetWeight() ;
		}

	cout << endl ;	
	if (this->type == "�������")
	{
		cout <<"������������� "<< a<<  " kg" <<endl ;	
	}	

	return a ;
	
}


	
alum_complex:: alum_complex()
{
		linetype *pline = new linetype[10] ;			
		
		//����ָ���ռ� 
		for(int i = 0; i< 10 ;i++)
		{
			plinetype[i] = pline + i;		
		}
	
}

alum_complex:: ~alum_complex()
{
		//delete [] plinetype ;
} 

//��֧�����Ͳ����� 
float alum_complex:: GetWeight()
{
	float a = 0 ;
	
		//ѭ���ۼӸ��߲ĵ����� 
		for(int i = 0; i< 10 ;i++)
		{
			a += plinetype[i]->weight * (this->length / 1000);
		}
	
			if(a != 0)
			cout <<"��֧���������Ͳ����أ� " << this->length <<"\t"<< a << " kg"<< endl ;
	
	return a ;
	
}
//��֧�����Ͳļ۸� 
float alum_complex:: GetPrice(LISTBom *l)
{
	float b = 0;
	
		//ѭ���ۼӸ��߲ĵ����� 
		for(int i = 0; i< 10 ;i++)
		{
			if(plinetype[i]->type == "����")
			{				
				b += plinetype[i]->weight* (this->length / 1000) *  GetValToName(l , "�Ͳĵ���") ;				
			}
			
			if(plinetype[i]->type == "������")
			{			
				b +=  (this->length / 1000)* plinetype[i]->price *  GetValToName(l , "���������");				
			}			
		}
		
		if(b != 0)
		cout <<"��֧���������Ͳļ۸� " << "\t\t"<< b << " Ԫ"<< endl ;

	return b ;
	
}


//���������Ͳ����۸� 
float alum_frametype:: GetPrice(LISTBom *l)
{
	float a = 0 ;
	
		//ѭ���ۼӸ��߲ĵ�����  
		for(int i = 0; i< 10 ;i++)
		{
			a += alumcom[i]->GetPrice(l);
		}
	
	cout <<endl;
			if(a != 0)
			cout <<"���������Ͳ����۸� " <<  a << " Ԫ"<< endl ;
	
	return a ;
	
}



float boardtype  :: GetWidth()
{  
	string str = "����";  
	if (this->type == str)
	cout <<"��������: " <<endl ;
	else 
	cout <<"����" <<endl ;
	
	
	cout <<"��� �� " << this->width << " mm"<< endl ;
 	return this->width;  
};


float boardtype  :: GetHeight()
{  
	cout <<"�߶� �� " <<  this ->height << " mm"<< endl ;
 	 return this ->height ;  
};

float boardtype  :: GetArea()
{ 
	cout <<"��� �� " << ((this->width/1000) * (this ->height/1000)) << " m2"<< endl ;
	return ((this->width/1000) * (this ->height/1000));  
};


float boardtype  :: GetPerimeter()
{  
	cout <<"�ܳ� �� " << (this->width + this ->height) *2 << " mm"<< endl ;
 	 return (this->width + this ->height) *2 ;  
};



















BEGIN_MESSAGE_MAP(DoorsAndWindowsDetail, CCmdTarget)
	//{{AFX_MSG_MAP(DoorsAndWindowsDetail)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DoorsAndWindowsDetail message handlers
