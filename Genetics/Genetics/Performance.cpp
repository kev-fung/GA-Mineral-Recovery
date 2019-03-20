#include "Header.h"
#include "CUnit.h"

vector<CUnit> unit_list;
double circuit_feed[2] = { 10, 100 };


double Evaluate_Circuit(vector<int> circuit_vector, double tolerance, int max_iterations)
{
	unit_list.resize(num_units + 2);

	double valuable_price = 100; //Price of valuable material
	double waste_cost = -500; // Cost of waste material

	for (int i = 0; i < num_units; i++) {
		// We'll be using unit_list to pick out units in this class.
		CUnit unit(i, circuit_vector[(2 * i) + 1], circuit_vector[(2 * i) + 2]);
		unit_list[i] = unit;

		// Initialise feeds with feed
		unit_list[i].feed = CStream(circuit_feed);
	}

	//insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units].feed = CStream(circuit_feed); //conc
	unit_list[num_units + 1];
	unit_list[num_units + 1].feed = CStream(circuit_feed); //tail

	double rel_tol = 1e9;	// Changes wrt the feed difference

	int cnt = 0;
	while (rel_tol > tolerance && cnt < max_iterations) { //while relative difference is more than tolerance
		for (int i = 0; i < num_units; i++) {
			int conc_id = unit_list[i].conc_num; //concentrations stream index
			int tail_id = unit_list[i].tails_num; //tails stream index 

			//split input feed into concentration stream and tail stream
			unit_list[i].output_con_tail(unit_list[conc_id], unit_list[tail_id]);

			//get largest tolerance value between the valuable and waste stream
			rel_tol = unit_list[i].rel_tol_calc();

			if (i == 0) {
				//add circuit feed to unit 0
				unit_list[0].feed.set_stream(circuit_feed);
			}
			else {
				// save feed value to other variable and 
				// reset feed to 0 for other units
				unit_list[i].feed_old = unit_list[i].feed;
				unit_list[i].feed.reset_stream();
			}
		}
		cnt++;
	}

	if (cnt == max_iterations) {
		// if circuit doesn't converge return worst possible value
		return circuit_feed[1] * waste_cost;
	}
	else {
		//calculate fitness value based on economical value of 
		//concentration unit
		double tot_valuable = unit_list[num_units].feed.M[0];
		double tot_waste = unit_list[num_units].feed.M[1];

		double fitness = (tot_valuable*valuable_price) + (tot_waste*waste_cost);

		return fitness;
	}
}