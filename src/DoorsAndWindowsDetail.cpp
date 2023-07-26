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
		//为窗框分配空间 
		alum_frametype *palum_frametype = new alum_frametype ;	
		frame =  palum_frametype;
		
				
		//为竖中梃分配空间 
		alum_complex *pvpost = new alum_complex[10] ;			
		
		//分配指定空间 
		for(int i = 0; i< 10 ;i++)
		{
			vpost[i] = pvpost + i;
		}
		
		//为横中梃分配空间 
		alum_complex *phpost = new alum_complex[10] ;			
		
		//分配指定空间 
		for( i = 0; i< 10 ;i++)
		{
			hpost[i] = phpost + i;
		}
		///////////
		
		
		//为固定压线框分配内存 
		alum_frametype *pfixframe = new alum_frametype[10] ;
		
		//分配指定空间 
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
	this->frame->type = "窗框组框";

	//指定窗框的4支穿条复合型材属性	 
	this->frame->alumcom[0]->length = this->frame->width;	//1600
	this->frame->alumcom[1]->length = this->frame->width;	//1600
	this->frame->alumcom[2]->length = this->frame->height;	//1900
	this->frame->alumcom[3]->length = this->frame->height;	//1900
	for(int i = 0; i< 4 ;i++)
	{	 
		this->frame->alumcom[i]->type = "穿条复合型材";
	}
	

	
	cout << "窗型: "<< "\t" << this->frame->width <<"\t"<< this->frame->height  << endl; 	
	
	//循环指定4支窗框复合型材的分解属性	 
	for( i = 0; i< 4 ;i++)
	{	 
		this->frame->alumcom[i]->plinetype[0]->type = "铝材";
		this->frame->alumcom[i]->plinetype[0]->weight = GetValToName(s ,"窗框铝材米重");
				
		this->frame->alumcom[i]->plinetype[1]->type = "隔热条";
		this->frame->alumcom[i]->plinetype[1]->weight =  GetValToName(s ,"窗框隔热条米重");
		this->frame->alumcom[i]->plinetype[1]->price  =  GetValToName(s ,"窗框隔热条单价"); 
		
	}
	
	
	cout <<  endl;
	this->frame->GetWeight();
	this->frame->GetPrice(p);
	
	float a ;	
	for( i = 0; i< 4 ;i++)
	{	 
		this->frame->hardware[i]->type = "窗框内铝角码";
		this->frame->hardware[i]->width = 20 ; // GetValToName(s ,"窗框角码宽");
		this->frame->hardware[i]->height = 15 ; // GetValToName(s ,"窗框角码高");	
		this->frame->hardware[i]->price  =  2.0  ; //GetValToName(s ,"窗框铝角码单价"); 
		a += this->frame->hardware[i]->price ;
		
		
	}
	
	cout << "窗框内铝角码 "<< a<<" 元"<< endl;
	
	for( i = 0; i< 50 ;i++)
	{	 
		if (this->frame->hardware[i]->type == "窗框内铝角码")
		a +=  this->frame->hardware[i]->width*2 + this->frame->hardware[i]->height ;	
		
		
	}
	
	cout << "窗框内铝角码注胶长度 "<< a<<" mm"<< endl;

	cout << "窗框内铝角码注胶费用 "<< a * 0.016 <<" 元"<< endl;	
	
	cout << "窗框断面胶费用 "<< 4 * 0.44 <<" 元"<< endl;	

	cout <<endl;
	cout <<endl;
	
	this->Isempty = false ; 
	 
	return true ;
}


///////////////////////////////////////////////


