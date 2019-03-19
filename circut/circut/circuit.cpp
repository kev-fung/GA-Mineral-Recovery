#include "Header.h"
#include "CUnit.h"

using namespace std;

CUnit* unit_list;
int num_units;
double circuit_feed[2] = { 10, 100 }; // Feed for valuable and waste component
CUnit circuit_tails, circuit_conc; //feed, and two bins for tails and concentration


double Evaluate_Circuit(vector<int> circuit_vector, double tolerance, int max_iterations)
{
	for (int i = 0; i < num_units; i++)
	{	
		// Fill up our unit_list vector from circuit_vector:
		// We'll be using unit_list to pick out units in this class.
		CUnit unit(i, circuit_vector[1 + i], circuit_vector[i + 2]);
		unit_list[i] = unit;

		// Initialise feeds
		unit_list[i].feed = CStream(circuit_feed);
	}

	//insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units + 1];

	double rel_tol = 1e9;	// Changes wrt the feed difference!

	while (rel_tol > tolerance)
	{
		for (int i = 0; i < num_units; i++)
		{
			int conc_id = unit_list[i].conc_num;
			int tail_id = unit_list[i].tail_num;

			unit_list[i].output_con_tail(unit_list[conc_id], unit_list[tail_id]); //THIS RESETS FEED TO ) FOR NOW //Can be change
			cout << "Conc bin feed: " << unit_list[num_units].feed.M[0] << "\t";


			rel_tol = unit_list[i].rel_tol_calc();

			if (i == 0)
			{
				unit_list[0].feed.set_stream(circuit_feed);
			}
			else
			{
				unit_list[i].feed.reset_stream();
				unit_list[i].feed_old = unit_list[i].feed; // TBC: copy constructor
			}
		}

		cout << endl;
	}


	double tot_valuable = unit_list[num_units].feed.M[0];
	double tot_valuable = unit_list[num_units + 1].feed.M[1];

	cout << "Concentration Output: " << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << unit_list[num_units].feed.M[i] << endl;
	}
	cout << endl;


	return 0;
}


int main()
{
	// Initialise example circuit:
	vector<int> circuit;
	int myarray[] = {0, 1, 2, 3, 0, 4, 0}; //{ 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };
	circuit.insert(circuit.begin(), myarray, myarray + 11);

	num_units = (circuit.size() - 1) / 2;	// Number of units

	unit_list = new CUnit[num_units+2];

	//unit_list.resize(num_units+2); // Vector of unit objects

	Evaluate_Circuit(circuit, 0.005, 1000);	

	delete[] unit_list;

	system("pause");
	return 0;
}