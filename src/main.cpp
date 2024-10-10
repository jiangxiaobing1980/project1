#include <iostream>
#include "AlumWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	AlumWindow a("C500x1800") ;
	
	a.setwidth(1500);
	a.sethigh (1800);
	
	cout << "windows name : " << a.getname() << "  --width: " << a.getwidth() << "  --high: " << a.gethigh()  << endl;

	cout << "windows size: " << "  --width: " << a.getwidth() << "  --high: " << a.gethigh()  << endl;

}