///线框 
line_frametype:: line_frametype()
{	
		linetype *pline = new linetype[10] ;			
		
		//分配指定空间 
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

//单支线材重量 
float linetype:: GetWeight()
{
	if(this->weight != 0)
	cout <<"单支线材米重： " << this->length <<"\t"<<this->weight * (this->length / 1000)<<" kg"<< endl ;
	
	return this->weight * (this->length / 1000); 
	
}

/////////////复合型材线框 初始化 
alum_frametype:: alum_frametype()
{
		alum_complex *palumcom = new alum_complex[10] ;			
		
		//分配指定空间 
		for(int i = 0; i< 10 ;i++)
		{
			alumcom[i] = palumcom + i;			
		}
	
}

alum_frametype:: ~alum_frametype()
{
		//delete [] alumcom ;	
} 


//线材组框重量 
float line_frametype:: GetWeight()
{		
		float a = 0 ;
	
		//循环累加各线材的重量 
		for(int i = 0; i< 10 ;i++)
		{		
			a += line[i]->GetWeight() ;
		}

	cout << endl ;	
	cout <<"线材组框重量： "<< a<<  " kg" <<endl ;
	
	return a ;	
}



//穿条复合型材组框重量 
float alum_frametype:: GetWeight()
{			
		float a = 0 ;
	
		//循环累加各线材的重量 
		for(int i = 0; i< 10 ;i++)
		{		
			a += alumcom[i]->GetWeight() ;
		}

	cout << endl ;	
	if (this->type == "窗框组框")
	{
		cout <<"窗框组框重量： "<< a<<  " kg" <<endl ;	
	}	

	return a ;
	
}


	
alum_complex:: alum_complex()
{
		linetype *pline = new linetype[10] ;			
		
		//分配指定空间 
		for(int i = 0; i< 10 ;i++)
		{
			plinetype[i] = pline + i;		
		}
	
}

alum_complex:: ~alum_complex()
{
		//delete [] plinetype ;
} 

//单支复合型材重量 
float alum_complex:: GetWeight()
{
	float a = 0 ;
	
		//循环累加各线材的重量 
		for(int i = 0; i< 10 ;i++)
		{
			a += plinetype[i]->weight * (this->length / 1000);
		}
	
			if(a != 0)
			cout <<"单支穿条复合型材米重： " << this->length <<"\t"<< a << " kg"<< endl ;
	
	return a ;
	
}
//单支复合型材价格 
float alum_complex:: GetPrice(LISTBom *l)
{
	float b = 0;
	
		//循环累加各线材的重量 
		for(int i = 0; i< 10 ;i++)
		{
			if(plinetype[i]->type == "铝材")
			{				
				b += plinetype[i]->weight* (this->length / 1000) *  GetValToName(l , "型材单价") ;				
			}
			
			if(plinetype[i]->type == "隔热条")
			{			
				b +=  (this->length / 1000)* plinetype[i]->price *  GetValToName(l , "隔热条损耗");				
			}			
		}
		
		if(b != 0)
		cout <<"单支穿条复合型材价格： " << "\t\t"<< b << " 元"<< endl ;

	return b ;
	
}


//穿条复合型材组框价格 
float alum_frametype:: GetPrice(LISTBom *l)
{
	float a = 0 ;
	
		//循环累加各线材的重量  
		for(int i = 0; i< 10 ;i++)
		{
			a += alumcom[i]->GetPrice(l);
		}
	
	cout <<endl;
			if(a != 0)
			cout <<"穿条复合型材组框价格： " <<  a << " 元"<< endl ;
	
	return a ;
	
}



float boardtype  :: GetWidth()
{  
	string str = "玻璃";  
	if (this->type == str)
	cout <<"玻璃数据: " <<endl ;
	else 
	cout <<"钢网" <<endl ;
	
	
	cout <<"宽度 ： " << this->width << " mm"<< endl ;
 	return this->width;  
};


float boardtype  :: GetHeight()
{  
	cout <<"高度 ： " <<  this ->height << " mm"<< endl ;
 	 return this ->height ;  
};

float boardtype  :: GetArea()
{ 
	cout <<"面积 ： " << ((this->width/1000) * (this ->height/1000)) << " m2"<< endl ;
	return ((this->width/1000) * (this ->height/1000));  
};


float boardtype  :: GetPerimeter()
{  
	cout <<"周长 ： " << (this->width + this ->height) *2 << " mm"<< endl ;
 	 return (this->width + this ->height) *2 ;  
};



















BEGIN_MESSAGE_MAP(DoorsAndWindowsDetail, CCmdTarget)
	//{{AFX_MSG_MAP(DoorsAndWindowsDetail)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DoorsAndWindowsDetail message handlers
