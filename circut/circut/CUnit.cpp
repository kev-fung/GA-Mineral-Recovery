#include "CStream.h"
#include "CUnit.h"
#include "Header.h"

using namespace std;



CUnit::CUnit(int id, int conc_num, int tail_num):id(id), conc_id(conc_num), tail_id(tail_num)
{
}


CUnit::CUnit()
{
	//cout << "Unit created" << endl;
}


CUnit::~CUnit()
{
}

void CUnit::output_con_tail()
{
	this->conc = (this->feed * this->conc_frac);
	//cout << "1Valuables: " << this->conc.M[0] << "\tWastes: " << this->conc.M[1] << endl;

	this->tail = (this->feed - this->conc);
	//cout << "2Valuables: " << this->tail.M[0] << "\tWastes: " << this->tail.M[1] << endl;

	//cout << "this conc: " << conc.M[0] << "  this tail: " << tail.M[0] << endl;

	//this->conc.reset_stream();
	//this->tail.reset_stream();
	//cout << "unit_tail.feed: " << unit_tail.feed.M[0] << endl;
	//cout << endl;
	//NEED TO COMMENT
}

void CUnit::send_streams(CUnit & unit_conc, CUnit & unit_tail)
{
	unit_conc.feed += this->conc;
	unit_tail.feed += this->tail;
}

void CUnit::store_feed()
{
	this->feed_old = this->feed;
}

double CUnit::rel_tol_calc()
{
	//double rel_tol[2];

	//for (int i = 0; i < 2; i++)
	//{
	//	rel_tol[i] = abs(this->feed.M[i] - this->feed_old.M[i]) / this->feed_old.M[i];
	//}

	//return (rel_tol[0] > rel_tol[1] ? rel_tol[0] : rel_tol[1]);
	
	double rel_tol;

	double tot_feed;
	double tot_feed_old; 

	tot_feed = feed.M[0] + feed.M[1];
	tot_feed_old = feed_old.M[0] + feed_old.M[1];

	rel_tol = abs(tot_feed - tot_feed_old) / tot_feed_old;

	return rel_tol;
}

class CUnit;