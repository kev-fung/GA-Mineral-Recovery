#include "CStream.h"


CStream::CStream() {
	for (int i = 0; i < 2; i++)
		M[i] = 0.0;
}


CStream::~CStream()
{}


CStream::CStream(double mass_sec[2]) {
	for (int i = 0; i < 2; i++)
		M[i] = mass_sec[i];
}


CStream CStream::operator+(const CStream &other)
{
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] + other.M[i];
	return newstream;
}


CStream &CStream::operator+=(const CStream &other)
{
	for (int i = 0; i < 2; i++)
		this->M[i] += other.M[i];
	return *this;
}


CStream CStream::operator*(double frac[2])
{
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] * frac[i];
	return newstream;
}


CStream CStream::operator-(const CStream & other)
{
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] - other.M[i];
	return newstream;
}


void CStream::reset_stream()
{
	this->M[0] = 0.0;
	this->M[1] = 0.0;
}


void CStream::set_stream(double mass[2])
{
	this->M[0] = mass[0];
	this->M[1] = mass[1];
}


class CStream;