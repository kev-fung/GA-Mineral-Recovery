#include "Genetic_Algorithm.h"
#include "Circuit.h"
#include "Validity.h"
#include <vector>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>


#include <mpi.h>


using namespace std;


// Define when one process has finished the iterations while loop.
bool finished = false;


Genetic_Algorithm::Genetic_Algorithm(int nunits, int nCircuits, double pCrossOver, double pMut, double toler, int max_iter, bool tGA) : num_units(nunits), numCircuits(nCircuits), proCrossOver(pCrossOver), proMut(pMut), tol(toler), max_iterations(max_iter), timeGA(tGA)
{
	sizeVec = 2 * nunits + 1;		// Initialise size of the GA circuit vector
	circuit.resize(sizeVec, 0);
	circuits.resize(numCircuits, vector<int>(sizeVec, 0));
	fitVec.resize(numCircuits, 0);
}


Genetic_Algorithm::~Genetic_Algorithm()
{
}


void Genetic_Algorithm::generateCircuit(vector<int> &circuit) {
	// Fill circuit with random int values
	circuit[0] = rand() % num_units;
	for (int i = 1; i < sizeVec; i++)
	{
		circuit[i] = rand() % (num_units + 2);
	}
}


vector<int> Genetic_Algorithm::geneticAlgo(int minIte, int maxIte, int bestIndCnt, Validity &val) {
	

    int id, p;
    int tag_num = 1;
    int flag = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Request* requestRec = new MPI_Request[p];
	MPI_Request* requestSend = new MPI_Request[p];


	// Size of the vector of int and number of circuits
	int sizeCirc = circuits[0].size();
	int numCircuits = circuits.size();

	// Initialise vector that will contain the next generation circuits
	vector<vector<int>> children(numCircuits, vector<int>(sizeCirc, 0));

	// Vectors the do the cross-over and/or mutation
	vector<int> circuit0(sizeCirc, 0);
	vector<int> circuit1(sizeCirc, 0);

	// To store the best child, output
	vector<int> best_child(sizeCirc, 0);

	int it = 0;		// number of iterations done
	int cnt;		// counter to keep track of the children

	double min;		// min value of fitness
	double max;		// max value of fitness

	int indmax;		// index of the best vector
	int cnt_indmax = 0; // keeping track if the best vector is still the first vector of the list



	// Set up receives.
	int recNum = 1;
	//MPI_Gather( vecin, 1, vec, vecout, n, MPI_DOUBLE, root, comm);
	//MPI_Gather(recNum, 1, MPI_INT, recArr, n, MPI_DOUBLE, root, comm);
	for (int i = 0; i<p; i++)
	{
		if (i!=id)
		{
			MPI_Irecv(&recNum, 1, MPI_INT, i, tag_num, MPI_COMM_WORLD, &requestRec[i]);
		}
	}	



	while (it < maxIte) {
		// Keep track of the children
		cnt = 0;

		// To get the max and min values of fitness
		min = fitVec[0];
		max = fitVec[0];

		// Index of the best vector
		indmax = 0;

		// The best goes on unchanged
		for (int i = 1; i < numCircuits; i++) {
			if (fitVec[i] > max) {
				max = fitVec[i];
				indmax = i;
			}
			if (fitVec[i] < min) min = fitVec[i];
		}
		cnt++;

		// Check if indmax has not changed (i.e. the first vector is the best and still the same)
		if (it > minIte && indmax == 0) {
			cnt_indmax++;
			if (cnt_indmax > bestIndCnt) break;
		}
		else {
			cnt_indmax = 0;
		}
		children[0] = circuits[indmax];

		// Find the range of fitness.
		vector<double> intervals(numCircuits + 1);
		intervals[0] = 0;
		double range = 0;
		for (int i = 0; i < numCircuits; i++)
		{
			fitVec[i] -= (min - 1e-3);  // We subtract the min minus a little bit
			range += fitVec[i];
			intervals[i + 1] = range;
		}

		// Iterate until we have all the children
		while (cnt != numCircuits)
		{
			// Find the indexes of the parents
			double num0, num1;
			int ind0 = 0, ind1 = 0;

			num0 = ((double)rand() / (RAND_MAX));
			num0 *= range;

			for (int i = 0; i < numCircuits; i++)
				if (num0 < intervals[i + 1])
				{
					ind0 = i;
					break;
				}
			do
			{
				// Pick a random number
				num1 = ((double)rand() / (RAND_MAX));
				num1 *= range;
				for (int i = 0; i < numCircuits; i++)
					if (num1 < intervals[i + 1])
					{
						ind1 = i;
						break;
					}
			} while (ind0 == ind1);

			// Do the cross-over
			num0 = ((double)rand() / (RAND_MAX)); // Cross-over probability
			if (num0 < proCrossOver) { // TO TUNE
				// Select a random point in the vector
				int pivot = rand() % (sizeCirc - 1) + 1;
				// Do the two children
				for (int i = 0; i < pivot; i++) {
					circuit0[i] = circuits[ind1][i];
					circuit1[i] = circuits[ind0][i];
				}
				for (int i = pivot; i < sizeCirc; i++) {
					circuit0[i] = circuits[ind0][i];
					circuit1[i] = circuits[ind1][i];
				}
			}
			// Case when the cross-over doesn't happen
			else {
				circuit0 = circuits[ind0];
				circuit1 = circuits[ind1];
			}

			// Do the mutation
			int randInt;
			num0 = ((double)rand() / (RAND_MAX)); // mutation probability

			// Mutate the feed
			if (num0 < proMut)
			{ // TO TUNE
				circuit0[0] = rand() % num_units;
			}
			num0 = ((double)rand() / (RAND_MAX)); // mutation probability
			if (num0 < proMut)
			{
				circuit1[0] = rand() % num_units;
			}
			// Mutate the rest of the circuit
			for (int i = 1; i < sizeCirc; i++)
			{
				num0 = ((double)rand() / (RAND_MAX)); // mutation probability

				if (num0 < proMut)
				{ // TO TUNE
					circuit0[i] = rand() % (num_units + 2);
				}

				num0 = ((double)rand() / (RAND_MAX)); // mutation probability

				if (num0 < proMut)
				{ // TO TUNE
					circuit1[i] = rand() % (num_units + 2);
				}
			}

			// Checking validity of the potential valid child
			if (val.Check_Validity(circuit0)) {
				children[cnt] = circuit0;
				cnt++;
			}
			if (cnt < numCircuits && val.Check_Validity(circuit1)) {
				children[cnt] = circuit1;
				cnt++;
			}
		}  // end while on the children

		// Updating the parents vector with the children
		for (int i = 0; i < numCircuits; i++) {
			circuits[i] = children[i];


			// Compute the new fitness
			Circuit circ(100.0, -500.0, 10, 100); // rebuilding the object
			fitVec[i] = circ.Evaluate_Circuit(children[i], tol, max_iterations);
		}

		// Getting the best child vector
		indmax = 0;
		max = fitVec[0];
		for (int i = 1; i < numCircuits; i++) {
			if (fitVec[i] > max) {
				max = fitVec[i];
				indmax = i;
			}
		}
		best_child = circuits[indmax];

		/*cout << "fitness: " << fitVec[indmax];
		cout << endl;*/

		it++;
		if (!timeGA) cout << "Number of iterations: " << it << " best " << fitVec[indmax] << "   Processor: " << id <<  endl;



		// Test the receives.
		for (int i=0; i<p; i++)
		{
			if(i!=id)
			{
				if (MPI_Test(&requestRec[i], &flag, MPI_STATUS_IGNORE)==MPI_SUCCESS && flag==1)
				{
					finished = true;
					cout << "Processor " << id << " is stopped." << endl;
					if (finished == true) break;
				}
			}
		}
		if (finished==true) break;



	}  // end of the while loop on the iterations.
	// When finished send a message to all the other processes.
	if (finished==false)
	{
		int sendNum = 1;
    	MPI_Request reqSend;
    	MPI_Ibcast(&sendNum, 1, MPI_INT, id, MPI_COMM_WORLD, &reqSend);

    	cout << endl << endl << "Processor " << id << " finished first." << endl;

    	for (int i=0; i<p; i++)
    	{
    		if (i!=id)
    		{
    			MPI_Isend(&sendNum, 1, MPI_INT, i, tag_num, MPI_COMM_WORLD, &requestSend[i]);
    		}
    	}
    }



	return best_child;
}



