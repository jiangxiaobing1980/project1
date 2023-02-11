#ifndef ALUMWINDOW_H
#define ALUMWINDOW_H

#include <string.h>
#include <vector>
#include "Shape.h"
#include "OutFrame.h"
#include "VirtualHole.h"
#include "Vent.h"

#pragma once
using namespace std;

class AlumWindow : public Shape
{
public:
    AlumWindow();
    ~AlumWindow();
    AlumWindow(string name):m_name(name){};
public:
     string  getname(){return m_name;};
private:
    string m_name;
    OutFrame Of;
    vector<VirtualHole*> vh;
    vector<Vent*> vc;


};

#endif