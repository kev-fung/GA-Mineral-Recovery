#pragma once


class CStream
{
public:
	// Constructors
	CStream();
	CStream(double mass_sec[2]);				// Mass/second, not to be confused with meters/second
	~CStream();

	// Operator Methods
	CStream operator+(const CStream &other);		//declare +operator overloading 
	CStream &operator+=(const CStream &other);
	CStream operator*(double frac[2]);
	CStream operator-(const CStream &other);

	// Methods
	void reset_stream();

	// Mass/second of each component in the stream
	// M[0] : Mass/sec of concentration
	// M[1] : Mass/sec of waste
	double M[2];


};