double Genetic_Algorithm::wTime()
{
	return (double)clock() / CLOCKS_PER_SEC;
}



vector<int> Genetic_Algorithm::runAlgo(int bestIndCnt, int minIte, int maxIte)
{


    int id, p;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	// Random seed.
	srand(time(NULL) + id * 10);


	if (timeGA)
	{
		//The timing starts here.
		tdif = -wTime();
	}

	// Generating the parents
	if (!timeGA) cout << "Generating parents" << endl;
	Validity validity(num_units, sizeVec);		// Make Validity Object
	for (int i = 0; i < numCircuits; i++)
	{
		while (!validity.Check_Validity(circuit))
		{
			generateCircuit(circuit);
		}
		Circuit circ;							// Initialise default circuit i.e. use default circuit param
		circuits[i] = circuit;
		fitVec[i] = circ.Evaluate_Circuit(circuit, tol, max_iterations);

		// Reinitialise the vector with 0
		for (int j = 0; j < sizeVec; j++) {
			circuit[j] = 0;
		}
	}
	if (!timeGA) cout << endl;

	// Display the vectors
	if (!timeGA)
	{
		cout << "Input Vectors" << endl;
		for (int i = 0; i < numCircuits; i++) {
			for (int j = 0; j < sizeVec; j++) {
				cout << circuits[i][j] << " ";
			}
			cout << " Fitness: " << fitVec[i] << endl;
		}
		cout << endl;
	}



	// Genetic algorithm
	vector<int> best_circuit;
	best_circuit = geneticAlgo(minIte, maxIte, bestIndCnt, validity);



	// Display the vector, only the processor finishing first.
	if (finished==false)
	{
		// Print the output.
		cout << endl << "Output best vector for process " << id << ":" << endl;
		for (int j = 0; j < sizeVec; j++) {
			cout << best_circuit[j] << " ";
		}

		Circuit circ;
		double best_fitness;
		best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iterations);
		cout << "   Fitness: " << best_fitness << endl << endl << endl;
	}



	// Timing.
	if (timeGA && finished==false)
	{
		tdif += wTime();
		cout << setprecision(5);
		cout << endl << "Time of execution = " << tdif << "s." << endl << endl;
	}



	return best_circuit;
}

//void Genetic_Algorithm::output_file(string name, )
//{
//
//	stringstream fname;
//	fstream f1;
//
//	fname << name << ".csv";
//
//	f1.open(fname.str().c_str(), ios_base::out);
//
//	for (int i = 1; i < id_ysize + 1; i++)
//	{
//		for (int j = 1; j < id_xsize + 1; j++)
//			f1 << grid[i][j] << ",";
//		f1 << endl;
//	}
//
//	f1.close();
//}
