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
#include <windef.h> 	//POINT ͷ�ļ� 
#include <string>
#include <list>

using namespace std ; 


class public_item
{
	public:
	
	string name;
	float val;
	
};

//����һ��list������ʵ��
typedef list<public_item> LISTBom;


float GetValToName(LISTBom *l ,string s);

//���� 
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

//�߲� 
class linetype  : public  bomitem
{  
    public:  
    float   GetWeight();
 	  
};


//��֧���ɷ��߲� 
class LineType  : public CBox
{  

public:
	LineType();
	virtual ~LineType(); 
	
public:
    void  SetWeight();
    float GetWeight();
 	  
};

//���ʽ�����߲ġ����紩���Ͳ�
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


//���������Ͳ� 
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

//��� 
class boardtype  : public  bomitem
{    
	public:
	float GetArea() ;
	float GetWidth() ;
    float GetHeight() ;	
	float GetPerimeter() ;
};



//�߿� 
class line_frametype  : public  bomitem
{  
 	public: 
    line_frametype();
    virtual ~line_frametype();    

	  float GetWeight();
	  float GetPrice(LISTBom *l);

    public: 
	linetype *line[10];
	boardtype *board; //���� �� ����	

	
	bomitem *hardware[50];	//����� 
	bomitem *SteelAnglePlane[16];	//����� 
	bomitem *AlumAngle[16];	//�����
	line_frametype *epdm[40];	//EPDM�������
	line_frametype *pvc[4];
	
	
	//bool Isjoint_45 ;


 	  
};


//�߿� 
class LineFrame  : public CBox
{  
public: 
    LineFrame();
    virtual ~LineFrame(); 	

	//LineFrame(CObjectList *);		//����ϵ���б�Ĺ��캯��	
	
public:
	CObjectList *Line_Item_List;		//��ɿ���߲��б�;
	
public:
	//float GetWidth();
	//float GetWeight();
	//float GetPrice(LISTBom *l);
	/*
	linetype *line[10];
	boardtype *board; //���� �� ����	
	
	
	bomitem *hardware[50];	//����� 
	bomitem *SteelAnglePlane[16];	//����� 
	bomitem *AlumAngle[16];	//�����
	lineframe *epdm[40];	//EPDM�������
	lineframe *pvc[4];
	
	
	//bool Isjoint_45 ;
	*/
	
 	  
};

//��ġ����粣����ɴ��
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


//��� 
class hardwaretype  : public  bomitem
{  
    public:  
 	  
};


//ƴ��������� 
class alum_frametype  : public  line_frametype
{  
    public: 
    alum_frametype();
    virtual ~alum_frametype();
    
    float GetWeight();
	float GetPrice(LISTBom *l);
    
    public: 
   
	alum_complex *alumcom[10];  //����һ�������Ͳ�ָ������
	
 	  
};

//���� 
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
	
	line_frametype *fixframe[10];	//�̶��� 
	
	alum_frametype *vent_gls[10];	//�������� 
	
	line_frametype *vent_net[10];	//����ɴ��         
  	  
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
 
	CObjectList *FixWindows;	//�̶��� 

	CObjectList *vent_gls , *vent_net;//�������� //����ɴ��
	

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
