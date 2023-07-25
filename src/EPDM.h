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
class Group;
class EPDM
{
public:
	EPDM();
	virtual ~EPDM();
public:
	double exitdistance;
	double m_weight;
	double m_weightprice;

public:
	EPDM( Group* pgroup , double distance, double weight, double weightprice) :exitdistance(distance) , m_weight(weight), m_weightprice(weightprice) {};

	double getLenght(){return 1.0 ; };	//pgroup(宽+高)*2-exitdistance*8.0
	double getWeight(){return getLenght() * m_weight;} ;
	double getprice(){return getLenght() * m_weightprice; };
		   


};

