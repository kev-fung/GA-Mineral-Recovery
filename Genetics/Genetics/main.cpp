#include "Header.h"
#include "Circuit.h"
#include <time.h>
#include <iomanip>

using namespace std;


const int num_units = 10;
int sizeVec = 2 * num_units + 1;

// Parameters for the Evaluate_Circuit function
double tol = 1e-6;
int max_iterations = 2000;


// Get the time.
double wTime()
{
	return (double)clock() / CLOCKS_PER_SEC;
}


int main() {
	int numCircuits = 100;  // TO TUNE


	// Inputs for convergence of the genetic algo.
	int bestIndCnt = 3000; // Minimum number of iterations for the best circuit to be the same
	int minIte = 0; // Minimum number of iterations to be done
	int maxIte = 10000; // Maximum number of iterations possible


	// Genetic algorithm parameters.
	double proCrosOver = 1.;  // Probability of cross-over.
	double proMut = 0.004;  // Probability of mutation.

	// Random seed
	srand(time(NULL));



	//The timing starts here.
	double tdif = -wTime();



	// Circuit and list of circuits
	vector<int> circuit(sizeVec, 0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec, 0));

	// List of fitness values
	vector<double> fitVec(numCircuits, 0);


	// Generating the parents
	cout << "Generating parents" << endl;
	for (int i = 0; i < numCircuits; i++) {
		while (!Check_Validity(circuit)) {
			generateCircuit(circuit);
		}
		Circuit circ(100.0, -500.0, 10, 100);

		circuits[i] = circuit;
		fitVec[i] = circ.Evaluate_Circuit(circuit, tol, max_iterations);

		// Reinitialise the vector with 0
		for (int j = 0; j < sizeVec; j++) {
			circuit[j] = 0;
		}
	}
	cout << endl;


	 // Check the vectors.
	 cout << "Input Vectors" << endl;
	 for (int i = 0; i < numCircuits; i++) {
	 	for (int j = 0; j < sizeVec; j++) {
	 		cout << circuits[i][j] << " ";
	 	}
	 	cout << " Fitness: " << fitVec[i] << endl;
	 }
	 cout << endl;


	vector<int> best_circuit;
	// Genetic algorithm
	//cout << "Genetic algorithm" << endl;
	best_circuit = geneticAlgo(circuits, fitVec, minIte, maxIte, bestIndCnt, proCrosOver, proMut);

	// Print the output.
	cout << "Output best vector" << endl;
	for (int j = 0; j < sizeVec; j++) {
		cout << best_circuit[j] << " ";
	}

	Circuit circ(100.0, -500.0, 10, 100);
	double best_fitness;
	best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iterations);
	cout << "Fitness: " << best_fitness;
	cout << endl;



	// Timing.
	tdif += wTime();
	cout << setprecision(5);
	cout << endl << "Time of execution = " << tdif << "s." << endl << endl;



	system("pause");
}