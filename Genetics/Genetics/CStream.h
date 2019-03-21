#pragma once
#include <vector>

using namespace std;

class CStream {
public:
	// Constructors
	CStream();										// Default sets masses to 0
	CStream(vector<double> mass_sec);					// Specify own mass flows
	~CStream();

	// Methods
	CStream operator+(const CStream &other);		// +operator overloading 
	CStream &operator+=(const CStream &other);		// +=operator overloading
	CStream operator*(vector<double> frac);				// *operator overloading
	CStream operator-(const CStream &other);		// -operator overloading

	void reset_stream();							// Set mass flows to 0
	void set_stream(vector<double> mass);				// Set mass flows to specfic masses

	vector<double> M;									// Mass/second of each component in the stream, M[0] : concentration, M[1] : waste
};