#include "Header.h"
#include "Circuit.h"

using namespace std;


const int num_units = 10;
int sizeVec = 2 * num_units + 1;

// parameters for the Evaluate_Circuit function
double tol = 1e-6;
int max_iterations = 2000;


int main() {
	int numCircuits = 100;  // TO TUNE
	int maxIte = 15000;

	// Inputs for convergence
	int bestIndCnt = 1000; // Minimum naumber of iterations for the best circuit to be the same.
	int minIte = 10000; // minimum number of iterations to be done
	int maxIte = 15000; // maximum number of iterations possible


	// Genetic algorithm parameters.
	double proCrosOver = 0.2;  // Probability of cross-over.
	double proMut = 0.01;  // Probability of mutation.

	
	// random seed
	srand(time(NULL));

	// Circuit and list of circuits
	vector<int> circuit(sizeVec, 0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec, 0));

	// List of fitness values
	vector<double> fitVec(numCircuits, 0);

	
	// Generating the parents
	cout << "Generating parents" << endl;
	for (int i = 0; i < numCircuits; i++) {
		while(!Check_Validity(circuit)){  
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
	best_circuit = geneticAlgo(circuits, fitVec, minIte, maxIte, proCrosOver, proMut);

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
	

	//system("pause");
}
