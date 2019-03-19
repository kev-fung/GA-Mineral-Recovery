#pragma once
#include "CStream.h"
#include "CUnit.h"
#include "Header.h"

using namespace std;



CUnit::CUnit(int id, int conc_num, int tail_num) :id(id), conc_num(conc_num), tails_num(tails_num)
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
	for (int i = 0; i < 2; i++)
	{
		conc.M[i] = feed.M[i];
		tail.M[i] = feed.M[i] - conc.M[i];
		feed_old.M[i] = feed.M[i];
		feed.M[i] = 0;
	}
}

class CUnit;

//diff between /total feed


//Collapse10:22 AMC CUnit.hCClick to downloadMessage InputMessage Deirdree