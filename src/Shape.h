#ifndef SHAPE_H
#define SHAPE_H

#pragma once

class Shape
{
public:
    Shape();
    ~Shape();

public:
    void setlenth(int l){m_lenth = l ;};
    int  getlenth(){return m_lenth;};

    void setwidth(int w){m_width = w ;};
    int  getwidth(){return m_width;};

    void sethigh(int h){m_high = h ;};
    int  gethigh(){return m_high;};

private:
    int m_lenth;
    int m_width;
    int m_high;

};

#endif