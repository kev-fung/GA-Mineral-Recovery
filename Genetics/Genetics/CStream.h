#pragma once


class CStream {
public:
	// Constructors
	CStream();										// Default sets masses to 0
	CStream(double mass_sec[2]);					// Specify own mass flows
	~CStream();

	// Methods
	CStream operator+(const CStream &other);		// +operator overloading 
	CStream &operator+=(const CStream &other);		// +=operator overloading
	CStream operator*(double frac[2]);				// *operator overloading
	CStream operator-(const CStream &other);		// -operator overloading

	void reset_stream();							// Set mass flows to 0
	void set_stream(double mass[2]);				// Set mass flows to specfic masses

	double M[2];									// Mass/second of each component in the stream, M[0] : concentration, M[1] : waste
};