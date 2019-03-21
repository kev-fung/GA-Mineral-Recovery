#pragma once
#include "CStream.h"
<<<<<<< HEAD
#include <vector>

using namespace std;
=======
>>>>>>> b76119a5f405708dd024613499203c4e8b515a24

class CUnit {
public:
	// Constructors:
	CUnit();
	CUnit(int id, int conc_num, int tail_num, vector<double> fraction, vector<double> feed);
	~CUnit();

	// Methods:
	void output_con_tail();
	void send_streams(CUnit &unit_conc, CUnit &unit_tail);
	void store_feed();
	double rel_tol_calc();

	// Variables:
	int id;						// Unit ID
	int conc_id;				// Index of the unit to which this unit’s concentrate stream is connected 
	int tail_id;				// Index of the unit to which this unit’s concentrate stream is connected 
	int num_components;		// Number of components in flow

	vector<double> conc_frac;	// conc_frac[0] : valuable frac, conc_frac[1:n] : waste frac in concentrate stream
	
	CStream feed_old, feed;
	CStream tail, conc;			// Stored output streams to tail and concentration units.

	bool mark;					//A Boolean that is changed to true if the unit has been seen by other member functions and variables of CUnit
};