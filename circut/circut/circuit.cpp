#include "Circuit.h"
#include "CUnit.h"
#include "CStream.h"
#include <iostream>

using namespace std;

<<<<<<< HEAD
vector<CUnit> unit_list;
int num_units;
double circuit_feed[2] = { 10, 100 }; // Feed for valuable and waste component
CUnit circuit_tails, circuit_conc; //feed, and two bins for tails and concentration

int max_iteration = 100;
double tolerance = 1e-6;

=======

Circuit::Circuit(double vprice, double wastec, double conc_feed, double tails_feed) : valuable_price(vprice), waste_cost(wastec), iter(0), rtol(1e9)
{
	this->circuit_feed[0] = conc_feed;
	this->circuit_feed[1] = tails_feed;
}

Circuit::~Circuit()
{
	delete[] unit_list;
}

Circuit::Circuit() : valuable_price(100.), waste_cost(500.), iter(0), rtol(1e9)
{
	this->circuit_feed[0] = 10;
	this->circuit_feed[1] = 100;
}
>>>>>>> a700eb4ae0ded90dbc0774d1ae9bfd0289a36f5c


double Circuit::Evaluate_Circuit(std::vector<int> circuit_vector, double tolerance, int max_iterations)
{
<<<<<<< HEAD
	double valuable_price = 100; //Price of valuable material
	double waste_cost = -500; // Cost of waste material
=======
	int max_iter = max_iterations;						// Max iterations
	num_units = (circuit_vector.size() - 1) / 2;		// Number of units
	unit_list = new CUnit[num_units + 2];
>>>>>>> a700eb4ae0ded90dbc0774d1ae9bfd0289a36f5c

	// Fill up our unit_list (vector of unit objects) from circuit_vector:
	for (int i = 0; i < num_units; i++)
	{
		CUnit unit(i, circuit_vector[(2 * i) + 1], circuit_vector[(2 * i) + 2]);
		unit_list[i] = unit;

		unit_list[i].feed = CStream(circuit_feed);		// Initialise all unit feeds with circuit feed
	}

	// Insert conc bin and tail bin
	unit_list[num_units];
<<<<<<< HEAD
	//unit_list[num_units].feed = CStream(circuit_feed); //conc
	unit_list[num_units + 1];
	//unit_list[num_units + 1].feed = CStream(circuit_feed); //tail

	double rel_tol = 1e9;	// Changes wrt the feed difference
	int cnt = 0;

	while (rel_tol > tolerance && cnt < max_iterations) //while relative difference is more than tolerance
=======
	unit_list[num_units + 1];
	unit_list[num_units].feed = CStream();				// Final concentration stream
	unit_list[num_units + 1].feed = CStream();			// Final tail stream 

	while (rtol > tolerance && iter < max_iter)			// while relative difference is more than specified tolerance
>>>>>>> a700eb4ae0ded90dbc0774d1ae9bfd0289a36f5c
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

<<<<<<< HEAD
			//get largest tolerance value between the valuable and waste stream
			rel_tol = unit_list[i].rel_tol_calc();
			cout << rel_tol << endl;

			if (i == 0)
			{
				//add circuit feed to unit 0
				unit_list[0].feed.set_stream(circuit_feed);
			}
			else
=======
		// Send the Tail and Conc streams to their destination units!
		for (int i = 0; i < num_units; i++)
		{
			conc_ID = unit_list[i].conc_id;
			tail_ID = unit_list[i].tail_id;

			unit_list[i].send_streams(unit_list[conc_ID], unit_list[tail_ID]);
		}

		// Work out the relative tolerances!
		max_rel_tol = -1e9;
		for (int i = 0; i < num_units; i++)
		{
			rel_tol = unit_list[i].rel_tol_calc();
			if (rel_tol > max_rel_tol)
>>>>>>> a700eb4ae0ded90dbc0774d1ae9bfd0289a36f5c
			{
				max_rel_tol = rel_tol;
			}
		}
<<<<<<< HEAD
		cnt++;
		if (cnt > 100)
			int a;
	}

	cout << cnt << endl;

	if (cnt == max_iterations)
	{
		// if circuit doesn't converge return worst possible value
		return circuit_feed[1] * waste_cost;
	}
	else
	{
		//calculate fitness value based on economical value of 
		//concentration unit
		double tot_valuable = unit_list[num_units].feed.M[0];
		double tot_waste = unit_list[num_units].feed.M[1];

		cout << "Valuable in concentrate: " << unit_list[num_units].feed.M[0] << endl; 
		cout << "Waste in concentrate: " << unit_list[num_units].feed.M[1] << endl;

		double fitness = (tot_valuable*valuable_price) + (tot_waste*waste_cost);

		return fitness;
	}
}



int main()
{
	// Initialise example circuit:
	vector<int> circuit;
	int myarray[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 }; //{0, 1, 2, 3, 0, 4, 0}; //
	circuit.insert(circuit.begin(), myarray, myarray + 11);

	num_units = (circuit.size() - 1) / 2;	// Number of units

	//unit_list = new CUnit[num_units+2];

	unit_list.resize(num_units+2); // Vector of unit objects

	double fitness = Evaluate_Circuit(circuit, tolerance, max_iteration);
	cout << fitness << endl;

	system("pause");
	return 0;
}
=======

		rtol = max_rel_tol;
		iter++;
	}

	cout << "iter: " << iter << endl;
	// Calculate fitness value based on economical value of concentration unit
	tot_valuable = unit_list[num_units].feed.M[0];
	tot_waste = unit_list[num_units].feed.M[1];

	fitness = (tot_valuable*valuable_price) - (tot_waste*waste_cost);

	return fitness;
}

class Circuit;
>>>>>>> a700eb4ae0ded90dbc0774d1ae9bfd0289a36f5c
