#pragma once;
#include "Header.h"
#include "CStream.h"

class CUnit {
public:

	CUnit(int id, int conc_num, int tail_num);
	~CUnit();
	CUnit();

	double fraction[2] = { 0.20, 0.05 };
	double input_rate_wst;

	//index of the unit to which this unit’s concentrate stream is connected 
	int conc_num;
	//index of the unit to which this unit’s concentrate stream is connected 
	int tails_num;

	// ID of current unit
	int id;

	void output_con_tail();

	//A Boolean that is changed to true if the unit has been seen by other member functions and variables of CUnit
	bool mark;


	CStream feed, tail, conc;
	CStream feed_old;


};