#pragma once


class CStream
{
public:
	CStream();
	CStream(double flow[2]);
	~CStream();

	double M[2];
	
	CStream operator+(const CStream &other); //declare +operator overloading 
	CStream &operator+=(const CStream &other);

};