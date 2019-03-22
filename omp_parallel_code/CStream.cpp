<<<<<<< HEAD:Genetics/Genetics/CStream.cpp
#include "CStream.h"
#include <vector>

using namespace std;

CStream::CStream() {

}

CStream::CStream(int size) 
{
	M.resize(size);
	for (int i = 0; i < size; i++)
		M[i] = 0.0;
}

CStream::~CStream()
{}


CStream::CStream(vector<double> mass_sec) {
	M.resize(mass_sec.size());
	for (int i = 0; i < mass_sec.size(); i++)
		M[i] = mass_sec[i];
}


CStream CStream::operator+(const CStream &other) {
	CStream newstream;
	for (int i = 0; i < M.size(); i++)
		newstream.M[i] = M[i] + other.M[i];
	return newstream;
}


CStream &CStream::operator+=(const CStream &other) {
	for (int i = 0; i < M.size(); i++)
		this->M[i] += other.M[i];
	return *this;
}


CStream CStream::operator*(vector<double> frac) {
	CStream newstream = CStream(frac.size());
	for (int i = 0; i < M.size(); i++)
		newstream.M[i] = M[i] * frac[i];
	return newstream;
}


CStream CStream::operator-(const CStream & other) {
	CStream newstream = CStream(other.M.size());
	for (int i = 0; i < M.size(); i++)
		newstream.M[i] = M[i] - other.M[i];
	return newstream;
}


void CStream::reset_stream() {
	for (int i = 0; i < M.size(); i++) {
		this->M[i] = 0.0;
	}
}


void CStream::set_stream(vector<double> mass) {
	M.resize(mass.size());
	for (int i = 0; i < mass.size(); i++)
		M[i] = mass[i];
}


=======
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


CStream CStream::operator+(const CStream &other) {
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] + other.M[i];
	return newstream;
}


CStream &CStream::operator+=(const CStream &other) {
	for (int i = 0; i < 2; i++)
		this->M[i] += other.M[i];
	return *this;
}


CStream CStream::operator*(double frac[2]) {
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] * frac[i];
	return newstream;
}


CStream CStream::operator-(const CStream & other) {
	CStream newstream;
	for (int i = 0; i < 2; i++)
		newstream.M[i] = M[i] - other.M[i];
	return newstream;
}


void CStream::reset_stream() {
	this->M[0] = 0.0;
	this->M[1] = 0.0;
}


void CStream::set_stream(double mass[2]) {
	this->M[0] = mass[0];
	this->M[1] = mass[1];
}


>>>>>>> 89c164f33287a85d9d6dc7c915e37b05781c81dd:src/CStream.cpp
class CStream;