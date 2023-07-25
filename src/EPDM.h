#pragma once
class EPDM
{
public:
	EPDM();
	virtual ~EPDM();
public:
	double m_weight;
	double m_price;

public:
	EPDM(double weight, double price) :m_weight(weight), m_price(price) {};


};

