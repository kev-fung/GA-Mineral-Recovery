#pragma once
#include "Header.h"
#include "CStream.h"
#include "vector"

class CUnit {
public:

	// Constructors:
	CUnit(int id, int conc_num, int tails_num);
	~CUnit();
	CUnit();

	// Methods:
	void output_con_tail(CUnit &unit_conc, CUnit &unit_tail);
	double rel_tol_calc();

	// Variables:
	int id;						// Unit ID
	int conc_num;				// Index of the unit to which this unit’s concentrate stream is connected 
	int tails_num;				// Index of the unit to which this unit’s tailing stream is connected 

	double conc_frac[2] = { 0.20, 0.05 };	// conc_frac[0] : valuable frac, conc_frac[1] : waste frac in concentrate stream

	CStream feed;
	CStream feed_old;
	CStream tail, conc;	// Output streams to tail and concentration units.

	bool mark; //A Boolean that is changed to true if the unit has been seen by other member functions and variables of CUnit
};