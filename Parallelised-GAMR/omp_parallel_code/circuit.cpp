#include "Circuit.h"
#include "CUnit.h"
#include "CStream.h"
#include <iostream>
#include <omp.h>

using namespace std;


Circuit::Circuit(double vprice, double wastec, double conc_feed, double tails_feed, double cf, double tf) : valuable_price(vprice), waste_cost(wastec), cfrac(cf), tfrac(tf), iter(0), rtol(1e9)
{
	this->circuit_feed[0] = conc_feed;
	this->circuit_feed[1] = tails_feed;
}


Circuit::~Circuit() {
	delete[] unit_list;
}


Circuit::Circuit() : valuable_price(100.), waste_cost(-500.), cfrac(0.20), tfrac(0.05), iter(0), rtol(1e9) 
{
	this->circuit_feed[0] = 10;
	this->circuit_feed[1] = 100;
}


double Circuit::Evaluate_Circuit(std::vector<int> circuit_vector, double tolerance, int max_iterations) {
	int max_iter = max_iterations;						// Max iterations
	num_units = (circuit_vector.size() - 1) / 2;		// Number of units
	unit_list = new CUnit[num_units + 2];

	int feed_id = circuit_vector[0];					// Save id of feed unit

	// Fill up our unit_list (vector of unit objects) from circuit_vector:
#pragma omp parallel for
	for (int i = 0; i < num_units; i++) {
		CUnit unit(i, circuit_vector[(2 * i) + 1], circuit_vector[(2 * i) + 2], cfrac, tfrac);
		unit_list[i] = unit;

		unit_list[i].feed = CStream(circuit_feed);		// Initialise all unit feeds with circuit feed
	}

	// Insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units + 1];
	unit_list[num_units].feed = CStream();				// Final concentration stream
	unit_list[num_units + 1].feed = CStream();			// Final tail stream 

	while (rtol > tolerance && iter < max_iter)			// while relative difference is more than specified tolerance
	{
		// Calculate Tail and Conc streams of all units for this time step!
#pragma omp parallel for
		for (int i = 0; i < num_units; i++) {
			unit_list[i].output_con_tail();
		}

		// Store current feed into old feed and reset feeds to zero!
#pragma omp parallel for
		for (int i = 0; i < num_units + 2; i++)			// INCLUDING END STREAMS!
		{
			unit_list[i].store_feed();
			unit_list[i].feed.reset_stream();			// [0, 0]
		}
		unit_list[feed_id].feed.set_stream(circuit_feed);		// [10, 100]

		// Send the Tail and Conc streams to their destination units!
#pragma omp parallel for
		for (int i = 0; i < num_units; i++) {
			conc_ID = unit_list[i].conc_id;
			tail_ID = unit_list[i].tail_id;

			unit_list[i].send_streams(unit_list[conc_ID], unit_list[tail_ID]);
		}

		// Work out the relative tolerances!
		max_rel_tol = -1e9;
#pragma omp parallel for
		for (int i = 0; i < num_units; i++) {
			rel_tol = unit_list[i].rel_tol_calc();
			if (rel_tol > max_rel_tol) {
				max_rel_tol = rel_tol;
			}
		}

		rtol = max_rel_tol;
		iter++;
	}
	if (iter == max_iter) {
		return circuit_feed[1] * waste_cost;
	}
		
	// Calculate fitness value based on economical value of concentration unit
	tot_valuable = unit_list[num_units].feed.M[0];
	tot_waste = unit_list[num_units].feed.M[1];

	fitness = (tot_valuable*valuable_price) + (tot_waste*waste_cost);

	return fitness;
}

class Circuit;