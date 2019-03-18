#include "CStream.h"


CStream::CStream()
{
}


CStream::~CStream()
{
}

Cstream Cstream ::operator+(const CStream &other)
{
    this->flow_rate +=  other.flow_rate;
    //return newstream;
}

CStream CStream::operator-(const CStream &other)
{
    this->flow_rate -= other.flow_rate;
}
