#include "Header.h"
#include "CUnit.h"

using namespace std;

CUnit* unit_list;
int num_units;
double circuit_feed[2] = { 10, 100 };		// Feed for valuable and waste component
CUnit circuit_tails, circuit_conc;			// Bins for tails and concentration


void printfeed(CStream feed)
{
	cout << "Valuables: " << feed.M[0] << "\tWastes: " << feed.M[1] << endl;
}


double Evaluate_Circuit(vector<int> circuit_vector, double tolerance, int max_iterations)
{
	double valuable_price = 100.;			// Price of valuable material
	double waste_cost = 500.;				// Cost of waste material
	int max_iter = max_iterations;			// Max iterations
	int iter = 0;							// Iteration
	double rtol = 1e9;						// While loop condition: relative tolerance of feeds
	double rel_tol;							// Relative tolerance of feeds
	double max_rel_tol;						// Maximum relative tolerance of feeds
	int conc_ID;							// Concentration unit index in unit_lists
	int tail_ID;							// Tails unit index in unit_lists
	double tot_valuable;					// Total valuables in final concentration stream 
	double tot_waste;						// Total wastes in final concentration stream
	double fitness;							// Performance metric of the circuit

	// Fill up our unit_list (vector of unit objects) from circuit_vector:
	for (int i = 0; i < num_units; i++)
	{	
		CUnit unit(i, circuit_vector[(2 * i)+1], circuit_vector[(2 * i) + 2]);
		unit_list[i] = unit;

		unit_list[i].feed = CStream(circuit_feed);		// Initialise all unit feeds with circuit feed
		// printfeed(unit_list[i].feed);
		// unit_list[i].output_con_tail();				// Work out the initial tail and conc streams
	}

	// Insert conc bin and tail bin
	unit_list[num_units];
	unit_list[num_units + 1];	
	unit_list[num_units].feed = CStream();				// Final concentration stream
	unit_list[num_units + 1].feed = CStream();			// Final tail stream 

	while (rtol > tolerance && iter < max_iter)							// while relative difference is more than specified tolerance
	{
		// Calculate Tail and Conc streams of all units for this time step!
		for (int i = 0; i < num_units; i++)
		{
		//	printfeed(unit_list[i].feed);
			unit_list[i].output_con_tail();
		//	printfeed(unit_list[i].conc);
		//	printfeed(unit_list[i].tail);
		}

		// Store current feed into old feed and reset feeds to zero!
		unit_list[0].store_feed();				
		unit_list[0].feed.set_stream(circuit_feed);		// [10, 100]
		for (int i = 1; i < num_units+2; i++)			// INCLUDING END STREAMS!
		{
	//		cout << "feed: ";
	//		printfeed(unit_list[i].feed);

			unit_list[i].store_feed();	
	//		cout << "old feed: ";
	//		printfeed(unit_list[i].feed_old);

			unit_list[i].feed.reset_stream();			// [0, 0]
	//		cout << "new reset feed: ";
	//		printfeed(unit_list[i].feed);
		}

		// Send the Tail and Conc streams to their destination units!
		for (int i = 0; i < num_units; i++)
		{
			conc_ID = unit_list[i].conc_id;
			tail_ID = unit_list[i].tail_id;

			unit_list[i].send_streams(unit_list[conc_ID], unit_list[tail_ID]);

			//cout << "This conc " << i << ": ";
			//printfeed(unit_list[i].conc);
			//cout << "This tail " << i << ": ";
			//printfeed(unit_list[i].tail);

			//cout << "To conc " << conc_ID << ": ";
			//printfeed(unit_list[conc_ID].feed);
			//cout << "To tail " << tail_ID << ": ";
			//printfeed(unit_list[tail_ID].feed);
			//// split input feed into concentration stream and tail stream
			//unit_list[i].output_con_tail();				//unit_list[conc_ID], unit_list[tail_ID]

			//// get largest tolerance value between the valuable and waste stream
			//rel_tol = unit_list[i].rel_tol_calc();

			//if (i == 0)
			//{
			//	// add circuit feed to unit 0
			//	unit_list[0].feed.set_stream(circuit_feed);
			//	// cout << "Unit 0 feed: " << unit_list[0].feed.M[0];
			//}
			////else if ()
			//else
			//{
			//	// save feed value to other variable and 
			//	// reset feed to 0 for other units
			//	unit_list[i].feed_old = unit_list[i].feed; 
			//	unit_list[i].feed.reset_stream();

			//}
			//cout << endl;
		}

		// Work out the relative tolerances!
		max_rel_tol = -1e9;
		for (int i = 0; i < num_units; i++)
		{
			rel_tol = unit_list[i].rel_tol_calc();
			if (rel_tol > max_rel_tol)
			{
				max_rel_tol = rel_tol;
			}
		}
		
		cout << "Unit 0";
		printfeed(unit_list[0].feed);

		cout << "Unit 1";
		printfeed(unit_list[1].feed);

		cout << "Unit 2";
		printfeed(unit_list[2].feed);

		cout << "Conc bin stream: ";
		printfeed(unit_list[num_units].feed);

		cout << "Tails bin stream: ";
		printfeed(unit_list[num_units+1].feed);

		rtol = max_rel_tol;
		iter++;
		/*
		system("pause");*/
	}

	cout << "Iteration: " << iter << endl;
	// Calculate fitness value based on economical value of concentration unit
	tot_valuable = unit_list[num_units].feed.M[0];
	tot_waste = unit_list[num_units].feed.M[1];

	fitness = (tot_valuable*valuable_price) - (tot_waste*waste_cost);

	return fitness;
}


int main()
{
	// Initialise example circuit:
	vector<int> circuit;
	int myarray[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };	// { 0, 1, 2, 3, 0, 0, 4 }; //	// //{ 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 }; //{6, 16, 7, 7, 13, 11, 12, 15, 5, 3, 6, 0, 2, 14, 12, 1, 12, 14, 11, 5, 16, 11, 9, 4, 1, 0, 8, 5, 10, 2, 6};  //{ 0, 1, 2, 3, 0, 0, 4 }; // // //
	circuit.insert(circuit.begin(), myarray, myarray + 11);	// 31 //11 //7

	num_units = (circuit.size() - 1) / 2;					// Number of units

	unit_list = new CUnit[num_units+2];

	double fitness = Evaluate_Circuit(circuit, 1e-6, 1000);	

	cout << "Fitness: " << fitness << endl;

	delete[] unit_list;

	system("pause");
	return 0;
}
/*
Test:

Converged Feeds

0: 14.70571678
0: 110.4972376
1: 2.941292889
1: 5.524861908
2: 11.76517156
2: 104.9723763

3: 0.588214597
3: 0.276243094
4: 9.411433559
4: 99.72375684
Total output: 109.9996481

*/