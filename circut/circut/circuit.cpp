#include "Circuit.h"
#include "CUnit.h"
#include "CStream.h"
#include <iostream>

using namespace std;


Circuit::Circuit(double vprice, double wastec, double conc_feed, double tails_feed) : valuable_price(vprice), waste_cost(wastec), iter(0), rtol(1e9)
{
	this->circuit_feed[0] = conc_feed;
	this->circuit_feed[1] = tails_feed;
}

Circuit::~Circuit()
{
	delete[] unit_list;
}

Circuit::Circuit() : valuable_price(100.), waste_cost(-500.), iter(0), rtol(1e9)
{
	this->circuit_feed[0] = 10;
	this->circuit_feed[1] = 100;
}


double Circuit::Evaluate_Circuit(std::vector<int> circuit_vector, double tolerance, int max_iterations)
{
	int max_iter = max_iterations;						// Max iterations
	num_units = (circuit_vector.size() - 1) / 2;		// Number of units
	unit_list = new CUnit[num_units + 2];

	// Fill up our unit_list (vector of unit objects) from circuit_vector:
	for (int i = 0; i < num_units; i++)
	{
		CUnit unit(i, circuit_vector[(2 * i) + 1], circuit_vector[(2 * i) + 2]);
		unit_list[i] = unit;

		unit_list[i].feed = CStream(circuit_feed);		// Initialise all unit feeds with circuit feed
	}
	// Insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units + 1];
	unit_list[num_units].feed = CStream();				// Final concentration stream
	unit_list[num_units + 1].feed = CStream();			// Final tail stream 

	double *rrtol = new double[2];
	rrtol[0] = 1e9;
	rrtol[1] = 1e9;

	while ((rrtol[0] > tolerance || rrtol[1] > tolerance) && iter < max_iter)			// while relative difference is more than specified tolerance
	{
		// Calculate Tail and Conc streams of all units for this time step!
		for (int i = 0; i < num_units; i++)
		{
			unit_list[i].output_con_tail();
		}

		// Store current feed into old feed and reset feeds to zero!
		unit_list[0].store_feed();
		unit_list[0].feed.set_stream(circuit_feed);		// [10, 100]
		for (int i = 1; i < num_units + 2; i++)			// INCLUDING END STREAMS!
		{
			unit_list[i].store_feed();
			unit_list[i].feed.reset_stream();			// [0, 0]
		}

		// Send the Tail and Conc streams to their destination units!
		for (int i = 0; i < num_units; i++)
		{
			conc_ID = unit_list[i].conc_id;
			tail_ID = unit_list[i].tail_id;

			unit_list[i].send_streams(unit_list[conc_ID], unit_list[tail_ID]);
		}

		// Work out the relative tolerances!
		//max_rel_tol = -1e9;
		double *max_rel_tol = new double[2];
		max_rel_tol[0] = -1e9;
		max_rel_tol[1] = -1e9;

		for (int i = 0; i < num_units; i++)
		{
			double *rel_tol;

			rel_tol = unit_list[i].rel_tol_calc();
			
			for (int i = 0; i < 2; i++)
			{
				if (rel_tol[i] > max_rel_tol[i])
				{
					max_rel_tol[i] = rel_tol[i];
				}
			}

			delete[] rel_tol;
		}

		rrtol[0] = max_rel_tol[0];
		rrtol[1] = max_rel_tol[1];

/*
		for (int i = 0; i < 2; i++)
		{
			if (max_rel_tol[i] > rtol)
			{
				rtol = max_rel_tol[i];
			}
		}*/
		//if (iter == 0) break;
		iter++;
	}

	cout << "iter: " << iter << endl;

	if (iter == max_iter)
		return circuit_feed[1] * waste_cost;

	// Calculate fitness value based on economical value of concentration unit
	tot_valuable = unit_list[num_units].feed.M[0];
	tot_waste = unit_list[num_units].feed.M[1];

	fitness = (tot_valuable*valuable_price) + (tot_waste*waste_cost);

	return fitness;
}

class Circuit;