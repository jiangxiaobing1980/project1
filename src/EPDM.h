#pragma once
/*
输入参数
1.胶条米重
2.胶条KG计重单价

输出
1.返回长度
2.返回单价
3.返回金额
*/
class EPDM
{
public:
	EPDM();
	virtual ~EPDM();
public:
	double m_weight;
	double m_price;

public:
	EPDM(double weight, double price) :m_weight(weight)， m_price(price) {};


};

