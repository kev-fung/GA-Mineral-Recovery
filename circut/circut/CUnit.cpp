#include "CStream.h"
#include "CUnit.h"
#include "Header.h"

using namespace std;



CUnit::CUnit(int id, int conc_num, int tail_num):id(id), conc_num(conc_num), tails_num(tails_num)
{

}


CUnit::CUnit()
{
	cout << "Unit created" << endl;
}


CUnit::~CUnit()
{
	cout << "Unit out" << endl;
}

void CUnit::output_con_tail()
{
	output_rate_con_val = input_rate_val*.20;
	output_rate_con_wst = input_rate_wst * 0.05;

	output_rate_tail_val = input_rate_val - output_rate_con_val;
	output_rate_tail_wst = input_rate_wst - output_rate_con_wst;
}

class CUnit;
