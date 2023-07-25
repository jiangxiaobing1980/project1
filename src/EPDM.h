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
private:
	double exitdistance;
	double m_weightmetre;
	double m_weightprice;

	bool bprices;
	double m_price;

public:
	EPDM( Group* pgroup , double distance, double weight, double weightprice) :exitdistance(distance) ,
	m_weightmetre(weight), m_weightprice(weightprice),bprices(0) {};

	double getLenght(){return 1.0 ; };	//pgroup(宽+高)*2-exitdistance*8.0

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

