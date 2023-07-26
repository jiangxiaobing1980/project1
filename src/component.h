#ifndef COMPONENT_H
#define COMPONENT_H

#endif


#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;


//�ӿ� 
class Component
{
public:
    virtual void process() = 0;
    virtual ~Component(){}
};

//���ڵ�
class Composite : public Component{
//public:

    
    
    list<Component*> elements;
    list<Component*>::iterator e; 
    
   	protected:   
    string name;  
    
public:
    Composite(const string & s) : name(s) {}
    
    void add(Component* element) {
        elements.push_back(element);
    }
    void remove(Component* element){
        elements.remove(element);
    }
    
    void process(){
        
        //1. process current node
        cout << name << endl;
        
        //2. process leaf nodes
        
      
         
		for(e = elements.begin();	e!=elements.end();	e++){  
        //for (Component* e : elements)
            (*e)->process(); //��̬����
           
            
            
		}
         
    }
};

//Ҷ�ӽڵ�
class Leaf : public Component{

 	protected:   
 	//public:
    string name;
public:
    Leaf(const string & s) : name(s) {};
            
    void process(){
        //process current node
        cout << name << endl;
    }
};


void Invoke(Component & c){
    //...
    c.process();
    //...
}


class Part  : public Leaf{
public:
	Part(const string & s) : Leaf (s) {};
	virtual  ~Part(){};
public:	
   	double m_Length ;
	double m_Width ;
	double m_Height ;
	double m_Weight ;
	double m_Price ;	
	double m_Amount;
};


class Group  : public Composite{
public:
	Group(const string & s) : Composite (s) {};
	virtual  ~Group(){};
public:	
   	double m_Length ;
	double m_Width ;
	double m_Height ;
	double m_Weight ;
	double m_Price ;	
	double m_Amount;
};



/*
�������
1.����ָ�� 
2.��������
3.����KG���ص���
4.�˳߾���

���
1.���س���
2.���ص���
3.�����ܳ����
*/
//class Group;
class EPDM
{
public:
	EPDM();
	virtual ~EPDM();
public:
private:
	double exitdistance;
	double m_weightmetre;
	double m_weightprice;

	bool bprices;
	double m_price;

public:
	EPDM( Group* pgroup , double weight, double weightprice) :exitdistance(distance) ,
	m_weightmetre(weight), m_weightprice(weightprice),bprices(0) {};

	double getLenght(){return (pgroup->m_Weight+ pgroup->m_Height) *2.0-exitdistance*8.0 ; };	//pgroup(��+��)*2-exitdistance*8.0

	double getmetreprice() {return m_weightmetre * m_weightprice; };

	void setprice(double price) {m_price =  price; bprices =1 ; };
	double getprice() {
		if(bprices)
			return getLenght() *  getmetreprice();
		else m_price; 
	};

private:
	double getWeight(){return getLenght() * m_weightmetre;} ;


};
