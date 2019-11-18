#include "Circuit.h"
#include "CUnit.h"
#include "CStream.h"
#include <iostream>

using namespace std;

Circuit::Circuit(int num_components, vector<double> feed, vector<double> prices) : num_components(num_components), iter(0), rtol(1e9)
{
	this->circuit_feed.resize(feed.size());
	this->price.resize(prices.size());
	for (int i = 0; i < feed.size(); i++)
	{
		this->circuit_feed[i] = feed[i];
		this->price[i] = prices[i];
	}
}

Circuit::~Circuit() {
	delete[] unit_list;
}

Circuit::Circuit() : iter(0), rtol(1e9) 
{
	this->circuit_feed.resize(2);
	this->price.resize(2);
	this->circuit_feed[0] = 10;
	this->circuit_feed[1] = 100;
	this->price[0] = 100;
	this->price[1] = -500;
}


double Circuit::Evaluate_Circuit(std::vector<int> circuit_vector, double tolerance, int max_iterations, vector<double> fraction) {
	int max_iter = max_iterations;						// Max iterations
	num_units = (circuit_vector.size() - 1) / 2;		// Number of units
	unit_list = new CUnit[num_units + 2];

	int feed_id = circuit_vector[0];					// Save id of feed unit

	// Fill up our unit_list (vector of unit objects) from circuit_vector:
	for (int i = 0; i < num_units; i++) {
		CUnit unit(i, circuit_vector[(2 * i) + 1], circuit_vector[(2 * i) + 2], fraction, circuit_feed);
		unit_list[i] = unit;

		unit_list[i].feed = CStream(circuit_feed);		// Initialise all unit feeds with circuit feed
	}

	// Insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units + 1];
	unit_list[num_units].feed = CStream(num_components);				// Final concentration stream
	unit_list[num_units + 1].feed = CStream(num_components);			// Final tail stream 

	while (rtol > tolerance && iter < max_iter)			// while relative difference is more than specified tolerance
	{
		// Calculate Tail and Conc streams of all units for this time step!
		for (int i = 0; i < num_units; i++) {
			unit_list[i].output_con_tail();
		}

		// Store current feed into old feed and reset feeds to zero!		
		for (int i = 0; i < num_units + 2; i++)			// INCLUDING END STREAMS!
		{
			unit_list[i].store_feed();
			unit_list[i].feed.reset_stream();			// [0, 0]
		}
		unit_list[feed_id].feed.set_stream(circuit_feed);		// [10, 100]

		// Send the Tail and Conc streams to their destination units!
		for (int i = 0; i < num_units; i++) {
			conc_ID = unit_list[i].conc_id;
			tail_ID = unit_list[i].tail_id;

			unit_list[i].send_streams(unit_list[conc_ID], unit_list[tail_ID]);
		}

		// Work out the relative tolerances!
		max_rel_tol = -1e9;
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
		return circuit_feed[1] * price[1];
	}
		
	// Calculate fitness value based on economical value of concentration unit
	double fitness = 0;
	for (int i = 0; i < num_components; i++)
	{
		fitness += unit_list[num_units].feed.M[i] * price[i];

	}

	return fitness;
}

class Circuit;