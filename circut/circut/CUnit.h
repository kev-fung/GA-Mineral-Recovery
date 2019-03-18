#pragma once
#include "Header.h"
#include "CStream.h"

class CUnit {
public:

	CUnit(int id, int conc_num, int tail_num);
	~CUnit();
	CUnit();

	double input_rate_val;
	double input_rate_wst;

	//index of the unit to which this unit’s concentrate stream is connected 
	int conc_num;
	//index of the unit to which this unit’s concentrate stream is connected 
	int tails_num;

	// ID of current unit
	int id;

	double output_rate_con_val;
	double output_rate_con_wst;
	double output_rate_tail_val;
	double output_rate_tail_wst;

	void output_con_tail();

	//A Boolean that is changed to true if the unit has been seen by other member functions and variables of CUnit
	bool mark;

	/*vector<CStream> input;
	CStream ouput_cnctrt;
	CStream output_tail;*/
	

};