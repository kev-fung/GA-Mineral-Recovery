#include "CStream.h"

CStream::CStream()
{
}

CStream::~CStream()
{
}

CStream::CStream(double flow[2])
{
	for (int i = 0; i < 2; i++)
		M[i] = flow[i];
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
		M[i] += other.M[i];
	return *this;
}