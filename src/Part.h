#ifndef PART_H
#define PART_H

#pragma once
#include "Shape.h"

class Part : public Shape
{
public:
    Part();
    ~Part();

private:
    float m_unitprice;
    float m_price;


};

#endif