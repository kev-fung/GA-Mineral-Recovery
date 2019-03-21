#include "CStream.h"
#include <vector>

using namespace std;

CStream::CStream() {
	for (int i = 0; i < M.size(); i++)
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
	CStream newstream;
	for (int i = 0; i < M.size(); i++)
		newstream.M[i] = M[i] * frac[i];
	return newstream;
}


CStream CStream::operator-(const CStream & other) {
	CStream newstream;
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


class CStream;