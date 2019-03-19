#include "CStream.h"
#include "CUnit.h"
#include "Header.h"

using namespace std;



CUnit::CUnit(int id, int conc_num, int tail_num):id(id), conc_num(conc_num), tail_num(tail_num)
{

}


CUnit::CUnit()
{
	cout << "Unit created" << endl;
}


CUnit::~CUnit()
{
}

void CUnit::output_con_tail(CUnit &unit_conc, CUnit &unit_tail)
{
	this->conc += (this->feed * this->conc_frac);
	this->tail += (this->feed - this->conc);
	//cout << "this conc: " << conc.M[0] << "  this tail: " << tail.M[0] << endl;
	unit_conc.feed += this->conc;
	//cout << "unit_conc.feed: " << unit_conc.feed.M[0] << endl;
	unit_tail.feed += this->tail;

	this->conc.reset_stream();
	this->tail.reset_stream();
	//cout << "unit_tail.feed: " << unit_tail.feed.M[0] << endl;
	//cout << endl;
	//NEED TO COMMENT
}

double CUnit::rel_tol_calc()
{
	double rel_tol[2];

	for (int i = 0; i < 2; i++)
	{
		rel_tol[i] = (this->feed.M[i] - this->feed_old.M[i]) / this->feed.M[i];
	}

	return (rel_tol[0] > rel_tol[1] ? rel_tol[0] : rel_tol[1]);
}

class CUnit;