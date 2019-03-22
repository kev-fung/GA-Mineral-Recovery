#pragma once
#include "CStream.h"

class CUnit {
public:
	// Constructors:
	CUnit();
	CUnit(int id, int conc_num, int tail_num);
	CUnit(int id, int conc_num, int tail_num, double cfrac, double tfrac);
	~CUnit();

	// Methods:
	void output_con_tail();									// Calculate the composite fraction of streams
	void send_streams(CUnit &unit_conc, CUnit &unit_tail);	// Send streams off to the destination units

	void store_feed();										// Store feed into feed old
	double rel_tol_calc();									// calculate relative difference between new and old feeds

	// Variables:
	int id;													// Unit ID
	int conc_id;											// Index of the unit to which this unit’s concentrate stream is connected 
	int tail_id;											// Index of the unit to which this unit’s concentrate stream is connected 

	double conc_frac[2];									// conc_frac[0] : valuable frac, conc_frac[1] : waste frac in concentrate stream

	CStream feed_old, feed;
	CStream tail, conc;										// Stored output streams to tail and concentration units.

	bool mark;												// A Boolean that is changed to true if the unit has been seen by other member functions and variables of CUnit
};