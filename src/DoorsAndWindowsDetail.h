#if !defined(AFX_DOORSANDWINDOWSDETAIL_H__8777FA6F_DF25_4CF2_9DFD_AD236EAF5AC0__INCLUDED_)
#define AFX_DOORSANDWINDOWSDETAIL_H__8777FA6F_DF25_4CF2_9DFD_AD236EAF5AC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoorsAndWindowsDetail.h : header file
//
#include "Box.h"

//#include <afxtempl.h>
//typedef CTypedPtrList<CPtrList , CObject*> CObjectList;

/////////////////////////////////////////////////////////////////////////////
#include <windef.h> 	//POINT 头文件 
#include <string>
#include <list>

using namespace std ; 


class public_item
{
	public:
	
	string name;
	float val;
	
};

//创建一个list容器的实例
typedef list<public_item> LISTBom;


float GetValToName(LISTBom *l ,string s);

//基类 
class bomitem  
{  
	public:
	bomitem();
	virtual ~bomitem(); 
	
    public:  
    
    int id ;
 	string name;
 	string type ; 
	string parenstype ;  
    float length ;
	float width ;
	float height ;
	float weight ;
	float price ;
	POINT Insert_pt;

	  
};

//线材 
class linetype  : public  bomitem
{  
    public:  
    float   GetWeight();
 	  
};


//单支不可分线材 
class LineType  : public CBox
{  

public:
	LineType();
	virtual ~LineType(); 
	
public:
    void  SetWeight();
    float GetWeight();
 	  
};

//组合式复合线材。例如穿条型材
class Composite_LineType : public  LineType
{  
public:
	Composite_LineType();
	virtual ~Composite_LineType(); 
	
	float GetWeight();
	float GetPrice();
public:  
    
    //linetype *plinetype[16];
    
	
};


//穿条复合型材 
class alum_complex : public  bomitem
{  
	public:
	alum_complex();
	virtual ~alum_complex(); 
	
	float GetWeight();
	float GetPrice(LISTBom *l);
    public:  
    
    linetype *plinetype[16];
    
  	  
};

//板材 
class boardtype  : public  bomitem
{    
	public:
	float GetArea() ;
	float GetWidth() ;
    float GetHeight() ;	
	float GetPerimeter() ;
};



//线框 
class line_frametype  : public  bomitem
{  
 	public: 
    line_frametype();
    virtual ~line_frametype();    

	  float GetWeight();
	  float GetPrice(LISTBom *l);

    public: 
	linetype *line[10];
	boardtype *board; //玻璃 或 钢网	

	
	bomitem *hardware[50];	//配件包 
	bomitem *SteelAnglePlane[16];	//配件包 
	bomitem *AlumAngle[16];	//配件包
	line_frametype *epdm[40];	//EPDM胶条组框
	line_frametype *pvc[4];
	
	
	//bool Isjoint_45 ;


 	  
};


//线框 
class LineFrame  : public CBox
{  
public: 
    LineFrame();
    virtual ~LineFrame(); 	

	//LineFrame(CObjectList *);		//输入系列列表的构造函数	
	
public:
	CObjectList *Line_Item_List;		//组成框的线材列表;
	
public:
	//float GetWidth();
	//float GetWeight();
	//float GetPrice(LISTBom *l);
	/*
	linetype *line[10];
	boardtype *board; //玻璃 或 钢网	
	
	
	bomitem *hardware[50];	//配件包 
	bomitem *SteelAnglePlane[16];	//配件包 
	bomitem *AlumAngle[16];	//配件包
	lineframe *epdm[40];	//EPDM胶条组框
	lineframe *pvc[4];
	
	
	//bool Isjoint_45 ;
	*/
	
 	  
};

//板材。例如玻璃、纱网
class BoardType  : public  LineFrame
{ 
public:
	BoardType();
	virtual ~BoardType();
	
public:
	float GetArea() ;
	float GetWidth() ;
    float GetHeight() ;	
	float GetPerimeter() ;
};


//五金 
class hardwaretype  : public  bomitem
{  
    public:  
 	  
};


//拼角组框类型 
class alum_frametype  : public  line_frametype
{  
    public: 
    alum_frametype();
    virtual ~alum_frametype();
    
    float GetWeight();
	float GetPrice(LISTBom *l);
    
    public: 
   
	alum_complex *alumcom[10];  //定义一个穿条型材指针数组
	
 	  
};

//整窗 
class window : public  bomitem
{  	
    public:  	
	window();
	virtual ~window();
	
	public:
	
	BOOL Addframe(float w , float h , LISTBom *s, LISTBom *p);
	
	public:
	BOOL Isempty; 
	
	
	public: 
	alum_frametype  *frame;		
	
	alum_complex *vpost[10] ;
	alum_complex *hpost[10] ;
	
	line_frametype *fixframe[10];	//固定窗 
	
	alum_frametype *vent_gls[10];	//开启玻扇 
	
	line_frametype *vent_net[10];	//开启纱扇         
  	  
};



class GroupBox : public CBox
{


};




// DoorsAndWindowsDetail command target
class DoorsAndWindowsDetail : public CBox //CCmdTarget
{
	DECLARE_DYNCREATE(DoorsAndWindowsDetail)

	DoorsAndWindowsDetail();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DoorsAndWindowsDetail)
	//}}AFX_VIRTUAL

// Implementation

	/*
public: 
	CObjectList *WindowsFrame;
	
	CObjectList *vpost , *hpost;
 
	CObjectList *FixWindows;	//固定窗 

	CObjectList *vent_gls , *vent_net;//开启玻扇 //开启纱扇
	

public:
	
	BOOL SetFrame(float w , float h );
	BOOL Addvpost(float h );
	BOOL Addhpost(float w );
	BOOL Addfixwindows(float w , float h );
	BOOL Addvent_gls(float w , float h );
	BOOL Addvent_net(float w , float h );

*/





	/*	
public:
	BOOL Isempty; 
	
	
	
	
	alum_complex *vpost[10] ;
	alum_complex *hpost[10] ;
	
	line_frametype *fixframe[10];	
	
	alum_frametype *vent_gls[10];	
	
	line_frametype *vent_net[10];	     


*/


	
protected:
	virtual ~DoorsAndWindowsDetail();

	// Generated message map functions
	//{{AFX_MSG(DoorsAndWindowsDetail)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOORSANDWINDOWSDETAIL_H__8777FA6F_DF25_4CF2_9DFD_AD236EAF5AC0__INCLUDED_)
