#ifndef VENT_H
#define VENT_H

#pragma once
#include "Shape.h"
class Vent : public Shape
{
public:
    Vent();
    ~Vent();

public:
    void setbackset(int dim){
        m_backset = dim ;
        //m_lenth
        };
    int  getbackset(){return m_backset;};
private:
    int m_backset;


};

#endif