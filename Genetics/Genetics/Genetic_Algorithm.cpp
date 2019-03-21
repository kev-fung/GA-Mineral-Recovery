#include "Header.h"
#include "Circuit.h"


void generateCircuit(vector<int> &vals) {
	// Set the feed.
	vals[0] = rand() % num_units;
	for (int i = 1; i < sizeVec; i++){
		vals[i] = rand() % (num_units + 2);
	}
}


vector<int> geneticAlgo(vector<vector<int>> &circuits, vector<double> &fitVec, int minIte, int maxIte, int bestIndCnt, double proCrosOver, double proMut, int num_components, vector<double> feed, vector<double> price, vector<double> fraction)
{
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

	int it = 0; // number of iterations done
	int cnt; // counter to keep track of the children

	double min; // min value of fitness
	double max; // max value of fitness

	int indmax; // index of the best vector
	int cnt_indmax = 0; // keeping track if the best vector is still the first vector of the list
	
	
	while(it<maxIte) {
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
			if (fitVec[i]<min) min=fitVec[i];
		}
		cnt++;

		// Check if indmax has not changed (i.e. the first vector is the best and still the same)
		if (it>minIte && indmax == 0) {
			cnt_indmax++;
			if (cnt_indmax>bestIndCnt) break;
		}
		else {
			cnt_indmax = 0;
		}
		children[0] = circuits[indmax];


		// Find the range of fitness.
		vector<double> intervals(numCircuits + 1);
		intervals[0] = 0;
		double range = 0;
		for (int i = 0; i < numCircuits; i++) {
			fitVec[i] -= (min - 1e-3);  // We subtract the min minus a little bit
			range += fitVec[i];
			intervals[i + 1] = range;
		}


		// Iterate until we have all the children
		while (cnt != numCircuits) {
			// Find the indexes of the parents
			double num0, num1;
			int ind0 = 0, ind1 = 0;
			while (ind0 == ind1) {
				// Pick a random number
				num0 = ((double)rand() / (RAND_MAX));
				num0 *= range;
				num1 = ((double)rand() / (RAND_MAX));
				num1 *= range;

				for (int i = 1; i < numCircuits + 1; i++) {
					if (num0 > intervals[i - 1] && num0 <= intervals[i]) ind0 = i - 1;
					if (num1 > intervals[i - 1] && num1 <= intervals[i]) ind1 = i - 1;
				}
			}


			// Do the cross-over
			num0 = ((double)rand() / (RAND_MAX)); // Cross-over probability
			if (num0>=0 && num0<proCrosOver) { // TO TUNE
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
			int stepSize = 3;
			num0 = ((double)rand() / (RAND_MAX)); // mutation probability

			// Mutate the feed
			if (num0 >= 0 && num0 < proMut ) { // TO TUNE
				randInt = rand() % stepSize + 1;
				circuit0[0] = (circuit0[0] + randInt) % num_units;
				randInt = rand() % stepSize + 1;
				circuit1[0] = (circuit1[0] + randInt) % num_units;
			}
			// Mutate the rest of the circuit
			for (int i = 1; i < sizeCirc; i++) {
				num0 = ((double)rand() / (RAND_MAX)); // mutation probability
				
				if (num0 >= 0 && num0 < proMut) { // TO TUNE
					randInt = rand() % stepSize + 1;
					circuit0[i] = (circuit0[i] + randInt) % (num_units + 2);
					randInt = rand() % stepSize + 1;
					circuit1[i] = (circuit1[i] + randInt) % (num_units + 2);
				}
			}

			// Checking validity of the potential valid child
			if (Check_Validity(circuit0)) {
				children[cnt] = circuit0;
				cnt++;
			}
			if (cnt < numCircuits && Check_Validity(circuit1)) {
				children[cnt] = circuit1;
				cnt++;
			}
		}  // end while on the children


		// Updating the parents vector with the children
		for (int i = 0; i < numCircuits; i++) {
			circuits[i] = children[i];


			// Compute the new fitness
			Circuit circ(num_components, feed, price); // rebuilding the object
			fitVec[i] = circ.Evaluate_Circuit(children[i], tol, max_iterations, fraction);
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
		cout << "Number of iterations: " << it << endl;
	}  // end of the while loop on the iterations

	return best_child;
}
