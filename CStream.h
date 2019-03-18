#pragma once
class CStream
{
public:
	CStream();
	~CStream();
	
	double v_output = 0.20;
	double w_output = 0.05;

	//stream in 
	int flow_rate;

	CStream operator+(const CStream &other);
	CStream operator-(const CStream &other);

	//void + operator(CStream other)
	//this->flow_rate += other.flowrate;

	//overide - operator

};

