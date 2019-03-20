#pragma once
#include "CUnit.h"
#include "CStream.h"
#include <vector>

class Circuit
{

public:
	// Constructors
	Circuit(double vprice, double wastec, double conc_feed, double tails_feed);
	~Circuit();
	Circuit();

	// Methods
	double Evaluate_Circuit(std::vector<int> circuit_vector, double tolerance, int max_iterations);

private:
	double valuable_price;					// Price of valuable material
	double waste_cost;						// Cost of waste material
	int iter;								// Iteration
	double rtol;							// While loop condition: relative tolerance of feeds
	double rel_tol;							// Relative tolerance of feeds
	double max_rel_tol;						// Maximum relative tolerance of feeds
	int conc_ID;							// Concentration unit index in unit_lists
	int tail_ID;							// Tails unit index in unit_lists
	double tot_valuable;					// Total valuables in final concentration stream 
	double tot_waste;						// Total wastes in final concentration stream
	double fitness;							// Performance metric of the circuit

	CUnit* unit_list;						// Dynamic array of units
	int num_units;							// Number of units in circuit
	double circuit_feed[2];					// Feed for valuable and waste component
	CUnit circuit_tails, circuit_conc;		// Bins for tails and concentration
};

