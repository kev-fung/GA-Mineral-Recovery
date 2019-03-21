#include "CStream.h"
#include "CUnit.h"
#include "Header.h"

using namespace std;


CUnit::CUnit()
{
}


CUnit::CUnit(int id, int conc_num, int tail_num) :id(id), conc_id(conc_num), tail_id(tail_num)
{
	this->conc_frac[0] = 0.20;
	this->conc_frac[1] = 0.05;
}


CUnit::~CUnit()
{
}


void CUnit::output_con_tail()
{
	this->conc = (this->feed * this->conc_frac);
	this->tail = (this->feed - this->conc);
}


void CUnit::send_stream(CUnit & unit, CStream & stream)
{
	unit.feed += stream;
}


void CUnit::store_feed()
{
	for (int i = 0; i < 2; i++)
	{
		this->feed_old.M[i] = this->feed.M[i];
	}
}


double CUnit::rel_tol_calc()
{
	double rel_tol[2];

	for (int i = 0; i < 2; i++)
	{
		rel_tol[i] = fabs((this->feed.M[i] - this->feed_old.M[i]) / this->feed_old.M[i]);
	}

	return (rel_tol[0] > rel_tol[1] ? rel_tol[0] : rel_tol[1]);
}

class CUnit;