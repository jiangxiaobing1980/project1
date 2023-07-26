#include <iostream>
#include "component.h"
//#include "material.h"

#include <map>
#include <string>
int main()
{
	/*

    Composite root("root");
    Composite treeNode1("treeNode1");
    Composite treeNode2("treeNode2");
    Composite treeNode3("treeNode3");
    Composite treeNode4("treeNode4");
    Leaf leaf1("left1");
    Leaf leaf2("left2");
    
    root.add(&treeNode1);
    treeNode1.add(&treeNode2);
    treeNode2.add(&leaf1);
    
    root.add(&treeNode3);
    treeNode3.add(&treeNode4);
    treeNode4.add(&leaf2);
    
    root.process();
    //process(leaf2);
    //process(treeNode3);
  */  
 /*      
    Leaf Alum1("ÂÁ²ÄPM0801A");    
    
    Leaf Alum2("ÂÁ²ÄPM0801B");      
    
    Composite Alum3("¸´ºÏPM0801");
    Alum3.add(&Alum1);    
    Alum3.add(&Alum2);    
    Alum3.process();
 */   
    Part  PA661("	PA66	C24"); 
    Part  PA662("	PA66	C24"); 
    Part  Alum1("	ÂÁ²Ä	PM0801A");  
    Part  Alum2("	ÂÁ²Ä	PM0801B");  

	map<string, double> m;
	
	m["½ðÊô»Òµ¥¼Û"] = 29.5;
	cout << m["½ðÊô»Òµ¥¼Û"] << endl;
	

    Group Alum3("¸´ºÏÂÁ²Ä-PM0801");
    Alum3.add(&Alum1);    
    Alum3.add(&Alum2); 
	Alum3.add(&PA661);  
	Alum3.add(&PA662);   
    
    
    Alum3.process();
  
}


