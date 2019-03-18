#pragma once


class CStream
{
public:
	CStream();
	~CStream();
	
	double M[2];

	//stream in 
	int flow_rate;

	CStream operator+(const CStream &other); //declare +operator overloading 
	CStream &operator+=(const CStream &other); 
 
	//notes:
	//void + operator(CStream other)
	//this->flow_rate += other.flowrate;

	//overide - operator

};
